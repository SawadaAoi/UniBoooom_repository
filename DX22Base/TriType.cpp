//TriType.cpp
//同じ型を３つ持つテンプレートクラスを実装

//＞更新履歴
//2023/10/26	制作
//2023/10/31	継承に対応・コメント修正・べき乗追加
//2023/11/02	べき乗代入演算子追加・powの中身を明示的に型キャスト・べき乗の引数をdouble→float
				//・引数のconst不足を解消・速度(メモリ効率)意識で引数を参照方式に変更・コメント修正
//2023/11/03	%演算子使用時に、計算に使用する値が整数型でないことがある問題を修正・Total()関数を追加
//2023/11/04	.cpp/.h分け



//＞インクルード部
#include "TriType.h"	//自身のヘッダ

/////
//＞コンストラクタ
//引数：なし
//戻り値：なし
//概要：生成時に行う処理
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType>::TTriType()
	:TTriType((TriType)0, (TriType)0, (TriType)0)	//委譲
{
}

/////
//＞コンストラクタ
//引数１：const TriType & x：１つめの値の参照
//引数２：const TriType & y：２つめの値の参照
//引数３：const TriType & z：３つめの値の参照
//戻り値：なし
//概要：生成時に行う処理
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType>::TTriType(const TriType & x, const TriType & y, const TriType & z)
{
	//＞初期化
	this->x = x;	//１つめ初期化
	this->y = y;	//２つめ初期化
	this->z = z;	//３つめ初期化
}

/////
//＞コピーコンストラクタ
//引数：const TTriType & Obj：複製するデータ元の参照
//戻り値：なし
//概要：コピー時に行う処理
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType>::TTriType(const TTriType & Obj)
{
	//＞複製
	this->x = Obj.x;	//１つめのデータコピー
	this->y = Obj.y;	//２つめのデータコピー
	this->z = Obj.z;	//３つめのデータコピー
}

/////
//＞デストラクタ
//引数：なし
//戻り値：なし
//概要：破棄時に行う処理
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType>::~TTriType()
{
}

/////
//＞総計関数
//引数：なし
//戻り値：３つのメンバー変数の合計値
//概要：自身の持つ３つのメンバー変数を合計する
/////
template<class TriType>	//テンプレート関数実装
TriType TTriType<TriType>::Total()
{
	//＞提供
	return (this->x + this->y + this->z);	//加算結果
}

/////
//＞代入演算子
//引数：const TTriType & Obj：代入する値の参照
//戻り値：代入が行われた自分自身
//概要：独立した３つのメンバー変数に対してそれぞれに代入処理を行う
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType>& TTriType<TriType>::operator=(const TTriType & Obj)
{
	//＞複製
	this->x = Obj.x;	//１つめのデータコピー
	this->y = Obj.y;	//２つめのデータコピー
	this->z = Obj.z;	//３つめのデータコピー

	//＞提供
	return	*this;	//自身の参照
}

/////
//＞加算演算子
//引数：const TTriType & Obj：加算する値の参照
//戻り値：自身と引数の加算結果
//概要：独立した３つのメンバー変数に対してそれぞれに加算処理を行う
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> TTriType<TriType>::operator+(const TTriType & Obj)
{
	//＞提供
	return { this->x + Obj.x, this->y + Obj.y, this->z + Obj.z };	//加算結果
}

