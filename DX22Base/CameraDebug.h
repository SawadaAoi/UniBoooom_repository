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
	�E2023/11/10 �ϐ��ǉ� takagi
	�E2024/01/16 ����̂��߁A�C���N���[�h�K�[�h��___��__�ɕύX	takagi
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __CAMERA_DEBUG_H__	//CameraDebug.h�C���N���[�h�K�[�h
#define __CAMERA_DEBUG_H__

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
private:
	// ===�����o�ϐ��錾=====
	float m_fRadXZ;			//X-Z���W�̉�]�p(rad)
	float m_fRadY;			//Y-XZ���W�̉�]�p(rad)
};	//�f�o�b�O�p�J����

#endif	//!__CAMERA_DEBUG_H__