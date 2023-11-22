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

// =============== 定数定義 =======================

#if MODE_GAME_PARAMETER
#else
const int BOSS_GAUGE_FULL_TIME = 45 * 60;		//ボスゲージMAXになる時間(何秒出現) * 60フレーム
const int SECOND_EMPTY_BOSS_GAUGE = 75 * 60;		//二体目のボス空ゲージ表す時間 * 60フレーム
const TPos2d<float> BOSS_GAUGE_EMPTY_POS(765.0f, 25.0f);	//ボスゲージ（空）の位置設定
const TPos2d<float> BOSS_GAUGE_FULL_POS(765.0f, 25.0f);	//ボスゲージ（満）の位置設定
const float BOSS_GAUGE_EMPTY_SIZE_X = 100.0f;			//ボスゲージ（空）のXの長さ設定
const float BOSS_GAUGE_EMPTY_SIZE_Y = -100.0f;			//ボスゲージ（空）のYの長さ設定
const float BOSS_GAUGE_FULL_SIZE_X = 100.0f;			//ボスゲージ（満）のXの長さ設定
const float BOSS_GAUGE_FULL_POS_Y_ADJUST = 50.0f;		//ボスゲージ増加時、位置表示するための調整量
const float BOSS_GAUGE_FULL_SIZE_Y_ADJUST = -100.0f;		//ボスゲージ増加時、サイズ計算用（計算して表示したい比率かける元々のサイズ(-100.0f)）
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
	,m_pTimer(nullptr)
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
	m_pTimer = new CTimer();
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
	SAFE_DELETE(m_pTimer);
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
	m_nGaugeCnt++;	//ゲージ表示計算用の加算値
	if (STAGE_TIME - m_pTimer->GetNowTime() == BOSS_GAUGE_FULL_TIME)
	{
		m_bGaugeFull = true;		//ゲージ満タン
		m_bShowBossGauge = false;	//ボス出現、ゲージフラグをfalseに、ゲージを消す

		//←TODOボス生成ボスの方に持っていくかここで呼ぶか
	}
	//二体目のボスのゲージ表示
	if (STAGE_TIME - m_pTimer->GetNowTime() == SECOND_EMPTY_BOSS_GAUGE)
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
	DirectX::XMMATRIX worldBossempty = DirectX::XMMatrixTranslation(BOSS_GAUGE_EMPTY_POS.x,BOSS_GAUGE_EMPTY_POS.y, 0.0f);
	DirectX::XMStoreFloat4x4(&bossempty[0], DirectX::XMMatrixTranspose(worldBossempty));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&bossempty[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projBossempty = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&bossempty[2], DirectX::XMMatrixTranspose(projBossempty));

	//スプライトの設定
	Sprite::SetWorld(bossempty[0]);
	Sprite::SetView(bossempty[1]);
	Sprite::SetProjection(bossempty[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_GAUGE_EMPTY_SIZE_X, BOSS_GAUGE_EMPTY_SIZE_Y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pBossGaugeEmpty);
	Sprite::Draw();

	float fFillGauge = 0;
	fFillGauge = (float)m_nGaugeCnt / (float)BOSS_GAUGE_FULL_TIME;
	FillGaugeDraw(fFillGauge);
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
void CBossgauge::FillGaugeDraw(float textureRange)
{

	//ボスゲージテクスチャ（満）
	DirectX::XMFLOAT4X4 bossfull[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldBossfull = DirectX::XMMatrixTranslation(BOSS_GAUGE_FULL_POS.x, BOSS_GAUGE_FULL_POS.y + (BOSS_GAUGE_FULL_POS_Y_ADJUST - BOSS_GAUGE_FULL_POS_Y_ADJUST * textureRange ), 0.0f);
	DirectX::XMStoreFloat4x4(&bossfull[0], DirectX::XMMatrixTranspose(worldBossfull));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&bossfull[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projBossfull = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&bossfull[2], DirectX::XMMatrixTranspose(projBossfull));

	//スプライトの設定
	Sprite::SetWorld(bossfull[0]);
	Sprite::SetView(bossfull[1]);
	Sprite::SetProjection(bossfull[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_GAUGE_FULL_SIZE_X, (textureRange * BOSS_GAUGE_FULL_SIZE_Y_ADJUST) ));		//描画大きさ設定
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, (1.0f - textureRange) ));		//描画のtextureの範囲設定
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, textureRange));				//表示するtextureの大きさ設定
	Sprite::SetTexture(m_pBossGaugeFull);
	Sprite::Draw();
}

