/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	プログラムのメイン部分
	------------------------------------
	Main.h
	------------------------------------
	作成者

	変更履歴
   ・↓まで 学校の配布物(授業に沿い変形)・Geometryに合わせた改造
	・2023/11/17 デバッグモード定義 takagi

========================================== */

// =============== デバッグモード ===================
#if _DEBUG
#define USE_SCENE_MANAGER (true)
#endif

#ifndef __MAIN_H__
#define __MAIN_H__

// =============== インクルード ===================
#include <Windows.h>

// =============== プロトタイプ宣言 ===============
HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update(float tick);
void Draw(); 
#if USE_SCENE_MANAGER
bool IsFin();
#endif

#endif // __MAIN_H__