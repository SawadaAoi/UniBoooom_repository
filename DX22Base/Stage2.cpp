/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W2����
	---------------------------------------
	Stage2.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 Stage1�̓��e���R�s�[ yamashita
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2023/12/15 �Q�[���X�^�[�g�\���������ς� nieda

========================================== */

// =============== �C���N���[�h ===================
#include "Stage2.h"	//���g�̃w�b�_
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
CStage2::CStage2()
{
	m_pFloor->SetFloorModel(CFloor::StageKinds::Stage2);

	m_pUIStageManager->GetBossGauge()->AddBossGauge(BOSS_GAUGE_S2[0].BossNum, BOSS_GAUGE_S2[0].startTime, BOSS_GAUGE_S2[0].maxTime);
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
void CStage2::Update()
{
	if (m_pDrawStart->GetAnimFlg())	// �V�[���J�ڌ�Q�[�����J�n���邩����
	{
		m_pDrawStart->Update();
	}
	else
	{
		// �J�����X�V
		m_pCamera->Update();

		//�|�[�Y�X�V
#if USE_PAUSE
		if (m_pPause)	//�k���`�F�b�N
		{
			m_pPause->Update();	//�|�[�Y�X�V
			if (m_pPause->IsPause())	//�|�[�Y��
			{
				return;	//�������f
			}
			m_bFinish = m_pPause->IsFin();	//�I������
		}
#endif

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

#if USE_FADE_GAME
	m_pFade->Update();
#endif

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
//!memo(����������ā[)�Fconst���ז��ɂȂ�����O���Ă�(.h�̕���)
void CStage2::Draw()
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
	if (m_pDrawStart->GetAnimFlg())
	{
		m_pDrawStart->Draw();
	}

#if USE_FADE_GAME
	m_pFade->Draw();
#endif
#if USE_PAUSE
	if (m_pPause)
	{
		m_pPause->Draw();
	}
#endif
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g���X�e�[�W2�ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CStage2::E_TYPE CStage2::GetType() const
{
	// =============== �� ===================
	return CStage2::E_TYPE_STAGE2;	//���g�̎��
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
CStage2::E_TYPE CStage2::GetNext() const
{
	// =============== �� ===================
	return CStage2::E_TYPE_RESULT;	//�J�ڐ�V�[���̎��
}