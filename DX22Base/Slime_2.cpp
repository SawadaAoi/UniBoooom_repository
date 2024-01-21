/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y2�p�\�[�X
	------------------------------------
	Slime_2.cpp
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
	�E2023/12/01 �^�b�N���̋�����ǉ� yamashita
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_2.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[

// =============== �萔��` =======================
const int	LEVEL2_ATTACK = 1;						// �U����
#if MODE_GAME_PARAMETER
#else
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;
#endif
const float LEVEL_2_SHADOW_SCALE = 2.5f;	// �X���C���Q���x���Q�̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_2::CSlime_2()
	: m_AtcMoveType(ATTACK_NONE)
	, m_nChargeCnt(0)
	, m_nTackleCnt(0)
	, m_nAtkInterval(0)
	, tackleDirection{0.0f,0.0f,0.0f,0.0f}
{
	m_Transform.fScale = { LEVEL2_SCALE,LEVEL2_SCALE ,LEVEL2_SCALE };
	m_Sphere.fRadius *= LEVEL2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_2;
	SetNormalSpeed();
	m_nAttack = LEVEL2_ATTACK;
	m_fScaleShadow = LEVEL_2_SHADOW_SCALE;	// �e�̑傫����ݒ�
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
CSlime_2::CSlime_2(TPos3d<float> pos,VertexShader* pVS,Model* pModel)
	: CSlime_2()
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
CSlime_2::~CSlime_2()
{
}

void CSlime_2::Update()
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
}

/* ========================================
	�ʏ�ړ��֐�
	----------------------------------------
	���e�F�v���C���[��ǐՂ���ړ����s��
	----------------------------------------
	����1�F�v���C���[�����蔻��(Sphere)
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlime_2::NormalMove()
{

	TPos3d<float> playerPos = m_PlayerTran->fPos;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// �v���C���[�Ƌ��������ȓ���������
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		if (m_nAtkInterval > LEVEL2_ATTACK_INTERVAL && m_AtcMoveType == ATTACK_NONE)
		{
			m_AtcMoveType = ATTACK_CHARGE;
			m_nAtkInterval = 0;
			return;
		}
	}

	//��Ԃɂ�镪�򏈗�
	switch (m_AtcMoveType)
	{
	case(ATTACK_NONE):	//�ʏ��Ԃ̎�
		m_nAtkInterval++;
		CSlimeBase::NormalMove();

		return;
	case (ATTACK_CHARGE):
		if (m_nChargeCnt > LEVEL2_ATTACK_CHARGE_CNT)
		{	//�`���[�W�̎��Ԃ𒴂��Ă�����^�b�N����ԂɈڍs����
			m_AtcMoveType = ATTACK_TACKLE;
			m_nChargeCnt = 0;
		}
		else 
		{ //�܂���������J�E���g�𗭂߂�
			m_nChargeCnt++; 
			CSlimeBase::NormalMove();

		}	

		//�^�b�N���̊p�x���m��
		// �G����v���C���[�ւ̃x�N�g��
		DirectX::XMFLOAT3 directionVector;
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;
		
		// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
		tackleDirection = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// �����x�N�g�������]�s����v�Z
		m_Transform.fRadian.y = (atan2(-tackleDirection.m128_f32[0], -tackleDirection.m128_f32[2]));

		//�ړ���0��
		m_move = TTriType<float>(0.0f, 0.0f, 0.0f);

		return;
	case (ATTACK_TACKLE):
		if (m_nTackleCnt < LEVEL2_ATTACK_TACKLE_CNT)
		{	//�^�b�N�����Ԃɖ����Ȃ��Ȃ�^�b�N���p��
			m_nTackleCnt++;
			m_move.x = sin(m_Transform.fRadian.y) * LEVEL2_TACKLE_SPEED;
			m_move.z = cos(m_Transform.fRadian.y) * LEVEL2_TACKLE_SPEED;

			return;
		}
		else //�^�b�N�����Ԃ𒴂��Ă���΃^�b�N���I��
		{
			m_AtcMoveType = ATTACK_NONE;
			m_nTackleCnt = 0;
			CSlimeBase::NormalMove();
		}
		break;
	}

	//��L�̂ǂ�if�ɂ����Ă͂܂�Ȃ��ꍇ�����_���ړ�
	RandomMove();
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
void CSlime_2::SetNormalSpeed()
{
	m_fSpeed = LEVEL2_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}



