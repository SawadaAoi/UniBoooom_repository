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
	�E2024/01/26 ���������₷���C��&&�g�[�^���X�R�A���Z�A�j�������ǉ� sawada
	�E2024/02/02 �Q�[���I���ԍۂ̉��Z�X�R�A���g�[�^���X�R�A�ɔ��f�����悤�� suzumura

========================================== */
#ifndef __TOTALSCORE_H__
#define __TOTALSCORE_H__

// =============== �C���N���[�h ===================
#include <Texture.h>
#include"Combo.h"
#include <vector>
#include "Defines.h"
#include "DiType.h"
#include "Timer.h"
#include "Player.h"
// =============== �N���X��` =====================
class CTotalScore
{
public:
	// ===�\���̒�`=========
	typedef struct
	{
		int   nAddScore;				// �X�R�A
		float fCombScoreMult;			// �R���{�X�R�A�{��
		bool  bEndComboFlg;				// �R���{�\���I���t���O(true:�R���{�I��)
		int   nDispFrame;				// �c�`��p���Z�l
		bool  bDispEndFlg;				// �X�R�A���Z�l�\���I���t���O
		int	  nDispComMultFrame;		// �R���{�{���\���p���Z�l
		bool  bDispComMultEndFlg;		// �X�R�A���Z�l�\���I���t���O
		bool  bDispGameEndFlg;				// �X�R�A���Z�ɂ�����v���C�I�����t���O

	}PlusScore;	// �X�R�A�������܂Ƃ�

	// �����\���p
	typedef struct
	{
		TDiType<float> fSize;
		TDiType<float> fPos; 
		TDiType<float> fUVSize; 
		float spaceW; 
		Texture* pTexture; 
		int digits;

	}NumbersParam;

	// �摜���
	enum TextureType
	{
		NUM_TOTAL_SCORE,
		NUM_ADD_SCORE,
		BG_TOTAL_SCORE,
		BG_ADD_SCORE,

		TEXTURE_MAX,
	};

public:
	CTotalScore(CPlayer* player, CTimer* timer);
	~CTotalScore();

	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	void SetAddScore(CCombo::ComboInfo comboInfo,int num);
	void ComboCheck(CCombo::ComboInfo comboInfo, int num);
	void AddTotalScore(int addScore);

	int GetTotalScore();
	std::vector<int> digitsToArray(int score, int digits);	//�����̐������e��1���z��ɓ����
private:
	void TotalScoreMove();

	void DrawBGTotalScore();			// �g�[�^���X�R�A�̔w�i�`��
	void DrawTotalScore();
	void DrawAddScore(int nNum, int lineNum);
	void DrawBGAddScore(int lineNum);		// ���Z�X�R�A�̔w�i�`��
	void DrawScoreComboMulti(int nNum, int lineNum);

	void DrawTexture(TDiType<float> fSize, TDiType<float> fPos, TDiType<float> fUVSize, TDiType<float> fUVPos, Texture * pTexture);
	void DrawNumber(int dispNum, TDiType<float> fSize, TDiType<float> fPos, TDiType<float> fUVSize, float spaceW, float spaceH, Texture* pTexture, int digits);

	CTotalScore::PlusScore ResetPlusScore();

	int m_nTotalScoreDisp;
	int m_nTotalScore;
	int m_nToScoreAddCnt;
	int m_nToScoAddPoint;
	
	PlusScore m_AddScore[MAX_COMBO_NUM];
	CCombo::ComboInfo* m_pComboInfo;

	Texture* m_pTexture[TEXTURE_MAX];

	CCombo* m_pCombo;
	int nArraySize;
	std::vector<int> TotalScoreArray;	//�e��1������邽�߂̔z��

	CPlayer* m_pPlayer;
	CTimer* m_pTimer;
	

};




#endif // !__TOTALSCORE_H__

