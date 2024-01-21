/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y3�p�w�b�_
	------------------------------------
	Slime_3.h
	------------------------------------
	�쐬�ҁ@yamashita

	�ύX����
	�E2023/11/08 �쐬 yamashita
	�E2023/11/08 �X���C���̈ړ����x��ݒ肷��֐����p�� yamashita
	�E2023/11/30 Update��NormalMove��override yamashita
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SLIME_3_H__	//Slime_3.h�C���N���[�h�K�[�h
#define __SLIME_3_H__

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

	void Update();
	void NormalMove() final;	// �ʏ펞�̈ړ�����

	void SetNormalSpeed() override;
private:

};


#endif	//!__SLIME_3_H__