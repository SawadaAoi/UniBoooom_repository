/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Define�p�w�b�_
	------------------------------------
	Defines.h
	------------------------------------
	�쐬�ҁ@���X�ؐ搶
		
	�ύX����
	�E2024/01/20 �R�����g���C takagi
	
========================================== */

#ifndef __DEFINES_H__	//Defines.h�C���N���[�h�K�[�h
#define __DEFINES_H__

// =============== �C���N���[�h ===================
#include <assert.h>		//�v���O�����ُ�I���p�}�N����`
#include <Windows.h>	//�E�B���h�E����p
#include <stdarg.h>		//�ϒ������̊֐��쐬�p
#include <stdio.h>		//���o�͗p

// =============== �萔�E�}�N����` ===================
#define ASSET(path)	"Assets/"path	//���\�[�X�p�X(�����̕����񌋍�)
#define APP_TITLE "UniBoooom!!"		//�^�C�g����
#define SCREEN_WIDTH (1280)			//��ʃT�C�Y(��)
#define SCREEN_HEIGHT (720)			//��ʃT�C�Y(�c)
#define DEBUG_GRID_NUM (10)			//�O���b�h���S����[�܂ł̐��̐�
#define DEBUG_GRID_MARGIN (1.0f)	//�O���b�h�z�u��(���[�g�����Z)

#endif //!__DEFINES_H__