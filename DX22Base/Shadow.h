/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�e�\���p�N���X��`
	---------------------------------------
	Shadow.h
	---------------------------------------
	�쐬�� nieda

	�ύX����
	�E2023/11/27 ���� nieda
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi
	�E2024/01/22 ���t�@�N�^�����O takagi

========================================== */

#ifndef __SHADOW_H__	//Shadow.h�C���N���[�h�K�[�h
#define __SHADOW_H__

// =============== �C���N���[�h ===================
#include "2dObject.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CShadow :public C2dObject	//2D�I�u�W�F�N�g
{
public:
	CShadow();				// �R���X�g���N�^
	CShadow(float fScale);	// �R���X�g���N�^
	~CShadow();				// �f�X�g���N�^
};	//�e

#endif	//!__SHADOW_H__
