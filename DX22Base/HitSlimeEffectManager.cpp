/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�q�b�g�X���C���G�t�F�N�g�Ǘ��pcpp
	---------------------------------------
	HitSlimeEffectManager.cpp

	�쐬��	�A �F��

	�ύX����
	�E2024/01/25 HitSlimeEffectManager�N���X�쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "HitSlimeEffectManager.h"

// =============== �萔��` =======================
const float TOTAL_HIT_EFFECT_TIME = 15.0f;

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CHitSlimeEffectManager::CHitSlimeEffectManager()
{

	// �q�b�g�G�t�F�N�g�z��̏�����
	for (int i = 0; i < MAX_HIT_NUM; i++)
	{
		m_phitEffect[i] = nullptr;
	}

	//�G�t�F�N�g������
	m_hitEffect = LibEffekseer::Create("Assets/Effect/hit_effect/hit.efkefc");
}

/* ========================================
	�֐��F�f�X�g���N�^
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CHitSlimeEffectManager::~CHitSlimeEffectManager()
{
	// �������폜
	for (int i = 0; i < MAX_HIT_NUM; i++)
	{
		SAFE_DELETE(m_phitEffect[i]);
	}
}

/* ========================================
	�֐��F�`��֐�
	----------------------------------------
	���e�F�����}�l�[�W���[�̕`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CHitSlimeEffectManager::Draw()
{
	// �q�b�g�G�t�F�N�g�̌���
	for (int i = 0; i < MAX_HIT_NUM; i++)
	{
		// ���g�p�̃q�b�g�G�t�F�N�g�̓X���[
		if (m_phitEffect[i] == nullptr) continue;

		m_phitEffect[i]->Draw(); // �q�b�g�G�t�F�N�g�̕`��

		break;
	}
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�����}�l�[�W���[�̍X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CHitSlimeEffectManager::Update()
{
	// �q�b�g�G�t�F�N�g������
	for (int i = 0; i < MAX_HIT_NUM; i++)
	{
		// ���g�p�̃q�b�g�G�t�F�N�g�̓X���[
		if (m_phitEffect[i] == nullptr) continue;
		m_phitEffect[i]->Update();
	}
	DeleteCheck();	// �폜�`�F�b�N
}

/* ========================================
	�q�b�g�G�t�F�N�g�z��擾�֐�
	----------------------------------------
	���e�F�q�b�g�G�t�F�N�g�z��̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�q�b�g�G�t�F�N�g�̔z��
======================================== */
CHitEffect * CHitSlimeEffectManager::GetHitPtr(int num)
{
	if (!m_phitEffect[num]) { return nullptr; }
	return m_phitEffect[num];
}

/* ========================================
	���������֐�
	-------------------------------------
	���e�F�q�b�g�G�t�F�N�g�̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CHitSlimeEffectManager::Create(TTriType<float> pos)
{
	// �q�b�g�G�t�F�N�g������
	for (int i = 0; i < MAX_HIT_NUM; i++)
	{
		// �g�p�ς݂̃q�b�g�G�t�F�N�g�̓X���[
		if (m_phitEffect[i] != nullptr) continue;

		// ���W�A�G�t�F�N�g���ԁAEffekseer�t�@�C���A�J�������w�肵�Đ���
		m_phitEffect[i] = new CHitEffect(pos, TOTAL_HIT_EFFECT_TIME, m_hitEffect, m_pCamera);	
		//m_phitEffect[i]->SetCamera(m_pCamera);		//�J�����Z�b�g
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
void CHitSlimeEffectManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}


/* ========================================
	�q�b�g�G�t�F�N�g�폜�֐�
	----------------------------------------
	���e�F�q�b�g�G�t�F�N�g������������`�F�b�N���Ă���폜
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CHitSlimeEffectManager::DeleteCheck()
{
	// �q�b�g�G�t�F�N�g������
	for (int i = 0; i < MAX_HIT_NUM; i++)
	{
		// ���g�p�̃q�b�g�G�t�F�N�g�̓X���[
		if (m_phitEffect[i] == nullptr) continue;
		// �폜�t���O�������ĂȂ��q�b�g�G�t�F�N�g�̓X���[
		if (m_phitEffect[i]->GetDelFlg() == false) continue;

		delete m_phitEffect[i]; m_phitEffect[i] = nullptr;	// �q�b�g�G�t�F�N�g���폜����

	}
}
