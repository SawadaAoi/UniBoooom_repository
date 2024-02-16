/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���G�t�F�N�g�Ǘ��pcpp
	---------------------------------------
	SweatEffectManager.cpp

	�쐬��	�A �F��

	�ύX����
	�E2024/02/02 SweatEffectManager�N���X�쐬 Tei
	�E2024/02/13 �J�����폜 takagi

========================================== */

// =============== �C���N���[�h ===================
#include "SweatEffectManager.h"

// =============== �萔��` =======================
const float TOTAL_SWEAT_EFFECT_TIME = 0.75f * 60.0f;

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CSweatEffectManager::CSweatEffectManager()
{
	// ���G�t�F�N�g�z��̏�����
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		m_pSweatEffect[i] = nullptr;
	}
	//�G�t�F�N�g������
	m_SweatEffect = LibEffekseer::Create("Assets/Effect/sweat/HEW_sweat.efkefc");
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
CSweatEffectManager::~CSweatEffectManager()
{
	// �������폜
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		SAFE_DELETE(m_pSweatEffect[i]);
	}
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F���G�t�F�N�g�}�l�[�W���[�̍X�V����
	-------------------------------------
	����1�F���W
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSweatEffectManager::Update(TTriType<float> pos)
{
	// ���G�t�F�N�g������
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// ���g�p�̊��G�t�F�N�g�̓X���[
		if (m_pSweatEffect[i] == nullptr) continue;
		m_pSweatEffect[i]->Update(pos);
	}
	DeleteCheck();	// �폜�`�F�b�N
}

/* ========================================
	�֐��F�`��֐�
	----------------------------------------
	���e�F���G�t�F�N�g�}�l�[�W���[�̕`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSweatEffectManager::Draw()
{
	// ���G�t�F�N�g�̌���
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// ���g�p�̊��G�t�F�N�g�̓X���[
		if (m_pSweatEffect[i] == nullptr) continue;

		m_pSweatEffect[i]->Draw(); // ���G�t�F�N�g�̕`��

	}
}

/* ========================================
	���������֐�
	-------------------------------------
	���e�F���G�t�F�N�g�̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F�����p�x(x,y,z)
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSweatEffectManager::Create(TTriType<float> pos,  TTriType<float> radian)
{
	// ���G�t�F�N�g������
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// �g�p�ς݂̊��G�t�F�N�g�̓X���[
		if (m_pSweatEffect[i] != nullptr) continue;
		// ���W�A�p�x�A�G�t�F�N�g���ԁAEffekseer�t�@�C���A�J�������w�肵�Đ���
		m_pSweatEffect[i] = new CSweatEffect(pos, radian, TOTAL_SWEAT_EFFECT_TIME, m_SweatEffect);
	}
		

}

/* ========================================
	���G�t�F�N�g�폜�֐�
	----------------------------------------
	���e�F���G�t�F�N�g������������`�F�b�N���Ă���폜
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSweatEffectManager::DeleteCheck()
{
	// ���G�t�F�N�g������
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// ���g�p�̊��G�t�F�N�g�̓X���[
		if (m_pSweatEffect[i] == nullptr) continue;
		// �폜�t���O�������ĂȂ����G�t�F�N�g�̓X���[
		if (m_pSweatEffect[i]->GetDelFlg() == false) continue;

		SAFE_DELETE(m_pSweatEffect[i]);	// ���G�t�F�N�g���폜����
	}

}


