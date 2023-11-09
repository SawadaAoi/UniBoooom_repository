/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	同じ型を２つ持つテンプレートクラスを定義
	------------------------------------
	DiType.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/07 Triからコピペ→改修 takagi
	・2023/11/08 一部関数にconst修飾子付与 takagi
	・2023/11/09 コメント揃え takagi

========================================== */

#ifndef ___DI_TYPE_H___
#define ___DI_TYPE_H___

// =============== インクルード ===================
#include <math.h>	//計算関数

// =============== テンプレートクラス定義 ===================
template<class DiType>
struct TDiType	//テンプレートクラス：同じ型の変数２つ
{
public:
	// ===メンバ変数宣言===
	DiType x;	//１つめの変数
	DiType y;	//２つめの変数

	// ===メンバ関数宣言===
	TDiType();												//コンストラクタ
	TDiType(const DiType& x, const DiType& y);				//引数付きコンストラクタ
	TDiType(const TDiType& Obj);							//コピーコンストラクタ
	virtual ~TDiType();										//デストラクタ
	virtual DiType Total() const;							//総計
	virtual TDiType& operator=(const TDiType& Obj);			//"="演算子のオーバーロード
	virtual TDiType operator+(const TDiType& Obj) const;	//"+"演算子のオーバーロード
	virtual TDiType& operator+=(const TDiType& Obj);		//"+="演算子のオーバーロード
	virtual TDiType operator-(const TDiType& Obj) const;	//"-"演算子のオーバーロード
	virtual TDiType& operator-=(const TDiType& Obj);		//"-="演算子のオーバーロード
	virtual TDiType operator*(const TDiType& Obj) const;	//"*"演算子のオーバーロード
	virtual TDiType& operator*=(const TDiType& Obj);		//"*="演算子のオーバーロード
	virtual TDiType operator/(const TDiType& Obj) const;	//"/"演算子のオーバーロード
	virtual TDiType& operator/=(const TDiType& Obj);		//"/="演算子のオーバーロード
	virtual TDiType operator%(const TDiType& Obj) const;	//"%"演算子のオーバーロード
	virtual TDiType& operator%=(const TDiType& Obj);		//"%="演算子のオーバーロード
	virtual TDiType operator^(const double& dIndex) const;	//"^"演算子のオーバーロード
	virtual TDiType& operator^=(const double& dIndex);		//"^="演算子のオーバーロード
};	//型テンプレート

/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType>::TDiType()
	:TDiType((DiType)0, (DiType)0)	//委譲
{
}

/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：const DiType & x：１つめの値の参照
	引数2：const DiType & y：２つめの値の参照
	-------------------------------------
	戻値：なし
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType>::TDiType(const DiType & x, const DiType & y)
{
	// =============== 初期化 ===================
	this->x = x;	//１つめ初期化
	this->y = y;	//２つめ初期化
}

/* ========================================
	コピーコンストラクタ
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const TDiType & Obj：複製するデータ元の参照
	-------------------------------------
	戻値：なし
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType>::TDiType(const TDiType & Obj)
{
	// =============== 複製 ===================
	this->x = Obj.x;	//１つめのデータコピー
	this->y = Obj.y;	//２つめのデータコピー
}

/* ========================================
	デストラクタ
	------------------------------------ -
	内容：破棄時に行う処理
	------------------------------------ -
	引数1：なし
	------------------------------------ -
	戻値：なし
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType>::~TDiType()
{
}

/* ========================================
	総計関数
	------------------------------------ -
	内容：自身の持つ２つのメンバー変数を合計する
	------------------------------------ -
	引数1：なし
	------------------------------------ -
	戻値：２つのメンバー変数の合計値
=========================================== */
template<class DiType>	//テンプレート関数実装
DiType TDiType<DiType>::Total() const
{
	// =============== 提供 ===================
	return (this->x + this->y);	//加算結果
}

