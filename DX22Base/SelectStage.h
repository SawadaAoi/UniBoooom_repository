/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�Z���N�g��`
	---------------------------------------
	SelectStage.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.h�C���N���[�h�K�[�h
#define __SELECT_STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CSelectStage :public CScene	//�V�[��
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	CSelectStage();						//�R���X�g���N�^
	~CSelectStage();					//�f�X�g���N�^
	void Update();						//�X�V
	void Draw() const;					//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
};	//�X�e�[�W�Z���N�g

#endif	//!__SELECT_STAGE_H__