/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	衝突判定定義
	---------------------------------------
	Collision.h
	---------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/05 作成 yamashita
	・2023/11/14 CheckCollisionSphere関数の引数追加 takagi
	・2024/01/19 リネーム・関数静的化 takagi
	・2024/01/21 コメント改修 takagi

======================================== */

#ifndef __COLLISION_H__	//Collision.hインクルードガード
#define __COLLISION_H__

// =============== インクルード ===================
#include "SphereInfo.h"	//ヒットボックス(球)

// =============== クラス定義 =====================
class CCollision
{
public:
	// ===プロトタイプ宣言===
	CCollision();																														//コンストラクタ
	~CCollision();																														//デストラクタ
	static bool CheckCollisionSphere(tagSphereInfo HitObj, tagSphereInfo NoMoveObj, TPos3d<float> fHitPos, TPos3d<float> fNoMovePos);	//球どうしの当たり判定
};	//衝突判定

#endif	//!__COLLISION_H__
