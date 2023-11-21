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
#include "Object.h"
#include "GameParameter.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const int	MAX_COMBO_NUM = 5;		// �ő哯���R���{��
#endif

// =============== �N���X��` =====================
class CCombo
{
public:
	// ===�\���̒�`=========
	typedef struct
	{
		int dCnt;		// �R���{��
		int dDispFrame;	// �c�`��p���Z�l
		bool bEndFlg;	// �R���{�I���t���O
	}ComboInfo;	// �R���{�������܂Ƃ�

public:
	// ===�v���g�^�C�v�錾===
	CCombo();
	~CCombo();
	void Update();
	void Draw();

	int FirstComboSet();
	void AddCombo(int num);
	int GetCombo(int num);
	void EndCombo(int num);
	void DisplayNumber(int cnt, float shiftPosY);

private:
	// ===�����o�ϐ��錾===
	Texture* m_pTextureNum;		// �����摜
	ComboInfo m_dComboInfo[MAX_COMBO_NUM];	// �R���{�p���܂Ƃ�

};


#endif // __COMBO_H__