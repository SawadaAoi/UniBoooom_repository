/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�ǐՃJ��������
	------------------------------------
	CameraDebug.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/04 ���� takagi
	�E2023/11/06 �R�[�f�B���O�K��K�p�E�ǐՑΏۓo�^�@�\�쐬

========================================== */



// =============== �C���N���[�h ===================
#include "CameraDebug.h"	//���g�̃w�b�_
#include "Input.h"			//���͎�t

// =============== �萔��` ===================
const float SPEED = 0.1f;	//�J�����̑��x



/* ========================================
	�R���X�g���N�^
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCameraDebug::CCameraDebug()
{
}

/* ========================================
	�f�X�g���N�^
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
	// ��������Shift�ACtrl�ŃJ�����̒����_�𓮂���
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

	// W,A,S,D,Q,E�ŃJ�����̈ʒu�𓮂���
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
	if (IsKeyPress('Q'))
	{
		m_fRadius += SPEED;
	}
	if (IsKeyPress('E'))
	{
		m_fRadius -= SPEED;
	}

	//�p�x�E�����E�����_����J�����̈ʒu���v�Z
	m_fPos = {
		cosf(m_fRadY) * sinf(m_fRadXZ) * m_fRadius + m_fLook.x,
		sinf(m_fRadY) * m_fRadius,
		cosf(m_fRadY) * cosf(m_fRadXZ) * m_fRadius + m_fLook.z
	};
}