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

========================================== */

// =============== �C���N���[�h ===================
#include "Stage1.h"	//���g�̃w�b�_
#include "CameraChase.h"
#include "Input.h"
#include "Line.h"
#include "HitStop.h"	//�q�b�g�X�g�b�v
#include "Fade.h"

// =============== �萔��` =======================
const int STARTSIGN_UV_NUM_X = 6;	// �e�N�X�`���̉��̕�����
const int STARTSIGN_UV_NUM_Y = 9;	// �e�N�X�`���̏c�̕�����

const float STARTSIGN_UV_POS_X = 1.0f / STARTSIGN_UV_NUM_X;		// ����UV���W�v�Z�p
const float STARTSIGN_UV_POS_Y = 1.0f / STARTSIGN_UV_NUM_Y;		// �c��UV���W�v�Z�p

// =============== �f�o�b�O���[�h ===================
#define USE_CAMERA_VIBRATION (true)
#define MODE_COORD_AXIS (true)			//���W���f�����ǂ���
#define MODE_GROUND (false)				//���W���f�����ǂ���
#if _DEBUG
#define TRY_USE_HIT_STOP (true)
#endif
#define USE_FADE_GAME (true)	//�t�F�[�h����
#define USE_PAUSE (false)	//�|�[�Y����		�����݃|�[�Y������߂��Ă����i��p�ӂ��Ă��Ȃ����ߗv���ӁI

#if USE_FADE_GAME
#include "Fade.h"
#endif

#if USE_CAMERA_VIBRATION
#include "Input.h"
#endif

#if TRY_USE_HIT_STOP
#include "Input.h"
#endif

