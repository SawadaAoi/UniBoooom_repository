/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�R���{UI�p�w�b�_
	------------------------------------
	Combo.h
	------------------------------------
	�쐬��
		�V�c����
	�ύX����
	�E2023/11/21 �쐬 Sawada

========================================== */
#ifndef __COMBO_H__
#define __COMBO_H__

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"

// =============== �N���X��` =====================
class CCombo
{
public:
	// ===�v���g�^�C�v�錾===
	CCombo();
	~CCombo();
	void Update();
	void Draw();



private:
	// ===�����o�ϐ��錾===
	Texture* m_pTextureNum;



};


#endif // __COMBO_H__