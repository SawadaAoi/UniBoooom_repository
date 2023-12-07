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
	�E2023/11/28 �U���̎d�l�ύX takagi
	�E2023/11/29 �U���̐V�d�l��S�U���ɔ��f�����t�@�N�^�����O�E�t���[���̃R�����g�Ȃ��̂͏���������\��̂��� takagi
	�E2023/11/30 Effekseer�p�Ɋ֐��ǉ� takagi
	�E2023/12/03 �ʒu�Q�b�^�쐬 takagi
	�E2023/12/04 GetViewWithoutTranspose,GetProjectionWithoutTranspose�̖߂�l��ύX yamashita
	�E2023/12/06 �Q�[���p�����[�^�Ή� takagi
	�E2023/12/07 �Q�[���p�����[�^����萔�ړ��E�s�v������ takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Camera.h"		//���g�̃w�b�_
#include "Defines.h"	//��ʏ��
#include "Random.h"		//���������p
#include <vector>		//�z��^�R���e�i

// =============== �񋓒�` =====================
enum E_DIRECT_VIBRATE
{
	E_DIRECT_VIBRATE_SIDE,		//������
	E_DIRECT_VIBRATE_VERTICAL,	//�c����
	E_DIRECT_VIBRATE_MAX,		//�v�f��
};	//�U������

// =============== �萔��` =====================
const float ASPECT = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;	//��ʔ䗦(y / x)
const TPos3d<float> INIT_LOOK(0.0f, 0.0f, 0.0f);					//���������n�_
const TTriType<float> INIT_UP_VECTOR(0.0f, 1.0f, 0.0f);				//�J�����̏����
const float INIT_CHANGE_RATE_AMPLITUDE = 1.0f;						//�����U���ω���
const TPos3d<float> INIT_POS(0.0f, 1.6f, -3.0f);					//�����ʒu
const float INIT_ANGLE = DirectX::XMConvertToRadians(73.0f);        //�J�����̊p�x
const float INIT_NEAR = 1.0f;										//��ʎ�O����z�l
const float INIT_FAR = 150.0f;										//��ʉ�����z�l
const float INIT_RADIUS = 15.0f;									//�J�����ƒ����_�Ƃ̋���(�����l)
const int MAX_CNT_CHANGE_VIBRATE = 10;								//�ő�U���ω���
const TDiType<int> INIT_FRAME_WEAK = { 125, 125 };					//��U���̃t���[����	x:��, y:�c
const TDiType<int> INIT_FRAME_STRONG = { 150, 150 };				//���U���̃t���[����	x:��, y:�c
const TDiType<float> CHANGE_RATE_AMPLITUDE_WEAK{ 0.99f, 0.99f };	//���U���ω���	1�𒴂���Ƒ��������A�����ƌ�������	x:��, y:�c
const TDiType<float> CHANGE_RATE_AMPLITUDE_STRONG{ 0.97f, 0.97f };	//���U���ω���	1�𒴂���Ƒ��������A�����ƌ�������	x:��, y:�c
///<summary>�U���̊m���F��
///<para>���v��1�ɂȂ�K�v�͂Ȃ�</para>
///</summary>
const std::vector<double> PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_MAX] = {
	{ 0.1, 0.3, 0.5, 0.3, 0.1 }, //����U��
	{ 0.1, 0.3, 0.5, 0.3, 0.1 }, //�c��U��
};
///<summary>
///<see cref="PROBABILITY_AMPITUDE_WEAK">����L�萔</see>�̃e�[�u��
///<para>���Ԃ����̂܂ܑΉ����Ă���A�������Ȃ��Ƌ@�\���Ȃ�(�Y��͎��R)</para>
///<para>�e�l�͐U���̑傫����\��</para>
///</summary>
const std::vector<float> TABLE_AMPITUDE_WEAK[E_DIRECT_VIBRATE_MAX] = {
	{ -0.05f, -0.025f, 0.0f, 0.025f, 0.05f },	//����U��
	{ -0.05f, -0.025f, 0.0f, 0.025f, 0.05f },	//�c��U��
};
///<summary>�U���̊m���F��
///<para>���v��1�ɂȂ�K�v�͂Ȃ�</para>
///</summary>
const std::vector<double> PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_MAX] = {
	{ 0.1, 0.3, 0.5, 0.3, 0.1 },	//�����U��
	{ 0.1, 0.3, 0.5, 0.3, 0.1 },	//�c���U��
};
///<summary>
///<see cref="PROBABILITY_AMPITUDE_STRONG">����L�萔</see>�̃e�[�u��
///<para>���Ԃ����̂܂ܑΉ����Ă���A�������Ȃ��Ƌ@�\���Ȃ�(�Y��͎��R)</para>
///<para>�e�l�͐U���̑傫����\��</para>
///</summary>
const std::vector<float> TABLE_AMPITUDE_STRONG[E_DIRECT_VIBRATE_MAX] = {
	{ -0.1f, -0.05f, 0.0f, 0.05f, 0.1f },	//�����U��
	{ -1.25f, -0.7f, 0.0f, 0.7f, 1.25f },	//�c���U��
};



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
	:m_ucFlag(0x00)												//�t���O
	, m_fPos(INIT_POS)											//�ʒu
	, m_fLook(INIT_LOOK)										//�����_
	, m_fUp(INIT_UP_VECTOR)										//����x�N�g��
	, m_fAngle(INIT_ANGLE)										//�p�x
	, m_fNear(INIT_NEAR)										//��ʎ�O
	, m_fFar(INIT_FAR)											//��ʉ�
	, m_fRadius(INIT_RADIUS)									//�����_�ƃJ�����̋���
	, m_fOffsetVibrateEye(0.0f)									//�J�����ʒu�U��
	, m_fOffsetVibrateLook(0.0f)								//�����_�U��
	, m_nFrameWeak(INIT_FRAME_WEAK)								//�t���[�����F��U��	x:��, y:�c
	, m_nFrameStrong(INIT_FRAME_STRONG)							//�t���[�����F���U��	x:��, y:�c
	, m_fChangeRateAmplitudeWeak(INIT_CHANGE_RATE_AMPLITUDE)	//�U���ϓ����F��		x:��, y:�c
	, m_fChangeRateAmplitudeStrong(INIT_CHANGE_RATE_AMPLITUDE)	//�U���ϓ����F��		x:��, y:�c
	, m_nCntChangeVibrate(0)									//�U���񐔃J�E���^
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
	DirectX::XMFLOAT4X4 Mat;

	// =============== �r���[�s��̌v�Z ===================
	DirectX::XMStoreFloat4x4(&Mat, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&GetViewWithoutTranspose())));	//�r���[�]�u

	// =============== �� ===================
	return Mat;	//�s���
}

