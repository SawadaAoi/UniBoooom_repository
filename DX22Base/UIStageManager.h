/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UI管理用ヘッダ
	------------------------------------
	UIManager.h
	------------------------------------
	作成者 Tei

	変更履歴
	・2023/11/28 ヘッダ作成UI用ヘッダ、メンバポインタを入れます Tei

========================================== */

#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

// =============== インクルード ===================
#include "TotalScore.h"
#include "BossGauge.h"
#include "StageFinishUI.h"
#include "HP_UI.h"
#include "Player.h"
#include "SlimeManager.h"

// =============== クラス定義 =====================
class CUIStageManager
{
public:
	// ===メンバ関数宣言===
	CUIStageManager(CPlayer* pPlayer,const CCamera* pCamera, CSlimeManager* pSlimeMng);
	~CUIStageManager();
	void Update();
	void Draw();
	CScoreOHManager* GetScoreMng();	//スコアマネージャーポインタを取得
	CCombo* GetCombo();	//コンボのポインタを取得
	CTimer* GetTimer();	//タイマーのポインタを取得

	
private:
	
	// ===メンバ変数宣言===

	//各必要なメンバーポインタ↓		
	CHP_UI* m_pHpMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CBossgauge* m_pBossgauge;
	CTotalScore* m_pTotalScore;
	CScoreOHManager* m_pScoreOHMng;
	CStageFinish* m_pStageFin;
};

#endif // __UI_MANAGER_H__