/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�q�[���X���C��.cpp
	------------------------------------
	Slime_Heal.cpp
	------------------------------------
	�쐬��	�A�F��

	�ύX����
	�E2023/12/04 cpp�쐬 Tei
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_Heal.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_HEAL_SCALE = 1.0f;						// �X���C���Q�q�[���̑傫��(�����蔻��܂�)
const float LEVEL_HEAL_SPEED = ENEMY_MOVE_SPEED * 0.3f;		// �ړ����x
const int	LEVEL_HEAL_ATTACK = 1;							// �U���� �i����H
#endif
const float LEVEL_HEAL_SHADOW_SCALE = 2.0f;	// �X���C���Q�q�[���̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Heal::CSlime_Heal()
{
	m_Transform.fScale = { LEVEL_HEAL_SCALE,LEVEL_HEAL_SCALE ,LEVEL_HEAL_SCALE };
	m_Sphere.fRadius *= LEVEL_HEAL_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_HEAL;
	SetNormalSpeed();
	m_nAttack = LEVEL_HEAL_ATTACK;
	m_fScaleShadow = LEVEL_HEAL_SHADOW_SCALE;	// �e�̑傫����ݒ�
}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	����2�F�V�F�[�_�[�|�C���^
	����3�F���f���|�C���^
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Heal::CSlime_Heal(TPos3d<float> pos, AnimeModel * pModel)
	:CSlime_Heal()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pModel = pModel;

	// �A�j���[�V�����̃Z�b�g
	m_eCurAnime = (int)HEAL_SLIME_MOVE;	// ���݂̃A�j���[�V�������Z�b�g
	m_pModel->Play(m_eCurAnime, true);
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Heal::~CSlime_Heal()
{

}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X���C���̍s���𖈃t���[���X�V����
	-------------------------------------
	����1�F�v���C���[�̏��A�X���C���̈ړ����x
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSlime_Heal::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;	// �v���C���[�̍ŐV�p�����[�^���擾
	m_fAnimeTime += ADD_ANIME;

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		// ���݂̃A�j���[�V�������u�ړ��v�ȊO�Ȃ�ړ����[�V�����ɕύX
		if (m_eCurAnime != (int)HEAL_SLIME_MOVE)
		{
			m_eCurAnime = (int)HEAL_SLIME_MOVE;
			m_fAnimeTime = 0.0f;	//�A�j���[�V�����^�C���̃��Z�b�g
		}

		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//��~�t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ړ�
		}
		else
		{	// �߂��Ŕ������N�����炻�̏�Œ�~����
			MoveStop();	
		}
	}
	else
	{
		//�G�̐�����шړ�
		HitMove();

		// ���݂̃A�j���[�V�������u�ړ��v�ȊO�Ȃ�ړ����[�V�����ɕύX
		if (m_eCurAnime != (int)HEAL_SLIME_HIT)
		{
			m_eCurAnime = (int)HEAL_SLIME_HIT;
			m_fAnimeTime = 0.0f;	//�A�j���[�V�����^�C���̃��Z�b�g
		}
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x * fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z * fSlimeMoveSpeed;
}

/* ========================================
	�ʏ�ړ��֐�
	-------------------------------------
	���e�F�X���C���̒ʏ�ړ����I�[�o�[���C�h
	-------------------------------------
	����1�F�v���C���[�����蔻��(Sphere) ���g�p���ĂȂ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSlime_Heal::NormalMove()
{
	RandomMove();	// �����_���ړ�
}

/* ========================================
	�X�s�[�h����֐�
	-------------------------------------
	���e�F�X���C���̈ړ����x��ݒ�
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSlime_Heal::SetNormalSpeed()
{
	m_fSpeed = LEVEL_HEAL_SPEED;	//�ړ����x�ɒ萔���Z�b�g

}
