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
	
========================================== */

// =============== �C���N���[�h ===================
#include "hammer.h"				// ���g�̃w�b�_
#include "Sphere.h"				// ���̂̏��p�w�b�_
#include "GameParameter.h"		// �萔��`�p�w�b�_�[


// =============== �萔��` =======================
const float HALF_PI = 3.141592f / 2;	//�n���}�[�̊J�n�n�_�̃��W�A���p(�v�C��)

const float HAMMER_ANGLE_X = DirectX::XMConvertToRadians(180.0f);	//�n���}�[�̕\���p�x
const float HAMMER_ANGLE_Y = DirectX::XMConvertToRadians(0.0f);		//�n���}�[�̕\���p�x
const float HAMMER_ANGLE_Z = DirectX::XMConvertToRadians(0.0f);		//�n���}�[�̕\���p�x
const float SWING_ANGLE = DirectX::XMConvertToRadians(90.0f);		//�n���}�[��U��͈�(��`�̊p�x�̑傫��)
#if MODE_GAME_PARAMETER
#else
const float SWING_TIME_FRAME = 0.15f * 60;						// �n���}�[��U�鎞��(�t���[���P��)
const float ROTATE_RADIUS = 1.0f;								// �n���}�[����]����v���C���[����̋���
const float HAMMER_COL_SIZE = 0.75f;							// �n���}�[�̓����蔻��̑傫��
const float HAMMER_SIZE = 1.5f;									// �n���}�[�̑傫��

const float SwingSpeed_INITIAL = 0.2f;									//�n���}�[�����Ԋu
const float SwingSpeed_PLUS = 3.2f;									//�n���}�[�����U��Ƃ��ɏ�Z�����l
const float SwingSpeed_MINUS = 0.97f;								//���t���[���n���}�[��U��Ԋu��Z��������l
const float SwingSpeed_SIOW = 50.0f;								//���t���[���n���}�[��U��Ԋu��Z��������l
#endif

const float ADJUST_DIRECTX_TO_COSINE = DirectX::XMConvertToRadians(90.0f);	// �O�p�֐���DirectX�p�x�̍���(DirectX�̊p�x�́���0�x�A�O�p�֐��́���0�x)
const float ONE_FRAME_ADD_ANGLE = SWING_ANGLE / SWING_TIME_FRAME;			// 1�t���[���ňړ�����p�x��

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
	, m_pCamera(nullptr)
	, m_fSwingSpeed(9.0f)
{
	m_fAddAngle = SWING_ANGLE / m_fSwingSpeed;
	m_Sphere.fRadius = HAMMER_COL_SIZE;
	m_Transform.fScale = HAMMER_SIZE;
	m_Transform.fRadian.x = HAMMER_ANGLE_X;
	m_Transform.fRadian.y = HAMMER_ANGLE_Y;
	m_Transform.fRadian.z = HAMMER_ANGLE_Z;

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
	if (m_dAddAngleCnt >= m_fSwingSpeed)
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
	if (!m_pCamera) { return; }

	if (m_pSphere)
	{
		DirectX::XMFLOAT4X4 mat;
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(3.0f, 3.0f, 3.0f) *
			DirectX::XMMatrixRotationY(m_Transform.fRadian.y) *
			DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));

		m_pSphere->SetWorld(mat);
		m_pSphere->SetView(m_pCamera->GetViewMatrix());
		m_pSphere->SetProjection(m_pCamera->GetProjectionMatrix());


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
		+ ADJUST_DIRECTX_TO_COSINE	// �{�O�p�֐���DirectX�p�x�̍���
		+ (SWING_ANGLE / 2);		// �{�n���}�[��U��p�x�̔���(��`�̉E�[����X�^�[�g�����)

	m_fAngleNow = StartAngle;	// �J�n�p�x���Z�b�g

	m_tPlayerPos = pPos;		// �v���C���[���W���Z�b�g

	// �p�x������W���擾(�v���C���[�̈ʒu�{�����{�v���C���[�̎���̉~��̈ʒu)
	m_Transform.fPos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);
	m_Transform.fPos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

}
/* ========================================
   �n���}�[�̃X�C���O�X�s�[�h��x������֐�
   ----------------------------------------
   ���e�F�n���}�[�̃X�C���O�X�s�[�h��x������
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::SwingSpeedAdd()
{
	m_fAddAngle = SWING_ANGLE / m_fSwingSpeed;
	m_fSwingSpeed*=SwingSpeed_PLUS; 
	if (m_fSwingSpeed >= SwingSpeed_SIOW)
	{
		m_fSwingSpeed = SwingSpeed_SIOW;
	}
	
}
/* ========================================
   �n���}�[�̃X�C���O�X�s�[�h�𑬂�����֐�
   ----------------------------------------
   ���e�F�n���}�[�̃X�C���O�X�s�[�h�𑬂�����
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::SwingSpeedSubtract()
{
	m_fSwingSpeed *= SwingSpeed_MINUS;
	if (m_fSwingSpeed <= SwingSpeed_MIN)
	{
		m_fSwingSpeed = SwingSpeed_MIN;
	}
	
}
/* ========================================
   �n���}�[�̊Ԋu�擾�֐�
   ----------------------------------------
   ���e�F�n���}�[�̊Ԋu�擾
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�n���}�[��U��Ԋu
   ======================================== */
float CHammer::GetInterval()
{
	return m_fSwingSpeed;
}


/* ========================================
   �J�����Z�b�g�֐�
   ----------------------------------------
   ���e�F�J�����̃|�C���^���Z�b�g
   ----------------------------------------
   ����1�F�J�����|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CHammer::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
