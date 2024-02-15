/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UI管理用cpp
	------------------------------------
	UIManager.cpp
	------------------------------------
	作成者 Tei

	変更履歴
	・2023/11/28 cpp作成UI用処理を入れます Tei
	・2023/12/08 シーン遷移用に関数追加 takagi
	・2024/01/01 タイマーを変更・ステージ管理 takagi
	・2024/02/11 ボス出現警告処理追加 Tei

========================================== */
#include "UIStageManager.h"
#include "TimerStage1.h"	//ステージ1用タイマー
#include "TimerStage2.h"	//ステージ2用タイマー
#include "TimerStage3.h"	//ステージ3用タイマー

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：プレイヤーのポインタ
	引数2：カメラのポインタ
	引数3：スライム管理
	引数4：ステージ番号
	-------------------------------------
	戻値：無し
=========================================== */
CUIStageManager::CUIStageManager(CPlayer* pPlayer,CCamera * pCamera, CSlimeManager* pSlimeMng, E_STAGE_NUM eStage)
	: m_pBossgauge(nullptr)
	, m_pCombo(nullptr)
	, m_pHpMng(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pStageFin(nullptr)
	, m_pTimer(nullptr)
	, m_pTotalScore(nullptr)
	, m_pBossArrow(nullptr)
	, m_pShowWarning(nullptr)
{
	m_pCombo = new CCombo();

	// =============== 動的確保 =====================
	switch(eStage)
	{
	case E_STAGE_1:	//ステージ1
		m_pTimer = new CTimerStage1();	//タイマー確保
		break;							//分岐処理終了
	case E_STAGE_2:	//ステージ2
		m_pTimer = new CTimerStage2();	//タイマー確保
		break;							//分岐処理終了
	case E_STAGE_3:	//ステージ3
		m_pTimer = new CTimerStage3();	//タイマー確保
		break;							//分岐処理終了	
	}
	if (m_pTimer)	//分岐処理で動的確保失敗
	{
		m_pTimer = new CTimerStage1();	//タイマー確保
	}

	m_pBossgauge = new CBossgauge(m_pTimer);
	m_pHpMng = new CHP_UI(pPlayer->GetHpPtr());
	m_pTotalScore = new CTotalScore();
	m_pScoreOHMng = new CScoreOHManager();
	m_pStageFin = new CStageFinish(pCamera, pPlayer, m_pTimer->GetTimePtr());
	m_pBossArrow = new CBossArrow();
	m_pShowWarning = new CShowWarning(static_cast<int>(eStage) + 1);

	m_pCombo->SetTotalScore(m_pTotalScore);
	m_pTimer->TimeStart();
	m_pBossgauge->SetSlimeManager(pSlimeMng);
	m_pBossgauge->SetShowWarning(m_pShowWarning);
	m_pScoreOHMng->SetCamera(pCamera);
	m_pBossArrow->SetSlimeMng(pSlimeMng);
	m_pBossArrow->SetPlayer(pPlayer);

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
CUIStageManager::~CUIStageManager()
{
	SAFE_DELETE(m_pShowWarning);
	SAFE_DELETE(m_pBossArrow);
	SAFE_DELETE(m_pStageFin);
	SAFE_DELETE(m_pHpMng);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pBossgauge);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pTotalScore);
}

/* ========================================
   更新処理関数
   -------------------------------------
   内容：更新処理
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：無し
=========================================== */
void CUIStageManager::Update()
{
	m_pTimer->Update();
	m_pStageFin->Update();
	m_pCombo->Update();
	m_pHpMng->Update();
	m_pBossgauge->Update();
	m_pTotalScore->Update();
	m_pScoreOHMng->Update();
	m_pBossArrow->Update();
	m_pShowWarning->Update();
}

/* ========================================
   描画処理関数
   -------------------------------------
   内容：描画処理
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：無し
=========================================== */
void CUIStageManager::Draw()
{
	m_pBossArrow->Draw();	// ボス方向矢印描画
	m_pStageFin->Draw();	// ステージ終了描画
	m_pTimer->Draw();		// タイマー描画
	m_pCombo->Draw();		// コンボ描画
	m_pHpMng->Draw();		// HPマネージャー描画
	m_pTotalScore->Draw();	// トータルスコア描画
	m_pBossgauge->Draw();	// ボスゲージ描画
	m_pScoreOHMng->Draw();	// スコアマネージャー描画
	m_pShowWarning->Draw();	// 警告描画
	
}

/* ========================================
   頭上スコアマネージャーポインタ取得処理関数
   -------------------------------------
   内容：頭上スコアマネージャーのポインタを返す
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：頭上スコアマネージャーのポインタ
=========================================== */
CScoreOHManager* CUIStageManager::GetScoreOHMngPtr()
{
	return m_pScoreOHMng;
}

/* ========================================
   コンボポインタ取得処理関数
   -------------------------------------
   内容：コンボのポインタを返す
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：コンボのポインタ
=========================================== */
CCombo* CUIStageManager::GetComboPtr()
{
	return m_pCombo;
}


/* ========================================
   タイマーポインタ取得処理関数
   -------------------------------------
   内容：タイマーのポインタを返す
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：タイマーのポインタ
=========================================== */
CTimer* CUIStageManager::GetTimerPtr()
{
	return m_pTimer;
}


/* ========================================
   ステージ終了判断オブジェクトポインタ取得処理関数
   -------------------------------------
   内容：ステージ終了判断オブジェクトのポインタを返す
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：ステージ終了判断オブジェクトのポインタ
=========================================== */
CStageFinish * CUIStageManager::GetStageFinishPtr()
{
	return m_pStageFin;
}


/* ========================================
   総スコアポインタ取得処理関数
   -------------------------------------
   内容：総スコアのポインタを返す
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：総スコアのポインタ
=========================================== */
CTotalScore * CUIStageManager::GetTotalScorePtr()
{
	return m_pTotalScore;
}


/* ========================================
   総スコアゲッタ関数
   -------------------------------------
   内容：総スコア取得
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：総スコア
=========================================== */
int CUIStageManager::GetTotalScore()
{
	// =============== 提供 ===================
	if (m_pTotalScore)	//ヌルチェック
	{
		return m_pTotalScore->GetTotalScore();	//総スコア
	}
	else
	{
		return 0;	//初期値で対応
	}
}

/* ========================================
   ボスゲージポインタゲッタ関数
   -------------------------------------
   内容：ボスゲージポインタ取得
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：総スコア
=========================================== */
CBossgauge* CUIStageManager::GetBossGaugePtr()
{
	return m_pBossgauge;
}


/* ========================================
   警告UIポインタゲッタ関数
   -------------------------------------
   内容：警告UIポインタ取得
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：総スコア
=========================================== */
CShowWarning* CUIStageManager::GetShowWarningPtr()
{
	return m_pShowWarning;
}
