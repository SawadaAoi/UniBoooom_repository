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
	�E2023/11/09 �J�����̗l�X����`�F�b�N�B ���؏x��

========================================== */

#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometry.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneGame.h"
#include "Defines.h"


//--- �O���[�o���ϐ�
SceneGame* g_pGame;	//

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX������
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	CGeometry::MakeShader();	//�V�F�[�_�쐬

	Sprite::Init();
	InitInput();

	// �V�[���쐬
	g_pGame = new SceneGame();

	return hr;
}

void Uninit()
{
	delete g_pGame;
	CGeometry::Uninit();
	UninitInput();
	Sprite::Uninit();
	UninitDirectX();
}

void Update(float tick)
{
	UpdateInput();
	g_pGame->Update(tick);
}

void Draw()
{
	BeginDrawDirectX();



	g_pGame->Draw();
	EndDrawDirectX();
}

// EOF