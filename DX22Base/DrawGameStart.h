/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���X�^�[�g�`��p�w�b�_
	---------------------------------------
	DrawAnimation.h

	�쐬��
			nieda

	�ύX����
	�E2023/12/12 �V�K�쐬 nieda

========================================== */

#ifndef __DRAW_GAMESTART_H__	//DrawAnimation.h�C���N���[�h�K�[�h
#define __DRAW_GAMESTART_H__

// =============== �C���N���[�h ===================
#include "DrawAnimation.h"

// =============== �N���X��` =====================
class CDrawStart :public CDrawAnim	//UI�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	CDrawStart(CCamera*);	// �R���X�g���N�^
	~CDrawStart() {};		// �f�X�g���N�^
protected:
	// ===�����o�ϐ��錾=====
};	//�Q�[���X�^�[�gUI�A�j���[�V����

#endif	//!__DRAW_GAMESTART_H__


