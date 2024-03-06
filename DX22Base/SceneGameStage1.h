/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�Q�[���V�[���̃X�e�[�W�P�p�w�b�_
	------------------------------------
	SceneGameStage1.h
	------------------------------------
	�쐬�� �m�}����

	�ύX����
	�E2023/11/17 �V�K�쐬 �m�}����

========================================== */
#ifndef __SCENE_GAME_STAGE1_H__
#define __SCENE_GAME_STAGE1_H__

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
#include "CollisionOfStage.h"
#include "DirectWrite.h"

// =============== �N���X��` =====================
class CSceneGameStage1
{
public:
	// ===�����o�֐��錾===
	CSceneGameStage1(DirectWrite* pDirectWrite);
	~CSceneGameStage1();
	void Update();
	void Draw();

	void SetDirectWrite(DirectWrite* pDirectWrite);
private:
	// ===�����o�ϐ��錾===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CExplosionManager* m_pExplosionMng;
	ChpManager* m_pHpMng;
	CCollisionOfStage* m_pColOfStg;
	DirectWrite* m_pDirectWrite;
};

#endif // !__SCENE_GAME_STAGE1_H__
