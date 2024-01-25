/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W2����
	---------------------------------------
	Stage2.cpp
	---------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 Stage1�̓��e���R�s�[ yamashita
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2023/12/15 �Q�[���X�^�[�g�\���������ς� nieda
	�E2023/12/18 �f�o�b�O���[�h�폜���f takagi
	�E2024/01/01 �e�R���X�g���N�^�Ăяo�� takagi
	�E2024/01/15 GameFinish()�֐��C���ERecordData()�֐��ǉ� takagi
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Stage2.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//�q�b�g�X�g�b�v
#include "Fade.h"

// =============== �萔�E�}�N����` ===================
const int STAGE_NUM = 2;	//�X�e�[�W�ԍ�

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CStage2::CStage2()
{
	// =============== ���I�m�� =====================
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress(), CFloor::Stage2);
	m_pFloor->SetCamera(m_pCamera);
}

/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CStage2::~CStage2()
{
	// =============== �L�^ =====================
	RecordData();	//�f�[�^�L�^
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
//void CStage2::Update()
//{
//	CStage::Update();	// �X�e�[�W�I������
//
//	//if (m_pStartText->GetAnimFlg())	// �V�[���J�ڌ�Q�[�����J�n���邩����
//	//{
//	//	m_pStartText->Update();
//	//}
//	//else
//	//{
//	//	// �J�����X�V
//	//	m_pCamera->Update();
//
//	//	//�|�[�Y�X�V
//	//	if (m_pPause)	//�k���`�F�b�N
//	//	{
//	//		m_pPause->Update();	//�|�[�Y�X�V
//	//		if (m_pPause->IsPause())	//�|�[�Y��
//	//		{
//	//			return;	//�������f
//	//		}
//	//		m_bFinish = m_pPause->IsFin();	//�I������
//	//	}
//
//	//	// =============== �q�b�g�X�g�b�v���� ===================
//	//	if (!CHitStop::IsStop())	//�q�b�g�X�g�b�v���������Ȃ�
//	//	{
//	//		// �v���C���[�X�V
//	//		m_pPlayer->Update();	//���J�����X�V��
//
//	//		// �X���C���}�l�[�W���[�X�V
//	//		m_pSlimeMng->Update(m_pExplosionMng);
//	//	}
//
//	//	m_pFloor->Update();				// ���X�V
//	//	m_pExplosionMng->Update();		// �����}�l�[�W���[�X�V
//	//	m_pHealItemMng->Update();		// �񕜃A�C�e���X�V
//	//	m_pUIStageManager->Update();	// UI�}�l�[�W���[�X�V
//	//	Collision();					// �����蔻��X�V
//
//
//	//}
//}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
//!memo(����������ā[)�Fconst���ז��ɂȂ�����O���Ă�(.h�̕���)
//void CStage2::Draw()
//{
////	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
////	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
////	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
////
//	//���̕`��
//	m_pFloor->Draw();
//
//	// �X���C���}�l�[�W���[�`��
//	m_pSlimeMng->Draw();
//
//	// �v���C���[�`��
//	m_pPlayer->Draw();
//
//	LibEffekseer::Draw();
//
//	//�����}�l�[�W���[�`��
//	m_pExplosionMng->Draw();
//
//	//�񕜃A�C�e���`��
//	m_pHealItemMng->Draw();
//	
//	//UI�}�l�[�W���[�`��
//	m_pUIStageManager->Draw();
//
//	// �X�^�[�g���}�`��
//	if (m_pStartText->GetAnimFlg())
//	{
//		m_pStartText->Draw();
//	}
//
//	//�|�[�Y�`��
//	if (m_pPause)
//	{
//		m_pPause->Draw();
//	}
//}

/* ========================================
	���V�[���Q�b�^
	----------------------------------------
	���e�F�J�ڂ������V�[��������������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�J�ڐ�V�[���̎��
=========================================== */
CStage2::E_TYPE CStage2::GetNext() const
{
	// =============== �� ===================
	return CStage2::E_TYPE_RESULT;	//�J�ڐ�V�[���̎��
}

/* ========================================
	�f�[�^�L�^�֐�
	----------------------------------------
	���e�F���U���g�p�Ƀf�[�^�L�^
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStage2::RecordData()
{
//	// =============== �ޔ� =====================
//	m_Data.nTotalScore = m_pUIStageManager->GetTotalScore();				// �X�R�A�ޔ�
//
//	// =============== �f�[�^�o�^ =====================
//	if (m_Data.nHighScore[STAGE_NUM - 1] < m_Data.nTotalScore)	// �n�C�X�R�A���X�V���Ă��邩�H
//	{
//		m_Data.nHighScore[STAGE_NUM - 1] = m_Data.nTotalScore;	// �n�C�X�R�A�X�V
//	}
//	m_Data.nAliveTime = m_pUIStageManager->GetTimer()->GetErapsedTime();	// �o�ߎ��ԑޔ�
//	m_Data.nMaxCombo = m_pUIStageManager->GetCombo()->GetMaxCombo();		// �ő�R���{���ޔ�
//	m_Data.bClearFlg = m_pUIStageManager->GetStageFinish()->GetClearFlg();	// �Q�[���N���A������
//	if (m_pSlimeMng)	//�k���`�F�b�N
//	{
//		m_Data.nTotalKill = m_pSlimeMng->GetTotalKillCnt();					// ���������ޔ�
//		m_pSlimeMng->GetKillCntArray(m_Data.nKill);							// �X���C���ʓ������ޔ�
//
//	}
	m_Data.nStageNum = STAGE_NUM;	// �v���C�����X�e�[�W�ԍ�
}