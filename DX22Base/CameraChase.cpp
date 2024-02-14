/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�ǐՃJ��������
	------------------------------------
	CameraChase.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/04 ���� takagi
	�E2023/11/06 �R�[�f�B���O�K��K�p�E�ǐՑΏۓo�^�@�\�쐬 takagi
	�E2023/11/07 GetViewMatrix()�֐���const�C���q�t�^�E�R�����g�C�� takagi
	�E2023/11/08 TPos�C�� takagi
	�E2023/11/09 ������ takagi
	�E2023/11/10 �p�����^�C�� takagi
	�E2023/11/18 �U���t���O���� takagi
	�E2023/11/29 �啶���E�������̏C�� takagi
	�E2023/12/03 �ʒu�Q�b�^�p���� takagi
	�E2023/12/04 GetViewWithoutTranspose�̖߂�l��ύX yamashita
	�E2023/12/16 �Y�[���@�\�ɑΉ� takagi
	�E2024/01/21 Player���ōX�V���Ȃ��Ă��ǂ��l�ɕύX�E���t�@�N�^�����O takagi
	�E2024/01/25 GetViewWithoutTranspose()�֐����ŏ��������Ȃ��p�^�[�����C�� takagi
	�E2024/02/15 �J�����ړ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "CameraChase.h"	//���g�̃w�b�_
#include "Input.h"			//���͎�t

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCameraChase::CCameraChase()
	:m_pTarget(nullptr)	//�ǐՑΏ�(�ǐՂ݂̂��s���l��ύX�ł��Ȃ��悤const�C���q�ɂ��Ă���)
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
CCameraChase::~CCameraChase()
{
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V�����@�����̃I�u�W�F�N�g����ɒǐՑΏۂ̍X�V�K�v����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCameraChase::Update()
{
	// =============== �t���O���� ===================
	HandleFlag();	//�t���O���e����

	// =============== ���炵 ===================
	Shift();	//���炵

	// =============== �����X�V ===================
	Zoom();	//�����X�V

	// =============== �ʒu�X�V ===================
	m_fPos = GetPos();	//���g�̈ʒu�X�V
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
DirectX::XMFLOAT4X4 CCameraChase::GetViewWithoutTranspose() const
{
	// =============== �ϐ��錾 ===================
	DirectX::XMFLOAT4X4 View;	//�s��i�[�p

	// =============== �r���[�s��̌v�Z ===================
	if (m_pTarget)	//�k���`�F�b�N
	{
		DirectX::XMStoreFloat4x4(&View, DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_pTarget->x + m_fOffsetVibrateEye.x
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_POS * cosf(*m_pfShiftAngle) *
				(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//�C�[�Y�C��
					: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
						: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//�C�[�Y�A�E�g
					: 0.0f),	//�k��
				m_pTarget->y + m_fRadius * sinf(m_fAngle),
				m_pTarget->z + m_fOffsetVibrateEye.y - m_fRadius * cosf(m_fAngle)
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_POS * sinf(*m_pfShiftAngle) *
				(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//�C�[�Y�C��
					: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
						: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//�C�[�Y�A�E�g
					: 0.0f),	//�k��
				0.0f),													//�J�������Έʒu
			DirectX::XMVectorSet(m_pTarget->x + m_fOffsetVibrateLook.x
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_LOOK * cosf(*m_pfShiftAngle) * 
					(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//�C�[�Y�C��
						: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
							: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//�C�[�Y�A�E�g
					: 0.0f),	//�k��
				m_pTarget->y,
				m_pTarget->z + m_fOffsetVibrateLook.y
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_LOOK * sinf(*m_pfShiftAngle) *
				(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//�C�[�Y�C��
					: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
						: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//�C�[�Y�A�E�g
					: 0.0f),	//�k��
				0.0f),													//�����_
			DirectX::XMVectorSet(m_fUp.x, m_fUp.y, m_fUp.z, 0.0f)));	//�A�b�v�x�N�g��
	}
	else
	{
		View = CCamera::GetViewWithoutTranspose();	//�Ϗ�
	}

	// =============== �� ===================
	return View;	//�r���[���W�n
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
TPos3d<float> CCameraChase::GetPos() const
{
	// =============== �� ===================
	if (m_pTarget)	//�k���`�F�b�N
	{
		return {
			m_pTarget->x + m_fOffsetVibrateEye.x,								//x���W
			m_pTarget->y + m_fRadius * sinf(m_fAngle),							//y���W
			m_pTarget->z + m_fOffsetVibrateEye.y - m_fRadius * cosf(m_fAngle)	//z���W
		};	//�����_�Ƃ̑��Έʒu
	}
	else
	{
		return m_fPos;	//���g�������Έʒu
	}
}

/* ========================================
	�ǐՑΏۓo�^�֐�
	-------------------------------------
	���e�F�ǐՑΏۂ̈ʒu�ϐ��̃A�h���X��o�^
	-------------------------------------
	����1�Fconst TPos3d<float>* pPos�F�ǐՑΏۂ̈ʒu�A�h���X
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCameraChase::SetTarget(const TPos3d<float>* pPos)
{
	// =============== �A�h���X�ύX ===================
	m_pTarget = pPos;	//�ǐՑΏۓo�^

	// =============== ������ ===================
	m_fPos = GetPos();	//�����Ώۈʒu�����g�ʒu�ɔ��f
}