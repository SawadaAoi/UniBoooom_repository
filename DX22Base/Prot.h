/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�v���g�^�C�v�V�[����`
	---------------------------------------
	Prot.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/05 ���� takagi
	�E2023/11/07 �R�����g�C�� takagi

========================================== */

#ifndef __PROT_H__
#define __PROT_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CProt :public CScene	//�V�[��
{
public:
	// ===�v���g�^�C�v�錾===
	CProt();							//�R���X�g���N�^
	~CProt();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw() const;					//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
};	//�^�C�g��

#endif	//!__PROT_H__