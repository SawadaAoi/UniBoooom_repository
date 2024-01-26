/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���V�[������
	---------------------------------------
	Title.cpp

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
	�E2024/01/26 �I���A����SE�ǉ�
	
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

// =============== �񋓌^��` ===================
enum E_2D	//�X�V��
{
	E_2D_BACK,		//�w�i
	E_2D_START,		//�J�n�R�}���h
	E_2D_FINISH,	//�I���R�}���h
	E_2D_LOGO,		//�^�C�g�����S
	E_2D_OPENING,	//�J�n�f��
	E_2D_MAX,		//�v�f��
};	//2D�̃I�u�W�F�N�g

// =============== �萔��` ===================
const float START_RADIUS_CAMERA = 0.5f;		//�����J��������
const float END_RADIUS_CAMERA = 15.0f;		//�ŏI�J��������
const int ZOOMOUT_FRAME = 90;				//�Y�[���A�E�g�ɂ�����t���[����
const float COMMAND_SPACE = 120.0f;			//�R�}���h���m�̏c�̊�
const float COMMAND_DOWN = 160.0f;			//�R�}���h�𒆐S����ǂꂾ�������邩
const std::map<int, int> MAP_WAIT_START = {
	{E_2D_BACK, 0},	//�w�i
	{E_2D_START, ZOOMOUT_FRAME},	//�J�n�R�}���h
	{E_2D_FINISH, ZOOMOUT_FRAME},	//�I���R�}���h
	{E_2D_LOGO, 0},		//�^�C�g�����S
	{E_2D_OPENING, 0},	//�J�n�f��
};	//�|���S���ƕ\���J�n�ҋ@���Ԃ̑Ή��\
const std::map<int, int> MAP_WAIT_FIN = {
	{E_2D_BACK, 30},	//�w�i
	{E_2D_START, 15},	//�J�n�R�}���h
	{E_2D_FINISH, 30},	//�I���R�}���h
	{E_2D_LOGO, 15},	//�^�C�g�����S
};	//�|���S���ƕ\���I���ҋ@���Ԃ̑Ή��\
const std::map<int, std::string> MAP_TEXTURE = {
	{E_2D_BACK, "Assets/Texture//Title/TitleBg.png"},				//�w�i
	{E_2D_START, "Assets/Texture/Title/Title_Start.png"},			//�J�n�R�}���h
	{E_2D_FINISH, "Assets/Texture/Pause/Pause_Finish.png"},			//�I���R�}���h
	{E_2D_LOGO, "Assets/Texture/Title/TitleLogo.png"},				//�^�C�g�����S
	{E_2D_OPENING, "Assets/Texture/Title/titleopening_kari.png"},	//�J�n�f��
};	//�|���S���ƃe�N�X�`���̑Ή��\
const std::map<int, TPos3d<float>> MAP_POS = {
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},		//�w�i
	{E_2D_START, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f, 0.0f}},										//�J�n�R�}���h
	{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f - COMMAND_SPACE, 0.0f}},						//�I���R�}���h
	//{E_2D_LOGO, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 450.0f, 0.0f}},										//�^�C�g�����S
	{E_2D_OPENING, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},	//�I�[�v�j���O
};	//�|���S���Ə������W�̑Ή��\

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
	, m_pSE{ nullptr,nullptr}
	, m_pSESpeaker{ nullptr ,nullptr}
{
	// =============== �����_���[ ===================
	RenderTarget*  p = GetDefaultRTV();	//2D�`��p�����_���[
	SetRenderTargets(1, &p, nullptr);	//2D�`��p�����_���[�Z�b�g

	// =============== ���I�m�� ===================
	m_p2dObj = {
		{E_2D_BACK,new CBgTitle(MAP_WAIT_START.at(E_2D_BACK))},				//�w�i�p
		{E_2D_START,new CCommandTitle(MAP_WAIT_START.at(E_2D_START))},		//�p���R�}���h�p
		{E_2D_FINISH,new CCommandTitle(MAP_WAIT_START.at(E_2D_FINISH))},	//�I���R�}���h�p
		{E_2D_LOGO,new CTitleLogo(MAP_WAIT_START.at(E_2D_LOGO))},			//�^�C�g�����S�p
#if USE_OPENING
		{E_2D_OPENING,new COpeningTitle()},									//�J�n�f���p
#endif
	};	//���ʃ|���S��
	m_pCamera = new CFixedCamera();	//�Œ�J����

	// =============== ������ ===================
	//m_pCamera->SetRadius(START_RADIUS_CAMERA);	//���������ݒ�
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		// =============== ���� ===================
		if (m_p2dObj.find(nIdx) == m_p2dObj.end() || !m_p2dObj.at(nIdx))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
		{
			// =============== �I�� ===================
			continue;	//�����ΏۊO
		}
		if (MAP_POS.find(nIdx) != MAP_POS.end())	//map�̔z�񂪑��݂���Y����
		{
			m_p2dObj.at(nIdx)->SetPos({ MAP_POS.at(nIdx) });				//�ʒu������
		}
		if (MAP_TEXTURE.find(nIdx) != MAP_TEXTURE.end())	//map�̔z�񂪑��݂���Y����
		{
			m_p2dObj.at(nIdx)->SetTexture(MAP_TEXTURE.at(nIdx).c_str());	//�e�N�X�`���o�^
		}

		// =============== �J�����o�^ ===================
		m_p2dObj.at(nIdx)->SetCamera(m_pCamera);	//�J�����o�^
	}

	// =============== ��� ===================
	if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
		&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Selected();	//�I����ԑJ��
	}
