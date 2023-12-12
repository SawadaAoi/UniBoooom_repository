/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��2.cpp
	------------------------------------
	Slime_Boss_2.cpp
	------------------------------------
	�쐬��	�V�c����

	�ύX����
	�E2023/12/12 �N���X�쐬 Sawada

========================================== */


// =============== �C���N���[�h ===================
#include "Slime_Boss_2.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
							

#endif
const float BOSS_2_SCALE = 6.0f;					// �{�X�P�̑傫��
const float BOSS_2_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// �{�X�P�̃X�s�[�h
const int	BOSS_2_MAX_HP = 100;					// �{�X�P�̍ő�HP
const float BOSS_2_SHADOW_SCALE = 12.0f;		// �{�X�P�̉e�̑傫��


CSlime_Boss_2::CSlime_Boss_2()
{
	m_nMoveState = MOVE_STATE::MOVE_NORMAL;
	m_Transform.fScale = { BOSS_2_SCALE,BOSS_2_SCALE ,BOSS_2_SCALE };
	m_Sphere.fRadius *= BOSS_2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_BOSS;
	SetNormalSpeed();
	SetMaxHp();
	m_nHp = m_nMaxHp;
	m_nAttack = BOSS_1_ATTACK;
	m_fScaleShadow = BOSS_2_SHADOW_SCALE;	// �e�̑傫����ݒ�

	for (int i = 0; i < MOVE_STATE::MOVE_MAX; i++)m_nMoveCnt[i] = 0;
}

CSlime_Boss_2::CSlime_Boss_2(TPos3d<float> pos, VertexShader * pVS, Model * pModel1, Model * pModel2)
{
}

CSlime_Boss_2::~CSlime_Boss_2()
{
}

void CSlime_Boss_2::Update(tagTransform3d playerTransform)
{
	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		NormalMove(playerTransform);	// �ʏ�s������
	}
	else
	{
		// �`���[�W���ɂԂ���΂��ꂽ��N�[���^�C���������Z�b�g
		if (m_nMoveState == CHARGE)
		{
			HitMove();		// �G�̐�����шړ�
			ResetAssault();	// �ˌ����Z�b�g
		}

		// �ˌ���Ԃ�"�������"���l�����Ȃ�
		if (m_nMoveState == ASSAULT)
		{
			m_bHitMove = false;
		}
		else
		{
			HitMove(); //�G�̐�����шړ�
		}
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.z += m_move.z;

	// �_���[�W����������Ȃ��Ȃ�_�ŏ������s��Ȃ�
	if (m_bFlash == false) return;
	// �_�ŏ���
	m_nInvFrame++;						//���t���[���ŃJ�E���g��ǉ�
	if (0 == m_nInvFrame % BOSS_DAMAGE_FLASH_FRAME)
	{
		// �`�悷�邩���Ȃ��؂�ւ�
		if (m_bDrawFlg)
		{
			m_bDrawFlg = false;	// true��false
		}
		else
		{
			m_bDrawFlg = true;	// false��true
		}

	}
	// ���_�Ŏ��Ԃ��߂�����I��
	if (m_nInvFrame >= BOSS_DAMAGE_FLASH_TOTAL_FRAME)
	{
		m_bFlash = false;
		m_nInvFrame = 0;
		m_bDrawFlg = true;
	}
}

void CSlime_Boss_2::NormalMove(tagTransform3d playerTransform)
{
}

void CSlime_Boss_2::MoveJump()
{
}

void CSlime_Boss_2::MoveTargetShadow()
{
}

void CSlime_Boss_2::MoveDrop()
{
}

/* ========================================
	�X�s�[�h����֐�
	-------------------------------------
	���e�F�X���C���̈ړ����x��ݒ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::SetNormalSpeed()
{
	m_fSpeed = BOSS_2_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}

/* ========================================
	�}�b�N�XHP����֐�
	-------------------------------------
	���e�F�X���C����MAXHP��ݒ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_2::SetMaxHp()
{
	m_nMaxHp = BOSS_2_MAX_HP;
}
