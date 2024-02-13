/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���f���Ǘ��N���X
	---------------------------------------
	ModelManager.h

	�쐬��
			yamashita
	�ύX����
	�E2024/02/08 �V�K�쐬

========================================== */

#include "ModelManager.h"
#include "ShaderList.h"

/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�j�����ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CModelManager::CModelManager()
{
	m_fModelSize[MODEL_PLAYER] = 1.0f;			// �v���C���[�̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_BLUE] = 0.15f;		// �X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_GREEN] = 0.15f;	// �΃X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_YELLOW] = 0.21f;	// ���F�X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_RED] = 0.18f;		// �ԃX���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_FLAME] = 0.3f;		// ���X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_HEAL] = 0.45f;		// �񕜃X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_ROCK] = 0.5f;		// ��X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_DEVIL] = 0.23f;	// �f�r���X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_ITEM_HEART] = 1.0f;		// �񕜃A�C�e���̃n�[�g�̃��f���T�C�Y�̔{��

	m_sFileName[MODEL_PLAYER]		 = "Assets/Model/player/pow.FBX";						// �v���C���[�̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_BLUE]	= "Assets/Model/slime/Blue/slime_blue_walk_1.0.fbx";	// �X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_GREEN]	= "Assets/Model/slime/Green/slime_green_walk_1.0.fbx";	// �΃X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_YELLOW] = "Assets/Model/slime/Yellow/slime_yellow_walk_1.0.fbx";// ���F�X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_RED]	= "Assets/Model/slime/Red/slime_red_walk_1.0.fbx";		// �ԃX���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_FLAME]	= "Assets/Model/flameSlime/fire_walk.fbx";				// ���X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_HEAL]	= "Assets/Model/healSlime/heal_walk.fbx";				// �񕜃X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_ROCK]	= "Assets/Model/boss_slime_rock/rock_walk_2.0.fbx";		// ��X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_DEVIL]	= "Assets/Model/boss_slime_devil/devil_walk.fbx";		// �f�r���X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_ITEM_HEART]	= "Assets/Model/heart/heart_1.FBX";						// �񕜃A�C�e���̃n�[�g�̃��f���̃t�@�C����
	
	// �e���f���̓ǂݍ���
	for (int i = 0; i < (int)MODEL_MAX; i++)
	{
		// ���f���̓��I�m��
		m_ModelList.emplace(MODEL_KIND(i), new AnimeModel());
		// ���f���̓ǂݍ���
		if (!m_ModelList.at(MODEL_KIND(i))->Load(m_sFileName[MODEL_KIND(i)].c_str(), m_fModelSize[MODEL_KIND(i)], AnimeModel::XFlip)) {		//�{���Ɣ��]�͏ȗ���
			MessageBox(NULL, m_sFileName[MODEL_KIND(i)].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
		// ���_�V�F�[�_�[���Z�b�g
		m_ModelList.at((MODEL_KIND)i)->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));	
	}

	// �A�j���[�V�����ǂݍ���
	LoadAnime();
}

/* ========================================
   �֐��F�f�X�g���N�^
   ----------------------------------------
   ���e�F�j�����ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CModelManager::~CModelManager()
{
	// ���I�m�ۂ������m���폜
	for (int i = 0; i, MODEL_KIND(i); i++)
	{
		SAFE_DELETE(m_ModelList.at(MODEL_KIND(i)));
	}
}


/* ========================================
   �֐��F�N���X�̍쐬����ю擾�֐�
   ----------------------------------------
   ���e�F�N���X���C���X�^���X���Ď擾����(���ɍ쐬����Ă���ꍇ�͍쐬���Ȃ�)
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F���̃N���X
======================================== */
CModelManager & CModelManager::GetInstance()
{
	static CModelManager modelManager; return modelManager;
}

/* ========================================
   �֐��F�A�j���[�V�����ǂݍ��݊֐�
   ----------------------------------------
   ���e�F���ꂼ��̃A�j���[�V������ǂݍ��ފ֐�
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CModelManager::LoadAnime()
{

	for (int i = 0; i < CPlayer::MOTION_PLAYER_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_PLAYER)->AddAnimation(m_sPlayerMotion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_PLAYER)->GetAnimation(i))
		{
			MessageBox(NULL, m_sPlayerMotion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	//�X���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL1_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_BLUE)->AddAnimation(m_sLevel1_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_BLUE)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel1_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	//�΃X���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL2_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_GREEN)->AddAnimation(m_sLevel2_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_GREEN)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel2_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	//���F�X���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL3_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_YELLOW)->AddAnimation(m_sLevel3_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_YELLOW)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel3_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	//�ԃX���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL4_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_RED)->AddAnimation(m_sLevel4_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_RED)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel4_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	// ���X���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlimeBase::FLAME_SLIME_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_FLAME)->AddAnimation(m_sFlameSlime_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_FLAME)->GetAnimation(i))
		{
			MessageBox(NULL, m_sFlameSlime_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	// �񕜃X���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlimeBase::HEAL_SLIME_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_HEAL)->AddAnimation(m_sHealSlime_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_HEAL)->GetAnimation(i))
		{
			MessageBox(NULL, m_sHealSlime_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	// �f�r���X���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlime_BossBase::DEVIL_SLIME_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_DEVIL)->AddAnimation(m_sDevilSlime_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_DEVIL)->GetAnimation(i))
		{
			MessageBox(NULL, m_sDevilSlime_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}

	// ��X���C���̃A�j���[�V�����ǂݍ���
	for (int i = 0; i < CSlime_BossBase::ROCK_SLIME_MAX; i++)
	{
		//�e�A�j���[�V�����̓ǂݍ���
		m_ModelList.at(MODEL_SLIME_ROCK)->AddAnimation(m_sRockSlime_Motion[i].c_str());
		//�ǂݍ��݂Ɏ��s������G���[���b�Z�[�W
		if (!m_ModelList.at(MODEL_SLIME_ROCK)->GetAnimation(i))
		{
			MessageBox(NULL, m_sRockSlime_Motion[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}
}

/* ========================================
   �֐��F���f���擾�֐�
   ----------------------------------------
   ���e�F�w�肵�����f�����擾����֐�
   ----------------------------------------
   �����F���f���̎��
   ----------------------------------------
   �ߒl�F���f���|�C���^
======================================== */
AnimeModel * CModelManager::GetModelPtr(MODEL_KIND model)
{
	return m_ModelList.at(model);
}
