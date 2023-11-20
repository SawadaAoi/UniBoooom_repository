/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X�R�A�Ǘ��w�b�_�[
   ---------------------------------------
   ScoreManager.h

   �쐬�� �R�{�@�M��

   �ύX����
	�E2023/11/17�@�쐬
========================================== */
#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__

// =============== �C���N���[�h ===================
#include "ScoreOverHead.h"
#include "GameParameter.h"
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CScoreOHManager
{
public:
	// ===�����o�֐��錾===
	CScoreOHManager();		//�R���X�g���N�^
	~CScoreOHManager();		//�f�X�g���N�^

	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	void DisplayOverheadScore(TTriType<float> pos,int score, float height);			// �X�R�A�̐���
	void DisplayOverheadScore(TTriType<float> pos, E_SLIME_LEVEL level);			// �X�R�A�̐���
	void AddScore();			//�X�R�A���Z

	
protected:
	// ===�����o�ϐ��錾===
	CScoreOverHead* m_pScore[MAX_EXPLOSION_NUM];	//�X�R�A�̔z��
	static int m_nTotalScore[5];	//�g�[�^���X�R�A//�����ӏ��Ή�	//�{��������O

private:
	
};


#endif // !__SCORE_MANAGER_H__
