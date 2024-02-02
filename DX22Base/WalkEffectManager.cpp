/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�v���C���[�ړ��G�t�F�N�g�Ǘ��pcpp
	---------------------------------------
	WalkEffectManager.cpp

	�쐬��	�A �F��

	�ύX����
	�E2024/01/30 WalkEffectManager�N���X�쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "WalkEffectManager.h"

// =============== �萔��` =======================
const float TOTAL_WALK_EFFECT_TIME = 10.0f;		//�G�t�F�N�g�����ԁi�t���[��

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
	: m_fRandNum(0.0f)
{
	
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
	����2�F�v���C���[17�t���[���O�̃g�����X�t�H�[��
	����3�F�v���C���[25�t���[���O�̃g�����X�t�H�[��
	----------------------------------------
	�ߒl�F�ړ��G�t�F�N�g�̔z��
======================================== */
void CWalkEffectManager::Create(tagTransform3d transform, tagTransform3d oldtransform17, tagTransform3d oldtransform25)
{
	
	// �v���C���[�ړ��G�t�F�N�g������
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// �g�p�ς݂̃v���C���[�ړ��G�t�F�N�g�̓X���[
		if (m_pwalkEffect[i] != nullptr) continue;

		// ���W�A�G�t�F�N�g���ԁAEffekseer�t�@�C���A�J�������w�肵�Đ���
		m_pwalkEffect[i] = new CWalkEffect(transform.fPos,oldtransform17.fPos, oldtransform25.fPos, transform.fRadian, TOTAL_WALK_EFFECT_TIME, GetRandom() , m_walkEffect, m_pCamera);
		m_pwalkEffect[i]->SetCamera(m_pCamera);		//�J�����Z�b�g
		break;
	}
}

/* ========================================
	�J�������Z�b�g�֐�
	----------------------------------------
	���e�F�`�揈���Ŏg�p����J�������Z�b�g
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CWalkEffectManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
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
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F������������
======================================== */
float CWalkEffectManager::GetRandom()
{
	
	srand((unsigned int)time(NULL));
	m_fRandNum = ((rand() % 6 + 1) - 3) * 0.1f;	// -0.3	�` 0.3
	return m_fRandNum;
}
