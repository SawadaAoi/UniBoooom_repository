/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スコア管理用cpp
	---------------------------------------
	ScoreManager.cpp

	作成者	山本凱翔

	変更履歴
	・2023/11/18　作成 yamamoto
	・2023/11/24　コメント追加 yamamoto
	・2024/02/13 UsingCamera使用 takagi

========================================== */

// =============== インクルード ===================
#include "ScoreOverHead.h"
#include "Sprite.h"
#include "GameParameter.h"		//定数定義用ヘッダー
#include "UsingCamera.h"	//カメラ使用

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：爆発の位置,スコア
	-------------------------------------
	戻値：なし
=========================================== */
CScoreOverHead::CScoreOverHead(TPos3d<float> fPos, int nScore, float posY,float fTime, bool delayFlg)
	: m_pScoreTexture(nullptr)
	, m_Transform(fPos, { 1.0f, 1.0f, 1.0f }, 0.0f)
	, digits{}
	, digitArray{}
	, nArraySize(0)
	, m_fDelFrame(0.0f)
	, m_fExplodeTime(fTime)	
	, m_bDelFlg(false)
	, m_bDelayFlg(delayFlg)
	, m_nDelayCnt(0)
{
	
	m_pScoreTexture = new Texture();
	//if (FAILED(m_pScoreTexture->Create("Assets/Texture/numbers_v1/number.png")))
	if (FAILED(m_pScoreTexture->Create("Assets/Texture/Score/score_numbers.png")))
	{
		MessageBox(NULL, "数字読み込み", "Error", MB_OK);
	}
	m_Transform.fPos.y += posY;
	//slimeのレベルによって爆発の大きさ変わるからslimeのとこで高さ調整する必要あり？
	//m_Transform.fPos.y

	// 数字を各桁ごとに配列に格納
	digitArray = digitsToArray(nScore);
	
	nArraySize = int(digitArray.size());
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CScoreOverHead::~CScoreOverHead()
{
	digits.clear();
	digitArray.clear();
	SAFE_DELETE(m_pScoreTexture);
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CScoreOverHead::Update()	//
{
	// スコア表示遅延処理が有効な場合
	if (m_bDelayFlg)
	{
		Delay();	// 遅延処理
		return;
	}

	DisplayTimeAdd();
}

/* ========================================
	描画処理関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CScoreOverHead::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, nullptr);		//DSVがnullだと2D表示になる

	DirectX::XMFLOAT4X4 mat[3];
	mat[1] = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();
	mat[2] = CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix();
	DirectX::XMFLOAT4X4 inv;//逆行列の格納先
	inv = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();

	//カメラの行列はGPUに渡す際に転置されているため、逆行列のために一度元に戻す
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);

	//移動成分は逆行列で打ち消す必要が無いので0を設定して移動を無視する
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);

	
	for (int i = 0; i < nArraySize; i++)
	{

		float width = 0.5f*i;


		DirectX::XMMATRIX world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x-width, m_Transform.fPos.y, m_Transform.fPos.z);
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
		Sprite::SetSize(DirectX::XMFLOAT2(0.5f, 0.5f));
		int y = digitArray[i] % 5;	//ここ名前募集します
		int x= digitArray[i] / 5;	//配列に入ってる数字の場所を計算してます
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));//0.2と0.5はtimeと同じなのであとでゲームパラメータに追加して変えます
		Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));

		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetTexture(m_pScoreTexture);
		Sprite::Draw();
		
	}


}
/* ========================================
	遅延処理関数
	-------------------------------------
	内容：スコアの表示を遅らせる
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CScoreOverHead::Delay()
{
	m_nDelayCnt++;

	// 遅延秒数が経ったら
	if (m_nDelayCnt >= DELAY_TIME)
	{
		m_bDelayFlg = false;	// 遅延フラグをオフにする
	}
}

/* ========================================
	スコア表示カウント加算処理関数
	-------------------------------------
	内容：スコア表示カウントを加算して一定秒数超えたら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CScoreOverHead::DisplayTimeAdd()
{
	m_fDelFrame++;	// フレーム加算
	// 一定秒数時間が経ったら
	if (m_fExplodeTime <= m_fDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}
}
/* ========================================
	配列収納処理関数
	-------------------------------------
	内容：表示したい数字を一桁ずつ配列に入れる
	-------------------------------------
	引数1：表示したいスコア
	-------------------------------------
	戻値：収納した配列
=========================================== */
std::vector<int> CScoreOverHead::digitsToArray(int score)
{
	//１の位から収納
	while (score > 0) {
		digits.push_back(score % 10);
		score /= 10;
	}
	
	return digits;
}
/* ========================================
	削除フラグ取得処理関数
	-------------------------------------
	内容：削除フラグを取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：削除フラグ(bool)
=========================================== */
bool CScoreOverHead::GetDelFlg()
{
	return m_bDelFlg;
}