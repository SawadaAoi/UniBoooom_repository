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
#include "BossArrow.h"

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
{

	// =============== ���I�m�� =====================
	m_pCamera = new CCameraChase();											//�J����
	m_p3dObject.emplace(E_3D_PLAYER, new CPlayer());						//�v���C���[
	m_p2dObjectOnWorld.emplace(E_2D_ON_WORLD_BOSS_ARROW, new CBossArrow());	//�{�X�����w�j
	m_p2dObjectOnWorld.emplace(E_2D_ON_WORLD_BOSS_GAUGE, new CBossGauge());	//�{�X�Q�[�W
	m_pObjectManager.emplace(E_MANAGER_SLIME, new CSlimeManager());			//�X���C���Ǘ�
	m_pObjectManager.emplace(E_MANAGER_EXPLOSION, new CExplosionManager());	//�����Ǘ�
	m_pObjectManager.emplace(E_MANAGER_SCORE_OH, new CScoreOHManager());	//ScoreOH�Ǘ�	//TODO:�C��
	m_pObjectManager.emplace(E_MANAGER_HEAL_ITEM, new CHealItemManager());	//�񕜃A�C�e���Ǘ�
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_OPENING, new CStartText());		//�J�n�\��
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_FINISH, new CStageFinish());		//�I���\��
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_TOTAL_SCORE, new CTotalScore());	//���X�R�A
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_COMBO, new CCombo());		//�R���{��
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_HP, new CHP_UI());			//HP
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_TIMER, new CTimer());		//����

	// =============== ������ =====================
	if (m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_pCamera).hash_code() == typeid(CCameraChase).hash_code() &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CCameraChase*>(m_pCamera)->SetTarget(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER))->GetPosAddress());	//�����_�o�^
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_HP, typeid(CHP_UI).hash_code())
		&& ACCESS_NULL_TYPE_CHECK(m_p3dObject, E_3D_PLAYER, typeid(CPlayer).hash_code()))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CHP_UI*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_HP))->SetPlayerHp(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER))->GetHpPtr());	//HP�A�h���X�o�^
	}
	for (auto Iterator = m_p3dObject.begin(); Iterator != m_p3dObject.end(); Iterator++)
	{
		if (Iterator->second)	//�k���`�F�b�N
		{
			(Iterator->second)->SetCamera(m_pCamera);	//�J�����Z�b�g
		}
	};	//3D�I�u�W�F�N�g�J�����o�^
	for (auto Iterator = m_p2dObjectOnWorld.begin(); Iterator != m_p2dObjectOnWorld.end(); Iterator++)
	{
		if (Iterator->second)	//�k���`�F�b�N
		{
			(Iterator->second)->SetCamera(m_pCamera);	//�J�����Z�b�g
		}
	};	//3D�\��2D�I�u�W�F�N�g�J�����o�^
	for (auto Iterator = m_pObjectManager.begin(); Iterator != m_pObjectManager.end(); Iterator++)
	{
		if (Iterator->second)	//�k���`�F�b�N
		{
			(Iterator->second)->SetCamera(m_pCamera);	//�J�����Z�b�g
		}
	};	//�}�l�[�W���J�����o�^
	for (auto Iterator = m_p2dObjectOnScreen.begin(); Iterator != m_p2dObjectOnScreen.end(); Iterator++)
	{
		if (Iterator->second)	//�k���`�F�b�N
		{
			(Iterator->second)->SetCamera(m_pCamera);	//�J�����Z�b�g
		}
	};	//2D�\��2D�I�u�W�F�N�g�J�����o�^
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetPlayer(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER)));	//�v���C���[�o�^
	}	//�X���C���}�l�[�W���[�@���@�v���C���[
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_pObjectManager.find(E_MANAGER_SCORE_OH) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SCORE_OH) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SCORE_OH)).hash_code() == typeid(CScoreOHManager).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetScoreOHMng(static_cast<CScoreOHManager*>(m_pObjectManager.at(E_MANAGER_SCORE_OH)));	//�v���C���[�o�^
	}	//�X���C���}�l�[�W���[�@���@�X�R�A�}�l�[�W���[
	if (m_pObjectManager.find(E_MANAGER_EXPLOSION) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_EXPLOSION) &&
		typeid(*m_pObjectManager.at(E_MANAGER_EXPLOSION)).hash_code() == typeid(CExplosionManager).hash_code() &&
		m_p2dObjectOnScreen.find(E_2D_ON_SCREEN_COMBO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO) &&
		typeid(*m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO)).hash_code() == typeid(CCombo).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CExplosionManager*>(m_pObjectManager.at(E_MANAGER_EXPLOSION))->SetCombo(static_cast<CCombo*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO)));	//�v���C���[�o�^
	}	//�����}�l�[�W���[�@���@�R���{
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_pObjectManager.find(E_MANAGER_EXPLOSION) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_EXPLOSION) &&
		typeid(*m_pObjectManager.at(E_MANAGER_EXPLOSION)).hash_code() == typeid(CExplosionManager).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetExplosionMng(static_cast<CExplosionManager*>(m_pObjectManager.at(E_MANAGER_EXPLOSION)));	//�v���C���[�o�^
	}	//�X���C���}�l�[�W���[�@���@�����}�l�[�W���[
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_pObjectManager.find(E_MANAGER_HEAL_ITEM) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_HEAL_ITEM) &&
		typeid(*m_pObjectManager.at(E_MANAGER_HEAL_ITEM)).hash_code() == typeid(CHealItemManager).hash_code())	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetHealMng(static_cast<CHealItemManager*>(m_pObjectManager.at(E_MANAGER_HEAL_ITEM)));	//�v���C���[�o�^
	}	//�X���C���}�l�[�W���[�@���@�񕜃A�C�e���}�l�[�W���\
	if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_SLIME) &&
		//m_p2dObjectOnScreen.find(E_2D_ON_SCREEN_COMBO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO) &&
		typeid(*m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_TIMER)).hash_code() == typeid(CCombo).hash_code())
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetHealMng(static_cast<CHealItemManager*>(m_pObjectManager.at(E_2D_ON_SCREEN_TIMER)));	//�v���C���[�o�^
	}	//�X���C���}�l�[�W���[�@���@�^�C�}�[

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
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_FINISH, typeid(CStageFinish).hash_code()))	//�A�N�Z�X�E�k���E�^�`�F�b�N
	{
		if (static_cast<CStageFinish*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_FINISH))->GetGameEndFlg())	//�Q�[�����I��������
		{
			// =============== �t���O�Ǘ� =====================
			m_bFinish = true;	// �^�C�g���V�[���I���t���OON

			// =============== �I�� =====================
			return;	//�������f
		}
	}

	// =============== �q�b�g�X�g�b�v���� ===================
	if (!CHitStop::IsStop())	//�q�b�g�X�g�b�v���������Ȃ�
	{
		// =============== ���� =====================
		if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_EXPLOSION))	//�A�N�Z�X�E�k���`�F�b�N
		{
			(m_pObjectManager.at(E_MANAGER_EXPLOSION))->Update();	//�Q�[�����I��������
		}
		if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_HEAL_ITEM))	//�A�N�Z�X�E�k���`�F�b�N
		{
			(m_pObjectManager.at(E_MANAGER_HEAL_ITEM))->Update();	//�Q�[�����I��������
		}
		if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_HEAL_ITEM))	//�A�N�Z�X�E�k���`�F�b�N
		{
			(m_pObjectManager.at(E_MANAGER_HEAL_ITEM))->Update();	//�Q�[�����I��������
		}
	}

	// =============== �X�V =====================
	CScene::Update();	//�e�֐��Ăяo��
	Collision();		// �����蔻��X�V
}