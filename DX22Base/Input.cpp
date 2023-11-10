/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	入力用cpp
	------------------------------------
	Input.cpp
	------------------------------------
	作成者

	変更履歴
	・XXXX/XX/XX 変更内容 変更者名

========================================== */

// =============== インクルード ===================
#include "Input.h"
#include "Controller.h"

// =============== グローバル変数定義 =============
BYTE g_keyTable[256];
BYTE g_oldTable[256];
Controller g_Controller;	// コントローラーの入力情報

/* ========================================
	関数 初期化関数
	-------------------------------------
	内容：初期化処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：S_OK
=========================================== */
HRESULT InitInput()
{
	// 一番最初の入力
	GetKeyboardState(g_keyTable);
	return S_OK;
}

/* ========================================
	関数 終了関数
	-------------------------------------
	内容：終了処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void UninitInput()
{
}

/* ========================================
	関数 更新関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void UpdateInput()
{
	// 古い入力を更新
	memcpy_s(g_oldTable, sizeof(g_oldTable), g_keyTable, sizeof(g_keyTable));
	// 現在の入力を取得
	GetKeyboardState(g_keyTable);

	g_Controller.Update();
}

/* ========================================
	関数 キー押下中判定関数
	-------------------------------------
	内容：キーを押している間処理を行う
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：押されているキー
=========================================== */
bool IsKeyPress(BYTE key)
{
	return g_keyTable[key] & 0x80;
}

/* ========================================
	関数 キー押下開始判定関数
	-------------------------------------
	内容：キーが押されたときに処理を行う
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：押されているキー
=========================================== */
bool IsKeyTrigger(BYTE key)
{
	return (g_keyTable[key] ^ g_oldTable[key]) & g_keyTable[key] & 0x80;
}

/* ========================================
	関数 キー押下終了判定関数
	-------------------------------------
	内容：キーを押した後離したときに行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：離したキー
=========================================== */
bool IsKeyRelease(BYTE key)
{
	return (g_keyTable[key] ^ g_oldTable[key]) & g_oldTable[key] & 0x80;
}

/* ========================================
	関数 キー押下判定フラグ
	-------------------------------------
	内容：同じキーを押し続けている間行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：true または false
=========================================== */
bool IsKeyRepeat(BYTE key)
{
	return false;
}
// ゲームコントローラーの関数-------------------------------------------------------

/* ========================================
   コントローラープレス入力関数(キーが押されているかどうか)
   ----------------------------------------
   内容：キーが押されている場合常にtrueを返し続ける
   ----------------------------------------
   引数：入力キー(例:VK_○○、'A')
   ----------------------------------------
   戻値：true:押されている / false:押されていない
   ======================================== */
bool IsKeyPressController(ControllerButton nKey)
{
	return g_Controller.GetKeyState()[nKey] & 1;

}

/* ========================================
   コントローラートリガー入力関数(キーを押したかどうか)
   ----------------------------------------
   内容：キーが押し込まれた瞬間に一度だけ返す
	  ----------------------------------------
   引数：入力キー(例:VK_○○、'A')
   ----------------------------------------
   戻値：true:押されている / false:押されていない
   ======================================== */
bool IsKeyTriggerController(ControllerButton nKey)
{
	int now = g_Controller.GetKeyState()[nKey];
	int old = g_Controller.GetKeyStateOld()[nKey];

	// 0→1の場合トリガーになる
	return (old ^ now) & now & 1;
}


/* ========================================
   コントローラーリリース入力関数(キーを離したかどうか)
   ----------------------------------------
   内容：キーを離した瞬間に一度だけ返す
	  ----------------------------------------
   引数：入力キー(例:VK_○○、'A')
   ----------------------------------------
   戻値：true:押されている / false:押されていない
   ======================================== */
bool IsKeyReleaseController(ControllerButton nKey)
{
	int now = g_Controller.GetKeyState()[nKey];
	int old = g_Controller.GetKeyStateOld()[nKey];

	// 1→0の場合リリースになる
	return (old ^ now) & old & 1;

}

/* ========================================
   右スティック傾き入力関数
   ----------------------------------------
   内容：右スティックの傾き情報を取得する
   ----------------------------------------
   戻値：傾き情報x,y(-1.0〜1.0)
   ======================================== */
TTriType<float> IsStickRight()
{
	return g_Controller.GetStickRight();
}

/* ========================================
   左スティック傾き入力関数
   ----------------------------------------
   内容：左スティックの傾き情報を取得する
   ----------------------------------------
   戻値：傾き情報x,y(-1.0〜1.0)
   ======================================== */
TTriType<float> IsStickLeft()
{
	return g_Controller.GetStickLeft();
}

bool GetUseVController()
{
	return g_Controller.GetUse();
}
