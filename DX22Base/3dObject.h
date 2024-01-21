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
	・2024/01/21 コメント改修・汎化作業 takagi

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
	const float INIT_RADIUS = 0.0f;							//初期半径
	const TPos3d<float> INIT_SHIFT = { 0.0f, 0.0f, 0.0f };	//初期位置ずれ値
public:
	// ===プロトタイプ宣言===
	C3dObject();												//コンストラクタ
	C3dObject(const C3dObject& Obj);							//コピーコンストラクタ
	virtual ~C3dObject();										//デストラクタ
	virtual tagTransform3d GetTransform() const final;			//ワールド座標ゲッタ
	virtual TTriType<float> GetRotate() const final;			//回転ゲッタ
	virtual TTriType<float> GetScale() const final;				//拡縮ゲッタ
	virtual tagSphereInfo GetSphere() const final;				//ヒットボックスゲッタ
	virtual float GetRadius() const final;						//半径ゲッタ
	virtual TPos3d<float> GetShift() const final;				//位置ずれ値ゲッタ
	virtual void SetSphere(const tagSphereInfo& Sphere) final;	//ヒットボックスセッタ
	virtual void SetRadius(const float& Radius) final;			//半径セッタ
	virtual void SetShift(const TPos3d<float>& Shift) final;	//位置ずれセッタ
protected:
	// ===メンバ変数宣言=====
	tagSphereInfo m_Sphere;		//当たり判定用の球体
};	//3Dオブジェクト

#endif	//!__3D_OBJECT_H__