#if !USE_OPENING	//�J�n�f�����Ȃ��ꍇ�����ɏk�����Ă�
	// =============== �k�� ===================
	if (m_p2dObj.find(E_2D_BACK) != m_p2dObj.end() && m_p2dObj.at(E_2D_BACK)
		&& typeid(CBgTitle) == typeid(*m_p2dObj.at(E_2D_BACK)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CBgTitle*>(m_p2dObj[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//�w�i�k���J�n
	}
	if (m_p2dObj.find(E_2D_LOGO) != m_p2dObj.end() && m_p2dObj.at(E_2D_LOGO)
		&& typeid(CTitleLogo) == typeid(*m_p2dObj.at(E_2D_LOGO)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		static_cast<CTitleLogo*>(m_p2dObj[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//���S�k���J�n
	}
#endif
	//===�T�E���h�t�@�C���ǂݍ���=====
	LoadSound();

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
		if (m_p2dObj.find(nIdx) != m_p2dObj.end() && m_p2dObj.at(nIdx))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
		{
			delete m_p2dObj.at(nIdx);	//�Ώۍ폜
			m_p2dObj.erase(nIdx);		//map����؏�
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
	if (m_p2dObj.find(E_2D_OPENING) != m_p2dObj.end() && m_p2dObj.at(E_2D_OPENING)
		&& typeid(COpeningTitle) == typeid(*m_p2dObj.at(E_2D_OPENING)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		if (!static_cast<COpeningTitle*>(m_p2dObj[E_2D_OPENING])->GetAnimFlg())
		{
			// =============== �I�� ===================
			delete m_p2dObj.at(E_2D_OPENING);	//�Ώۍ폜
			m_p2dObj.erase(E_2D_OPENING);		//map����؏�

			//// =============== �Y�[���A�E�g ===================
			//if (m_pCamera)	//�k���`�F�b�N
			//{
			//	m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);	//�Y�[���A�E�g�J�n
			//}

			// =============== �k�� ===================
			if (m_p2dObj.find(E_2D_BACK) != m_p2dObj.end() && m_p2dObj.at(E_2D_BACK)
				&& typeid(CBgTitle) == typeid(*m_p2dObj.at(E_2D_BACK)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CBgTitle*>(m_p2dObj[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//�w�i�k���J�n
			}
			if (m_p2dObj.find(E_2D_LOGO) != m_p2dObj.end() && m_p2dObj.at(E_2D_LOGO)
				&& typeid(CTitleLogo) == typeid(*m_p2dObj.at(E_2D_LOGO)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CTitleLogo*>(m_p2dObj[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//���S�k���J�n
			}
		}
		else
		{
			// =============== �X�V ===================
			m_p2dObj[E_2D_OPENING]->Update();	//�A�j���X�V

			// =============== �I�� ===================
			return;	//����ȏ�X�V���Ȃ�
		}
	}

	// =============== ���͎�t ===================
	if (!(m_ucFlag & E_FLAG_TIDYING_UP))	//�Еt�����łȂ�
	{
		// =============== �R���g���[�� ==================
		if (GetUseVController())	// �R���g���[�����ڑ�����Ă���ꍇ
		{
			// =============== �J�[�\���ړ� ===================
			if (IsStickLeft().y < 0)		//�����͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Selected();	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_CONTINUE);								//��̃R�}���h�̗p
					}
				}
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->UnSelected();	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�s�̗p

						//===== SE�̍Đ� =======
						PlaySE(SE_CHOOSE);
					}
				}

			}
			if (IsStickLeft().y > 0)	//�����͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->Selected();	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�̗p
					}
				}
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->UnSelected();	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_CONTINUE);									//��̃R�}���h�s�̗p

						//===== SE�̍Đ� =======
						PlaySE(SE_CHOOSE);
					}
				}

			}

			// =============== ���� ===================
			if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START))
				&& m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//�\����
				{
					if (IsKeyTriggerController(BUTTON_B))	//B�{�^�����͎�
					{
						// =============== �t���O���� ===================
						UpFlag(E_FLAG_DECIDE_COMMAND);	//����

						//===== SE�̍Đ� =======
						PlaySE(SE_DECISION);
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
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Selected();	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_CONTINUE);								//��̃R�}���h�̗p
					}
				}
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->UnSelected();	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�s�̗p

						//===== SE�̍Đ� =======
						PlaySE(SE_CHOOSE);
					}
				}

			}
			if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//���ES���͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->Selected();	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�̗p
					}
				}
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//�\����
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->UnSelected();	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_CONTINUE);									//��̃R�}���h�s�̗p
						//===== SE�̍Đ� =======
						PlaySE(SE_CHOOSE);
					}
				}

			}

			// =============== ���� ===================
			if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START))
				&& m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
				{
				if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//�\����
				{
					if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE))	//Enter�ESpace���͎�
					{
						// =============== �t���O���� ===================
						UpFlag(E_FLAG_DECIDE_COMMAND);	//����

						//===== SE�̍Đ� =======
						PlaySE(SE_DECISION);
					}
				}
			}
		}
	}

	// =============== �I���m�� ===================
	if (m_ucFlag & E_FLAG_DECIDE_COMMAND)	//�R�}���h���莞
	{
		// =============== �I����Ԕ��� ===================
		if (m_ucFlag & E_FLAG_COMMAND_CONTINUE)	//�p��
		{
			// =============== ��ԑJ�� ===================
			if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Decide();	//�����ԑJ��
			}

			m_bFinish = true;					//�V�[���̏I���\��
			m_eNextScene = E_TYPE_SELECT_STAGE;	//�X�e�[�W�I����
			DownFlag(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH)	//�I��
		{
			// =============== ��ԑJ�� ===================
			if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
			{
				static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->Decide();	//�����ԑJ��
			}
			m_bFinish = true;					//�V�[���̏I���\��
			m_eNextScene = E_TYPE_FINISH_ALL;	//�A�v���I��
			DownFlag(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
	}



	// =============== �X�V ===================
	if (m_pCamera)	//�k���`�F�b�N
	{
		m_pCamera->Update();	//�J�����X�V
	}
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		if (m_p2dObj.find(nIdx) != m_p2dObj.end() && m_p2dObj.at(nIdx))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
		{
			m_p2dObj.at(nIdx)->Update();	//�X�V�Ώ�
		}
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
		if (m_p2dObj.find(nIdx) != m_p2dObj.end() && m_p2dObj.at(nIdx))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
		{
			m_p2dObj.at(nIdx)->Draw();	//�`��Ώ�
		}
	}
}

