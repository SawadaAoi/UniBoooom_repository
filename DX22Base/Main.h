#ifndef __MAIN_H__
#define __MAIN_H__

// =============== インクルード ===================
#include <Windows.h>

// =============== プロトタイプ宣言 ===============
HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update(float tick);
void Draw();

#endif // __MAIN_H__