/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�w�i��`
	---------------------------------------
	TitleBgBase.h

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/17 �ŏ��g�傳�ꏙ�X�ɏk������悤�� takagi
	�E2024/02/05 ���t�@�N�^�����O takagi

========================================== */

#ifndef __TITLE_BG_BASE_H__	//TitleBgBase.h�C���N���[�h�K�[�h
#define __TITLE_BG_BASE_H__

// =============== �C���N���[�h =====================
#include "TitleInitZoomOut.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTitleBgBase :public CTitleInitZoomOut	//�J�n���Y�[���A�E�g����^�C�g���p���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CTitleBgBase();				//�R���X�g���N�^
	virtual ~CTitleBgBase();	//�f�X�g���N�^
};	//�^�C�g���p�w�i

#endif	//!__TITLE_BG_BASE_H__