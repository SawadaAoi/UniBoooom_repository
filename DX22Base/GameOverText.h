/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���X�^�[�g�`��p�w�b�_
	---------------------------------------
	GameOverText.h

	�쐬��
			nieda

	�ύX����
	�E2023/12/17 �V�K�쐬 nieda
	�E2024/02/13 �J�����폜 takagi

========================================== */

#ifndef __GAMEOVER_TEXT_H__	//DrawAnimation.h�C���N���[�h�K�[�h
#define __GAMEOVER_TEXT_H__

// =============== �C���N���[�h ===================
#include "DrawAnimation.h"

// =============== �N���X��` =====================
class COverText :public CDrawAnim	//UI�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	COverText();		// �R���X�g���N�^
	~COverText() {};	// �f�X�g���N�^
protected:
	// ===�����o�ϐ��錾=====
};	//�Q�[���X�^�[�gUI�A�j���[�V����

#endif	//!__GAMEOVER_TEXT_H__
