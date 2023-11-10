#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
/* ========================================
   DX21
   ---------------------------------------
   �R���g���[���[�p�w�b�_
   ---------------------------------------
   Controller.h
   ======================================== */

 // =============== �C���N���[�h ===================
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


	JOYINFOEX   m_joyInfoEx;    // �W���C�X�e�B�b�N�̏����i�[����ϐ�
	int m_keyState[10];			// �{�^���������Z�b�g�z��(����)
	int m_oldState[10];			// �{�^���������Z�b�g�z��(1�t���[���O)

	bool m_bUse;	// �R���g���[���̗L�������t���O
};




#endif // !__CONTROLLER_H__

