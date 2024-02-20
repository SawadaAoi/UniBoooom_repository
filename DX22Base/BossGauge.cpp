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
	・2023/11/22 ボスゲージ表示のフェードアウト追加、パラメータ調整
	・2023/11/27 ボス出現処理追加	Sawada
	・2023/12/07 ゲームパラメータから一部定数移動・インクルード追加 takagi
	・2024/02/16 ボスゲージスケールモーション追加 Tei

========================================== */

// =============== インクルード ===================
#include "BossGauge.h"
#include "Timer.h"	//STAGE_TIME用

// =============== 定数定義 =======================
const TPos2d<float> BOSS_GAUGE_FRAME_POS(765.0f, 45.0f);		// ボスゲージ（枠）の位置設定
const TPos2d<float> BOSS_GAUGE_FULL_POS(765.0f, 46.5f);			// ボスゲージ（中身）の位置設定
const TPos2d<float> BOSS_GAUGE_FRAME_SIZE = { 60.0f ,-60.0f };	// ボスゲージ（枠）の大きさ
const TPos2d<float> BOSS_GAUGE_FULL_SIZE = {					// ボスゲージ（中身）の大きさ
	(6.0f / 7.0f) * BOSS_GAUGE_FRAME_SIZE.x ,
	(6.0f / 7.0f) * BOSS_GAUGE_FRAME_SIZE.y };			
const float BOSS_GAUGE_FULL_POS_Y_ADJUST = BOSS_GAUGE_FULL_SIZE.x / 2;		//ボスゲージ（中身）増加時、位置表示するための調整量
const float BOSS_GAUGE_FULL_SIZE_Y_ADJUST = BOSS_GAUGE_FULL_SIZE.y;			//ボスゲージ（中身）増加時、サイズ計算用（計算して表示したい比率かける元々のサイズ(100.0f)）
const float BOSS_GAUGE_WARNING_PER = 0.7f;			// ボスゲージ7割
const float BOSS_GAUGE_SCALE_NORMAL = 0.0025f;		// 普段拡大縮小の比率
const float BOSS_GAUGE_SCALE_WARNING = 0.02f;		// ボス出現前拡大縮小の比率(少し大きく)
const int GAUGE_SCALE_SPEED_NORMAL = 120;			// 拡大縮小一回のフレーム数(120flame一回遅い)
const int GAUGE_SCALE_SPEED_WARNING = 30;			// 拡大縮小一回のフレーム数(30flame一回速い)
#if MODE_GAME_PARAMETER
#else
typedef struct
{
	float startTime;	// 開始時間(秒)
	float maxTime;		// ゲージ経過最大時間(秒)

}BossGaugeSetParam;

const BossGaugeSetParam BOSS_GAUGE_S1[2] = { {0, 45},{75, 45} };	// ステージ1のボスゲージ設定
const int FADE_TIME = 5 * 60;										// ボスゲージが溜まってから消える時間
#endif


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：int 現在の時間取る
	----------------------------------------
	戻値：なし
