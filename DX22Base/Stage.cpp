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
	�E2024/01/23 �e�֐��ďo takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Stage.h"			//���g�̃w�b�_
#include "HitStop.h"		//�q�b�g�X�g�b�v
#include "ControllMap.h"	//map����
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
	:m_pPause(nullptr)	//�|�[�Y���
	, m_pPlayer(nullptr)
	, m_pBox(nullptr)
	, m_pSlimeMng(nullptr)
	, m_pCollision(nullptr)
	, m_pExplosionMng(nullptr)
	, m_pTexture(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pHealItemMng(nullptr)
	,m_pFloor(nullptr)
{
	// =============== ���I�m�� =====================
	m_pCamera = new CCameraChase();						//�J����
	//================3dObject���I�m��================
	m_pPlayer = new CPlayer();							// �v���C���[����
	if (typeid(m_pCamera).hash_code() == typeid(CCameraChase).hash_code())
	{
		static_cast<CCameraChase*>(m_pCamera)->SetTarget(m_pPlayer->GetPosAddress());	//�J��������
	}
	m_pExplosionMng = new CExplosionManager();			// �����}�l�[�W���[����
	m_pSlimeMng = new CSlimeManager();			// �X���C���}�l�[�W���[����
	m_pSlimeMng->SetPlayer(m_pPlayer);
	m_pHealItemMng = new CHealItemManager();			// �񕜃A�C�e���}�l�[�W���[����
	//================System���I�m��================

	m_pCollision = new CCollision();					//�Փ˔���`�F�b�N����
	m_pStartText = new CStartText();
	m_pStartText->SetCamera(m_pCamera);
	//================�Z�b�g================
	// �J����
	m_pPlayer->SetCamera(m_pCamera);
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pHealItemMng->SetCamera(m_pCamera);
	m_pPause = new CPause(m_pCamera);
	//�X���C���}�l�[�W���[�@���@�X�R�A�}�l�[�W���[
	m_pSlimeMng->SetScoreOHMng(m_pScoreOHMng);
	//�����}�l�[�W���[�@���@�R���{
	m_pExplosionMng->SetCombo(m_pCombo);
	//�X���C���}�l�[�W���[�@���@�����}�l�[�W���[
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);
	// �X���C���}�l�[�W���[�@���@�񕜃A�C�e���}�l�[�W���\
	m_pSlimeMng->SetHealMng(m_pHealItemMng);
	//�����}�l�[�W���[�@���@�^�C�}�[
	m_pSlimeMng->SetTimer(m_pTimer);
	// �f�[�^�󂯌p��
	m_Data.Load();	//�t�@�C���ɏオ���Ă������ǂݍ���
	
	
	m_pTimer = new CTimer;
	m_pTimer->SetCamera(m_pCamera);
	m_pBossGauge = new CBossGauge();
	m_pBossGauge->SetCamera(m_pCamera);
	m_pBossGauge->SetTimer(m_pTimer);
	m_pBossGauge->SetSlimeManager(m_pSlimeMng);
	m_pHpMng = new CHP_UI();
	m_pHpMng->SetCamera(m_pCamera);
	m_pHpMng->SetPlayerHp(m_pPlayer->GetHpPtr());
	m_pTotalScore = new CTotalScore();
	m_pTotalScore->SetCamera(m_pCamera);
	m_pScoreOHMng = new CScoreOHManager();
	m_pScoreOHMng->SetCamera(m_pCamera);
	m_pStageFin = new CStageFinish();
	m_pStageFin->SetCamera(m_pCamera);
	m_pStageFin->SetTime(m_pTimer->GetTimePtr());
	m_pStageFin->SetPlHp(m_pPlayer->GetHpPtr());
	m_pBossArrow = new CBossArrow();
	m_pBossArrow->SetCamera(m_pCamera);
	m_pBossArrow->SetSlimeMng(m_pSlimeMng);
	m_pBossArrow->SetPlayer(m_pPlayer);
	m_pCombo = new CCombo();
	m_pCombo->SetCamera(m_pCamera);
	m_pCombo->SetTotalScore(m_pTotalScore);

	m_pTimer->TimeStart();

	// =============== �f�[�^�󂯌p�� =====================
	m_Data.Load();	//�t�@�C���ɏオ���Ă������ǂݍ���

	// =============== �f�[�^�󂯌p�� =====================
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		auto func = [](CSlimeManager* pSlimeMng) {pSlimeMng->Create(pSlimeMng->GetRandomLevel()); };	//�����_�������p�����_��
		func(static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME)));	//�X���C�������_������
	}	//�X���C���}�l�[�W���[�@���@�v���C���[

	Update();
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
	SAFE_DELETE(m_pPause);
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
	if (m_pStageFin)
	{
		if(m_pStageFin->GetGameEndFlg())
		{
			// =============== �t���O�Ǘ� =====================
			m_bFinish = true;	// �^�C�g���V�[���I���t���OON

			// =============== �I�� =====================
			return;	//�������f
		}
	}

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
			m_pPlayer->Update();	//�v���C���[�X�V

			// �X���C���}�l�[�W���[�X�V
			m_pSlimeMng->Update(m_pExplosionMng);
		}

		m_pFloor->Update();				// ���X�V
		m_pExplosionMng->Update();		// �����}�l�[�W���[�X�V
		m_pHealItemMng->Update();		// �񕜃A�C�e���X�V
		m_pTimer->Update();
		m_pStageFin->Update();
		m_pCombo->Update();
		m_pHpMng->Update();
		m_pBossGauge->Update();
		m_pScoreOHMng->Update();
		m_pBossArrow->Update();
		Collision();					// �����蔻��X�V
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
void CStage::Draw() const
{
//	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
//	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
//	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
//
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
	
	//UI�}�l�[�W���[�`��
	m_pTimer->Draw();
	m_pBossGauge->Draw();
	m_pHpMng->Draw();
	m_pTotalScore->Draw();
	m_pScoreOHMng->Draw();
	m_pStageFin->Draw();
	m_pBossArrow->Draw();
	m_pCombo->Draw();

	// �X�^�[�g���}�`��
	if (m_pStartText->GetAnimFlg())
	{
		m_pStartText->Draw();
	}

	//�|�[�Y�`��
	if (m_pPause)
	{
		m_pPause->Draw();
	}
}