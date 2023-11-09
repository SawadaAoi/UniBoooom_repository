#ifndef __INPUT_H__
#define __INPUT_H__

#include <Windows.h>
#include"TriType.h"
#undef max
#undef min

// =============== íËêîíËã` =======================
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

TTriType<float> IsStickRight();
TTriType<float> IsStickLeft();


#endif // __INPUT_H__