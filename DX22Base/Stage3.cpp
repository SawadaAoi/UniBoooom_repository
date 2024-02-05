/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W3����
	---------------------------------------
	Stage3.cpp

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
	�E2024/01/25 �q�b�g�G�t�F�N�g�֌W�̏����ǉ� Tei
	�E2024/02/05 �Q�[���I���ԍۂ̉��Z�X�R�A���g�[�^���X�R�A�ɔ��f�����悤��(��) sawada

========================================== */

// =============== �C���N���[�h ===================
#include "Stage3.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "HitStop.h"	//�q�b�g�X�g�b�v

// =============== �萔�E�}�N����` ===================
const int STAGE_NUM = 3;	//�X�e�[�W�ԍ�

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CStage3::CStage3()
	:CStage(CUIStageManager::E_STAGE_3)	//�e�֐��Ăяo��
{
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress(), CFloor::Stage3);	// ������
	m_pUIStageManager->GetBossGauge()->AddBossGauge(BOSS_GAUGE_S3[0].BossNum, BOSS_GAUGE_S3[0].startTime, BOSS_GAUGE_S3[0].maxTime);
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
CStage3::~CStage3()
{
	// =============== �L�^ =====================
	RecordData();	//�f�[�^�L�^

	// =============== �I�� =====================
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
void CStage3::Update()
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
		m_pHitEffectMng->Update();		// �q�b�g�G�t�F�N�g�}�l�[�W���[�X�V


	}

#if SCENE_TRANSITION
	if (m_pUIStageManager->GetStageFinishPtr()->GetDispFlg())
	{
		if (IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_A))
		{
			m_bFinish = true;	// �^�C�g���V�[���I���t���OON
		}
	}
#else
	CStage::GameFinish();	// �X�e�[�W�I������
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
void CStage3::Draw()
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

	// �q�b�g�G�t�F�N�g�`��
	m_pHitEffectMng->Draw();
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g���X�e�[�W3�ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CStage3::E_TYPE CStage3::GetType() const
{
	// =============== �� ===================
	return CStage3::E_TYPE_STAGE3;	//���g�̎��
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
CStage3::E_TYPE CStage3::GetNext() const
{
	// =============== �� ===================
	return CStage3::E_TYPE_RESULT;	//�J�ڐ�V�[���̎��
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
void CStage3::RecordData()
{
	m_pUIStageManager->GetTotalScorePtr()->GameEndAddTotal();	// �g�[�^���X�R�A�R���{�r�����Z����

	// =============== �ޔ� =====================
	m_Data.nTotalScore = m_pUIStageManager->GetTotalScore();				// �X�R�A�ޔ�

	// =============== �f�[�^�o�^ =====================
	if (m_Data.nHighScore[STAGE_NUM - 1] < m_Data.nTotalScore)	// �n�C�X�R�A���X�V���Ă��邩�H
	{
		m_Data.nHighScore[STAGE_NUM - 1] = m_Data.nTotalScore;	// �n�C�X�R�A�X�V
	}
	m_Data.nAliveTime = m_pUIStageManager->GetTimerPtr()->GetErapsedTime();	// �o�ߎ��ԑޔ�
	m_Data.nMaxCombo = m_pUIStageManager->GetComboPtr()->GetMaxCombo();		// �ő�R���{���ޔ�
	m_Data.bClearFlg = m_pUIStageManager->GetStageFinishPtr()->GetClearFlg();	// �Q�[���N���A������
	if (m_pSlimeMng)	//�k���`�F�b�N
	{
		m_Data.nTotalKill = m_pSlimeMng->GetTotalKillCnt();					// ���������ޔ�
		m_pSlimeMng->GetKillCntArray(m_Data.nKill);							// �X���C���ʓ������ޔ�

	}
	m_Data.nStageNum = STAGE_NUM;	// �v���C�����X�e�[�W�ԍ�
}