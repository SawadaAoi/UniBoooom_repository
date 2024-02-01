/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�Z���N�g��`
	---------------------------------------
	SelectStage.h

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi
	�E2023/12/12 �X�e�[�W�Z���N�g�p�̍\���́A�z��A�֐��ǉ� yamamoto
	�E2024/01/26 �g�k���� takagi
	�E2024/01/26 �I���A����SE�ǉ� suzumura
	�E2024/01/28 �������� takagi
	�E2024/01/29 �摜�C�� takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.h�C���N���[�h�K�[�h
#define __SELECT_STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"		//�e�̃w�b�_
#include "2dPolygon.h"
#include "FrameCnt.h"	//�������o�p
#include "Sound.h"		//�T�E���h�w�b�_
#include <string>		//�����񑀍�
#include "BattleData.h"	//�����o�̃w�b�_


// =============== �萔��` =======================
const int STAGE_NUM = 3;						// �X�e�[�W�̐�

// =============== �N���X��` =====================
class CSelectStage :public CScene	//�V�[��
{
private:
	// ===�񋓒�`===========
	enum E_2D_OBJECT
	{
		E_2D_OBJECT_BACK_GROUND,		// �w�i
		E_2D_OBJECT_STAGE_1_REMINE,		// �X�e�[�W1��z���c���
		E_2D_OBJECT_STAGE_1_LEAVE,		// �X�e�[�W1��z��������
		E_2D_OBJECT_STAGE_2_REMINE,		// �X�e�[�W2��z���c���
		E_2D_OBJECT_STAGE_2_LEAVE,		// �X�e�[�W2��z��������
		E_2D_OBJECT_STAGE_3_REMINE,		// �X�e�[�W3��z���c���
		E_2D_OBJECT_STAGE_3_LEAVE,		// �X�e�[�W3��z��������
		E_2D_OBJECT_BACK_SCENE_NAME,	//�V�[����
		E_2D_OBJECT_HISCORE_BG,			// �n�C�X�R�A�w�i
		E_2D_OBJECT_HISCORE_TEXT,		// �n�C�X�R�A�e�L�X�g
		E_2D_OBJECT_HISCORE_NUM,		// �n�C�X�R�A����
		E_2D_OBJECT_BUTTON_EXPLANATION,	// ����{�^���w��

		E_2D_OBJECT_MAX,				// �v�f��
	};	//2d�ň����I�u�W�F�N�g

	// ===�萔��`===========
	const float MIN_SIZE_ARR_LET		= 350.0f;			// ��z���ŏ��T�C�Y
	const float MAX_SIZE_ARR_LET		= 450.0f;			// ��z���ő�T�C�Y
	const float ASPECT_RATE_ARR_LET		= 400.0f / 500.0f;	// ��z���c�ɑ΂��鉡�̔䗦
	const TTriType<float> INIT_SIZE_ARR_LET = { MIN_SIZE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f };	//��z�������T�C�Y
	const float MARGIN_FALL				= 0.0f;			// �����؂����Ɣ��f����Ƃ��ɕ␳����]�T
	const int	FALL_TIME_ARR_LET		= 60;			// ��z����������̂ɂ����鎞��

	const TDiType<float> STAGE_TEXTURE_OFFSET = { 0.0f, -0.5f };				// �X�e�[�W��z���摜�̒��S���W�ړ��l
	const float POS_OFFSET_ADJUST_Y = MIN_SIZE_ARR_LET * STAGE_TEXTURE_OFFSET.y;	// �X�e�[�W��z���摜�̃I�t�Z�b�g�ɂ��Y���𒼂� 

