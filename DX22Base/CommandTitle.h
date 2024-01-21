/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�R�}���h��`
	---------------------------------------
	CommandTitle.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __COMMAND_TITLE_H__	//CommandTitle.h�C���N���[�h�K�[�h
#define __COMMAND_TITLE_H__

// =============== �C���N���[�h =====================
#include "TitleObj.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CCommandTitle :public CTitleObj	//���ʃI�u�W�F
{
private:
	enum E_TEXTURE
	{
		E_TEXTURE_UNSELECTED,	//��I�����
		E_TEXTURE_SELECTED,		//�I�����
		E_TEXTURE_DECIDE,		//������
		E_TEXTURE_MAX,			//�v�f��
	};	//�e�N�X�`�����
public:
	// ===�v���g�^�C�v�錾===
	CCommandTitle(const int& nWaitTime);	//�R���X�g���N�^
	~CCommandTitle();						//�f�X�g���N�^
	void Update() override;					//�X�V
	void Selected();						//�I����ԉ�
	void UnSelected();						//��I����ԉ�
	void Decide();							//����
private:
	// ===�ϐ��錾===
	E_TEXTURE m_eTexNo;			//�e�N�X�`����
	TDiType<float> m_fScale;	//�g�k��
	int* m_pnTimer;				//����e�N�X�`���\�����Ԍv���p
};	//�^�C�g���p�R�}���h

#endif	//!__COMMAND_TITLE_H__