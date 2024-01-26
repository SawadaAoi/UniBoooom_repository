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

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.h�C���N���[�h�K�[�h
#define __SELECT_STAGE_H__

// =============== �C���N���[�h ===================
#include "Scene.h"	//�e�̃w�b�_
#include "2dPolygon.h"
#include "FrameCnt.h"	//�������o�p
#include <string>		//�����񑀍�
// =============== �萔��` =======================
const int SUTAGE_NUM = 3;						// �X�e�[�W�̐�

// =============== �N���X��` =====================
class CSelectStage :public CScene	//�V�[��
{
private:
	// ===�񋓒�`===========
	enum E_2D_OBJECT
	{
		E_2D_OBJECT_BACK_GROUND,		//�w�i
		E_2D_OBJECT_STAGE_1_REMINE,		//�X�e�[�W1��z���c���
		E_2D_OBJECT_STAGE_1_LEAVE,		//�X�e�[�W1��z��������
		E_2D_OBJECT_STAGE_2_REMINE,		//�X�e�[�W2��z���c���
		E_2D_OBJECT_STAGE_2_LEAVE,		//�X�e�[�W2��z��������
		E_2D_OBJECT_STAGE_3_REMINE,		//�X�e�[�W3��z���c���
		E_2D_OBJECT_STAGE_3_LEAVE,		//�X�e�[�W3��z��������
		E_2D_OBJECT_BACK_SCENE_NAME,	//�V�[����
		E_2D_OBJECT_MAX,				//�v�f��
	};	//2d�ň����I�u�W�F�N�g
	// ===�萔��`===========
	const float MIN_SIZE_ARR_LET = 450.0f;				//��z���ŏ��T�C�Y
	const float MAX_SIZE_ARR_LET = 550.0f;				//��z���ő�T�C�Y
	const float ASPECT_RATE_ARR_LET = 400.0f / 500.0f;	//��z���c�ɑ΂��鉡�̔䗦
	const TTriType<float> INIT_SIZE_ARR_LET = { MIN_SIZE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f };	//��z�������T�C�Y
	const int CHANGE_SCALE_HALF_TIME = 120;	//�g�k����������ɂ����鎞��
	const std::map<E_2D_OBJECT, std::string> MAP_TEXTURE_FILE= {
	{ E_2D_OBJECT_STAGE_1_REMINE, "Assets/Texture/StageSelect/zako1-1.png" },	//�X�e�[�W1��z���c���
	{ E_2D_OBJECT_STAGE_1_LEAVE,	"Assets/Texture/StageSelect/zako1-2.png" },	//�X�e�[�W1��z��������
	{ E_2D_OBJECT_STAGE_2_REMINE, "Assets/Texture/StageSelect/boss1-1.png" },	//�X�e�[�W2��z���c���
	{ E_2D_OBJECT_STAGE_2_LEAVE,	"Assets/Texture/StageSelect/boss1-2.png" },	//�X�e�[�W2��z��������
	{ E_2D_OBJECT_STAGE_3_REMINE, "Assets/Texture/StageSelect/stone1-1.png" },	//�X�e�[�W3��z���c���
	{ E_2D_OBJECT_STAGE_3_LEAVE, "Assets/Texture/StageSelect/stone1-2.png" },	//�X�e�[�W3��z��������
	{ E_2D_OBJECT_BACK_GROUND, "Assets/Texture/StageSelect/StageSelectBG.png"},	//�w�i
	{ E_2D_OBJECT_BACK_SCENE_NAME, "Assets/Texture/StageSelect/stselectUI.png"},//�V�[����
	};	//�e�N�X�`���̃t�@�C����
	const std::map<E_2D_OBJECT, TPos3d<float>> INIT_MAP_POS = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { 250.0f, 300.0f,1.0f } },							//�X�e�[�W1��z���c���
	{ E_2D_OBJECT_STAGE_1_LEAVE, { 250.0f, 300.0f,1.0f } },								//�X�e�[�W1��z��������
	{ E_2D_OBJECT_STAGE_2_REMINE, { 600.0f, 300.0f,1.0f } },							//�X�e�[�W2��z���c���
	{ E_2D_OBJECT_STAGE_2_LEAVE, { 600.0f, 300.0f,1.0f } },								//�X�e�[�W2��z��������
	{ E_2D_OBJECT_STAGE_3_REMINE, { 950.0f, 300.0f,1.0f } },							//�X�e�[�W3��z���c���
	{ E_2D_OBJECT_STAGE_3_LEAVE, { 950.0f, 300.0f,1.0f } },								//�X�e�[�W3��z��������
	{ E_2D_OBJECT_BACK_GROUND, { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f ,1.0f }},	//�w�i
	{ E_2D_OBJECT_BACK_SCENE_NAME, { 640.0f, 660.0f  ,1.0f }},							//�V�[����
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
	};	//�I�u�W�F�N�g���̏�����]
	const std::map<E_2D_OBJECT, TTriType<float>> INIT_MAP_SIZE = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W1��z���c���
	{ E_2D_OBJECT_STAGE_1_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W1��z��������
	{ E_2D_OBJECT_STAGE_2_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W2��z���c���
	{ E_2D_OBJECT_STAGE_2_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W2��z��������
	{ E_2D_OBJECT_STAGE_3_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W3��z���c���
	{ E_2D_OBJECT_STAGE_3_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//�X�e�[�W3��z��������
	{ E_2D_OBJECT_BACK_GROUND, { SCREEN_WIDTH, SCREEN_HEIGHT,1.0f }},									//�w�i
	{ E_2D_OBJECT_BACK_SCENE_NAME, { SCREEN_WIDTH, 120.0f ,1.0f }},										//�V�[����
	};	//�I�u�W�F�N�g���̏����g�k
public:
	// =============== �v���g�^�C�v�錾 ===============
	CSelectStage();						//�R���X�g���N�^
	~CSelectStage();					//�f�X�g���N�^
	void Update();						//�X�V
	void Draw();// const;				//�`��	
	void Select();
	E_TYPE GetType() const override;	//���g�̎�ރQ�b�^
	E_TYPE GetNext() const override;	//���̃V�[���Q�b�^
private:
	std::map<E_2D_OBJECT, C2dPolygon*> m_p2dObject;	//2d�ň����I�u�W�F�N�g
	bool m_bStickFlg;			// �R���g���[���[�̃X�e�B�b�N���������Ă��邩
	CFrameCnt* m_pFrameCnt;		//�C�[�W���O�p�^�C�}�[
	bool m_bCntUpDwn;			//�J�E���g�A�b�v�E�_�E��
	E_TYPE m_eNextType;			//���̃V�[���̎��
};	//�X�e�[�W�Z���N�g

#endif	//!__SELECT_STAGE_H__