/* ========================================
	代入演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに代入処理を行う
	------------------------------------ -
	引数1：const TDiType & Obj：代入する値の参照
	------------------------------------ -
	戻値：代入が行われた自分自身
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType>& TDiType<DiType>::operator=(const TDiType & Obj)
{
	// =============== 複製 ===================
	this->x = Obj.x;	//１つめのデータコピー
	this->y = Obj.y;	//２つめのデータコピー

	// =============== 提供 ===================
	return	*this;	//自身の参照
}

/* ========================================
	加算演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに加算処理を行う
	------------------------------------ -
	引数1：const TDiType & Obj：加算する値の参照
	------------------------------------ -
	戻値：自身と引数の加算結果
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> TDiType<DiType>::operator+(const TDiType & Obj) const
{
	// =============== 提供 ===================
	return { this->x + Obj.x, this->y + Obj.y };	//加算結果
}

/* ========================================
	加算代入演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに加算処理を行ったものを代入する
	------------------------------------ -
	引数1：const TDiType & Obj：加算する値の参照
	------------------------------------ -
	戻値：引数が加算された自分自身
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> & TDiType<DiType>::operator+=(const TDiType & Obj)
{
	// =============== 提供 ===================
	return (*this = *this + Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/* ========================================
	減算演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに減算処理を行う
	------------------------------------ -
	引数1：const TDiType & Obj：減算する値の参照
	------------------------------------ -
	戻値：自身 - 引数の結果
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> TDiType<DiType>::operator-(const TDiType & Obj) const
{
	// =============== 提供 ===================
	return { this->x - Obj.x, this->y - Obj.y };	//減算結果
}

/* ========================================
	減算代入演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに減算処理を行ったものを代入する
	------------------------------------ -
	引数1：const TDiType & Obj：減算する値の参照
	------------------------------------ -
	戻値：引数が減算された自分自身
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> & TDiType<DiType>::operator-=(const TDiType & Obj)
{
	// =============== 提供 ===================
	return (*this = *this - Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/* ========================================
	乗算演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに乗算処理を行う
	------------------------------------ -
	引数1：const TDiType & Obj：乗算する値の参照
	------------------------------------ -
	戻値：自身と引数の乗算結果
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> TDiType<DiType>::operator*(const TDiType & Obj) const
{
	// =============== 提供 ===================
	return { this->x * Obj.x, this->y * Obj.y };	//乗算結果
}

/* ========================================
	乗算代入演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに乗算処理を行ったものを代入する
	------------------------------------ -
	引数1：const TDiType & Obj：乗算する値の参照
	------------------------------------ -
	戻値：引数が乗算された自分自身
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> & TDiType<DiType>::operator*=(const TDiType & Obj)
{
	// =============== 提供 ===================
	return (*this = *this * Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/* ========================================
	除算演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに除算処理を行う
	------------------------------------ -
	引数1：const TDiType & Obj：除算する値の参照
	------------------------------------ -
	戻値：自身 / 引数の結果
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> TDiType<DiType>::operator/(const TDiType & Obj) const
{
	// =============== 提供 ===================
	return { this->x / Obj.x, this->y / Obj.y };	//除算結果
}

/* ========================================
	除算代入演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに除算処理を行ったものを代入する
	------------------------------------ -
	引数1：const TDiType & Obj：除算する値の参照
	------------------------------------ -
	戻値：引数が除算された自分自身
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> & TDiType<DiType>::operator/=(const TDiType & Obj)
{
	// =============== 提供 ===================
	return (*this = *this / Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/* ========================================
	剰余演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに剰余演算処理を行う
	------------------------------------ -
	引数1：const TDiType & Obj：剰余演算する値の参照
	------------------------------------ -
	戻値：自身と引数の剰余演算結果
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> TDiType<DiType>::operator%(const TDiType & Obj) const
{
	// =============== 提供 ===================
	return { static_cast<DiType>(static_cast<int>(this->x) % static_cast<int>(Obj.x)), static_cast<DiType>((int)this->y % (int)Obj.y) };	//剰余演算結果
}

/* ========================================
	剰余代入演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれに剰余演算処理を行ったものを代入する
	------------------------------------ -
	引数1：const TDiType & Obj：剰余演算する値の参照
	------------------------------------ -
	戻値：引数で剰余演算された自分自身
=========================================== */
/////
template<class DiType>	//テンプレート関数実装
TDiType<DiType> & TDiType<DiType>::operator%=(const TDiType & Obj)
{
	// =============== 提供 ===================
	return (*this = *this % Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/* ========================================
	べき乗演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれにべき乗処理を行う
	------------------------------------ -
	引数1：const double & dIndex：指数の参照
	------------------------------------ -
	戻値：自身を引数でべき乗した演算結果
=========================================== */
template<class DiType>	//テンプレート関数実装
TDiType<DiType> TDiType<DiType>::operator^(const double & dIndex) const
{
	// =============== 提供 ===================
	return { (DiType)pow((double)this->x, dIndex), (DiType)pow((double)this->y, dIndex) };	//べき乗演算結果
}

/* ========================================
	べき乗代入演算子
	------------------------------------ -
	内容：独立した２つのメンバー変数に対してそれぞれにべき乗処理を行ったものを代入する
	------------------------------------ -
	引数1：const double & dIndex：指数の参照
	------------------------------------ -
	戻値：引数がべき乗された自分自身
=========================================== */
template<class DiType>
TDiType<DiType> & TDiType<DiType>::operator^=(const double & dIndex)
{
	// =============== 提供 ===================
	return (*this = *this ^ dIndex);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

#endif // !___DI_TYPE_H___




//--- ここから下は試運転(cppにかかないと動かないので、試したい場合このヘッダをallコピーしてcppに貼り付けてください) ---//
	//！： 既存のmain関数がある場合は別プロジェクトで試すか、一時的にコメントアウトしてください。
//#include <iostream>
//#include <string>
//
//int main()
//{
//	TDiType<int> a;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//0,0のハズ
//
//	a = TDiType<int>(1, 1);
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;
//
//	a = { 2, 2 };
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;
//
//	a.x = 3;
//	a.y = 3;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;
//
//	TDiType<int> b(4, 4);
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;
//
//	a + b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//3,3のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;	//4,4のハズ
//
//	a = b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//4,4のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;	//4,4のハズ
//
//	a += b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << std::endl;	//8,8のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << std::endl;	//4,4のハズ
//	std::cin.get();
//
//
//	return 0;
//}