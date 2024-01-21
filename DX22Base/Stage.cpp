/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�p���ۃN���X����
	!memo�F�����蔻��֘A�̏�����CollisionOfStage.cpp�ɋL��
	---------------------------------------
	Stage.cpp
	---------------------------------------
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
	�E2024/01/19 GetType()�֐��폜�E���̑����t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Stage.h"	//���g�̃w�b�_
#if _DEBUG
#include <Windows.h>		//���b�Z�[�W�{�b�N�X�p
#endif

//* ========================================
//	�R���X�g���N�^
//	----------------------------------------
//	���e�F�������ɍs������
//	----------------------------------------
//	����1�F�Ȃ�
//	----------------------------------------
//	�ߒl�F�Ȃ�
//=========================================== */
CStage::CStage()
	:m_pPlayer(nullptr)
	,m_pSlimeMng(nullptr)
	,m_pExplosionMng(nullptr)
	,m_pFloor(nullptr)
	,m_pScoreOHMng(nullptr)
	,m_pHealItemMng(nullptr)
	,m_pUIStageManager(nullptr)
	,m_pPause(nullptr)				//�|�[�Y���
	,m_pSEHitHammer(nullptr)
	,m_pSEHitHammerSpeaker(nullptr)
{
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
	m_pCamera = new CCameraChase();													//�J��������
	static_cast<CCameraChase*>(m_pCamera)->SetTarget(m_pPlayer->GetPosAddress());	//�����_�o�^

	//================2dObject���I�m��================
	m_pUIStageManager = new CUIStageManager(m_pPlayer, m_pCamera, m_pSlimeMng, CUIStageManager::E_STAGE_1);	// UI�}�l�[�W���[����
	m_pStartText = new CStartText(m_pCamera);

	//================�Z�b�g================
	// �J����
	m_pPlayer->SetCamera(m_pCamera);
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pHealItemMng->SetCamera(m_pCamera);
	m_pPause = new CPause(m_pCamera);

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

	// =============== �I�� ===================
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pSlimeMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pPause);
	SAFE_DELETE(m_pUIStageManager);
	SAFE_DELETE(m_pStartText);
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
	// =============== ���� =====================
	if (m_pUIStageManager->GetStageFinish()->GetGameEndFlg())	//�Q�[�����I��������
	{
		// =============== �t���O�Ǘ� =====================
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON

		// =============== �I�� =====================
		return;	//�������f
	}

	// =============== �X�V =====================
	CScene::Update();	//�e�֐��Ăяo��
}