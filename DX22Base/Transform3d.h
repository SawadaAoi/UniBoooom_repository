/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ワールド行列を定義
	------------------------------------
	Transform3d.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/10/26 制作 takagi
	・2023/10/31 継承に対応・コメント修正・べき乗追加 takagi
	・2023/11/02 べき乗代入演算子追加・powの中身を明示的に型キャスト・べき乗の引数をdouble→float
					・引数のconst不足を解消・速度(メモリ効率)意識で引数を参照方式に変更・コメント修正 takagi
	・2023/11/03 %演算子使用時に、計算に使用する値が整数型でないことがある問題を修正・Total()関数を追加 takagi
	・2023/11/04 .cpp/.h分け→分割解除 takagi
	・2023/11/07 コーディング規約適用 takagi
	・2023/11/08 行列変換関数追加 takagi

========================================== */

#ifndef __TRANSFORM_3D_H__
#define __TRANSFORM_3D_H__

// =============== インクルード ===================
#include "Pos3d.h"			//メンバのヘッダ
#include "TriType.h"		//メンバのヘッダ
#include <DirectXMath.h>	//マトリックス型使用

// =============== 構造体定義 ===================
struct tagTransform3d	//ワールド行列に関わる情報
{
public:
	// ===メンバ変数宣言===
	TPos3d<float> fPos;			//位置
	TTriType<float> fScale;		//拡縮率
	TTriType<float> fRadian;	//回転角

	// ===メンバ関数宣言===
	tagTransform3d();										//コンストラクタ
	tagTransform3d(const TPos3d<float>& fPos, const TTriType<float>& fScale,
		const TTriType<float>& fRadian);					//引数付きコンストラクタ
	tagTransform3d(const tagTransform3d& Obj);				//コピーコンストラクタ
	~tagTransform3d();										//デストラクタ
	DirectX::XMFLOAT4X4 GetWorldMatrixTRS();				//ワールド行列(TRS変換)
	DirectX::XMFLOAT4X4 GetWorldMatrixSRT();				//ワールド行列(SRT変換)
	//tagTransform3d& operator=(const tagTransform3d& Obj);	//"="演算子のオーバーロード
	//tagTransform3d operator+(const tagTransform3d& Obj);	//"+"演算子のオーバーロード
	//tagTransform3d& operator+=(const tagTransform3d& Obj);	//"+="演算子のオーバーロード
	//tagTransform3d operator-(const tagTransform3d& Obj);	//"-"演算子のオーバーロード
	//tagTransform3d& operator-=(const tagTransform3d& Obj);	//"-="演算子のオーバーロード
	//tagTransform3d operator*(const tagTransform3d& Obj);	//"*"演算子のオーバーロード
	//tagTransform3d& operator*=(const tagTransform3d& Obj);	//"*="演算子のオーバーロード
	//tagTransform3d operator/(const tagTransform3d& Obj);	//"/"演算子のオーバーロード
	//tagTransform3d& operator/=(const tagTransform3d& Obj);	//"/="演算子のオーバーロード
};	//型テンプレート

#endif //!__TRANSFORM_3D_H__