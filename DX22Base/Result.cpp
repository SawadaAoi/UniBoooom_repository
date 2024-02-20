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
	�E2024/02/09 GetType()�֐��폜 takagi

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
	{CResult::BG_SCREEN_CLEAR,		"Assets/Texture/Result/ResultBG.png"},			// ��ʑS�̂̔w�i
	{CResult::BG_SCREEN_GAMEOVER,	"Assets/Texture/Result/ResultBG_blue.png"},		// ��ʑS�̂̔w�i
	{CResult::BG_PANEL_CLEAR,		"Assets/Texture/Result/result_waku.png"},		// �e���ڂ̔w�i(�����w�i)
	{CResult::BG_PANEL_GAMEOVER,	"Assets/Texture/Result/result_waku_blue.png"},	// �e���ڂ̔w�i(�����w�i)
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

const std::map<CResult::E_2D_OBJ_ID, TTriType<float>> MAP_TEX_POS = {
	{CResult::OBJ_BG_SCREEN,			{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , 1.0f} },	// �w�i
	{CResult::OBJ_BG_PANEL,				{ 905.0f, SCREEN_HEIGHT / 2, 1.0f } },				// ���ڔw�i
	{CResult::OBJ_WARNING_STAGE,		{ 260.0f, 340.0f, 1.0f } },							// ��z���摜
	{CResult::OBJ_CLEAR_STAMP,			{ 260.0f, 340.0f, 1.0f } },							// �X�^���v�摜
	{CResult::OBJ_RESULT_TEXT,			{ 275.0f, 660.0f, 1.0f } },							// ���U���g(����)
	{CResult::OBJ_SVL_TIME_TEXT,		{ 650.0f, 690.0f, 1.0f } },							// ��������(����)
	{CResult::OBJ_SVL_TIME_SECOND_NUM,	{ 1200.0f,670.0f, 1.0f } },							// ��������(�b)
	{CResult::OBJ_SVL_TIME_COLON,		{ 1083.0f,670.0f, 1.0f } },							// ��������(�R����)	
	{CResult::OBJ_SVL_TIME_MINUTE_NUM,	{ 1035.0f,670.0f, 1.0f } },							// ��������(��)		
	{CResult::OBJ_SVL_TIME_LINE,		{ 907.0f, 620.0f, 1.0f } },							// ��؂��
	{CResult::OBJ_SCORE_TEXT,			{ 655.0f, 590.0f, 1.0f } },							// �X�R�A(����)
	{CResult::OBJ_NEW_RECORD_TEXT,		{ 800.0f, 540.0f, 1.0f } },							// �V�L�^(����)
	{CResult::OBJ_SCORE_NUM,			{ 1200.0f,560.0f, 1.0f } },							// �X�R�A(����)
	{CResult::OBJ_HIGH_SCORE_TEXT,		{ 645.0f, 480.0f, 1.0f } },							// �n�C�X�R�A(����)
	{CResult::OBJ_HIGH_SCORE_NUM,		{ 1200.0f,460.0f, 1.0f } },							// �n�C�X�R�A(����)
	{CResult::OBJ_SCORE_LINE,			{ 907.0f, 420.0f, 1.0f } },							// ��؂��
	{CResult::OBJ_HUNT_TEXT,			{ 710.0f, 380.0f, 1.0f } },							// ������(����)
	{CResult::OBJ_SLIME_HUNT_BG,		{ 650.0f, 290.0f, 1.0f } },							// �������w�i�X���C���摜
	{CResult::OBJ_SLIME_HUNT_NUM,		{ 650.0f, 290.0f, 1.0f } },							// �X���C���ʓ�����
	{CResult::OBJ_PARENTHESIS,			{ 600.0f, 210.0f, 1.0f } },							// ()
	{CResult::OBJ_MULTI,				{ 650.0f, 210.0f, 1.0f } },							// �~
	{CResult::OBJ_MULTI_BLUE_SLIME,		{ 615.0f, 210.0f, 1.0f } },							// �X���C���摜�̈ʒu
	{CResult::OBJ_MULTI_NUM,			{ 685.0f, 210.0f, 1.0f } },							// �X���C���̔{��
	{CResult::OBJ_TOTAL_HUNT_TEXT,		{ 670.0f, 160.0f, 1.0f } },							// ��������(����)
	{CResult::OBJ_TOTAL_HUNT_NUM,		{ 1200.0f,140.0f, 1.0f } },							// ��������(����)
	{CResult::OBJ_HUNT_LINE,			{ 907.0f, 100.0f, 1.0f } },							// ��؂��
	{CResult::OBJ_MAX_COMBO_TEXT,		{ 695.0f,  65.0f, 1.0f } },							// �ő�R���{��(����)
	{CResult::OBJ_MAX_COMBO_NUM,		{ 1200.0f, 50.0f, 1.0f } },							// �ő�R���{��(����)
	{CResult::OBJ_SELECT_BUTTON,		{ 65.0f,   40.0f, 1.0f } },							// ���� 
};