/* ========================================
	�t�s��擾�֐�
	-------------------------------------
	���e�F�r���[�s��̋t�s����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�쐬�����s��
=========================================== */
DirectX::XMMATRIX CCamera::GetInverseViewMatrix() const
{
	// =============== �ϐ��錾 ===================
	DirectX::XMMATRIX Mat;			//�s��i�[�p
	DirectX::XMFLOAT4X4 pFlt44;	//�s��ҏW�p

	// =============== �r���[�s��̌v�Z ===================
	DirectX::XMFLOAT4X4 view = GetViewWithoutTranspose();
	Mat = DirectX::XMLoadFloat4x4(&view);	//�r���[�ϊ�

	// =============== �s��ҏW ===================
	DirectX::XMStoreFloat4x4(&pFlt44, Mat);				//�s��ҏW�p�ɕϊ�
	pFlt44._41 = pFlt44._42 = pFlt44._43 = 0.0f;		//�ړ��l�ŏ���
	Mat = DirectX::XMLoadFloat4x4(&pFlt44);				//�s��X�V

	// =============== �� ===================
	return DirectX::XMMatrixInverse(nullptr, Mat);	//�t�s��
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
	�]�u�����r���[�s��擾�֐�
	-------------------------------------
	���e�F�]�u���Ă��Ȃ��r���[�s����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�쐬�����s��
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetViewWithoutTranspose() const
{
	DirectX::XMFLOAT4X4 view;
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_fPos.x, m_fPos.y, m_fPos.z, 0.0f),		//�J�����ʒu
		DirectX::XMVectorSet(m_fLook.x, m_fLook.y, m_fLook.z, 0.0f),	//�����_
		DirectX::XMVectorSet(m_fUp.x, m_fUp.y, m_fUp.z, 0.0f)));			//�A�b�v�x�N�g��
	// =============== �� ===================
	return view;	//�r���[���W�n
}

