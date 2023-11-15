#ifndef __SLIME_3__H__
#define __SLIME_3__H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y3�p�w�b�_
	------------------------------------
	Slime_3.h
	------------------------------------
	�쐬�ҁ@�R�����C

	�ύX����
	�E2023/11/08 �쐬 �R�����C
	�E2023/11/08 �X���C���̈ړ����x��ݒ肷��֐����p�� �R�����C

========================================== */

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_3 :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_3();
	CSlime_3(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_3();

	void SetNormalSpeed() override;
private:

};


#endif __SLIME_3__H__