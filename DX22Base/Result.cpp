/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	���U���g�V�[������
	---------------------------------------
	Result.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/11/20 ���e�N�X�`���\���A��ʑJ�� nieda
	�E2023/11/23 �R���g���[���[�ɑΉ� nieda
	�E2023/11/24 �R�����g�A�萔��`�A�񋓒ǉ� nieda
	�E2023/12/08 �V�[���J�ڗp�ɕϐ��ǉ� takagi
	�E2023/12/11 ���щ��\�� takagi
	�E2023/12/25 �\�����e�̕ύX Sawada
	�E2024/01/26 ����SE�ǉ� suzumura
	�E2024/01/26 �A�j���[�V�����ǉ� goto
	�E2024/02/01 �J�ڐ�ύX sawada
	�E2024/02/03 ���U���g�\���ʒu�������� suzumura


========================================== */

// =============== �C���N���[�h ===================
#include "Result.h"	//���g�̃w�b�_
#include "DirectXTex/TextureLoad.h"	
#include "FixedCamera.h"	//�C���X�^���X���
#include "Pos3d.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"
#include <array>					//�z��
#include <map>						//�A�z�^�R���e�i
#include "Defines.h"				//��ʃT�C�Y���


// =============== �萔��` ===================
const std::map<int, std::string> MAP_TEX_PATH = {
	{CResult::BG_SCREEN,		"Assets/Texture/Result/ResultBG.png"},			// ��ʑS�̂̔w�i
	{CResult::BG_PANEL,			"Assets/Texture/Result/result_waku.png"},		// �e���ڂ̔w�i(�����w�i)
	{CResult::RESULT_TEXT,		"Assets/Texture/Result/result.png"},			// ����(Result)
	{CResult::SVL_TIME_TEXT,	"Assets/Texture/Result/SurvivalTime.png"},		// ����(��������)
	{CResult::SCORE_TEXT,		"Assets/Texture/Result/SCORE.png"},				// ����(SCORE)	
	{CResult::HIGH_SCORE_TEXT,	"Assets/Texture/Result/HISCORE.png"},			// ����(HISCORE)
	{CResult::NEW_RECORD_TEXT,	"Assets/Texture/Result/NewRecord.png"},			// ����(NEW RECORD)
	{CResult::TOTAL_HUNT_TEXT,	"Assets/Texture/Result/TotalHunt.png"},			// ����(�X���C��������)
	{CResult::HUNT_TEXT,		"Assets/Texture/Result/slimeCnt.png"},			// ����(��������)
	{CResult::SLIME_BLUE,		"Assets/Texture/Result/Slime_Blue.png"},		// �X���C���摜(��)
	{CResult::SLIME_GREEN,		"Assets/Texture/Result/Slime_Green.png"},		// �X���C���摜(��)
	{CResult::SLIME_YELLOW,		"Assets/Texture/Result/Slime_Yellow.png"},		// �X���C���摜(��)
	{CResult::SLIME_RED,		"Assets/Texture/Result/Slime_Red.png"},			// �X���C���摜(��)
	{CResult::SLIME_BOSS,		"Assets/Texture/Result/Slime_Boss.png"},		// �X���C���摜(�{�X)
	{CResult::MAX_COMBO_TEXT,	"Assets/Texture/Result/MaxCombo.png"},			// ����(�ő�R���{��)
	{CResult::NUM,				"Assets/Texture/Result/ResultSpliteSheet.png"},	// ����
	{CResult::COLON,			"Assets/Texture/Result/Colon.png"},				// �R����
	{CResult::LINE,				"Assets/Texture/Result/Line.png"},				// ��
	{CResult::MULTI,			"Assets/Texture/Result/kakeru.png"},			// �~
	{CResult::PARENTHESIS,		"Assets/Texture/Result/parenthesis.png"},		// ()
	{CResult::WARNING_STAGE_1,	"Assets/Texture/Result/Lv1.png"},				// �X�e�[�W1�̎�z��
	{CResult::WARNING_STAGE_2,	"Assets/Texture/Result/Lv2.png"},				// �X�e�[�W2�̎�z��
	{CResult::WARNING_STAGE_3,	"Assets/Texture/Result/Lv3.png"},				// �X�e�[�W3�̎�z��
	{CResult::CLEAR_STAMP,		"Assets/Texture/Result/stamp.png"},				// CLEAR�X�^���v
	{CResult::SELECT,			"Assets/Texture/Result/Result_Button.png"},		// ����{�^��
};	


// �摜�\���p�p�����[�^�܂Ƃ�
typedef struct
{
	TDiType<float> fPos;
	TDiType<float> fSize;
}Display_Param;

typedef struct
{
	TTriType<float> fPos;
	TTriType<float> fSize;
}Display_Param_3;

const Display_Param WARNING_TEXTURE_PARAM	= { {260.0f, 380.0f} ,{460.0f, 580.0f} };	// ��z��
const Display_Param CLEAR_STAMP_PARAM		= { {260.0f, 380.0f} ,{460.0f, 580.0f} };	// �X�^���v
const Display_Param_3 RESULT_TEXT_PARAM = { { 275.0f, 660.0f, 1.0f},{ 640.0f,  280.0f, 1.0f} };	// ���U���g
const int			RESULT_TEXT_FLASH = 0.04 * 60;

const float DEF_NUM_SPACE = 68.0f;
const TDiType<int> NUM_SPLIT = { 5, 2 };
const TDiType<float> NUM_UVSCALE = { (1.0f / 5) ,(1.0f / 2) };

const Display_Param BG_SCREEN_PARAM		= { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },{ SCREEN_WIDTH, SCREEN_HEIGHT } };	// �w�i
const Display_Param BG_PANEL_PARAM		= { { 905.0f, SCREEN_HEIGHT / 2 } ,{ 750.0f, SCREEN_HEIGHT } };					// ���ڔw�i

const Display_Param SVL_TIME_TEXT_PARAM = { { 650.0f, 30.0f },{ 200.0f, 80.0f } };	// ��������(����)
const Display_Param SVL_TIME_NUM__PARAM = { { 1200.0f, 50.0f },{ 85.0f, 95.0f } };	// ��������(����)
const Display_Param SVL_TIME_LINE_PARAM = { { 907.0f, 100.0f },{ 729.0f, 5.0f } };	// ��
const float SVL_TIME_NUM_SPACE = 55.0f;		// ���Ԃ̊�(�� 12��:��33)

const Display_Param SCORE_TEXT_PARAM		= { { 655.0f, 130.0f },{ 220.0f, 75.0f } };		// �X�R�A(����)
const Display_Param NEW_RECORD_TEXT_PARAM	= { { 820.0f,180.0f },{ 170.0f, 55.0f } };		// �V�L�^(����)
const Display_Param SCORE_NUM_PARAM			= { { 1200.0f, 160.0f },{ 85.0f, 105.0f } };	// �X�R�A(����)
const Display_Param HIGH_SCORE_TEXT_PARAM	= { { 645.0f, 240.0f },{ 180.0f, 75.0f } };		// �n�C�X�R�A(����)
const Display_Param HIGH_SCORE_NUM_PARAM	= { { 1200.0f, 260.0f },{ 55.0f, 55.0f } };		// �n�C�X�R�A(����)
const Display_Param SCORE_LINE_PARAM		= { { 907.0f, 300.0f },{ 729.0f, 5.0f } };		// ��
const float SCORE_NUM_SPACE = 70.0f;
const float HIGH_SCORE_NUM_SPACE = 45.0f;


const Display_Param HUNT_TEXT_PARAM			= { { 710.0f, 340.0f },{ 330.0f, 110.0f } };	// ������(����)
const Display_Param SLIME_TEXTURE_PARAM		= { { 650.0f, 430.0f },{ 160.0f, 160.0f } };	// �X���C���摜
const float SLIME_SPACE_Y = 130.0f;	// �X���C���摜�̊�
const Display_Param SLIME_HUNT_NUM_PARAM	= { { 650.0f, 430.0f },{ 60.0f, 60.0f } };		// �X���C���ʓ�����
const Display_Param PARENTHESIS_PARAM		= { { 650.0f, 530.0f },{ 0.0f, 0.0f } };		// ()
const Display_Param MULTI_PARAM				= { { 650.0f, 510.0f },{ 40.0f, 40.0f } };		// �~
const Display_Param MULTI_SLIME_PARAM		= { { 615.0f, 510.0f },{ 30.0f, 30.0f } };		// �X���C���摜�̈ʒu
const Display_Param MULTI_NUM_PARAM			= { { 685.0f, 510.0f },{ 40.0f, 40.0f } };		// �X���C���̔{��
const Display_Param TOTAL_HUNT_TEXT_PARAM	= { { 670.0f, 560.0f },{ 250.0f, 80.0f } };		// ��������(����)
const Display_Param TOTAL_HUNT_NUM_PARAM	= { { 1200.0f, 580.0f },{ 85.0f, 105.0f } };	// ��������(����)
const Display_Param HUNT_LINE_PARAM			= { { 907.0f, 620.0f } , { 729.0f, 5.0f } };	// ��
const float HUNT_NUM_SPACE = 45.0f;															// �����Ԃ̋���


const Display_Param MAX_COMBO_TEXT_PARAM	= { { 695.0f, 655.0f } , {  300.0f, 90.0f } };	// �ő�R���{��(����)
const Display_Param MAX_COMBO_NUM_PARAM		= { { 1200.0f, 670.0f } ,{ 85.0f, 105.0f } };	// �ő�R���{��(����)

const Display_Param_3 SELECT_PARAM			= { { 65.0f, 40.0f, 1.0f } , { 130.0f, 65.0f, 1.0f } };		// ����{�^��
const float FLASH_BUTTON_TEXT_ADJUST		= 0.02f;										//�u����v�e�L�X�g�̓_�ŊԊu����

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CResult::CResult()
	: m_pSE{ nullptr }
	, m_pSESpeaker{ nullptr }
	, m_nButtonAlphaCnt(0)

{
	for (int i = 0; i < E_TEXTURE::TEXTURE_MAX; i++)
	{
		// ���U���g�摜�Ǎ�
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(MAP_TEX_PATH.at(i).c_str())))
		{
			MessageBox(NULL, "Result Texture", "Error", MB_OK);
		}
	}
	
	// ���U���g�����̃A�j���[�V�����̏�����
	m_pTextureResultText = new CDrawAnim(60, TDiType<int>(5, 12), RESULT_TEXT_FLASH);
	m_pTextureResultText->SetTexture(m_pTexture[E_TEXTURE::RESULT_TEXT]);
	m_pTextureResultText->SetPos(RESULT_TEXT_PARAM.fPos);
	m_pTextureResultText->SetSize(RESULT_TEXT_PARAM.fSize);
	m_pTextureResultText->SetLoopFlg(true);

	// ����{�^��������
	m_pSelectButton = new C2dPolygon();
	m_pSelectButton->SetTexture(m_pTexture[E_TEXTURE::SELECT]);
	m_pSelectButton->SetPos(SELECT_PARAM.fPos);
	m_pSelectButton->SetSize(SELECT_PARAM.fSize);

	// �f�[�^�󂯌p��
	m_Data.Load();	//�t�@�C���ɏオ���Ă������ǂݍ���

	//=== �T�E���h�t�@�C���ǂݍ��� =====
	LoadSound();

}

