/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X�R�A�w�b�_�[
   ---------------------------------------
   Score.h

   �쐬�� �R�{�@�M��

   �ύX����
	�E2023/11/17�@�쐬
========================================== */
#ifndef __SCORE_H__
#define __SCORE_H__
// =============== �C���N���[�h ===================
#include "Transform3d.h"	//���[���h���W�n���w�b�_�[
// =============== �N���X��` =====================
class CScore
{
public:
	CScore(TPos3d<float> fPos,float fTime,int nScore);
	~CScore();

	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�

private:

};






#endif // __SCORE_H__