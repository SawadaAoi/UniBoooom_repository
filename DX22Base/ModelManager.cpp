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
	m_fModelSize[MODEL_SLIME_YELLOW] = 0.15f;	// ���F�X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_RED] = 0.18f;		// �ԃX���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_FLAME] = 0.3f;		// ���X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_HEAL] = 0.45f;		// �񕜃X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_ROCK] = 0.5f;		// ��X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_SLIME_DEVIL] = 0.23f;	// �f�r���X���C���̃��f���T�C�Y�̔{��
	m_fModelSize[MODEL_ITEM_HEART] = 1.0f;		// �񕜃A�C�e���̃n�[�g�̃��f���T�C�Y�̔{��

	m_sFileName[MODEL_PLAYER] = 1.0f;			// �v���C���[�̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_BLUE] = 0.15f;		// �X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_GREEN] = 0.15f;		// �΃X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_YELLOW] = 0.15f;	// ���F�X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_RED] = 0.18f;		// �ԃX���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_FLAME] = 0.3f;		// ���X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_HEAL] = 0.45f;		// �񕜃X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_ROCK] = 0.5f;		// ��X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_SLIME_DEVIL] = 0.23f;		// �f�r���X���C���̃��f���̃t�@�C����
	m_sFileName[MODEL_ITEM_HEART] = 1.0f;		// �񕜃A�C�e���̃n�[�g�̃��f���̃t�@�C����
	
	// �e���f���̓ǂݍ���
	for (int i = 0; i < (int)MODEL_MAX; i++)
	{
		// ���f���̓��I�m��
		m_pModelList.emplace(MODEL_KIND(i), new AnimeModel());
		// ���f���̓ǂݍ���
		if (!m_pModelList.at(MODEL_KIND(i))->Load(m_sFileName[MODEL_KIND(i)].c_str(), m_fModelSize[MODEL_KIND(i)], AnimeModel::XFlip)) {		//�{���Ɣ��]�͏ȗ���
			MessageBox(NULL, m_sFileName[MODEL_KIND(i)].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
		// ���_�V�F�[�_�[���Z�b�g
		m_pModelList.at((MODEL_KIND)i)->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));	
	}
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
		SAFE_DELETE(m_pModelList.at(MODEL_KIND(i)));
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
