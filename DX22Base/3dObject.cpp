/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	3Dオブジェクト実装
	------------------------------------
	3dObject.cpp
	------------------------------------
	作成者	yamamoto

	変更履歴
	・2023/11/14 作成　yamamoto
	・2024/01/16 リネーム、継承 takagi
	・2024/01/18 続き及びリファクタリング takagi
	・2024/01/20 GetPos()関数を親に移動 takagi
	・2024/01/21 コメント改修・汎化作業 takagi

========================================== */

// =============== インクルード ===================
#include "3dObject.h"	//自身のヘッダ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
C3dObject::C3dObject()
	:m_Sphere(INIT_RADIUS, INIT_SHIFT)	//ヒットボックス
{
}

/* ========================================
	コピーコンストラクタ関数
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const C3dObject & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
C3dObject::C3dObject(const C3dObject & Obj)
	:m_Sphere(Obj.m_Sphere)	//ヒットボックス
{
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
C3dObject::~C3dObject()
{
}

/* ========================================
	ワールド座標ゲッタ関数
	-------------------------------------
	内容：自身のワールド座標位置を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：自身のワールド座標位置
=========================================== */
tagTransform3d C3dObject::GetTransform() const
{
	// =============== 提供 ===================
	return m_Transform;	//ワールド座標
}

/* ========================================
	回転ゲッタ関数
	-------------------------------------
	内容：自身の回転角を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：自身の回転角
=========================================== */
TTriType<float> C3dObject::GetRotate() const
{
	// =============== 提供 ===================
	return m_Transform.fRadian;	//回転
}

/* ========================================
	拡縮率ゲッタ関数
	-------------------------------------
	内容：自身の拡縮率を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：自身の拡縮率
=========================================== */
TTriType<float> C3dObject::GetScale() const
{
	// =============== 提供 ===================
	return m_Transform.fScale;	//拡縮率
}

/* ========================================
	ヒットボックスゲッタ関数
	-------------------------------------
	内容：自身のヒットボックスを提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：自身の球状ヒットボックス
=========================================== */
tagSphereInfo C3dObject::GetSphere() const
{
	// =============== 提供 ===================
	return m_Sphere;	//ヒットボックス
}

/* ========================================
	半径ゲッタ関数
	-------------------------------------
	内容：自身の半径を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：自身の半径
=========================================== */
float C3dObject::GetRadius() const
{
	// =============== 提供 ===================
	return m_Sphere.fRadius;	//半径
}

/* ========================================
	位置ずれゲッタ関数
	-------------------------------------
	内容：自身の位置ずれを提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：自身の位置ずれ
=========================================== */
TPos3d<float> C3dObject::GetShift() const
{
	// =============== 提供 ===================
	return m_Sphere.fShift;	//位置ずれ
}

/* ========================================
	ヒットボックスセット関数
	-------------------------------------
	内容：ヒットボックス登録
	-------------------------------------
	引数1：const tagSphereInfo& Sphere：球状ヒットボックス
	-------------------------------------
	戻値：なし
=========================================== */
void C3dObject::SetSphere(const tagSphereInfo& Sphere)
{
	// =============== 格納 ===================
	m_Sphere = Sphere;	//ヒットボックス格納
}

/* ========================================
	当たり判定半径セット関数
	-------------------------------------
	内容：当たり判定の球の半径をセットする
	-------------------------------------
	引数1：const float& Radius：球の半径
	-------------------------------------
	戻値：なし
=========================================== */
void C3dObject::SetRadius(const float& Radius)
{
	// =============== 格納 ===================
	m_Sphere.fRadius = Radius;	//半径格納
}

/* ========================================
	当たり判定位置ずれセット関数
	-------------------------------------
	内容：当たり判定の位置ずれをセットする
	-------------------------------------
	引数1：const TPos3d<float>& Shift：球の位置ずれ
	-------------------------------------
	戻値：なし
=========================================== */
void C3dObject::SetShift(const TPos3d<float>& Shift)
{
	// =============== 格納 ===================
	m_Sphere.fShift = Shift;	//位置ずれ格納
}