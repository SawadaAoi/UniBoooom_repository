/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t���C���X���C��h
	------------------------------------
	Slime_Flame.h
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/14 �N���X�쐬 Suzumura
	�E2023/11/14 NormalMove���I�[�o�[���C�h���č쐬 Suzumura
	�E2023/11/15 �X���C���̃��f���ƒ��_�V�F�[�_�[��manager����󂯎��悤�ɕύX yamashita
	�E2024/01/18 ���X���C���G�t�F�N�g�ǉ� Tei

========================================== */
#ifndef __SLIME_FLAME__H__
#define __SLIME_FLAME__H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_Flame :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Flame();
	CSlime_Flame(TPos3d<float> pos, Effekseer::EffectRef flameSlimeEffect, VertexShader* pVS, Model* pModel);
	~CSlime_Flame();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:
	////=======Effekseer=======
	//Effekseer::EffectRef m_flameSlimeEffect;
	//Effekseer::Handle m_efcslimeHnadle;
};


#endif __SLIME_FLAME__H__
