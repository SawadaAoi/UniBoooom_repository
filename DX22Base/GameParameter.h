/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���p�����[�^�[�����p�w�b�_
	---------------------------------------
	GameParameter.h

	�쐬��	�鑺����

	�ύX����
	�E2023/11/11 �w�b�_�쐬 suzumura


=========================================== */
#ifndef __GAME_PARAMETER_H__
#define __GAME_PARAMETER_H__

// =============== �p�����[�^�[ ���[�h =======================
#define MODE_GAME_PARAMETER	(true)

#if MODE_GAME_PARAMETER

// �v���C���[ ================================================
const float PLAYER_MOVE_SPEED	= 0.1f;		// �v���C���[�̈ړ����x
const int	PLAYER_HP			= 5;		// �v���C���[��HP
const float PLAYER_RADIUS		= 0.1f;		// �v���C���[�̓����蔻��̑傫��
const float PLAYER_SIZE			= 1.0f;		// �v���C���[�̑傫��
const int	NO_DAMAGE_TIME		= 3 * 60;	// �v���C���[�̖��G����
const int	DAMAGE_FLASH_FRAME	= 0.1 * 60;	// �v���C���[�̃_���[�W�_�ł̐؂�ւ��Ԋu

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


const int ENEMY_CREATE_INTERVAL		= 2 * 60;									// �����Ԋu
const int RANDOM_POS				= 15;										// �������W�͈�
const int CREATE_DISTANCE			= 10;										// �v���C���[����ǂꂭ�炢���ꂽ�����ɐ������邩
const int SLIME_LEVEL1_PER			= 50;										// �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER			= 30;										// �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER			= 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER;// �X���C��_3�̐����m��
const float MAX_SIZE_EXPLODE		= 8.0f;										// �X���C��4���m�̔����̑傫��
const float EXPLODE_BASE_RATIO		= 2.0f;										// �X���C���̔����ڐG�ł̔����̑傫���̃x�[�X

// �X���C�����m�̔��˂̌��Z�l
// ��1.0f�ł��̂܂�
const float COL_SUB_HIT_TO_BIG		= 0.1f;			// �X���C���Փ�(������)�̏Փˑ��̌��Z�l(���˂���ړ�)
const float COL_SUB_STAND_TO_SMALL	= 0.8f;			// �X���C���Փ�(������)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)
const float COL_SUB_HIT_TO_SMALL	= 0.3f;			// �X���C���Փ�(�偨��)�̏Փˑ��̌��Z�l(�ړ�����)
const float COL_SUB_STAND_TO_BIG	= 1.2f;			// �X���C���Փ�(�偨��)�̏Փ˂���鑤�̌��Z�l(�Փ˂��ꂽ����)

// �T�C�Y1
const float LEVEL1_SCALE = 1.0f;					// �X���C���Q���x���P�̑傫��(�����蔻��܂�)
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;		// �ړ����x

// �T�C�Y2
const float LEVEL2_SCALE = 2.0f;					// �X���C���Q���x���Q�̑傫��(�����蔻��܂�)
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.9;	// �ړ����x

// �T�C�Y3
const float LEVEL3_SCALE = 3.0f;					// �X���C���Q���x���R�̑傫��(�����蔻��܂�)
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.7;	// �ړ����x

// �T�C�Y4
const float LEVEL4_SCALE = 5.0f;					// �X���C���Q���x���S�̑傫��(�����蔻��܂�)
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.5;	// �ړ����x


// ���� =====================================================
const int	MAX_EXPLOSION_NUM		= 20;				// �ő唚����
const float MAX_DISPLAY_TIME		= 2.0f * 60;		// ���������b��
const float ONE_SECOND_FRAME		= 1.0f * 30;		// �傫���Ȃ�܂ł̕b��


// �J���� =====================================================
const TPos3d<float> INIT_POS(0.0f, 2.6f, -3.0f);					// �����ʒu

const float INIT_ANGLE	= DirectX::XMConvertToRadians(73.0f);       // �J�����̊p�x
const float INIT_NEAR	= 1.0f;										// ��ʎ�O����z�l
const float INIT_FAR	= 150.0f;									// ��ʉ�����z�l
const float INIT_RADIUS = 15.0f;									// �J�����ƒ����_�Ƃ̋���(�����l)





#endif

#endif // !__GAME_PARAMETER_H__




