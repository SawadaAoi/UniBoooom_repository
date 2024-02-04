/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�p���ۃN���X��`
	---------------------------------------
	Stage.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/11/22 �����o�ϐ���ʒǉ� nieda
	�E2023/12/04 �|�[�Y�N���X�ǉ��E�f�X�g���N�^���� takagi
	�E2023/12/05 �R�����g�C�� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2023/12/08 �V�[���J�ڗp�ɕϐ��ǉ� takagi
	�E2023/12/12 Stage1���烁���o�ϐ����ړ� yamashita
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2023/12/15 �t�F�[�h�폜 takagi
	�E2023/12/16 �s�v�ȕϐ��ȂǍ폜 nieda
	�E2023/12/28 BattleData�i�[�������܂Ƃ߂��֐���ǉ�	Sawada
	�E2024/01/01 �X�e�[�W���� Takagi
	�E2024/01/15 GameFinish()�֐��̈����C���ERecordData()�֐��ǉ� Takagi
	�E2024/01/25 �q�b�g�G�t�F�N�g�֌W�̕ϐ��A�w�b�_�[�ǉ� Tei

========================================== */

#ifndef __STAGE_H__	//Stage.h�C���N���[�h�K�[�h
#define __STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"				//�e�̃w�b�_
#include "Shader.h"
#include "Collision.h"
#include "Player.h"
#include "SlimeManager.h"
#include "ExplosionManager.h"
#include "Floor.h"
#include "Timer.h"
#include "StageFinishUI.h"
#include "Combo.h"
#include "HP_UI.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Pause.h"				//�����o�̃w�b�_
#include "BossGauge.h"
#include "ScoreOHManager.h"
#include "TotalScore.h"
#include "Sound.h"
#include "UIStageManager.h"
#include "HitSlimeEffectManager.h"
#include "BattleData.h"			//�����o�̃w�b�_
#include "GameStartText.h"

// =============== �f�o�b�O���[�h ===================
#if _DEBUG
#define MODE_COORD_AXIS (true)	//���W���f�����ǂ���
#define SCENE_TRANSITION(false)	// �V�[���J�ڂ��{�^����������������؂�ւ��itrue�͎���)
#endif

// =============== �N���X��` =====================
class CStage :public CScene	//�V�[��
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	CStage(CUIStageManager::E_STAGE_NUM eStage);	//�R���X�g���N�^
	virtual ~CStage();								//�f�X�g���N�^
	//virtual void Update();				//�X�V
	//virtual void Draw() const;			//�`��	
	//virtual E_TYPE GetType() const = 0;	//���g�̎�ރQ�b�^
	void Collision();


protected:
	virtual void RecordData() = 0;	//�f�[�^�L�^
	void GameFinish();
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
	// ===�����o�ϐ��錾===
	VertexShader* m_pVs;
	CPlayer* m_pPlayer;
	CGeometry* m_pBox;
	CSlimeManager* m_pSlimeMng;
	CCOLLISION* m_pCollision;
	CExplosionManager* m_pExplosionMng;
	CFloor* m_pFloor;
	Texture* m_pTexture;
	CScoreOHManager* m_pScoreOHMng;
	CHealItemManager* m_pHealItemMng;
	CPause* m_pPause;						//�|�[�Y���
	CUIStageManager* m_pUIStageManager;
	BattleData m_Data;	//�퓬�f�[�^�L�^�p�ϐ�
	CStartText* m_pStartText;	// �Q�[���X�^�[�g�`��
	CHitSlimeEffectManager* m_pHitEffectMng;
	
	//�T�E���h
	XAUDIO2_BUFFER* m_pSEHitHammer;
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;

private:
	void LoadSE();
};	//�X�e�[�W

#endif	//!__STAGE_H__