/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��.h
	------------------------------------
	Slime_Boss.h
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/17 �N���X�쐬 Suzumura
	�E2023/11/20 Damage�AIsDead�֐���ǉ� Suzumura
	�E2023/11/23 MaxHp�֌W��ǉ� Suzumura

========================================== */
#ifndef __SLIME_BOSS_BASE__H__
#define __SLIME_BOSS_BASE__H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"

// =============== �N���X��` =====================
class CSlime_BossBase :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾======
	CSlime_BossBase();
	~CSlime_BossBase();


	void Warp(TPos3d<float> playerPos);	// ���[�v�֐� TODO:������

	void Damage(int num);		// �_���[�W�֐�
	bool IsDead();				// ����ł��邩�ǂ���

	virtual void SetMaxHp() = 0;

protected:
	// ===�����o�ϐ�======
	int m_nMaxHp;	//�ő�HP�̓{�X�ɂ���ĕύX����������protected��

private:

	int m_nHp;
	bool m_bDead;
};


#endif //__SLIME_BOSS_BASE__H__
