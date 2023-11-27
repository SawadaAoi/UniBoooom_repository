/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�e�\���p�N���X��`
	---------------------------------------
	Shadow.h

	�쐬�� nieda

	�ύX����
	�E2023/11/27 ���� nieda
========================================== */

#ifndef __SHADOW_H__	// Shadow.h�C���N���[�h�K�[�h
#define __SHADOW_H__

// =============== �C���N���[�h ===================
#include "Texture.h"	// �e�N�X�`���p�w�b�_
#include "Object.h"		// �I�u�W�F�N�g�p�w�b�_
#include "Camera.h"		// �J�����p�w�b�_

// =============== �N���X��` =====================
class CShadow
{
public:
	CShadow();		// �R���X�g���N�^
	~CShadow();		// �f�X�g���N�^
	void Update();	// �X�V�֐�
	void Draw(tagTransform3d m_Pos, float fscale, CCamera* pCamera);	// �`��֐�
private:
	bool m_bDisp;				// �\�����邩����
	Texture* m_pTextureShadow;	// �e�N�X�`���N���X�̃|�C���^
	CObject* m_pObject;			// �I�u�W�F�N�g�N���X�̃|�C���^
};	// �e

#endif	//!__SHADOW_H__
