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

========================================== */

// =============== �C���N���[�h ===================
#include "Stage.h"	//���g�̃w�b�_
#include "Line.h"
#include "Stage1.h"	//�X�e�[�W1
#include "Stage2.h"	//�X�e�[�W2
#include "Stage3.h"	//�X�e�[�W3

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
	:m_pVs(nullptr)
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

#if MODE_COORD_AXIS
	// �����̕\��
	CLine::Init();
#endif

	//================3dObject���I�m��================
	m_pPlayer = new CPlayer();							// �v���C���[����
	m_pExplosionMng = new CExplosionManager();			// �����}�l�[�W���[����
	m_pSlimeMng = new CSlimeManager(m_pPlayer);			// �X���C���}�l�[�W���[����
	m_pHealItemMng = new CHealItemManager();			// �񕜃A�C�e���}�l�[�W���[����

	//================System���I�m��================
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());	//�J��������
	m_pCollision = new CCOLLISION();							//�Փ˔���`�F�b�N����

	//================2dObject���I�m��================
	m_pUIStageManager = new CUIStageManager(m_pPlayer, m_pCamera, m_pSlimeMng, eStage);	// UI�}�l�[�W���[����
	m_pStartText = new CStartText(m_pCamera);

	//================�G�t�F�N�g���I�m��================
	m_pHitEffectMng = new CHitSlimeEffectManager();

	//================�Z�b�g================
	// �J����
	m_pHitEffectMng->SetCamera(m_pCamera);
	m_pPlayer->SetCamera(m_pCamera);
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pHealItemMng->SetCamera(m_pCamera);
	m_pPause = new CPause(m_pCamera);

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
	SAFE_DELETE(m_pFade);
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