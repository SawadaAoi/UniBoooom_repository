/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�v���O�����̃��C��������`
	------------------------------------
	Main.h
	------------------------------------
	�쐬��

	�ύX����
   �E���܂� �w�Z�̔z�z��(���Ƃɉ����ό`)�EGeometry�ɍ��킹������
	�E2023/11/17 �f�o�b�O���[�h��` takagi
	�E2024/01/21 ���t�@�N�^�����O takagi

========================================== */

#ifndef __MAIN_H__	//Main.h�C���N���[�h�K�[�h
#define __MAIN_H__

// =============== �f�o�b�O���[�h ===================
#if _DEBUG
#define USE_SCENE_MANAGER (true)
#endif

// =============== �C���N���[�h ===================
#include <Windows.h>

// =============== �v���g�^�C�v�錾 ===============
HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update(float tick);
void Draw(); 
#if USE_SCENE_MANAGER
bool IsFin();
#endif

#endif	//!__MAIN_H__