/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �g�[�^���X�R�A�w�b�_�[
   ---------------------------------------
   TotalScore.h

   �쐬�� �R�{�@�M��

   �ύX����
	�E2023/11/22�@�쐬
========================================== */
#ifndef __TOTALSCORE_H__
#define __TOTALSCORE_H__

// =============== �C���N���[�h ===================
#include <Texture.h>
#include "GameParameter.h"

// =============== �N���X��` =====================
class CTotalScore
{
public:
	CTotalScore();
	~CTotalScore();

	void Draw();		 		//�`��֐�
	void AddScore(int Score);
	int GetTotalScore();
private:
	int m_nTotalScore;	
	Texture* m_pToScoreTexture;
};




#endif // !__TOTALSCORE_H__

