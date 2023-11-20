/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���V�[����`
	---------------------------------------
	Title.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/10/26 ������ takagi
	�E2023/11/05 ���i�K�̃R�[�f�B���O�K��K�p takagi
	�E2023/11/07 �R�����g�C�� takagi
	�E2023/11/16 �I�[�o�[���C�h�֐��ǉ� takagi

========================================== */

#ifndef __TITLE_H__	//Title.h�C���N���[�h�K�[�h
#define __TITLE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_
#include "Texture.h"

// =============== �N���X��` =====================
class CTitle :public CScene	//�V�[��
{
public:
	// =============== �v���g�^�C�v�錾 ===============
	CTitle();							//�R���X�g���N�^
	~CTitle();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();					//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
	void Draw2d(float, float, float, float, Texture*);
private:
	Texture* m_pTexture;
};	//�^�C�g��

#endif	//!__TITLE_H__