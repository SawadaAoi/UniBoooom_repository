/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g�����S��`
	---------------------------------------
	TitleLogo.h

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/17 �����Q�Ɖ� takagi
	�E2024/02/02 ���t�@�N�^�����O takagi
	�E2024/02/05 ���t�@�N�^�����O takagi

========================================== */

#ifndef __TITLE_LOGO_H__	//TitleLogo.h�C���N���[�h�K�[�h
#define __TITLE_LOGO_H__

// =============== �C���N���[�h =====================
#include "TitleInitZoomOut.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTitleLogo :public CTitleInitZoomOut	//�J�n���Y�[���A�E�g����^�C�g���p���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CTitleLogo();					//�R���X�g���N�^
	virtual ~CTitleLogo();			//�f�X�g���N�^
	virtual void Update() final;	//�X�V
};	//�^�C�g�����S

#endif	//!__TITLE_LOGO_H__