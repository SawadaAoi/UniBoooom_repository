/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�v���C���[�ړ��G�t�F�N�g�Ǘ��pcpp
	---------------------------------------
	WalkEffectManager.cpp

	�쐬��	�A �F��

	�ύX����
	�E2024/01/30 WalkEffectManager�N���X�쐬 Tei
	�E2024/02/13 �J�����폜 takagi

========================================== */

// =============== �C���N���[�h ===================
#include "WalkEffectManager.h"

// =============== �萔��` =======================
const int TOTAL_WALK_EFFECT_TIME = 0.5f * 60;		//�G�t�F�N�g�����ԁi�t���[��

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CWalkEffectManager::CWalkEffectManager()
{
	srand((unsigned int)time(NULL));
	
	// �v���C���[�ړ��G�t�F�N�g�z��̏�����
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		m_pwalkEffect[i] = nullptr;
	}

	//�G�t�F�N�g������
	m_walkEffect = LibEffekseer::Create("Assets/Effect/walk_effect/step_smoke.efkefc");

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
CWalkEffectManager::~CWalkEffectManager()
{
	// �������폜
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		SAFE_DELETE(m_pwalkEffect[i]);
	}
}

/* ========================================
   �X�V�����֐��֐�
   ----------------------------------------
   ���e�F�X�V����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CWalkEffectManager::Update()
{
	// �v���C���[�ړ��G�t�F�N�g������
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// ���g�p�̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] == nullptr) continue;
		m_pwalkEffect[i]->Update();
		
	}
	DeleteCheck();	// �폜�`�F�b�N
}

/* ========================================
   �`�揈���֐�
   ----------------------------------------
   ���e�F�`�揈��
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CWalkEffectManager::Draw()
{
	// �q�b�g�G�t�F�N�g�̌���
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// ���g�p�̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] == nullptr) continue;

		m_pwalkEffect[i]->Draw(); // �v���C���[�ړ��G�t�F�N�g�̕`��

		break;
	}
}

/* ========================================
	�ړ��G�t�F�N�g�z��擾�֐�
	----------------------------------------
	���e�F�ړ��G�t�F�N�g�z��̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�ړ��G�t�F�N�g�̔z��
======================================== */
CWalkEffect * CWalkEffectManager::GetWalkPtr(int num)
{
	if (!m_pwalkEffect[num]) { return nullptr; }
	return m_pwalkEffect[num];
}

/* ========================================
	�G�t�F�N�g�쐬�֐�
	----------------------------------------
	���e�F�v���C���[����̍��W��p���Ĉړ��G�t�F�N�g�𐶐�
	----------------------------------------
	����1�F�v���C���[�̃g�����X�t�H�[��
	----------------------------------------
	�ߒl�F����
======================================== */
void CWalkEffectManager::Create(tagTransform3d tTransForm)
{
	// �v���C���[�ړ��G�t�F�N�g������
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// �g�p�ς݂̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] != nullptr) continue;

		// ���W�A�G�t�F�N�g���ԁAEffekseer�t�@�C���A�J�������w�肵�Đ���
		m_pwalkEffect[i] = new CWalkEffect(
			tTransForm,
			TOTAL_WALK_EFFECT_TIME,
			(GetRandom(6) * 0.1f),
			m_walkEffect
		);

		break;
	}
}

/* ========================================
	�ړ��G�t�F�N�g�폜�֐�
	----------------------------------------
	���e�F�ړ��G�t�F�N�g������������`�F�b�N���Ă���폜
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CWalkEffectManager::DeleteCheck()
{
	// �v���C���[�ړ��G�t�F�N�g������
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// ���g�p�̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] == nullptr) continue;
		// �폜�t���O�������ĂȂ��v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i]->GetDelFlg() == false) continue;

		delete m_pwalkEffect[i]; m_pwalkEffect[i] = nullptr;	// �v���C���[�ړ��G�t�F�N�g���폜����

	}
}

/* ========================================
	���������֐�
	----------------------------------------
	���e�F�G�t�F�N�g�Ŏg�������𐶐�����
	----------------------------------------
	�����F�͈͎w��(6�Ɠ��͂����ꍇ�A-3 �` 3)
	----------------------------------------
	�ߒl�F������������
======================================== */
int CWalkEffectManager::GetRandom(int nRange)
{
	int reRandNum = ((rand() % nRange + 1) - (nRange / 2));	// -nRange	�` nRange
	return reRandNum;
}
