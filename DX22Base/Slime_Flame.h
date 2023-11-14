/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t���C���X���C��h
	------------------------------------
	Slime_Flame.h
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/14 �N���X�쐬
	�E2023/11/14 NormalMove���I�[�o�[���C�h���č쐬

========================================== */
#ifndef __SLIME_FRAME__H__
#define __SLIME_FRAME__H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_Flame :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Flame();
	CSlime_Flame(TPos3d<float> pos);
	~CSlime_Flame();
	void NormalMove(TPos3d<float> playerSphere) override;
	void SetNormalSpeed() override;

private:

};


#endif __SLIME_FRAME__H__
