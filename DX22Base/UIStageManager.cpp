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

========================================== */
#include "UIStageManager.h"

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：プレイヤーのポインタ
	引数2：カメラのポインタ
	-------------------------------------
	戻値：無し
=========================================== */
CUIStageManager::CUIStageManager(CPlayer* pPlayer, const CCamera * pCamera, CSlimeManager* pSlimeMng)
	: m_pBossgauge(nullptr)
	, m_pCombo(nullptr)
	, m_pHpMng(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pStageFin(nullptr)
	, m_pTimer(nullptr)
	, m_pTotalScore(nullptr)
{
	// コンボ数表示生成
	m_pCombo = new CCombo();

	//スコア生成
	m_pScoreOHMng = new CScoreOHManager();
	m_pScoreOHMng->SetCamera(pCamera);

	//トータルスコア生成
	m_pTotalScore = new CTotalScore();
	m_pCombo->SetTotalScore(m_pTotalScore);
	

	// タイマー生成
	m_pTimer = new CTimer();
	m_pTimer->TimeStart();

	//ステージ終了のUI表示
	m_pStageFin = new CStageFinish(pPlayer->GetHP(), m_pTimer->GetTimePtr());

	m_pHpMng = new CHP_UI(pPlayer->GetHP());

	//ボスゲージ
	m_pBossgauge = new CBossgauge(m_pTimer->GetNowTime());
	m_pBossgauge->SetSlimeManager(pSlimeMng);
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
	m_pScoreOHMng->Update();
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
	m_pStageFin->Draw();	// ステージ終了描画
	m_pTimer->Draw();		// タイマー描画
	m_pCombo->Draw();		// コンボ描画
	m_pHpMng->Draw();		// HPマネージャー描画
	m_pTotalScore->Draw();	// トータルスコア描画
	m_pBossgauge->Draw();	// ボスゲージ描画
	m_pScoreOHMng->Draw();	// スコアマネージャー描画
}

CScoreOHManager* CUIStageManager::GetScoreMng()
{
	return m_pScoreOHMng;
}

CCombo * CUIStageManager::GetCombo()
{
	return m_pCombo;
}

