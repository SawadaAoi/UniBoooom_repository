/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�Œ�J������`
	------------------------------------
	FixedCamera.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2024/01/16 ����̂��߁A�C���N���[�h�K�[�h��___��__�ɕύX	takagi
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __FIXED_CAMERA_H__	//FixedCamera.h�C���N���[�h�K�[�h
#define __FIXED_CAMERA_H__

// =============== �C���N���[�h ===================
#include "Camera.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CFixedCamera :public CCamera	//�J����
{
public:
	// ===�v���g�^�C�v�錾===
	void Update();		//�X�V
};	//�Œ�J����

#endif	//!__FIXED_CAMERA_H__