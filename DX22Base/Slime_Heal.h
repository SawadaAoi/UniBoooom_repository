/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�q�[���X���C����`
	------------------------------------
	Slime_Heal.h
	------------------------------------
	�쐬��	tei

	�ύX����
	�E2023/12/04 �N���X�쐬 tei
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SLIME_HEAL_H__	//Slime_Heal.h�C���N���[�h�K�[�h
#define __SLIME_HEAL_H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"
#include "GameParameter.h"

// =============== �N���X��` =====================
class CSlime_Heal :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Heal();
	CSlime_Heal(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_Heal();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:

};


#endif	//!__SLIME_HEAL_H__