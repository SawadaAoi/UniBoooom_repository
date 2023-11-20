/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�R�A�Ǘ��pcpp
	---------------------------------------
	ScoreManager.cpp

	�쐬��	�R�{�M��

	�ύX����
	�E2023/11/18�@�쐬

========================================== */

// =============== �C���N���[�h ===================
#include "ScoreManager.h"
#include "GameParameter.h"
#include "Sphere.h"				//����`�w�b�_�[�@�Ȃ�ł�������񂯂Ǖt������܂��ɂȂ�

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CScoreManager::CScoreManager()
{
	// �X�R�A�z��̏�����
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		m_pScore[i] = nullptr;
	}
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
CScoreManager::~CScoreManager()
{
	// �������폜
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		SAFE_DELETE(m_pScore[i]);
	}
}

void CScoreManager::Update()
{
}

void CScoreManager::Draw()
{
	// slime�̏�ɕ\������X�R�A�̌���
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// ���g�p�̃X�R�A�̓X���[
		if (m_pScore[i] == nullptr) continue;
	
		m_pScore[i]->Draw(); // �����̕`��
	}

	//�g�[�^���X�R�A�̕\��

}

void CScoreManager::CreateScore(TTriType<float> pos,int score,float posY)
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̔����̓X���[
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScore(pos,score,posY);
	}
}

void CScoreManager::AddScore()
{

}
