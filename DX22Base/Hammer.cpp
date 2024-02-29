/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Hammer�pcpp
	------------------------------------
	Hammer.cpp
	------------------------------------
	�쐬��
		�R�{�M��
	�ύX����
	�E2023/11/08 �R�����g�ǉ� yamashita
	�E2023/11/08 �ł������̕ϐ��̓����o�C�j�V�����C�U�ŏ����� yamashita
	�E2023/11/08 �萔HALF_PI�AANGULAR_ANGLE�AROTATE_RADIUS���` yamashita
	�E2023/11/08 Update�ɏ�����Ă���������Swing�֐��ɕ������@yamashita
	�E2023/11/08 ���I�m�ۂ����|�C���^��delete����SAFE_DELETE�ɕύX�@yamashita
	�E2023/11/09 �����蔻��p��Sphere�̃Q�b�g�֐���ǉ� yamashita
	�E2023/11/11 parameter�p�w�b�_�ǉ� suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/14 �S�̓I�ɏ����̗��ꂪ������Â炩�����̂ŏC�� Sawada
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/23 �W�I���g���[���烂�f���ɍ����ւ��@yamashita
	�E2023/11/29 Interval�ǉ��@yamamoto
	�E2023/12/01 Interval��SwingSpeed�ɕύX�@yamamoto
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2024/02/08 �U�鑬�x�̑����ɂ��ď������C�� sawada
	�E2024/02/09 UsingCamera�g�p takagi

========================================== */

// =============== �C���N���[�h ===================
#include "hammer.h"				// ���g�̃w�b�_
#include "Sphere.h"				// ���̂̏��p�w�b�_
#include "GameParameter.h"		// �萔��`�p�w�b�_�[
#include "TriType.h"
#include "UsingCamera.h"		//�J�����g�p

// =============== �萔��` =======================
const float HALF_PI = 3.141592f / 2;	//�n���}�[�̊J�n�n�_�̃��W�A���p(�v�C��)

const TTriType<float> HAMMER_DISP_ANGLE = {	// �n���}�[�̕\���p�x
	DirectX::XMConvertToRadians(180.0f),
	DirectX::XMConvertToRadians(0.0f) ,
	DirectX::XMConvertToRadians(0.0f) };

const float SWING_ANGLE = DirectX::XMConvertToRadians(130.0f);		//�n���}�[��U��͈�(��`�̊p�x�̑傫��)
#if MODE_GAME_PARAMETER
#else
const float SWING_TIME_FRAME = 0.15f * 60;						// �n���}�[��U�鎞��(�t���[���P��)
const float ROTATE_RADIUS = 1.0f;								// �n���}�[����]����v���C���[����̋���
const float HAMMER_COL_SIZE = 0.75f;							// �n���}�[�̓����蔻��̑傫��
const float HAMMER_SIZE = 1.5f;									// �n���}�[�̑傫��

const float SwingSpeed_INITIAL = 0.2f;									//�n���}�[�����Ԋu
const float SWING_TIME_ADD_MULT = 3.2f;									//�n���}�[�����U��Ƃ��ɏ�Z�����l
const float SWING_TIME_MINUS_MULT = 0.97f;								//���t���[���n���}�[��U��Ԋu��Z��������l
const float SWING_TIME_MAX = 50.0f;								//���t���[���n���}�[��U��Ԋu��Z��������l
#endif

const float ADJUST_DIRECTX_TO_COSINE = DirectX::XMConvertToRadians(90.0f);	// �O�p�֐���DirectX�p�x�̍���(DirectX�̊p�x�́���0�x�A�O�p�֐��́���0�x)
const float FIRST_ADD_ANGLE = SWING_ANGLE / SWING_TIME_MIN;

/* ========================================
   �R���X�g���N�^�֐�
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CHammer::CHammer()
	: m_tPlayerPos(0.0f,0.0f,0.0f)
	, m_fAngleNow(0)
	, m_dAddAngleCnt(0)
	, m_nSwingTimeFrame(SWING_TIME_MIN)
	, m_fSwingSpeed(1.0f)
{
	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1�t���[���̉��Z�p�x���v�Z

	m_Sphere.fRadius	= HAMMER_COL_SIZE;
	m_Transform.fScale	= HAMMER_SIZE;
	m_Transform.fRadian = HAMMER_DISP_ANGLE;

	m_fSwingSpeed = m_nSwingTimeFrame / SWING_TIME_MIN;

	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pSphere = new CSphere();
}

/* ========================================
   �f�X�g���N�^�֐�
   ----------------------------------------
   ���e�F�j�����ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CHammer::~CHammer()
{
	SAFE_DELETE(m_pSphere);

	SAFE_DELETE(m_pVS);
}

/* ========================================
   �X�V�֐�
   ----------------------------------------
   ���e�F�X�V���s��
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�n���}�[�̗L������
   ======================================== */
bool CHammer::Update()
{
	Swing();		//��]�ɂ��ړ��֐�

	// �ݒ�l�܂ňړ�����������
	if (m_nSwingTimeFrame <= m_dAddAngleCnt  )
	{
		m_dAddAngleCnt = 0;		// �p�x�ύX�t���[���J�E���g���Z�b�g
		
		return false;
	}
	// �ړ�����true��Ԃ�
	else
	{
		return true;
	}
}

/* ========================================
   �`��֐�
   ----------------------------------------
   ���e�F�`����s��
   ----------------------------------------
   �����FCamera�N���X�̃|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::Draw()
{
	if (m_pSphere)
	{
		DirectX::XMFLOAT4X4 mat;
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(3.0f, 3.0f, 3.0f) *
			DirectX::XMMatrixRotationY(m_Transform.fRadian.y) *
			DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));

		m_pSphere->SetWorld(mat);
		m_pSphere->SetView(CUsingCamera::GetThis().GetCamera()->GetViewMatrix());
		m_pSphere->SetProjection(CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix());


		// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
		RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
		DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
		SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

		m_pSphere->Draw();
	}
}

/* ========================================
   �n���}�[��]�֐�
   ----------------------------------------
   ���e�F�n���}�[�̉�]�ɂ��ړ��̏���
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::Swing()
{
	m_fAngleNow -= m_fAddAngle;	// �n���}�[�����蔻��p�x�ړ�		

	// �p�x������W���擾(�v���C���[�̈ʒu�{�����{�v���C���[�̎���̉~��̈ʒu)
	m_Transform.fPos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);	// �O�p�֐�(�����v���)��DirectX(���v���)�̊p�x�̌������t�Ȃ̂Ŕ��]����
	m_Transform.fPos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

	m_Transform.fRadian.y = m_fAngleNow - DirectX::XMConvertToRadians(90.0f);

	m_dAddAngleCnt++;	// �p�x�ύX�t���[���J�E���g���Z

}
/* ========================================
   �n���}�[�̉�]�֐�
   ----------------------------------------
   ���e�F�U���������J�n����
   ----------------------------------------
   ����1�F�v���C���[���W
   ����2�F�v���C���[�̌���
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::AttackStart(TPos3d<float>pPos, float angle)
{
	float StartAngle =
		  angle						// �v���C���[�̌���
		+ DirectX::XMConvertToRadians(180.0f)
		+ ADJUST_DIRECTX_TO_COSINE	// �{�O�p�֐���DirectX�p�x�̍���
		+ (SWING_ANGLE / 2);		// �{�n���}�[��U��p�x�̔���(��`�̉E�[����X�^�[�g�����)

	m_fAngleNow = StartAngle;	// �J�n�p�x���Z�b�g

	m_tPlayerPos = pPos;		// �v���C���[���W���Z�b�g

	// �p�x������W���擾(�v���C���[�̈ʒu�{�����{�v���C���[�̎���̉~��̈ʒu)
	m_Transform.fPos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);
	m_Transform.fPos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

}
/* ========================================
   �n���}�[�X�C���O�X�s�[�h�x���֐�
   ----------------------------------------
   ���e�F�n���}�[�̃X�C���O�X�s�[�h��x������
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::SwingSpeedSlow()
{
	m_nSwingTimeFrame = m_nSwingTimeFrame * SWING_TIME_ADD_MULT;	// ��U��Ɋ|���鎞�Ԃ𑝂₷

	// �U�鎞�Ԃ��ő�l�𒴂����ꍇ
	if (SWING_TIME_MAX <= m_nSwingTimeFrame)
	{
		m_nSwingTimeFrame = SWING_TIME_MAX;
	}


	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1�t���[���̉��Z�p�x���v�Z
	m_fSwingSpeed = m_fAddAngle / FIRST_ADD_ANGLE;			// ���݂̃n���}�[�̈�U��̑��x�v�Z
}

/* ========================================
   �`���[�W�n���}�[�X�C���O�X�s�[�h�x���֐�
   ----------------------------------------
   ���e�F�`���[�W�n���}�[���̃X�C���O�X�s�[�h��x������
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::SwingSpeedSlow_Charge()
{

	m_nSwingTimeFrame = m_nSwingTimeFrame * SWING_TIME_ADD_MULT_CHARGE;	// ��U��Ɋ|���鎞�Ԃ𑝂₷

	// �U�鎞�Ԃ��ő�l�𒴂����ꍇ
	if (SWING_TIME_MAX <= m_nSwingTimeFrame)
	{
		m_nSwingTimeFrame = SWING_TIME_MAX;
	}

	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1�t���[���̉��Z�p�x���v�Z
	m_fSwingSpeed = m_fAddAngle / FIRST_ADD_ANGLE;			// ���݂̃n���}�[�̈�U��̑��x�v�Z
}
/* ========================================
   �n���}�[�̃X�C���O�X�s�[�h�����֐�
   ----------------------------------------
   ���e�F�n���}�[�̃X�C���O�X�s�[�h�𑬂�����
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::SwingSpeedFast()
{
	m_nSwingTimeFrame = m_nSwingTimeFrame * SWING_TIME_MINUS_MULT;	// ��U��Ɋ|���鎞�Ԃ����炷

	// �U�鎞�Ԃ��ŏ��l����������ꍇ
	if (m_nSwingTimeFrame <= SWING_TIME_MIN)
	{
		m_nSwingTimeFrame = SWING_TIME_MIN;
	}


	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1�t���[���̉��Z�p�x���v�Z
	m_fSwingSpeed = m_fAddAngle / FIRST_ADD_ANGLE;			// ���݂̃n���}�[�̈�U��̑��x�v�Z
}

/* ========================================
   �n���}�[���x�擾�֐�
   ----------------------------------------
   ���e�F�n���}�[�̑��x���擾
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�n���}�[�𑬓x(�����l��1.0)
   ======================================== */
float CHammer::GetSwingSpeed()
{
	return m_fSwingSpeed;
}