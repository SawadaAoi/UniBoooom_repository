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
	�E2023/11/16 �V�K�쐬 �m�}����
	�E2023/11/29 �A�j���[�V�����Đ��p�ϐ��ǉ� �m�}����

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
		HEART_FULL,			// ���^���̃n�[�g
		HEART_HALF,			// �����̃n�[�g
		HEART_NONE,			// ��̃n�[�g
		HEART_FH_ANIM,		// �n�[�g�����^���������Ɍ���A�j���[�V����
		HEART_HE_ANIM,		// �n�[�g����������Ɍ���A�j���[�V����
		HEART_MAX,			// �n�[�g�̃e�N�X�`���̍ő吔
	};

public:
	// ===�����o�֐��錾===
	CHP_UI(const int* pPlayerHp);		// �R���X�g���N�^
	~CHP_UI();							// �f�X�g���N�^
	void Update();				// �X�V����
	void Draw();				// �`�揈��


private:
	// ===�����o�ϐ��錾===
	Texture*	m_pTexture[HEART_MAX];		// �e�N�X�`���p�|�C���^
	const int*	m_pPlayerHp;				// �v���C���[��HP�p�|�C���^
	int m_nPlayerOldHp;						// �ύX�O��HP���i�[
	bool m_bPlayAnim;	// HP�̃A�j���[�V�������Đ����邩����

	int m_nCnt;			// �A�j���[�V�����؂�ւ��J�E���g�p
	float m_fUVposX;	// �e�N�X�`���̉�������
	float m_fUVposY;	// �e�N�X�`���̏c������
	int m_nCntWidth;	// �e�N�X�`���̉��������J�E���g�p
	int m_nCntHeight;	// �e�N�X�`���̏c�������J�E���g�p
};

#endif	// !__HP_UI_H__
