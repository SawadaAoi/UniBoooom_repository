// CPP用　----------------------------------------------------
/* ========================================
HEW/UniBoooom!!
---------------------------------------
衝突判定用cpp
---------------------------------------
Collision.cpp

変更履歴
・2023/11/05 変更内容

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