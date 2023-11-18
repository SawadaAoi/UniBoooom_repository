/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�v���O�����̃��C������
	------------------------------------
	Main.cpp
	------------------------------------
	�쐬�� 

	�ύX����
   �E���܂� �w�Z�̔z�z��(���Ƃɉ����ό`)�EGeometry�ɍ��킹������
	�E2023/11/09 �J�����̗l�X����`�F�b�N�B takagi
	�E2023/11/17 �V�[���Ǘ������� takagi
	�E2023/11/18 sound.h���C���N���[�h����sound�̏������ƏI����ǉ� yamashita

========================================== */

// =============== �C���N���[�h ===================
#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometry.h"
#include "Sprite.h"
#include "Input.h"
#if USE_SCENE_MANAGER
#include "SceneManager.h"
#else
#include "SceneGame.h"
#endif
#include "Defines.h"
#include <time.h>
#include "Sound.h"

// =============== �O���[�o���ϐ���` =============
#if USE_SCENE_MANAGER
CSceneManager* g_pSceneMng;
#else
SceneGame* g_pGame;
#endif

/* ========================================
	�����������֐�
	-------------------------------------
	���e�F����������
	-------------------------------------
	����1�F(hWnd)	//TODO�F������Ȃ�
	-------------------------------------
	����2�F��ʃT�C�Y����(width)
	-------------------------------------
	����3�F��ʃT�C�Y�c��(height)
	-------------------------------------
	�ߒl�F����
=========================================== */
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX������
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	CSound::InitSound();

	CGeometry::MakeShader();			//�V�F�[�_�쐬
	srand((unsigned int)time(NULL));	// �����p�^�[���ݒ�

	Sprite::Init();
	InitInput();

	// �V�[���쐬
#if USE_SCENE_MANAGER
	g_pSceneMng = new CSceneManager();
#else
	g_pGame = new SceneGame(GetDirectWrite());
#endif

	return hr;
}

/* ========================================
	�I�������֐�
	-------------------------------------
	���e�F�I������
	-------------------------------------
	�����F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void Uninit()
{
#if USE_SCENE_MANAGER
	if (g_pSceneMng)	//�k���`�F�b�N
	{
		delete g_pSceneMng;
		g_pSceneMng = nullptr;
	}
#else
	delete g_pGame;
#endif
	CGeometry::Uninit();
	UninitInput();
	Sprite::Uninit();
	CSound::UninitSound();
	UninitDirectX();
}

/* ========================================
	�X�V�����֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	�����F�e�B�b�N��(tick)
	-------------------------------------
	�ߒl�F����
=========================================== */
void Update(float tick)
{
	UpdateInput();
#if USE_SCENE_MANAGER
	if (g_pSceneMng)	//�k���`�F�b�N
	{
		g_pSceneMng->Update();
	}
#else
	g_pGame->Update(tick);
#endif
}

/* ========================================
	�`�揈���֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	�����F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void Draw()
{
	BeginDrawDirectX();
#if USE_SCENE_MANAGER
	if (g_pSceneMng)	//�k���`�F�b�N
	{
		g_pSceneMng->Draw();
	}
#else
	g_pGame->Draw();
#endif
	EndDrawDirectX();
}

#if USE_SCENE_MANAGER
/* ========================================
	�I�������֐�
	-------------------------------------
	���e�F���̃A�v�����I�����邩�ǂ������肷��
	-------------------------------------
	�����F����
	-------------------------------------
	�ߒl�F�I������
=========================================== */
bool IsFin()
{
	if (g_pSceneMng)	//�k���`�F�b�N
	{
		return g_pSceneMng->IsFin();
	}
	else
	{
		return false;	//�p��
	}
}
#endif

// EOF