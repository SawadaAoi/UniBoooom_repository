/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HP�e�N�X�`���\���Ǘ��p�w�b�_
	------------------------------------
	HpManager.h
	------------------------------------
	�쐬��	�m�}����

	�ύX����
	�E2023/11/16 �V�K�쐬 �m�}����

========================================== */
#ifndef __HP_UI_H__
#define __HP_UI_H__

// =============== �C���N���[�h ===================
#include "Texture.h"	// �e�N�X�`���p�w�b�_
#include <vector>

// =============== �N���X��` =====================
class CHP_UI
{
public:
	enum HEART_STATE
	{
		HEART_FULL,
		HEART_NONE,
		HEART_MAX,
	};

public:
	// ===�����o�֐��錾===
	CHP_UI(const int* pPlayerHp);		// �R���X�g���N�^
	~CHP_UI();				// �f�X�g���N�^
	void Update();				// �X�V����
	void Draw();				// �`�揈��
	void Draw2d(float, float, float, float, Texture*);	// �`�揈��

	void SetHpTexture();

private:
	// ===�����o�ϐ��錾===
	Texture*	m_pTexture[HEART_MAX];		// �e�N�X�`���p�|�C���^
	std::vector<HEART_STATE>	m_HpState;
	const int*	m_pPlayerHp;				// �v���C���[��HP�p�|�C���^

};

#endif	// !__HP_UI_H__
