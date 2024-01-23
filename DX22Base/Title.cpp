/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���V�[������
	---------------------------------------
	Title.cpp
	------------------------------------
	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/10/26 ������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �I�[�o�[���C�h�֐��ǉ� takagi
	�E2023/11/22 ���e�N�X�`���\���A��ʑJ�� nieda
	�E2023/11/23 �R���g���[���[�ɑΉ� nieda
	�E2023/11/24 �R�����g�A�萔��`�A�񋓒ǉ� nieda
	�E2023/12/12 �J�ڐ�V�[�����X�e�[�W�Z���N�g�ɕύX yamamoto
	�E2023/12/16 �`�敨���P takagi
	�E2023/12/17 �R�}���h���\������Ă��Ȃ��Ƃ��͌���L�[���󂯕t���Ȃ��悤�� takagi
	�E2023/12/18 �摜�����ւ��E�R�}���h�ʒu�����E�I�[�v�j���O�g�p�؊��쐬 takagi
	�E2024/01/20 GetType()�֐��폜�E���t�@�N�^�����O takagi
	
========================================== */

// =============== �f�o�b�O���[�h ===================
#define USE_OPENING (false)	//�I�[�v�j���O�����݂��邩

// =============== �C���N���[�h ===================
#include "Title.h"			//���g�̃w�b�_
#include "Input.h"			//���͎�t
#include "FixedCamera.h"	//�C���X�^���X���
#include "BgTitle.h"		//�C���X�^���X���
#include "CommandTitle.h"	//�C���X�^���X���
#include "TitleLogo.h"		//�C���X�^���X���
#include "OpeningTitle.h"	//�C���X�^���X���

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTitle::CTitle()
	:m_ucFlag(E_FLAG_COMMAND_CONTINUE)	//�t���O
{
	// =============== �����_���[ ===================
	RenderTarget*  p = GetDefaultRTV();	//2D�`��p�����_���[
	SetRenderTargets(1, &p, nullptr);	//2D�`��p�����_���[�Z�b�g

	// =============== ���I�m�� ===================
	m_p2dObjectOnScreen.emplace(E_2D_BACK, new CBgTitle(MAP_WAIT_START.at(E_2D_BACK)));			//�w�i
	m_p2dObjectOnScreen.emplace(E_2D_START, new CCommandTitle(MAP_WAIT_START.at(E_2D_START)));	//�p���R�}���h
	m_p2dObjectOnScreen.emplace(E_2D_FINISH, new CCommandTitle(MAP_WAIT_START.at(E_2D_FINISH)));	//�I���R�}���h
	m_p2dObjectOnScreen.emplace(E_2D_LOGO, new CTitleLogo(MAP_WAIT_START.at(E_2D_LOGO)));		//�^�C�g�����S
#if USE_OPENING
	m_p2dObjectOnScreen.emplace(E_2D_OPENING, new COpeningTitle());							//�J�n�f��
#endif
	m_pCamera = new CFixedCamera();	//�Œ�J����

	// =============== ������ ===================
	//m_pCamera->SetRadius(START_RADIUS_CAMERA);	//���������ݒ�
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		// =============== ���� ===================
		if (m_p2dObjectOnScreen.find(nIdx) == m_p2dObjectOnScreen.end() || !m_p2dObjectOnScreen.at(nIdx))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
		{
			// =============== �I�� ===================
			continue;	//�����ΏۊO
		}
		if (MAP_POS.find(nIdx) != MAP_POS.end())	//map�̔z�񂪑��݂���Y����
		{
			m_p2dObjectOnScreen.at(nIdx)->SetPos({ MAP_POS.at(nIdx) });				//�ʒu������
		}
		if (MAP_TEXTURE.find(nIdx) != MAP_TEXTURE.end())	//map�̔z�񂪑��݂���Y����
		{
			m_p2dObjectOnScreen.at(nIdx)->SetTexture(MAP_TEXTURE.at(nIdx).c_str());	//�e�N�X�`���o�^
		}

		// =============== �J�����o�^ ===================
		m_p2dObjectOnScreen.at(nIdx)->SetCamera(m_pCamera);	//�J�����o�^
	}

	// =============== ��� ===================
	if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
		&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Selected();	//�I����ԑJ��
	}
#if !USE_OPENING	//�J�n�f�����Ȃ��ꍇ�����ɏk�����Ă�
	// =============== �k�� ===================
	if (m_p2dObjectOnScreen.find(E_2D_BACK) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_BACK)
		&& typeid(CBgTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_BACK)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CBgTitle*>(m_p2dObjectOnScreen[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//�w�i�k���J�n
	}
	if (m_p2dObjectOnScreen.find(E_2D_LOGO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_LOGO)
		&& typeid(CTitleLogo) == typeid(*m_p2dObjectOnScreen.at(E_2D_LOGO)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CTitleLogo*>(m_p2dObjectOnScreen[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//���S�k���J�n
	}
#endif
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
CTitle::~CTitle()
{
	// =============== �I�� ===================
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		if (m_p2dObjectOnScreen.find(nIdx) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(nIdx))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
		{
			delete m_p2dObjectOnScreen.at(nIdx);	//�Ώۍ폜
			m_p2dObjectOnScreen.erase(nIdx);		//map����؏�
		}
	}
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
void CTitle::Update()
{
	// =============== ��� ===================
	if (m_p2dObjectOnScreen.find(E_2D_OPENING) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_OPENING)
		&& typeid(COpeningTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_OPENING)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		if (!static_cast<COpeningTitle*>(m_p2dObjectOnScreen[E_2D_OPENING])->GetAnimFlg())	//OP�A�j���[�V�������͕`�悵�Ȃ�
		{
			// =============== �I�� ===================
			delete m_p2dObjectOnScreen.at(E_2D_OPENING);	//�Ώۍ폜
			m_p2dObjectOnScreen.erase(E_2D_OPENING);		//map����؏�

			//// =============== �Y�[���A�E�g ===================
			//if (m_pCamera)	//�k���`�F�b�N
			//{
			//	m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);	//�Y�[���A�E�g�J�n
			//}

			// =============== �k�� ===================
			if (m_p2dObjectOnScreen.find(E_2D_BACK) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_BACK)
				&& typeid(CBgTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_BACK)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CBgTitle*>(m_p2dObjectOnScreen[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//�w�i�k���J�n
			}
			if (m_p2dObjectOnScreen.find(E_2D_LOGO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_LOGO)
				&& typeid(CTitleLogo) == typeid(*m_p2dObjectOnScreen.at(E_2D_LOGO)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CTitleLogo*>(m_p2dObjectOnScreen[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//���S�k���J�n
			}
		}
		else
		{
			// =============== �X�V ===================
			m_p2dObjectOnScreen[E_2D_OPENING]->Update();	//�A�j���X�V

			// =============== �I�� ===================
			return;	//����ȏ�X�V���Ȃ�
		}
	}

	// =============== ���͎�t ===================
	if (!(m_ucFlag.Check(E_FLAG_TIDYING_UP)))	//�Еt�����łȂ�
	{
		// =============== �R���g���[�� ==================
		if (GetUseVController())	// �R���g���[�����ڑ�����Ă���ꍇ
		{
			// =============== �J�[�\���ړ� ===================
			if (IsStickLeft().y < 0)		//�����͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Selected();		//�I����ԑJ��
						m_ucFlag.Up(E_FLAG_COMMAND_CONTINUE);								//��̃R�}���h�̗p
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->UnSelected();	//�I����ԑJ��
						m_ucFlag.Down(E_FLAG_COMMAND_FINISH);								//���̃R�}���h�s�̗p
					}
				}
			}
			if (IsStickLeft().y > 0)	//�����͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->Selected();	//�I����ԑJ��
						m_ucFlag.Up(E_FLAG_COMMAND_FINISH);										//���̃R�}���h�̗p
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->UnSelected();	//�I����ԑJ��
						m_ucFlag.Down(E_FLAG_COMMAND_CONTINUE);									//��̃R�}���h�s�̗p
					}
				}
			}

			// =============== ���� ===================
			if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START))
				&& m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//�\����
				{
					if (IsKeyTriggerController(BUTTON_B))	//B�{�^�����͎�
					{
						// =============== �t���O���� ===================
						m_ucFlag.Up(E_FLAG_DECIDE_COMMAND);	//����
					}
				}
			}
		}
		else
		{
			// =============== �J�[�\���ړ� ===================
			if (IsKeyTrigger(VK_UP) || IsKeyTrigger('W'))		//���EW���͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Selected();		//�I����ԑJ��
						m_ucFlag.Up(E_FLAG_COMMAND_CONTINUE);								//��̃R�}���h�̗p
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->UnSelected();	//�I����ԑJ��
						m_ucFlag.Down(E_FLAG_COMMAND_FINISH);								//���̃R�}���h�s�̗p
					}
				}
			}
			if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//���ES���͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->Selected();	//�I����ԑJ��
						m_ucFlag.Up(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�̗p
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->UnSelected();	//�I����ԑJ��
						m_ucFlag.Down(E_FLAG_COMMAND_CONTINUE);								//��̃R�}���h�s�̗p
					}
				}
			}

			// =============== ���� ===================
			if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START))
				&& m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
				if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//�\����
				{
					if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE))	//Enter�ESpace���͎�
					{
						// =============== �t���O���� ===================
						m_ucFlag.Up(E_FLAG_DECIDE_COMMAND);	//����
					}
				}
			}
		}
	}

	// =============== �I���m�� ===================
	if (m_ucFlag.Check(E_FLAG_DECIDE_COMMAND))	//�R�}���h���莞
	{
		// =============== �I����Ԕ��� ===================
		if (m_ucFlag.Check(E_FLAG_COMMAND_CONTINUE))	//�p��
		{
			// =============== ��ԑJ�� ===================
			if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Decide();	//�����ԑJ��
			}

			m_bFinish = true;						//�V�[���̏I���\��
			m_eNextScene = E_TYPE_SELECT_STAGE;		//�X�e�[�W�I����
			m_ucFlag.Down(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
		if (m_ucFlag.Check(E_FLAG_COMMAND_FINISH))	//�I��
		{
			// =============== ��ԑJ�� ===================
			if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->Decide();	//�����ԑJ��
			}
			m_bFinish = true;						//�V�[���̏I���\��
			m_eNextScene = E_TYPE_FINISH_ALL;		//�A�v���I��
			m_ucFlag.Down(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
	}

	// =============== �X�V ===================
	if (m_pCamera)	//�k���`�F�b�N
	{
		m_pCamera->Update();	//�J�����X�V
	}
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		CScene::Update();	//�e�֐��Ăяo��
		//if (m_p2dObjectOnScreen.find(nIdx) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(nIdx))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
		//{
		//	m_p2dObjectOnScreen.at(nIdx)->Update();	//�X�V�Ώ�
		//}
	}
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CTitle::Draw()
{
	// =============== �`�� ===================
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		CScene::Draw();	//�e�֐��Ăяo��
	}
}

/* ========================================
	���V�[���Q�b�^
	----------------------------------------
	���e�F�J�ڂ������V�[��������������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�J�ڐ�V�[���̎��
=========================================== */
CTitle::E_TYPE CTitle::GetNext() const
{
	// =============== �� ===================
	return CTitle::m_eNextScene;	//�J�ڐ�V�[���̎��
}