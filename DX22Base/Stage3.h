/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W3��`
	---------------------------------------
	Stage3.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 LoadSE���I�[�o�[���C�h yamashita

========================================== */

#ifndef __STAGE3_H__	//Stage3.h�C���N���[�h�K�[�h
#define __STAGE3_H__

// =============== �C���N���[�h ===================
#include "Stage.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CStage3 :public CStage	//�X�e�[�W
{
public:
	// ===�v���g�^�C�v�錾===
	CStage3();							//�R���X�g���N�^
	~CStage3();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();					//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
};	//�X�e�[�W3

#endif	//!__STAGE3_H__