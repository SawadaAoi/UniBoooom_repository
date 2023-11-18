/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボスゲージ
	------------------------------------
	BossGauge.cpp
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/17 cpp,作成 Tei

========================================== */

// =============== インクルード ===================
#include "BossGauge.h"
#include "Timer.h"

// =============== 定数定義 =======================
const int MAX_GAUGE = 45;	//マックスゲージ量(何秒に出現)


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CBossgauge::CBossgauge()
	:m_pBossGauge(nullptr)
	,m_nGaugeCnt(0)
	,m_bGaugeFull(false)
{
	//ボスゲージのテクスチャ読む込み
	/*m_pBossGauge = new Texture();

	if (FAILED(m_pBossGauge->Create("Assets/Texture/Star.png")))
	{
		MessageBox(NULL, "ItemUI Star.png", "Error", MB_OK);
	}*/
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
CBossgauge::~CBossgauge()
{
	if (m_pBossGauge)
	{
		delete m_pBossGauge;
		m_pBossGauge = nullptr;
	}
}

/* ========================================
	タイマー更新関数
	----------------------------------------
	内容：タイマーのカウントダウン処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::Update()
{

}

/* ========================================
	描画関数
	----------------------------------------
	内容：タイマーの描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(1080.0f, 100.0f, 10.0f);;
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	//スプライトの設定
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(100.0f, -100.0f));
	Sprite::SetTexture(m_pBossGauge);
	Sprite::Draw();
}
