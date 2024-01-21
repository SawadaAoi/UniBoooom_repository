/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���͗p�w�b�_
	------------------------------------
	Input.h
	------------------------------------
	�쐬��

	�ύX����
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __INPUT_H__	//Input.h�C���N���[�h�K�[�h
#define __INPUT_H__

// =============== �C���N���[�h ===================
#include <Windows.h>
#include"TriType.h"
#undef max
#undef min

// =============== �񋓒�` =======================
enum ControllerButton
{
	BUTTON_X,
	BUTTON_Y,
	BUTTON_A,
	BUTTON_B,
	BUTTON_LB,		// L�{�^��
	BUTTON_RB,		// R�{�^��
	BUTTON_LT,		// L�g���K�[
	BUTTON_RT,		// R�g���K�[
	BUTTON_LS,		// L�X�e�B�b�N��������
	BUTTON_RS,		// R�X�e�B�b�N��������
	BUTTON_SELECT,	// �Z���N�g�{�^��
	BUTTON_START,	// �X�^�[�g�{�^��
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

bool GetUseVController();

#endif	//!__INPUT_H__