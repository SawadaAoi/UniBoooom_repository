/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	三次元位置座標を管理するテンプレートクラスを定義
	------------------------------------
	Pos3d.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/10/31 制作 takagi
	・2023/11/02 距離計算関数のreturn文に不足していた'('を添加 takagi
					・引数のconst不足を解消・速度(メモリ効率)意識で引数を参照方式に変更・コメント修正 takagi
	・2023/11/03 Distance()関数の不具合を修正 takagi
	・2023/11/04 .cpp/.h分け→分割解除 takagi
	・2023/11/07 コーディング規約適用 takagi
	・2023/11/09 変換コンストラクタ作成 takagi

========================================== */

#ifndef ___POS_3D_H___
#define ___POS_3D_H___

// =============== インクルード ===================
#include "TriType.h"	//３つの同じ型を持つ型

// =============== テンプレートクラス定義 ===================
template<class Pos3d>
struct TPos3d :public TTriType<Pos3d>	//テンプレートクラス：位置
{
public:
	// ===メンバ関数宣言===
	TPos3d();												//コンストラクタ
	TPos3d(const Pos3d& x, const Pos3d& y, const Pos3d& z);	//引数付きコンストラクタ
	TPos3d(const TTriType<Pos3d>& Tri);						//変換コンストラクタ
	TPos3d(const TPos3d& Obj);								//コピーコンストラクタ
	~TPos3d();												//デストラクタ
	Pos3d Distance(const TPos3d& Obj);						//距離計算
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
template<class Pos3d>	//テンプレート関数実装
TPos3d<Pos3d>::TPos3d()
	:TTriType<Pos3d>()	//委譲
{
}

/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：const Pos3d & x：x軸上の位置の参照
	引数2：const Pos3d & y：y軸上の位置の参照
	引数3：const Pos3d & z：z軸上の位置の参照
	-------------------------------------
	戻値：なし
=========================================== */
template<class Pos3d>	//テンプレート関数実装
TPos3d<Pos3d>::TPos3d(const Pos3d & x, const Pos3d & y, const Pos3d & z)
	:TTriType<Pos3d>(x, y, z)	//委譲
{
}

/* ========================================
	変換コンストラクタ
	-------------------------------------
	内容：親の型からのキャスト演算子
	-------------------------------------
	引数1：const TTriType<Pos3d> & Tri：変換元の型
	-------------------------------------
	戻値：なし
=========================================== */
template<class Pos3d>
TPos3d<Pos3d>::TPos3d(const TTriType<Pos3d> & Tri)
{
	// =============== 格納 ===================
	*this = Tri;	//型変換
}

/* ========================================
	コピーコンストラクタ
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const TPos3d & Obj：複製するデータ元の参照
	-------------------------------------
	戻値：なし
=========================================== */
template<class Pos3d>	//テンプレート関数実装
TPos3d<Pos3d>::TPos3d(const TPos3d & Obj)
	:TTriType<Pos3d>(Obj)	//委譲
{
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
template<class Pos3d>	//テンプレート関数実装
TPos3d<Pos3d>::~TPos3d()
{
}

/* ========================================
	距離計算
	------------------------------------ -
	内容：二点の位置情報をもとに距離を求める
	------------------------------------ -
	引数1：const TPos3d & Obj：距離を求める値の参照
	------------------------------------ -
	戻値：自身と引数の距離
=========================================== */
template<class Pos3d>	//テンプレート関数実装
Pos3d TPos3d<Pos3d>::Distance(const TPos3d & Obj)
{
	// =============== 変数宣言 =======================
	TPos3d Temp((*this - Obj) ^ 2);	//引き算の結果

	// =============== 提供 =======================
	return (Pos3d)(pow((double)Temp.Total(), 0.5));	//計算結果
}

#endif // !___POS_3D_H___



//--- ここから下は試運転(cppにかかないと動かないので、試したい場合このヘッダをallコピーしてcppに貼り付けてください) ---//
	//！： 既存のmain関数がある場合は別プロジェクトで試すか、一時的にコメントアウトしてください。
//#include <iostream>
//#include <string>
//
//int main()
//{
//	TPos3d<int> a;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//0,0,0のハズ
//
//	a = TPos3d<int>(1, 1, 1);
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
//	TPos3d<int> b(4, 4, 4);
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
//	a -= b;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//8,8,8のハズ
//	std::cout << std::to_string(b.x) << "," << std::to_string(b.y) << "," << std::to_string(b.z) << std::endl;	//4,4,4のハズ
//
//	a ^= 2;	//暗黙の型キャスト
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//64,64,64のハズ
//
//	a ^= 0.5;
//	std::cout << std::to_string(a.x) << "," << std::to_string(a.y) << "," << std::to_string(a.z) << std::endl;	//8,8,8のハズ
//
//	//std::cout << std::to_string(a.Distance(b)) << std::endl;	//12のハズ
//
//	std::cin.get();
//
//	return 0;
//}