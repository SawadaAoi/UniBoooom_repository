/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W1����
	---------------------------------------
	Stage1.cpp
	---------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/05 ���� takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 Prot.cpp��Stage1.cpp takagi
	�E2023/11/20 SceneGame����ڐA nieda
	�E2023/11/21 �Q�[���J�n���e�N�X�`���\�� nieda
	�E2023/11/22 �����悤����Ȃ��ϐ��Ȃǒǉ� nieda
	�E2023/11/27 �o�O�C�� takagi
	�E2023/11/29 �q�b�g�X�g�b�v�d�l�ύX�Ή� takagi
	�E2023/12/03 �J�����X�V�̋L�q���� takagi
	�E2023/12/05 �X�e�[�W�Ƀ|�[�Y���� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2023/12/07 �X�e�[�W�����U���g�J�ڕ��@�؂�ւ����� nieda
	�E2023/12/07 �r���[�s��擾�ɃJ�����g�p takagi
	�E2023/12/08 ���U���g�V�[���J�ڗp�ɏ����ǉ� takagi
	�E2023/12/12 �����o�ϐ���e�N���X�Ɉړ� yamashita
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2023/12/15 �Q�[���X�^�[�g�\���������ς� nieda
	�E2023/12/18 �f�o�b�O���[�h�폜���f takagi
	�E2024/01/01 �e�R���X�g���N�^�Ăяo�� takagi
	�E2024/01/15 GameFinish()�֐��C���ERecordData()�֐��ǉ� takagi
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi
	�E2024/01/23 �e�֐��ďo takagi

	========================================== */

// =============== �C���N���[�h ===================
#include "Stage1.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//�q�b�g�X�g�b�v
#include "Fade.h"
#include "ControllMap.h"	//�}�b�v����
#include <algorithm>

// =============== �萔�E�}�N����` ===================
const int STAGE_NUM = 1;	//�X�e�[�W�ԍ�

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CStage1::CStage1()
	:CStage()	//�e�֐��Ăяo��
{
	// =============== ���I�m�� =====================
	if (m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_pCamera).hash_code() == typeid(CCameraChase).hash_code() &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		m_p3dObject.emplace(E_3D_FLOOR, new CFloor(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER))->GetPosAddress(), CFloor::Stage1));	// ������
	}

	// =============== ������ =====================
	if (m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		m_p3dObject.at(E_3D_FLOOR)->SetCamera(m_pCamera);	//�J�����o�^
	}
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
CStage1::~CStage1()
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
void CStage1::Update()
{
	// =============== �X�V ===================
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_OPENING, typeid(CStartText).hash_code()) && 
		static_cast<CStartText*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_OPENING))->GetAnimFlg())	// �V�[���J�ڌ�Q�[�����J�n���邩����
	{
		m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_OPENING)->Update();	//�ꕔ�X�V
	}
	else
	{
		if (m_pPause)	//�k���`�F�b�N
		{
			m_pPause->Update();	//�|�[�Y�X�V
			if (m_pPause->IsPause())	//�|�[�Y��
			{
				return;	//�������f
			}
			m_bFinish = m_pPause->IsFin();	//�I������
		}

		// =============== �֐��ďo ===================
		CStage::Update();	//�e�֐��Ăяo��
	}
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStage1::Draw()
{
	// =============== �֐��ďo ===================
	CStage::Draw();	//�e�֐��Ăяo��

	// =============== �`�� ===================
	if (m_pPause)	//�k���`�F�b�N
	{
		m_pPause->Draw();	// �|�[�Y�`��
	}
}

/* ========================================
	���V�[���Q�b�^
	----------------------------------------
	���e�F�J�ڂ������V�[��������������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�J�ڐ�V�[���̎��
=========================================== */
CStage1::E_TYPE CStage1::GetNext() const
{
	// =============== �� ===================
	return CStage1::E_TYPE_RESULT;	//�J�ڐ�V�[���̎��
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
void CStage1::RecordData()
{
	// =============== �ޔ� =====================
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_FINISH, typeid(CTotalScore).hash_code()))	//�A�N�Z�X�E�k���E�^�`�F�b�N
	{
		m_Data.nTotalScore = static_cast<CTotalScore*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_FINISH))->GetTotalScore();	//�X�R�A�ޔ�
	}

	// =============== �f�[�^�o�^ =====================
	if (m_Data.nHighScore[STAGE_NUM - 1] < m_Data.nTotalScore)	// �n�C�X�R�A���X�V���Ă��邩�H
	{
		m_Data.nHighScore[STAGE_NUM - 1] = m_Data.nTotalScore;	// �n�C�X�R�A�X�V
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_TIMER, typeid(CTimer).hash_code()))	//�A�N�Z�X�E�k���E�^�`�F�b�N
	{
		m_Data.nTotalScore = static_cast<CTimer*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_TIMER))->GetErapsedTime();	// �o�ߎ��ԑޔ�
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_COMBO, typeid(CCombo).hash_code()))	//�A�N�Z�X�E�k���E�^�`�F�b�N
	{
		m_Data.nTotalScore = static_cast<CCombo*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO))->GetMaxCombo();		// �ő�R���{���ޔ�
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_COMBO, typeid(CStageFinish).hash_code()))	//�A�N�Z�X�E�k���E�^�`�F�b�N
	{
		m_Data.nTotalScore = static_cast<CStageFinish*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO))->GetClearFlg();	// �Q�[���N���A������
	}
	if (ACCESS_NULL_TYPE_CHECK(m_pObjectManager, E_MANAGER_SLIME, typeid(CSlimeManager).hash_code()))	//�A�N�Z�X�E�k���E�^�`�F�b�N
	{
		m_Data.nTotalKill = static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->GetTotalKillCnt();	// ���������ޔ�
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->GetKillCntArray(m_Data.nKill);			// �X���C���ʓ������ޔ�
	}
	m_Data.nStageNum = STAGE_NUM;	// �v���C�����X�e�[�W�ԍ�
}