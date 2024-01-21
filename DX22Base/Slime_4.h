/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y4�p�w�b�_
	------------------------------------
	Slime_4.h
	------------------------------------
	�쐬�ҁ@yamashita

	�ύX����
	�E2023/11/08 �쐬 yamashita
	�E2023/11/08 �X���C���̈ړ����x��ݒ肷��֐����p�� yamashita
	�E2023/11/16 �����t���R���X�g���N�^�̈����ɒ��_�V�F�[�_�[�ƃ��f���̃|�C���^��ǉ� yamashita
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SLIME_4_H__	//Slime_4.h�C���N���[�h�K�[�h
#define	__SLIME_4_H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_4 :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_4();
	CSlime_4(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_4();
	void Update() override;

	void NormalMove() override;

	void SetNormalSpeed() override;
private:
	

};


#endif	//!__SLIME_4_H__