/* ========================================
HEW/UniBoooom!!
---------------------------------------
�Փ˔���p�w�b�_
---------------------------------------
Collision.h

�ύX����
�E2023/11/05 �ύX���e

======================================== */

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "SphereInfo.h"

// =============== �N���X��` =====================
class CCOLLISION
{
public:
	CCOLLISION() {};	//�R���X�g���N�^
	~CCOLLISION() {};	//�f�X�g���N�^

	bool CheckCollisionSphere(CSphereInfo::Sphere hitObj, CSphereInfo::Sphere noMoveObj);
private:

};

#endif // !__COLLISION_H__
