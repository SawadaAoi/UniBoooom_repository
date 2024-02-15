/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�p���ۃN���X����
	!memo�F�����蔻��֘A�̏�����CollisionOfStage.cpp�ɋL��
	---------------------------------------
	Stage.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/01 �T�E���h�̓ǂݍ��� yamashita
	�E2023/12/04 �|�[�Y�N���X�ǉ��E�f�X�g���N�^���� takagi
	�E2023/12/05 �R�����g�C�� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2023/12/14 BGM�̊Ǘ���SceneManager�Ɉړ� yamashita
	�E2023/12/15 �Q�[���X�^�[�g�\�������ς��ɔ����K�v�Ȃ��Ȃ����ϐ��폜 nieda
	�E2023/12/15 �t�F�[�h�폜 takagi
	�E2023/12/18 �|�[�Y���I�m�� takagi
	�E2023/12/28 BattleData�i�[�������܂Ƃ߂��֐���ǉ�	Sawada
	�E2024/01/01 �X�e�[�W���� Takagi
	�E2024/01/25 �q�b�g�G�t�F�N�g�֌W�̏����ǉ� Tei
	�E2024/01/30 �v���C���[�ړ��G�t�F�N�g�֌W�̏����ǉ� Tei
	�E2024/02/02 ���G�t�F�N�g�����ǉ� Tei
	�E2024/02/09 UsingCamera�g�p takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Stage.h"	//���g�̃w�b�_
#include "Line.h"
#include "Stage1.h"	//�X�e�[�W1
#include "Stage2.h"	//�X�e�[�W2
#include "Stage3.h"	//�X�e�[�W3
#include "HitStop.h"	//�q�b�g�X�g�b�v
#include "Fade.h"
#include "UsingCamera.h"	//�J�����g�p


//* ========================================
//	�R���X�g���N�^
//	----------------------------------------
//	���e�F�������ɍs������
//	----------------------------------------
//	����1�FCUIStageManager::E_STAGE_NUM eStage�F�X�e�[�W�ԍ�
//	----------------------------------------
//	�ߒl�F�Ȃ�
//=========================================== */
CStage::CStage(CUIStageManager::E_STAGE_NUM eStage)
	: m_pVs(nullptr)
	, m_pPlayer(nullptr)
	, m_pBox(nullptr)
	, m_pSlimeMng(nullptr)
	, m_pCollision(nullptr)
	, m_pExplosionMng(nullptr)
	, m_pFloor(nullptr)
	, m_pTexture(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pHealItemMng(nullptr)
	, m_pUIStageManager(nullptr)
	, m_pPause(nullptr)	//�|�[�Y
	, m_pSEHitHammer(nullptr)
	, m_pSEHitHammerSpeaker(nullptr)
	, m_nStageNum(0)
{
	// ���_�V�F�[�_�̓Ǎ�
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
	
	//================3dObject���I�m��================
	m_pPlayer = new CPlayer();							// �v���C���[����
	m_pExplosionMng = new CExplosionManager();			// �����}�l�[�W���[����
	m_pSlimeMng = new CSlimeManager(m_pPlayer);			// �X���C���}�l�[�W���[����
	m_pHealItemMng = new CHealItemManager();			// �񕜃A�C�e���}�l�[�W���[����

	//================System���I�m��================
	m_pMainCamera = std::make_shared<CCameraChase>();												//�J��������
	std::static_pointer_cast<CCameraChase>(m_pMainCamera)->SetTarget(m_pPlayer->GetPosAddress());	//�����_�ݒ�
	CUsingCamera::GetThis().SetCamera(m_pMainCamera);												//�J�����o�^
	m_pCollision = new CCOLLISION();																//�Փ˔���`�F�b�N����

	//================2dObject���I�m��================
	m_pUIStageManager = new CUIStageManager(m_pPlayer, m_pSlimeMng, eStage);	// UI�}�l�[�W���[����
	m_pStartText = new CStartText();

	//================�G�t�F�N�g���I�m��================
	m_pHitEffectMng = new CHitSlimeEffectManager();

	m_pPause = new CPause();

	//�X���C���}�l�[�W���[�@���@�X�R�A�}�l�[�W���[
	m_pSlimeMng->SetScoreOHMng(m_pUIStageManager->GetScoreOHMngPtr());

	//�����}�l�[�W���[�@���@�R���{
	m_pExplosionMng->SetCombo(m_pUIStageManager->GetComboPtr());

	//�X���C���}�l�[�W���[�@���@�����}�l�[�W���[
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);

	// �X���C���}�l�[�W���[�@���@�񕜃A�C�e���}�l�[�W���\
	m_pSlimeMng->SetHealMng(m_pHealItemMng);

	//�����}�l�[�W���[�@���@�^�C�}�[
	m_pSlimeMng->SetTimer(m_pUIStageManager->GetTimerPtr());

	// �f�[�^�󂯌p��
	m_Data.Load();	//�t�@�C���ɏオ���Ă������ǂݍ���


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
void CStage::Update()
{
	if (m_pStartText->GetAnimFlg())	// �V�[���J�ڌ�Q�[�����J�n���邩����
	{
		m_pStartText->Update();
	}
	else
	{
		// �J�����X�V
		m_pCamera->Update();

		// �{�X�x���\�����͒�~
		if (m_pUIStageManager->GetShowWarningPtr()->GetDispFlg())
		{
			m_pUIStageManager->GetShowWarningPtr()->Update();	// �x���̂ݍX�V

			return;
		}

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
void CStage::Draw()
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

	// �G�t�F�N�g�`��
	m_pHitEffectMng->Draw();

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
CStage::~CStage()
{
	// =============== �Z�[�u =====================
	m_Data.Save();	//�X�e�[�W�̃f�[�^�Z�[�u

#if MODE_COORD_AXIS
// �����̕\��
	CLine::Uninit();
#endif

	// =============== �I�� ===================
	SAFE_DELETE(m_pVs);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pBox);
	SAFE_DELETE(m_pSlimeMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pHitEffectMng);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pPause);
	SAFE_DELETE(m_pUIStageManager);
	SAFE_DELETE(m_pStartText);
}



/* ========================================
	�Q�[���I������
	----------------------------------------
	���e�F�Q�[���I�����̏���
	----------------------------------------
	����1�F�X�e�[�W�ԍ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStage::GameFinish()
{
	// �Q�[�����I���������H
	if (m_pUIStageManager->GetStageFinishPtr()->GetGameEndFlg())
	{
		// =============== �t���O�Ǘ� =====================
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON
	}
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
void CStage::RecordData()
{
	m_pUIStageManager->GetTotalScorePtr()->GameEndAddTotal();	// �g�[�^���X�R�A�R���{�r�����Z����

	// =============== �ޔ� =====================
	m_Data.nTotalScore = m_pUIStageManager->GetTotalScore();				// �X�R�A�ޔ�

	// =============== �f�[�^�o�^ =====================
	if (m_Data.nHighScore[m_nStageNum - 1] < m_Data.nTotalScore)	// �n�C�X�R�A���X�V���Ă��邩�H
	{
		m_Data.nHighScore[m_nStageNum - 1] = m_Data.nTotalScore;	// �n�C�X�R�A�X�V
	}
	m_Data.nAliveTime = m_pUIStageManager->GetTimerPtr()->GetErapsedTime();	// �o�ߎ��ԑޔ�
	m_Data.nMaxCombo = m_pUIStageManager->GetComboPtr()->GetMaxCombo();		// �ő�R���{���ޔ�
	m_Data.bClearFlg = m_pUIStageManager->GetStageFinishPtr()->GetClearFlg();	// �Q�[���N���A������
	if (m_pSlimeMng)	//�k���`�F�b�N
	{
		m_Data.nTotalKill = m_pSlimeMng->GetTotalKillCnt();					// ���������ޔ�
		m_pSlimeMng->GetKillCntArray(m_Data.nKill);							// �X���C���ʓ������ޔ�

	}
	m_Data.nStageNum = m_nStageNum;	// �v���C�����X�e�[�W�ԍ�
}