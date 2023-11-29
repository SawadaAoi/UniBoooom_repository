/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�J�����p���ۃN���X����
	------------------------------------
	Camera.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/24 ������ takagi
	�E2023/11/02 �����o�[�ϐ��ǉ� takagi
	�E2023/11/04 �X�V�֐��̎��������폜 takagi
	�E2023/11/06 �t���O�����E�R�����g�C�� takagi
	�E2023/11/07 GetViewMatrix()�֐���const�C���q�t�^�E�R�����g�C�� takagi
	�E2023/11/09 �J�����̗l�X����`�F�b�N�B takagi
	�E2023/11/10 �p�����^�C�� takagi
	�E2023/11/11 define�p�w�b�_�ǉ� suzumura
	�E2023/11/17 2D�\��/3D�\���̐؊����R���X�g���N�^�łȂ�GetProjectionMatrix()�֐��ōs���悤�ɕύX�E�U���@�\�ǉ� takagi
	�E2023/11/18 2D�\���̃~�X����� takagi
	�E2023/11/24 �萔�l�C���E�t���O�o�O�C���E�ꕔ�R�����g�ڍ׉� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Camera.h"		//���g�̃w�b�_
#include "Defines.h"	//��ʏ��
#include "GameParameter.h"

// =============== �萔��` =====================
const float ASPECT = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;	//��ʔ䗦(y / x)
const TPos3d<float> INIT_LOOK(0.0f, 0.0f, 0.0f);					//���������n�_
const TTriType<float> INIT_UP_VECTOR(0.0f, 1.0f, 0.0f);				//�J�����̏����
#if MODE_GAME_PARAMETER
#else
const TPos3d<float> INIT_POS(0.0f, 1.6f, -3.0f);					//�����ʒu

const float Pi = 3.141592f;
constexpr float ANGLE_TO_RADIAN(float fAngle)
{
	return fAngle / 180.0f * Pi;	//�p�x�����W�A���p
}

const float INIT_ANGLE = DirectX::XMConvertToRadians(73.0f);        //�J�����̊p�x
const float INIT_NEAR = 1.0f;										//��ʎ�O����z�l
const float INIT_FAR = 150.0f;										//��ʉ�����z�l
const float INIT_RADIUS = 15.0f;									//�J�����ƒ����_�Ƃ̋���(�����l)

const float RADIAN_VELOCITY_WEAK = ANGLE_TO_RADIAN(1.5f);		//�p���x�F��
const float RADIAN_VELOCITY_STRONG = ANGLE_TO_RADIAN(1.0f);		//�p���x�F��
const TDiType<float> AMPLITUDE_WEAK(3.0f, 0.7f);				//�U���F��			x:�c, y:��
const TDiType<float> AMPLITUDE_STRONG(10.0f, 50.0f);			//�U���F��			x:�c, y:��
const TDiType<float> VIRTUAL_FRICTION(0.5f);					//�^�����C��
const TDiType<float> VIRTUAL_GRAVITY(0.5f);						//�^���d��
const TDiType<float> DECREASE_RADIAN_WEAK(0.005f, 0.005f);		//�p���x�����ʁF��	x:�c, y:��
const TDiType<float> DECREASE_RADIAN_STRONG(0.005f, 0.008f);	//�p���x�����ʁF��	x:�c, y:��
#endif



/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCamera::CCamera()
	:m_ucFlag(0)								//�t���O
	,m_fPos(INIT_POS)							//�ʒu
	,m_fLook(INIT_LOOK)							//�����_
	,m_fUp(INIT_UP_VECTOR)						//����x�N�g��
	,m_fAngle(INIT_ANGLE)						//�p�x
	,m_fNear(INIT_NEAR)							//��ʎ�O
	,m_fFar(INIT_FAR)							//��ʉ�
	,m_fRadius(INIT_RADIUS)						//�����_�ƃJ�����̋���
	,m_fOffsetVibrateEye(0.0f)					//�J�����ʒu�U��
	,m_fOffsetVibrateLook(0.0f)					//�����_�U��
	,m_fRadianVelocityWeak(0.0f)				//�~�ϊp���x�F��
	,m_fRadianVelocityStrong(0.0f)				//�~�ϊp���x�F��
	,m_fAddRadianWeak(RADIAN_VELOCITY_WEAK)		//�p���x�����ʁF��
	,m_fAddRadianStrong(RADIAN_VELOCITY_STRONG)	//�p���x�����ʁF��
{
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCamera::~CCamera()
{
}

/* ========================================
	�t���O�I���֐�
	-------------------------------------
	���e�F�����ŗ����Ă���t���O�𗧂Ă�
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCamera::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag |= ucBitFlag;	//�t���O����
}

/* ========================================
	�t���O�I�t�֐�
	-------------------------------------
	���e�F�����ŗ����Ă���t���O���~�낷
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCamera::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag &= (ucBitFlag ^ 0xFF);	//�t���O����
}

/* ========================================
	�t���O�Z�b�^�֐�
	-------------------------------------
	���e�F�����ŗ����Ă���t���O���t�]������
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCamera::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag ^= ucBitFlag;	//�t���O����
}

/* ========================================
	�r���[�s��擾�֐�
	-------------------------------------
	���e�F�J�����̃r���[�s����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�쐬�����s��
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetViewMatrix() const
{
	// =============== �ϐ��錾 ===================
	DirectX::XMFLOAT4X4 mat;

	// =============== �r���[�s��̌v�Z ===================
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_fPos.x, m_fPos.y, m_fPos.z, 0.0f),		//�J�����ʒu
			DirectX::XMVectorSet(m_fLook.x, m_fLook.y, m_fLook.z, 0.0f),	//�����_
			DirectX::XMVectorSet(m_fUp.x, m_fUp.y, m_fUp.z, 0.0f)))			//�A�b�v�x�N�g��
	);	//�r���[�ϊ�

	// =============== �� ===================
	return mat;	//�s���
}

/* ========================================
	�v���W�F�N�V�����s��擾�֐�
	-------------------------------------
	���e�F�J�����̃v���W�F�N�V�����s����
	-------------------------------------
	����1�Fconst E_DRAW_TYPE& eDraw�F2D�\����3D�\����
	-------------------------------------
	�ߒl�F�쐬�����s��
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetProjectionMatrix(const E_DRAW_TYPE& eDraw) const
{
	// =============== �ϐ��錾 ===================
	DirectX::XMFLOAT4X4 mat;	//�s��i�[�p

	// =============== �v���W�F�N�V�����s��̌v�Z ===================
	switch (eDraw)	//���e�I��
	{
		// =============== 2D�\�� ===================
	case E_DRAW_TYPE_2D:	//2D�̃v���W�F�N�V�������W�쐬
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, m_fNear, m_fFar)));	//���������_(0,0)�Ƃ������W�n
		break;	//���򏈗��I��

    // =============== 3D�\�� ===================
	case E_DRAW_TYPE_3D:	//3D�̃v���W�F�N�V�������W�쐬
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixPerspectiveFovLH(m_fAngle, ASPECT, m_fNear, m_fFar)));	//3D�v���W�F�N�V�����ϊ�
		break;	//���򏈗��I��
	}

	// =============== �� ===================
	return mat;	//�s���
}

/* ========================================
	�t���O�ʏ����֐�
	-------------------------------------
	���e�F�t���O�ɂ���Ĕ��f�����e���������s����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCamera::HandleFlag()
{
	// =============== �U���t���O ===================
			//�[�P�U���̓�����������ۂ����ȂƎv�����̂ō̗p���Ă݂�[
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_WEAK)
	{
		// =============== �U�� ===================
		m_fAddRadianWeak.x -= DECREASE_RADIAN_WEAK.x;								//�p���x�����ʍX�V
		if (m_fAddRadianWeak.x >= 0.0f)
		{
			m_fRadianVelocityWeak.x += m_fAddRadianWeak.x;							//�p���x�X�V
			m_fOffsetVibrateEye.x = AMPLITUDE_WEAK.x * sinf(m_fRadianVelocityWeak.x);	//�P�U��
			m_fOffsetVibrateLook.x = m_fOffsetVibrateEye.x;	//�����_�U��
		}
		else
		{
			DownFlag(E_BIT_FLAG_VIBRATION_SIDE_WEAK);		//�t���O���~
			m_fAddRadianWeak.x = RADIAN_VELOCITY_WEAK;		//�p���x�����ʏ�����
			m_fRadianVelocityWeak.x = 0.0f;					//�p���x������
			m_fOffsetVibrateEye.x = 0.0f;					//������
			m_fOffsetVibrateLook.x = 0.0f;					//������
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK)
	{
		// =============== �U�� ===================
		m_fAddRadianWeak.y -= DECREASE_RADIAN_WEAK.y;									//�p���x�����ʍX�V
		if (m_fAddRadianWeak.y >= 0.0f)
		{
			m_fRadianVelocityWeak.y += m_fAddRadianWeak.y;								//�p���x�X�V
			m_fOffsetVibrateEye.y = AMPLITUDE_WEAK.y * sinf(m_fRadianVelocityWeak.y);	//�P�U��
			m_fOffsetVibrateLook.y = m_fOffsetVibrateEye.y + m_fOffsetVibrateEye.y;		//�����_�U��
		}
		else
		{
			DownFlag(E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK);	//�t���O���~
			m_fAddRadianWeak.y = RADIAN_VELOCITY_WEAK;		//�p���x�����ʏ�����
			m_fRadianVelocityWeak.y = 0.0f;					//�p���x������
			m_fOffsetVibrateEye.y = 0.0f;					//������
			m_fOffsetVibrateLook.y = 0.0f;					//������
		}
	}	
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_STRONG)
	{
		// =============== �U�� ===================
		m_fAddRadianStrong.x -= DECREASE_RADIAN_STRONG.x;									//�p���x�����ʍX�V
		if (m_fAddRadianStrong.x >= 0.0f)
		{
			m_fRadianVelocityStrong.x += m_fAddRadianStrong.x;								//�p���x�X�V
			m_fOffsetVibrateEye.x = AMPLITUDE_STRONG.x * sinf(m_fRadianVelocityStrong.x);	//�P�U��
			m_fOffsetVibrateLook.x = m_fOffsetVibrateEye.x;			//�����_�U��
		}
		else
		{
			DownFlag(E_BIT_FLAG_VIBRATION_SIDE_STRONG);			//�t���O���~
			m_fAddRadianStrong.x = RADIAN_VELOCITY_STRONG;		//�p���x�����ʏ�����
			m_fRadianVelocityStrong.x = 0.0f;					//�p���x������
			m_fOffsetVibrateEye.x = 0.0f;						//������
			m_fOffsetVibrateLook.x = 0.0f;						//������
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG)
	{
		// =============== �U�� ===================
		m_fAddRadianStrong.y -= DECREASE_RADIAN_STRONG.y;								//�p���x�����ʍX�V
		if (m_fAddRadianStrong.y >= 0.0f)
		{
			m_fRadianVelocityStrong.y += m_fAddRadianWeak.y;							//�p���x�X�V
			m_fOffsetVibrateEye.y = AMPLITUDE_WEAK.y * sinf(m_fRadianVelocityStrong.y);	//�P�U��
			m_fOffsetVibrateLook.y = m_fOffsetVibrateEye.y + m_fOffsetVibrateEye.y;		//�����_�U��
		}
		else
		{
			DownFlag(E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);		//�t���O���~
			m_fAddRadianStrong.y = RADIAN_VELOCITY_STRONG;		//�p���x�����ʏ�����
			m_fRadianVelocityStrong.y = 0.0f;					//�p���x������
			m_fOffsetVibrateEye.y = 0.0f;						//������
			m_fOffsetVibrateLook.y = 0.0f;						//������
		}
	}
}