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

========================================== */

// =============== �C���N���[�h ===================
#include "Stage.h"	//���g�̃w�b�_
#include "Line.h"

// =============== �f�o�b�O���[�h ===================
#define USE_CAMERA_VIBRATION (true)
#define MODE_COORD_AXIS (true)			//���W���f�����ǂ���
#define MODE_GROUND (false)				//���W���f�����ǂ���
#if _DEBUG
#define TRY_USE_HIT_STOP (true)
#endif
#define USE_FADE_GAME (true)	//�t�F�[�h����
#define USE_PAUSE (true)	//�|�[�Y����		�����݃|�[�Y������߂��Ă����i��p�ӂ��Ă��Ȃ����ߗv���ӁI
#define SCENE_TRANSITION(false)		// �V�[���J�ڂ��{�^����������������؂�ւ��itrue�͎���)

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


///* ========================================
//	�R���X�g���N�^
//	----------------------------------------
//	���e�F�������ɍs������
//	----------------------------------------
//	����1�F�Ȃ�
//	----------------------------------------
//	�ߒl�F�Ȃ�
//=========================================== */
CStage::CStage()
	:m_pVs(nullptr)
	, m_pPlayer(nullptr)
	, m_pBox(nullptr)
	, m_pSlimeMng(nullptr)
	, m_pCollision(nullptr)
	, m_pExplosionMng(nullptr)
	, m_pFloor(nullptr)
	, m_pFade(nullptr)
	, m_pTexture(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pHealItemMng(nullptr)
	, m_pUIStageManager(nullptr)
	, m_pPause(nullptr)	//�|�[�Y
	, m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	, m_nNum(0)
	, m_fSize(0.0f)
	, m_fResize(10.0f)
	, m_bStart(false), m_fUVPos(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntW(0)
	, m_nCntH(0)
	, m_bStartSign(false)
	, m_pSEHitHammer(nullptr)
	, m_pSEHitHammerSpeaker(nullptr)
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
	m_pPlayer = new CPlayer();							// �v���C���[����
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress());	// ������
	m_pExplosionMng = new CExplosionManager();			// �����}�l�[�W���[����
	m_pSlimeMng = new CSlimeManager(m_pPlayer);			// �X���C���}�l�[�W���[����
	m_pHealItemMng = new CHealItemManager();			// �񕜃A�C�e���}�l�[�W���[����

	//================System���I�m��================
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());	//�J��������
	m_pCollision = new CCOLLISION();							//�Փ˔���`�F�b�N����

	//================2dObject���I�m��================
	m_pUIStageManager = new CUIStageManager(m_pPlayer, m_pCamera, m_pSlimeMng);	// UI�}�l�[�W���[����


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
	// �J����
	m_pPlayer->SetCamera(m_pCamera);
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pFloor->SetCamera(m_pCamera);
	m_pHealItemMng->SetCamera(m_pCamera);

	//�X���C���}�l�[�W���[�@���@�X�R�A�}�l�[�W���[
	m_pSlimeMng->SetScoreOHMng(m_pUIStageManager->GetScoreMng());

	//�����}�l�[�W���[�@���@�R���{
	m_pExplosionMng->SetCombo(m_pUIStageManager->GetCombo());

	//�X���C���}�l�[�W���[�@���@�����}�l�[�W���[
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);

	// �X���C���}�l�[�W���[�@���@�񕜃A�C�e���}�l�[�W���\
	m_pSlimeMng->SetHealMng(m_pHealItemMng);

	//�����}�l�[�W���[�@���@�^�C�}�[
	m_pSlimeMng->SetTimer(m_pUIStageManager->GetTimer());

	//�X�e�[�W���ň���SE�̃��[�h
	LoadSE();
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
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pPause);
	SAFE_DELETE(m_pUIStageManager);
	SAFE_DELETE(m_pSEHitHammer);
	SAFE_DELETE(m_pSEHitHammerSpeaker);
}

///* ========================================
//	�X�V�֐�
//	----------------------------------------
//	���e�F�X�V����
//	----------------------------------------
//	����1�F�Ȃ�
//	----------------------------------------
//	�ߒl�F�Ȃ�
//=========================================== */
//void CStage::Update()
//{
//}
//
///* ========================================
//	�`��֐�
//	----------------------------------------
//	���e�F�`�揈��
//	----------------------------------------
//	����1�F�Ȃ�
//	----------------------------------------
//	�ߒl�F�Ȃ�
//	======================================== */
//	//!memo(����������ā[)�Fconst���ז��ɂȂ�����O���Ă�(.h�̕���)
//void CStage::Draw() const
//{
//}

/* ========================================
   SE�̃T�E���h�t�@�C���ǂݍ��݊֐�
   -------------------------------------
   ���e�FSE�̃T�E���h�t�@�C���̓ǂݍ���
   -------------------------------------
   ����1�F����
   -------------------------------------
   �ߒl�F����
=========================================== */
void CStage::LoadSE()
{
	m_pSEHitHammer = CSound::LoadSound("Assets/Sound/SE/Smash.mp3");		//SE�̓ǂݍ���
}
