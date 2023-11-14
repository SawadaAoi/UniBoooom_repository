/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Փ˔���p�w�b�_
	---------------------------------------
	Collision.h

	�ύX����
	�E2023/11/05 �쐬
	�E2023/11/14 CheckCollisionSphere�֐��̈����ǉ� takagi

======================================== */

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "SphereInfo.h"

// =============== �N���X��` =====================
class CCOLLISION
{
public:
	// ===�v���g�^�C�v�錾===
	CCOLLISION() {};	//�R���X�g���N�^
	~CCOLLISION() {};	//�f�X�g���N�^

	bool CheckCollisionSphere(tagSphereInfo HitObj, tagSphereInfo NoMoveObj, TPos3d<float> fHitPos, TPos3d<float> fNoMovePos);	//���ǂ����̓����蔻��
};

#endif // !__COLLISION_H__
