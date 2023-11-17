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
#define MAX_HP	(5)

// =============== �N���X��` =====================
class ChpManager
{
public:
	// ===�����o�֐��錾===
	ChpManager();
	~ChpManager();
	void Update();
	void Draw();
private:
	// ===�����o�ϐ��錾===
	CHpUI* m_pUI[MAX_HP];
	int m_playerHP;
	int m_playerOldHP;
};

#endif	// !__HP_MANAGER_H__
