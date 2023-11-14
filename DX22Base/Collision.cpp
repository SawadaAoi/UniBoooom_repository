/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	衝突判定用cpp
	---------------------------------------
	Collision.cpp

	変更履歴
	・2023/11/05 変更内容
	・2023/11/14 CheckCollisionSphere関数の引数追加 takagi

======================================== */

// =============== インクルード ===================
#include "Collision.h"	// 自身のヘッダ

/* ========================================
	球体衝突判定関数
	-------------------------------------
	内容：球体の衝突判定
	-------------------------------------
	引数1：当たりに行く側の球体の情報（構造体）
	-------------------------------------
	引数2：当たられる側の球体の情報（構造体）
	-------------------------------------
	引数1：当たりに行く側の表示位置
	-------------------------------------
	引数2：当たられる側の表示位置
	-------------------------------------
	戻値：true または false
=========================================== */
bool CCOLLISION::CheckCollisionSphere(tagSphereInfo HitObj, tagSphereInfo NoMoveObj, TPos3d<float> fHitPos, TPos3d<float> fNoMovePos)
{
	TPos3d<float> HitCol = HitObj.GetCollisionPos(fHitPos);				//当たりに行く側の当たり判定位置
	TPos3d<float> NoMoveCol = NoMoveObj.GetCollisionPos(fNoMovePos);	//当たられる側の当たり判定位置

	float Distance = HitCol.Distance(NoMoveCol);	// オブジェクト間の距離

	if (Distance < HitObj.fRadius + NoMoveObj.fRadius)	// オブジェクト間の距離の距離が半径の合計より小さくなったら
	{
		return true;	// 衝突している
	}

	return false;	// それ以外は衝突していない
}