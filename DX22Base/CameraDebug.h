/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�f�o�b�O�p�J������`
	------------------------------------
	CameraDebug.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/04 ���� takagi
	�E2023/11/06 �R�[�f�B���O�K��K�p�E�ǐՑΏۓo�^�@�\�쐬 takagi
	�E2023/11/07 �R�����g�C�� takagi

========================================== */

#ifndef ___CAMERA_DEBUG_H___
#define ___CAMERA_DEBUG_H___

// =============== �C���N���[�h ===================
#include "Camera.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CCameraDebug :public CCamera	//�J����
{
public:
	// ===�v���g�^�C�v�錾===
	CCameraDebug();		//�R���X�g���N�^
	~CCameraDebug();	//�f�X�g���N�^
	void Update();		//�X�V
};	//�f�o�b�O�p�J����

#endif // !___CAMERA_DEBUG_H___