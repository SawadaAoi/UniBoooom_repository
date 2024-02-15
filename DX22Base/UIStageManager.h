/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UI�Ǘ��p�w�b�_
	------------------------------------
	UIManager.h
	------------------------------------
	�쐬�� Tei

	�ύX����
	�E2023/11/28 �w�b�_�쐬UI�p�w�b�_�A�����o�|�C���^�����܂� Tei
	�E2023/12/08 �V�[���J�ڗp�Ɋ֐��ǉ� takagi
	�E2023/12/15 �{�X�Q�[�W�̎擾�����ǉ� Sawada
	�E2024/01/01 �V�[���ԍ��� takagi
	�E2024/02/11 �{�X�o���x�������ǉ� Tei

========================================== */

#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

// =============== �C���N���[�h ===================
#include "TotalScore.h"
#include "BossGauge.h"
#include "StageFinishUI.h"
#include "HP_UI.h"
#include "Player.h"
#include "SlimeManager.h"
#include "BossArrow.h"
#include "ShowWarning.h"


// =============== �N���X��` =====================
class CUIStageManager
{
public:

	// === �� ===
	enum SE_Type
	{
		SE_ADD_SCORE,			 // �g�[�^���X�R�A���Z
		SE_BOSS_WARNING,		 // �{�X�x��

		SE_MAX			//SE�̑���
	};

	enum E_STAGE_NUM
	{
		E_STAGE_1,
		E_STAGE_2,
		E_STAGE_3,
		E_STAGE_MAX,
	};
public:
	// ===�����o�֐��錾===
	CUIStageManager(CPlayer* pPlayer,CCamera* pCamera, CSlimeManager* pSlimeMng, E_STAGE_NUM eStage);
	~CUIStageManager();
	void Update();
	void Draw();

	CScoreOHManager* GetScoreOHMngPtr();	//�X�R�A�}�l�[�W���[�|�C���^���擾
	CCombo* GetComboPtr();	//�R���{�̃|�C���^���擾
	CTimer* GetTimerPtr();	//�^�C�}�[�̃|�C���^���擾
	CStageFinish* GetStageFinishPtr();
	CTotalScore* GetTotalScorePtr();


	int GetTotalScore();	//���X�R�A�Q�b�^

	CBossgauge* GetBossGaugePtr();
	CShowWarning* GetShowWarningPtr();

	void PlaySE(SE_Type se, float volume = 1.0f);
	void StopSE(SE_Type se);
	void LoadSound();

private:

	// ===�����o�ϐ��錾===

	//�e�K�v�ȃ����o�[�|�C���^��		
	CHP_UI* m_pHpMng;
	CTimer* m_pTimer;
	CCombo* m_pCombo;
	CBossgauge* m_pBossgauge;
	CTotalScore* m_pTotalScore;
	CScoreOHManager* m_pScoreOHMng;
	CStageFinish* m_pStageFin;
	CBossArrow* m_pBossArrow;
	CShowWarning* m_pShowWarning;

	//=====SE�֘A=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];

	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/AddScore.mp3",			// �g�[�^���X�R�A���Z
		"Assets/Sound/SE/BossWarnig.mp3",		// �{�X�x��

	};

};

#endif // __UI_MANAGER_H__