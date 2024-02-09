/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���Ǘ�����
	---------------------------------------
	SceneManager.cpp
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/24 ������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �V�[���J�ڂ̗�������� takagi
	�E2023/11/17 �ߋ��V�[���ɖ߂鏈����ǉ��E�L�[���͂ŃV�[����؂�ւ�����f�o�b�O���[�h�ǉ� takagi
	�E2023/11/23 �t�F�[�h�E�q�b�g�X�g�b�v�@�\�ǉ� takagi
	�E2023/11/27 �t�F�[�h�{���� takagi
	�E2023/11/29 �q�b�g�X�g�b�v�̎d�l�ύX�ɑΉ� takagi
	�E2023/12/01 �t�F�[�h�̎d�l�ύX takagi
	�E2023/12/12 �ŏ��̃V�[�����^�C�g���ɕύX takagi
	�E2023/12/14 BGM�̊Ǘ���Scene������ړ� yamashita
	�E2023/12/14 BGM�p�̒萔��` yamashita
	�E2023/12/14 BGM���t�F�[�h����悤�ɕύX yamashita
	�E2023/12/15 �A�v���I������ takagi
	�E2024/01/18 CScene->GetType()�֐����g�p���Ȃ��`�ɕύX�Ȃǃ��t�@�N�^�����O takagi
	�E2024/01/20 ���֌W���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C�Ebgm�o�O�C���EMessageBox���P takagi
	�E2024/01/25 �I�u�W�F�N�g�`�F�b�N�ǉ�
	�E2024/02/09 �J�����폜 takagi

========================================== */

// =============== �f�o�b�O���[�h ===================
#if _DEBUG
#define KEY_CHANGE_SCENE (true)	//�L�[���͂ŃV�[����ς���
#endif

// =============== �C���N���[�h ===================
#include "SceneManager.h"	//���g�̃w�b�_
#include "HitStop.h"		//�q�b�g�X�g�b�v
#if _DEBUG
#include <Windows.h>		//���b�Z�[�W�{�b�N�X�p
#endif
#if KEY_CHANGE_SCENE
#include <string>			//�����񑀍�
#include "Input.h"			//�L�[����
#endif

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CSceneManager::CSceneManager()
	:m_pScene(nullptr)					//�V�[��
	, m_ePastScene(CScene::E_TYPE_NONE)	//�O�̃V�[��
	, m_eNextScene(CScene::E_TYPE_TITLE)	//�V�[���J�ڐ�
	, m_pFade(nullptr)					//�t�F�[�h
	, m_pBGMSpeaker(nullptr)				//BGM�𕷂���鑤
{
	// =============== ���I�m�� ===================
	if (!m_pScene)	//�k���`�F�b�N
	{
		ChangeScene();	//�ŏ��Ɏn�߂�V�[���쐬
	}
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
CSceneManager::~CSceneManager()
{
	// =============== �I�� ===================
	SAFE_DELETE(m_pScene);			//�V�[���폜
	SAFE_DELETE(m_pFade);			//�t�F�[�h�폜
	UNLOAD_SOUND(m_pBGMSpeaker);	//BGM�̍Đ����~���A���̉��f�[�^�̕R�Â���j��		�����̂Ƃ����g�̃|�C���^�[���f�[�^�������Ȃ��ƃG���[�ƂȂ�
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
void CSceneManager::Update()
{
#if KEY_CHANGE_SCENE
	for (int nIdx = 0; nIdx < CScene::E_TYPE_MAX; nIdx++)
	{
		if (nIdx < 10)	//�L�[���͂ł���͈�
		{
			//Shift���͒��ɐ����������Ƃ��̐����̃V�[���Ɉڂ�
			if (IsKeyPress(VK_SHIFT) & IsKeyTrigger(*std::to_string(nIdx).c_str()))	//shift�������Ȃ���V�[���ԍ������͂��ꂽ
			{
				m_eNextScene = static_cast<CScene::E_TYPE>(nIdx);	//�ړ���V�[���o�^
				delete m_pScene;									//���������
				m_pScene = nullptr;									//��A�h���X���
				ChangeScene();										//�V�[���ύX
			}
		}
	}
#endif

	// =============== �q�b�g�X�g�b�v ===================
	CHitStop::Update();	//�q�b�g�X�g�b�v�X�V

	// =============== �V�[���؊� ===================
	if (m_pFade)	//�k���`�F�b�N
	{
		if (!m_pFade->IsFade())	//�t�F�[�h����
		{
			if (m_UcFlag.Check(E_BIT_FLAG_START_FADE_OUT))	//�t�F�[�h�A�E�g���J�n���Ă����Ƃ�
			{
				ChangeScene();								//�V�[���ύX
				m_UcFlag.Down(E_BIT_FLAG_START_FADE_OUT);	//���̃t���O�͖�ڂ��I����
			}
		}
	}

	// =============== �X�V ===================
	if (m_pScene)	//�k���`�F�b�N
	{
		if (m_pScene->IsFin())	//�V�[���I������
		{
			// =============== �t�F�[�h ===================
			if (m_pFade)	//�k���`�F�b�N
			{
				if (!m_pFade->IsFadeOut())
				{
					m_pFade->Start();						//�t�F�[�h�J�n
					m_UcFlag.Up(E_BIT_FLAG_START_FADE_OUT);	//�t�F�[�h�A�E�g���J�n
				}
			}
		}
		else
		{
			// =============== �t�F�[�h ===================
			if (m_pFade)	//�k���`�F�b�N
			{
				if (!m_pFade->IsFade())
				{
					m_pScene->Update();	//�V�[���X�V
				}
			}
		}
	}

	// =============== �t�F�[�h�n ===================
	if (m_pFade)	//�k���`�F�b�N
	{
		m_pFade->Update();	//�t�F�[�h�X�V
	}

	// =============== �T�E���h ===================
	SoundUpdate();	//�T�E���h�X�V
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSceneManager::Draw()
{
	// =============== �`�� ===================
	if (m_pScene)	//�k���`�F�b�N
	{
		m_pScene->Draw();	//�V�[���`��
	}

	// =============== �t�F�[�h�n ===================
	if (m_pFade)	//�k���`�F�b�N
	{
		m_pFade->Draw();	//�t�F�[�h�X�V
	}
}

/* ========================================
	�I���m�F�֐�
	----------------------------------------
	���e�F�V�[���Ǘ�����߂邩�ǂ����̃t���O��Ԃ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Ftrue:�V�[���Ǘ�����߂��� / false:�V�[���Ǘ��𑱂�����
=========================================== */
bool CSceneManager::IsFin() const
{
	// =============== �� =====================
	return m_UcFlag.Check(E_BIT_FLAG_FINISH);	//�I���v���t���O
}

/* ========================================
	�V�[���ύX�֐�
	----------------------------------------
	���e�F���݃V�[���폜�����V�[������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSceneManager::ChangeScene()
{
	// =============== ���O���� =====================
	if (m_pScene)	//�k���`�F�b�N
	{
		m_eNextScene = m_pScene->GetNext();	//�J�ڐ�擾
	}

	// =============== �J�ڐ挟�� =====================
	if (CScene::E_TYPE_NONE == m_eNextScene || CScene::E_TYPE_MAX == m_eNextScene)
	{
		return;	//�������f
	}

	// =============== �V�[���폜 =====================
	if (m_pScene)	//�k���`�F�b�N
	{
		m_ePastScene = MAP_SCENE_TYPE.at(typeid(*m_pScene).hash_code());	//���݃V�[����ޔ�
		delete m_pScene;													//���������
		m_pScene = nullptr;													//��A�h���X
	}

	// =============== �V�[���؊� =====================
	MakeNewScene();	//�V�V�[���쐬

	// =============== �t�F�[�h�n ===================
	if (m_pFade)	//�k���`�F�b�N
	{
		delete m_pFade;		//�������J��
		m_pFade = nullptr;	//��A�h���X���
	}
	if (m_pScene)	//�V�K�V�[��������Ă���
	{
		m_pFade = new CFade();	//���I�m��
	}
}

/* ========================================
	�V�V�[���쐬�֐�
	----------------------------------------
	���e�F���V�[���������ɁA�V�[���̓��I�m�ە��򏈗�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSceneManager::MakeNewScene()
{
	// =============== �V�[������ =====================
	if (m_pScene)	//���łɃV�[�������邩
	{
		return;	//�������f
	}

	// =============== �V�[���쐬 =====================
	switch (m_eNextScene)	//����
	{
		// =============== �^�C�g���V�[�� =====================
	case CScene::E_TYPE_TITLE:		//�J�ڐ�F�^�C�g��
		m_pScene = new CTitle();	//���I�m��
		break;						//���򏈗��I��

		// =============== �X�e�[�W�Z���N�g =====================
	case CScene::E_TYPE_SELECT_STAGE:	//�J�ڐ�F�X�e�[�W�Z���N�g
		m_pScene = new CSelectStage();	//���I�m��
		break;							//���򏈗��I��

		// =============== �X�e�[�W1 =====================
	case CScene::E_TYPE_STAGE1:		//�J�ڐ�F�X�e�[�W1
		m_pScene = new CStage1();	//���I�m��
		break;						//���򏈗��I��

		// =============== �X�e�[�W2 =====================
	case CScene::E_TYPE_STAGE2:		//�J�ڐ�F�X�e�[�W2
		m_pScene = new CStage2();	//���I�m��
		break;						//���򏈗��I��

		// =============== �X�e�[�W3 =====================
	case CScene::E_TYPE_STAGE3:		//�J�ڐ�F�X�e�[�W3
		m_pScene = new CStage3();	//���I�m��
		break;						//���򏈗��I��

		// =============== ���U���g�V�[�� =====================
	case CScene::E_TYPE_RESULT:		//�J�ڐ�F���U���g
		m_pScene = new CResult();	//���I�m��
		break;						//���򏈗��I��

		// =============== �O�̃V�[�� =====================
	case CScene::E_TYPE_PAST:			//�J�ځF�߂�
		m_eNextScene = m_ePastScene;	//�ߋ��V�[�������V�[���ɓo�^
		MakeNewScene();					//��������蒼��
		break;							//���򏈗��I��

		// =============== �V�K�V�[���͍��Ȃ� =====================
	case CScene::E_TYPE_FINISH_ALL:		//�J�ځF�A�v���I��
		m_UcFlag.Up(E_BIT_FLAG_FINISH);	//�V�[���Ǘ��I���\��
		break;							//���򏈗��I��

		// =============== ��O ===================
	default:	//��L�ȊO
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "���݂��Ȃ��V�[�����Ăяo����܂���").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
		break;	//���򏈗��I��
	}

	// =============== BGM�Đ� ===================
	if (m_eNextScene != CScene::E_TYPE_FINISH_ALL)	//�V�[�����I�����Ȃ��ꍇ
	{
		PlayBGM();	//�V�K�V�[���ɑΉ�����BGM�̍Đ�
	}

	// =============== �J�ڐ�X�V =====================
	m_eNextScene = CScene::E_TYPE_NONE;	//�ړ���N���A
}

/* ========================================
	BGM�X�V�֐�
	----------------------------------------
	���e�FBGM�X�V
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSceneManager::SoundUpdate()
{
	// =============== �t�F�[�h���Ή� =====================
	SoundFade();	//BGM�̃t�F�[�h
}

/* ========================================
	BGM�t�F�[�h�֐�
	----------------------------------------
	���e�FBGM�̃t�F�[�h
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSceneManager::SoundFade()
{
	// =============== ���� =====================
	if (!m_pFade || !m_pBGMSpeaker)	//�k���`�F�b�N
	{
		// =============== �I�� =====================
		return;	//�������f
	}

	// =============== ���ʍX�V =====================
	if (m_pFade->IsFadeIn())	//�t�F�[�h�C����
	{
		m_pBGMSpeaker->SetVolume((1.0f - m_pFade->GetFrameRate()) * BGM_VOLUME);	//�t�F�[�h�C�����A���ʂ����񂾂�傫������
	}
	else if (m_pFade->IsFadeOut())	//�t�F�[�h�A�E�g��
	{
		m_pBGMSpeaker->SetVolume(m_pFade->GetFrameRate() * BGM_VOLUME);				//�t�F�[�h�A�E�g���A���ʂ����񂾂񏬂�������
	}
}

/* ========================================
	BGM�Đ��֐�
	----------------------------------------
	���e�FBGM�̍Đ�
	----------------------------------------
	����1�FScene�̎��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSceneManager::PlayBGM()
{
	// =============== ���ݒ� =====================
	if (m_pScene && MAP_BGM.find(typeid(*m_pScene).hash_code()) != MAP_BGM.end() && MAP_BGM.at(typeid(*m_pScene).hash_code()))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
	{
		UNLOAD_SOUND(m_pBGMSpeaker);													//BGM�̍Đ����~���A���̉��f�[�^�̕R�Â���j��	�������ȊO�ō폜����ƃk���`�F�b�N�ł��Ȃ����g�̃|�C���^�[���k���ƂȂ�f�X�g���N�^�Œ�~����
		m_pBGMSpeaker = CSound::PlaySound(MAP_BGM.at(typeid(*m_pScene).hash_code()));	//BGM�o�^�E�Đ�
		m_pBGMSpeaker->SetVolume(0.0f);													//�Đ����ʐݒ�
	}
#if _DEBUG
	else
	{
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "���̃f�[�^���s�����Ă��܂�").c_str(), "Error", MB_OK | MB_ICONERROR);								//�G���[�ʒm
	}
#endif
}