	const std::map<E_2D_OBJECT, std::string> MAP_TEXTURE_FILE= {
	{ E_2D_OBJECT_STAGE_1_REMINE, "Assets/Texture/StageSelect/zako1-3.png" },		// �X�e�[�W1��z���c���
	{ E_2D_OBJECT_STAGE_1_LEAVE,	"Assets/Texture/StageSelect/zako1-2.png" },		// �X�e�[�W1��z��������
	{ E_2D_OBJECT_STAGE_2_REMINE, "Assets/Texture/StageSelect/stone1-3.png" },		// �X�e�[�W2��z���c���
	{ E_2D_OBJECT_STAGE_2_LEAVE,	"Assets/Texture/StageSelect/stone1-2.png" },	// �X�e�[�W2��z��������
	{ E_2D_OBJECT_STAGE_3_REMINE, "Assets/Texture/StageSelect/boss1-3.png" },		// �X�e�[�W3��z���c���
	{ E_2D_OBJECT_STAGE_3_LEAVE, "Assets/Texture/StageSelect/boss1-2.png" },		// �X�e�[�W3��z��������
	{ E_2D_OBJECT_BACK_GROUND, "Assets/Texture/StageSelect/StageSelectBG.png"},		// �w�i
	{ E_2D_OBJECT_BACK_SCENE_NAME, "Assets/Texture/StageSelect/stselectUI.png"},		// �w�i
	{ E_2D_OBJECT_HISCORE_BG,	 "Assets/Texture/StageSelect/HiscoreBG.png"},		// �n�C�X�R�A�w�i
	{ E_2D_OBJECT_HISCORE_TEXT, "Assets/Texture/StageSelect/HiscoreText.png"},		// �n�C�X�R�A�e�L�X�g
	{ E_2D_OBJECT_HISCORE_NUM, "Assets/Texture/StageSelect/HiscoreNum.png"},		// �n�C�X�R�A����
	{ E_2D_OBJECT_BUTTON_EXPLANATION, "Assets/Texture/StageSelect/Select_Button.png"},		// ����{�^���w��

	};	//�e�N�X�`���̃t�@�C����


