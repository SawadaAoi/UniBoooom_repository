/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Փ˔����`
	---------------------------------------
	Collision.h
	---------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/05 �쐬 yamashita
	�E2023/11/14 CheckCollisionSphere�֐��̈����ǉ� takagi
	�E2024/01/19 ���l�[���E�֐��ÓI�� takagi
	�E2024/01/21 �R�����g���C takagi

======================================== */

#ifndef __COLLISION_H__	//Collision.h�C���N���[�h�K�[�h
#define __COLLISION_H__

// =============== �C���N���[�h ===================
#include "SphereInfo.h"	//�q�b�g�{�b�N�X(��)

// =============== �N���X��` =====================
class CCollision
{
public:
	// ===�v���g�^�C�v�錾===
	CCollision();																														//�R���X�g���N�^
	~CCollision();																														//�f�X�g���N�^
	static bool CheckCollisionSphere(tagSphereInfo HitObj, tagSphereInfo NoMoveObj, TPos3d<float> fHitPos, TPos3d<float> fNoMovePos);	//���ǂ����̓����蔻��
};	//�Փ˔���

#endif	//!__COLLISION_H__
