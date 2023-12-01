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

========================================== */

// =============== �C���N���[�h ===================
#include "Stage1.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "Input.h"
#include "Line.h"
#include "HitStop.h"	//�q�b�g�X�g�b�v

// =============== �f�o�b�O���[�h ===================
#define USE_CAMERA_VIBRATION (true)
#define MODE_COORD_AXIS (true)			//���W���f�����ǂ���
#define MODE_GROUND (false)				//���W���f�����ǂ���
#if _DEBUG
#define TRY_USE_HIT_STOP (true)
#endif
#define USE_FADE_GAME (true)	//�t�F�[�h����

#if USE_FADE_GAME
#include "Fade.h"
#endif

#if USE_CAMERA_VIBRATION
#include "Input.h"
#endif

#if TRY_USE_HIT_STOP
#include "Input.h"
#endif

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

	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/start_sign.png")))
	{
		MessageBox(NULL, "�X�^�[�g�e�L�X�g�ǂݍ���", "Error", MB_OK);
	}

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

#if MODE_COORD_AXIS
	// �����̕\��
	CLine::Init();
#endif
	

	//================3dObject���I�m��================

	//�v���C���[����
	m_pPlayer = new CPlayer();

	//������
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress());

	// �����}�l�[�W���[����
	m_pExplosionMng = new CExplosionManager();

	// �X���C���}�l�[�W���[����
	m_pSlimeMng = new CSlimeManager(m_pPlayer);
	
	// �񕜃A�C�e���}�l�[�W���[����
	m_pHealItemMng = new CHealItemManager();

	//================System���I�m��================

	//�J��������
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());

	//�Փ˔���`�F�b�N����
	m_pCollision = new CCOLLISION();

	//================2dObject���I�m��================

	// UI�}�l�[�W���[����
	m_pUIStageManager = new CUIStageManager(m_pPlayer, m_pCamera, m_pSlimeMng);

	//�X�e�[�W�I����UI�\��
	m_pStageFin = new CStageFinish(m_pPlayer->GetHpPtr(), m_pTimer->GetTimePtr());
	
	
#if MODE_GROUND
	m_pBox = new CBox();
#endif
#if USE_FADE_GAME
	m_pFade = new CFade(m_pCamera);
#endif
	//================�Z�b�g================

	//�v���C���[�@���@�J����
	m_pPlayer->SetCamera(m_pCamera);

	//�����}�l�[�W���[�@���@�J����
	m_pExplosionMng->SetCamera(m_pCamera);

	//�X���C���}�l�[�W���[�@���@�J����
	m_pSlimeMng->SetCamera(m_pCamera);

	//���@���@�J����
	m_pFloor->SetCamera(m_pCamera);

	//�񕜃A�C�e���}�l�[�W���[�@���@�J����
	m_pHealItemMng->SetCamera(m_pCamera);

	//�X���C���}�l�[�W���[�@���@�X�R�A�}�l�[�W���[
	m_pSlimeMng->SetScoreOHMng(m_pUIStageManager->GetScoreMng());
	
	//�����}�l�[�W���[�@���@�R���{
	m_pExplosionMng->SetCombo(m_pUIStageManager->GetCombo());

	//�X���C���}�l�[�W���[�@���@�����}�l�[�W���[
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);

	// �X���C���}�l�[�W���[�@���@�񕜃A�C�e���}�l�[�W���\
	m_pSlimeMng->SetHealMng(m_pHealItemMng);

	//================�^�C�}�[�X�^�[�g================
	//m_pTimer->TimeStart();

	//================BGM�̐ݒ�================
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
	if (m_pSpeaker)
	{
		m_pSpeaker->Stop();
		m_pSpeaker->DestroyVoice();
	}
	SAFE_DELETE(m_pStageFin);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// �X���C���}�l�[�W���[�폜
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);

#if MODE_COORD_AXIS
	// �����̕\��
	CLine::Uninit();
#endif
	SAFE_DELETE(m_pVs);

	//SAFE_DELETE(m_pDirectWrite);

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
	if (!m_bStart)	// �V�[���J�ڌ�Q�[�����J�n���邩����
	{
		// �^�C�g������J�ڌシ���Q�[���J�n�ɂȂ�Ȃ��悤�ɂ��鏈��
		m_nNum++;
		
		if (m_nNum < 100)
		{
			m_fResize += 1.0f;
			m_fSize -= m_fResize;
		}
		else
		{
			m_bStart = true;
		}
	}
	else
	{
		// �J�����X�V
		m_pCamera->Update();

		// =============== �q�b�g�X�g�b�v���� ===================
		if (!CHitStop::IsStop())	//�q�b�g�X�g�b�v���������Ȃ�
		{
			// �v���C���[�X�V
			m_pPlayer->Update();

			// �X���C���}�l�[�W���[�X�V
			m_pSlimeMng->Update(m_pExplosionMng);
		}

		//���X�V
		m_pFloor->Update();

		// �����}�l�[�W���[�X�V
		m_pExplosionMng->Update();
		
		//�񕜃A�C�e���X�V
		m_pHealItemMng->Update();

		// UI�}�l�[�W���[�X�V
		m_pUIStageManager->Update();

		// �����蔻��X�V
		Collision();
		
	}

#if USE_FADE_GAME
	m_pFade->Update();
#endif

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

	//�񕜃A�C�e���`��
	m_pHealItemMng->Draw();

	//2D�`��ϊ�
	SetRenderTargets(1, &pRTV, nullptr);

	//UI�}�l�[�W���[�`��
	m_pUIStageManager->Draw();

#if USE_FADE_GAME
	m_pFade->Draw();
#endif
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
