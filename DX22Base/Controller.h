
/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   コントローラー用ヘッダ
   ---------------------------------------
   Controller.h
   ======================================== */
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

 // =============== インクルード ===================
#include <Windows.h>
#include <mmsystem.h>             // joyGetPosEx, JOYINFOEX, JOYSTICKID1
#include "TriType.h"

class Controller
{
public:
	// ===プロトタイプ宣言===
	Controller();
	~Controller();
	void Update();

	TTriType<float> GetStickRight();
	TTriType<float> GetStickLeft();
	int* GetKeyState() { return m_keyState; }
	int* GetKeyStateOld() { return m_oldState; }

private:
	void SetKeyState();

	// ===メンバ変数宣言=====
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

};




#endif // !__CONTROLLER_H__

