/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��.cpp
	------------------------------------
	Slime_Boss.cpp
	------------------------------------
	�쐬��	�鑺����

	�ύX����
	�E2023/11/17 �N���X�쐬 Suzumura
	�E2023/11/23 �ˌ������̒ǉ� Suzumura
	�E2023/11/28 �e�̑傫����ݒ肷��ϐ��ǉ� nieda

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_Boss_1.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "Input.h"
// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_BOSS_1_SCALE = 6.0f;						// �{�X�P�̑傫��
const float LEVEL_BOSS_1_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// �{�X�P�̃X�s�[�h
const int BOSS_1_MAX_HP = 100;								// �{�X�P�̍ő�HP

const float ASSAULT_DISTANCE = 0.2f;						// �ˌ���������
const int ASSAULT_COOL_TIME = 10 * 60;						// �ˌ��N���[�^�C��
const int ASSAULT_CHARGE_TIME = 2 * 60;						// �ˌ��`���[�W����
const int ASSAULT_TIME = 1.0f * 60;							// �ˌ�������
const float ASSAULT_SPEED = LEVEL_BOSS_1_SPEED * 15.0f;		// �ˌ����̃X�s�[�h
const int	BOSS_1_ATTACK = 2;	// �U����

#endif
/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Boss_1::CSlime_Boss_1()
	:m_nFrame(0)
	,m_eState(NORMAL)
	,m_assaultDistancePlayer(0.0f)
	,m_assaultMovePos{0.0f,0.0f,0.0f}
{
	m_Transform.fScale = { LEVEL_BOSS_1_SCALE,LEVEL_BOSS_1_SCALE ,LEVEL_BOSS_1_SCALE };
	m_Sphere.fRadius *= LEVEL_BOSS_1_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_BOSS;
	SetNormalSpeed();
	SetMaxHp();
	m_nHp = m_nMaxHp;
	m_nAttack = BOSS_1_ATTACK;
	m_fScaleShadow = BOSS_1_SHADOW_SCALE;	// �e�̑傫����ݒ�

}

