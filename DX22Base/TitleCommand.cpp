/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�R�}���h����
	---------------------------------------
	TitleCommand.cpp

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/18 �T�C�Y�ύX*2.0f��*3.5f takagi
	�E2024/02/05 ���t�@�N�^�����O takagi

========================================== */

// =============== �C���N���[�h ===================
#include "TitleCommand.h"	//���g�̃w�b�_

// =============== �萔��` ===================
const unsigned int ALPHA_FRAME = 30;	//�����x�ω��̕Г�����

// =============== �O���[�o���ϐ��錾 ===================
bool CTitleCommand::m_bCntUpDwn = true;																			//�J�E���g�A�b�v�E�_�E���؊��t���O
std::shared_ptr<CFrameCnt> CTitleCommand::m_pAlphaCnt = std::make_shared<CFrameCnt>(ALPHA_FRAME, m_bCntUpDwn);	//�����x�ω��p�J�E���^

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�Fconst E_STATE& eInitState�F�������
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTitleCommand::CTitleCommand(const E_STATE& eInitState)
	:m_eTexNo(eInitState)	//�e�N�X�`���ԍ�
	,m_unAnimeNo(0)			//�A�j���[�V�����R�}�ԍ�
	,m_pAnimeInterval(0)	//�A�j���[�V�����Ԋu
{
	// =============== ������ ===================
#if _DEBUG
	if (MAP_SCALE.find(m_eTexNo) == MAP_SCALE.end())	//�A�N�Z�X�`�F�b�N
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "�A�z�R���e�i�̃L�[���s�����Ă��܂�").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
	}
#endif	//!_DEBUG
	m_fScale = MAP_SCALE.at(m_eTexNo);	//�g�k
	SetSize(m_fScale);					//�傫��������
#if _DEBUG
	if (MAP_MAX_ANIMATION_NUM.find(m_eTexNo) == MAP_MAX_ANIMATION_NUM.end())	//�A�N�Z�X�`�F�b�N
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "�A�z�R���e�i�̃L�[���s�����Ă��܂�").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
	}
