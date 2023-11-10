#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
/* ========================================
   DX21
   ---------------------------------------
   コントローラー用ヘッダ
   ---------------------------------------
   Controller.h
   ======================================== */

 // =============== インクルード ===================
#include <Windows.h>
#include <mmsystem.h>             // joyGetPosEx, JOYINFOEX, JOYSTICKID1
#include "TriType.h"

class Controller
{
public:
	Controller();
	~Controller();
	void Update();

	TTriType<float> GetStickRight();
	TTriType<float> GetStickLeft();
	int* GetKeyState() { return m_keyState; }
	int* GetKeyStateOld() { return m_oldState; }

	bool GetUse() { return m_bUse; }
private:
	void SetKeyState();

	bool Button1();
	bool Button2();
	bool Button3();
	bool Button4();
	bool Button5();
	bool Button6();
	bool Button7();
	bool Button8();
	bool Button9();
	bool Button10();
	float LeftStickX();
	float LeftStickY();
	float RightStickX();
	float RightStickY();


	JOYINFOEX   m_joyInfoEx;    // ジョイスティックの情報を格納する変数
	int m_keyState[10];			// ボタン押下情報セット配列(現在)
	int m_oldState[10];			// ボタン押下情報セット配列(1フレーム前)

	bool m_bUse;	// コントローラの有効無効フラグ
};




#endif // !__CONTROLLER_H__

