/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	2D�̃V�F�[�_�[�ɓn���萔�o�b�t�@���`
	------------------------------------
	Transform2d.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/07 ���� takagi
	�E2023/11/09 �ꕔ���Z�q���I�[�o�[���[�h takagi
	�E2023/11/16 �g�p���Ȃ��w�b�_�t�@�C�����폜 takagi

========================================== */

#ifndef __TRANSFORM_2D_H__	//Transform2d.h�C���N���[�h�K�[�h
#define __TRANSFORM_2D_H__

// =============== �C���N���[�h ===================
#include <math.h>		//�v�Z�֐�
#include "Pos2d.h"		//�����o�̃w�b�_
#include "DiType.h"		//�����o�̃w�b�_

// =============== �N���X��` ===================
struct tagTransform2d	//2D�̒萔�o�b�t�@�Ɋւ����
{
public:
	// ===�����o�ϐ��錾===
	TPos2d<float> fPos;		//�ʒu
	TDiType<float> fScale;	//�g�k
	float fRadian;			//�p

	// ===�����o�֐��錾===
	tagTransform2d();											//�R���X�g���N�^
	tagTransform2d(const TPos2d<float>& fPos, const TDiType<float>& fScale,
		const float& fRadian);									//�����t���R���X�g���N�^
	tagTransform2d(const tagTransform2d& Obj);					//�R�s�[�R���X�g���N�^
	~tagTransform2d();											//�f�X�g���N�^
	tagTransform2d& operator=(const tagTransform2d& Obj);		//"="���Z�q�̃I�[�o�[���[�h
	tagTransform2d operator+(const tagTransform2d& Obj) const;	//"+"���Z�q�̃I�[�o�[���[�h
	tagTransform2d& operator+=(const tagTransform2d& Obj);		//"+="���Z�q�̃I�[�o�[���[�h
	tagTransform2d operator-(const tagTransform2d& Obj) const;	//"-"���Z�q�̃I�[�o�[���[�h
	tagTransform2d& operator-=(const tagTransform2d& Obj);		//"-="���Z�q�̃I�[�o�[���[�h
	tagTransform2d operator*(const tagTransform2d& Obj) const;	//"*"���Z�q�̃I�[�o�[���[�h
	tagTransform2d& operator*=(const tagTransform2d& Obj);		//"*="���Z�q�̃I�[�o�[���[�h
	tagTransform2d operator/(const tagTransform2d& Obj) const;	//"/"���Z�q�̃I�[�o�[���[�h
	tagTransform2d& operator/=(const tagTransform2d& Obj);		//"/="���Z�q�̃I�[�o�[���[�h
};	//�^�e���v���[�g

#endif //!__TRANSFORM_2D_H__