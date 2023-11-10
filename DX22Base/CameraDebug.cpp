/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�f�o�b�O�p�J��������
	------------------------------------
	CameraDebug.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/04 ���� takagi
	�E2023/11/06 �R�[�f�B���O�K��K�p�E�ǐՑΏۓo�^�@�\�쐬 takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/10 �ϐ��ǉ� takagi

========================================== */



// =============== �C���N���[�h ===================
#include "CameraDebug.h"	//���g�̃w�b�_
#include "Input.h"			//���͎�t

// =============== �萔��` ===================
const float SPEED = 0.1f;	//�J�����̑��x
const float INIT_RADIAN_XZ = 0.0f;									//X-Z�ʂ̏������W�A���p
const float INIT_RADIAN_Y = 0.0f;									//Y-XZ�ʂ̏������W�A���p


/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCameraDebug::CCameraDebug()
	:m_fRadXZ(INIT_RADIAN_XZ)	//X-Z�ʂ̉�]�p
	, m_fRadY(INIT_RADIAN_Y)		//Y-XZ�ʂ̉�]�p
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
CCameraDebug::~CCameraDebug()
{
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCameraDebug::Update()
{
	// =============== �����_���� =====================
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_UP))
	{
		m_fLook.z += SPEED;
	}
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_DOWN))
	{
		m_fLook.z -= SPEED;
	}
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_RIGHT))
	{
		m_fLook.x -= SPEED;
	}
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_LEFT))
	{
		m_fLook.x += SPEED;
	}

	// =============== �J������] =====================
	if (IsKeyPress('W'))
	{
		m_fRadY += SPEED;
	}
	if (IsKeyPress('S'))
	{
		m_fRadY -= SPEED;
	}
	if (IsKeyPress('A'))
	{
		m_fRadXZ -= SPEED;
	}
	if (IsKeyPress('D'))
	{
		m_fRadXZ += SPEED;
	}

	// =============== �����_����̋������� =====================
	if (IsKeyPress('Q'))
	{
		m_fRadius += SPEED;
	}
	if (IsKeyPress('E'))
	{
		m_fRadius -= SPEED;
	}

	// =============== �J�����ʒu����o�� =====================
	m_fPos = {
		cosf(m_fRadY) * sinf(m_fRadXZ) * m_fRadius + m_fLook.x,	//x���W
		sinf(m_fRadY) * m_fRadius,								//y���W
		cosf(m_fRadY) * cosf(m_fRadXZ) * m_fRadius + m_fLook.z	//z���W
	};
}