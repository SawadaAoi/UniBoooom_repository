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

#ifndef __HP_MANAGER_H__
#define __HP_MANAGER_H__

// =============== �C���N���[�h ===================
#include "HpUI.h"

// =============== �萔��` =======================
#define MAX_HP	(5)		// HP�̍ő吔

// =============== �N���X��` =====================
class CHpManager
{
public:
	// ===�����o�֐��錾===
	CHpManager(const int*);		// �R���X�g���N�^
	~CHpManager();				// �f�X�g���N�^
	void Update();				// �X�V����
	void Draw();				// �`�揈��
private:
	// ===�����o�ϐ��錾===
	CHpUI* m_pUI[MAX_HP];		// HP�̃e�N�X�`���p�|�C���^
	const int* m_pnPlayerHp;	// �v���C���[��HP�p�|�C���^
};

#endif	// !__HP_MANAGER_H__
