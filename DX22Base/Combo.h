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
	�E2023/11/23 �\���̂ɃX�R�A��ǉ��@yamamoto
	�E2023/11/30 �A�j���[�V�����p�ϐ��ǉ��@nieda
	�E2023/12/07 �Q�[���p�����[�^����萔�ړ� takagi

========================================== */
#ifndef __COMBO_H__
#define __COMBO_H__

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include <Texture.h>
#include "Object.h"
#include "DrawAnimation.h"
class CTotalScore;

// =============== �萔��` =======================
const int	MAX_COMBO_NUM = 5;					// �ő哯���R���{��

// =============== �N���X��` =====================
class CCombo
{
public:
	// ===�\���̒�`=========
	typedef struct
	{
		int dComboCnt;		// �R���{��
		int nOldComboCnt;	// �R���{���i�����������̃`�F�b�N�Ɏg�p�j

		int dDispFrame;	// �c�`��p���Z�l
		bool bEndFlg;	// �R���{�I���t���O
		int dScore;		// �X�R�A�i�A���̂��тɉ��Z�����j
	}ComboInfo;	// �R���{�������܂Ƃ�

	enum TEXTURE_KIND
	{
		TEX_NUM,
		TEX_BG,

		TEX_MAX,
	};

public:
	// ===�v���g�^�C�v�錾===
	CCombo();
	~CCombo();
	void Update();
	void Draw();

	int FirstComboSet();
	void AddCombo(int num);
	void AddScore(int num,int combo);
	void EndCombo(int num);


	void SetTotalScore(CTotalScore* pTotalScore);


	int GetComboNum(int num);
	int GetComboEndFlg(int num);
	int GetMaxCombo();
private:
	void DisplayNumber(int cnt, int lineNum);
	void DispComboBG(int ArrayNum, int lineNum);

	// ===�����o�ϐ��錾===
	Texture* m_pTexture[TEX_MAX];		// �����摜
	ComboInfo m_dComboInfo[MAX_COMBO_NUM];	// �R���{�p���܂Ƃ�
	CTotalScore* m_pTotalScore;	

	CDrawAnim* m_pComboBG[MAX_COMBO_NUM];		// �R���{�̔w�i�A�j���[�V����
	C2dPolygon* m_pTexNumber;

	int m_nMaxComboNum;
};


#endif // __COMBO_H__