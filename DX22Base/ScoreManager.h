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
#include "Score.h"
#include "GameParameter.h"

// =============== �N���X��` =====================
class CScoreManager
{
public:
	// ===�����o�֐��錾===
	CScoreManager();		//�R���X�g���N�^
	~CScoreManager();		//�f�X�g���N�^

	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	void CreateScore(TTriType<float> pos,float time, int score);			//�X�R�A�̐���
	void AddScore();			//�X�R�A���Z

	
protected:
	// ===�����o�ϐ��錾===
	CScore* m_pScore[MAX_EXPLOSION_NUM];	//�X�R�A�̔z��
	static int m_nTotalScore[5];	//�g�[�^���X�R�A//�����ӏ��Ή�
private:
	
};


#endif // !__SCORE_MANAGER_H__
