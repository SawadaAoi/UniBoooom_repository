/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W1����
	---------------------------------------
	Stage1.cpp

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

	========================================== */

// =============== �C���N���[�h ===================
#include "Stage1.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//�q�b�g�X�g�b�v
#include "Fade.h"

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
{
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress(), CFloor::Stage1);	// ������
	//================�Z�b�g================
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
CStage1::~CStage1()
{
	SAFE_DELETE(m_pFloor);
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
	if (m_pStartText->GetAnimFlg())	// �V�[���J�ڌ�Q�[�����J�n���邩����
	{
		m_pStartText->Update();
	}
	else
	{
		// �J�����X�V
		m_pCamera->Update();

		//�|�[�Y�X�V
		if (m_pPause)	//�k���`�F�b�N
		{
			m_pPause->Update();	//�|�[�Y�X�V
			if (m_pPause->IsPause())	//�|�[�Y��
			{
				return;	//�������f
			}
			m_bFinish = m_pPause->IsFin();	//�I������
		}

		// =============== �q�b�g�X�g�b�v���� ===================
		if (!CHitStop::IsStop())	//�q�b�g�X�g�b�v���������Ȃ�
		{
			// �v���C���[�X�V
			m_pPlayer->Update();	//���J�����X�V��

			// �X���C���}�l�[�W���[�X�V
			m_pSlimeMng->Update(m_pExplosionMng);
		}

		m_pFloor->Update();				// ���X�V
		m_pExplosionMng->Update();		// �����}�l�[�W���[�X�V
		m_pHealItemMng->Update();		// �񕜃A�C�e���X�V
		m_pUIStageManager->Update();	// UI�}�l�[�W���[�X�V
		PlayerHealItemCollision();		// �񕜃A�C�e����锻��
		Collision();					// �����蔻��X�V

		
	}

#if SCENE_TRANSITION
	if (m_pUIStageManager->GetStageFinish()->GetDispFlg())
	{
		if (IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_A))
		{
			m_bFinish = true;	// �^�C�g���V�[���I���t���OON
		}
	}
#else
	if (m_pUIStageManager->GetStageFinish()->GetDeleteDispFlg())
	{
		// =============== �t���O�Ǘ� =====================
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON

		// =============== �ޔ� =====================
		m_Data.nTotalScore = m_pUIStageManager->GetTotalScore();			//�X�R�A�ޔ�
		m_Data.nAliveTime = m_pUIStageManager->GetTimer()->GetErapsedTime();	//�o�ߎ��ԑޔ�
		if (m_pSlimeMng)	//�k���`�F�b�N
		{
			m_Data.nKill = m_pSlimeMng->GetKillCnt();						//�������ޔ�
		}

		m_Data.nStageNum = 1;
	}
#endif
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
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

	//���̕`��
	m_pFloor->Draw();

	// �X���C���}�l�[�W���[�`��
	m_pSlimeMng->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw();

	LibEffekseer::Draw();

	//�����}�l�[�W���[�`��
	m_pExplosionMng->Draw();

	//�񕜃A�C�e���`��
	m_pHealItemMng->Draw();

	//2D�`��ϊ�
	SetRenderTargets(1, &pRTV, nullptr);

	//UI�}�l�[�W���[�`��
	m_pUIStageManager->Draw();

	// �X�^�[�g���}�`��
	if (m_pStartText->GetAnimFlg())
	{
		m_pStartText->Draw();
	}

	// �|�[�Y�`��
	if (m_pPause)
	{
		m_pPause->Draw();
	}
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g���X�e�[�W1�ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CStage1::E_TYPE CStage1::GetType() const
{
	// =============== �� ===================
	return CStage1::E_TYPE_STAGE1;	//���g�̎��
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