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
	・2023/12/07 ゲームパラメータから定数移動 takagi
	・2024/02/09 UsingCamera使用 takagi
	・2024/02/13 カメラ削除 takagi
	・2024/02/20 拡縮アニメーション実装 suzumura

========================================== */

// =============== インクルード ===================
#include "BoooomUI.h"
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 ===================
const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUIのXの長さ（textureの比率と合わせる）
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUIのYの長さ（textureの比率と合わせる）

#if MODE_GAME_PARAMETER
#else
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUIサイズのスケール
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUIサイズのスケール
const float BOOOOM_UI_MAX_SCALE_X = BOOOOM_UI_SCALE_X * 2.2f;	//アニメーション用拡縮最大サイズ_X
const float BOOOOM_UI_MAX_SCALE_Y = BOOOOM_UI_SCALE_Y * 2.2f;	//アニメーション用拡縮最大サイズ_Y
const float ANIM_TIME_RATE = 0.7f;	// 爆発総時間の内、BOOOOM表示を行うのは何割か(0.0f~1.0f)
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
CBoooomUI::CBoooomUI(TPos3d<float> pos, Texture* pTex, float fTime)
	:m_pBoooomTex(pTex)
	,m_pos(pos)
	,m_scale{ BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f}
	,m_fExplodeTime(fTime * ANIM_TIME_RATE)
	,m_nDelFrame(0)
	,m_bDelFlg(false)
	,m_nAnimFrame(0)
	,m_fAnimRate(0.0f)
	,m_fAddScaleX(0.0f)
	,m_fAddScaleY(0.0f)
	,m_fScalingTime(fTime * ANIM_TIME_RATE)
	,m_fAlpha(1.0f)
{
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

	m_nAnimFrame++;
	ScalingAnim();	//拡縮アニメーション
	


}

/* ========================================
	描画関数
	----------------------------------------
	内容：Boooomの描画
	----------------------------------------
	引数1：描画モード
	----------------------------------------
	戻値：なし
=========================================== */
void CBoooomUI::Draw()
{

	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, nullptr);		//DSVがnullだと2D表示になる

	DirectX::XMFLOAT4X4 mat[3];
	mat[1] = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();
	mat[2] = CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix();

	DirectX::XMFLOAT4X4 inv;	//逆行列(inverse)の格納先
	inv = CUsingCamera::GetThis().GetCamera()->GetViewMatrix();

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
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fAlpha));
	Sprite::Draw();

	SetRenderTargets(1, &pRTV, pDSV);		//爆発モデルと一緒に描画するために3Dに戻る
}

/*========================================
boooomUIアニメーション処理関数
------------------------------------ -
内容：boooomUIの拡縮のアニメーションを処理する
------------------------------------ -
引数1：無し
------------------------------------ -
戻値：無し
========================================== = */
void CBoooomUI::ScalingAnim()
{
	// 拡縮時間の内、"拡大"する時間を設定
	float fExpandTime = m_fScalingTime / 2.0f;

	//-- 拡大
	if (m_nAnimFrame < (int)fExpandTime)
	{
		m_fAnimRate += 1.0f / fExpandTime;	//フレーム加算

	}
	//-- 縮小
	else if (m_nAnimFrame >= 0)
	{
		m_fAnimRate -= 1.0f / (m_fScalingTime - fExpandTime);	//フレーム減算

		//-- 徐々に消えていく処理
		m_fAlpha -= 0.01f;	//透明度更新
	}
	// 0を下回らないように
	if (m_fAnimRate < 0) m_fAnimRate = 0;

	// 補間値を使用してスケールを計算
	float scalingFactor = (sqrt(1 - pow(m_fAnimRate - 1, 2)));
	// スケールの設定
	m_scale = TPos3d<float>(BOOOOM_UI_SCALE_X + ((BOOOOM_UI_MAX_SCALE_X - BOOOOM_UI_SCALE_X) * scalingFactor),
		BOOOOM_UI_SCALE_Y + ((BOOOOM_UI_MAX_SCALE_Y - BOOOOM_UI_SCALE_Y) * scalingFactor), 0.0f);
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
