/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�R�A�Ǘ��pcpp
	---------------------------------------
	ScoreManager.cpp

	�쐬��	�R�{�M��

	�ύX����
	�E2023/11/18�@�쐬 yamamoto
	�E2023/11/25�@�R�����g�����A�g���Ă��Ȃ��֐��폜 yamamoto

========================================== */

// =============== �C���N���[�h ===================
#include "ScoreOHManager.h"
#include "GameParameter.h"
#include "Sphere.h"				//����`�w�b�_�[�@�Ȃ�ł�������񂯂Ǖt������܂��ɂȂ�
// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else

#endif
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
	: m_pCamera(nullptr)
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
/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CScoreOHManager::Update()
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// ���g�p�̔����̓X���[
		if (m_pScore[i] == nullptr)
		{
			continue;
		}

		m_pScore[i]->Update();
	}

	DeleteCheck();	// �폜�`�F�b�N
}
/* ========================================
	�`�揈���֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F����
=========================================== */
void CScoreOHManager::Draw()
{
	// slime�̏�ɕ\������X�R�A�̌���
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// ���g�p�̃X�R�A�̓X���[
		if (m_pScore[i] == nullptr) continue;
	
		m_pScore[i]->Draw(); // �X�R�A�̕`��
	}

}
/* ========================================
	���������֐��i�ԓ��m�̍ŏ��̔��j���j
	-------------------------------------
	���e�F����X�R�A�̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F�X�R�A
	����3�F�X�R�A�\���ʒu
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CScoreOHManager::DisplayOverheadScore(TTriType<float> pos,int score,float height)
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̔����̓X���[
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScoreOverHead(pos,score, height, LEVEL_4_EXPLODE_TIME,false);
		m_pScore[i]->SetCamera(m_pCamera);
		break;
	}
}
/* ========================================
	���������֐��i���j�Ɋ������܂ꂽ�X���C���̃X�R�A�j
	-------------------------------------
	���e�F����X�R�A�̐���
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F�X�R�A
	����3�F�X�R�A�\���ʒu
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CScoreOHManager::DisplayOverheadScore(TTriType<float> pos, E_SLIME_LEVEL level)
{
	 int score;
	float ScoreTime;
	switch (level) {
	case LEVEL_1:		score = LEVEL_1_SCORE;  ScoreTime = LEVEL_1_EXPLODE_TIME; break;
	case LEVEL_2:		score = LEVEL_2_SCORE;  ScoreTime = LEVEL_2_EXPLODE_TIME; break;
	case LEVEL_3:		score = LEVEL_3_SCORE;  ScoreTime = LEVEL_3_EXPLODE_TIME; break;
	case LEVEL_4:		score = LEVEL_4_SCORE;  ScoreTime = LEVEL_4_EXPLODE_TIME; break;
	case LEVEL_FLAME:	score = LEVEL_1_SCORE;  ScoreTime = LEVEL_1_EXPLODE_TIME; break;
	case LEVEL_HEAL:	score = LEVEL_1_SCORE;  ScoreTime = LEVEL_1_EXPLODE_TIME; break;	// �񕜃X���C���̓_���Ǝc�莞��
	}
	// �X�R�A������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// �g�p�ς݂̃X�R�A�̓X���[
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScoreOverHead(pos, score, SLIME_SCORE_HEIGHT, ScoreTime,true);
		m_pScore[i]->SetCamera(m_pCamera);
		break;
	}
}

/* ========================================
	�X�R�A�폜�֐�
	----------------------------------------
	���e�F�X�R�A����������`�F�b�N���Ă���폜
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CScoreOHManager::DeleteCheck()
{
	// ����������
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// ���g�p�̃X�R�A�̓X���[
		if (m_pScore[i] == nullptr) continue;
		// �폜�t���O�������ĂȂ��X�R�A�̓X���[
		if (m_pScore[i]->GetDelFlg() == false) continue;

		delete m_pScore[i]; m_pScore[i] = nullptr;	// �������폜����

	}
}
/* ========================================
   �J�����̃Z�b�g�֐�
   ----------------------------------------
   ���e�F�v���C���[�Ǐ]�J�������Z�b�g����
   ----------------------------------------
   �����F�J����
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CScoreOHManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;	//���g�͕ς����Ȃ����ǃ|�C���^�͂������̂Ń��V�I
}
