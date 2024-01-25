/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t���C���X���C��cpp
	------------------------------------
	Slime_Flame.cpp
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/14 �N���X�쐬 Suzumura
	�E2023/11/14 ���X���C���d�l�̎��� Suzumura
	�E2023/11/15 �X���C���̃��f���ƒ��_�V�F�[�_�[��manager����󂯎��悤�ɕύX yamashita
	�E2023/11/28 �e�̑傫����ݒ肷��ϐ��ǉ� nieda
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2024/01/18 ���X���C���G�t�F�N�g�ǉ� Tei

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_Flame.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_FLAME_SCALE = 1.0f;
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;
const int	LEVEL_FLAME_ATTACK = 1;	// �U����
#endif
const float LEVEL_FLAME_SHADOW_SCALE = 2.0f; // �X���C���Q�t���C���̉e�̑傫��
const float FLAME_EFFECT_SCALE = 0.7f;		 // �X���C���Q�t���C���̉��G�t�F�N�g�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Flame::CSlime_Flame()
{
	m_Transform.fScale = { LEVEL_FLAME_SCALE,LEVEL_FLAME_SCALE ,LEVEL_FLAME_SCALE };
	m_Sphere.fRadius *= LEVEL_FLAME_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_FLAME;
	SetNormalSpeed();	
	m_nAttack = LEVEL_FLAME_ATTACK;
	m_fScaleShadow = LEVEL_FLAME_SHADOW_SCALE;	// �e�̑傫����ݒ�
}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Flame::CSlime_Flame(TPos3d<float> pos, Effekseer::EffectRef flameSlimeEffect, VertexShader* pVS, AnimeModel* pModel)
	: CSlime_Flame()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pVS = pVS;
	m_pModel = pModel;
	// �G�t�F�N�g������
	m_flameSlimeEffect = flameSlimeEffect;	//�G�t�F�N�g���Z�b�g
	m_efcslimeHnadle = LibEffekseer::GetManager()->Play(m_flameSlimeEffect, pos.x, pos.y, pos.z + 0.5f);	//�G�t�F�N�g�̊J�n
	LibEffekseer::GetManager()->SetScale(m_efcslimeHnadle, FLAME_EFFECT_SCALE, FLAME_EFFECT_SCALE * 1.1f, FLAME_EFFECT_SCALE);	//�G�t�F�N�g�̃T�C�Y��ݒ�
	LibEffekseer::GetManager()->SetRotation(m_efcslimeHnadle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);					//�G�t�F�N�g�̉�]�p�x��ݒ�
	LibEffekseer::GetManager()->SetLocation(m_efcslimeHnadle, pos.x, pos.y, pos.z);																	//�G�t�F�N�g�̈ʒu��ݒ�
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F
	-------------------------------------
	�ߒl�F
=========================================== */
CSlime_Flame::~CSlime_Flame()
{
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
void CSlime_Flame::NormalMove()
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
void CSlime_Flame::SetNormalSpeed()
{
	m_fSpeed = LEVEL_FLAME_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}