=========================================== */
CBossgauge::CBossgauge(CTimer* pTimer)
	: m_pTexFrame(nullptr)
	, m_pTexGauge(nullptr)
	, m_pTimer(pTimer)
	, m_fBossgaugeScale(1.0f)	// ボスゲージスケール倍率、普段は1.0f
	, m_nBossgaugeScaleCnt(0)
{

	//ボスゲージのテクスチャ読む込み
	m_pTexFrame = new Texture();
	m_pTexGauge = new Texture();
	if (FAILED(m_pTexFrame->Create("Assets/Texture/Boss_UI/Gauge/bossgauge_empty.png")))
	{
		MessageBox(NULL, "bossgauge_empty.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexGauge->Create("Assets/Texture/Boss_UI/Gauge/bossgauge_full.png")))
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
	SAFE_DELETE(m_pTexFrame);
	SAFE_DELETE(m_pTexGauge);
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
	// ボスゲージ配列数分(表示するボス数分)
	for (auto itr = m_BossGauges.begin(); itr != m_BossGauges.end(); ++itr)
	{
		// ボスゲージ開始時間よりも前の場合
		if ((*itr).nStartFrame >= m_pTimer->GetErapsedTime()) continue;
		// 削除済みのボスゲージの場合
		if ((*itr).bDelFlg == true) continue;

		// ゲージ加算値 < 最大加算値(最大までゲージが溜まってない)
		if ((*itr).nGaugeCnt < (*itr).nMaxGaugeFrame)
		{
			(*itr).nGaugeCnt++;
			(*itr).fGaugeDispPer = (float)((*itr).nGaugeCnt) / (float)(*itr).nMaxGaugeFrame;
			
			// ---ボスゲージ拡大縮小処理---
			// ゲージ7割になったら緊張感がある拡大縮小モーションする
			if ((*itr).fGaugeDispPer >= BOSS_GAUGE_WARNING_PER)		
			{
				BossGaugeScaleMotion(BOSS_GAUGE_SCALE_WARNING, GAUGE_SCALE_SPEED_WARNING);
			}
			// 普段の拡大縮小モーション
			else
			{
				BossGaugeScaleMotion(BOSS_GAUGE_SCALE_NORMAL, GAUGE_SCALE_SPEED_NORMAL);
			}
		}
		//　ゲージが最大までたまった場合
		else
		{
			// フェードフラグがまだオフの場合
			if ((*itr).bFadeFlg == false)
			{
				m_pShowWarn->StartShowWarning();			// ボス警告開始
				m_pSlimeMng->CreateBoss((*itr).nBossNum);	// ボススライムを生成
				(*itr).bFadeFlg = true;		// フェードフラグオン
			}
			else
			{
				(*itr).nFadeCnt++;
				// フェード時間経過したか
				if (FADE_TIME <= (*itr).nFadeCnt)
				{
					(*itr).bDelFlg = true;	// 削除フラグをオン
				}
			}
		}
		



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
	// ボスゲージ配列数分(表示するボス数分)
	for (auto itr = m_BossGauges.begin(); itr != m_BossGauges.end(); ++itr)
	{
		// ボスゲージ開始時間よりも前の場合
		if ((*itr).nStartFrame >= m_pTimer->GetErapsedTime()) continue;
		// 削除済みのボスゲージの場合
		if ((*itr).bDelFlg == true) continue;
		

		DrawFrame(itr);		// 枠の表示
		DrawGauge(itr);		// ゲージの表示

	}
}

/* ========================================
	ボスゲージ枠描画関数
	----------------------------------------
	内容：ボスゲージの描画処理
	----------------------------------------
	引数1：イテレータ
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::DrawFrame(std::vector<BossGauge>::iterator itr)
{
	//ボスゲージテクスチャ（空）
	DirectX::XMFLOAT4X4 bossempty[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldBossempty = DirectX::XMMatrixTranslation(BOSS_GAUGE_FRAME_POS.x, BOSS_GAUGE_FRAME_POS.y, 0.0f);
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
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_GAUGE_FRAME_SIZE.x * m_fBossgaugeScale, BOSS_GAUGE_FRAME_SIZE.y * m_fBossgaugeScale));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f - ((float)(*itr).nFadeCnt / (float)FADE_TIME)));
	Sprite::SetTexture(m_pTexFrame);
	Sprite::Draw();
}

/* ========================================
	ゲージ増加関数
	----------------------------------------
	内容：ボスゲージ増加量の描画処理
	----------------------------------------
	引数1：イテレータ
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::DrawGauge(std::vector<BossGauge>::iterator itr)
{

	//ボスゲージテクスチャ（満）
	DirectX::XMFLOAT4X4 bossfull[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldBossfull = DirectX::XMMatrixTranslation(
		BOSS_GAUGE_FULL_POS.x, 
		(BOSS_GAUGE_FULL_POS.y + (BOSS_GAUGE_FULL_POS_Y_ADJUST - (BOSS_GAUGE_FULL_POS_Y_ADJUST * (*itr).fGaugeDispPer)) * m_fBossgaugeScale)
		, 0.0f);
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
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_GAUGE_FULL_SIZE.x * m_fBossgaugeScale, ((*itr).fGaugeDispPer * BOSS_GAUGE_FULL_SIZE_Y_ADJUST) * m_fBossgaugeScale));		//描画大きさ設定
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, (1.0f - (*itr).fGaugeDispPer)));		//描画のtextureの範囲設定
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, (*itr).fGaugeDispPer));				//表示するtextureの大きさ設定
	Sprite::SetTexture(m_pTexGauge);
	Sprite::Draw();
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

}


/* ========================================
	スライム管理ポインタセット関数
	----------------------------------------
	内容：スライム管理のポインタをセットする
	----------------------------------------
	引数1：スライム管理ポインタ
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::SetSlimeManager(CSlimeManager* pSlimeMng)
{
	m_pSlimeMng = pSlimeMng;
}

/* ========================================
	ボス警告ポインタセット関数
	----------------------------------------
	内容：ボス警告のポインタをセットする
	----------------------------------------
	引数1：ボス警告ポインタ
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::SetShowWarning(CShowWarning* pShowWarn)
{
	m_pShowWarn = pShowWarn;
}

/* ========================================
	ボスゲージセット関数
	----------------------------------------
	内容：ボスゲージ情報をセットする
	----------------------------------------
	引数1：開始時間
	引数1：最大時間
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::AddBossGauge(int BossNum, float fStartTime, float fMaxTime)
{
	BossGauge addPram = { 
		BossNum,
		false,				// 削除フラグ
		false,				// フェードフラグ
		fStartTime * 60,	// 開始時間Frame
		fMaxTime * 60,		// 最大値Frame
		0,					// ゲージ加算
		0,					// フェード加算
		0.0f,				// 表示割合 
	};

	m_BossGauges.push_back(addPram);	// 配列に追加

}

/* ========================================
	ボスゲージ拡大縮小関数
	----------------------------------------
	内容：ボスゲージ拡大縮小する
	----------------------------------------
	引数1：拡大縮小のサイズ
	引数2：一回の拡大縮小のフレーム数
	----------------------------------------
	戻値：なし
=========================================== */
void CBossgauge::BossGaugeScaleMotion(float fSize, int nFlame)
{
	m_nBossgaugeScaleCnt++;										// タイマーフレームカウント加算
	if (m_nBossgaugeScaleCnt % nFlame <= (nFlame / 2) - 1)		//設定したフレーム数の前半加算(拡大)、後半減算(縮小)
	{
		m_fBossgaugeScale += fSize;
	}
	else
	{
		m_fBossgaugeScale -= fSize;
	}
}

