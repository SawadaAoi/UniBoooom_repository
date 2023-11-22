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
#include "Camera.h"
#include "Collision.h"
#include "Player.h"
#include "SlimeManager.h"
#include "ExplosionManager.h"
#include "Floor.h"
#include "Timer.h"
#include "StageFinishUI.h"
#include "Combo.h"
#include "Fade.h"
	
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
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();
	// ===メンバ変数宣言===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CFloor* m_pFloor;
	CStageFinish* m_pStageFin;
	CFade* m_pFade;
	Texture* m_pTexture;
};	//ステージ

#endif	//!__STAGE_H__