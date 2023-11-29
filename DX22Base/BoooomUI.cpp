/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	BoooomUI表示
	------------------------------------
	BoooomUI.cpp
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/20 cpp,作成 Tei
	・2023/11/20 描画で必要な関数を作成 Tei

========================================== */

// =============== インクルード ===================
#include "BoooomUI.h"
#include "GameParameter.h"

// =============== 定数定義 ===================
#if MODE_GAME_PARAMETER
#else
const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUIのXの長さ
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUIのYの長さ
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUIのスケール
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUIのスケール
#endif
/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CBoooomUI::CBoooomUI(TPos3d<float> pos, Texture* pTex, const CCamera* pCamera, float fTime)
	:m_pBoooomTex(pTex)
	,m_pos(pos)
	,m_scale{ BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f}
	,m_fExplodeTime(0.0f)
	,m_nDelFrame(0)
	,m_bDelFlg(false)
{
	
	m_pCamera = pCamera;		//カメラセット
	m_fExplodeTime = fTime;		//爆発総時間をセットする
		
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CBoooomUI::~CBoooomUI()
{
	
}

void CBoooomUI::Update()
{
	DisplayTimeAdd();
	//TODO爆発連鎖するときのスケール ?
}

/* ========================================
	描画関数
	----------------------------------------
	内容：Boooomの描画
	----------------------------------------
	引数1：爆発位置
	----------------------------------------
	戻値：なし
=========================================== */
void CBoooomUI::Draw()
{

	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, nullptr);		//DSVがnullだと2D表示になる

	DirectX::XMFLOAT4X4 mat[3];
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	DirectX::XMFLOAT4X4 inv;	//逆行列(inverse)の格納先
	inv = m_pCamera->GetViewMatrix();

	//カメラの行列なGPUに渡す際に転置されているため、逆行列の計算のために一度元に戻す
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);	//invに格納されたカメラ行列を変換
	matInv = DirectX::XMMatrixTranspose(matInv);	//matInvを転置する

	////移動成分は逆行列でうち消す必要がないので、0を設定して移動を無視する
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);	//逆行列の計算

	DirectX::XMMATRIX UI = matInv * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);	//ワールド行列とビルボードの行列をかけ合わせたもの（複数行）
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(UI));
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOOOOM_UI_SIZE_X * m_scale.x, BOOOOM_UI_SIZE_Y * m_scale.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pBoooomTex);	//ビルボードで表示したいテクスチャ
	Sprite::Draw();

	SetRenderTargets(1, &pRTV, pDSV);		//爆発モデルと一緒に描画するために3Dに戻る
}

/* ========================================
	boooomUI表示カウント加算処理関数
	-------------------------------------
	内容：boooomUI表示カウントを加算して一定秒数超えたら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CBoooomUI::DisplayTimeAdd()
{
	m_nDelFrame++;		// フレーム加算

	// 一定秒数時間が経ったら
	if (m_fExplodeTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}

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
bool CBoooomUI::GetDelFlg()
{
	return m_bDelFlg;
}

/* ========================================
	カメラ情報セット関数
	----------------------------------------
	内容：描画処理で使用するカメラ情報セット
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CBoooomUI::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}