/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	衝突判定用ヘッダ
	---------------------------------------
	Collision.h

	変更履歴
	・2023/11/05 作成
	・2023/11/14 CheckCollisionSphere関数の引数追加 takagi

======================================== */

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "SphereInfo.h"

// =============== クラス定義 =====================
class CCOLLISION
{
public:
	// ===プロトタイプ宣言===
	CCOLLISION() {};	//コンストラクタ
	~CCOLLISION() {};	//デストラクタ

	bool CheckCollisionSphere(tagSphereInfo HitObj, tagSphereInfo NoMoveObj, TPos3d<float> fHitPos, TPos3d<float> fNoMovePos);	//球どうしの当たり判定
};

#endif // !__COLLISION_H__
