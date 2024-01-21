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

========================================== */

#ifndef __SHADOW_H__	//Shadow.h�C���N���[�h�K�[�h
#define __SHADOW_H__

// =============== �C���N���[�h ===================
#include "Texture.h"	// �e�N�X�`���p�w�b�_
#include "2dObject.h"		// �I�u�W�F�N�g�p�w�b�_
#include "Camera.h"		// �J�����p�w�b�_

// =============== �N���X��` =====================
class CShadow
	:public C2dObject
{
public:
	CShadow();		// �R���X�g���N�^
	CShadow(float fScale);		// �R���X�g���N�^
	~CShadow();		// �f�X�g���N�^
	void Update();	// �X�V�֐�
private:
	bool m_bDisp;				// �\�����邩����
	Texture* m_pTextureShadow;	// �e�N�X�`���N���X�̃|�C���^
};	// �e

#endif	//!__SHADOW_H__
