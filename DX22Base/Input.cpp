#include "Input.h"
#include "Controller.h"
//--- �O���[�o���ϐ�
BYTE g_keyTable[256];
BYTE g_oldTable[256];
Controller g_Controller;	// �R���g���[���[�̓��͏��

HRESULT InitInput()
{
	// ��ԍŏ��̓���
	GetKeyboardState(g_keyTable);
	return S_OK;
}
void UninitInput()
{
}
void UpdateInput()
{
	// �Â����͂��X�V
	memcpy_s(g_oldTable, sizeof(g_oldTable), g_keyTable, sizeof(g_keyTable));
	// ���݂̓��͂��擾
	GetKeyboardState(g_keyTable);
}

bool IsKeyPress(BYTE key)
{
	return g_keyTable[key] & 0x80;
}
bool IsKeyTrigger(BYTE key)
{
	return (g_keyTable[key] ^ g_oldTable[key]) & g_keyTable[key] & 0x80;
}
bool IsKeyRelease(BYTE key)
{
	return (g_keyTable[key] ^ g_oldTable[key]) & g_oldTable[key] & 0x80;
}
bool IsKeyRepeat(BYTE key)
{
	return false;
}
// �Q�[���R���g���[���[�̊֐�-------------------------------------------------------

/* ========================================
   �R���g���[���[�v���X���͊֐�(�L�[��������Ă��邩�ǂ���)
   ----------------------------------------
   ���e�F�L�[��������Ă���ꍇ���true��Ԃ�������
   ----------------------------------------
   �����F���̓L�[(��:VK_�����A'A')
   ----------------------------------------
   �ߒl�Ftrue:������Ă��� / false:������Ă��Ȃ�
   ======================================== */
bool IsKeyPressController(ControllerButton nKey)
{
	return g_Controller.GetKeyState()[nKey] & 1;

}

/* ========================================
   �R���g���[���[�g���K�[���͊֐�(�L�[�����������ǂ���)
   ----------------------------------------
   ���e�F�L�[���������܂ꂽ�u�ԂɈ�x�����Ԃ�
	  ----------------------------------------
   �����F���̓L�[(��:VK_�����A'A')
   ----------------------------------------
   �ߒl�Ftrue:������Ă��� / false:������Ă��Ȃ�
   ======================================== */
bool IsKeyTriggerController(ControllerButton nKey)
{
	int now = g_Controller.GetKeyState()[nKey];
	int old = g_Controller.GetKeyStateOld()[nKey];

	// 0��1�̏ꍇ�g���K�[�ɂȂ�
	return (old ^ now) & now & 1;
}


/* ========================================
   �R���g���[���[�����[�X���͊֐�(�L�[�𗣂������ǂ���)
   ----------------------------------------
   ���e�F�L�[�𗣂����u�ԂɈ�x�����Ԃ�
	  ----------------------------------------
   �����F���̓L�[(��:VK_�����A'A')
   ----------------------------------------
   �ߒl�Ftrue:������Ă��� / false:������Ă��Ȃ�
   ======================================== */
bool IsKeyReleaseController(ControllerButton nKey)
{
	int now = g_Controller.GetKeyState()[nKey];
	int old = g_Controller.GetKeyStateOld()[nKey];

	// 1��0�̏ꍇ�����[�X�ɂȂ�
	return (old ^ now) & old & 1;

}

/* ========================================
   �E�X�e�B�b�N�X�����͊֐�
   ----------------------------------------
   ���e�F�E�X�e�B�b�N�̌X�������擾����
   ----------------------------------------
   �ߒl�F�X�����x,y(-1.0�`1.0)
   ======================================== */
TTriType<float> IsStickRight()
{
	return g_Controller.GetStickRight();
}

/* ========================================
   ���X�e�B�b�N�X�����͊֐�
   ----------------------------------------
   ���e�F���X�e�B�b�N�̌X�������擾����
   ----------------------------------------
   �ߒl�F�X�����x,y(-1.0�`1.0)
   ======================================== */
TTriType<float> IsStickLeft()
{
	return g_Controller.GetStickLeft();
}