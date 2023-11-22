/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	SceneGame�e�X�e�[�W�̓����蔻��p�w�b�_
	---------------------------------------
	CollisionOfStage.h
	------------------------------------
	�쐬�� �m�}����

	�ύX���� 2023/11/17 �V�K�쐬 �m�}����	

========================================== */

#ifndef __COLLISION_OF_STAGE_H__
#define __COLLISION_OF_STAGE_H__

// =============== �C���N���[�h ===================
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

// =============== �N���X��` =====================
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
	// ===�����o�ϐ��錾===
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	ChpManager* m_pHpMng;
};

#endif	//!__COLLISION_OF_STAGE_H__
