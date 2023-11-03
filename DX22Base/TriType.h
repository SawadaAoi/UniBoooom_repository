//TriType.h
//同じ型を３つ持つテンプレートクラスを定義

//＞更新履歴
//2023/10/26	制作
//2023/10/31	継承に対応・コメント修正・べき乗追加
//2023/11/02	べき乗代入演算子追加・powの中身を明示的に型キャスト・べき乗の引数をdouble→float
				//・引数のconst不足を解消・速度(メモリ効率)意識で引数を参照方式に変更・コメント修正
//2023/11/03	%演算子使用時に、計算に使用する値が整数型でないことがある問題を修正・Total()関数を追加
//2023/11/04	.cpp/.h分け



//＞インクルードガード
#ifndef ___TRI_TYPE_H___
#define ___TRI_TYPE_H___

//＞インクルード部
#include <math.h>	//計算関数

//＞テンプレートクラス定義
template<class TriType>
class TTriType	//テンプレートクラス：同じ型の変数３つ
{
public:
	//＞変数宣言
	TriType x;	//１つめの変数
	TriType y;	//２つめの変数
	TriType z;	//３つめの変数
	//＞プロトタイプ宣言
	TTriType();														//コンストラクタ
	TTriType(const TriType& x, const TriType& y, const TriType& z);	//引数付きコンストラクタ
	TTriType(const TTriType& Obj);									//コピーコンストラクタ
	virtual ~TTriType();											//デストラクタ
	virtual TriType Total();										//総計
	virtual TTriType& operator=(const TTriType& Obj);				//"="演算子のオーバーロード
	virtual TTriType operator+(const TTriType& Obj);				//"+"演算子のオーバーロード
	virtual TTriType& operator+=(const TTriType& Obj);				//"+="演算子のオーバーロード
	virtual TTriType operator-(const TTriType& Obj);				//"-"演算子のオーバーロード
	virtual TTriType& operator-=(const TTriType& Obj);				//"-="演算子のオーバーロード
	virtual TTriType operator*(const TTriType& Obj);				//"*"演算子のオーバーロード
	virtual TTriType& operator*=(const TTriType& Obj);				//"*="演算子のオーバーロード
	virtual TTriType operator/(const TTriType& Obj);				//"/"演算子のオーバーロード
	virtual TTriType& operator/=(const TTriType& Obj);				//"/="演算子のオーバーロード
	virtual TTriType operator%(const TTriType& Obj);				//"%"演算子のオーバーロード
	virtual TTriType& operator%=(const TTriType& Obj);				//"%="演算子のオーバーロード
	virtual TTriType operator^(const double& dIndex);				//"^"演算子のオーバーロード
	virtual TTriType& operator^=(const double& dIndex);				//"^="演算子のオーバーロード
};	//型テンプレート

#endif // !___TRI_TYPE_H___