/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p2D�I�u�W�F��`
	---------------------------------------
	TitleObj.h

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/17 ChackPutOut()�֐��ǉ��E�����Q�Ɖ� takagi
	�E2024/02/05 ���t�@�N�^�����O takagi

========================================== */

#ifndef __TITLE_OBJ_H__	//TitleObj.h�C���N���[�h�K�[�h
#define __TITLE_OBJ_H__

// =============== �C���N���[�h =====================
#include "2dPolygon.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTitleObj :public C2dPolygon	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CTitleObj();			//�R���X�g���N�^
	virtual ~CTitleObj();	//�f�X�g���N�^
};	//�^�C�g���p�I�u�W�F

#endif	//!__TITLE_OBJ_H__