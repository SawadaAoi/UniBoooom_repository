#ifndef __MAIN_H__
#define __MAIN_H__

// =============== �C���N���[�h ===================
#include <Windows.h>

// =============== �v���g�^�C�v�錾 ===============
HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update(float tick);
void Draw();

#endif // __MAIN_H__