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
	�E2023/11/19 �T�E���h�t�@�C���̓ǂݍ��݊֐���ǉ� yamashita
	�E2023/11/19 �T�E���h�p�̃����o�ϐ���ǉ� yamashita
	�E2023/11/21 �R���{�p�̃����o�ϐ���ǉ� Sawada

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
#include "HP_UI.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Floor.h"
#include "StageFinishUI.h"
#include "Combo.h"
#include "Fade.h"
#include "BossGauge.h"

#include "ScoreOHManager.h"
#include "TotalScore.h"
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
	void SlimeSlimeNormalMoveCollision();
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
	CHP_UI* m_pHpMng;
	DirectWrite* m_pDirectWrite;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CBossgauge* m_pBossgauge;
	CFloor* m_pFloor;
	CStageFinish* m_pStageFin;
	CFade* m_pFade;
	CTotalScore* m_pTotalScore;

	CScoreOHManager* m_pScoreOHMng;
	XAUDIO2_BUFFER* m_pBGM;							//BGM�̉����f�[�^
	XAUDIO2_BUFFER* m_pSEHitHammer;					//SE�̉����f�[�^
	IXAudio2SourceVoice* m_pSpeaker;				//BGM�𕷂���鑤
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;		//SE�𕷂���鑤

};

#endif // __SCENE_GAME_H__