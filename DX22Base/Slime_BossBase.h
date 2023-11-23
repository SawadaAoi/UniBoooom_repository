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
	�E2023/11/23 Hp�֌W��ǉ� Suzumura
	�E2023/11/23 �_�ŏ������� Suzumura
========================================== */
#ifndef __SLIME_BOSS_BASE__H__
#define __SLIME_BOSS_BASE__H__

// =============== �C���N���[�h ===================
#include "SlimeBase.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const int DAMAGE_FLASH_FRAME = 0.1 * 60;		// �_���[�W�󂯂��ۂ̓_�Ńt���[��(���G�ł͂Ȃ�)
const int DAMAGE_FLASH_TOTAL_FRAME = 0.5 * 60;	// �_���[�W���󂯂��ۂ̓_�ł����t���[���s����
#endif

// =============== �N���X��` =====================
class CSlime_BossBase :
	public CSlimeBase
{
public:
	// ===�v���g�^�C�v�錾======
	CSlime_BossBase();
	~CSlime_BossBase();

	void Update(TPos3d<float> playerPos) override;
	void Draw(const CCamera* pCamera) override;

	void Warp(TPos3d<float> playerPos);	// ���[�v�֐� TODO:������

	void Damage(int num);		// �_���[�W�֐�
	bool IsDead();				// ����ł��邩�ǂ���
	virtual void SetMaxHp() = 0;

protected:
	// ===�����o�ϐ�======
	int m_nMaxHp;		//�ő�HP�̓{�X�ɂ���ĕύX����������protected��
	int m_nHp;			// ��HP

	int m_nInvFrame;	// �_�łň����t���[��
	bool m_bDrawFlg;	// �`����s�����ǂ����̃t���O
	bool m_bFlash;		// �_���[�W���󂯂Ĉ�莞�ԓ_�ł����邽�߂̃t���O

private:
	bool m_bDead;		// ����ł��邩�ǂ���

};


#endif //__SLIME_BOSS_BASE__H__
