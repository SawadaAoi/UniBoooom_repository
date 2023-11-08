/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�V�F�[�_�[�ɓn���萔�o�b�t�@���`
	------------------------------------
	Transform2d.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/10/26 ���� takagi
	�E2023/10/31 �p���ɑΉ��E�R�����g�C���E�ׂ���ǉ� takagi
	�E2023/11/02 �ׂ��������Z�q�ǉ��Epow�̒��g�𖾎��I�Ɍ^�L���X�g�E�ׂ���̈�����double��float
					�E������const�s���������E���x(����������)�ӎ��ň������Q�ƕ����ɕύX�E�R�����g�C�� takagi
	�E2023/11/03 %���Z�q�g�p���ɁA�v�Z�Ɏg�p����l�������^�łȂ����Ƃ���������C���ETotal()�֐���ǉ� takagi
	�E2023/11/04 .cpp/.h�������������� takagi
	�E2023/11/07 �R�[�f�B���O�K��K�p takagi

========================================== */

#ifndef __TRANSFORM_2D_H__
#define __TRANSFORM_2D_H__

// =============== �C���N���[�h ===================
#include <math.h>		//�v�Z�֐�
#include "Transform.h"	//�e�̃w�b�_
#include "Pos2d.h"		//�����o�̃w�b�_
#include "DiType.h"		//�����o�̃w�b�_

// =============== �N���X��` ===================
struct CTransform2d	//���[���h�s��Ɋւ����
{
public:
	// ===�����o�ϐ��錾===
	TPos2d<float> m_fPos;		//�ʒu
	TDiType<float> m_fScale;	//�g�k
	float m_fRadian;			//�p

	// ===�����o�֐��錾===
	//CTransform2d();		//�R���X�g���N�^
	//~CTransform2d();	//�f�X�g���N�^
};	//�^�e���v���[�g

#endif //!__TRANSFORM_2D_H__