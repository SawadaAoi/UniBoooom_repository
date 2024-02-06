/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�J�n���Y�[���A�E�g����
	---------------------------------------
	TitleInitZoomOut.cpp

	�쐬��	takagi

	�ύX����
	�E2024/02/02 ���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "TitleInitZoomOut.h"	//���g�̃w�b�_
#include "TitleInitCounter.h"	//�J�E���^�g�p

// =============== �萔�E�}�N����` ===================
const TTriType<float> SCALE_RATE_L = {2.0f, 2.0f, 0.0f};	//�g�厞�̊g�k����ݒ肷��

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTitleInitZoomOut::CTitleInitZoomOut()
{
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
CTitleInitZoomOut::~CTitleInitZoomOut()
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
void CTitleInitZoomOut::Update()
{
	// =============== �ϐ��錾 ===================
	auto pCounter = CTitleInitCounter::GetThis().GetCounter().lock();	//�J�E���^

	// =============== �X�V ===================
	if (pCounter && m_pfScaleShort && m_pfScaleLarge)	//�k���`�F�b�N
	{
		auto fCheck = (*m_pfScaleLarge - *m_pfScaleShort) * pCounter->GetRate() + *m_pfScaleShort;
		CTitleObj::SetSize(fCheck);	//�J�E���^�i�s�𗘗p�����g�k�X�V
	}
	CTitleObj::Update();	//�e�̊֐��g�p
}

/* ========================================
	�傫���Z�b�^�֐�
	-------------------------------------
	���e�F�ŏ��E�ő�̑傫���o�^
	-------------------------------------
	����1�Fconst TTriType<float> & fScale�F�ʏ펞��(�ŏ�)�g�k���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitleInitZoomOut::SetSize(const TTriType<float>& fScale)
{
	// =============== �������E���I�m�� ===================
	if (m_pfScaleShort)	//�k���`�F�b�N
	{
		*m_pfScaleShort = fScale;	//�ŏ��g�k��������
	}
	else
	{
		m_pfScaleShort = std::make_shared<TTriType<float>>(fScale);	//�ŏ��g�k���m��
	}
	if (m_pfScaleLarge)	//�k���`�F�b�N
	{
		*m_pfScaleLarge = fScale;	//�ŏ��g�k��������
	}
	else
	{
		m_pfScaleLarge = std::make_shared<TTriType<float>>(fScale);	//�ő�g�k���m��
	}

	// =============== �g�k��񔽉f ===================
	if (m_pfScaleRateShort)	//�k���`�F�b�N
	{
		*m_pfScaleShort *= *m_pfScaleRateShort;	//�ŏ��T�C�Y�ݒ�
	}
	if (m_pfScaleRateLarge)	//�k���`�F�b�N
	{
		*m_pfScaleLarge *= *m_pfScaleRateLarge;	//�ő�T�C�Y�ݒ�
	}
	else
	{
		*m_pfScaleLarge *= SCALE_RATE_L;	//�ő�T�C�Y�ݒ�
	}

	// =============== ������ ===================
	CTitleObj::SetSize(*m_pfScaleLarge);	//�傫���ݒ�
}

/* ========================================
	�g�k���Z�b�^�֐�
	-------------------------------------
	���e�F�ŏ��E�ő�̊g�k���o�^
	-------------------------------------
	����1�Fconst std::array<TTriType<float>, 2>& fScaleRate�F�g�k��[0:�ŏ�, 1:�ő�]
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitleInitZoomOut::SetScaleRate(const std::array<TTriType<float>, 2>& fScaleRate)
{
	// =============== �������E���I�m�� ===================
	if (m_pfScaleRateShort)	//�k���`�F�b�N
	{
		*m_pfScaleRateShort = fScaleRate.at(0);	//�ŏ��g�k��������
	}
	else
	{
		m_pfScaleRateShort = std::make_shared<TTriType<float>>(fScaleRate.at(0));	//�ŏ��g�k���m��
	}
	if (m_pfScaleRateLarge)	//�k���`�F�b�N
	{
		*m_pfScaleRateLarge = fScaleRate.at(1);	//�ŏ��g�k��������
	}
	else
	{
		m_pfScaleRateLarge = std::make_shared<TTriType<float>>(fScaleRate.at(1));	//�ő�g�k���m��
	}

	// =============== ���f ===================
	if (m_pfScaleShort)	//�k���`�F�b�N
	{
		*m_pfScaleShort *= *m_pfScaleRateShort;	//�ŏ��T�C�Y�ݒ�
	}
	if (m_pfScaleLarge)	//�k���`�F�b�N
	{
		*m_pfScaleLarge *= *m_pfScaleRateLarge;	//�ő�T�C�Y�ݒ�
	}
}