#if USE_PAUSE	//�|�[�Y�Վ��Ăяo��
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
	, m_fSize(0.0f)
	, m_fResize(10.0f)
	, m_bStart(false), m_fUVPos(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntW(0)
	, m_nCntH(0)
	, m_bStartSign(false)
{
	// ���_�V�F�[�_�̓Ǎ�
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/start_sprite.png")))
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
	
	m_pHealItemMng = new CHealItemManager();

	//================2dObject���I�m��================

	// �R���{���\������
	m_pCombo = new CCombo();

	//����X�R�A�}�l�[�W���[����
	m_pScoreOHMng = new CScoreOHManager();

	//�g�[�^���X�R�A����
	m_pTotalScore = new CTotalScore();

	// �^�C�}�[����
	m_pTimer = new CTimer();

	//�{�X�Q�[�W����
	m_pBossgauge = new CBossgauge(m_pTimer->GetNowTime());

	//�X�e�[�W�I����UI�\��
	m_pStageFin = new CStageFinish(m_pPlayer->GetHpPtr(), m_pTimer->GetTimePtr());

	//�v���C���[HP��UI����
	m_pHpMng = new CHP_UI(m_pPlayer->GetHpPtr());
	
	//================System���I�m��================

	//�J��������
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());

	//�Փ˔���`�F�b�N����
	m_pCollision = new CCOLLISION();
	
#if MODE_GROUND
	m_pBox = new CBox();
#endif
#if USE_FADE_GAME
	m_pFade = new CFade(m_pCamera);
#endif

#if USE_PAUSE
	m_pPause = new CPause(m_pCamera);
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

	//����X�R�A�}�l�[�W���[�@���@�J����
	m_pScoreOHMng->SetCamera(m_pCamera);

	m_pHealItemMng->SetCamera(m_pCamera);

	//�X���C���}�l�[�W���[�@���@�X�R�A�}�l�[�W���[
	m_pSlimeMng->SetScoreOHMng(m_pScoreOHMng);
	
	//�����}�l�[�W���[�@���@�R���{
	m_pExplosionMng->SetCombo(m_pCombo);

	//�X���C���}�l�[�W���[�@���@�����}�l�[�W���[
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);

	//�R���{�@���@�g�[�^���X�R�A
	m_pCombo->SetTotalScore(m_pTotalScore);

	//�{�X�Q�[�W�@���@�X���C���}�l�[�W���[
	m_pBossgauge->SetSlimeManager(m_pSlimeMng);

	//�����}�l�[�W���[�@���@�^�C�}�[
	m_pSlimeMng->SetTimer(m_pTimer);

	m_pSlimeMng->SetHealMng(m_pHealItemMng);

	//================�^�C�}�[�X�^�[�g================
	m_pTimer->TimeStart();

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
	SAFE_DELETE(m_pPause);
	if (m_pSpeaker)
	{
		m_pSpeaker->Stop();
		m_pSpeaker->DestroyVoice();
	}
	SAFE_DELETE(m_pStageFin);
	SAFE_DELETE(m_pHpMng);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pBossgauge);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pSlimeMng);	// �X���C���}�l�[�W���[�폜
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pTotalScore);

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
		
		if (m_nNum > TIME_WAIT_START)	// �t�F�[�h�I���܂ő҂��č��}�Đ�
		{
			m_bStartSign = true;
		}

		if (m_bStartSign)	// �t�F�[�h���I��������A�j���[�V�����Đ��J�n
		{
			m_nCntSwitch++;
		}

		if (m_nCntSwitch > 1)	// ���̊Ԋu�Ő؂�ւ���
		{
			m_nCntSwitch = 0;		// �J�E���g��������

			m_fUVPos.x = (STARTSIGN_UV_POS_X)* m_nCntW;		// ��������UV���W�v�Z
			m_fUVPos.y = (STARTSIGN_UV_POS_Y)* m_nCntH;		// �c������UV���W�v�Z

			++m_nCntW;		// �������ɍ��W��1�i�߂�
			if (m_nCntW == STARTSIGN_UV_NUM_X)	// �e�N�X�`���̉E�[�܂ōs������ 
			{
				m_nCntW = 0;	// �J�E���g��������
				++m_nCntH;		// �c��1�i�߂�
			}

			if (m_nCntH == STARTSIGN_UV_NUM_Y)		// �e�N�X�`���̉��[�܂ōs������
			{
				m_nCntH = 0;	// �J�E���g��������
				m_nCntW = 0;
				m_bStart = true;	// �A�j���[�V�����Đ���OFF
			}
		}
	}
	else
	{
		// �J�����X�V
		m_pCamera->Update();

		//�|�[�Y�X�V
#if USE_PAUSE
		if (m_pPause)	//�k���`�F�b�N
		{
			if (IsKeyPress('P'))
			{
				m_pPause->Boot();
			}
			if (m_pPause->IsPause())	//�|�[�Y��
			{
				m_pPause->Update();

				return;	//�������f
			}
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

		//���X�V
		m_pFloor->Update();

		// �����}�l�[�W���[�X�V
		m_pExplosionMng->Update();

		m_pHealItemMng->Update();

		// �^�C�}�[�X�V
		m_pTimer->Update();

		// �X�e�[�W�I���X�V
		m_pStageFin->Update();

		// �R���{�X�V
		m_pCombo->Update();

		//����X�R�A�X�V
		m_pScoreOHMng->Update();

		// HP�}�l�[�W���[�X�V
		m_pHpMng->Update();

		//�{�X�̏o���Q�[�W�X�V
		m_pBossgauge->Update();

		// �����蔻��X�V
		Collision();
		
		// �񕜃A�C�e����锻��
		PlayerHealItemCollision();
		
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
		DirectX::XMFLOAT4X4 mat[3];

		// ���[���h�s���X��Y�݂̂��l�����č쐬
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(START_POS_X, START_POS_Y, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

		// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
		// ���̍s���2D�̃X�N���[���̑傫�������܂�
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// ���t���e�s���ݒ�
		DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


		// �X�v���C�g�̐ݒ�
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(START_SCALE_X, -START_SCALE_Y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVPos.x, m_fUVPos.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(STARTSIGN_UV_POS_X, STARTSIGN_UV_POS_Y));
		Sprite::SetTexture(m_pTexture);
		Sprite::Draw();
	}

	//���̕`��
	m_pFloor->Draw();

	// �X���C���}�l�[�W���[�`��
	m_pSlimeMng->Draw();

	// �v���C���[�`��
	m_pPlayer->Draw();

	LibEffekseer::Draw();

	//�����}�l�[�W���[�`��
	m_pExplosionMng->Draw();

	m_pHealItemMng->Draw();



	//�^�C�}�[�`��
	SetRenderTargets(1, &pRTV, nullptr);

	//�X�e�[�W�I�����̌��ʂ�`��
	m_pStageFin->Draw();

	// �^�C�}�[�`��
	m_pTimer->Draw();

	// HP�}�l�[�W���[�`��
	m_pHpMng->Draw();

	// �R���{�`��
	m_pCombo->Draw();
	
	//�g�[�^���X�R�A�`��
	m_pTotalScore->Draw();

	//�{�X�Q�[�W�`��
	m_pBossgauge->Draw();

	//����X�R�A�}�l�[�W���[�`��
	m_pScoreOHMng->Draw();
//
//#if USE_FADE_GAME
//	m_pFade->Draw();
//#endif
//
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
