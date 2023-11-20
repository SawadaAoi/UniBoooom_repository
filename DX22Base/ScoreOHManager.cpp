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
#include "ScoreOHManager.h"
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
CScoreOHManager::CScoreOHManager()
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
CScoreOHManager::~CScoreOHManager()
{
	// �������폜
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		SAFE_DELETE(m_pScore[i]);
	}
}

void CScoreOHManager::Update()
{
}

void CScoreOHManager::Draw()
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

void CScoreOHManager::DisplayOverheadScore(TTriType<float> pos,int score,float height)
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̔����̓X���[
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScoreOverHead(pos,score, height);
	}
}

void CScoreOHManager::DisplayOverheadScore(TTriType<float> pos, E_SLIME_LEVEL level)
{
	float height; int score;

	switch (level) {
	case LEVEL_1:		score = LEVEL_1_SCORE; height = LEVEL_1_HEIGHT; break;
	case LEVEL_2:		score = LEVEL_2_SCORE; height = LEVEL_2_HEIGHT; break;
	case LEVEL_3:		score = LEVEL_3_SCORE; height = LEVEL_3_HEIGHT; break;
	case LEVEL_4:		score = LEVEL_4_SCORE; height = LEVEL_4_HEIGHT; break;
	case LEVEL_FLAME:	score = LEVEL_1_SCORE; height = LEVEL_1_HEIGHT; break;
	}
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̔����̓X���[
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScoreOverHead(pos, score, height);
	}
}

void CScoreOHManager::AddScore()
{

}
