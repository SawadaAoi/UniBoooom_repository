/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ用抽象クラス定義
	---------------------------------------
	Stage.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/11/22 メンバ変数大量追加 nieda
========================================== */

#ifndef __STAGE_H__	//Stage.hインクルードガード
#define __STAGE_H__

// =============== インクルード ===================
#include "Scene.h"			//親のヘッダ
#include "Shader.h"
#include "Collision.h"
#include "Player.h"
#include "SlimeManager.h"
#include "ExplosionManager.h"
#include "Floor.h"
#include "Timer.h"
#include "StageFinishUI.h"
#include "Combo.h"
#include "Geometry.h"
#include "HP_UI.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Fade.h"
#include "BossGauge.h"
#include "ScoreOHManager.h"
#include "TotalScore.h"

// =============== クラス定義 =====================
class CStage :public CScene	//シーン
{
public:
	// =============== プロトタイプ宣言 ===============
	//CStage();							//コンストラクタ
	//virtual ~CStage();					//デストラクタ
	//virtual void Update();				//更新
	//virtual void Draw() const;			//描画	
	//virtual E_TYPE GetType() const = 0;	//自身の種類ゲッタ
	void Collision();
protected:
	void PlayerSlimeCollision();
	void PlayerBossCollision();		//追加
	void HammerSlimeCollision();
	void HammerBossCollision();		//追加
	void SlimeSlimeCollision();
	void SlimeBossCollision();		//追加
	void BossSlimeCollision();		//追加
	void BossBossCollision();		//追加
	void ExplosionBossCollision();	//追加
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();

	void SlimeBossNormalMoveCollision();		//追加
	void BossSlimeNormalMoveCollision();		//追加
	void BossBossNormalMoveCollision();			//追加
	// ===メンバ変数宣言===
	VertexShader* m_pVs;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CFloor* m_pFloor;
	CFade* m_pFade;
	CStageFinish* m_pStageFin;
	Texture* m_pTexture;
	CScoreOHManager* m_pScoreOHMng;
	CTotalScore* m_pTotalScore;
	CHP_UI* m_pHpMng;
	CBossgauge* m_pBossgauge;
	
};	//ステージ

#endif	//!__STAGE_H__