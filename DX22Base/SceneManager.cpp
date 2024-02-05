/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���Ǘ�����
	---------------------------------------
	SceneManager.cpp

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
	�E2023/12/12 �ŏ��̃V�[�����^�C�g���ɕύX
	�E2023/12/14 BGM�̊Ǘ���Scene������ړ� yamashita
	�E2023/12/14 BGM�p�̒萔��` yamashita
	�E2023/12/14 BGM���t�F�[�h����悤�ɕύX yamashita
	�E2023/12/15 �A�v���I������ takagi 

========================================== */

// =============== �f�o�b�O���[�h ===================
#if _DEBUG
#define KEY_CHANGE_SCENE (true)	//�L�[���͂ŃV�[����ς���
#endif

// =============== �C���N���[�h ===================
#include "SceneManager.h"	//���g�̃w�b�_
//#include "Prot.h"			//�C���X�^���X���
#include "Title.h"			//�C���X�^���X���
#include "SelectStage.h"	//�C���X�^���X���
#include "Stage1.h"			//�C���X�^���X���
#include "Stage2.h"			//�C���X�^���X���
#include "Stage3.h"			//�C���X�^���X���
#include "Result.h"			//�C���X�^���X���
#include "HitStop.h"		//�q�b�g�X�g�b�v

#if _DEBUG
#include <Windows.h>		//���b�Z�[�W�{�b�N�X�p
#endif

#if KEY_CHANGE_SCENE
#include <string>			//�����񑀍�
#include "Input.h"			//�L�[����
#endif

// =============== �萔��` ===================
const std::string BGM_FILE[CScene::E_TYPE_MAX] = {	//�e�X�e�[�W��BGM�̃t�@�C��
	"Assets/Sound/BGM/Title_Select.mp3",	//�^�C�g��
	"Assets/Sound/BGM/Title_Select.mp3",	//�X�e�[�W�Z���N�g
	"Assets/Sound/BGM/Stage1.mp3",	//Stage1
	"Assets/Sound/BGM/Stage2.mp3",	//Stage2
	"Assets/Sound/BGM/Stage3.mp3",	//Stage3
	"Assets/Sound/BGM/Result.mp3" };	//���U���g

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
	: m_pScene(nullptr)						//�V�[��
	, m_ePastScene(CScene::E_TYPE_NONE)		//�O�̃V�[��
	, m_eNextScene(CScene::E_TYPE_TITLE)	//�V�[���J�ڐ�
	, m_bFinish(false)						//�V�[���Ǘ����J�n
	, m_pFade(nullptr)						//�t�F�[�h
	, m_bStartFadeOut(false)
	, m_bFinFadeOut(false)
	, m_pBGM{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}
	, m_pBGMSpeaker(nullptr)
{
	// =============== �T�E���h�ǂݍ��� ===================
	LoadSound();
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
	if (m_pScene)	//�k���`�F�b�N
	{
		SAFE_DELETE(m_pScene);	//���
	}
	if (m_pFade)	//�k���`�F�b�N
	{
		SAFE_DELETE(m_pFade);	//���
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
void CSceneManager::Update()
{
#if KEY_CHANGE_SCENE
	for (int nIdx = 0; nIdx < CScene::E_TYPE_MAX; nIdx++)
	{
		if (nIdx < 10)	//�L�[���͂ł���͈�
		{
			//Shift���͒��ɐ����������Ƃ��̐����̃V�[���Ɉڂ�
			if (IsKeyPress(VK_SHIFT) & IsKeyTrigger(*std::to_string(nIdx).c_str()))
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
			if (m_bStartFadeOut)
			{
				ChangeScene();
				m_bStartFadeOut = false;
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
					m_pFade->Start();		//�t�F�[�h�J�n
					m_bStartFadeOut = true;
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
	SoundUpdate();
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
	return m_bFinish;	//�I���v���t���O
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
		m_eNextScene = m_pScene->GetNext();	// �J�ڐ�擾
	}

	// =============== �J�ڐ挟�� =====================
	if (CScene::E_TYPE_NONE == m_eNextScene || CScene::E_TYPE_MAX == m_eNextScene)
	{
		return;	//�������f
	}

	// =============== �V�[���폜 =====================
	if (m_pScene)	//�k���`�F�b�N
	{
		//BGM�̍폜
		m_pBGMSpeaker->Stop();
		m_pBGMSpeaker->DestroyVoice();	//BGM�̍폜
		//�V�[���̍폜
		m_ePastScene = m_pScene->GetType();	//���݃V�[����ޔ�
		delete m_pScene;					//���������
		m_pScene = nullptr;					//��A�h���X
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
		m_pFade = new CFade(m_pScene->GetCamera());	//���I�m��
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
		PlayBGM(m_eNextScene);		//BGM�̍Đ�
		break;						//���򏈗��I��

		// =============== �X�e�[�W�Z���N�g =====================
	case CScene::E_TYPE_SELECT_STAGE:	//�J�ڐ�F�X�e�[�W�Z���N�g
		m_pScene = new CSelectStage();	//���I�m��
		PlayBGM(m_eNextScene);		//BGM�̍Đ�

		break;							//���򏈗��I��

		// =============== �X�e�[�W1 =====================
	case CScene::E_TYPE_STAGE1:		//�J�ڐ�F�X�e�[�W1
		m_pScene = new CStage1();	//���I�m��
		PlayBGM(m_eNextScene);		//BGM�̍Đ�
		break;						//���򏈗��I��

		// =============== �X�e�[�W2 =====================
	case CScene::E_TYPE_STAGE2:		//�J�ڐ�F�X�e�[�W2
		m_pScene = new CStage2();	//���I�m��
		PlayBGM(m_eNextScene);		//BGM�̍Đ�
		break;						//���򏈗��I��

		// =============== �X�e�[�W3 =====================
	case CScene::E_TYPE_STAGE3:		//�J�ڐ�F�X�e�[�W3
		m_pScene = new CStage3();	//���I�m��
		PlayBGM(m_eNextScene);		//BGM�̍Đ�
		break;						//���򏈗��I��

		// =============== ���U���g�V�[�� =====================
	case CScene::E_TYPE_RESULT:					//�J�ڐ�F���U���g
		m_pScene = new CResult();				//���I�m��
		PlayBGM(m_eNextScene);					//BGM�̍Đ�
		break;									//���򏈗��I��

		// =============== �O�̃V�[�� =====================
	case CScene::E_TYPE_PAST:			//�J�ځF�߂�
		m_eNextScene = m_ePastScene;	//�ߋ��V�[�������V�[���ɓo�^
		MakeNewScene();					//��������蒼��
		break;							//���򏈗��I��

		// =============== �V�K�V�[���͍��Ȃ� =====================
	case CScene::E_TYPE_FINISH_ALL:		//�J�ځF�A�v���I��
		m_bFinish = true;				//�V�[���Ǘ��I���\��
		break;							//���򏈗��I��

		// =============== ���̑� =====================
	default:	//�Y���Ȃ�
#if _DEBUG
		MessageBox(nullptr, "���݂��Ȃ��V�[�����Ăяo����܂���", "SceneManager.cpp->Error", MB_OK);	//�G���[�ʒm
#endif
		break;	//���򏈗��I��
	}

	// =============== �J�ڐ�X�V =====================
	m_eNextScene = CScene::E_TYPE_NONE;	//�ړ���N���A
}

/* ========================================
	BGM�ǂݍ��݊֐�
	----------------------------------------
	���e�FBGM�̃T�E���h�t�@�C����ǂݍ���
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CSceneManager::LoadSound()
{
	m_pBGM[CScene::E_TYPE_TITLE] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_TITLE].c_str(), true);			//�^�C�g���p
	m_pBGM[CScene::E_TYPE_SELECT_STAGE] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_SELECT_STAGE].c_str(), true);	//�Z���N�g�X�e�[�W�p
	m_pBGM[CScene::E_TYPE_STAGE1] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_STAGE1].c_str(), true);		//�X�e�[�W1�p
	m_pBGM[CScene::E_TYPE_STAGE2] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_STAGE2].c_str(), true);		//�X�e�[�W2�p
	m_pBGM[CScene::E_TYPE_STAGE3] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_STAGE3].c_str(), true);		//�X�e�[�W3�p
	m_pBGM[CScene::E_TYPE_RESULT] = CSound::LoadSound(BGM_FILE[CScene::E_TYPE_RESULT].c_str(), true);		//���U���g�p
}

void CSceneManager::SoundUpdate()
{
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
	if (!m_pFade || !m_pBGMSpeaker) { return; }	//null�`�F�b�N
	//�t�F�[�h�C���������炾�񂾂�傫���Ȃ�
	if (m_pFade->IsFadeIn())	
	{
		m_pBGMSpeaker->SetVolume((1.0f - m_pFade->GetFrameRate()) * BGM_VOLUME);
	}
	//�t�F�[�h�A�E�g�������炾�񂾂񏬂����Ȃ�
	else if (m_pFade->IsFadeOut())
	{
		m_pBGMSpeaker->SetVolume(m_pFade->GetFrameRate() * BGM_VOLUME);
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
void CSceneManager::PlayBGM(CScene::E_TYPE Scene)
{
	m_pBGMSpeaker = CSound::PlaySound(m_pBGM[Scene]);
	m_pBGMSpeaker->SetVolume(0.0f);
}