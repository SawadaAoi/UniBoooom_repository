/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ����`
   ---------------------------------------
   Sphere.h

   �쐬��	takagi

   �ύX����
   �E2023/11/05 ���� takagi
   �E2023/11/09 �C���N���[�h�K�[�h�C�� takagi


   ======================================== */

#ifndef __SPHERE_H__
#define __SPHERE_H__

// =============== �C���N���[�h ===================
#include "Geometry.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CSphere :public CGeometry	//�`��
{
	//static const int CIRCLE_DETAIL = 16;
public:
	// =============== �v���g�^�C�v�錾 ===============
	CSphere();				//�R���X�g���N�^
	CSphere(CSphere& Obj);	//�R�s�[�R���X�g���N�^
	~CSphere();				//�f�X�g���N�^
	void Draw();			//�`��
};	//��

#endif //!__SPHERE_H__