#endif	//!_DEBUG
	SetUvScale({ 1.0f / static_cast<float>(E_STATE_MAX), 1.0f / static_cast<float>(MAP_MAX_ANIMATION_NUM.at(m_eTexNo)) });	//UV�g�k������
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
CTitleCommand::~CTitleCommand()
{
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitleCommand::Update()
{
	// =============== �A�j���[�V�����ԍ��X�V ===================
	if (!(m_pAnimeInterval && !m_pAnimeInterval->IsFin()))	//�C���^�[�o�����łȂ�
	{
		m_unAnimeNo++;																			//�A�j���[�V�����ԍ��i�s
		m_pAnimeInterval.reset();																//�폜
#if _DEBUG
		if (MAP_ANIMATION_INTERVAL.find(m_eTexNo) == MAP_ANIMATION_INTERVAL.end())	//�A�N�Z�X�`�F�b�N
		{
			std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
			MessageBox(nullptr, (ErrorSpot + "�A�z�R���e�i�̃L�[���s�����Ă��܂�").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
		}
#endif	//!_DEBUG
		m_pAnimeInterval = std::make_shared<CFrameCnt>(MAP_ANIMATION_INTERVAL.at(m_eTexNo));	//�C���^�[�o�����Z�b�g
	}
#if _DEBUG
	if (MAP_MAX_ANIMATION_NUM.find(m_eTexNo) == MAP_MAX_ANIMATION_NUM.end())	//�A�N�Z�X�`�F�b�N
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "�A�z�R���e�i�̃L�[���s�����Ă��܂�").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
	}
#endif	//!_DEBUG
	while (m_unAnimeNo > MAP_MAX_ANIMATION_NUM.at(m_eTexNo))	//��`��`�F�b�N
	{
		m_unAnimeNo -= MAP_MAX_ANIMATION_NUM.at(m_eTexNo);	//��`��Ɏ��߂�
	}

	// =============== UV�ړ� ===================
	SetUvOffset({ static_cast<float>(m_eTexNo) / static_cast<float>(E_STATE_MAX),
		static_cast<float>(m_unAnimeNo) / static_cast<float>(MAP_MAX_ANIMATION_NUM.at(m_eTexNo)) });	//UV���W�ړ�

	// =============== �g�k ===================
	if (m_pFrameCnt && m_pfReScalingStartSize)	//�k���`�F�b�N
	{
		// =============== �X�V ===================
		m_pFrameCnt->Count();	//�J�E���g�i�s
#if _DEBUG
		if (MAP_SCALE.find(m_eTexNo) == MAP_SCALE.end())	//�A�N�Z�X�`�F�b�N
		{
			std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
			MessageBox(nullptr, (ErrorSpot + "�A�z�R���e�i�̃L�[���s�����Ă��܂�").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
		}
#endif	//!_DEBUG
		m_fScale = (*m_pfReScalingStartSize - MAP_SCALE.at(m_eTexNo)) * m_pFrameCnt->GetRate() + MAP_SCALE.at(m_eTexNo);	//�g�k�X�V

		// =============== �T�C�Y�ύX ===================
		SetSize(m_fScale);	//�g�k����

		// =============== �폜 ===================
		if (m_pFrameCnt->IsFin())	//�J�E���g����
		{
			m_pFrameCnt.reset();			//�J�E���^�폜
			m_pfReScalingStartSize.reset();	//�傫���ޔ����폜
		}
	}

	// =============== ���� ===================
	if (E_STATE_SELECTED == m_eTexNo)	//�I�����
	{
		// =============== �����x�X�V =====================
		if (m_pAlphaCnt)	//�k���`�F�b�N
		{
			m_pAlphaCnt->Count();				//�J�E���g�i�s
			SetAlpha(m_pAlphaCnt->GetRate());	//�I����Ԃ̂Ƃ����ł���
			if (m_pAlphaCnt->IsFin())	//�J�E���g����
			{
				m_bCntUpDwn ^= 1;														//�J�E���g�A�b�v�_�E���t�]
				m_pAlphaCnt.reset();													//�J�E���^�폜
				m_pAlphaCnt = std::make_shared<CFrameCnt>(ALPHA_FRAME, m_bCntUpDwn);	//�J�E���g�A�b�v�E�_�E��
			}
		}
	}

	// =============== �X�V ===================
	CTitleObj::Update();	//�e�̊֐��g�p
}

/* ========================================
	��ԕύX�֐�
	----------------------------------------
	���e�F���g�̏�Ԃ�ύX
	----------------------------------------
	����1�Fconst E_STATE & eState�F�ω���̏��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitleCommand::ChangeState(const E_STATE & eState)
{
	// =============== ��ԑJ�� ===================
	m_eTexNo = eState;	//�e�N�X�`���ԍ��؊�

	// =============== �ޔ� ===================
	if (m_pfReScalingStartSize)	//�k���`�F�b�N
	{
		// =============== ������ ===================
		*m_pfReScalingStartSize = m_fScale;	//�傫���ޔ�
	}
	else
	{
		// =============== ���I�m�� ===================
		m_pfReScalingStartSize = std::make_shared<TTriType<float>>(m_fScale);	//�傫���ޔ�
	}

	// =============== �j�� ===================
	if (m_pFrameCnt)	//�k���`�F�b�N
	{
		m_pFrameCnt.reset();	//�J�E���^�폜
	}

	// =============== ���I�m�� ===================
#if _DEBUG
	if (MAP_ANIMATION_FRAME.find(m_eTexNo) == MAP_ANIMATION_FRAME.end())	//�A�N�Z�X�`�F�b�N
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "�A�z�R���e�i�̃L�[���s�����Ă��܂�").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
	}
#endif	//!_DEBUG
	m_pFrameCnt = std::make_shared<CFrameCnt>(MAP_ANIMATION_FRAME.at(m_eTexNo));	//�J�E���^�m��
	
	// =============== �����x���Z�b�g ===================
	if (E_STATE_SELECTED != m_eTexNo)	//�I����ԂłȂ�
	{
		SetAlpha(1.0f);	//�s����
	}
}

/* ========================================
	����A�j���Đ��m�F�֐�
	----------------------------------------
	���e�F����A�j���Đ��ς��m�F����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F����A�j���Đ�������true, ����ȊO��false
=========================================== */
bool CTitleCommand::DesideAnimeFin()
{
	// =============== ���� ===================
	if (E_STATE_DECIDE == m_eTexNo && !m_pFrameCnt)	//����A�j���Đ�������
	{
		// =============== �� ===================
		return true;	//����A�j���Đ�����
	}
	// =============== �� ===================
	return false;	//����A�j���Đ�������
}