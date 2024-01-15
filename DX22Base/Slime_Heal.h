/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�q�[���X���C��.h
	------------------------------------
	Slime_Heal.h
	------------------------------------
	�쐬��	�A�F��

	�ύX����
	�E2023/12/04 �N���X�쐬 Tei

========================================== */
#ifndef __SLIME_HEAL__H__
#define __SLIME_HEAL__H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"
#include "GameParameter.h"
#include "AnimeModel.h"
// =============== �N���X��` =====================
class CSlime_Heal :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Heal();
	CSlime_Heal(TPos3d<float> pos, VertexShader* pVS, AnimeModel* pModel);
	~CSlime_Heal();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:

};


#endif __SLIME_HEAL__H__
