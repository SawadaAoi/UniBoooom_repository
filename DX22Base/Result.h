/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���U���g�V�[����`
	---------------------------------------
	Result.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/08 �V�[���J�ڗp�ɕϐ��ǉ� takagi
	�E2023/12/11 ���щ��\�� takagi
	�E2023/12/25 �\�����e�̕ύX Sawada

========================================== */

#ifndef __RESULT_H__	//Result.h�C���N���[�h�K�[�h
#define __RESULT_H__

// =============== �C���N���[�h ===================
#include "Scene.h"		//�e�̃w�b�_
#include "Texture.h"
#include "BattleData.h"	//�����o�̃w�b�_
#include <vector>		//�z��^�R���e�i
#include "2dPolygon.h"	// 2D�I�u�W�F�N�g�p
#include "NumberText.h"

// =============== �N���X��` =====================
class CResult :public CScene	//�V�[��
{
public:
	// ===�񋓒�`===========
	enum E_TEXTURE	// �\���摜
	{
		BG_SCREEN,			// ��ʑS�̂̔w�i
		BG_PANEL,			// �e���ڂ̔w�i(�����w�i)
		RESULT_TEXT,		// ����(Result)
		SVL_TIME_TEXT,		// ����(��������)
		SCORE_TEXT,			// ����(SCORE)	
		HIGH_SCORE_TEXT,	// ����(HISCORE)
		NEW_RECORD_TEXT,	// ����(NEW RECORD)
		HUNT_TEXT,			// ����(�X���C��������)
		TOTAL_HUNT_TEXT,	// ����(��������)
		SLIME_BLUE,			// �X���C���摜(��)
		SLIME_GREEN,		// �X���C���摜(��)
		SLIME_YELLOW,		// �X���C���摜(��)
		SLIME_RED,			// �X���C���摜(��)
		SLIME_BOSS,			// �X���C���摜(�{�X)
		MAX_COMBO_TEXT,		// ����(�ő�R���{��)

		NUM,				// ����
		COLON,				// �R����
		LINE,				// ��
		MULTI,				// �~
		PARENTHESIS,		// ()

		WARNING_STAGE_1,	// �X�e�[�W1�̎�z��
		WARNING_STAGE_2,	// �X�e�[�W2�̎�z��
		WARNING_STAGE_3,	// �X�e�[�W3�̎�z��
		CLEAR_STAMP,		// CLEAR�X�^���v

		TEXTURE_MAX,

	};


public:
	// =============== �v���g�^�C�v�錾 ===============
	CResult();							//�R���X�g���N�^
	~CResult();							//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();					//�`��	
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:
	void DrawBgScreen();
	void DrawWarningTexture();
	void DrawSurvivalTime();
	void DrawScore();
	void DrawHunt();
	void DrawMaxCombo();

	void DispTime();
	void DispNum(int dispNum, int nDigits, TDiType<float> pos, TDiType<float> size, float NumSpace);
	void NumStorage(std::vector<int>* digitArray,int nNumber, int nDigits);

	// =============== �����o�ϐ���` ===============
	
	Texture* m_pTexture[TEXTURE_MAX];
	BattleData m_Data;					//�퓬����

};	//���U���g

#endif	//!__RESULT_H__