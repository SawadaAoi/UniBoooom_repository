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

========================================== */

// =============== �C���N���[�h ===================
#include "Stage1.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "Input.h"


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
	: m_nNum(0)
	, m_fSize(100.0f)
	, m_bStart(false)
{
	// ���_�V�F�[�_�̓Ǎ�
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// �e�N�X�`���Ǎ�
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/text_start.png")))
	{
		MessageBox(NULL, "Stage1 text_start.png", "Error", MB_OK);
	}

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

	// �����蔻�萶��
	m_pCollision = new CCOLLISION();

	// �v���C���[����
	m_pPlayer = new CPlayer();

	// �J��������
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());
	m_pPlayer->SetCamera(m_pCamera);

	// ������
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress());
	m_pFloor->SetCamera(m_pCamera);

	// �X���C���}�l�[�W���[����
	m_pSlimeMng = new CSlimeManager();
	m_pSlimeMng->SetCamera(m_pCamera);

	// �R���{���\������
	m_pCombo = new CCombo();

	// �����}�l�[�W���[����
	m_pExplosionMng = new CExplosionManager();
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pExplosionMng->SetCombo(m_pCombo);

	// �^�C�}�[����
	m_pTimer = new CTimer();
	m_pTimer->TimeStart();

	//�X�e�[�W�I����UI�\��
	m_pStageFin = new CStageFinish(m_pPlayer->GetHP(), m_pTimer->GetTimePtr());

	LoadSound();
	//BGM�̍Đ�
	m_pSpeaker = CSound::PlaySound(m_pBGM);		//BGM�̍Đ�
	m_pSpeaker->SetVolume(BGM_VOLUME);			//���ʂ̐ݒ�
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
	/*if (m_pSpeaker)
	{
		m_pSpeaker->Stop();
		m_pSpeaker->DestroyVoice();
	}*/
	SAFE_DELETE(m_pStageFin);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// �X���C���}�l�[�W���[�폜
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pVs);
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
	// �^�C�g������J�ڌシ���Q�[���J�n�ɂȂ�Ȃ��悤�ɂ��鏈��
	// ���܂�ɂ��K���ɍ�����̂Ŗ{�������ɂ����Ə����܂�
	if (!m_bStart)
	{
		m_nNum++;
		if (m_nNum > 10)
		{
			m_fSize += 10.0f;
		}

		if (m_nNum > 50)
		{
			m_bStart = true;
		}
	}
	else
	{
		// �J�����X�V
		m_pCamera->Update();

		// �v���C���[�X�V
		m_pPlayer->Update();

		// �X���C���}�l�[�W���[�X�V
		m_pSlimeMng->SetPlayerPos(m_pPlayer->GetPos());
		m_pSlimeMng->Update(m_pExplosionMng);

		// �����}�l�[�W���[�X�V
		m_pExplosionMng->Update();

		// �^�C�}�[�X�V
		m_pTimer->Update();

		// �X�e�[�W�I���X�V
		m_pStageFin->Update();

		// �R���{�X�V
		m_pCombo->Update();

		// �����蔻��X�V
		Collision();
	}

	if (m_pStageFin->GetDispFlg())
	{
		if (IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_A))
		{
			m_bFinish = true;	// �^�C�g���V�[���I���t���OON
		}
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
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

	// �X�^�[�g���}�`��
	if (!m_bStart)
	{
		// ���܂�ɂ��K���ɍ�����̂Ŏ�������Ȃ炿���Ə����܂�
		Draw2d(640.0f, 360.0f, m_fSize, m_fSize, m_pTexture);
	}

	//���̕`��
	m_pFloor->Draw();

	// �X���C���}�l�[�W���[�`��
	m_pSlimeMng->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw();

	//�����}�l�[�W���[�`��
	m_pExplosionMng->Draw();

	//�^�C�}�[�`��
	SetRenderTargets(1, &pRTV, nullptr);
	m_pStageFin->Draw();

	// �^�C�}�[�`��
	m_pTimer->Draw();

	// �R���{�`��
	m_pCombo->Draw();
	
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
