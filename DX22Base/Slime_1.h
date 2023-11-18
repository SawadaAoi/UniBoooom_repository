/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y1�p�w�b�_
	------------------------------------
	Slime_1.h
	------------------------------------
	�쐬�ҁ@�V�c

	�ύX����
	�E2023/11/08 �쐬 �V�c����
	�E2023/11/08 �X���C���̈ړ����x��ݒ肷��֐����p�� �R�����C
	�E2023/11/16 �����t���R���X�g���N�^�̈����ɒ��_�V�F�[�_�[�ƃ��f���̃|�C���^��ǉ� �R�����C

========================================== */
#ifndef __SLIME_1__H__
#define __SLIME_1__H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_1 :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_1();
	CSlime_1(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_1();

	void SetNormalSpeed() override;
private:

};


#endif __SLIME_1__H__