/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��ʎ���
	---------------------------------------
	Pause.cpp
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/01 ���� takagi
	�E2023/12/04 ���� takagi
	�E2023/12/05 ���� takagi
	�E2023/12/06 pose��pause�C���A�|�[�Y�����\�� takagi
	�E2023/12/08 �X�V��������i�s takagi
	�E2023/12/09 �I�u�W�F�N�g���� takagi
	�E2023/12/10 ����i�s takagi
	�E2023/12/12 �X�^�[�g�{�^���̓��͔��f sawada
	�E2023/12/12 �^�`�F�b�N�C�� takagi
	�E2023/12/17 �Q�[���p�����[�^������ takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Pause.h"			//���g�̃w�b�_
#include <map>				//�֌W���R���e�i
#include <array>			//�z��
#include "CameraDef.h"		//�^���J����
#include "Input.h"			//�L�[����
#include "CharPause.h"		//�C���X�^���X���
#include "BgPause.h"		//�C���X�^���X���
#include "CommandPause.h"	//�C���X�^���X���

// =============== �񋓌^��` ===================
enum E_2D
{
	E_2D_BACK,		//�w�i
	E_2D_PA,		//�|�[�Y�́h�|�h
	E_2D_U,			//�|�[�Y�́h�[�h
	E_2D_SE,		//�|�[�Y�́h�Y�h
	E_2D_CONTINUE,	//�p���R�}���h
	E_2D_FINISH,	//�I���R�}���h
	E_2D_MAX,		//�v�f��
};	//2D�̃I�u�W�F�N�g
enum E_COMMAND
{
	E_COMMAND_CONTINUE,	//�Q�[���𑱂���
	E_COMMAND_FINISH,	//�Q�[������߂�
	E_COMMAND_MAX,		//�v�f��
};	//�R�}���h����
enum E_SHADER_TYPE
{
	E_SHADER_TYPE_VERTEX,	//���_�V�F�[�_�[
	E_SHADER_TYPE_PIXEL,	//�s�N�Z���V�F�[�_�[
	E_SHADER_TYPE_MAX,		//�v�f��
};	//�V�F�[�_�[�̎��

// =============== �萔��` ===================
const float COMMAND_SPACE_HALF = 85.0f;	//�R�}���h���m�̏c�̊�
const float CHARA_Y = 620.0f;			//�|�[�Y�\�L�����Sy�ʒu
const float CHARA_SPACE = 85.0f;		//�|�[�Y�\�L�̉��̊�
const float CHARA_WIDTH = 100.0f;		//�|�[�Y�\�L����
const float CHARA_HEIGHT = 100.0f;		//�|�[�Y�\�L�c��
const std::map<int, int> MAP_WAIT_START = {	//�X�V��
	{E_2D_BACK, 0},		//�w�i
	{E_2D_PA, 0},		//�|�[�Y�́h�|�h
	{E_2D_U, 15},		//�|�[�Y�́h�[�h
	{E_2D_SE, 30},		//�|�[�Y�́h�Y�h
	{E_2D_CONTINUE, 15},	//�p���R�}���h
	{E_2D_FINISH, 30},	//�I���R�}���h
};	//�|���S���ƕ\���J�n�ҋ@���Ԃ̑Ή��\
const std::map<int, int> MAP_WAIT_FIN = {	//�X�V��
	{E_2D_BACK, 30},		//�w�i
	{E_2D_PA, 30},		//�|�[�Y�́h�|�h
	{E_2D_U, 15},		//�|�[�Y�́h�[�h
	{E_2D_SE, 0},		//�|�[�Y�́h�Y�h
	{E_2D_CONTINUE, 15},	//�p���R�}���h
	{E_2D_FINISH, 30},	//�I���R�}���h
};	//�|���S���ƕ\���I���ҋ@���Ԃ̑Ή��\
const std::map<int, std::string> MAP_TEXTURE = {	//�X�V��
	{E_2D_BACK, "Assets/Texture/Pause/PauseBg.png"},			//�w�i
	{E_2D_PA, "Assets/Texture/Pause/Pause_po.png"},				//�|�[�Y�́h�|�h
	{E_2D_U, "Assets/Texture/Pause/Pause_-.png"},				//�|�[�Y�́h�[�h
	{E_2D_SE, "Assets/Texture/Pause/Pause_zu.png"},				//�|�[�Y�́h�Y
	{E_2D_CONTINUE, "Assets/Texture/Pause/Pause_Continue.png"},	//�p���R�}���h
	{E_2D_FINISH, "Assets/Texture/Pause/Pause_Finish.png"},		//�I���R�}���h
};	//�|���S���ƃe�N�X�`���̑Ή��\
const std::map<int, TPos3d<float>> MAP_POS = {	//�X�V��
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},								//�w�i
	{E_2D_PA, {static_cast<float>(SCREEN_WIDTH) / 2.0f - CHARA_SPACE, CHARA_Y, 0.0f}},													//�|�[�Y�́h�|�h
	{E_2D_U, {static_cast<float>(SCREEN_WIDTH) / 2.0f, CHARA_Y, 0.0f}},																	//�|�[�Y�́h�[�h
	{E_2D_SE, {static_cast<float>(SCREEN_WIDTH) / 2.0f + CHARA_SPACE, CHARA_Y, 0.0f}},													//�|�[�Y�́h�Y�h
	{E_2D_CONTINUE, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f + COMMAND_SPACE_HALF, 0.0f}},	//�p���R�}���h
	{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f - COMMAND_SPACE_HALF, 0.0f}},		//�I���R�}���h
};	//�|���S���Ə������W�̑Ή��\

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�Fconst CCamera* pCamera�F�J�����̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CPause::CPause(const CCamera* pCamera)
	:m_ucFlag(0x00)			//�t���O
{	
	// =============== ������ ===================
	m_pCamera = pCamera;	//�J����������
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
CPause::~CPause()
{	
	// =============== �I�� ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.end(); Iterator != m_p2dObj.begin();)
	{
		if (*(--Iterator))	//�k���`�F�b�N
		{
			delete (*Iterator);					//���������
		}
		Iterator = m_p2dObj.erase(Iterator);	//�C�e���[�^�폜�E�ړ�
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
void CPause::Update()
{
	if (!(m_ucFlag & E_FLAG_TIDYING_UP))	//�Еt�����łȂ�
	{
		// =============== �R���g���[�� ==================
		if (GetUseVController())	// �R���g���[�����ڑ�����Ă���ꍇ
		{
			// =============== �N���E�I�� ===================
			if (IsKeyTriggerController(BUTTON_START))
			{
				if (IsPause())	//���łɃ|�[�Y��
				{
					Destroy();	//�I��
				}
				else
				{
					Boot();		//�N��
				}
			}

			// =============== ���� ===================
			if (!IsPause())	//�|�[�Y���łȂ�
			{
				// =============== �I�� ===================
				return;	//�������f
			}

			// =============== �J�[�\���ړ� ===================
			if (IsStickLeft().y < 0)		//�����͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObj[E_2D_CONTINUE] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_CONTINUE]))	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_CONTINUE])->Selected();	//�I����ԑJ��
				}
				if (m_p2dObj[E_2D_FINISH] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_FINISH]))	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_FINISH])->UnSelected();	//�I����ԑJ��
				}

				// =============== �t���O���� ===================
				UpFlag(E_FLAG_COMMAND_CONTINUE);	//��̃R�}���h�̗p
				DownFlag(E_FLAG_COMMAND_FINISH);	//���̃R�}���h�s�̗p
			}
			if (IsStickLeft().y > 0)	//�����͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObj[E_2D_FINISH] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_FINISH]))	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_FINISH])->Selected();	//�I����ԑJ��
				}
				if (m_p2dObj[E_2D_CONTINUE] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_CONTINUE]))	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_CONTINUE])->UnSelected();	//�I����ԑJ��
				}
				// =============== �t���O���� ===================
				UpFlag(E_FLAG_COMMAND_FINISH);		//���̃R�}���h�̗p
				DownFlag(E_FLAG_COMMAND_CONTINUE);	//��̃R�}���h�s�̗p
			}

			// =============== ���� ===================
			if (IsKeyTriggerController(BUTTON_B))	//A�{�^�����͎�
			{
				// =============== �t���O���� ===================
				UpFlag(E_FLAG_DECIDE_COMMAND);	//����
			}
		}
		else
		{
			// =============== �N���E�I�� ===================
			if (IsKeyTrigger('P'))
			{
				if (IsPause())	//���łɃ|�[�Y��
				{
					Destroy();	//�I��
				}
				else
				{
					Boot();		//�N��
				}
			}

			// =============== ���� ===================
			if (!IsPause())	//�|�[�Y���łȂ�
			{
				// =============== �I�� ===================
				return;	//�������f
			}

			// =============== �J�[�\���ړ� ===================
			if (IsKeyTrigger(VK_UP) || IsKeyTrigger('W'))		//���EW���͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObj[E_2D_CONTINUE] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_CONTINUE]))	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_CONTINUE])->Selected();	//�I����ԑJ��
				}
				if (m_p2dObj[E_2D_FINISH] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_FINISH]))	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_FINISH])->UnSelected();	//�I����ԑJ��
				}

				// =============== �t���O���� ===================
				UpFlag(E_FLAG_COMMAND_CONTINUE);	//��̃R�}���h�̗p
				DownFlag(E_FLAG_COMMAND_FINISH);	//���̃R�}���h�s�̗p
			}
			if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//���ES���͎�
			{
				// =============== ��ԑJ�� ===================
				if (m_p2dObj[E_2D_FINISH])	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_FINISH])->Selected();	//�I����ԑJ��
				}
				if (m_p2dObj[E_2D_CONTINUE])	//�k���`�F�b�N�A�^�`�F�b�N
				{
					static_cast<CCommandPause*>(m_p2dObj[E_2D_CONTINUE])->UnSelected();	//�I����ԑJ��
				}
				// =============== �t���O���� ===================
				UpFlag(E_FLAG_COMMAND_FINISH);		//���̃R�}���h�̗p
				DownFlag(E_FLAG_COMMAND_CONTINUE);	//��̃R�}���h�s�̗p
			}

			// =============== ���� ===================
			if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE))	//Enter�ESpace���͎�
			{
				// =============== �t���O���� ===================
				UpFlag(E_FLAG_DECIDE_COMMAND);	//����
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
			if (m_p2dObj[E_2D_CONTINUE] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_CONTINUE]))	//�k���`�F�b�N�A�^�`�F�b�N
			{
				static_cast<CCommandPause*>(m_p2dObj[E_2D_CONTINUE])->Decide();	//�����ԑJ��
			}
			Destroy();							//�|�[�Y�𒆒f���A�Q�[�����ĊJ����
			DownFlag(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH)	//�I��
		{
			// =============== ��ԑJ�� ===================
			if (m_p2dObj[E_2D_FINISH] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_FINISH]))	//�k���`�F�b�N�A�^�`�F�b�N
			{
				static_cast<CCommandPause*>(m_p2dObj[E_2D_FINISH])->Decide();	//�����ԑJ��
			}
			Destroy();							//�|�[�Y�𒆒f����
			DownFlag(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
	}

	// =============== �ϐ��錾 ===================
	int nCnt = 0;	//���[�v�J�E���g�p

	// =============== �X�V ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); )
	{
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			if (*Iterator)	//�k���`�F�b�N
			{
				(*Iterator)->Update();						//���ʕ`��
				if ((*Iterator)->IsDestroyed())	//�j�����Ă��ǂ��Ƃ�
				{
					delete(*Iterator);						//���������
					Iterator = m_p2dObj.erase(Iterator);	//�C�e���[�^�폜
				}
				else
				{
					Iterator++;								//�C�e���[�^�␳
				}
			}
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
	}

	// =============== �|�[�Y���� ===================
	if (0 == m_p2dObj.size())	//�I�u�W�F�N�g������
	{
		// =============== �t���O���� ===================
		if (m_ucFlag & E_FLAG_COMMAND_FINISH)	//��߂�ꍇ
		{
			DownFlag(0xFF);				//�t���O������
			UpFlag(E_FLAG_CALL_FINISH);	//�Q�[���̏I���\���̂ݎc��
		}
		else
		{
			DownFlag(0xFF);	//�t���O������
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
void CPause::Draw()
{
	// =============== ���[�h���� ===================
	if (!(m_ucFlag & E_FLAG_PAUSEMODE))	//�|�[�Y���[�h�̃t���O�������Ă��Ȃ�
	{
		// =============== �I�� ==================
		return;	//�������f
	}

	// =============== �ϐ��錾 ===================
	int nCnt = 0;	//���[�v�J�E���g�p
	RenderTarget*  p = GetDefaultRTV();
	SetRenderTargets(1, &p , nullptr);

	// =============== �`�� ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			if (*Iterator)	//�k���`�F�b�N
			{
				(*Iterator)->Draw();	//���ʕ`��
			}
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
	}
	SetRenderTargets(1, &p, GetDefaultDSV());
}

/* ========================================
	�I�������֐�
	----------------------------------------
	���e�F�I���t���O�̒l��Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
bool CPause::IsFin() const
{
	// =============== �� ===================
	return (m_ucFlag & E_FLAG_CALL_FINISH);	//�I���t���O
}

/* ========================================
	�J�����o�^�֐�
	----------------------------------------
	���e�Fnullptr�łȂ��J�����̃A�h���X���󂯎��g�p����B
	----------------------------------------
	����1�Fconst CCamera * pCamera�F�J�����̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CPause::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	�|�[�Y����֐�
	----------------------------------------
	���e�F�|�[�Y�����ǂ�����Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
bool CPause::IsPause() const
{
	// =============== �� ===================
	return (m_ucFlag & E_FLAG_PAUSEMODE);	//�|�[�Y���[�h�t���O�������Ă��邩
}

/* ========================================
	�N���֐�
	----------------------------------------
	���e�F�|�[�Y���[�h���N������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CPause::Boot()
{
	// =============== �t���O���� ===================
	UpFlag(E_FLAG_PAUSEMODE | E_FLAG_COMMAND_CONTINUE);	//�|�[�Y�J�n
	InitObjects();										//�I�u�W�F�N�g������
}

/* ========================================
	�����o�[�������֐�
	----------------------------------------
	���e�F�����o�[�̃I�u�W�F�N�g�𓮓I�m�ہE����������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CPause::InitObjects()
{
	// =============== �ϐ��錾 ===================
	int nCnt = 0;	//���[�v�J�E���g�p

	// =============== ���I�m�� ===================
	m_p2dObj = {	//�X�V��
		new CBgPause(MAP_WAIT_START.at(E_2D_BACK)),				//�w�i�p
		new CCharPause(MAP_WAIT_START.at(E_2D_PA)),				//�|�̎��p
		new CCharPause(MAP_WAIT_START.at(E_2D_U)),				//�[�̎��p
		new CCharPause(MAP_WAIT_START.at(E_2D_SE)),				//�Y�̎��p
		new CCommandPause(MAP_WAIT_START.at(E_2D_CONTINUE)),	//�p���R�}���h�p
		new CCommandPause(MAP_WAIT_START.at(E_2D_FINISH)),		//�I���R�}���h�p
	};	//���ʃ|���S��

	// =============== ������ ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); Iterator++)
	{
		if (MAP_POS.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetReach({ MAP_POS.at(nCnt) });	//�ʒu������
		}
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			(*Iterator)->SetTexture(MAP_TEXTURE.at(nCnt).c_str());	//�e�N�X�`���o�^
		}

		// =============== �J�����o�^ ===================
		(*Iterator)->SetCamera(m_pCamera);	//�J�����o�^

		// =============== ��� ===================
		if (m_p2dObj[E_2D_CONTINUE] && typeid(CCommandPause) == typeid(*m_p2dObj[E_2D_CONTINUE]))	//�k���`�F�b�N�A�^�`�F�b�N
		{
			static_cast<CCommandPause*>(m_p2dObj[E_2D_CONTINUE])->Selected();	//�I����ԑJ��
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
	}
}

/* ========================================
	�I���֐�
	----------------------------------------
	���e�F�|�[�Y���[�h���I������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CPause::Destroy()
{
	// =============== �ϐ��錾 ===================
	int nCnt = 0;	//���[�v�J�E���g�p

	// =============== �X�V ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//map�̔z�񂪑��݂���Y����
		{
			if (*Iterator)
			{
				(*Iterator)->Destroy(MAP_WAIT_FIN.at(nCnt));	//���ʕ`��
			}
		}

		// =============== �J�E���^ ===================
		nCnt++;	//�J�E���g�i�s
	}

	// =============== �t���O���� ===================
	UpFlag(E_FLAG_TIDYING_UP);	//�|�[�Y�`��n�Еt����
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
void CPause::UpFlag(const unsigned char & ucBitFlag)
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
void CPause::DownFlag(const unsigned char & ucBitFlag)
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
void CPause::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== ��� ===================
	m_ucFlag ^= ucBitFlag;	//�t���O����
}