/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y4�p�\�[�X
	------------------------------------
	Slime_4.cpp
	------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/08 �쐬 yamashita
	�E2023/11/08 �傫���̒萔���`	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �R���X�g���N�^�Ń��x�����Ƃ̃p�����[�^���Z�b�g	yamashita
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	�E2023/11/14 Base���烂�f���A�V�F�[�_�̓ǂݍ��݂��ړ� suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� takagi
	�E2023/11/15 �X���C���̃��f���ƒ��_�V�F�[�_�[��manager����󂯎��悤�ɕύX yamashita
	�E2023/11/28 �e�̑傫����ݒ肷��ϐ��ǉ� nieda
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_4.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL4_SCALE = 4.0f;
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.85;
const int	LEVEL4_ATTACK = 2;	// �U����
#endif
const float LEVEL_4_SHADOW_SCALE = 8.0f;	// �X���C���Q���x���S�̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_4::CSlime_4()
{
	m_Transform.fScale = { LEVEL4_SCALE,LEVEL4_SCALE ,LEVEL4_SCALE };
	m_Sphere.fRadius *= LEVEL4_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_4;
	SetNormalSpeed();
	m_nAttack = LEVEL4_ATTACK;
	m_fScaleShadow = LEVEL_4_SHADOW_SCALE;	// �e�̑傫����ݒ�
}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	����2�F���_�V�F�[�_�[�̃|�C���^
	����3�F���f���̃|�C���^
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_4::CSlime_4(TPos3d<float> pos, VertexShader* pVS, Model* pModel)
	: CSlime_4()
{
	m_Transform.fPos = pos;			// �������W���w��
	m_pVS = pVS;
	m_pModel = pModel;
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
CSlime_4::~CSlime_4()
{
}

void CSlime_4::Update()
{
	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		if (!m_bEscape  && m_nEscapeCnt == 0)	//������t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ٓ�
		}
		else
		{
			Escape();	//�������瓦����
		}
	}
	else
	{
		//�G�̐�����шړ�
		HitMove();
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x;// *fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z;// *fSlimeMoveSpeed;

	C3dObject::Update();
}

void CSlime_4::NormalMove()
{
	TPos3d<float> playerPos = m_PlayerTran->fPos;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// �v���C���[�Ƌ��������ȓ���������
	if (distancePlayer < 5)
	{
		// �v���C���[�ւ̊p�x���擾
		float rad = atan2f(playerPos.z - m_Transform.fPos.z, playerPos.x - m_Transform.fPos.x);
		// �v���C���[�Ɣ��Ε����Ɉړ�
		m_move.x = -(cosf(rad)) * m_fSpeed;
		m_move.z = -(sinf(rad)) * m_fSpeed;
		m_Transform.fRadian.y = atan2f(m_move.x, m_move.z);
	}
	else
	{
		RandomMove();	// �����_���ړ�

	}
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
void CSlime_4::SetNormalSpeed()
{
	m_fSpeed = LEVEL4_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}



