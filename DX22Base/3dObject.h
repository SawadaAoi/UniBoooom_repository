/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	3Dオブジェクト定義
	------------------------------------
	3dObject.h
	------------------------------------
	作成者	yamamoto

	変更履歴
	・2023/11/14 作成	yamamoto
	・2024/01/16 リネーム、継承 takagi
	・2024/01/18 続き及びリファクタリング takagi
	・2024/01/20 GetPos()関数を親に移動 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __3D_OBJECT_H__	//3dObject.hインクルードガード
#define __3D_OBJECT_H__

// =============== インクルード ===================
#include "Object.h"		//親のヘッダ
#include "SphereInfo.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class C3dObject	:public CObject	//オブジェクト継承
{
private:
	// ===定数定義===========
	const float INIT_RADIUS = 0.0f;				//初期半径
	const TPos3d<float> INIT_SHIFT = { 0.0f, 0.0f, 0.0f };	//初期位置ずれ値
public:
	// ===プロトタイプ宣言===
	C3dObject();									//コンストラクタ
	C3dObject(const C3dObject& Obj);				//コピーコンストラクタ
	~C3dObject();									//デストラクタ
	virtual void Update() = 0;						//更新
	virtual void Draw() = 0;						//描画
	tagTransform3d GetTransform() const;			//ワールド座標ゲッタ
	TTriType<float> GetRotate() const;				//回転ゲッタ
	TTriType<float> GetScale() const;				//拡縮ゲッタ
	tagSphereInfo GetSphere() const;				//ヒットボックスゲッタ
	float GetRadius() const;						//半径ゲッタ
	TPos3d<float> GetShift() const;					//位置ずれ値ゲッタ
	void SetSphere(const tagSphereInfo& Sphere);	//ヒットボックスセッタ
	void SetRadius(const float& Radius);			//半径セッタ
	void SetShift(const TPos3d<float>& Shift);		//位置ずれセッタ
protected:
	// ===メンバ変数宣言=====
	tagSphereInfo m_Sphere;		//当たり判定用の球体
};	//3Dオブジェクト

#endif	//!__3D_OBJECT_H__