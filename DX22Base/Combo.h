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
		int dCnt;		// �R���{��
		int dDispFrame;	// �c�`��p���Z�l
		bool bEndFlg;	// �R���{�I���t���O
		int dScore;		// �X�R�A�i�A���̂��тɉ��Z�����j
	}ComboInfo;	// �R���{�������܂Ƃ�

public:
	// ===�v���g�^�C�v�錾===
	CCombo();
	~CCombo();
	void Update();
	void Draw();

	int FirstComboSet();
	void AddCombo(int num);
	void AddScore(int num,int combo);
	int GetCombo(int num);
	void EndCombo(int num);
	void DisplayNumber(int cnt, float shiftPosY);
	void DrawTexture(float posX, float posY, float h, float w, Texture* pTexture);
	void SetTotalScore(CTotalScore* pTotalScore);

	int GetMaxCombo();
private:
	// ===�����o�ϐ��錾===
	Texture* m_pTextureNum[3];		// �����摜
	ComboInfo m_dComboInfo[MAX_COMBO_NUM];	// �R���{�p���܂Ƃ�
	CTotalScore* m_pTotalScore;	

	int m_nMaxComboNum;

	float m_fSizeX;		// ��UV���W�i�[�p
	float m_fSizeY;		// �cUV���W�i�[�p
	int m_nCntWidth;	// �e�N�X�`���̉��������J�E���g�p
	int m_nCntHeight;	// �e�N�X�`���̏c�������J�E���g�p
	int m_nCntOldCombo[MAX_COMBO_NUM];	// �R���{�������m�F�p
	int m_nCnt;			// �A�j���[�V�����؂�ւ��J�E���g�p
};


#endif // __COMBO_H__