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
	�E2023/11/21 3d�A�j���[�V�����p�z�z���K�p
	�E2024/02/27 �f�o�b�O���[�h���� takagi
	�E�ŏ��̓ǂݍ��ݎ��Ԃɑҋ@��ʒǉ� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometry.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneManager.h"
#include "Defines.h"
#include <time.h>
#include "Sound.h"
#include "ShaderList.h"	//���f���A�j���[�V�����p
#include "LibEffekseer.h"
#include "2dPolygon.h"

// =============== �O���[�o���ϐ���` =============
CSceneManager* g_pSceneMng;
bool g_bScrren = false;	//�t���X�N���[�����ۂ������߂�(true�Ńt���X�N���[��)

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
	hr = InitDirectX(hWnd, width, height, g_bScrren);
	if (FAILED(hr)) { return hr; }

	CSound::InitSound();
	LibEffekseer::Init(GetDevice(), GetContext());

	CGeometry::MakeShader();			//�V�F�[�_�쐬
	srand((unsigned int)time(NULL));	// �����p�^�[���ݒ�

	Sprite::Init();
	InitInput();

	ShaderList::Init();

	//�ǂݍ��ݑ҂����
	C2dPolygon Tex;
	Tex.SetTexture("Assets/Texture/Start/Wait.png");
	Tex.SetPos({ static_cast<float>(SCREEN_WIDTH / 2.0f), static_cast<float>(SCREEN_HEIGHT / 2.0f), 0.0f });
	Tex.SetSize({ static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f });
	BeginDrawDirectX();	//�����o���J�n
	Tex.Draw();			//�`��
	EndDrawDirectX();	//�����o������

	// �V�[���쐬
	g_pSceneMng = new CSceneManager();

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
	if (g_pSceneMng)	//�k���`�F�b�N
	{
		delete g_pSceneMng;
		g_pSceneMng = nullptr;
	}
	ShaderList::Uninit();
	CGeometry::Uninit();
	UninitInput();
	Sprite::Uninit();
	LibEffekseer::Uninit();
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
	if (g_pSceneMng)	//�k���`�F�b�N
	{
		g_pSceneMng->Update();
	}
	if (IsKeyTrigger('M')/* || IsKeyTriggerController(BUTTON_LB)*/)
	{
		g_bScrren ^= 1;	//�t���O�؊�
		SetScreenMode(g_bScrren);	//�X�N���[�����X�V
	}
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
	if (g_pSceneMng)	//�k���`�F�b�N
	{
		g_pSceneMng->Draw();
	}
	EndDrawDirectX();
}

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

// EOF