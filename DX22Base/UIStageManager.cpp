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

========================================== */
#include "UIStageManager.h"

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F�v���C���[�̃|�C���^
	����2�F�J�����̃|�C���^
	-------------------------------------
	�ߒl�F����
=========================================== */
CUIStageManager::CUIStageManager(CPlayer* pPlayer, const CCamera * pCamera, CSlimeManager* pSlimeMng)
	: m_pBossgauge(nullptr)
	, m_pCombo(nullptr)
	, m_pHpMng(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pStageFin(nullptr)
	, m_pTimer(nullptr)
	, m_pTotalScore(nullptr)
{
	m_pCombo = new CCombo();
	m_pTimer = new CTimer();
	m_pBossgauge = new CBossgauge(m_pTimer->GetNowTime());
	m_pHpMng = new CHP_UI(pPlayer->GetHpPtr());
	m_pTotalScore = new CTotalScore();
	m_pScoreOHMng = new CScoreOHManager();
	m_pStageFin = new CStageFinish(pPlayer->GetHpPtr(), m_pTimer->GetTimePtr());


	m_pCombo->SetTotalScore(m_pTotalScore);
	m_pTimer->TimeStart();
	m_pBossgauge->SetSlimeManager(pSlimeMng);
	m_pScoreOHMng->SetCamera(pCamera);

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
	m_pScoreOHMng->Update();
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
	m_pStageFin->Draw();	// �X�e�[�W�I���`��
	m_pTimer->Draw();		// �^�C�}�[�`��
	m_pCombo->Draw();		// �R���{�`��
	m_pHpMng->Draw();		// HP�}�l�[�W���[�`��
	m_pTotalScore->Draw();	// �g�[�^���X�R�A�`��
	m_pBossgauge->Draw();	// �{�X�Q�[�W�`��
	m_pScoreOHMng->Draw();	// �X�R�A�}�l�[�W���[�`��
}

CScoreOHManager* CUIStageManager::GetScoreMng()
{
	return m_pScoreOHMng;
}

CCombo * CUIStageManager::GetCombo()
{
	return m_pCombo;
}
