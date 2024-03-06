/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���[�h�C���W�P�[�^��`
	---------------------------------------
	LoadIndicator.cpp

	�쐬��	takagi

	�ύX����
	�E2024/03/06 ����J�n takagi

========================================== */

// =============== �C���N���[�h =====================
#include "LoadIndicator.h"	//���g�̃w�b�_

// =============== �萔��` ===================
const std::string TEX = "Assets/Texture/Title/PlayerToRight.png";	//�e�N�X�`���t�@�C��
const TPos3d<float> POS{ static_cast<float>(SCREEN_WIDTH) - 200.0f, 100.0f, 0.0f };	//�ʒu
const TPos3d<float> SCALE(320.0f, 180.0f, 0.0f);				//�������Ƃ��̑傫��
const int MAX_ANIM(55);																								//�A�j���[�V������
const TDiType<int> MAX_SEAT(5, 11);																					//5x11
const /*TODO:unsigned*/ int ANIMATION_INTERVAL = 2;																	//�A�j���[�V�����t���[���Ԋu
const unsigned int REST_FRAME = 180;

/* ========================================
	���g�񋟊֐�
	----------------------------------------
	���e�F���g��B��̂ݑ��݂����A���̃A�h���X��񋟂���
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̃A�h���X
=========================================== */
CLoadIndicator& CLoadIndicator::GetThis()
{
	// =============== ���� =====================
	static CLoadIndicator LoadIndicator;	//���g�̃C���X�^���X�𐶐�

	// =============== �� =====================
	return LoadIndicator;	//�������ꂽ���g�̃A�h���X���
}

void CLoadIndicator::BeginDraw()
{
	if (!m_DrawThread.joinable())	//�X���b�h�̒��g���Ȃ���
	{
		std::jthread Thread{ [this](std::stop_token ThreadStop) {

	while (!ThreadStop.stop_requested())
	{
		if (m_p2d)	//�k���`�F�b�N
		{
			C2dPolygon Tex;
			Tex.SetTexture("Assets/Texture/Start/Wait.png");
			Tex.SetPos({ static_cast<float>(SCREEN_WIDTH / 2.0f), static_cast<float>(SCREEN_HEIGHT / 2.0f), 0.0f });
			Tex.SetSize({ static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f });
			if (GetContext())
			{
				BeginDrawDirectX();	//�����o���J�n
				Tex.Draw();			//�`��
				m_p2d->Update();
				m_p2d->Draw();	//�`��
				EndDrawDirectX();	//�����o������
			}
		}
	}
			} };			//�ꎞ�I�ȃX���b�h�錾
		//m_DrawThread = std::move(Thread);	//swap�ł͂Ȃ��ꎞ�ϐ������[�u���ď���������
		m_DrawThread.swap(Thread);
		std::stop_token token;
		m_DrawThread.get_stop_token().swap(token);
	}
}

void CLoadIndicator::EndDraw()
{
	if (m_DrawThread.joinable())	//�X���b�h�̒��g�����鎞
	{
		m_DrawThread.request_stop();	//�֐�������std::stop_token���~�v����Ԃɂ���
		m_DrawThread.join();			//�X���b�h�I���ҋ@
	}
}

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CLoadIndicator::CLoadIndicator()
{
	m_p2d = std::make_shared<CDrawAnim>(MAX_ANIM, MAX_SEAT, ANIMATION_INTERVAL);//�A�j���摜

	m_p2d->SetTexture(TEX.c_str());	//�e�N�X�`���o�^
	m_p2d->SetPos(POS);				//�ʒu�o�^
	m_p2d->SetSize(SCALE);			//�傫���o�^
	m_p2d->SetLoopFlg(true);		//���[�v�ݒ�
}

/* ========================================
	�R�s�[�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�Fconst CLoadIndicator& Obj�F�R�s�[��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CLoadIndicator::CLoadIndicator(const CLoadIndicator& Obj)
{	//Nothing to do
}

/* ========================================
	������Z�q
	----------------------------------------
	���e�F�����ɍs������
	----------------------------------------
	����1�Fconst CLoadIndicator& Obj�F�R�s�[��
	----------------------------------------
	�ߒl�F�������Ă��Ȃ����g�̎Q��
=========================================== */
CLoadIndicator& CLoadIndicator::operator=(const CLoadIndicator& Obj)
{
	// =============== �� =====================
	return *this;	//���g�̎Q��
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
CLoadIndicator::~CLoadIndicator()
{
}