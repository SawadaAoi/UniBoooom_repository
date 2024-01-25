/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X���C���T�C�Y3�pcpp
	------------------------------------
	Slime_3.cpp
	------------------------------------
	�쐬��	�R�����C

	�ύX����
	�E2023/11/08 �쐬 yamashita
	�E2023/11/08 �傫���̒萔���`	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �X���C���̈ړ����x��傫�����ƂɕύX����֐����쐬	yamashita
	�E2023/11/08 �R���X�g���N�^�Ń��x�����Ƃ̃p�����[�^���Z�b�g	yamashita
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	�E2023/11/14 Base���烂�f���A�V�F�[�_�̓ǂݍ��݂��ړ� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� takagi
	�E2023/11/15 �X���C���̃��f���ƒ��_�V�F�[�_�[��manager����󂯎��悤�ɕύX yamashita
	�E2023/11/16 �����t���R���X�g���N�^�̈����ɒ��_�V�F�[�_�[�ƃ��f���̃|�C���^��ǉ� �R�����C
	�E2023/11/28 �e�̑傫����ݒ肷��ϐ��ǉ� nieda
	�E2023/11/30 �v���C���[�Ɍ����Ă�����~�܂鏈����ǉ� yamashita
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Slime_3.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "DirectWrite.h"
// =============== �萔��` =======================
const int	LEVEL3_ATTACK = 1;						// �U����
#if MODE_GAME_PARAMETER
#else
const float LEVEL3_SCALE = 3.0f;
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.90;
const float LEVEL3_STOP_RANGE = DirectX::XMConvertToRadians(20.0f);	// �X���C�����~�܂�p�x�͈̔�
#endif
const float LEVEL_3_SHADOW_SCALE = 3.5f;	// �X���C���Q���x���R�̉e�̑傫��

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSlime_3::CSlime_3()
{
	m_Transform.fScale = { LEVEL3_SCALE,LEVEL3_SCALE ,LEVEL3_SCALE };
	m_Sphere.fRadius *= LEVEL3_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_3;
	SetNormalSpeed();
	m_nAttack = LEVEL3_ATTACK;
	m_fScaleShadow = LEVEL_3_SHADOW_SCALE;	// �e�̑傫����ݒ�
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
CSlime_3::CSlime_3(TPos3d<float> pos, VertexShader* pVS, AnimeModel* pModel)
	: CSlime_3()
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
CSlime_3::~CSlime_3()
{
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�v���C���[��transform
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlime_3::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//������t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ٓ�
		}
		else
		{
			MoveStop();	//�������瓦����
		}
	}
	else
	{
		//�G�̐�����шړ�
		HitMove();
	}

	// -- ���W�X�V
	m_Transform.fPos.x += m_move.x * fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z * fSlimeMoveSpeed;
}

/* ========================================
	�ʏ�ړ��֐�
	----------------------------------------
	���e�F�v���C���[��ǐՂ���ړ����s��
		  �v���C���[�Ɍ����Ă�����~�܂�
	----------------------------------------
	����1�F�v���C���[��transform
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlime_3::NormalMove()
{

	TPos3d<float> playerPos = m_PlayerTran.fPos;
	TTriType<float> playerRad = m_PlayerTran.fRadian;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// �v���C���[�Ƌ��������ȓ���������
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		//�v���C���[���X���C���̕����������Ă��邩�m�F
	 	float PlayerToSlimeRad = m_PlayerTran.Angle(m_Transform);	//�v���C���[����X���C���ւ̊p�x
		if (PlayerToSlimeRad < 0.0f) { PlayerToSlimeRad = PlayerToSlimeRad + (DirectX::g_XMTwoPi[0]); }			//�p�x�𐳂̐��ɕϊ�
		float adjustPlayerRad = playerRad.y + DirectX::XMConvertToRadians(90.0f);			//�v���C���[�̌��Ă���p�x
		if(adjustPlayerRad < 0.0f){adjustPlayerRad = adjustPlayerRad + (DirectX::g_XMTwoPi[0]);}	//�p�x�𐳂̐��ɕϊ�
		float sumRad = PlayerToSlimeRad + adjustPlayerRad;
		//�v���C���[�̌����Ă���������X���C���̎~�܂�p�x�̒���������
		float checkRad = (abs(sumRad - (DirectX::g_XMTwoPi[0]))) > DirectX::g_XMTwoPi[0] ?
			(abs(sumRad - (DirectX::g_XMTwoPi[0]))) - DirectX::g_XMTwoPi[0] :
			(abs(sumRad - (DirectX::g_XMTwoPi[0])));
		if (checkRad < LEVEL3_STOP_RANGE)
		{
			m_move = TTriType<float>(0.0f, 0.0f, 0.0f);	//�ړ��ʂ�0�ɂ���
			m_Transform.fRadian.y = -(m_Transform.Angle(m_PlayerTran) - DirectX::XMConvertToRadians(90.0f));	//�p�x��DirectX�p�ɕύX
			return;
		}
		else	//�v���C���[���X���C���ƕʂ̕����������Ă�����
		{
			TPos3d<float> movePos;
			movePos = playerPos - m_Transform.fPos;	// �v���C���[�ւ̃x�N�g�����v�Z
			if (distancePlayer != 0)	//0���Z���
			{
				m_move.x = movePos.x / distancePlayer * m_fSpeed;
				m_move.z = movePos.z / distancePlayer * m_fSpeed;
			}
			// �G����v���C���[�ւ̃x�N�g��
			DirectX::XMFLOAT3 directionVector;
			directionVector.x = m_Transform.fPos.x - playerPos.x;
			directionVector.y = m_Transform.fPos.y - playerPos.y;
			directionVector.z = m_Transform.fPos.z - playerPos.z;

			// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
			DirectX::XMVECTOR direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
			// �����x�N�g�������]�s����v�Z
			m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);
		}
	}
	else	//���G�͈͊O��������
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
void CSlime_3::SetNormalSpeed()
{
	m_fSpeed = LEVEL3_SPEED;	//�ړ����x�ɒ萔���Z�b�g
}


