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
#include "Texture.h"	// �e�N�X�`���p�w�b�_

// =============== �N���X��` =====================
class CHpManager
{
public:
	// ===�����o�֐��錾===
	CHpManager(const int*);		// �R���X�g���N�^
	~CHpManager();				// �f�X�g���N�^
	void Update();				// �X�V����
	void Draw();				// �`�揈��
	void Draw2d(float, float, float, float, Texture*);	// �`�揈��
private:
	// ===�����o�ϐ��錾===
	Texture* m_pTexture[2];		// �e�N�X�`���p�|�C���^
	const int* m_pnPlayerHp;	// �v���C���[��HP�p�|�C���^
	bool m_bLost;				// HP�����ɂ��\���ؑ֗p�t���O
};

#endif	// !__HP_MANAGER_H__
