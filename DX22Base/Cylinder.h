/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�~����`
	------------------------------------
	Cylinder.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/05 ���� takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __CYLINDER_H__	//Cylinder.h�C���N���[�h�K�[�h
#define __CYLINDER_H__

   // =============== �C���N���[�h ===================
#include "Geometry.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CCylinder :public CGeometry	//�`��
{
public:
	// ===�v���g�^�C�v�錾===
	CCylinder();				//�R���X�g���N�^
	CCylinder(CCylinder& Obj);	//�R�s�[�R���X�g���N�^
	~CCylinder();			//�f�X�g���N�^
	void Draw();		//�`��
};	//������

#endif	//!__CYLINDER_H__