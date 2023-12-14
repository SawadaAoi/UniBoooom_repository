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
	�E2023/11/24 �p�����[�^�[�ǉ�(// �J����) Takagi
	�E2023/11/27 �p�����[�^�[�ǉ�(// �e) nieda
	�E2023/11/30 �p�����[�^�[�ҏW(// �J����) Takagi
	�E2023/12/01 �p�����[�^�[�ǉ�(// HP�A�R���{�̃A�j���[�V�����֘A) nieda
	�E2023/12/05 �p�����[�^�[�ǉ�(// �|�[�Y) Takagi
	�E2023/12/06 �p�����[�^�[�ҏW(// �|�[�Y) Takagi
	�E2023/12/07 �p�����[�^�[�폜(// �s�K�v) Takagi

=========================================== */
#ifndef __GAME_PARAMETER_H__
#define __GAME_PARAMETER_H__

// =============== �p�����[�^�[ ���[�h =======================
#define MODE_GAME_PARAMETER	(true)

#if MODE_GAME_PARAMETER
// =============== �C���N���[�h ===================
#include "Pos2d.h"
#include "Pos3d.h"
#include <DirectXMath.h>


//�Q�[���V�[��================================================
const float BGM_VOLUME = 0.02f;				//�V�[���Q�[���̉���
const float SE_HAMMER_HIT_VOLUME = 0.5f;	// �X���C����ł�������SE�̉���
// ��ʃT�C�Y
const int SCREEN_WIDTH_ = 1280;
const int SCREEN_HEIGHT_ = 720;


// �v���C���[ ================================================
const float PLAYER_MOVE_SPEED	= 0.12f;			// �v���C���[�̈ړ����x
const int	PLAYER_HP			= 10;			// �v���C���[��HP
const float PLAYER_RADIUS		= 0.12f;			// �v���C���[�̓����蔻��̑傫��
const float PLAYER_SIZE			= PLAYER_RADIUS * 2.0f;			// �v���C���[�̑傫��
const int	NO_DAMAGE_TIME		= 3 * 60;		// �v���C���[�̖��G����
const int	DAMAGE_FLASH_FRAME	= int(0.1f * 60);	// �v���C���[�̃_���[�W�_�ł̐؂�ւ��Ԋu


// �n���}�[
const float SWING_TIME_FRAME	= 0.15f * 60;							// �n���}�[��U�鎞��(�t���[���P��)
const float ROTATE_RADIUS		= 2.0f;									// �n���}�[����]����v���C���[����̋���
const float HAMMER_COL_SIZE		= 2.0f;								//�n���}�[�̓����蔻��̑傫��
const float HAMMER_SIZE			= HAMMER_COL_SIZE * 0.26666f;									//�n���}�[�̑傫��
const float INTERVAL_INITIAL = 0.2f;								//�n���}�[�����Ԋu
const float SwingSpeed_PLUS = 1.4f;									//�n���}�[�����U��Ƃ��ɏ�Z�����l
const float SwingSpeed_MINUS = 0.99f;									//���t���[���n���}�[��U��Ԋu��Z��������l
const float SwingSpeed_SIOW = 50.0f;


// �G�L���� ==================================================

// ����
const int	MAX_SLIME_NUM = 25;					// �X���C���̍ő吶����
const int	MAX_BOSS_SLIME_NUM = 1;				// �{�X�X���C���̍ő吶����
const int	START_ENEMY_NUM = 6;				// �Q�[���J�n���̓G�L�����̐�
const float ENEMY_MOVE_SPEED = 0.035f;			// �G�̒ʏ�ړ����x
const float MOVE_DISTANCE_PLAYER = 18.0f;	// �v���C���[�ǐՈړ��ɐ؂�ւ��鋗��
const int ENEMY_CREATE_INTERVAL		= int(1.0f * 60);			// �����Ԋu
const int RANDOM_POS = 15;										// �������W�͈�
const int CREATE_DISTANCE = 19;									// �v���C���[����ǂꂭ�炢���ꂽ�����ɐ������邩
const int SLIME_LEVEL1_PER = 65;								// �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER = 20;								// �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER = 5;									// �X���C��_3�̐����m��
const int SLIME_LEVEL_FLAME_PER = 5;							// �X���C��_�t���C���̐����m��
const int SLIME_LEVEL_HEAL_PER = 5;								// �X���C��_�q�[���̐����m��
const float MAX_SIZE_EXPLODE		= 6.0f;						// �X���C��4���m�̔����̑傫��
const float EXPLODE_BASE_RATIO		= 1.5f;						// �X���C���̔����ڐG�ł̔����̑傫���̃x�[�X
const float ESCAPE_DISTANCE			= 15.0f;					// ���������̋������߂������瓦����͈�
const int ESCAPE_TIME				= int(60 * 0.8f);			// ���̊Ԋu�œ����鏈�����I������

// �X���C�����m�̔��˂̌��Z�l
const float LEAVE_DISTANCE = 29.0f;					// ����ȏ㗣�ꂽ��Ίp����Ɉړ�����

// �T�C�Y1
const float LEVEL1_SCALE = 1.0f;					// �X���C���Q���x���P�̑傫��(�����蔻��܂�)
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;		// �ړ����x

// �T�C�Y2
const float LEVEL2_SCALE = 2.0f;					// �X���C���Q���x���Q�̑傫��(�����蔻��܂�)
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.9f;	// �ړ����x

// �T�C�Y3
const float LEVEL3_SCALE = 4.5f;					// �X���C���Q���x���R�̑傫��(�����蔻��܂�)
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.7f;	// �ړ����x
const float LEVEL3_STOP_RANGE = DirectX::XMConvertToRadians(20.0f);	// �X���C�����~�܂�p�x�͈̔�
const int	LEVEL2_ATTACK_INTERVAL = int(60 * 4.0f);		// �U���I�����玟�̍U���܂ł̊Ԋu
const int	LEVEL2_ATTACK_CHARGE_CNT = int(60 * 1.0f);	// �ːi����܂ł̂��ߎ���
const int	LEVEL2_ATTACK_TACKLE_CNT = int(60 * 0.45f);	// �ːi���Ă��鎞��
const float	LEVEL2_TACKLE_SPEED = 0.2f;					// �ːi�̑��x

// �T�C�Y4
const float LEVEL4_SCALE = 5.5f;					// �X���C���Q���x���S�̑傫��(�����蔻��܂�)
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.5f;	// �ړ����x
const int	LEVEL4_ATTACK = 2;						// �U����

// �t���C���X���C��
const float LEVEL_FLAME_SCALE = 1.5f;						// �X���C���Q�t���C���̑傫��(�����蔻��܂�)
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;	// �ړ����x
const int	LEVEL_FLAME_ATTACK = 1;							// �U����

// �q�[���X���C��
const float LEVEL_HEAL_SCALE = 1.5f;						// �X���C���Q�q�[���̑傫��(�����蔻��܂�)
const float LEVEL_HEAL_SPEED = ENEMY_MOVE_SPEED * 0.3f;		// �ړ����x
const int	LEVEL_HEAL_ATTACK = 1;							// �U���� �i����H

// �{�X�X���C��
const float LEVEL_BOSS_1_SCALE = 6.0f;								// �{�X�P�̑傫��
const float LEVEL_BOSS_1_SPEED = ENEMY_MOVE_SPEED * 0.4f;			// �{�X�P�̃X�s�[�h
const int	BOSS_1_MAX_HP = 10;								// �{�X�P�̍ő�HP
const int	BOSS_1_ATTACK = 2;								// �{�X�P�̍U����
const float SLIME_HP_HEIGHT = 5.0f;							//�{�X�̗͕̑\���ʒu�iY�j
const float ASSAULT_DISTANCE = 0.2f;								// �ˌ���������
const int	ASSAULT_COOL_TIME = 10 * 60;							// �ˌ��N���[�^�C��
const int	ASSAULT_CHARGE_TIME = int(2 * 60);						// �ˌ��`���[�W����
const int	ASSAULT_TIME = int(1.0f * 60);						// �ˌ�������
const float ASSAULT_SPEED = LEVEL_BOSS_1_SPEED * 20.0f;		// �ˌ����̃X�s�[�h
const float BOSS_HP_SIZEX = 0.3f;		// �̗͂P���̑傫���iX�j
const float BOSS_HP_SIZEY = 0.5f;		// �̗͂P���̑傫���iY�j
const float BOSS_HPFRAME_SIZEX = 0.2f;	// �̗̓Q�[�W���ǂꂾ���傫�����iX�j
const float BOSS_HPFRAME_SIZEY = 0.2f;	// �̗̓Q�[�W���ǂꂾ���傫�����iY�j
const float BOSS_HP_POSX = 8.6f;		// �̗̓o�[�i������j�̈ʒu
const int BOSS_DAMAGE_FLASH_FRAME = int(0.1f * 60);					// �_���[�W�󂯂��ۂ̓_�Ńt���[��(���G�ł͂Ȃ�)
const int BOSS_DAMAGE_FLASH_TOTAL_FRAME = int(0.5f * 60);			// �_���[�W���󂯂��ۂ̓_�ł����t���[���s����
const float ADD_CREATE_BOSS_POS_Z = 20.0f;							// �{�X�̐����ʒu(�v���C���[�̐����ʒu�ɑ΂��Ăǂꂾ�����ɏo����)


// ���� =====================================================
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// �X���C��_1�̔���������
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// �X���C��_2�̔���������
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// �X���C��_3�̔���������
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// �X���C��_4�̔���������
const float LEVEL_BOSS_EXPLODE_TIME = 4.0f * 60.0f;	// �X���C��_�{�X�̔���������
const int	DELAY_TIME = int(0.2f * 60);			// �x���b��


// �X���C�����ԍ����� =====================================================
const enum TIME_STATE
{
	STATE_FIRST = 0,
	STATE_SECOND,
	STATE_THIRD,
	STATE_MAX,
};


// �^�C�}�[ =====================================================
const float SLM_PARAM_CHANGE_TIME[STATE_MAX]	= { 60.0f, 120.0f, 180.0f };	// �o�ߎ��Ԃ̕b��
const int	SLM_CREATE_NUM[STATE_MAX]			= { 20, 25, MAX_SLIME_NUM };	// �ő吶����
const float SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 1.0f, 1.5f, 1.5f };			// �����Ԋu
const float SLM_MOVE_ADD_SPEED[STATE_MAX]		= { 1.0f, 1.1f, 1.2f };			// �ړ��X�s�[�h


// �{�X�Q�[�W =====================================================
typedef struct
{
	float startTime;	// �J�n����(�b)
	float maxTime;		// �Q�[�W�o�ߍő厞��(�b)

}BossGaugeSetParam;

const BossGaugeSetParam BOSS_GAUGE_S1[2] = { {0, 45},{75, 45} };	// �X�e�[�W1�̃{�X�Q�[�W�ݒ�

const int FADE_TIME = 5 * 60;										// �{�X�Q�[�W�����܂��Ă�������鎞��
 

// �� ====================================
const float FLOOR_SCALE_X = 3.1f;
const float FLOOR_SCALE_Z = 3.1f;


// �^�C�g����� =========================================================
const float TEXTURE_TITLE_TITLE_POSX = SCREEN_WIDTH_ / 2;	// �^�C�g���摜�\���ʒu��X���W
const float TEXTURE_TITLE_TITLE_POSY = 400.0f;				// �^�C�g���摜�\���ʒu��Y���W
const float TEXTURE_TITLE_TITLE_WIDTH = 300.0f;				// �^�C�g���摜�̉���
const float TEXTURE_TITLE_TITLE_HEIGHT = 50.0f;				// �^�C�g���摜�̏c��
const float TEXTURE_TITLE_BUTTON_POSX = SCREEN_WIDTH_ / 2;	// �^�C�g���摜�\���ʒu��X���W
const float TEXTURE_TITLE_BUTTON_POSY = 100.0f;				// �^�C�g����ʃ{�^�������w���摜�\���ʒu��Y���W
const float TEXTURE_TITLE_BUTTON_WIDTH = 300.0f;			// �^�C�g����ʃ{�^�������w���摜�̉���
const float TEXTURE_TITLE_BUTTON_HEIGHT = 100.0f;			// �^�C�g����ʃ{�^�������w���摜�̏c��


// �q�b�g�X�g�b�v =========================================================
const int FRAME_STOP_SOFT = 2;		//�X�g�b�v�F�y�@�̃t���[����	// ���ݎg�p���Ă��镨
const int FRAME_STOP_NORMAL = 4;	//�X�g�b�v�F���@�̃t���[����


// �Q�[���J�n���X�^�[�g�\�� ==================================================
const float TIME_WAIT_START = 75;				// �Q�[���J�n���}�\���҂�����
const int SWITCH_ANIM_START = 1;				// �X�^�[�g�A�j���[�V�����؂�ւ�����
const int START_SCALE_X = SCREEN_WIDTH_;		// UI�̉���
const int START_SCALE_Y = SCREEN_HEIGHT_;		// UI�̏c��
const float START_POS_X = SCREEN_WIDTH_ / 2;	// �\���ʒu��X���W
const float START_POS_Y = SCREEN_HEIGHT_ / 2;	// �\���ʒu��Y���W


// �Q�[���N���A�A�Q�[���I�[�o�[�\�� ==================================================
const int SWITCH_ANIM_CLEAR = 1;				// �����A�j���[�V�����؂�ւ�����
const int SWITCH_ANIM_OVER = 1;					// ���s�A�j���[�V�����؂�ւ�����
const int STATE_SCALE_X = SCREEN_WIDTH_;		// UI�̉���
const int STATE_SCALE_Y = SCREEN_HEIGHT_;		// UI�̏c��
const float STATE_POS_X = SCREEN_WIDTH_ / 2;	// �\���ʒu��X���W
const float STATE_POS_Y = SCREEN_HEIGHT_ / 2;	// �\���ʒu��Y���W


// �|�[�Y ====================================================================
const float COMMAND_SPACE_HALF = 85.0f;	//�R�}���h���m�̏c�̊�
const float CHARA_Y = 620.0f;			//�|�[�Y�\�L�����Sy�ʒu
const float CHARA_SPACE = 85.0f;		//�|�[�Y�\�L�̉��̊�
const float CHARA_WIDTH = 100.0f;		//�|�[�Y�\�L����
const float CHARA_HEIGHT = 100.0f;		//�|�[�Y�\�L�c��
const float COMMAND_WIDTH = 360.0f;		//�R�}���h�c��
const float COMMAND_HEIGHT = 78.0f;		//�R�}���h����

#endif // !MODE_GAME_PARAMETER
#endif // !__GAME_PARAMETER_H__