/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���X�^�[�g�`��p�w�b�_
	---------------------------------------
	GameStartText.h
	---------------------------------------
	�쐬��	nieda

	�ύX����
	�E2023/12/12 �V�K�쐬 nieda
	�E2023/12/17 ���O�ύX nieda
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __GAMESTART_TEXT_H__	//GameStartText.h�C���N���[�h�K�[�h
#define __GAMESTART_TEXT_H__

// =============== �C���N���[�h ===================
#include "DrawAnimation.h"

// =============== �N���X��` =====================
class CStartText :public CDrawAnim	//UI�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	CStartText();	// �R���X�g���N�^
	~CStartText() {};		// �f�X�g���N�^
protected:
	// ===�����o�ϐ��錾=====
};	//�Q�[���X�^�[�gUI�A�j���[�V����

#endif	//!__GAMESTART_TEXT_H__