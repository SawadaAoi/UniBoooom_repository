/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y1�p�w�b�_
	------------------------------------
	Slime_1.h
	------------------------------------
	�쐬�ҁ@sawada

	�ύX����
	�E2023/11/08 �쐬 sawada
	�E2023/11/08 �X���C���̈ړ����x��ݒ肷��֐����p�� yamashita
	�E2023/11/16 �����t���R���X�g���N�^�̈����ɒ��_�V�F�[�_�[�ƃ��f���̃|�C���^��ǉ� yamashita
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SLIME_1_H__	//Slime_1.h�C���N���[�h�K�[�h
#define __SLIME_1_H__

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


#endif	//!__SLIME_1_H__