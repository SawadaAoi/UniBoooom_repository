///* ========================================
//	HEW/UniBoooom!!
//	------------------------------------
//	UI管理用ソース
//	------------------------------------
//	UIStageManager.cpp
//	------------------------------------
//	作成者	tei
//
//	変更履歴
//	・2023/11/28 cpp作成UI用処理を入れます tei
//	・2023/12/08 シーン遷移用に関数追加 takagi
//	・2024/01/01 タイマーを変更・ステージ管理 takagi
//	・2024/01/21 コメント改修 takagi
//
//========================================== */
//
//#include "UIStageManager.h"
//#include "TimerStage1.h"	//ステージ1用タイマー
//#include "TimerStage2.h"	//ステージ2用タイマー
//#include "TimerStage3.h"	//ステージ3用タイマー
//
///* ========================================
//	デストラクタ関数
//	-------------------------------------
//	内容：デストラクタ
//	-------------------------------------
//	引数1：プレイヤーのポインタ
//	引数2：カメラのポインタ
//	引数3：スライム管理
//	引数4：ステージ番号
//	-------------------------------------
//	戻値：無し
//=========================================== */
//CUIStageManager::CUIStageManager(CPlayer* pPlayer,CCamera * pCamera, CSlimeManager* pSlimeMng, E_STAGE_NUM eStage)
//	: m_pBossGauge(nullptr)
//	, m_pCombo(nullptr)
//	, m_pHpMng(nullptr)
//	, m_pScoreOHMng(nullptr)
//	, m_pStageFin(nullptr)
//	, m_pTimer(nullptr)
//	, m_pTotalScore(nullptr)
//	, m_pBossArrow(nullptr)
//{
//	m_pCombo = new CCombo();
//
//	// =============== 動的確保 =====================
//	switch(eStage)
//	{
//	case E_STAGE_1:	//ステージ1
//		m_pTimer = new CTimerStage1();	//タイマー確保
//		break;							//分岐処理終了
//	case E_STAGE_2:	//ステージ2
//		m_pTimer = new CTimerStage2();	//タイマー確保
//		break;							//分岐処理終了
//	case E_STAGE_3:	//ステージ3
//		m_pTimer = new CTimerStage3();	//タイマー確保
//		break;							//分岐処理終了	
//	}
//	if (m_pTimer)	//分岐処理で動的確保失敗
//	{
//		m_pTimer = new CTimerStage1();	//タイマー確保
//	}
//
//	m_pBossGauge = new CBossGauge(m_pTimer);
//	m_pHpMng = new CHP_UI(pPlayer->GetHpPtr());
//	m_pTotalScore = new CTotalScore();
//	m_pScoreOHMng = new CScoreOHManager();
//	m_pStageFin = new CStageFinish(pCamera, pPlayer->GetHpPtr(), m_pTimer->GetTimePtr());
//	m_pBossArrow = new CBossArrow();
//
//	m_pCombo->SetTotalScore(m_pTotalScore);
//	m_pTimer->TimeStart();
//	m_pBossGauge->SetSlimeManager(pSlimeMng);
//	m_pScoreOHMng->SetCamera(pCamera);
//	m_pBossArrow->SetSlimeMng(pSlimeMng);
//	m_pBossArrow->SetPlayer(pPlayer);
//
//	/*
//	m_pBossGauge->AddBossGauge(BOSS_GAUGE_S1[0].startTime, BOSS_GAUGE_S1[0].maxTime);
//	m_pBossGauge->AddBossGauge(BOSS_GAUGE_S1[1].startTime, BOSS_GAUGE_S1[1].maxTime);*/
//
//}
//
///* ========================================
//	デストラクタ関数
//	-------------------------------------
//	内容：デストラクタ
//	-------------------------------------
//	引数1：無し
//	-------------------------------------
//	戻値：無し
//=========================================== */
//CUIStageManager::~CUIStageManager()
//{
//	SAFE_DELETE(m_pBossArrow);
//	SAFE_DELETE(m_pStageFin);
//	SAFE_DELETE(m_pHpMng);
//	SAFE_DELETE(m_pTimer);
//	SAFE_DELETE(m_pBossGauge);
//	SAFE_DELETE(m_pCombo);
//	SAFE_DELETE(m_pScoreOHMng);
//	SAFE_DELETE(m_pTotalScore);
//}
//
///* ========================================
//   更新処理関数
//   -------------------------------------
//   内容：更新処理
//   -------------------------------------
//   引数：無し
//   -------------------------------------
//   戻値：無し
//=========================================== */
//void CUIStageManager::Update()
//{
//	m_pTimer->Update();
//	m_pStageFin->Update();
//	m_pCombo->Update();
//	m_pHpMng->Update();
//	m_pBossGauge->Update();
//	m_pScoreOHMng->Update();
//	m_pBossArrow->Update();
//}
//
///* ========================================
//   描画処理関数
//   -------------------------------------
//   内容：描画処理
//   -------------------------------------
//   引数：無し
//   -------------------------------------
//   戻値：無し
//=========================================== */
//void CUIStageManager::Draw()
//{
//	m_pBossArrow->Draw();	// ボス方向矢印描画
//	m_pStageFin->Draw();	// ステージ終了描画
//	m_pTimer->Draw();		// タイマー描画
//	m_pCombo->Draw();		// コンボ描画
//	m_pHpMng->Draw();		// HPマネージャー描画
//	m_pTotalScore->Draw();	// トータルスコア描画
//	m_pBossGauge->Draw();	// ボスゲージ描画
//	m_pScoreOHMng->Draw();	// スコアマネージャー描画
//}
//
//CScoreOHManager* CUIStageManager::GetScoreMng()
//{
//	return m_pScoreOHMng;
//}
//
//CCombo * CUIStageManager::GetCombo()
//{
//	return m_pCombo;
//}
//
//CTimer * CUIStageManager::GetTimer()
//{
//	return m_pTimer;
//}
//
//CStageFinish * CUIStageManager::GetStageFinish()
//{
//	return m_pStageFin;
//}
//
//
//
//
//
///* ========================================
//   総スコアゲッタ関数
//   -------------------------------------
//   内容：総スコア取得
//   -------------------------------------
//   引数1：無し
//   -------------------------------------
//   戻値：総スコア
//=========================================== */
//int CUIStageManager::GetTotalScore()
//{
//	// =============== 提供 ===================
//	if (m_pTotalScore)	//ヌルチェック
//	{
//		return m_pTotalScore->GetTotalScore();	//総スコア
//	}
//	else
//	{
//		return 0;	//初期値で対応
//	}
//}
//
//CBossGauge* CUIStageManager::GetBossGauge()
//{
//	return m_pBossGauge;
//}
