/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���͗p�w�b�_
	------------------------------------
	Input.h
	------------------------------------
	�쐬��

	�ύX����
	�EXXXX/XX/XX �ύX���e �ύX�Җ�

========================================== */

#ifndef __INPUT_H__
#define __INPUT_H__

// =============== �C���N���[�h ===================
#include <Windows.h>
#include"TriType.h"
#undef max
#undef min

// =============== �񋓒�` =======================
enum ControllerButton
{
	BUTTON_X = 0,
	BUTTON_Y = 1,
	BUTTON_A = 2,
	BUTTON_B = 3,
	BUTTON_LB = 4,
	BUTTON_RB = 5,
	BUTTON_LT = 6,
	BUTTON_RT = 7,
	BUTTON_LS = 8,
	BUTTON_RS = 9,
};

// ===�v���g�^�C�v�錾===
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

// =============== �萔��` =======================
TTriType<float> IsStickRight();
TTriType<float> IsStickLeft();


#endif // __INPUT_H__