	const std::map<E_2D_OBJECT, TPos3d<float>> INIT_MAP_POS = {
	{ E_2D_OBJECT_STAGE_1_REMINE,	{ 250.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// �X�e�[�W1��z���c���
	{ E_2D_OBJECT_STAGE_1_LEAVE,	{ 250.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// �X�e�[�W1��z��������
	{ E_2D_OBJECT_STAGE_2_REMINE,	{ 600.0f, 300.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// �X�e�[�W2��z���c���
	{ E_2D_OBJECT_STAGE_2_LEAVE,	{ 600.0f, 300.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// �X�e�[�W2��z��������
	{ E_2D_OBJECT_STAGE_3_REMINE,	{ 950.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// �X�e�[�W3��z���c���
	{ E_2D_OBJECT_STAGE_3_LEAVE,	{ 950.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// �X�e�[�W3��z��������
	{ E_2D_OBJECT_BACK_GROUND,		{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f ,1.0f }},	// �w�i
	{ E_2D_OBJECT_BACK_SCENE_NAME,	{ 640.0f, 660.0f, 1.0f }},								// �V�[����
	{ E_2D_OBJECT_HISCORE_BG,		{ 0.0f	, 0.0f	, 1.0f }},								// �n�C�X�R�A�w�i
	{ E_2D_OBJECT_HISCORE_TEXT,		{ -45.0f, 20.0f	, 1.0f }},								// �n�C�X�R�A�e�L�X�g
	{ E_2D_OBJECT_HISCORE_NUM,		{ 110.0f, -20.0f, 1.0f }},								// �n�C�X�R�A����
	{ E_2D_OBJECT_BUTTON_EXPLANATION,	{ 1150.0f	, 50.0f	, 1.0f }},						// ����{�^���w��
	};	//�I�u�W�F�N�g���̏����ʒu


	const std::map<E_2D_OBJECT, TTriType<float>> INIT_MAP_ROTATE = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { 0.0f,0.0f,-0.25f } },	//�X�e�[�W1��z���c���
	{ E_2D_OBJECT_STAGE_1_LEAVE, { 0.0f,0.0f,-0.25f } },	//�X�e�[�W1��z��������
	{ E_2D_OBJECT_STAGE_2_REMINE, { 0.0f,0.0f,0.05f } },	//�X�e�[�W2��z���c���
	{ E_2D_OBJECT_STAGE_2_LEAVE, { 0.0f,0.0f,0.05f } },		//�X�e�[�W2��z��������
	{ E_2D_OBJECT_STAGE_3_REMINE, { 0.0f,0.0f,0.1f } },		//�X�e�[�W3��z���c���
	{ E_2D_OBJECT_STAGE_3_LEAVE, { 0.0f,0.0f,0.1f } },		//�X�e�[�W3��z��������
	{ E_2D_OBJECT_BACK_GROUND, {0.0f, 0.0f, 0.0f}},			//�w�i
	{ E_2D_OBJECT_BACK_SCENE_NAME, { 0.0f,0.0f,0.0f }},		//�V�[����
	{ E_2D_OBJECT_HISCORE_BG,	 { 0.0f, 0.0f  ,0.0f }},	// �n�C�X�R�A�w�i
	{ E_2D_OBJECT_HISCORE_TEXT,	 { 0.0f, 0.0f  ,0.0f }},	// �n�C�X�R�A�e�L�X�g
	{ E_2D_OBJECT_HISCORE_NUM, { 0.0f, 0.0f  ,0.0f }},		// �n�C�X�R�A����
	{ E_2D_OBJECT_BUTTON_EXPLANATION, { 0.0f, 0.0f  ,0.0f }},	// ����{�^���w��
	};	//�I�u�W�F�N�g���̏�����]


	const std::map<E_2D_OBJECT, TTriType<float>> INIT_MAP_SIZE = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W1��z���c���
	{ E_2D_OBJECT_STAGE_1_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W1��z��������
	{ E_2D_OBJECT_STAGE_2_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W2��z���c���
	{ E_2D_OBJECT_STAGE_2_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W2��z��������
	{ E_2D_OBJECT_STAGE_3_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W3��z���c���
	{ E_2D_OBJECT_STAGE_3_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W3��z��������
	{ E_2D_OBJECT_BACK_GROUND, { SCREEN_WIDTH, SCREEN_HEIGHT,1.0f }},									//�w�i
	{ E_2D_OBJECT_BACK_SCENE_NAME, { SCREEN_WIDTH, 130.0f ,1.0f }},										//�V�[����
	{ E_2D_OBJECT_HISCORE_BG, { 280.0f, 100.0f  ,1.0f }},								// �n�C�X�R�A�w�i
	{ E_2D_OBJECT_HISCORE_TEXT, { 150.0f, 60.0f  ,1.0f }},								// �n�C�X�R�A�e�L�X�g
	{ E_2D_OBJECT_HISCORE_NUM, { 50.0f, 55.0f  ,1.0f }},								// �n�C�X�R�A����
	{ E_2D_OBJECT_BUTTON_EXPLANATION, { 250.0f, 60.0f  ,1.0f }},						// ����{�^���w��
	};	//�I�u�W�F�N�g���̑傫��

public:
	// ===�񋓐錾===========
	enum SE
	{
		SE_DECISION,	//���艹
		SE_CHOOSE,		//���ڑI��SE

		SE_MAX			//SE�̑���
	}; //SE
public:
	// =============== �v���g�^�C�v�錾 ===============
	CSelectStage();						// �R���X�g���N�^
	~CSelectStage();					// �f�X�g���N�^
	void Update();						// �X�V
	void Draw();// const;				// �`��	
	void StageSelect();						   
	E_TYPE GetType() const override;	// ���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	// ���̃V�[���Q�b�^
	void LoadSound();								// �V�[���Z���N�g�p�̃T�E���h�����[�h
	void PlaySE(SE se, float volume = 1.0f);		// SE���Đ�����
private:
	void SelectStageChange(int select);
	void SelectStageTextureAnimation(CScene::E_TYPE stage);
	void FallAnimationStageTexture();
	void ResetStageTexture(CScene::E_TYPE stage);

	void DrawStageTexture();
	void DrawHiscore();
	void DispNum(int dispNum, int nDigits, TTriType<float> pos);
	void NumStorage(std::vector<int>* digitArray, int nNumber, int nDigits);

	std::map<E_2D_OBJECT, C2dPolygon*> m_p2dObject;	// 2d�ň����I�u�W�F�N�g
	float m_fChangeRotate;							// �I�����Ă���X�e�[�W��z���摜�̌X���ϓ��l
	bool m_bStickFlg;								// �X�e�B�b�N����x�j���[�g�����ɖ߂�����
	CFrameCnt* m_pFrameCntFall;						// �����C�[�W���O�p�^�C�}�[
	CFrameCnt* m_pFrameCntRotate;					// �g�k�C�[�W���O�p�^�C�}�[
	bool m_bCntUpDwn;								// �J�E���g�A�b�v�E�_�E���؊��t���O
	E_TYPE m_eNextType;								// ���̃V�[���̎��
	BattleData m_Data;								// �퓬����
	int m_nButtonAlphaCnt;

	//=====SE�֘A=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Paper_break.mp3",			// ���艹
		"Assets/Sound/SE/Select_Cursor.mp3" 		// �I����
	};
};	//�X�e�[�W�Z���N�g

#endif	//!__SELECT_STAGE_H__