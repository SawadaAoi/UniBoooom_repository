/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	入力用ヘッダ
	------------------------------------
	Input.h
	------------------------------------
	作成者

	変更履歴
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __INPUT_H__	//Input.hインクルードガード
#define __INPUT_H__

// =============== インクルード ===================
#include <Windows.h>
#include"TriType.h"
#undef max
#undef min

// =============== 列挙定義 =======================
enum ControllerButton
{
	BUTTON_X,
	BUTTON_Y,
	BUTTON_A,
	BUTTON_B,
	BUTTON_LB,		// Lボタン
	BUTTON_RB,		// Rボタン
	BUTTON_LT,		// Lトリガー
	BUTTON_RT,		// Rトリガー
	BUTTON_LS,		// Lスティック押し込み
	BUTTON_RS,		// Rスティック押し込み
	BUTTON_SELECT,	// セレクトボタン
	BUTTON_START,	// スタートボタン
};

// ===プロトタイプ宣言===
HRESULT InitInput();
void UninitInput();
void UpdateInput();

bool IsKeyPress(BYTE key);
bool IsKeyTrigger(BYTE key);
bool IsKeyRelease(BYTE key);
bool IsKeyRepeat(BYTE key);

bool IsKeyPressController(ControllerButton nKey);
bool IsKeyTriggerController(ControllerButton nKey);
bool IsKeyReleaseController(ControllerButton nKey);

// =============== 定数定義 =======================
TTriType<float> IsStickRight();
TTriType<float> IsStickLeft();

bool GetUseVController();

#endif	//!__INPUT_H__