/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X�R�A�w�b�_�[
   ---------------------------------------
   Score.h

   �쐬�� �R�{�@�M��

   �ύX����
	�E2023/11/17�@�쐬 yamamoto
	�E2024/02/13 �J�����폜 takagi

========================================== */
#ifndef __SCORE_H__
#define __SCORE_H__
// =============== �C���N���[�h ===================
#include "Transform3d.h"	//���[���h���W�n���w�b�_�[
#include <Texture.h>
#include <vector>

// =============== �N���X��` =====================
class CScoreOverHead
{
public:
	CScoreOverHead(TPos3d<float> fPos,int nScore, float posY, float Time, bool delayFlg);
	~CScoreOverHead();

	
	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	void Delay();				//�X�R�A�\���x������
	void DisplayTimeAdd();		// �X�R�A�\���J�E���g���Z�����֐�
	std::vector<int> digitsToArray(int score);	//�����̐������e��1���z��ɓ����
	bool GetDelFlg();
private:
	Texture* m_pScoreTexture;	//�X�R�A�\���p�e�N�X�`���|�C���^
	tagTransform3d m_Transform;	//���[���h���W�n�ɕK�v�ȏ��

	std::vector<int> digits;	//�e��1������邽�߂̔z��
	std::vector<int> digitArray;//digits�������ɓ����
	int nArraySize;				//�\������for���Ŏg�p
	float m_fExplodeTime;		//����X�R�A�\������
	float m_fDelFrame;			//�\���o�ߎ���
	bool m_bDelFlg;				//�폜�t���O
	bool m_bDelayFlg;			//�X�R�A�\���x���t���O
	int m_nDelayCnt;			//�x�����J�E���g
};






#endif // __SCORE_H__