/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t���C���X���C����`
	------------------------------------
	Slime_Flame.h
	------------------------------------
	�쐬��	suzumura

	�ύX����
	�E2023/11/14 �N���X�쐬 suzumura
	�E2023/11/14 NormalMove���I�[�o�[���C�h���č쐬 suzumura
	�E2023/11/15 �X���C���̃��f���ƒ��_�V�F�[�_�[��manager����󂯎��悤�ɕύX yamashita
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SLIME_FLAME_H__	//Slime_Flame.h�C���N���[�h�K�[�h
#define __SLIME_FLAME_H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_Flame :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Flame();
	CSlime_Flame(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_Flame();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:

};


#endif	//!__SLIME_FLAME_H__
