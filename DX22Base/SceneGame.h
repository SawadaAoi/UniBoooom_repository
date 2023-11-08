#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�Q�[���V�[���p�w�b�_
	------------------------------------
	SceneGame.h
	------------------------------------
	�쐬�� �V�c

	�ύX����
	�E2023/11/08 �R�����g�ǉ��ƁA���ʂȉӏ����폜

========================================== */

// =============== �C���N���[�h ===================
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
#include "SlimeManager.h"
#include "Collision.h"
#include "Player.h"
#include "ExplosionManager.h"

// =============== �N���X��` =====================
class SceneGame
{
public:
	// ===�����o�֐��錾===
	SceneGame();
	~SceneGame();
	void Update(float tick);
	void Draw();

	void SceneGameCollision();
	void PlayerSlimeCollision();
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
private:
	// ===�����o�ϐ��錾===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CSlimeManager* m_pSlimeMng;
	CExplosionManager* m_pExplodeMng;
	CCOLLISION* m_pCollision;
};

#endif // __SCENE_GAME_H__