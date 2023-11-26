/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���p�����[�^�[�����p�w�b�_
	---------------------------------------
	GameParameter.h

	�쐬��	�鑺����

	�ύX����
	�E2023/11/11 �w�b�_�쐬 Suzumura
	�E2023/11/13 �p�����[�^�[�ǉ�(LEVEL_�Z_EXPLODE_TIME) Suzumura
	�E2023/11/14 �p�����[�^�[�ǉ�(// �t���C���X���C��) Suzumura
	�E2023/11/15 �p�����[�^�[�ǉ�(// �t���C���X���C��) Suzumura
	�E2023/11/18 �p�����[�^�[�ǉ�(// �X�R�A) yamamoto
	�E2023/11/21 �p�����[�^�[�ǉ�(// �R���{��) Sawada
	�E2023/11/23 �p�����[�^�[�ǉ�(// �{�X�P�X���C��) Suzumura
	�E2023/11/23 �p�����[�^�[�ǉ�(// 2D�`��) nieda
	�E2023/11/24 �p�����[�^�[�폜(// �J����) Takagi
	�E2023/11/25 �p�����[�^�[�ǉ�(// �X�R�A) yamamoto

=========================================== */
#ifndef __GAME_PARAMETER_H__
#define __GAME_PARAMETER_H__

// =============== �C���N���[�h ===================
#include "Pos2d.h"
#include "Pos3d.h"
#include <DirectXMath.h>

// =============== �p�����[�^�[ ���[�h =======================
#define MODE_GAME_PARAMETER	(true)

#if MODE_GAME_PARAMETER

// =============== �C���N���[�h ===================
#include "Pos3d.h"

//�Q�[���V�[��================================================
const float BGM_VOLUME = 0.02f;				//�V�[���Q�[���̉���
const float SE_HAMMER_HIT_VOLUME = 0.5f;	// �X���C����ł�������SE�̉���
// ��ʃT�C�Y
const int SCREEN_WIDTH_ = 1280;
const int SCREEN_HEIGHT_ = 720;

// �v���C���[ ================================================
const float PLAYER_MOVE_SPEED	= 0.1f;			// �v���C���[�̈ړ����x
const int	PLAYER_HP			= 5;			// �v���C���[��HP
const float PLAYER_RADIUS		= 0.1f;			// �v���C���[�̓����蔻��̑傫��
const float PLAYER_SIZE			= 0.2f;			// �v���C���[�̑傫��
const int	NO_DAMAGE_TIME		= 3 * 60;		// �v���C���[�̖��G����
const int	DAMAGE_FLASH_FRAME	= 0.1f * 60;	// �v���C���[�̃_���[�W�_�ł̐؂�ւ��Ԋu
const int	SE_RUN_INTERVAL		= 0.4f * 60;	//�v���C���[�̈ړ��ɂ��SE�����̊Ԋu
const float	SE_RUN_VOLUME		= 0.3f;			//�ړ��ɂ��SE�̉���

// �n���}�[
const float HAMMER_ANGLE_X		= DirectX::XMConvertToRadians(180.0f);								//�n���}�[�̕\���p�x
const float HAMMER_ANGLE_Y		= DirectX::XMConvertToRadians(0.0f);								//�n���}�[�̕\���p�x
const float HAMMER_ANGLE_Z		= DirectX::XMConvertToRadians(0.0f);								//�n���}�[�̕\���p�x
const float SWING_ANGLE			= DirectX::XMConvertToRadians(90.0f);	// �n���}�[��U��͈�(��`�̊p�x�̑傫��)
const float SWING_TIME_FRAME	= 0.15f * 60;							// �n���}�[��U�鎞��(�t���[���P��)
const float ROTATE_RADIUS		= 1.0f;									// �n���}�[����]����v���C���[����̋���
const float HAMMER_COL_SIZE		= 0.75f;								//�n���}�[�̓����蔻��̑傫��
const float HAMMER_SIZE			= 0.2f;									//�n���}�[�̑傫��


// �G�L���� ==================================================

// ����
const int	MAX_SLIME_NUM = 50;		// �X���C���̍ő吶����
const int	MAX_BOSS_SLIME_NUM = 5;		// �{�X�X���C���̍ő吶����
const int	START_ENEMY_NUM = 6;		// �Q�[���J�n���̓G�L�����̐�
const float ENEMY_MOVE_SPEED = 0.035f;	// �G�̒ʏ�ړ����x
const float HAMMER_HIT_MOVE_SPEED = 1.0f;		// �n���}�[�ɐ�����΂��ꂽ���̃X�s�[�h
const int	RANDOM_MOVE_SWITCH_TIME = 3 * 60;	// �����_���ړ��̕����؂�ւ�

const float SPEED_DOWN_RATIO = 0.6f;		// ������ԍۂɂ�����ړ����x�̕ω��̊���    RATIO=>����
const float MOVE_RESIST = 0.05f;	// ������шړ����̃X���C���̈ړ����x�ɖ��t���[�������錸�Z���l
const float MOVE_DISTANCE_PLAYER = 13.0f;	// �v���C���[�ǐՈړ��ɐ؂�ւ��鋗��
const float SLIME_BASE_RADIUS = 0.5f;		// �X���C���̊�̑傫��

const int ENEMY_CREATE_INTERVAL = 2 * 60;													// �����Ԋu
const int RANDOM_POS = 15;														// �������W�͈�
const int CREATE_DISTANCE = 10;														// �v���C���[����ǂꂭ�炢���ꂽ�����ɐ������邩
const int SLIME_LEVEL1_PER = 45;																// �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER = 35;																// �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER = 10;																// �X���C��_3�̐����m��
const int SLIME_LEVEL_FLAME_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// �X���C��_�t���C���̐����m��
const float MAX_SIZE_EXPLODE = 5.0f;										// �X���C��4���m�̔����̑傫��
const float EXPLODE_BASE_RATIO = 1.5f;										// �X���C���̔����ڐG�ł̔����̑傫���̃x�[�X


// �X���C�����m�̔��˂̌��Z�l
// ��1.0f�ł��̂܂�
const float COL_SUB_HIT_TO_BIG = 0.1f;			// �X���C���Փ�(������)�̏Փˑ��̌��Z�l(���˂���ړ�)
const float COL_SUB_STAND_TO_SMALL = 0.8f;			// �X���C���Փ�(������)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
const float COL_SUB_HIT_TO_SMALL = 0.3f;			// �X���C���Փ�(�偨��)�̏Փˑ��̌��Z�l(�ړ�����)
const float COL_SUB_STAND_TO_BIG = 1.2f;			// �X���C���Փ�(�偨��)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)

// �T�C�Y1
const float LEVEL1_SCALE = 1.0f;					// �X���C���Q���x���P�̑傫��(�����蔻��܂�)
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;		// �ړ����x

// �T�C�Y2
const float LEVEL2_SCALE = 2.0f;					// �X���C���Q���x���Q�̑傫��(�����蔻��܂�)
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.9f;	// �ړ����x

// �T�C�Y3
const float LEVEL3_SCALE = 3.0f;					// �X���C���Q���x���R�̑傫��(�����蔻��܂�)
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.7f;	// �ړ����x

// �T�C�Y4
const float LEVEL4_SCALE = 5.0f;					// �X���C���Q���x���S�̑傫��(�����蔻��܂�)
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.5f;	// �ړ����x

// �t���C���X���C��
const float LEVEL_FLAME_SCALE = 1.0f;						// �X���C���Q�t���C���̑傫��(�����蔻��܂�)
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;	// �ړ����x

const int LEVEL_1_SCORE = 10;				// �X���C��_1�̃X�R�A
const int LEVEL_2_SCORE = 30;				// �X���C��_2�̃X�R�A
const int LEVEL_3_SCORE = 100;				// �X���C��_3�̃X�R�A
const int LEVEL_4_SCORE = 500;				// �X���C��_4�̃X�R�A
const int LEVEL_4x4_SCORE = 1000;			// �ԁX�̔����̃X�R�A
// �{�X�X���C��
#define DEBUG_BOSS	(false)	// �f�o�b�O�p�ɃQ�[���J�n���{�X�𐶐����邩�ǂ���

const float LEVEL_BOSS_1_SCALE = 6.0f;								// �{�X�P�̑傫��
const float LEVEL_BOSS_1_SPEED = ENEMY_MOVE_SPEED * 0.4f;			// �{�X�P�̃X�s�[�h
const int	BOSS_1_MAX_HP = 10;								// �{�X�P�̍ő�HP

const float ASSAULT_DISTANCE = 0.2f;								// �ˌ���������
const int	ASSAULT_COOL_TIME = 10 * 60;							// �ˌ��N���[�^�C��
const int	ASSAULT_CHARGE_TIME = 2 * 60;							// �ˌ��`���[�W����
const int	ASSAULT_TIME = 1.0f * 60;						// �ˌ�������
const float ASSAULT_SPEED = LEVEL_BOSS_1_SPEED * 20.0f;		// �ˌ����̃X�s�[�h

const int BOSS_DAMAGE_FLASH_FRAME = 0.1 * 60;					// �_���[�W�󂯂��ۂ̓_�Ńt���[��(���G�ł͂Ȃ�)
const int BOSS_DAMAGE_FLASH_TOTAL_FRAME = 0.5 * 60;					// �_���[�W���󂯂��ۂ̓_�ł����t���[���s����

// ���� =====================================================
const int	MAX_EXPLOSION_NUM = 20;			// �ő唚����
const float EXPAND_QUICK_RATE = 0.2f;			// �c���������� 
const int MAX_BOOOOM_NUM = 10;					//�ő�boom��
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// �X���C��_1�̔���������
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// �X���C��_2�̔���������
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// �X���C��_3�̔���������
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// �X���C��_4�̔���������
const float LEVEL_BOSS_EXPLODE_TIME = 4.0f * 60.0f;	// �X���C��_�{�X�̔���������
const int	DELAY_TIME = 0.2f * 60;		// �x���b��

const int	LEVEL_1_EXPLODE_DAMAGE = 1;
const int	LEVEL_2_EXPLODE_DAMAGE = 2;
const int	LEVEL_3_EXPLODE_DAMAGE = 3;
const int	LEVEL_4_EXPLODE_DAMAGE = 4;
// �X�R�A =====================================================
const float SLIME_SCORE_HEIGHT = 4.0f;			//����������X�R�A�̕\���ʒu

const int TOTALSCORE_DIGIT = 5;				//�g�[�^���X�R�A�̌���
const int MAX_TOTALSCORE = 99999;			//���ꏏ�ɕς��Ă��������i������9��ǉ��j//�ő�g�[�^�A���X�R�A
const TPos2d<float> TOTALSCORE_POS(1100.0f, 25.0f);			//�g�[�^���X�R�A�̈ʒu�ݒ�

const DirectX::XMFLOAT2 TOTALSCORE_SIZE(50.0f, -50.0f);		//�g�[�^���X�R�A�̕\���̑傫��
const DirectX::XMFLOAT2 PLUSSCORE_SIZE(30.0f, -30.0f);		//�v���X�X�R�A�̕\���̑傫��
const int ROW_HIGHT = 40;			//�X�R�A�𕡐��\������ԏォ��ǂ̂��炢�����邩�iPLUSSCORE_SIZE.y�̐�Βl���傫�������Łj

const DirectX::XMFLOAT2 SMALLDECIMAL_SIZE(15.0f, -15.0f);	//�����_�̑傫��
const int MAGNIFICATION = 40;		//�{���\�����̊Ԋu�B��ԉE�̐�������ǂꂾ�����ɂ��炷���i�����_������̂ł������P�A����j
const TPos2d<float> SMALLDECIMAL_POS(2.0f, -3.0f);//���̒l�ŏ����_�̈ʒu�̔�����


// �J���� =====================================================
const TPos3d<float> INIT_POS(0.0f, 2.6f, -3.0f);					// �����ʒu

const float INIT_ANGLE = DirectX::XMConvertToRadians(73.0f);       // �J�����̊p�x
const float INIT_NEAR = 1.0f;										// ��ʎ�O����z�l
const float INIT_FAR = 150.0f;									// ��ʉ�����z�l
const float INIT_RADIUS = 15.0f;									// �J�����ƒ����_�Ƃ̋���(�����l)

// UI =====================================================
// 2D�\��
const float VIEW_LEFT = 0.0f;		// ��ʍ��[�̍��W
const float VIEW_RIGHT = 1280.0f;	// ��ʉE�[�̍��W�i��ʉ����j
const float VIEW_BOTTOM = 720.0f;	// ��ʉ��[�̍��W�i��ʏc���j
const float VIEW_TOP = 0.0f;		// ��ʏ�[�̍��W
const float NEAR_Z = 0.1f;			// ��ʂɎʂ�n�߂鋗��
const float FAR_Z = 10.0f;			// �ʂ�����E����

// �^�C�}�[ =====================================================
const int STAGE_TIME = 180 * 60;	//�X�e�[�W�������ԁi�b*�t���[���j
const TPos2d<float> MINUTE_POS(565.0f, 25.0f);			//���̈ʒu�ݒ�
const TPos2d<float> SECOND_TENS_POS(640.0f, 25.0f);	//�\�̌��b�̈ʒu�ݒ�
const TPos2d<float> SECOND_ONE_POS(690.0f, 25.0f);		//��̌��b�̈ʒu�ݒ�
const TPos2d<float> TIME_BACKGROUND_POS(630.0f, 25.0f);	//�o�b�N�O���E���h�ʒu�ݒ�
const TPos2d<float> TIME_COLON_POS(602.5f, 25.0f);		//�R�����̈ʒu�ݒ�
const float TIME_BACK_GROUND_SIZE_X = 200.0f;			//�^�C�}�[�̃o�b�N�O�����h��X�̒����ݒ�
const float TIME_BACK_GROUND_SIZE_Y = -75.0f;			//�^�C�}�[�̃o�b�N�O�����h��Y�̒����ݒ�
const float TIME_COLON_SIZE_X = 35.0f;					//�^�C�}�[�̃R������X�̒����ݒ�
const float TIME_COLON_SIZE_Y = -35.0f;					//�^�C�}�[�̃R������Y�̒����ݒ�

// �{�X�Q�[�W =====================================================
const int BOSS_GAUGE_FULL_TIME = 45 * 60;		//�{�X�Q�[�WMAX�ɂȂ鎞��(���b�o��) * 60�t���[��
const int SECOND_EMPTY_BOSS_GAUGE = 75 * 60;		//��̖ڂ̃{�X��Q�[�W�\������ * 60�t���[��
const TPos2d<float> BOSS_GAUGE_EMPTY_POS(765.0f, 30.0f);	//�{�X�Q�[�W�i��j�̈ʒu�ݒ�
const TPos2d<float> BOSS_GAUGE_FULL_POS(765.0f, 31.5f);	//�{�X�Q�[�W�i���j�̈ʒu�ݒ�
const float BOSS_GAUGE_EMPTY_SIZE_X = 60.0f;			//�{�X�Q�[�W�i��j��X�̒����ݒ�
const float BOSS_GAUGE_EMPTY_SIZE_Y = -60.0f;			//�{�X�Q�[�W�i��j��Y�̒����ݒ�
const float BOSS_GAUGE_FULL_SIZE_X = (6.0f / 7.0f) * BOSS_GAUGE_EMPTY_SIZE_X;			//�{�X�Q�[�W�i���j��X�̒����ݒ�
const float BOSS_GAUGE_FULL_SIZE_Y = (6.0f / 7.0f) * BOSS_GAUGE_EMPTY_SIZE_Y;			//�{�X�Q�[�W�i���j��Y�̒����ݒ�
const float BOSS_GAUGE_FULL_POS_Y_ADJUST = BOSS_GAUGE_FULL_SIZE_X / 2;		//�{�X�Q�[�W�������A�ʒu�\�����邽�߂̒�����
const float BOSS_GAUGE_FULL_SIZE_Y_ADJUST = BOSS_GAUGE_FULL_SIZE_Y;	//�{�X�Q�[�W�������A�T�C�Y�v�Z�p�i�v�Z���ĕ\���������䗦�����錳�X�̃T�C�Y(100.0f)�j
const int FADE_TIME = 5 * 60;							//�{�X�Q�[�W�����܂��Ă�������鎞��


// HP
const float DRAW_POSX = 80.0f;	// �e�N�X�`����\������ʒu��X���W
const float DRAW_FIRSTPOSX = 0.9f;		// 1�ڂ̃e�N�X�`����\������ʒu�̒��ߗp
const float DRAW_GAP = 1.15f;	// �e�N�X�`�����m�̊Ԋu
const float DRAW_POSY = 60.0f;	// �e�N�X�`����\������ʒu��Y���W
const float DRAW_HEIGHT = 90.0f;	// �e�N�X�`���̏c��
const float DRAW_WIDTH = 90.0f;	// �e�N�X�`���̉���

// BoooomUI =====================================================
const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUI��X�̒����itexture�̔䗦�ƍ��킹��j
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUI��Y�̒����itexture�̔䗦�ƍ��킹��j
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUI�T�C�Y�̃X�P�[��
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUI�T�C�Y�̃X�P�[��

// �R���{ =========================================================
const int	MAX_COMBO_NUM = 5;					// �ő哯���R���{��
const TPos2d<float> COMBO_UI_POSITION = { 1025.0f, 600.0f };	// �R���{UI�̕`��ʒu
const TPos2d<float> COMBO_UI_SIZE = { 70.0f, 130.0f };	// �R���{UI�̑傫��
const float COMBO_UI_NUM_SPACE = 80.0f;				// �����̊ԃX�y�[�X
const float COMBO_UI_MULTI_DISP_SPACE = 100.0f;				// �����R���{�`�掞�̏㉺�̋�
const int COMBO_UI_DISP_DILAY_TIME = 2.0f * 60;			// �c�R���{���\���̕b��

const TPos2d<float> COMBO_UI_BACK_POS = { 1100.0f, 600.0f };	// �R���{UI�̔w�i�̕`��ʒu
const TPos2d<float> COMBO_UI_BACK_SIZE = { 370.0f, 280.0f };	// �R���{UI�̔w�i�̑傫��
const TPos2d<float> COMBO_UI_STRING_POS = { 1150.0f, 615.5f };	// �R���{UI�̕����̕`��ʒu
const TPos2d<float> COMBO_UI_STRING_SIZE = { 180.0f, 100.0f };		// �R���{UI�̕����̑傫��

// �� ====================================
const float FLOOR_SCALE_X = 1.1f;
const float FLOOR_SCALE_Z = 1.1f;
const float FLOOR_OFFSET_X = 48.0f * FLOOR_SCALE_X;
const float FLOOR_OFFSET_Z = 48.0f * FLOOR_SCALE_Z;

// �^�C�g����� =========================================================
const float TEXTURE_TITLE_TITLE_POSX = SCREEN_WIDTH_ / 2;	// �^�C�g���摜�\���ʒu��X���W
const float TEXTURE_TITLE_TITLE_POSY = 400.0f;				// �^�C�g���摜�\���ʒu��Y���W
const float TEXTURE_TITLE_TITLE_WIDTH = 300.0f;				// �^�C�g���摜�̉���
const float TEXTURE_TITLE_TITLE_HEIGHT = 50.0f;				// �^�C�g���摜�̏c��
const float TEXTURE_TITLE_BUTTON_POSX = SCREEN_WIDTH_ / 2;	// �^�C�g���摜�\���ʒu��X���W
const float TEXTURE_TITLE_BUTTON_POSY = 100.0f;				// �^�C�g����ʃ{�^�������w���摜�\���ʒu��Y���W
const float TEXTURE_TITLE_BUTTON_WIDTH = 300.0f;			// �^�C�g����ʃ{�^�������w���摜�̉���
const float TEXTURE_TITLE_BUTTON_HEIGHT = 100.0f;			// �^�C�g����ʃ{�^�������w���摜�̏c��

#endif

#endif // !__GAME_PARAMETER_H__




