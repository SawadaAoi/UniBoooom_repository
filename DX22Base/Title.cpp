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
	�E2024/01/29 �w�i�ύX takagi
	�E2024/02/02 ���t�@�N�^�����O takagi
	�E2024/02/05 ���t�@�N�^�����O takagi
	�E2024/02/06 ���t�@�N�^�����O takagi
	�E2024/02/09 GetType()�֐��폜�EUsingCamera�g�p takagi
	�E2024/02/09 GetType()�֐��폜 takagi
	�E2024/02/12 �e�N�X�`���Ǘ��@�ύX�ɔ����C�� takagi
	�E2024/02/13 �R�}���h�I�����̃o�O�C�� takagi
	�E2024/02/16 ��s���͖h�~ takagi
	
========================================== */

// =============== �C���N���[�h ===================
#include "Title.h"				//���g�̃w�b�_
#include "Input.h"				//���͎�t
#include "TitleInitCounter.h"	//�����J�E���^
#include "FixedCamera.h"		//�C���X�^���X���
#include "UsingCamera.h"		//�J�����g�p

// =============== �萔�E�}�N����` ===================
const float START_RADIUS_CAMERA = 0.5f;						//�����J��������
const float END_RADIUS_CAMERA = 15.0f;						//�ŏI�J��������
#define PTR_UPDATE(ptr) do{if(ptr){ptr->Update();}}while(0)	//�k���`�F�b�N�E�X�V
#define PTR_DRAW(ptr) do{if(ptr){ptr->Draw();}}while(0)		//�k���`�F�b�N�E�`��

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
	:m_ucFlag(E_FLAG_COMMAND_START)	//�t���O
	, m_pSE{ nullptr,nullptr}
	, m_pSESpeaker{ nullptr ,nullptr}
{
	// =============== �����_���[ ===================
	RenderTarget*  p = GetDefaultRTV();	//2D�`��p�����_���[
	SetRenderTargets(1, &p, nullptr);	//2D�`��p�����_���[�Z�b�g

	// =============== ���I�m�� ===================
	m_pLogo = std::make_shared<CTitleLogo>();		//�^�C�g�����S
	m_pBgBase = std::make_shared<CTitleBgBase>();	//�w�i
	m_pBgCloud = std::make_shared<CTitleBgCloud>();	//�w�i�̉_
	m_pBgGrass = std::make_shared<CTitleBgGrass>();	//�w�i�̑�
	m_pMainCamera = std::make_shared<CFixedCamera>();	//�Œ�J����
	m_pCommandStart = std::make_shared<CTitleCommandStart>();	//�J�n�R�}���h
	m_pCommandFinish = std::make_shared<CTitleCommandFinish>();	//�I���R�}���h
	m_pBgPlayer = std::make_shared<CTitleBgPlayer>();			//�w�i�̃v���C���[

	// =============== �J�����o�^ ===================
	CUsingCamera::GetThis().SetCamera(m_pMainCamera);	//�J�����o�^

	// =============== �A�j���[�V�����J�n ===================
	CTitleInitCounter::GetThis().StartCount();	//�J�E���g�J�n

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
	// =============== �ϐ��錾 ===================
	auto pCounter = CTitleInitCounter::GetThis().GetCounter().lock();	//�J�E���^

	// =============== �j�� ===================
	if (m_pBgPlayer && !m_pBgPlayer->GetAnimFlg())	//�k���`�F�b�N�E�A�j���[�V��������
	{
		m_pBgPlayer.reset();	//�폜
	}

	// =============== ���͎�t ===================
	if (!pCounter || pCounter->IsFin())	//�k���E���ԃ`�F�b�N
	{
		if (GetUseVController())	// �R���g���[�����ڑ�����Ă���ꍇ
		{
			// =============== �J�[�\���ړ� ===================
			if (IsStickLeft().y < 0)		//�����͎�
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_START))	//���ɊJ�n�R�}���h��I�����Ă��Ȃ�
				{
					// =============== ��ԑJ�� ===================
					if (m_pCommandStart)	//�k���`�F�b�N
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_SELECTED);	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_START);									//��̃R�}���h�̗p
					}
					if (m_pCommandFinish)	//�k���`�F�b�N
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�s�̗p
					}
					//===== SE�̍Đ� =======
					PlaySE(SE_CHOOSE);
				}
			}
			if (IsStickLeft().y > 0)	//�����͎�
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_FINISH))	//���ɏI���R�}���h��I�����Ă��Ȃ�
				{
					// =============== ��ԑJ�� ===================
					if (m_pCommandFinish)	//�k���`�F�b�N
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_SELECTED);	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�̗p
					}
					if (m_pCommandStart)	//�k���`�F�b�N
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_START);										//��̃R�}���h�s�̗p
					}
					//===== SE�̍Đ� =======
					PlaySE(SE_CHOOSE);
				}
			}

			// =============== ���� ===================
			if (IsKeyTriggerController(BUTTON_B) || IsKeyTriggerController(BUTTON_Y) && !(m_ucFlag & E_FLAG_DECIDE_COMMAND))	//B�{�^�����͂��񌈒莞
			{
				// =============== �I����Ԕ��� ===================
				if (m_ucFlag & E_FLAG_COMMAND_START && m_pCommandStart)	//�J�n�R�}���h�E�k���`�F�b�N
				{
					// =============== ��ԑJ�� ===================
					m_pCommandStart->ChangeState(CTitleCommand::E_STATE_DECIDE);	//�����ԑJ��

					// =============== �t���O���� ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//����

					//===== SE�̍Đ� =======
					PlaySE(SE_DECISION);
				}
				if (m_ucFlag & E_FLAG_COMMAND_FINISH && m_pCommandFinish)	//�I���R�}���h�E�k���`�F�b�N
				{
					// =============== ��ԑJ�� ===================
					m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_DECIDE);	//�����ԑJ��

					// =============== �t���O���� ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//����

					//===== SE�̍Đ� =======
					PlaySE(SE_DECISION);
				}
			}
		}
		else
		{//�L�[�{�[�h����
			// =============== �J�[�\���ړ� ===================
			if (IsKeyTrigger(VK_UP) || IsKeyTrigger('W'))	//���EW���͎�
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_START))	//���ɊJ�n�R�}���h��I�����Ă��Ȃ�
				{
					// =============== ��ԑJ�� ===================
					if (m_pCommandStart)	//�k���`�F�b�N
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_SELECTED);	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_START);									//��̃R�}���h�̗p
					}
					if (m_pCommandFinish)	//�k���`�F�b�N
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�s�̗p
					}
					//===== SE�̍Đ� =======
					PlaySE(SE_CHOOSE);
				}
			}
			if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//���ES���͎�
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_FINISH))	//���ɏI���R�}���h��I�����Ă��Ȃ�
				{
					// =============== ��ԑJ�� ===================
					if (m_pCommandFinish)	//�k���`�F�b�N
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_SELECTED);	//�I����ԑJ��
						UpFlag(E_FLAG_COMMAND_FINISH);									//���̃R�}���h�̗p
					}
					if (m_pCommandStart)	//�k���`�F�b�N
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//�I����ԑJ��
						DownFlag(E_FLAG_COMMAND_START);										//��̃R�}���h�s�̗p
					}
					//===== SE�̍Đ� =======
					PlaySE(SE_CHOOSE);
				}
			}

			// =============== ���� ===================
			if ((IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)) && !(m_ucFlag & E_FLAG_DECIDE_COMMAND))	//Enter�ESpace���͂��񌈒莞
			{
				// =============== �I����Ԕ��� ===================
				if (m_ucFlag & E_FLAG_COMMAND_START && m_pCommandStart)	//�J�n�R�}���h�E�k���`�F�b�N
				{
					// =============== ��ԑJ�� ===================
					m_pCommandStart->ChangeState(CTitleCommand::E_STATE_DECIDE);	//�����ԑJ��

					// =============== �t���O���� ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//����

					//===== SE�̍Đ� =======
					PlaySE(SE_DECISION);
				}
				if (m_ucFlag & E_FLAG_COMMAND_FINISH && m_pCommandFinish)	//�I���R�}���h�E�k���`�F�b�N
				{
					// =============== ��ԑJ�� ===================
					m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_DECIDE);	//�����ԑJ��

					// =============== �t���O���� ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//����

					//===== SE�̍Đ� =======
					PlaySE(SE_DECISION);
				}
			}
		}
	}

	// =============== �I���m�� ===================
	if (m_ucFlag & E_FLAG_DECIDE_COMMAND)	//�R�}���h���莞
	{
		// =============== �I����Ԕ��� ===================
		if (m_ucFlag & E_FLAG_COMMAND_START && m_pCommandStart && m_pCommandStart->DesideAnimeFin())	//�J�n�R�}���h�E�k���`�F�b�N�E�A�j���Đ�����
		{
			// =============== �����Ԕ��f ===================
			m_bFinish = true;					//�V�[���̏I���\��
			m_eNextScene = E_TYPE_SELECT_STAGE;	//�X�e�[�W�I����
			DownFlag(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH && m_pCommandFinish && m_pCommandFinish->DesideAnimeFin())	//�I���R�}���h�E�k���`�F�b�N�E�A�j���Đ�����
		{
			// =============== �����Ԕ��f ===================
			m_bFinish = true;					//�V�[���̏I���\��
			m_eNextScene = E_TYPE_FINISH_ALL;	//�A�v���I��
			DownFlag(E_FLAG_DECIDE_COMMAND);	//���菈������
		}
	}

	// =============== �X�V ===================
	CTitleInitCounter::GetThis().Update();	//�J�E���^�X�V
	PTR_UPDATE(m_pBgBase);					//�w�i�X�V
	PTR_UPDATE(m_pBgCloud);					//�_�X�V
	if (!pCounter || pCounter->IsFin())	//�k���E���ԃ`�F�b�N
	{
		PTR_UPDATE(m_pBgPlayer);			//�v���C���[�X�V
	}
	PTR_UPDATE(m_pBgGrass);					//�����X�V
	if (!pCounter || pCounter->IsFin())	//�k���E���ԃ`�F�b�N
	{
		PTR_UPDATE(m_pCommandStart);		//�J�n�R�}���h�X�V
		PTR_UPDATE(m_pCommandFinish);		//�I���R�}���h�X�V
	}
	PTR_UPDATE(m_pLogo);					//�^�C�g�����S�X�V
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
	// =============== �ϐ��錾 ===================
	auto pCounter = CTitleInitCounter::GetThis().GetCounter().lock();	//�J�E���^

	// =============== �`�� ===================
	PTR_DRAW(m_pBgBase);		//�w�i�`��
	PTR_DRAW(m_pBgCloud);		//�_�`��
	if (!pCounter || pCounter->IsFin())	//�k���E���ԃ`�F�b�N
	{
	PTR_DRAW(m_pBgPlayer);		//�v���C���[�`��
	}
	PTR_DRAW(m_pBgGrass);		//�����`��
	if (!pCounter || pCounter->IsFin())	//�k���E���ԃ`�F�b�N
	{
		PTR_DRAW(m_pCommandStart);	//�J�n�R�}���h�`��
		PTR_DRAW(m_pCommandFinish);	//�I���R�}���h�`��
	}
	PTR_DRAW(m_pLogo);			//�^�C�g�����S�`��
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