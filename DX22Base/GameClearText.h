/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���X�^�[�g�`��p�w�b�_
	---------------------------------------
	GameClearText.h
	---------------------------------------
	�쐬��	nieda

	�ύX����
	�E2023/12/17 �V�K�쐬 nieda
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __GAMECLEAR_TEXT_H__	//GameClearText.h�C���N���[�h�K�[�h
#define __GAMECLEAR_TEXT_H__

// =============== �C���N���[�h ===================
#include "DrawAnimation.h"

// =============== �N���X��` =====================
class CClearText :public CDrawAnim	//UI�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	CClearText(CCamera*);	// �R���X�g���N�^
	~CClearText() {};		// �f�X�g���N�^
protected:
	// ===�����o�ϐ��錾=====
};	//�Q�[���X�^�[�gUI�A�j���[�V����

#endif	//!__GAMECLEAR_TEXT_H__