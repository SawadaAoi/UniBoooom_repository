/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��������
	---------------------------------------
	CommandPause.cpp

	�쐬��	takagi

	�ύX����
	�E2023/12/10 ���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "CommandPause.h"	//���g�̃w�b�_
#include "GameParameter.h"

// =============== �萔��` ===================
const float AMPITUDE(25.0f);										//�U��
const float ANGLE_SPEED(DirectX::XMConvertToRadians(1.5f));			//�P�U���̊p���x
const TDiType<float> UV_SCALE(1.0f / 3.0f, 1.0f);					//UV�g�k
#if !MODE_GAME_PARAMETER
const float COMMAND_WIDTH = 360.0f;									//�R�}���h�c��
const float COMMAND_HEIGHT = 78.0f;									//�R�}���h����
#endif // !MODE_GAME_PARAMETER
const TDiType<float> SCALE_UNSELECT(COMMAND_WIDTH, COMMAND_HEIGHT);	//��I�����̍ő�g�k��
const TDiType<float> SCALE_SELECT(SCALE_UNSELECT * 1.1f);			//�I�����̍ŏ��g�k��
const TDiType<float> SCALE_DESIDE(SCALE_UNSELECT * 1.2f);			//���莞�̊g�嗦
const TDiType<float> ADD_SCALE(60.0f * 0.04f, 13.0f * 0.04f);		//�g�k��������
const int DISPLAY_DECIDE(15);										//����e�N�X�`����\�����鎞��

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�Fconst int& nWaitTime�F�ҋ@����
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCommandPause::CCommandPause(const int& nWaitTime)
	:m_eTexNo(E_TEXTURE_UNSELECTED)	//�e�N�X�`���ԍ�
	,m_fScale(SCALE_UNSELECT)		//�g�k
	,m_pnTimer(nullptr)				//�^�C�}�[
	,CPauseObj(nWaitTime)			//�Ϗ�
{
	// =============== ������ ===================
	SetSize({ m_fScale.x, m_fScale.y, 0.0f });	//�傫��������
	SetUvScale(UV_SCALE);						//UV�g�k������
}

/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCommandPause::~CCommandPause()
{
	// =============== �I�� ===================
	SAFE_DELETE(m_pnTimer);	//�^�C�}�[�폜
}

void CCommandPause::Update()
{
	// =============== �X�V ===================
	CPauseObj::Update();	//�e�̊֐��g�p

	// =============== UV�ړ� ===================
	SetUvOffset({ static_cast<float>(m_eTexNo) / static_cast<float>(E_TEXTURE_MAX), 0.0f });	//UV���W�ړ�

	// =============== ��ԕ��� ===================
	if (E_TEXTURE_DECIDE == m_eTexNo)	//������
	{
		// =============== �^�C�}�[ ===================
		if (m_pnTimer)	//�k���`�F�b�N
		{
			if (--(*m_pnTimer) > 0)	//�J�E���g�_�E��
			{
			}
			else
			{
				SAFE_DELETE(m_pnTimer);	//�^�C�}�폜
				// =============== ��ԊǗ� ===================
				m_eTexNo = E_TEXTURE_SELECTED;	//�I����Ԃɖ߂�
			}
		}

	}
	else
	{
		// =============== �T�C�Y�Ǘ� ===================
		if (E_TEXTURE_SELECTED == m_eTexNo)	//������
		{
			m_fScale += ADD_SCALE;	//�T�C�Y����
			if (m_fScale.x > SCALE_SELECT.x)	//���E�l�`�F�b�N
			{
				m_fScale.x = SCALE_SELECT.x;	//�␳
			}
			if (m_fScale.y > SCALE_SELECT.y)	//���E�l�`�F�b�N
			{
				m_fScale.y = SCALE_SELECT.y;	//�␳
			}
		}
		else 
		{
			if (E_TEXTURE_UNSELECTED == m_eTexNo)	//������
			{
				m_fScale -= ADD_SCALE;	//�T�C�Y����
				if (m_fScale.x < SCALE_UNSELECT.x)	//���E�l�`�F�b�N
				{
					m_fScale.x = SCALE_UNSELECT.x;	//�␳
				}
				if (m_fScale.y < SCALE_UNSELECT.y)	//���E�l�`�F�b�N
				{
					m_fScale.y = SCALE_UNSELECT.y;	//�␳
				}
			}
		}
	}

	// =============== �T�C�Y�ύX ===================
	SetSize(TPos3d<float>(m_fScale.x, m_fScale.y, 0.0f));	//�g�k����
}

/* ========================================
	�I�����֐�
	----------------------------------------
	���e�F�\����I����ԉ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCommandPause::Selected()
{
	// =============== ��ԑJ�� ===================
	m_eTexNo = E_TEXTURE_SELECTED;	//�e�N�X�`���ԍ��؊�
}

/* ========================================
	��I�����֐�
	----------------------------------------
	���e�F�\�����I����ԉ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCommandPause::UnSelected()
{
	// =============== ��ԑJ�� ===================
	m_eTexNo = E_TEXTURE_UNSELECTED;	//�e�N�X�`���ԍ��؊�
}

/* ========================================
	����֐�
	----------------------------------------
	���e�F�\���������ԉ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCommandPause::Decide()
{
	// =============== ��ԑJ�� ===================
	m_eTexNo = E_TEXTURE_DECIDE;	//�e�N�X�`���ԍ��؊�
	m_fScale = SCALE_DESIDE;		//UV�g�k�ύX

	// =============== �^�C�}�[�쐬 ===================
	if (m_pnTimer)	//�k���`�F�b�N
	{
		SAFE_DELETE(m_pnTimer);	//�^�C�}�폜
	}
	m_pnTimer = new int(DISPLAY_DECIDE);	//���I�m��
}