/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X���C���x�[�X �N���X����
	---------------------------------------
	SlimeBase.cpp
	
	�쐬�ҁF�鑺 ����
	
	�ύX����
	�E2023/11/04 �X���C���x�[�X�N���X�쐬 Suzumura
	�E2023/11/06 �n���}�[�������͓G�ɂ�萁����΂����֐���ǉ� Yamashita
	�E2023/11/06 �C���N���[�h�뎚�̏C�� Tei
	�E2023/11/08 GetPos��GetSphere�ɖ��O��ύX Yamashita
	�E2023/11/08 �萔��`���w�b�_�[�ɂ������̂�cpp�Ɉړ� Yamashita
	�E2023/11/08 �R�����g��ǉ� Sawada
	�E2023/11/09 �v���C���[�ǐՈړ��ύX Sawada
	�E2023/11/09 Update,NormalMove�̈����ύX Sawada
	�E2023/11/11 parameter�p�w�b�_�ǉ� Suzumura
	�E2023/11/12 �v���C���[�̕����������Ȃ���i�ނ悤�ɕύX  Yamamoto
	�E2023/11/12 �����_���ړ���ǉ�  Sawada
	�E2023/11/13 GetScale�֐���ǉ� Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/26 �X���C�����������瓦���鏈�����쐬�@yamashita
	�E2023/11/28 �U���͂�ǉ� Sawada
	�E2023/11/29 �e���������[�N���� takagi
	�E2023/11/30 ���f���̓ǂݍ��݂����]�����̂�radian.y�����΂ɂȂ�悤�ɕύX yamashita
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "SlimeBase.h"
#include "Geometry.h"
#include "GameParameter.h"		//�萔��`�p�w�b�_�[


// =============== �萔��` =======================
const float SLIME_BASE_RADIUS = 0.5f;			// �X���C���̊�̑傫��
const int	RANDOM_MOVE_SWITCH_TIME = 3 * 60;	// �����_���ړ��̕����؂�ւ�
const float SPEED_DOWN_RATIO = 0.6f;			// ������ԍۂɂ�����ړ����x�̕ω��̊���    RATIO=>����
const float REFLECT_RATIO = 0.1f;				//�X���C�����X���C���𐁂���΂����ۂɐ�����΂������̃X���C���̈ړ��ʂ�ς��銄��
const float MOVE_RESIST = 0.05f;				// ������шړ����̃X���C���̈ړ����x�ɖ��t���[�������錸�Z���l
#if MODE_GAME_PARAMETER
#else
const float MOVE_DISTANCE_PLAYER = 15;			// �v���C���[�ǐՈړ��ɐ؂�ւ��鋗��
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
CSlimeBase::CSlimeBase()
	: m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_move(0.0f, 0.0f, 0.0f)
	, m_fSpeed(ENEMY_MOVE_SPEED)
	, m_fVecAngle(0.0f)
	, m_bHitMove(false)
	, m_eSlimeSize(LEVEL_1)	//���SLIME_NONE�ɂ��� <=TODO
	, m_RanMoveCnt(RANDOM_MOVE_SWITCH_TIME)	// ����
	, m_ExpPos{ 0.0f,0.0f,0.0f }
	, m_bEscape(false)
	, m_nEscapeCnt(0)
	, m_fScaleShadow(0.0f)
	, m_fAnimeTime(0.0f)
	, m_eCurAnime(MOTION_LEVEL1_MOVE)
{
	m_Transform.fScale = (1.0f, 1.0f, 1.0f);
	//�����蔻��(����)������
	m_Sphere.fRadius = SLIME_BASE_RADIUS;

	int random = abs(rand() % 360);	//�����_����0�`359�̐������쐬
	m_Ry = DirectX::XMMatrixRotationY((float)random);

	m_pShadow = new CShadow();	// �e����

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
CSlimeBase::~CSlimeBase()
{
	// =============== �������J�� ===================
	SAFE_DELETE(m_pShadow);	//�e���
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
void CSlimeBase::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;	// �v���C���[�̍ŐV�p�����[�^���擾

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		if (!m_bEscape  && m_nEscapeCnt == 0)	//������t���O��off�Ȃ�
		{
			NormalMove();	//�ʏ�ړ�
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
	m_Transform.fPos.x += m_move.x * fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z * fSlimeMoveSpeed;
}

/* ========================================
	�`�揈���֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F�J����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CSlimeBase::Draw(const CCamera* pCamera)
{
	if (!m_pCamera) { return; }

	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();
	
	//-- �s����V�F�[�_�[�֐ݒ�
	m_pVS->WriteBuffer(0, mat);

	//-- ���f���\��
	if (m_pModel) {
		m_pModel->Draw();
	}

	//-- �e�̕`��
	m_pShadow->Draw(m_Transform, m_fScaleShadow, m_pCamera);
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
void CSlimeBase::NormalMove()
{
	TPos3d<float> playerPos = m_PlayerTran.fPos;

	// �G����G�l�~�[�̋����A�p�x���v�Z
	float distancePlayer	= m_Transform.fPos.Distance(playerPos);

	// �v���C���[�Ƌ��������ȓ���������
	if (distancePlayer < MOVE_DISTANCE_PLAYER) 
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
		directionVector.x = m_Transform.fPos.x-playerPos.x;
		directionVector.y = m_Transform.fPos.y-playerPos.y;
		directionVector.z = m_Transform.fPos.z-playerPos.z;

		// �x�N�g���𐳋K�����ĕ����x�N�g���𓾂�
		DirectX::XMVECTOR direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// �����x�N�g�������]�s����v�Z
		m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);
	}
	else
	{
		RandomMove();	// �����_���ړ�

	}

}

/* ========================================
	�����_���ړ��֐�
	----------------------------------------
	���e�F360�x�Ƀ����_���ړ����s��
	----------------------------------------
	����1�F����
	----------------------------------------
	�ߒl�F����
======================================== */
void CSlimeBase::RandomMove()
{
	m_RanMoveCnt++;		// �ړ������؂�ւ��Ԋu���ԉ��Z

	// �ړ������؂�ւ����Ԃ��o������
	if (m_RanMoveCnt >= RANDOM_MOVE_SWITCH_TIME)
	{
		int ranAngle = rand() % 360;	// �ړ���������

		// �p�x�����Ɉړ�����
		m_move.x = -cosf(DirectX::XMConvertToRadians((float)ranAngle)) * m_fSpeed;
		m_move.z = sinf(DirectX::XMConvertToRadians((float)ranAngle)) * m_fSpeed;

		// ������ς���
		m_Transform.fRadian.y = DirectX::XMConvertToRadians((float)ranAngle - 90);

		m_RanMoveCnt = 0;	// ���Z�l�����Z�b�g
	}


}

/* ========================================
	�n���}�[���G�ɐ�����΂���Ď��ۂɈړ��ʂ��m�肷��֐�
	----------------------------------------
	���e�FX������Z�����̈ړ��ʂ��m�肷�鏈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::HitMove()
{
	//�G�L�����̈ړ����x�ƈړ��p�x�ɉ�����X������Z�����̈ړ��ʂ����߂�
	m_move.x = cos(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);
	m_move.z = sin(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);

	m_fSpeed -= MOVE_RESIST;	//���t���[���̑��x�̌��Z����
	if (m_fSpeed <= 0)	//���x��0�ȉ��ɂȂ�����
	{
		m_bHitMove = false;				//������я�Ԃ̃t���O��OFF�ɂ���
		SetNormalSpeed();	// �p�������֐����g�p���đ傫�����Ƃ̃X�s�[�h���Z�b�g����
		m_RanMoveCnt = RANDOM_MOVE_SWITCH_TIME;
	}
}

/* ========================================
	�n���}�[���G�ɐ�����΂����֐�
	----------------------------------------
	���e�F�����ɉ����Ĕ�ԕ����ƈړ����x�����߂鏈��
	----------------------------------------
	����1�F���x
	����2�F�p�x
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::HitMoveStart(float speed, float angle)
{
	m_fSpeed = speed;		//�ړ��ʂ�����
	m_fVecAngle = angle;		//�ړ�����������
	m_bHitMove = true;		//������я�Ԃ�ON�ɂ���
}

/* ========================================
	�����֐�
	----------------------------------------
	���e�F�X���C���ɔ����̊�������Z���鏈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::Reflect()
{
	m_fSpeed *= REFLECT_RATIO;
}


/* ========================================
	�����֐�
	----------------------------------------
	���e�F�X���C�����������瓦����֐�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::Escape()
{
	//�����ւ̊p�x���擾
	float rad = atan2f(m_ExpPos.z - m_Transform.fPos.z, m_ExpPos.x - m_Transform.fPos.x);	
	//�����Ɣ��Ε����Ɉړ�
	m_move.x = 0.0f;//-(cosf(rad)) * ENEMY_MOVE_SPEED;
	m_move.z = 0.0f;//-(sinf(rad)) * ENEMY_MOVE_SPEED;
	m_Transform.fRadian.y = atan2f(m_move.x,m_move.z);

	m_nEscapeCnt++;	//�J�E���g�𑝉�
	if (m_nEscapeCnt > ESCAPE_TIME) 
	{ 
		m_bEscape = false; 
		m_nEscapeCnt = 0;
	}
}

/* ========================================
	�J�������Z�b�g�֐�
	----------------------------------------
	���e�F�`�揈���Ŏg�p����J�������Z�b�g
	----------------------------------------
	����1�F�J�����̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	�������W�Z�b�g�֐�
	----------------------------------------
	���e�F�����̍��W���Z�b�g����
	----------------------------------------
	����1�F�����̍��W
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::SetExplosionPos(TPos3d<float> expPos)
{
	m_ExpPos = expPos;
}

/* ========================================
	������ԃZ�b�g�֐�
	----------------------------------------
	���e�F�X���C���������邩�����łȂ����̏�Ԃ��Z�b�g����
	----------------------------------------
	����1�F�X���C�����������邩�ǂ���
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::SetEscapeFlag(bool bEscape)
{
	m_bEscape = bEscape;
}

/* ========================================
	�X���C�����x���擾�֐�
	----------------------------------------
	���e�F�X���C���̃��x����Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�X���C���̃��x��
======================================== */
E_SLIME_LEVEL CSlimeBase::GetSlimeLevel()
{
	return m_eSlimeSize;
}

/* ========================================
	�����ԃt���O�擾�֐�
	----------------------------------------
	���e�F�����ԃt���O��Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�����ԃt���O
======================================== */
bool CSlimeBase::GetHitMoveFlg()
{
	return m_bHitMove;
}

/* ========================================
	���W�擾�֐�
	----------------------------------------
	���e�F�X���C���̍��W���擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�X���C���̍��W
======================================== */
TPos3d<float> CSlimeBase::GetPos()
{
	return m_Transform.fPos;
}

/* ========================================
	������Ԏ擾�֐�
	----------------------------------------
	���e�F�������瓦���Ă��邩�̊m�F
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Fbool
======================================== */
bool CSlimeBase::GetEscapeFlag()
{
	return m_bEscape = false;
}

/* ========================================
	�U���͎擾�֐�
	----------------------------------------
	���e�F�U���͂��擾����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�U����
======================================== */
int CSlimeBase::GetAttack()
{
	return m_nAttack;
}

/* ========================================
	�ړ����x�擾�֐�
	----------------------------------------
	���e�F�X���C���̈ړ����x��Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�X���C���̈ړ����x
======================================== */
float CSlimeBase::GetSpeed()
{
	return m_fSpeed;
}