/////
//＞加算代入演算子
//引数：const TTriType & Obj：加算する値の参照
//戻り値：引数が加算された自分自身
//概要：独立した３つのメンバー変数に対してそれぞれに加算処理を行ったものを代入する
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> & TTriType<TriType>::operator+=(const TTriType & Obj)
{
	//＞提供
	return (*this = *this + Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/////
//＞減算演算子
//引数：const TTriType & Obj：減算する値の参照
//戻り値：自身 - 引数の結果
//概要：独立した３つのメンバー変数に対してそれぞれに減算処理を行う
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> TTriType<TriType>::operator-(const TTriType & Obj)
{
	//＞提供
	return { this->x - Obj.x, this->y - Obj.y, this->z - Obj.z };	//減算結果
}

/////
//＞減算代入演算子
//引数：const TTriType & Obj：減算する値の参照
//戻り値：引数が減算された自分自身
//概要：独立した３つのメンバー変数に対してそれぞれに減算処理を行ったものを代入する
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> & TTriType<TriType>::operator-=(const TTriType & Obj)
{
	//＞提供
	return (*this = *this - Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/////
//＞乗算演算子
//引数：const TTriType & Obj：乗算する値の参照
//戻り値：自身と引数の乗算結果
//概要：独立した３つのメンバー変数に対してそれぞれに乗算処理を行う
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> TTriType<TriType>::operator*(const TTriType & Obj)
{
	//＞提供
	return { this->x * Obj.x, this->y * Obj.y, this->z * Obj.z };	//乗算結果
}

/////
//＞乗算代入演算子
//引数：const TTriType & Obj：乗算する値の参照
//戻り値：引数が乗算された自分自身
//概要：独立した３つのメンバー変数に対してそれぞれに乗算処理を行ったものを代入する
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> & TTriType<TriType>::operator*=(const TTriType & Obj)
{
	//＞提供
	return (*this = *this * Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/////
//＞除算演算子
//引数：const TTriType & Obj：除算する値の参照
//戻り値：自身 / 引数の結果
//概要：独立した３つのメンバー変数に対してそれぞれに除算処理を行う
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> TTriType<TriType>::operator/(const TTriType & Obj)
{
	//＞提供
	return { this->x / Obj.x, this->y / Obj.y, this->z / Obj.z };	//除算結果
}

/////
//＞除算代入演算子
//引数：const TTriType & Obj：除算する値の参照
//戻り値：引数が除算された自分自身
//概要：独立した３つのメンバー変数に対してそれぞれに除算処理を行ったものを代入する
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> & TTriType<TriType>::operator/=(const TTriType & Obj)
{
	//＞提供
	return (*this = *this / Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/////
//＞剰余演算子
//引数：const TTriType & Obj：剰余演算する値の参照
//戻り値：自身と引数の剰余演算結果
//概要：独立した３つのメンバー変数に対してそれぞれに剰余演算処理を行う
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> TTriType<TriType>::operator%(const TTriType & Obj)
{
	//＞提供
	return { static_cast<TriType>(static_cast<int>(this->x) % static_cast<int>(Obj.x)), static_cast<TriType>((int)this->y % (int)Obj.y), static_cast<TriType>((int)this->z % (int)Obj.z) };	//剰余演算結果
}

/////
//＞剰余代入演算子
//引数：const TTriType & Obj：剰余演算する値の参照
//戻り値：引数が剰余演算された自分自身
//概要：独立した３つのメンバー変数に対してそれぞれに剰余演算処理を行ったものを代入する
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> & TTriType<TriType>::operator%=(const TTriType & Obj)
{
	//＞提供
	return (*this = *this % Obj);	//実装済演算子を使用して処理を行い、自身の参照を返す
}

/////
//＞べき乗演算子
//引数：const double & dIndex：指数の参照
//戻り値：自身を引数でべき乗した演算結果
//概要：独立した３つのメンバー変数に対してそれぞれにべき乗処理を行う
/////
template<class TriType>	//テンプレート関数実装
TTriType<TriType> TTriType<TriType>::operator^(const double & dIndex)
{
	//＞提供
	return { (TriType)pow((double)this->x, dIndex), (TriType)pow((double)this->y, dIndex), (TriType)pow((double)this->z, dIndex) };	//べき乗演算結果
}

/////
//＞べき乗代入演算子
//引数：const double & dIndex：指数の参照
//戻り値：引数がべき乗された自分自身
//概要：独立した３つのメンバー変数に対してそれぞれにべき乗処理を行ったものを代入する
/////
template<class TriType>
TTriType<TriType> & TTriType<TriType>::operator^=(const double & dIndex)
{
	//＞提供
	return (*this = *this ^ dIndex);	//実装済演算子を使用して処理を行い、自身の参照を返す
}



//--- ここから下は試運転(cppにかかないと動かないので、試したい場合このヘッダをallコピーしてcppに貼り付けてください) ---//
	//！： 既存のmain関数がある場合は別プロジェクトで試すか、一時的にコメントアウトしてください。
//#include <iostream>
//#include <string>
//
//int main()
//{
//	TTriType<int> a;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//0,0,0のハズ
//
//	a = TTriType<int>(1, 1, 1);
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;
//
//	a = { 2, 2, 2 };
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;
//
//	a.x = 3;
//	a.y = 3;
//	a.z = 3;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;
//
//	TTriType<int> b(4, 4, 4);
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;
//
//	a + b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//3,3,3のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4のハズ
//
//	a = b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//4,4,4のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4のハズ
//
//	a += b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//8,8,8のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4のハズ
//
//
//	a %= b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//0,0,0のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4のハズ
//
//	b ^= 2.0;
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//16,16,16のハズ
//
//	b ^= 0.5;
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4のハズ
//
//	b ^= 0.25;
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//1,1,1のハズ
//
//	std::cin.get();
//
//	return 0;
//}