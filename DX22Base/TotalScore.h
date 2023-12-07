/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �g�[�^���X�R�A�w�b�_�[
   ---------------------------------------
   TotalScore.h

   �쐬�� �R�{�M��

   �ύX����
	�E2023/11/22�@�쐬 yamamoto
	�E2023/11/23�@score�\���́Acombo�̍\���̂̏��擾�����ǉ� yamamoto
	�E2023/12/07 �Q�[���p�����[�^�Ɉˑ����Ă����̂ŏC�� takagi

========================================== */
#ifndef __TOTALSCORE_H__
#define __TOTALSCORE_H__

// =============== �C���N���[�h ===================
#include <Texture.h>
#include"Combo.h"
#include <vector>
// =============== �N���X��` =====================
class CTotalScore
{
public:
	// ===�\���̒�`=========
	typedef struct
	{
		int   nAddScore;				// �X�R�A
		float fComboMagnification;	//�R���{�{��
		bool  bEndComboFlg;			// �R���{�\���I���t���O
		bool  bDispTotalScoreFlg;	// �X�R�A�\���I���t���O
		int   nDispFrame;				// �c�`��p���Z�l
		bool  bDispFlg;				
	}PlusScore;	// �X�R�A�������܂Ƃ�
public:
	CTotalScore();
	~CTotalScore();

	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	void AddScore(CCombo::ComboInfo comboInfo,int num);
	void ComboCheck(CCombo::ComboInfo comboInfo, int num);
	void AddTotalScore();
	int GetTotalScore();
	std::vector<int> digitsToArray(int score);	//�����̐������e��1���z��ɓ����
private:
	int m_nTotalScore;
	
	PlusScore m_PlusScore[MAX_COMBO_NUM];
	CCombo::ComboInfo* m_pComboInfo;
	Texture* m_pToScoreTexture;
	Texture* m_pPlusScoreTexture;
	CCombo* m_pCombo;
	int nArraySize;
	std::vector<int> TotalScoreArray;	//�e��1������邽�߂̔z��
	std::vector<int> digitArray;//digits�������ɓ����
	std::vector<int> digits;//digits�������ɓ����
	

};




#endif // !__TOTALSCORE_H__