const std::map<CResult::E_2D_OBJ_ID, TTriType<float>> MAP_TEX_SIZE = {
	{CResult::OBJ_BG_SCREEN,			{ SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f} },	// �w�i
	{CResult::OBJ_BG_PANEL,				{ 750.0f, SCREEN_HEIGHT, 1.0f } },		// ���ڔw�i
	{CResult::OBJ_WARNING_STAGE,		{ 460.0f, 580.0f, 1.0f } },				// ��z���摜
	{CResult::OBJ_CLEAR_STAMP,			{ 460.0f, 580.0f, 1.0f } },				// �X�^���v�摜
	{CResult::OBJ_RESULT_TEXT,			{ 640.0f, 280.0f, 1.0f } },				// ���U���g(����)
	{CResult::OBJ_SVL_TIME_TEXT,		{ 200.0f, 80.0f,  1.0f } },				// ��������(����)
	{CResult::OBJ_SVL_TIME_SECOND_NUM,	{ 85.0f,  95.0f , 1.0f } },				// ��������(�b��)
	{CResult::OBJ_SVL_TIME_COLON,		{ 85.0f,  95.0f,  1.0f } },				// ��������(�R����)	
	{CResult::OBJ_SVL_TIME_MINUTE_NUM,	{ 85.0f,  95.0f,  1.0f } },				// ��������(��)		
	{CResult::OBJ_SVL_TIME_LINE,		{ 729.0f, 5.0f ,  1.0f } },				// ��؂��
	{CResult::OBJ_SCORE_TEXT,			{ 220.0f, 75.0f,  1.0f } },				// �X�R�A(����)
	{CResult::OBJ_NEW_RECORD_TEXT,		{ 170.0f, 55.0f,  1.0f } },				// �V�L�^(����)
	{CResult::OBJ_SCORE_NUM,			{ 85.0f, 105.0f,  1.0f } },				// �X�R�A(����)
	{CResult::OBJ_HIGH_SCORE_TEXT,		{ 180.0f, 75.0f,  1.0f } },				// �n�C�X�R�A(����)
	{CResult::OBJ_HIGH_SCORE_NUM,		{ 55.0f, 55.0f,   1.0f } },				// �n�C�X�R�A(����)
	{CResult::OBJ_SCORE_LINE,			{ 729.0f, 5.0f,   1.0f } },				// ��؂��
	{CResult::OBJ_HUNT_TEXT,			{ 330.0f, 110.0f, 1.0f } },				// ������(����)
	{CResult::OBJ_SLIME_HUNT_BG,		{ 160.0f, 160.0f, 1.0f } },				// �������w�i�X���C���摜
	{CResult::OBJ_SLIME_HUNT_NUM,		{ 60.0f, 60.0f,   1.0f } },				// �X���C���ʓ�����
	{CResult::OBJ_PARENTHESIS,			{ 40.0f, 40.0f,   1.0f } },				// ()
	{CResult::OBJ_MULTI,				{ 40.0f, 40.0f,   1.0f } },				// �~
	{CResult::OBJ_MULTI_BLUE_SLIME,		{ 30.0f, 30.0f,   1.0f } },				// �X���C���摜�̈ʒu
	{CResult::OBJ_MULTI_NUM,			{ 40.0f, 40.0f,   1.0f } },				// �X���C���̔{��
	{CResult::OBJ_TOTAL_HUNT_TEXT,		{ 250.0f, 80.0f,  1.0f } },				// ��������(����)
	{CResult::OBJ_TOTAL_HUNT_NUM,		{ 85.0f, 105.0f,  1.0f } },				// ��������(����)
	{CResult::OBJ_HUNT_LINE,			{ 729.0f, 5.0f,   1.0f } },				// ��؂��
	{CResult::OBJ_MAX_COMBO_TEXT,		{ 300.0f, 90.0f,  1.0f } },				// �ő�R���{��(����)
	{CResult::OBJ_MAX_COMBO_NUM,		{ 85.0f, 105.0f,  1.0f } },				// �ő�R���{��(����)
	{CResult::OBJ_SELECT_BUTTON,		{ 130.0f, 65.0f,  1.0f } },				// ���� 
};

