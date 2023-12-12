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
#include "Geometry.h"
#include "HP_UI.h"
#include "DirectWrite.h"
#include "Timer.h"
#include "Fade.h"
#include "Pause.h"				//�����o�̃w�b�_
#include "BossGauge.h"
#include "ScoreOHManager.h"
#include "TotalScore.h"
#include "Sound.h"
#include "UIStageManager.h"
#include "BattleData.h"			//�����o�̃w�b�_

// =============== �N���X��` =====================
class CStage :public CScene	//�V�[��
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	CStage();							//�R���X�g���N�^
	virtual ~CStage();					//�f�X�g���N�^
	//virtual void Update();				//�X�V
	//virtual void Draw() const;			//�`��	
	//virtual E_TYPE GetType() const = 0;	//���g�̎�ރQ�b�^
	void Collision();
protected:
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
	//CTimer* m_pTimer;
	//CCombo* m_pCombo;
	CFloor* m_pFloor;
	CFade* m_pFade;
	//CStageFinish* m_pStageFin;
	Texture* m_pTexture;
	CScoreOHManager* m_pScoreOHMng;
	////CTotalScore* m_pTotalScore;
	//CHP_UI* m_pHpMng;
	//CBossgauge* m_pBossgauge;
	CHealItemManager* m_pHealItemMng;
	CPause* m_pPause;						//�|�[�Y���
	CUIStageManager* m_pUIStageManager;
	BattleData m_Data;	//�퓬�f�[�^�L�^�p�ϐ�

	int m_nNum;			// �Q�[���X�^�[�g�\���J�E���g�p
	float m_fSize;		// �Q�[���X�^�[�g�\���̃T�C�Y
	float m_fResize;	// �Q�[���X�^�[�g�\���̃T�C�Y�ύX�p
	bool m_bStart;		// �Q�[�����J�n�����邩����
	const int* m_pPlayerHp;		// �v���C���[HP�擾�p
	const int* m_pTimeCnt;		// �������Ԏ擾�p

	TPos2d<float> m_fUVPos;	// UV���W�ۑ��p
	int m_nCntSwitch;	// �A�j���[�V�����؂�ւ��J�E���g�p
	int m_nCntW;		// ���J�E���g�p
	int m_nCntH;		// �c�J�E���g�p
	bool m_bStartSign;		// �X�^�[�g���}�J�n�t��


	//�T�E���h
	XAUDIO2_BUFFER* m_pSEHitHammer;
	IXAudio2SourceVoice* m_pSEHitHammerSpeaker;

private:
	void LoadSE();
};	//�X�e�[�W

#endif	//!__STAGE_H__