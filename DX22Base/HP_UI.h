/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HP�e�N�X�`���\���Ǘ��p�w�b�_
	------------------------------------
	HpManager.h
	------------------------------------
	�쐬��	�m�}����

	�ύX����
	�E2023/11/16 �V�K�쐬 Nieda
	�E2023/11/28 ����������悤�ɏC�� Sawada

========================================== */
#ifndef __HP_UI_H__
#define __HP_UI_H__

// =============== �C���N���[�h ===================
#include "Texture.h"	// �e�N�X�`���p�w�b�_


// =============== �N���X��` =====================
class CHP_UI
{
public:
	enum HEART_STATE
	{
		HEART_FULL,
		HEART_HALF,
		HEART_NONE,
		HEART_MAX,
	};

public:
	// ===�����o�֐��錾===
	CHP_UI(const int* pPlayerHp);		// �R���X�g���N�^
	~CHP_UI();				// �f�X�g���N�^
	void Update();				// �X�V����
	void Draw();				// �`�揈��


private:
	// ===�����o�ϐ��錾===
	Texture*	m_pTexture[HEART_MAX];		// �e�N�X�`���p�|�C���^
	const int*	m_pPlayerHp;				// �v���C���[��HP�p�|�C���^


};

#endif	// !__HP_UI_H__