/* ========================================
	�R���X�g���N�^�֐�(���W�w��)
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����������W
	����2�F���_�V�F�[�_
	����3�F�������郂�f��
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Boss_1::CSlime_Boss_1(TPos3d<float> pos, VertexShader* pVS, Model* pModel)
	: CSlime_Boss_1()
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
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_Boss_1::~CSlime_Boss_1()
{
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�v���C���[���W(TPos3d)
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::Update(tagTransform3d playerTransform)
{
	
	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		NormalMove(playerTransform);	// �ʏ�s������
	}
	else
	{
		// �`���[�W���ɂԂ���΂��ꂽ��N�[���^�C���������Z�b�g
		if (m_eState == CHARGE)
		{
			HitMove();		// �G�̐�����шړ�
			ResetAssault();	// �ˌ����Z�b�g
		}

		// �ˌ���Ԃ�"�������"���l�����Ȃ�
		if (m_eState == ASSAULT)
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

/* ========================================
	�ʏ�s���֐�(�{�X)
	----------------------------------------
	���e�F�v���C���[��ǐՂ���ړ����s��(�{�X)
	----------------------------------------
	����1�F�v���C���[���W(TPos3d)
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlime_Boss_1::NormalMove(tagTransform3d playerTransform)
{
	TPos3d<float> movePos;
	TPos3d<float> playerPos = playerTransform.fPos;

	// �t���[�����Z
	m_nFrame++;

	// ��Ԃɂ���ē��������
	switch (m_eState)
	{
	//--�m�[�}�����
	case NORMAL:
		// �ϐ��錾
		float distancePlayer;
		DirectX::XMFLOAT3 directionVector;
		DirectX::XMVECTOR direction;

		// �G����G�l�~�[�̋����A�p�x���v�Z
		distancePlayer = m_Transform.fPos.Distance(playerPos);

		movePos = playerPos - m_Transform.fPos;	// �v���C���[�ւ̃x�N�g�����v�Z
		if (distancePlayer != 0)	//0���Z���
		{
			m_move.x = movePos.x / distancePlayer * m_fSpeed;
			m_move.z = movePos.z / distancePlayer * m_fSpeed;
		}
		// �G����v���C���[�ւ̃x�N�g��
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;

		// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
		direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// �����x�N�g�������]�s����v�Z
		m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);

		// �N�[���^�C�����I����ĂȂ��Ȃ�NORMAL�̂܂�
		if (m_nFrame <= ASSAULT_COOL_TIME)	break;

		// �v���C���[�Ƌ��������ȓ���������
		if (distancePlayer > ASSAULT_DISTANCE)
		{
			m_eState = CHARGE;	// "�`���[�W"��ԂɑJ��
			m_nFrame = 0;		// �t���[�����Z�b�g
		}
		break;

		//-- �`���[�W���
	case CHARGE:
		Charge(playerPos, movePos);	// �`���[�W�Ăяo��
		break;

		//-- �ˌ����
	case ASSAULT:
		Assault();		// �ˌ��Ăяo��

		break;

	}
}

/* ========================================
	�`���[�W���s���֐�
	-------------------------------------
	���e�F�{�X���ˌ��̂��߂̃`���[�W���s������
	-------------------------------------
	����1�F�v���C���[���W(TPos3d)
	����2�F�v���C���[�̈ړ���(TPos3d)
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::Charge(TPos3d<float> playerPos, TPos3d<float> movePos)
{
	// �ϐ��錾
	float distancePlayer;
	DirectX::XMFLOAT3 directionVector;
	DirectX::XMVECTOR direction;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	distancePlayer = m_Transform.fPos.Distance(playerPos);
	movePos = playerPos - m_Transform.fPos;	// �v���C���[�ւ̃x�N�g�����v�Z

	if (distancePlayer != 0)	//0���Z���
	{
		// �`���[�W���͑��x�O
		m_fSpeed = 0;	
		m_move.x = movePos.x / distancePlayer * m_fSpeed;
		m_move.z = movePos.z / distancePlayer * m_fSpeed;
	}

	// �G����v���C���[�ւ̃x�N�g��
	directionVector.x = m_Transform.fPos.x - playerPos.x;
	directionVector.y = m_Transform.fPos.y - playerPos.y;
	directionVector.z = m_Transform.fPos.z - playerPos.z;

	// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
	direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
	// �����x�N�g�������]�s����v�Z
	m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);

	// �`���[�W�^�C�����I�������"�ˌ�"
	if (m_nFrame >= ASSAULT_CHARGE_TIME)
	{
		m_assaultDistancePlayer = distancePlayer;	// ����̋�����ۑ�
		m_assaultMovePos = movePos;					// �ړ��ʂ�ۑ�
		m_eState = ASSAULT;							// "�ˌ�"��Ԃ�
		m_nFrame = 0;								// �t���[�����Z�b�g
	}
}

/* ========================================
	�{�X��"�ˌ�"���s���֐�
	-------------------------------------
	���e�F�{�X���ˌ��U�����s������
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::Assault()
{
	if (m_assaultDistancePlayer != 0)	//0���Z���
	{
		m_fSpeed = ASSAULT_SPEED;	// �ˌ����̃X�s�[�h�ɕύX
		m_move.x = m_assaultMovePos.x / m_assaultDistancePlayer * m_fSpeed;
		m_move.z = m_assaultMovePos.z / m_assaultDistancePlayer * m_fSpeed;
	}

	// �ˌ����Ԃ��I��
	if (m_nFrame >= ASSAULT_TIME)
	{
		ResetAssault();	// �ˌ����Z�b�g
	}
}

/* ========================================
	"�ˌ�"�̃��Z�b�g���s���֐�
	-------------------------------------
	���e�F�ˌ������Z�b�g�������Ƃ��Ɉꊇ�ŌĂ�
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_Boss_1::ResetAssault()
{
	m_eState = NORMAL;	// "�m�[�}��"��Ԃ�
	SetNormalSpeed();	// �X�s�[�h��ʏ��Ԃɖ߂�
	m_nFrame = 0;		//�t���[�����Z�b�g
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
void CSlime_Boss_1::SetNormalSpeed()
{
	m_fSpeed = LEVEL_BOSS_1_SPEED;	//�ړ����x�ɒ萔���Z�b�g
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
void CSlime_Boss_1::SetMaxHp()
{
	m_nMaxHp = BOSS_1_MAX_HP;
}