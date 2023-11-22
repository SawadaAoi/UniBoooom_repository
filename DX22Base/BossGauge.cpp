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
	・2023/11/19 描画処理、ゲージ出現、消す処理追加 Tei

========================================== */

// =============== インクルード ===================
#include "BossGauge.h"
#include "Timer.h"

// =============== 定数定義 =======================

#if MODE_GAME_PARAMETER
#else
const int BOSS_GAUGE_FULL_TIME = 45 * 60;		//ボスゲージMAXになる時間(何秒出現) * 60フレーム
const int SECOND_EMPTY_BOSSGAUGE = 75 * 60;		//二体目のボス空ゲージ表す時間 * 60フレーム
const TPos2d<float> BOSSGAUGE_EMPTY_POS(765.0f, 25.0f);	//ボスゲージ（空）の位置設定
const TPos2d<float> BOSSGAUGE_FULL_POS(765.0f, 25.0f);	//ボスゲージ（満）の位置設定

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
CBossgauge::CBossgauge()
	:m_pBossGaugeEmpty(nullptr)
	,m_pBossGaugeFull(nullptr)
	,m_nGaugeCnt(0)
	,m_bGaugeFull(false)
	,m_bShowBossGauge(true)
{
	//ボスゲージのテクスチャ読む込み
	m_pBossGaugeEmpty = new Texture();
	m_pBossGaugeFull = new Texture();
	if (FAILED(m_pBossGaugeEmpty->Create("Assets/Texture/bossgauge_empty.png")))
	{
		MessageBox(NULL, "bossgauge_empty.png", "Error", MB_OK);
	}
	if (FAILED(m_pBossGaugeFull->Create("Assets/Texture/bossgauge_full.png")))
	{
		MessageBox(NULL, "bossgauge_full.png", "Error", MB_OK);
	}
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
	SAFE_DELETE(m_pBossGaugeEmpty);
	SAFE_DELETE(m_pBossGaugeFull);
}

/* ========================================
	更新関数
	----------------------------------------
	内容：時間をカウントして、出現の時間になったら、ボス出る、ゲージ消す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::Update()
{
	//ボス出現カウント
	m_nGaugeCnt++;
	if (m_nGaugeCnt == BOSS_GAUGE_FULL_TIME)
	{
		m_bGaugeFull = true;		//ゲージ満タン
		m_bShowBossGauge = false;	//ボス出現、ゲージフラグをfalseに、ゲージを消す

		//←TODOボス生成ボスの方に持っていくかここで呼ぶか
	}
	//二体目のボスのゲージ表示
	if (m_nGaugeCnt == SECOND_EMPTY_BOSSGAUGE)
	{
		m_bShowBossGauge = true;
		m_nGaugeCnt = 0;
	}
}

/* ========================================
	描画関数
	----------------------------------------
	内容：ボスゲージの描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::Draw()
{
	//ゲージ表示フラグfalseだったら return（表示しません）
	if (m_bShowBossGauge == false) return;

	//ボスゲージテクスチャ（空）
	DirectX::XMFLOAT4X4 bossempty[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldBossempty = DirectX::XMMatrixTranslation(BOSSGAUGE_EMPTY_POS.x,BOSSGAUGE_EMPTY_POS.y, 10.0f);;
	DirectX::XMStoreFloat4x4(&bossempty[0], DirectX::XMMatrixTranspose(worldBossempty));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&bossempty[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projBossempty = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&bossempty[2], DirectX::XMMatrixTranspose(projBossempty));

	//スプライトの設定
	Sprite::SetWorld(bossempty[0]);
	Sprite::SetView(bossempty[1]);
	Sprite::SetProjection(bossempty[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(100.0f, -100.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pBossGaugeEmpty);
	Sprite::Draw();

	float fFillGauge = 0;
	fFillGauge = (float)m_nGaugeCnt / (float)BOSS_GAUGE_FULL_TIME;
	FillGauge(fFillGauge);
}

/* ========================================
	ゲージュ増加関数
	----------------------------------------
	内容：ボスゲージ増加量の描画処理
	----------------------------------------
	引数1：ボスゲージ中の部分描く範囲
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::FillGauge(float textureRange)
{

	//ボスゲージテクスチャ（満）
	DirectX::XMFLOAT4X4 bossfull[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldBossfull = DirectX::XMMatrixTranslation(BOSSGAUGE_FULL_POS.x, BOSSGAUGE_FULL_POS.y + (50.0f - 50 * textureRange ), 10.0f);;
	DirectX::XMStoreFloat4x4(&bossfull[0], DirectX::XMMatrixTranspose(worldBossfull));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&bossfull[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projBossfull = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&bossfull[2], DirectX::XMMatrixTranspose(projBossfull));

	//スプライトの設定
	Sprite::SetWorld(bossfull[0]);
	Sprite::SetView(bossfull[1]);
	Sprite::SetProjection(bossfull[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(100.0f, (-textureRange * 100) ));		//描画大きさ設定
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, (1.0f - textureRange) ));		//描画のtextureの範囲設定
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, textureRange));				//表示するtextureの大きさ設定
	Sprite::SetTexture(m_pBossGaugeFull);
	Sprite::Draw();
}

