/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UI�Ǘ��pcpp
	------------------------------------
	UIManager.cpp
	------------------------------------
	�쐬�� Tei

	�ύX����
	�E2023/11/28 cpp�쐬UI�p���������܂� Tei
	�E2023/12/08 �V�[���J�ڗp�Ɋ֐��ǉ� takagi
	�E2024/01/01 �^�C�}�[��ύX�E�X�e�[�W�Ǘ� takagi
	�E2024/02/11 �{�X�o���x�������ǉ� Tei

========================================== */
#include "UIStageManager.h"
#include "TimerStage1.h"	//�X�e�[�W1�p�^�C�}�[
#include "TimerStage2.h"	//�X�e�[�W2�p�^�C�}�[
#include "TimerStage3.h"	//�X�e�[�W3�p�^�C�}�[

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F�v���C���[�̃|�C���^
	����2�F�J�����̃|�C���^
	����3�F�X���C���Ǘ�
	����4�F�X�e�[�W�ԍ�
	-------------------------------------
	�ߒl�F����
=========================================== */
CUIStageManager::CUIStageManager(CPlayer* pPlayer,CCamera * pCamera, CSlimeManager* pSlimeMng, E_STAGE_NUM eStage)
	: m_pBossgauge(nullptr)
	, m_pCombo(nullptr)
	, m_pHpMng(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pStageFin(nullptr)
	, m_pTimer(nullptr)
	, m_pTotalScore(nullptr)
	, m_pBossArrow(nullptr)
	, m_pShowWarning(nullptr)
{
	m_pCombo = new CCombo();

	// =============== ���I�m�� =====================
	switch(eStage)
	{
	case E_STAGE_1:	//�X�e�[�W1
		m_pTimer = new CTimerStage1();	//�^�C�}�[�m��
		break;							//���򏈗��I��
	case E_STAGE_2:	//�X�e�[�W2
		m_pTimer = new CTimerStage2();	//�^�C�}�[�m��
		break;							//���򏈗��I��
	case E_STAGE_3:	//�X�e�[�W3
		m_pTimer = new CTimerStage3();	//�^�C�}�[�m��
		break;							//���򏈗��I��	
	}
	if (m_pTimer)	//���򏈗��œ��I�m�ێ��s
	{
		m_pTimer = new CTimerStage1();	//�^�C�}�[�m��
	}

	m_pBossgauge = new CBossgauge(m_pTimer);
	m_pHpMng = new CHP_UI(pPlayer->GetHpPtr());
	m_pTotalScore = new CTotalScore();
	m_pScoreOHMng = new CScoreOHManager();
	m_pStageFin = new CStageFinish(pCamera, pPlayer, m_pTimer->GetTimePtr());
	m_pBossArrow = new CBossArrow();
	m_pShowWarning = new CShowWarning(static_cast<int>(eStage) + 1);

	m_pCombo->SetTotalScore(m_pTotalScore);
	m_pTimer->TimeStart();
	m_pBossgauge->SetSlimeManager(pSlimeMng);
	m_pBossgauge->SetShowWarning(m_pShowWarning);
	m_pScoreOHMng->SetCamera(pCamera);
	m_pBossArrow->SetSlimeMng(pSlimeMng);
	m_pBossArrow->SetPlayer(pPlayer);

}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CUIStageManager::~CUIStageManager()
{
	SAFE_DELETE(m_pShowWarning);
	SAFE_DELETE(m_pBossArrow);
	SAFE_DELETE(m_pStageFin);
	SAFE_DELETE(m_pHpMng);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pBossgauge);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pTotalScore);
}

/* ========================================
   �X�V�����֐�
   -------------------------------------
   ���e�F�X�V����
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F����
=========================================== */
void CUIStageManager::Update()
{
	m_pTimer->Update();
	m_pStageFin->Update();
	m_pCombo->Update();
	m_pHpMng->Update();
	m_pBossgauge->Update();
	m_pTotalScore->Update();
	m_pScoreOHMng->Update();
	m_pBossArrow->Update();
	m_pShowWarning->Update();
}

/* ========================================
   �`�揈���֐�
   -------------------------------------
   ���e�F�`�揈��
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F����
=========================================== */
void CUIStageManager::Draw()
{
	m_pBossArrow->Draw();	// �{�X�������`��
	m_pStageFin->Draw();	// �X�e�[�W�I���`��
	m_pTimer->Draw();		// �^�C�}�[�`��
	m_pCombo->Draw();		// �R���{�`��
	m_pHpMng->Draw();		// HP�}�l�[�W���[�`��
	m_pTotalScore->Draw();	// �g�[�^���X�R�A�`��
	m_pBossgauge->Draw();	// �{�X�Q�[�W�`��
	m_pScoreOHMng->Draw();	// �X�R�A�}�l�[�W���[�`��
	m_pShowWarning->Draw();	// �x���`��
	
}

/* ========================================
   ����X�R�A�}�l�[�W���[�|�C���^�擾�����֐�
   -------------------------------------
   ���e�F����X�R�A�}�l�[�W���[�̃|�C���^��Ԃ�
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F����X�R�A�}�l�[�W���[�̃|�C���^
=========================================== */
CScoreOHManager* CUIStageManager::GetScoreOHMngPtr()
{
	return m_pScoreOHMng;
}

/* ========================================
   �R���{�|�C���^�擾�����֐�
   -------------------------------------
   ���e�F�R���{�̃|�C���^��Ԃ�
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F�R���{�̃|�C���^
=========================================== */
CCombo* CUIStageManager::GetComboPtr()
{
	return m_pCombo;
}


/* ========================================
   �^�C�}�[�|�C���^�擾�����֐�
   -------------------------------------
   ���e�F�^�C�}�[�̃|�C���^��Ԃ�
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F�^�C�}�[�̃|�C���^
=========================================== */
CTimer* CUIStageManager::GetTimerPtr()
{
	return m_pTimer;
}


/* ========================================
   �X�e�[�W�I�����f�I�u�W�F�N�g�|�C���^�擾�����֐�
   -------------------------------------
   ���e�F�X�e�[�W�I�����f�I�u�W�F�N�g�̃|�C���^��Ԃ�
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F�X�e�[�W�I�����f�I�u�W�F�N�g�̃|�C���^
=========================================== */
CStageFinish * CUIStageManager::GetStageFinishPtr()
{
	return m_pStageFin;
}


/* ========================================
   ���X�R�A�|�C���^�擾�����֐�
   -------------------------------------
   ���e�F���X�R�A�̃|�C���^��Ԃ�
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F���X�R�A�̃|�C���^
=========================================== */
CTotalScore * CUIStageManager::GetTotalScorePtr()
{
	return m_pTotalScore;
}


/* ========================================
   ���X�R�A�Q�b�^�֐�
   -------------------------------------
   ���e�F���X�R�A�擾
   -------------------------------------
   ����1�F����
   -------------------------------------
   �ߒl�F���X�R�A
=========================================== */
int CUIStageManager::GetTotalScore()
{
	// =============== �� ===================
	if (m_pTotalScore)	//�k���`�F�b�N
	{
		return m_pTotalScore->GetTotalScore();	//���X�R�A
	}
	else
	{
		return 0;	//�����l�őΉ�
	}
}

/* ========================================
   �{�X�Q�[�W�|�C���^�Q�b�^�֐�
   -------------------------------------
   ���e�F�{�X�Q�[�W�|�C���^�擾
   -------------------------------------
   ����1�F����
   -------------------------------------
   �ߒl�F���X�R�A
=========================================== */
CBossgauge* CUIStageManager::GetBossGaugePtr()
{
	return m_pBossgauge;
}


/* ========================================
   �x��UI�|�C���^�Q�b�^�֐�
   -------------------------------------
   ���e�F�x��UI�|�C���^�擾
   -------------------------------------
   ����1�F����
   -------------------------------------
   �ߒl�F���X�R�A
=========================================== */
CShowWarning* CUIStageManager::GetShowWarningPtr()
{
	return m_pShowWarning;
}
