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
	�E2024/01/26 ����SE�ǉ� suzumura
	�E2024/01/26 �A�j���[�V�����ǉ� goto
	�E2024/02/03 ���U���g�\���ʒu�������� suzumura
	�E2024/02/09 GetType()�֐��폜 takagi

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
#include "DrawAnimation.h"
#include "Sound.h"
#include "FrameCnt.h"	//�������o�p


// =============== �N���X��` =====================
class CResult :public CScene	//�V�[��
{
public:
	// ===�񋓒�`===========
	enum E_TEXTURE	// �\���摜
	{
		BG_SCREEN_CLEAR,		// ��ʑS�̂̔w�i �ԁF�Q�[���N���A
		BG_SCREEN_GAMEOVER,		// ��ʑS�̂̔w�i �F�Q�[���I�[�o�[
		BG_PANEL_CLEAR,			// �e���ڂ̔w�i(�����w�i) �Ԙg�F�Q�[���N���A
		BG_PANEL_GAMEOVER,		// �e���ڂ̔w�i(�����w�i) �g�F�Q�[���I�[�o�[
		RESULT_TEXT,			// ����(Result)
		SVL_TIME_TEXT,			// ����(��������)
		SCORE_TEXT,				// ����(SCORE)	
		HIGH_SCORE_TEXT,		// ����(HISCORE)
		NEW_RECORD_TEXT,		// ����(NEW RECORD)
		HUNT_TEXT,				// ����(�X���C��������)
		TOTAL_HUNT_TEXT,		// ����(��������)
		SLIME_BLUE,				// �X���C���摜(��)
		SLIME_GREEN,			// �X���C���摜(��)
		SLIME_YELLOW,			// �X���C���摜(��)
		SLIME_RED,				// �X���C���摜(��)
		SLIME_BOSS,				// �X���C���摜(�{�X)
		MAX_COMBO_TEXT,			// ����(�ő�R���{��)

		NUM,					// ����
		COLON,					// �R����
		LINE,					// ��
		MULTI,					// �~
		PARENTHESIS,			// ()

		WARNING_STAGE_1,		// �X�e�[�W1�̎�z��
		WARNING_STAGE_2,		// �X�e�[�W2�̎�z��
		WARNING_STAGE_3,		// �X�e�[�W3�̎�z��
		CLEAR_STAMP,			// CLEAR�X�^���v
		SELECT,					// ����{�^��

		TEXTURE_MAX,

	};

	enum SE
	{
		SE_DECISION,	//���艹

		SE_MAX			//SE�̑���
	}; //SE

	enum E_2D_OBJ_ID
	{
		OBJ_BG_SCREEN,				// �w�i
		OBJ_BG_PANEL,				// ���ڔw�i
		OBJ_WARNING_STAGE,			// ��z���摜
		OBJ_CLEAR_STAMP,			// �X�^���v�摜
		OBJ_RESULT_TEXT,			// ���U���g(����)
		OBJ_SVL_TIME_TEXT,			// ��������(����)
		OBJ_SVL_TIME_SECOND_NUM,	// ��������(�b)
		OBJ_SVL_TIME_COLON,			// ��������(�R����)	
		OBJ_SVL_TIME_MINUTE_NUM,	// ��������(��)		
		OBJ_SVL_TIME_LINE,			// ��؂��
		OBJ_SCORE_TEXT,				// �X�R�A(����)
		OBJ_NEW_RECORD_TEXT,		// �V�L�^(����)
		OBJ_SCORE_NUM,				// �X�R�A(����)
		OBJ_HIGH_SCORE_TEXT,		// �n�C�X�R�A(����)
		OBJ_HIGH_SCORE_NUM,			// �n�C�X�R�A(����)
		OBJ_SCORE_LINE,				// ��؂��
		OBJ_HUNT_TEXT,				// ������(����)
		OBJ_SLIME_HUNT_BG,			// �������w�i�X���C���摜
		OBJ_SLIME_HUNT_NUM,			// �X���C���ʓ�����
		OBJ_PARENTHESIS,			// ()
		OBJ_MULTI,					// �~
		OBJ_MULTI_BLUE_SLIME,		// �X���C���摜�̈ʒu
		OBJ_MULTI_NUM,				// �X���C���̔{��
		OBJ_TOTAL_HUNT_TEXT,		// ��������(����)
		OBJ_TOTAL_HUNT_NUM,			// ��������(����)
		OBJ_HUNT_LINE,				// ��؂��
		OBJ_MAX_COMBO_TEXT,			// �ő�R���{��(����)
		OBJ_MAX_COMBO_NUM,			// �ő�R���{��(����)
		OBJ_SELECT_BUTTON,			// ���� 

		OBJ_2D_MAX,
	};

public:
	// =============== �v���g�^�C�v�錾 ===============
	CResult();													//�R���X�g���N�^
	~CResult();													//�f�X�g���N�^
	void Update();												//�X�V
	void Draw();												//�`��
	E_TYPE GetNext() const override;							//���̃V�[���Q�b�^

private:
	void DrawBgScreen();
	void DrawWarningTexture();
	void DrawSurvivalTime();
	void DrawScore();
	void DrawHunt();
	void DrawMaxCombo();

	void DispTime();
	void DispNum(int dispNum, int nDigits, E_2D_OBJ_ID objId, TTriType<float> fPos, float NumSpace);
	void NumStorage(std::vector<int>* digitArray,int nNumber, int nDigits);

	void LoadSound();								//�T�E���h�����[�h
	void PlaySE(SE se, float volume = 1.0f);		//SE���Đ�����
	// =============== �����o�ϐ���` ===============
	
	Texture* m_pTexture[TEXTURE_MAX];
	BattleData m_Data;					// �퓬����
	CDrawAnim* m_pTextureResultText;	// ���U���g�̕���
	int m_nButtonAlphaCnt;			// �_�ŗp
	int m_nNewRecoAlphaCnt;			// �_�ŗp

	C2dPolygon* m_p2dObj[OBJ_2D_MAX];

	int m_nStAnimCnt;
	bool m_nStartAnimEnd;

	//=====SE�֘A=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Decision.mp3",				// ���艹
	};


};	//���U���g

#endif	//!__RESULT_H__