/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g���^�C�g���V�[���ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CTitle::E_TYPE CTitle::GetType() const
{
	// =============== �� ===================
	return CTitle::E_TYPE_TITLE;	//���g�̎��
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

/* ========================================
	�t���O�I���֐�
	-------------------------------------
	���e�F�����ɑΉ������t���O���N����
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag�F�Ώۃt���O
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitle::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag |= ucBitFlag;	//�t���O����
}

/* ========================================
	�t���O�I�t�֐�
	-------------------------------------
	���e�F�����ɑΉ������t���O���~�낷
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag�F�Ώۃt���O
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitle::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag &= (ucBitFlag ^ 0xFF);	//�t���O����
}

/* ========================================
	�t���O�X�C�b�`�֐�
	-------------------------------------
	���e�F�����ɑΉ������t���O�̔��]
	-------------------------------------
	����1�Fconst unsigned char & ucBitFlag�F�Ώۃt���O
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitle::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag ^= ucBitFlag;	//�t���O����
}

/* ========================================
   �^�C�g���pSE�ǂݍ��݊֐�
   ----------------------------------------
   ���e�F�^�C�g���p��SE�̃t�@�C����ǂݍ���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CTitle::LoadSound()
{
	//SE�̓ǂݍ���
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}
}

/* ========================================
	SE�̍Đ��֐�
	----------------------------------------
	���e�FSE�̍Đ�
	----------------------------------------
	����1�FSE�̎��(enum)
	����2�F����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTitle::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE�Đ�
	m_pSESpeaker[se]->SetVolume(volume);				//���ʂ̐ݒ�
}