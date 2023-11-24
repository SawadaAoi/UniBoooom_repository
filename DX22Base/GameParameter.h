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
	�E2023/11/21 �p�����[�^�[�ǉ�(// �R���{��) Sawada

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
const float PLAYER_SIZE			= 1.0f;			// �v���C���[�̑傫��
const int	NO_DAMAGE_TIME		= 3 * 60;		// �v���C���[�̖��G����
const int	DAMAGE_FLASH_FRAME	= 0.1f * 60;	// �v���C���[�̃_���[�W�_�ł̐؂�ւ��Ԋu
const int	SE_RUN_INTERVAL		= 0.4f * 60;	//�v���C���[�̈ړ��ɂ��SE�����̊Ԋu
const float	SE_RUN_VOLUME		= 0.3f;			//�ړ��ɂ��SE�̉���

// �n���}�[
const float SWING_ANGLE			= DirectX::XMConvertToRadians(90.0f);	// �n���}�[��U��͈�(��`�̊p�x�̑傫��)
const float SWING_TIME_FRAME	= 0.15f * 60;							// �n���}�[��U�鎞��(�t���[���P��)
const float ROTATE_RADIUS		= 1.0f;									// �n���}�[����]����v���C���[����̋���
const float HAMMER_COL_SIZE		= 0.75f;								//�n���}�[�̓����蔻��̑傫��
const float HAMMER_SIZE			= 1.5f;									//�n���}�[�̑傫��

// �G�L���� ==================================================

// ����
const int	MAX_SLIME_NUM			= 50;		// �X���C���̍ő吶����
const int	START_ENEMY_NUM			= 6;		// �Q�[���J�n���̓G�L�����̐�
const float ENEMY_MOVE_SPEED		= 0.035f;	// �G�̒ʏ�ړ����x
const float HAMMER_HIT_MOVE_SPEED	= 1.0f;		// �n���}�[�ɐ�����΂��ꂽ���̃X�s�[�h
const int	RANDOM_MOVE_SWITCH_TIME = 3 * 60;	// �����_���ړ��̕����؂�ւ�

const float SPEED_DOWN_RATIO		= 0.6f;		// ������ԍۂɂ�����ړ����x�̕ω��̊���    RATIO=>����
const float MOVE_RESIST				= 0.05f;	// ������шړ����̃X���C���̈ړ����x�ɖ��t���[�������錸�Z���l
const float MOVE_DISTANCE_PLAYER	= 13.0f;	// �v���C���[�ǐՈړ��ɐ؂�ւ��鋗��
const float SLIME_BASE_RADIUS		= 0.5f;		// �X���C���̊�̑傫��

const int ENEMY_CREATE_INTERVAL		= 2 * 60;													// �����Ԋu
const int RANDOM_POS				= 15;														// �������W�͈�
const int CREATE_DISTANCE			= 10;														// �v���C���[����ǂꂭ�炢���ꂽ�����ɐ������邩
const int SLIME_LEVEL1_PER = 45;																// �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER = 35;																// �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER = 10;																// �X���C��_3�̐����m��
const int SLIME_LEVEL_FLAME_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// �X���C��_�t���C���̐����m��
const float MAX_SIZE_EXPLODE		= 5.0f;										// �X���C��4���m�̔����̑傫��
const float EXPLODE_BASE_RATIO		= 1.5f;										// �X���C���̔����ڐG�ł̔����̑傫���̃x�[�X


// �X���C�����m�̔��˂̌��Z�l
// ��1.0f�ł��̂܂�
const float COL_SUB_HIT_TO_BIG		= 0.1f;			// �X���C���Փ�(������)�̏Փˑ��̌��Z�l(���˂���ړ�)
const float COL_SUB_STAND_TO_SMALL	= 0.8f;			// �X���C���Փ�(������)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
const float COL_SUB_HIT_TO_SMALL	= 0.3f;			// �X���C���Փ�(�偨��)�̏Փˑ��̌��Z�l(�ړ�����)
const float COL_SUB_STAND_TO_BIG	= 1.2f;			// �X���C���Փ�(�偨��)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
const float LEAVE_DISTANCE = 40.0f;					// ����ȏ㗣�ꂽ��Ίp����Ɉړ�����

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

// ���� =====================================================
const int	MAX_EXPLOSION_NUM		= 20;		// �ő唚����
const float EXPAND_QUICK_RATE		= 0.2f;		// �c���������� 
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// �X���C��_1�̔���������
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// �X���C��_2�̔���������
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// �X���C��_3�̔���������
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// �X���C��_4�̔���������
const int	DELAY_TIME			 = 0.2f * 60;		// �x���b��


// �J���� C
const TPos3d<float> INIT_POS(0.0f, 2.6f, -3.0f);					// �����ʒu

const float INIT_ANGLE	= DirectX::XMConvertToRadians(73.0f);       // �J�����̊p�x
const float INIT_NEAR	= 1.0f;										// ��ʎ�O����z�l
const float INIT_FAR	= 150.0f;									// ��ʉ�����z�l
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
const TPos2d<float> SECOND_TENS_POS (640.0f, 25.0f);	//�\�̌��b�̈ʒu�ݒ�
const TPos2d<float> SECOND_ONE_POS (690.0f, 25.0f);		//��̌��b�̈ʒu�ݒ�
const TPos2d<float> TIME_BACKGROUND_POS (630.0f, 25.0f);	//�o�b�N�O���E���h�ʒu�ݒ�
const TPos2d<float> TIME_COLON_POS (615.0f, 25.0f);		//�R�����̈ʒu�ݒ�

// HP
const float DRAW_POSX		= 80.0f;	// �e�N�X�`����\������ʒu��X���W
const float DRAW_FIRSTPOSX	= 0.9f;		// 1�ڂ̃e�N�X�`����\������ʒu�̒��ߗp
const float DRAW_GAP		= 1.15f;	// �e�N�X�`�����m�̊Ԋu
const float DRAW_POSY		= 60.0f;	// �e�N�X�`����\������ʒu��Y���W
const float DRAW_HEIGHT		= 90.0f;	// �e�N�X�`���̏c��
const float DRAW_WIDTH		= 90.0f;	// �e�N�X�`���̉���
// �R���{ =========================================================
const int	MAX_COMBO_NUM				= 5;					// �ő哯���R���{��
const TPos2d<float> COMBO_UI_POSITION	= { 1025.0f, 600.0f };	// �R���{UI�̕`��ʒu
const TPos2d<float> COMBO_UI_SIZE		= {   70.0f, 130.0f };	// �R���{UI�̑傫��
const float COMBO_UI_NUM_SPACE			= 80.0f;				// �����̊ԃX�y�[�X
const float COMBO_UI_MULTI_DISP_SPACE	= 100.0f;				// �����R���{�`�掞�̏㉺�̋�
const int COMBO_UI_DISP_DILAY_TIME		= 2.0f * 60;			// �c�R���{���\���̕b��

const TPos2d<float> COMBO_UI_BACK_POS	 = {1100.0f, 600.0f};	// �R���{UI�̔w�i�̕`��ʒu
const TPos2d<float> COMBO_UI_BACK_SIZE	 = {370.0f, 280.0f};	// �R���{UI�̔w�i�̑傫��
const TPos2d<float> COMBO_UI_STRING_POS  = {1150.0f, 615.5f};	// �R���{UI�̕����̕`��ʒu
const TPos2d<float> COMBO_UI_STRING_SIZE = {180.0f, 100.0f};		// �R���{UI�̕����̑傫��

// �� ====================================
const float FLOOR_SCALE_X = 1.1f;
const float FLOOR_SCALE_Z = 1.1f;
const float FLOOR_OFFSET_X = 48.0f * FLOOR_SCALE_X;
const float FLOOR_OFFSET_Z = 48.0f * FLOOR_SCALE_Z;

#endif

#endif // !__GAME_PARAMETER_H__