const int	RESULT_TEXT_FLASH = 0.04 * 60;

const TDiType<int>		NUM_SPLIT = { 5, 2 };			// �����摜�����l
const TDiType<float>	NUM_UVSCALE = {					// �����摜UV�l
						(1.0f / NUM_SPLIT.x) ,(1.0f / NUM_SPLIT.y) };

const TDiType<float>		PARENTHESIS_SPLIT = { 2, 1 };	// �J�b�R�摜�����l
const TDiType<float>	PARENTHESIS_UVSCALE = {			// �J�b�R�摜UV�l
						(1.0f / PARENTHESIS_SPLIT.x) ,(1.0f / PARENTHESIS_SPLIT.y) };

const float DEF_NUM_SPACE			= 68.0f;			// �����Ԃ̋���(�f�t�H���g)
const float SVL_TIME_NUM_SPACE		= 55.0f;			// ���Ԃ̊�(�� 12��:��33)
const float SCORE_NUM_SPACE			= 70.0f;			// �����Ԃ̋���(�X�R�A)
const float HIGH_SCORE_NUM_SPACE	= 45.0f;			// �����Ԃ̋���(�n�C�X�R�A)
const float HUNT_NUM_SPACE			= 45.0f;			// �����Ԃ̋���(������)

const float SLIME_SPACE_Y = 130.0f;						// �X���C���摜�̊�
const float FLASH_BUTTON_TEXT_ADJUST		= 0.02f;	//�u����v�e�L�X�g�̓_�ŊԊu����
const float FLASH_NEW_RECORD_TEXT_ADJUST	= 0.04f;	//�u�n�C�X�R�A�v�e�L�X�g�̓_�ŊԊu����

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
	, m_nNewRecoAlphaCnt(0)
	, m_nStAnimCnt(0)
	, m_nStartAnimEnd(false)

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

	for (int i = 0; i < E_2D_OBJ_ID::OBJ_2D_MAX; i++)
	{
		m_p2dObj[i] = new C2dPolygon();
		m_p2dObj[i]->SetPos(MAP_TEX_POS.at(static_cast<E_2D_OBJ_ID>(i)));
		m_p2dObj[i]->SetSize(MAP_TEX_SIZE.at(static_cast<E_2D_OBJ_ID>(i)));
	}
	
	// ���U���g�����̃A�j���[�V�����̏�����
	m_pTextureResultText = new CDrawAnim(60, TDiType<int>(5, 12), RESULT_TEXT_FLASH);
	m_pTextureResultText->SetTexture(m_pTexture[E_TEXTURE::RESULT_TEXT]);
	m_pTextureResultText->SetPos(MAP_TEX_POS.at(E_2D_OBJ_ID::OBJ_RESULT_TEXT));
	m_pTextureResultText->SetSize(MAP_TEX_SIZE.at(E_2D_OBJ_ID::OBJ_RESULT_TEXT));
	m_pTextureResultText->SetLoopFlg(true);
	
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

	// ����{�^���_�ŉ��Z�l
	m_nButtonAlphaCnt++;
	m_nNewRecoAlphaCnt++;
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
	// �Q�[���N���A
	if (m_Data.bClearFlg)
	{
		// �S�̂̔w�i
		m_p2dObj[OBJ_BG_SCREEN]->SetTexture(m_pTexture[E_TEXTURE::BG_SCREEN_CLEAR]);
		// �E�����̊e���ڂ̔w�i
		m_p2dObj[OBJ_BG_PANEL]->SetTexture(m_pTexture[E_TEXTURE::BG_PANEL_CLEAR]);
	}
	// �Q�[���I�[�o�[
	else
	{
		// �S�̂̔w�i
		m_p2dObj[OBJ_BG_SCREEN]->SetTexture(m_pTexture[E_TEXTURE::BG_SCREEN_GAMEOVER]);
		// �E�����̊e���ڂ̔w�i
		m_p2dObj[OBJ_BG_PANEL]->SetTexture(m_pTexture[E_TEXTURE::BG_PANEL_GAMEOVER]);
	}

	// �`��
	m_p2dObj[OBJ_BG_SCREEN]->Draw();
	m_p2dObj[OBJ_BG_PANEL]->Draw();

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
	

	m_p2dObj[OBJ_WARNING_STAGE]->SetTexture(pWarningTex);
	m_p2dObj[OBJ_WARNING_STAGE]->Draw();

	// �N���A�����ꍇ
	if (m_Data.bClearFlg)
	{
		// �X�^���v��\������
		m_p2dObj[OBJ_CLEAR_STAMP]->SetTexture(m_pTexture[E_TEXTURE::CLEAR_STAMP]);
		m_p2dObj[OBJ_CLEAR_STAMP]->Draw();
	}

	// ����{�^��
	m_p2dObj[OBJ_SELECT_BUTTON]->SetTexture(m_pTexture[E_TEXTURE::SELECT]);

	m_p2dObj[OBJ_SELECT_BUTTON]->SetAlpha(fabs(cosf(m_nButtonAlphaCnt * FLASH_BUTTON_TEXT_ADJUST)));	// �_�łׁ̈A�����x�ύX
	m_p2dObj[OBJ_SELECT_BUTTON]->Draw();

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
	m_p2dObj[OBJ_SVL_TIME_TEXT]->SetTexture(m_pTexture[E_TEXTURE::SVL_TIME_TEXT]);
	m_p2dObj[OBJ_SVL_TIME_TEXT]->Draw();

	// ��������(����)
	DispTime();

	// ��
	m_p2dObj[OBJ_SVL_TIME_LINE]->SetTexture(m_pTexture[E_TEXTURE::LINE]);
	m_p2dObj[OBJ_SVL_TIME_LINE]->Draw();
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
	m_p2dObj[OBJ_SCORE_TEXT]->SetTexture(m_pTexture[E_TEXTURE::SCORE_TEXT]);
	m_p2dObj[OBJ_SCORE_TEXT]->Draw();


	// ���X�R�A(����)
	DispNum(m_Data.nTotalScore, 5, OBJ_SCORE_NUM, MAP_TEX_POS.at(OBJ_SCORE_NUM), SCORE_NUM_SPACE);

	// �n�C�X�R�A(����)
	m_p2dObj[OBJ_HIGH_SCORE_TEXT]->SetTexture(m_pTexture[E_TEXTURE::HIGH_SCORE_TEXT]);
	m_p2dObj[OBJ_HIGH_SCORE_TEXT]->Draw();

	// �n�C�X�R�A���X�V���Ă�����(�Q�[���I�����Ƀn�C�X�R�A���X�V�����)
	if (m_Data.nHighScore[m_Data.nStageNum-1] == m_Data.nTotalScore)
	{
		// �j���[���R�[�h(����)
		m_p2dObj[OBJ_NEW_RECORD_TEXT]->SetTexture(m_pTexture[E_TEXTURE::NEW_RECORD_TEXT]);
		m_p2dObj[OBJ_NEW_RECORD_TEXT]->SetAlpha(fabs(cosf(m_nNewRecoAlphaCnt * FLASH_NEW_RECORD_TEXT_ADJUST)));	// �_�łׁ̈A�����x�ύX

		m_p2dObj[OBJ_NEW_RECORD_TEXT]->Draw();

	}

	// �n�C�X�R�A(����)
	DispNum(m_Data.nHighScore[m_Data.nStageNum - 1], 5, OBJ_HIGH_SCORE_NUM, MAP_TEX_POS.at(OBJ_HIGH_SCORE_NUM), HIGH_SCORE_NUM_SPACE);
	

	// ��
	m_p2dObj[OBJ_SCORE_LINE]->SetTexture(m_pTexture[E_TEXTURE::LINE]);
	m_p2dObj[OBJ_SCORE_LINE]->Draw();
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
	m_p2dObj[OBJ_HUNT_TEXT]->SetTexture(m_pTexture[E_TEXTURE::HUNT_TEXT]);
	m_p2dObj[OBJ_HUNT_TEXT]->Draw();

	// �X�e�[�W�P�Ȃ�{�X��������\�����Ȃ�
	int nDispHuntNum = 5;	// �{�΁{���{�ԁ{�{�X���T
	if (m_Data.nStageNum == 1) nDispHuntNum = 4;	// �[�{�X���S

	// �X���C���̎�ސ����摜��\��
	for (int i = 0; i < nDispHuntNum; i++)
	{
		// �X���C���̉摜
		m_p2dObj[OBJ_SLIME_HUNT_BG]->SetPos({
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_BG).x + (i * SLIME_SPACE_Y),
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_BG).y,
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_BG).z,
			});
		m_p2dObj[OBJ_SLIME_HUNT_BG]->SetTexture(m_pTexture[E_TEXTURE::SLIME_BLUE + i]);
		m_p2dObj[OBJ_SLIME_HUNT_BG]->Draw();

		
		// �X���C���΁`�Ԃ̉��ɐ̔{����\������(i = 1�`3)
		if (1 <= i && i <= 3)
		{
			// ()
			for (int j = 0; j < 2; j++)
			{
				m_p2dObj[OBJ_PARENTHESIS]->SetPos({
								MAP_TEX_POS.at(OBJ_PARENTHESIS).x + (i * SLIME_SPACE_Y) + (j * 100),
								MAP_TEX_POS.at(OBJ_PARENTHESIS).y,
								MAP_TEX_POS.at(OBJ_PARENTHESIS).z,
					});
				m_p2dObj[OBJ_PARENTHESIS]->SetUvOffset({ PARENTHESIS_UVSCALE.x * j, PARENTHESIS_UVSCALE.y });
				m_p2dObj[OBJ_PARENTHESIS]->SetUvScale(PARENTHESIS_UVSCALE);
				m_p2dObj[OBJ_PARENTHESIS]->SetTexture(m_pTexture[E_TEXTURE::PARENTHESIS]);
				m_p2dObj[OBJ_PARENTHESIS]->Draw();
			}
			

			// �X���C���摜
			m_p2dObj[OBJ_MULTI_BLUE_SLIME]->SetPos({
				MAP_TEX_POS.at(OBJ_MULTI_BLUE_SLIME).x + (i * SLIME_SPACE_Y),
				MAP_TEX_POS.at(OBJ_MULTI_BLUE_SLIME).y,
				MAP_TEX_POS.at(OBJ_MULTI_BLUE_SLIME).z,
				});
			m_p2dObj[OBJ_MULTI_BLUE_SLIME]->SetTexture(m_pTexture[E_TEXTURE::SLIME_BLUE]);
			m_p2dObj[OBJ_MULTI_BLUE_SLIME]->Draw();

			// �~
			m_p2dObj[OBJ_MULTI]->SetPos({
				MAP_TEX_POS.at(OBJ_MULTI).x + (i * SLIME_SPACE_Y),
				MAP_TEX_POS.at(OBJ_MULTI).y,
				MAP_TEX_POS.at(OBJ_MULTI).z,
				});
			m_p2dObj[OBJ_MULTI]->SetTexture(m_pTexture[E_TEXTURE::MULTI]);
			m_p2dObj[OBJ_MULTI]->Draw();

			// �{��
			DispNum(pow(2,i), 1, OBJ_MULTI_NUM, {
			MAP_TEX_POS.at(OBJ_MULTI_NUM).x + (i * SLIME_SPACE_Y),
			MAP_TEX_POS.at(OBJ_MULTI_NUM).y,
			MAP_TEX_POS.at(OBJ_MULTI_NUM).z },
			DEF_NUM_SPACE);
		}

		// �X���C���ʓ�����
		std::vector<int> digitArray;
		NumStorage(&digitArray, m_Data.nKill[i], 1);
		DispNum(m_Data.nKill[i], 1, OBJ_SLIME_HUNT_NUM, {
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_NUM).x + (i * SLIME_SPACE_Y) + (20.0f * (digitArray.size() - 1)),
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_NUM).y,
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_NUM).z },
			HUNT_NUM_SPACE);

	}

	// ��������(����)
	m_p2dObj[OBJ_TOTAL_HUNT_TEXT]->SetTexture(m_pTexture[E_TEXTURE::TOTAL_HUNT_TEXT]);
	m_p2dObj[OBJ_TOTAL_HUNT_TEXT]->Draw();

	// ��������(����)
	DispNum(m_Data.nTotalKill, 1, OBJ_TOTAL_HUNT_NUM, MAP_TEX_POS.at(OBJ_TOTAL_HUNT_NUM), DEF_NUM_SPACE);

	// ��
	m_p2dObj[OBJ_HUNT_LINE]->SetTexture(m_pTexture[E_TEXTURE::LINE]);
	m_p2dObj[OBJ_HUNT_LINE]->Draw();
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
	m_p2dObj[OBJ_MAX_COMBO_TEXT]->SetTexture(m_pTexture[E_TEXTURE::MAX_COMBO_TEXT]);
	m_p2dObj[OBJ_MAX_COMBO_TEXT]->Draw();

	// �ő�R���{��(����)
	DispNum(m_Data.nMaxCombo, 1, OBJ_MAX_COMBO_NUM, MAP_TEX_POS.at(OBJ_MAX_COMBO_NUM), DEF_NUM_SPACE);
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
	DispNum(m_Data.GetSecond(), 2, OBJ_SVL_TIME_SECOND_NUM, MAP_TEX_POS.at(OBJ_SVL_TIME_SECOND_NUM), DEF_NUM_SPACE);

	// �R����
	m_p2dObj[OBJ_SVL_TIME_COLON]->SetTexture(m_pTexture[E_TEXTURE::COLON]);
	m_p2dObj[OBJ_SVL_TIME_COLON]->Draw();

	// ����
	DispNum(m_Data.GetMinute(), 2, OBJ_SVL_TIME_MINUTE_NUM, MAP_TEX_POS.at(OBJ_SVL_TIME_MINUTE_NUM), DEF_NUM_SPACE);
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
void CResult::DispNum(int dispNum, int nDigits, E_2D_OBJ_ID objId, TTriType<float> fPos, float NumSpace)
{

	std::vector<int> digitArray;
	int Num = dispNum;

	NumStorage(&digitArray, dispNum, nDigits);

	for (int i = 0; i < digitArray.size(); i++)
	{

		int width = int(NumSpace * i);

		TTriType<float> pos ={ 
			fPos.x - width,
			fPos.y,
			fPos.z };

		int x = digitArray[i] % NUM_SPLIT.x;	
		int y = digitArray[i] / NUM_SPLIT.x;	

		m_p2dObj[objId]->SetPos(pos);
		m_p2dObj[objId]->SetUvOffset({ NUM_UVSCALE.x * x, NUM_UVSCALE.y * y });
		m_p2dObj[objId]->SetUvScale({ NUM_UVSCALE.x, NUM_UVSCALE.y });

		m_p2dObj[objId]->SetTexture(m_pTexture[E_TEXTURE::NUM]);
		m_p2dObj[objId]->Draw();
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