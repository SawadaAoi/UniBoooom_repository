// CPP�p�@----------------------------------------------------
/* ========================================
HEW/UniBoooom!!
---------------------------------------
�Փ˔���pcpp
---------------------------------------
Collision.cpp

�ύX����
�E2023/11/05 �ύX���e

======================================== */

#include "Collision.h"


bool CCOLLISION::CheckCollisionSphere(CSphereInfo::Sphere hitObj, CSphereInfo::Sphere noMoveObj)
{
	float Distance = hitObj.Distance(noMoveObj);

	if (Distance < hitObj.radius + noMoveObj.radius)
	{
		return true;
	}

	return false;
}