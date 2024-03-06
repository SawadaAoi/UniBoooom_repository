/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�v���O�����̃��C������
	------------------------------------
	Main.h
	------------------------------------
	�쐬��

	�ύX����
   �E���܂� �w�Z�̔z�z��(���Ƃɉ����ό`)�EGeometry�ɍ��킹������
	�E2023/11/17 �f�o�b�O���[�h��` takagi
	�E2024/02/27 �f�o�b�O���[�h���� takagi

========================================== */

#ifndef __MAIN_H__
#define __MAIN_H__

// =============== �C���N���[�h ===================
#include <Windows.h>

// =============== �v���g�^�C�v�錾 ===============
HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update(float tick);
void Draw(); 
bool IsFin();

#endif // __MAIN_H__