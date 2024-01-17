/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	オブジェクト用ヘッダ
	------------------------------------
	Object.h
	------------------------------------
	作成者
		山本凱翔

	変更履歴
	・2023/11/14 作成	yamamoto
	・2024/01/16 リネーム、継承 takagi

========================================== */

#ifndef __OBJECT_H__	//
#define __OBJECT_H__
// =============== インクルード ===================
#include "Obj.h"
#include "SphereInfo.h"

// =============== クラス定義 =====================
class CObject	:public CObj
{
public:
	// ===プロトタイプ宣言===
	CObject();//コンストラクタ
	~CObject();//デストラクタ
	
	// ゲット関数
	tagTransform3d GetTransform(); 
	TPos3d<float> GetPos();
	TTriType<float> GetRadian();
	TTriType<float> GetScale();
	tagSphereInfo GetSphere();
	float GetRadius();
	TPos3d<float> GetShift();

	//セット関数
	void SetTransform(tagTransform3d Transform);
	void SetPos(TPos3d<float> Pos);
	void SetRadian(TTriType<float> Radian);
	void SetScale(TTriType<float> Scale);
	void SetSphere(tagSphereInfo Sphere);
	void SetRadius(float Radius);
	void SetShift(TPos3d<float> Shift);

protected:
	// ===メンバ変数宣言=====
	tagSphereInfo m_Sphere;		//当たり判定用の球体
};

#endif //!__OBJECT_H__