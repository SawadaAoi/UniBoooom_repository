/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���[���h�s����Q��`
	------------------------------------
	Transform3d.h
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
	�E2023/11/08 �s��ϊ��֐��ǉ� takagi
	�E2023/11/09 �ꕔ���C�� takagi
	�E2023/11/14 �p�x���Z takagi
	�E2023/12/05 �r���{�[�h�ɑΉ� takagi
	�E2023/12/17 �����Q�Ɖ� takagi

========================================== */

#ifndef __TRANSFORM_3D_H__	//Transform3d.h�C���N���[�h�K�[�h
#define __TRANSFORM_3D_H__

// =============== �C���N���[�h ===================
#include "Pos3d.h"			//�����o�̃w�b�_
#include "TriType.h"		//�����o�̃w�b�_
#include <DirectXMath.h>	//�}�g���b�N�X�^�g�p

// =============== �\���̒�` ===================
struct tagTransform3d	//���[���h�s��Ɋւ����
{
public:
	// ===�����o�ϐ��錾===
	TPos3d<float> fPos;			// �ʒu
	TTriType<float> fScale;		// �g�k��
	TTriType<float> fRadian;	// ��]�p

	// ===�����o�֐��錾===
	tagTransform3d();										//�R���X�g���N�^
	tagTransform3d(const TPos3d<float>& fPos, const TTriType<float>& fScale,
		const TTriType<float>& fRadian);					//�����t���R���X�g���N�^
	tagTransform3d(const tagTransform3d& Obj);				//�R�s�[�R���X�g���N�^
	~tagTransform3d();										//�f�X�g���N�^
	DirectX::XMFLOAT4X4 GetWorldMatrixTRS(const DirectX::XMMATRIX& Inverse
		= DirectX::XMMatrixIdentity());						//���[���h�s��(TRS�ϊ�)
	DirectX::XMFLOAT4X4 GetWorldMatrixSRT(const DirectX::XMMATRIX& Inverse
		= DirectX::XMMatrixIdentity());						//���[���h�s��(SRT�ϊ�)
	float Angle(const tagTransform3d& Obj);					//�p�x���Z
	tagTransform3d& operator=(const tagTransform3d& Obj);	//"="���Z�q�̃I�[�o�[���[�h
	tagTransform3d operator+(const tagTransform3d& Obj);	//"+"���Z�q�̃I�[�o�[���[�h
	tagTransform3d& operator+=(const tagTransform3d& Obj);	//"+="���Z�q�̃I�[�o�[���[�h
	tagTransform3d operator-(const tagTransform3d& Obj);	//"-"���Z�q�̃I�[�o�[���[�h
	tagTransform3d& operator-=(const tagTransform3d& Obj);	//"-="���Z�q�̃I�[�o�[���[�h
	tagTransform3d operator*(const tagTransform3d& Obj);	//"*"���Z�q�̃I�[�o�[���[�h
	tagTransform3d& operator*=(const tagTransform3d& Obj);	//"*="���Z�q�̃I�[�o�[���[�h
	tagTransform3d operator/(const tagTransform3d& Obj);	//"/"���Z�q�̃I�[�o�[���[�h
	tagTransform3d& operator/=(const tagTransform3d& Obj);	//"/="���Z�q�̃I�[�o�[���[�h
};	//�^�e���v���[�g

#endif //!__TRANSFORM_3D_H__