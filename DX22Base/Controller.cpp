/* ========================================
   DX21
   ---------------------------------------
   ゲームコントローラー用cpp
   ---------------------------------------
   Controller.cpp
   ---------------------------------------
   ※コントローラーがDirectXモードじゃないと勝手に上に行くので注意
   ======================================== */

// =============== インクルード ===================
#include "Controller.h"


// =============== 定数定義 =======================
const int STICK_PLUS	= 65535;	// コントローラーのスティックが+方向に入力されている時	(ffff)
const int STICK_NEUTRAL = 32767;	// コントローラーのスティックが入力されていない時		(7fff)
const int STICK_MINUS	= 0;		// コントローラーのスティックが-方向に入力されている時	(0000)


/* ========================================

	コンストラクタ

   ======================================== */
Controller::Controller()
	: m_bUse(false)
{
	m_joyInfoEx.dwSize = sizeof(m_joyInfoEx);	// この構造体のサイズ (バイト単位)。
	m_joyInfoEx.dwFlags = JOY_RETURNALL;		// 構造体で返される有効な情報を示すフラグ

	// コントローラが接続されてない場合
	if (JOYERR_NOERROR != joyGetPosEx(0, &m_joyInfoEx))
	{
		m_bUse = false;
	}
	else
	{
		m_bUse = true;
	}
}

/* ========================================

	デストラクタ

   ======================================== */
Controller::~Controller()
{

}

/* ========================================

	更新処理

   ======================================== */
void Controller::Update()
{

	memcpy(m_oldState, m_keyState, sizeof(m_oldState));	// 1フレーム前の値配列にメモリの内容を丸々コピー

	MMRESULT result = joyGetPosEx(JOYSTICKID1, &m_joyInfoEx);	// 現在のコントローラーの入力情報をセット

	SetKeyState();	// 現フレームのボタン入力情報を配列にセット


	// コントローラが接続されてない場合
	if (JOYERR_NOERROR != joyGetPosEx(0, &m_joyInfoEx))
	{
		m_bUse = false;
	}
	else
	{
		m_bUse = true;
	}
}


/* ========================================
   右スティック入力値取得関数
   ----------------------------------------
   内容：右スティックの傾き情報を渡す
   ----------------------------------------
   戻値：傾き情報x,y(-1.0〜1.0)
   ======================================== */
TTriType<float> Controller::GetStickRight()
{
	TTriType<float> stick;
	stick.x = RightStickX();
	stick.y = RightStickY();
	return stick;
}

/* ========================================
   左スティック入力値取得関数
   ----------------------------------------
   内容：左スティックの傾き情報を渡す
   ----------------------------------------
   戻値：傾き情報x,y(-1.0〜1.0)
   ======================================== */
TTriType<float> Controller::GetStickLeft()
{
	TTriType<float> stick;
	stick.x = LeftStickX();
	stick.y = LeftStickY();
	return stick;
}

/* ========================================
   ボタン情報セット関数
   ----------------------------------------
   内容：コントローラーの全ボタンの情報をセットする
   ======================================== */
void Controller::SetKeyState()
{
	m_keyState[0] = Button1();
	m_keyState[1] = Button2();
	m_keyState[2] = Button3();
	m_keyState[3] = Button4();
	m_keyState[4] = Button5();
	m_keyState[5] = Button6();
	m_keyState[6] = Button7();
	m_keyState[7] = Button8();
	m_keyState[8] = Button9();
	m_keyState[9] = Button10();

}


/* ========================================
   ボタン1入力値取得関数
   ----------------------------------------
   内容：ボタン1の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button1()
{
	// dwButtonsは2進数で設定されている(ボタンに対応する桁数の値が1になる)
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON1) != 0);
}

/* ========================================
   ボタン2入力値取得関数
   ----------------------------------------
   内容：ボタン2の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button2()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON2) != 0);
}

/* ========================================
   ボタン3入力値取得関数
   ----------------------------------------
   内容：ボタン3の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button3()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON3) != 0);
} 

/* ========================================
   ボタン4入力値取得関数
   ----------------------------------------
   内容：ボタン4の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button4()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON4) != 0);
} 

/* ========================================
   ボタン5入力値取得関数
   ----------------------------------------
   内容：ボタン5の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button5()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON5) != 0);
} 

/* ========================================
   ボタン6入力値取得関数
   ----------------------------------------
   内容：ボタン6の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button6()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON6) != 0);
} 

/* ========================================
   ボタン7入力値取得関数
   ----------------------------------------
   内容：ボタン7の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button7()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON7) != 0);
} 

/* ========================================
   ボタン8入力値取得関数
   ----------------------------------------
   内容：ボタン8の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button8()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON8) != 0);
} 

/* ========================================
   ボタン9入力値取得関数
   ----------------------------------------
   内容：ボタン9の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button9()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON9) != 0);
} 

/* ========================================
   ボタン10入力値取得関数
   ----------------------------------------
   内容：ボタン10の入力値を取得する
   ----------------------------------------
   戻値：true:押されている/false:押されてない
   ======================================== */
bool Controller::Button10()
{
	return ((m_joyInfoEx.dwButtons & JOY_BUTTON10) != 0);
}

/* ========================================
   左スティックのX軸方向値取得関数
   ----------------------------------------
   内容：左スティックのX軸方向の傾きを取得する
   ----------------------------------------
   戻値：-1.0〜0.0〜1.0
   ======================================== */
float Controller::LeftStickX()
{
	return (((float)m_joyInfoEx.dwXpos - STICK_NEUTRAL) / STICK_NEUTRAL);
}

/* ========================================
   左スティックのY軸方向値取得関数
   ----------------------------------------
   内容：左スティックのY軸方向の傾きを取得する
   ----------------------------------------
   戻値：-1.0〜0.0〜1.0
   ======================================== */
float Controller::LeftStickY()
{
	return (((float)m_joyInfoEx.dwYpos - STICK_NEUTRAL) / STICK_NEUTRAL);
}

/* ========================================
   右スティックのX軸方向値取得関数
   ----------------------------------------
   内容：右スティックのX軸方向の傾きを取得する
   ----------------------------------------
   戻値：-1.0〜0.0〜1.0
   ======================================== */
float Controller::RightStickX()
{
	return (((float)m_joyInfoEx.dwZpos - STICK_NEUTRAL) / STICK_NEUTRAL);
}

/* ========================================
   右スティックのY軸方向値取得関数
   ----------------------------------------
   内容：右スティックのY軸方向の傾きを取得する
   ----------------------------------------
   戻値：-1.0〜0.0〜1.0
   ======================================== */
float Controller::RightStickY()
{
	return (((float)m_joyInfoEx.dwRpos - STICK_NEUTRAL) / STICK_NEUTRAL);
}


