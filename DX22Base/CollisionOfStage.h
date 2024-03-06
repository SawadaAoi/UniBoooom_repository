/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	SceneGame各ステージの当たり判定用ヘッダ
	---------------------------------------
	CollisionOfStage.h
	------------------------------------
	作成者 仁枝潤哉

	変更履歴 2023/11/17 新規作成 仁枝潤哉	

========================================== */

#ifndef __COLLISION_OF_STAGE_H__
#define __COLLISION_OF_STAGE_H__

// =============== インクルード ===================
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
#include "SlimeManager.h"
#include "Collision.h"
#include "Player.h"
#include "ExplosionManager.h"
#include "HpManager.h"
#include "DirectWrite.h"

// =============== クラス定義 =====================
class CCollisionOfStage
{
public:
	CCollisionOfStage();
	~CCollisionOfStage();
	void CollisionOfStage();
	void PlayerSlimeCollision();
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();
private:
	// ===メンバ変数宣言===
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	ChpManager* m_pHpMng;
};

#endif	//!__COLLISION_OF_STAGE_H__
