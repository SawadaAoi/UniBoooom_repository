/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���U���g�V�[����`
	---------------------------------------
	Result.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi

========================================== */

#ifndef __RESULT_H__	//Result.h�C���N���[�h�K�[�h
#define __RESULT_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CResult :public CScene	//�V�[��
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	CResult();							//�R���X�g���N�^
	~CResult();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw() const;					//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
};	//���U���g

#endif	//!__RESULT_H__