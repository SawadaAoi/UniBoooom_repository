/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�I���R�}���h��`
	---------------------------------------
	TitleCommandFinish.h

	�쐬��	takagi

	�ύX����
	�E2024/02/02 ���� takagi
	�E2024/02/05 ����i�s takagi

========================================== */

#ifndef __TITLE_COMMAND_FINISH_H__	//TitleCommandFinish.h�C���N���[�h�K�[�h
#define __TITLE_COMMAND_FINISH_H__

// =============== �C���N���[�h =====================
#include "TitleCommand.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTitleCommandFinish :public CTitleCommand	//�^�C�g���p�R�}���h
{
public:
	// ===�v���g�^�C�v�錾===
	CTitleCommandFinish();			//�R���X�g���N�^
	virtual ~CTitleCommandFinish();	//�f�X�g���N�^
};	//�I���R�}���h

#endif	//!__TITLE_COMMAND_FINISH_H__