/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CResult::~CResult()
{
	// =============== �Z�[�u =====================
	m_Data.Save();	//�X�e�[�W�̃f�[�^�Z�[�u

	// �j������
	for (int i = 0; i < E_TEXTURE::TEXTURE_MAX; i++)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
	SAFE_DELETE(m_pTextureResultText);
	SAFE_DELETE(m_pSelectButton);
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::Update()
{
	// �X�y�[�X�L�[�����������A�܂��̓R���g���[����B�{�^������������ 
	if (IsKeyTrigger(VK_SPACE) || IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// �^�C�g���V�[���I���t���OON
		//===== SE�̍Đ� =======
		PlaySE(SE_DECISION);
	}

	// ���U���g�̕����̃A�j���[�V����
	m_pTextureResultText->Update();
	// ����{�^��
	m_pSelectButton->Update();
	m_nButtonAlphaCnt++;
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
	======================================== */
void CResult::Draw()
{
	
	DrawBgScreen();			// �w�i
	DrawWarningTexture();	// Result������z��
	DrawSurvivalTime();		// ��������
	DrawScore();			// �X�R�A
	DrawHunt();				// ������
	DrawMaxCombo();			// �R���{��
}

/* ========================================
	�w�i�`��֐�
	----------------------------------------
	���e�F�w�i��`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DrawBgScreen()
{
	// �S�̂̔w�i
	Draw2d(
		BG_SCREEN_PARAM.fPos.x, BG_SCREEN_PARAM.fPos.y,
		BG_SCREEN_PARAM.fSize.x, BG_SCREEN_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::BG_SCREEN]);

	// �E�����̊e���ڂ̔w�i
	Draw2d(
		BG_PANEL_PARAM.fPos.x,BG_PANEL_PARAM.fPos.y,
		BG_PANEL_PARAM.fSize.x,BG_PANEL_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::BG_PANEL]);
}

/* ========================================
	��z���`��֐�
	----------------------------------------
	���e�F��z����`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DrawWarningTexture()
{
	Texture* pWarningTex;	// ��z���摜

	// ���U���g����
	m_pTextureResultText->Draw();

	// �v���C�����X�e�[�W�ɂ���Ď�z���̉摜��ς���
	switch (m_Data.nStageNum)
	{
	case 1: pWarningTex = m_pTexture[E_TEXTURE::WARNING_STAGE_1]; break;
	case 2: pWarningTex = m_pTexture[E_TEXTURE::WARNING_STAGE_2]; break;
	case 3: pWarningTex = m_pTexture[E_TEXTURE::WARNING_STAGE_3]; break;
	}
	
	// ��z���\��
	Draw2d(
		WARNING_TEXTURE_PARAM.fPos.x,
		WARNING_TEXTURE_PARAM.fPos.y,
		WARNING_TEXTURE_PARAM.fSize.x,
		WARNING_TEXTURE_PARAM.fSize.y,
		pWarningTex);

	// �N���A�����ꍇ
	if (m_Data.bClearFlg)
	{
		// �X�^���v��\������
		Draw2d(
			CLEAR_STAMP_PARAM.fPos.x,
			CLEAR_STAMP_PARAM.fPos.y,
			CLEAR_STAMP_PARAM.fSize.x,
			CLEAR_STAMP_PARAM.fSize.y,
			m_pTexture[E_TEXTURE::CLEAR_STAMP]);
	}

	// ����{�^��
	m_pSelectButton->SetAlpha(fabs(cosf(m_nButtonAlphaCnt * FLASH_BUTTON_TEXT_ADJUST)));	// �_�łׁ̈A�����x�ύX
	m_pSelectButton->Draw();

}


/* ========================================
	�������ԕ`��֐�
	----------------------------------------
	���e�F�������Ԃ�`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DrawSurvivalTime()
{
	// ��������(����)
	Draw2d(
		SVL_TIME_TEXT_PARAM.fPos.x,
		SVL_TIME_TEXT_PARAM.fPos.y,
		SVL_TIME_TEXT_PARAM.fSize.x,
		SVL_TIME_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::SVL_TIME_TEXT]);

	// ��������(����)
	DispTime();

	// ��
	Draw2d(
		SVL_TIME_LINE_PARAM.fPos.x,
		SVL_TIME_LINE_PARAM.fPos.y,
		SVL_TIME_LINE_PARAM.fSize.x,
		SVL_TIME_LINE_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::LINE]);
}


/* ========================================
	�X�R�A�`��֐�
	----------------------------------------
	���e�F�X�R�A��`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DrawScore()
{
	// �X�R�A(����)
	Draw2d(
		SCORE_TEXT_PARAM.fPos.x,
		SCORE_TEXT_PARAM.fPos.y,
		SCORE_TEXT_PARAM.fSize.x,
		SCORE_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::SCORE_TEXT]);


	// ���X�R�A(����)
	DispNum(m_Data.nTotalScore, 5, SCORE_NUM_PARAM.fPos, SCORE_NUM_PARAM.fSize, SCORE_NUM_SPACE);

	// �n�C�X�R�A(����)
	Draw2d(
		HIGH_SCORE_TEXT_PARAM.fPos.x,
		HIGH_SCORE_TEXT_PARAM.fPos.y,
		HIGH_SCORE_TEXT_PARAM.fSize.x,
		HIGH_SCORE_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::HIGH_SCORE_TEXT]);

	// �n�C�X�R�A���X�V���Ă�����(�Q�[���I�����Ƀn�C�X�R�A���X�V�����)
	if (m_Data.nHighScore[m_Data.nStageNum-1] == m_Data.nTotalScore)
	{
		// �j���[���R�[�h(����)
		Draw2d(
			NEW_RECORD_TEXT_PARAM.fPos.x,
			NEW_RECORD_TEXT_PARAM.fPos.y,
			NEW_RECORD_TEXT_PARAM.fSize.x,
			NEW_RECORD_TEXT_PARAM.fSize.y,
			m_pTexture[E_TEXTURE::NEW_RECORD_TEXT]);

	}

	// �n�C�X�R�A(����)
	DispNum(m_Data.nHighScore[m_Data.nStageNum - 1], 5, HIGH_SCORE_NUM_PARAM.fPos, HIGH_SCORE_NUM_PARAM.fSize, HIGH_SCORE_NUM_SPACE);
	

	// ��
	Draw2d(
		SCORE_LINE_PARAM.fPos.x,
		SCORE_LINE_PARAM.fPos.y,
		SCORE_LINE_PARAM.fSize.x,
		SCORE_LINE_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::LINE]);
}


/* ========================================
	�������`��֐�
	----------------------------------------
	���e�F��������`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DrawHunt()
{
	// ������(����)
	Draw2d(
		HUNT_TEXT_PARAM.fPos.x,
		HUNT_TEXT_PARAM.fPos.y,
		HUNT_TEXT_PARAM.fSize.x,
		HUNT_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::HUNT_TEXT]);

	// �X�e�[�W�P�Ȃ�{�X��������\�����Ȃ�
	int nDispHuntNum = 5;	// �{�΁{���{�ԁ{�{�X���T
	if (m_Data.nStageNum == 1) nDispHuntNum = 4;	// �[�{�X���S

	// �X���C���̎�ސ����摜��\��
	for (int i = 0; i < nDispHuntNum; i++)
	{
		// �X���C���̉摜
		Draw2d(
			SLIME_TEXTURE_PARAM.fPos.x + (i * SLIME_SPACE_Y),
			SLIME_TEXTURE_PARAM.fPos.y,
			SLIME_TEXTURE_PARAM.fSize.x,
			SLIME_TEXTURE_PARAM.fSize.y,
			m_pTexture[E_TEXTURE::SLIME_BLUE + i]);

		// �X���C���΁`�Ԃ̉��ɐ̔{����\������
		if (1 <= i && i <= 3)
		{
			// ()
			Draw2d(
				PARENTHESIS_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				PARENTHESIS_PARAM.fPos.y,
				PARENTHESIS_PARAM.fSize.x,
				PARENTHESIS_PARAM.fSize.y,
				m_pTexture[E_TEXTURE::PARENTHESIS]);

			// �X���C���摜
			Draw2d(
				MULTI_SLIME_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				MULTI_SLIME_PARAM.fPos.y,
				MULTI_SLIME_PARAM.fSize.x,
				MULTI_SLIME_PARAM.fSize.y,
				m_pTexture[E_TEXTURE::SLIME_BLUE]);

			// �~
			Draw2d(
				MULTI_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				MULTI_PARAM.fPos.y,
				MULTI_PARAM.fSize.x,
				MULTI_PARAM.fSize.y,
				m_pTexture[E_TEXTURE::MULTI]);

		}
		// �{��
		DispNum(2, 1, { MULTI_NUM_PARAM.fPos.x + (1 * SLIME_SPACE_Y), MULTI_NUM_PARAM.fPos.y }, MULTI_NUM_PARAM.fSize, DEF_NUM_SPACE);
		DispNum(4, 1, { MULTI_NUM_PARAM.fPos.x + (2 * SLIME_SPACE_Y), MULTI_NUM_PARAM.fPos.y }, MULTI_NUM_PARAM.fSize, DEF_NUM_SPACE);
		DispNum(8, 1, { MULTI_NUM_PARAM.fPos.x + (3 * SLIME_SPACE_Y), MULTI_NUM_PARAM.fPos.y }, MULTI_NUM_PARAM.fSize, DEF_NUM_SPACE);

		// �X���C���ʓ�����
		//�Q���ȏ�̏ꍇ
		if (m_Data.nKill[i] >= 10)
		{
			DispNum(m_Data.nKill[i], 1, {
			SLIME_HUNT_NUM_PARAM.fPos.x + (i*SLIME_SPACE_Y) + (SLIME_HUNT_NUM_PARAM.fSize.x / 3),
			SLIME_HUNT_NUM_PARAM.fPos.y },
			SLIME_HUNT_NUM_PARAM.fSize, HUNT_NUM_SPACE);
		}
		//�P���̏ꍇ
		else
		{
			DispNum(m_Data.nKill[i], 1, {
				SLIME_HUNT_NUM_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				SLIME_HUNT_NUM_PARAM.fPos.y },
				SLIME_HUNT_NUM_PARAM.fSize, HUNT_NUM_SPACE);
		}

	}

	// ��������(����)
	Draw2d(
		TOTAL_HUNT_TEXT_PARAM.fPos.x,
		TOTAL_HUNT_TEXT_PARAM.fPos.y,
		TOTAL_HUNT_TEXT_PARAM.fSize.x,
		TOTAL_HUNT_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::TOTAL_HUNT_TEXT]);

	// ��������(����)
	DispNum(m_Data.nTotalKill, 1, TOTAL_HUNT_NUM_PARAM.fPos, TOTAL_HUNT_NUM_PARAM.fSize, DEF_NUM_SPACE);

	// ��
	Draw2d(
		HUNT_LINE_PARAM.fPos.x,
		HUNT_LINE_PARAM.fPos.y,
		HUNT_LINE_PARAM.fSize.x,
		HUNT_LINE_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::LINE]);
}


/* ========================================
	�ő�R���{���`��֐�
	----------------------------------------
	���e�F�ő�R���{����`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DrawMaxCombo()
{
	// �ő�R���{��(����)
	Draw2d(
		MAX_COMBO_TEXT_PARAM.fPos.x,
		MAX_COMBO_TEXT_PARAM.fPos.y,
		MAX_COMBO_TEXT_PARAM.fSize.x,
		MAX_COMBO_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::MAX_COMBO_TEXT]);

	// �ő�R���{��(����)
	DispNum(m_Data.nMaxCombo, 1, MAX_COMBO_NUM_PARAM.fPos, MAX_COMBO_NUM_PARAM.fSize, DEF_NUM_SPACE);
}


/* ========================================
	�������ԕ`��֐�
	----------------------------------------
	���e�F�������Ԃ�`�悷��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DispTime()
{
	// �b��
	DispNum(m_Data.GetSecond(), 2, SVL_TIME_NUM__PARAM.fPos, SVL_TIME_NUM__PARAM.fSize, DEF_NUM_SPACE);

	// �R����
	Draw2d(
		SVL_TIME_NUM__PARAM.fPos.x - (SVL_TIME_NUM_SPACE * 2) -7.0f,	// -7.0f�̓R�����̈ʒu�̔�����
		SVL_TIME_NUM__PARAM.fPos.y,
		SVL_TIME_NUM__PARAM.fSize.x,
		SVL_TIME_NUM__PARAM.fSize.y,
		m_pTexture[E_TEXTURE::COLON]);

	TDiType<float> pos = { 
		SVL_TIME_NUM__PARAM.fPos.x - (SVL_TIME_NUM_SPACE * 3) ,
		SVL_TIME_NUM__PARAM.fPos.y };

	// ����
	DispNum(m_Data.GetMinute(), 2, pos, SVL_TIME_NUM__PARAM.fSize, DEF_NUM_SPACE);
}

/* ========================================
	�����`��֐�
	----------------------------------------
	���e�F������`�悷��
	----------------------------------------
	����1�F�`�悷�鐔��
	����2�F����
	����3�F�ʒu
	����4�F�傫��
	����5�F�����Ԃ̑傫��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CResult::DispNum(int dispNum, int nDigits, TDiType<float> pos, TDiType<float> size, float NumSpace)
{

	std::vector<int> digitArray;
	DirectX::XMFLOAT4X4 mat;
	int Num = dispNum;


	NumStorage(&digitArray, dispNum, nDigits);


	

	for (int i = 0; i < digitArray.size(); i++)
	{

		int width = int(NumSpace * i);
		//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x - width, pos.y, 0.0f);
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(world));

		//�X�v���C�g�̐ݒ�
		Sprite::SetWorld(mat);

		int x = digitArray[i] % NUM_SPLIT.x;	//�������O��W���܂�
		int y = digitArray[i] / NUM_SPLIT.x;	//�z��ɓ����Ă鐔���̏ꏊ���v�Z���Ă܂�

		Sprite::SetSize(DirectX::XMFLOAT2(size.x, -size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(NUM_UVSCALE.x * x, NUM_UVSCALE.y * y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(NUM_UVSCALE.x, NUM_UVSCALE.y));
		Sprite::SetTexture(m_pTexture[E_TEXTURE::NUM]);
		Sprite::Draw();
	}
}


/* ========================================
	�������i�[����
	----------------------------------------
	���e�F�z��ɐ����������ƂɊi�[����
	----------------------------------------
	����1�F���i�[�z��
	����1�F�i�[���鐔��
	����1�F����
	----------------------------------------
	�ߒl�F����
=========================================== */
void CResult::NumStorage(std::vector<int>* digitArray, int nNumber, int nDigits)
{
	// �������z������Z�b�g
	(*digitArray).clear();

	// �\�����鐔����0�ȏ�̏ꍇ
	if (0 < nNumber)
	{
		// nNumber��S�Ċi�[����܂ŌJ��Ԃ�
		while (0 != nNumber) 
		{
			(*digitArray).push_back(nNumber % 10);	// nNumber�̉�1�����i�[����
			nNumber /= 10;							// nNumber��1���X���C�h������
			
		}

	}

	// �w�茅���܂�0���߂���
	while ((*digitArray).size() < nDigits)
	{
		(*digitArray).push_back(0);
	}
}



/* ========================================
	��ރQ�b�^
	----------------------------------------
	���e�F���g�����U���g�V�[���ł��邱�Ƃ�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F���g�̎��
=========================================== */
CResult::E_TYPE CResult::GetType() const
{
	// =============== �� ===================
	return CResult::E_TYPE_RESULT;	//���g�̎��
}

/* ========================================
	���V�[���Q�b�^
	----------------------------------------
	���e�F�J�ڂ������V�[��������������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�J�ڐ�V�[���̎��
=========================================== */
CResult::E_TYPE CResult::GetNext() const
{
	// =============== �� ===================
	return CResult::E_TYPE_SELECT_STAGE;	//�J�ڐ�V�[���̎��
}

/* ========================================
	���U���g�pSE�ǂݍ��݊֐�
   ----------------------------------------
   ���e�F���U���g�p��SE�̃t�@�C����ǂݍ���
   ----------------------------------------
   �����F����
   ----------------------------------------
   �ߒl�F����
======================================== */
void CResult::LoadSound()
{
	//SE�̓ǂݍ���
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
	}
}

/* ========================================
	SE�̍Đ��֐�
	----------------------------------------
	���e�FSE�̍Đ�
	----------------------------------------
	����1�FSE�̎��(enum)
	����2�F����
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CResult::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE�Đ�
	m_pSESpeaker[se]->SetVolume(volume);				//���ʂ̐ݒ�
}