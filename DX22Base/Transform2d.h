/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	2Dのシェーダーに渡す定数バッファを定義
	------------------------------------
	Transform2d.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/07 制作 takagi
	・2023/11/09 一部演算子をオーバーロード takagi
	・2023/11/16 使用しないヘッダファイルを削除 takagi

========================================== */

#ifndef __TRANSFORM_2D_H__	//Transform2d.hインクルードガード
#define __TRANSFORM_2D_H__

// =============== インクルード ===================
#include <math.h>		//計算関数
#include "Pos2d.h"		//メンバのヘッダ
#include "DiType.h"		//メンバのヘッダ

// =============== クラス定義 ===================
struct tagTransform2d	//2Dの定数バッファに関わる情報
{
public:
	// ===メンバ変数宣言===
	TPos2d<float> fPos;		//位置
	TDiType<float> fScale;	//拡縮
	float fRadian;			//角

	// ===メンバ関数宣言===
	tagTransform2d();											//コンストラクタ
	tagTransform2d(const TPos2d<float>& fPos, const TDiType<float>& fScale,
		const float& fRadian);									//引数付きコンストラクタ
	tagTransform2d(const tagTransform2d& Obj);					//コピーコンストラクタ
	~tagTransform2d();											//デストラクタ
	tagTransform2d& operator=(const tagTransform2d& Obj);		//"="演算子のオーバーロード
	tagTransform2d operator+(const tagTransform2d& Obj) const;	//"+"演算子のオーバーロード
	tagTransform2d& operator+=(const tagTransform2d& Obj);		//"+="演算子のオーバーロード
	tagTransform2d operator-(const tagTransform2d& Obj) const;	//"-"演算子のオーバーロード
	tagTransform2d& operator-=(const tagTransform2d& Obj);		//"-="演算子のオーバーロード
	tagTransform2d operator*(const tagTransform2d& Obj) const;	//"*"演算子のオーバーロード
	tagTransform2d& operator*=(const tagTransform2d& Obj);		//"*="演算子のオーバーロード
	tagTransform2d operator/(const tagTransform2d& Obj) const;	//"/"演算子のオーバーロード
	tagTransform2d& operator/=(const tagTransform2d& Obj);		//"/="演算子のオーバーロード
};	//型テンプレート

#endif //!__TRANSFORM_2D_H__