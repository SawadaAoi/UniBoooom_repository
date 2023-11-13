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
	�E2023/11/09 �J�����̈ړ���������悤�ɒn�ʒǉ����� ���؏x��
	�E2023/11/11 �X���C�����m���d�Ȃ�Ȃ�������ǉ� yamashita

========================================== */
#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

// =============== �C���N���[�h ===================
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Geometry.h"
#include "SlimeManager.h"
#include "Collision.h"
#include "Player.h"
#include "ExplosionManager.h"
#include "DirectWrite.h"
// =============== �N���X��` =====================
class SceneGame
{
public:
	// ===�����o�֐��錾===
	SceneGame(DirectWrite* pDirectWrite);
	~SceneGame();
	void Update(float tick);
	void Draw();

	void SceneGameCollision();
	void PlayerSlimeCollision();
	void HammerSlimeCollision();
	void SlimeSlimeCollision();
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();
	void SetDirectWrite(DirectWrite* pDirectWrite);
private:
	// ===�����o�ϐ��錾===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	DirectWrite* m_pDirectWrite;
};

#endif // __SCENE_GAME_H__