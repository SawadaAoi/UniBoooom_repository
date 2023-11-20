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
#include <Texture.h>
#include <vector>
#include "Camera.h"			//�J������`�w�b�_�[


// =============== �N���X��` =====================
class CScore
{
public:
	CScore(TPos3d<float> fPos,int nScore, float posY);
	~CScore();

	
	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	std::vector<int> digitsToArray(int score);	//�����̐������e��1���z��ɓ����
private:
	Texture* m_pScoreTexture;	//�X�R�A�\���p�e�N�X�`���|�C���^
	tagTransform3d m_Transform;	//���[���h���W�n�ɕK�v�ȏ��

	std::vector<int> digits;	//�e��1������邽�߂̔z��
	std::vector<int> digitArray;//digits�������ɓ����
	int ArraySize;				//�\������for���Ŏg�p

	const CCamera*	m_pCamera;	//�J�����̃|�C���^

};






#endif // __SCORE_H__