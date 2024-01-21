/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	オブジェクト定義
	------------------------------------
	Object.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/18 作成 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __OBJECT_H__	//Object.hインクルードガード
#define __OBJECT_H__

// =============== インクルード ===================
#include "Transform3d.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CObject
{
private:
	// ===定数定義===========
	const TPos3d<float> INIT_POS = { 640.0f, 360.0f, 0.0f };	//初期位置
	const TTriType<float> INIT_SCALE = { 1.0f, 1.0f, 0.0f };	//初期拡縮
	const TTriType<float> INIT_RADIAN = 0.0f;					//初期回転
public:
	// ===プロトタイプ宣言===
	CObject();													//コンストラクタ
	CObject(const CObject& Obj);								//コピーコンストラクタ
	virtual ~CObject();											//デストラクタ
	virtual void Update() = 0;									//更新
	virtual void Draw() = 0;									//描画
	TPos3d<float> GetPos() const;								//位置ゲッタ
	const float& GetPosZ() const;								//Z座標ゲッタ
	virtual void SetPos(const TPos3d<float>& fPos);				//位置セッタ
	virtual void SetSize(const TTriType<float>& fScale);		//大きさセッタ
	virtual void SetRotate(const TTriType<float>& fRotate);		//回転セッタ
	virtual void SetTransform(const tagTransform3d& Transform);	//ワールド座標セッタ
protected:
	// ===メンバ変数宣言=====
	tagTransform3d m_Transform;	//ワールド座標
};	//オブジェクト

#endif	//!__OBJECT_H__