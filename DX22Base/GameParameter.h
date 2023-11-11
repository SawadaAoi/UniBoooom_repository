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

// =============== �f�t�@�C�����[�h =======================
#define MODE_DEFINE	(true)

//--.h
//===ExplosionManager.h======
const int MAX_EXPLOSION_NUM = 20;    //�ő唚����

//===SlimeBase.h=======
const float ENEMY_MOVE_SPEED = 0.01f;    //�G�̈ړ����x

//===SlimeManager.h======
const int MAX_SLIME = 30;    //�X���C���̍ő吶����


//--.cpp
//===Explosion.cpp=======
const float MAX_DISPLAY_TIME = 60 * 3.0f;    // ���������b��
const float ONE_SECOND_FRAME = 60;           // �傫���Ȃ�܂ł̕b��

//===Hammer.cpp=======
const float ANGULAR_ANGLE = 0.1f;        //���t���[���ړ�����p�x��
const float ROTATE_RADIUS = 1.0f;        //�n���}�[����]����v���C���[����̋���
const float HAMMER_SIZE = 1.0f;          //�n���}�[�̓����蔻��̑傫��

//===Player.cpp======
const float PLAYERMOVE(0.1f);		//�v���C���[�̈ړ����x
const int PLAYER_HP = 5;			//�v���C���[��HP
const float PLAYER_RADIUS = 0.5f;   //�v���C���[�̓����蔻��̑傫��
const int NO_DAMAGE_TIME = 3 * 60;  //�v���C���[�̖��G����

//===SlimeBase.cpp======
const float SPEED_DOWN_RATIO = 0.6f;		//�X���C�����ڐG���Đ�����ԍۂɂ�����ړ����x�̕ω��̊���    RATIO=>����
const float MOVE_RESIST = 0.1f;				//������шړ����̃X���C���̈ړ����x�ɖ��t���[�������錸�Z���l
const float REFLECT_RATIO = 0.1f;			//�X���C�����X���C���𐁂���΂����ۂɐ�����΂������̃X���C���̈ړ��ʂ�ς��銄��
const float MOVE_DISTANCE_PLAYER = 20.0f;   // �v���C���[�ǐՈړ��ɐ؂�ւ��鋗��
const float SLIME_BASE_RADIUS = 0.5f;		// �X���C���̊�̑傫��

//===Slime_01.cpp======
const float LEVEL1_SCALE = 1.0f;
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;	

//===Slime_02.cpp======
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;

//===Slime_03.cpp======
const float LEVEL3_SCALE = 3.0f;
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.90;

//===Slime_04.cpp======
const float LEVEL4_SCALE = 4.0f;
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.85;

//===SlimeManager.cpp======
const int ENEMY_GENERATE_INTERVAL = 3 * 60;		// �����Ԋu
const int RANDOM_POS_MIN = -15;					// �������W�͈͉���(x,z����)
const int RANDOM_POS_MAX = 15;					// �������W�͈͏��(x,z����)
const int CREATE_DISTANCE = 10;					// ���������ŏ��l
const int SLIME_LEVEL1_PER = 50;                // �X���C��_1�̐����m��
const int SLIME_LEVEL2_PER = 30;                // �X���C��_2�̐����m��
const int SLIME_LEVEL3_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER;    // �X���C��_3�̐����m��
const float MAX_SIZE_EXPLODE = 5.0f;		// �X���C��4���m�̔����̑傫��
const float EXPLODE_BASE_RATIO = 1.0f;		// �X���C���̔����ڐG�ł̔����̑傫���̃x�[�X


#endif // !__GAME_PARAMETER_H__