/* ========================================
	�]�u�����v���W�F�N�V�����s��擾�֐�
	-------------------------------------
	���e�F�]�u���Ă��Ȃ��v���W�F�N�V�����s��(2D�Œ�)���
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�쐬�����s��
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetProjectionWithoutTranspose() const
{
	DirectX::XMFLOAT4X4 projection;
	DirectX::XMStoreFloat4x4(&projection, DirectX::XMMatrixPerspectiveFovLH(m_fAngle, ASPECT, m_fNear, m_fFar));
	// =============== �� ===================
	return projection;
}


/* ========================================
	�ʒu�Q�b�^�֐�
	-------------------------------------
	���e�F�J�����ʒu���
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F���݈ʒu
=========================================== */
TPos3d<float> CCamera::GetPos() const
{
	// =============== �� ===================
	return m_fPos;	//���g�̌��݈ʒu
}

/* ========================================
	�U���K�͕ύX�֐�
	-------------------------------------
	���e�F�U�����Ă��鎞�̂݁A�U���Ɋւ���ϐ��Ɋ���
	-------------------------------------
	����1�Fint nChangeFrame�F�U�����Ă���m_nFrame�ɑ��������B���̒l�Ȃ玝�����Ԃ����сA���Ȃ�k��
	����2�Ffloat fChangegRateAmp�F�U�����Ă���m_fChangeRateAmplitude�Ɋ|��������B���̒l�Ȃ玝�����Ԃ����сA���Ȃ�k��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCamera::ChangeScaleVibrate(int nChangeFrame, float fChangegRateAmp)	//TODO:�C�ӂ̐U���ɍi�����g��
{
	// =============== �U���t���O ===================
	if (m_nCntChangeVibrate > MAX_CNT_CHANGE_VIBRATE)
	{
		// =============== �I�� ===================
		return;	//�������f
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_WEAK)
	{
		// =============== �X�V ===================
		m_nFrameWeak.x += nChangeFrame;						//�t���[���J�E���^����
		m_fChangeRateAmplitudeWeak.x *= fChangegRateAmp;	//�␳������
		m_nCntChangeVibrate++;								//�U���񐔃J�E���g
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK)
	{
		// =============== �X�V ===================
		m_nFrameWeak.y += nChangeFrame;						//�t���[���J�E���^����
		m_fChangeRateAmplitudeWeak.y *= fChangegRateAmp;	//�␳������
		m_nCntChangeVibrate++;								//�U���񐔃J�E���g
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_STRONG)
	{
		// =============== �X�V ===================
		m_nFrameStrong.x += nChangeFrame;					//�t���[���J�E���^����
		m_fChangeRateAmplitudeStrong.x *= fChangegRateAmp;	//�␳������
		m_nCntChangeVibrate++;								//�U���񐔃J�E���g
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG)
	{
		// =============== �X�V ===================
		m_nFrameStrong.y += nChangeFrame;					//�t���[���J�E���^����
		m_fChangeRateAmplitudeStrong.y *= fChangegRateAmp;	//�␳������
		m_nCntChangeVibrate++;								//�U���񐔃J�E���g
	}
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
		//���������Ȃ�0�ɂȂ�Ȃ����ߗ��_�I�Ȗ����U�����\�I(���ۂɂ͌덷���x�̒l�ȉ��ɂȂ�Ǝ��F�ł��Ȃ��Ȃ�A���̂�����񗎂�����)
	if (!m_ucFlag)	//�����t���O����
	{
		// =============== ������ ===================
		m_nCntChangeVibrate = 0;	//�J�E���^������
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_WEAK)
	{
		// =============== ����U�� ===================
		if (m_nFrameWeak.x > 0)
		{
			// =============== �U�� ===================
			m_fOffsetVibrateEye.x = TABLE_AMPITUDE_WEAK[E_DIRECT_VIBRATE_SIDE][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_SIDE].begin(), PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_SIDE].end() }(CRandom::GetEngine())]	//�����_���ȐU��
				* m_fChangeRateAmplitudeWeak.x;											//�U���␳
				m_fOffsetVibrateLook.x = m_fOffsetVibrateEye.x + m_fOffsetVibrateEye.x;	//�����_�U��
				m_fChangeRateAmplitudeWeak.x *= CHANGE_RATE_AMPLITUDE_WEAK.x;			//�␳���ω�

				// =============== �J�E���^ ===================
				m_nFrameWeak.x--;	//�t���[���J�E���g
		}
		else
		{
			// =============== ������ ===================
			DownFlag(E_BIT_FLAG_VIBRATION_SIDE_WEAK);				//�t���O���~
			m_fOffsetVibrateEye.x = 0.0f;								//�J�����ʒu���ꏉ����
			m_fOffsetVibrateLook.x = 0.0f;								//�����_���ꏉ����
			m_fChangeRateAmplitudeWeak.x = INIT_CHANGE_RATE_AMPLITUDE;	//�U���␳������
			m_nFrameWeak.x = INIT_FRAME_WEAK.x;
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK)
	{
		// =============== �c��U�� ===================
		if (m_nFrameWeak.y > 0)
		{
			// =============== �U�� ===================
			m_fOffsetVibrateEye.y = TABLE_AMPITUDE_WEAK[E_DIRECT_VIBRATE_VERTICAL][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_VERTICAL].begin(), PROBABILITY_AMPITUDE_WEAK[E_DIRECT_VIBRATE_VERTICAL].end() }(CRandom::GetEngine())]	//�����_���ȐU��
				* m_fChangeRateAmplitudeWeak.y;											//�U���␳
				m_fOffsetVibrateLook.y = m_fOffsetVibrateEye.y + m_fOffsetVibrateEye.y;	//�����_�U��
				m_fChangeRateAmplitudeWeak.y *= CHANGE_RATE_AMPLITUDE_WEAK.y;			//�␳���ω�

				// =============== �J�E���^ ===================
				m_nFrameWeak.y--;	//�t���[���J�E���g
		}
		else
		{
			// =============== ������ ===================
			DownFlag(E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK);				//�t���O���~
			m_fOffsetVibrateEye.y = 0.0f;								//�J�����ʒu���ꏉ����
			m_fOffsetVibrateLook.y = 0.0f;								//�����_���ꏉ����
			m_fChangeRateAmplitudeWeak.y = INIT_CHANGE_RATE_AMPLITUDE;	//�U���␳������
			m_nFrameWeak.y = INIT_FRAME_WEAK.y;
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_SIDE_STRONG)
	{
		// =============== �����U�� ===================
		if (m_nFrameStrong.x > 0)
		{
			// =============== �U�� ===================
			m_fOffsetVibrateEye.x = TABLE_AMPITUDE_STRONG[E_DIRECT_VIBRATE_SIDE][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_SIDE].begin(), PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_SIDE].end() }(CRandom::GetEngine())]	//�����_���ȐU��
				* m_fChangeRateAmplitudeStrong.x;									//�U���␳
				m_fOffsetVibrateLook.x = m_fOffsetVibrateEye.x + m_fOffsetVibrateEye.x;	//�����_�U��
				m_fChangeRateAmplitudeStrong.x *= CHANGE_RATE_AMPLITUDE_STRONG.x;		//�␳���ω�

				// =============== �J�E���^ ===================
				m_nFrameStrong.x--;	//�t���[���J�E���g
		}
		else
		{
			// =============== ������ ===================
			DownFlag(E_BIT_FLAG_VIBRATION_SIDE_STRONG);					//�t���O���~
			m_fOffsetVibrateEye.x = 0.0f;									//�J�����ʒu���ꏉ����
			m_fOffsetVibrateLook.x = 0.0f;									//�����_���ꏉ����
			m_fChangeRateAmplitudeStrong.x = INIT_CHANGE_RATE_AMPLITUDE;	//�U���␳������
			m_nFrameStrong.x = INIT_FRAME_STRONG.x;
		}
	}
	if (m_ucFlag & E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG)
	{
		// =============== �c���U�� ===================
		if (m_nFrameStrong.y > 0)
		{
			// =============== �U�� ===================
			m_fOffsetVibrateEye.y = TABLE_AMPITUDE_STRONG[E_DIRECT_VIBRATE_VERTICAL][std::discrete_distribution<>{
				PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_VERTICAL].begin(), PROBABILITY_AMPITUDE_STRONG[E_DIRECT_VIBRATE_VERTICAL].end() }(CRandom::GetEngine())]	//�����_���ȐU��
				* m_fChangeRateAmplitudeStrong.y;									//�U���␳
				m_fOffsetVibrateLook.y = m_fOffsetVibrateEye.y + m_fOffsetVibrateEye.y;	//�����_�U��
				m_fChangeRateAmplitudeStrong.y *= CHANGE_RATE_AMPLITUDE_STRONG.y;		//�␳���ω�

				// =============== �J�E���^ ===================
				m_nFrameStrong.y--;	//�t���[���J�E���g
		}
		else
		{
			// =============== ������ ===================
			DownFlag(E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);					//�t���O���~
			m_fOffsetVibrateEye.y = 0.0f;									//�J�����ʒu���ꏉ����
			m_fOffsetVibrateLook.y = 0.0f;									//�����_���ꏉ����
			m_fChangeRateAmplitudeStrong.y = INIT_CHANGE_RATE_AMPLITUDE;	//�U���␳������
			m_nFrameStrong.y = INIT_FRAME_STRONG.y;
		}
	}
}