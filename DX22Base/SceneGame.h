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
	�E2023/11/09 �J�����̈ړ���������悤�ɒn�ʒǉ����� Takagi
	�E2023/11/11 �X���C�����m���d�Ȃ�Ȃ�������ǉ� Yamashita
	�E2023/11/19 �T�E���h�t�@�C���̓ǂݍ��݊֐���ǉ� Yamashita
	�E2023/11/19 �T�E���h�p�̃����o�ϐ���ǉ� Yamashita
	�E2023/11/21 �R���{�p�̃����o�ϐ���ǉ� Sawada
	�E2023/11/21 �{�X�p�̓����蔻��𑽐��ǉ� Suzumura
	�E2023/11/27 �񕜃A�C�e���̒ǉ� Sawada

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
#include "Floor.h"
#include "Fade.h"
#include "UIStageManager.h"
#include "Timer.h"

#include "ScoreOHManager.h"
#include "TotalScore.h"
#include "HealItemManager.h"

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
	void PlayerBossCollision();		//�ǉ�
	void PlayerHealItemCollision();
	void HammerSlimeCollision();
	void HammerBossCollision();		//�ǉ�
	void SlimeSlimeCollision();
	void SlimeBossCollision();		//�ǉ�
	void BossSlimeCollision();		//�ǉ�
	void BossBossCollision();		//�ǉ�
	void ExplosionBossCollision();	//�ǉ�
	void ExplosionSlimeCollision();
	void SlimeSlimeNormalMoveCollision();
	void SlimeBossNormalMoveCollision();		//�ǉ�
	void BossSlimeNormalMoveCollision();		//�ǉ�
	void BossBossNormalMoveCollision();			//�ǉ�

private:
	void LoadSound();	//�T�E���h�t�@�C���̓ǂݍ���
	// ===�����o�ϐ��錾===
	VertexShader* m_pVs;
	CCamera* m_pCamera;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	DirectWrite* m_pDirectWrite;
	CFloor* m_pFloor;
	CFade* m_pFade;
	CHealItemManager* m_pHealItemMng;

	CUIStageManager* m_pUIStageMng;				//UI�̃}�l�W���[

	XAUDIO2_BUFFER* m_pBGM;							//BGM�̉����f�[�^
	XAUDIO2_BUFFER* m_pSEHitHammer;					//SE�̉����f�[�^
	IXAudio2SourceVoice* m_pSpeaker;				//BGM�𕷂���鑤
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;		//SE�𕷂���鑤

};

#endif // __SCENE_GAME_H__