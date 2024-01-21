/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UI管理用ヘッダ
	------------------------------------
	UIStageManager.h
	------------------------------------
	作成者	tei

	変更履歴
	・2023/11/28 ヘッダ作成UI用ヘッダ、メンバポインタを入れます tei
	・2023/12/08 シーン遷移用に関数追加 takagi
	・2023/12/15 ボスゲージの取得処理追加 sawada
	・2024/01/01 シーン番号列挙 takagi
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __UI_STAGE_MANAGER_H__	//UIStageManager.hインクルードガード
#define __UI_STAGE_MANAGER_H__

// =============== インクルード ===================
#include "TotalScore.h"
#include "BossGauge.h"
#include "StageFinishUI.h"
#include "HP_UI.h"
#include "Player.h"
#include "SlimeManager.h"
#include "BossArrow.h"


// =============== クラス定義 =====================
class CUIStageManager
{
public:
	enum E_STAGE_NUM
	{
		E_STAGE_1,
		E_STAGE_2,
		E_STAGE_3,
		E_STAGE_MAX,
	};
public:
	// ===メンバ関数宣言===
	CUIStageManager(CPlayer* pPlayer,CCamera* pCamera, CSlimeManager* pSlimeMng, E_STAGE_NUM eStage);
	~CUIStageManager();
	void Update();
	void Draw();
	CScoreOHManager* GetScoreMng();	//スコアマネージャーポインタを取得
	CCombo* GetCombo();	//コンボのポインタを取得
	CTimer* GetTimer();	//タイマーのポインタを取得
	CStageFinish* GetStageFinish();

	int GetTotalScore();	//総スコアゲッタ

	CBossgauge* GetBossGauge();
	
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
	CBossArrow* m_pBossArrow;

};

#endif	//!__UI_STAGE_MANAGER_H__