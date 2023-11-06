/* ========================================
HEW/UniBoooom!!
---------------------------------------
衝突判定用ヘッダ
---------------------------------------
Collision.h

変更履歴
・2023/11/05 変更内容

======================================== */

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "SphereInfo.h"

// =============== クラス定義 =====================
class CCOLLISION
{
public:
	CCOLLISION() {};	//コンストラクタ
	~CCOLLISION() {};	//デストラクタ

	bool CheckCollisionSphere(CSphereInfo::Sphere hitObj, CSphereInfo::Sphere noMoveObj);
private:

};

#endif // !__COLLISION_H__
