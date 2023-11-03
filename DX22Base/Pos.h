//Pos.h
//位置座標を管理するテンプレートクラスを定義

//＞更新履歴
//2023/10/31	制作
//2023/11/02	距離計算関数のreturn文に不足していた'('を添加
				//・引数のconst不足を解消・速度(メモリ効率)意識で引数を参照方式に変更・コメント修正
//2023/11/03	Distance()関数の不具合を修正
//2023/11/04	.cpp/.h分け



//＞インクルードガード
#ifndef ___POS_H___
#define ___POS_H___

//＞インクルード部
#include "TriType.h"	//３つの同じ型を持つ型

//＞テンプレートクラス定義
template<class Pos>
class TPos :public TTriType<Pos>	//テンプレートクラス：位置
{
public:
	//＞プロトタイプ宣言
	TPos();											//コンストラクタ
	TPos(const Pos& x, const Pos& y, const Pos& z);	//引数付きコンストラクタ
	TPos(const TPos& Obj);							//コピーコンストラクタ
	~TPos();										//デストラクタ
	Pos Distance(const TPos& Obj);					//距離計算
};	//型テンプレート

#endif // !___POS_H___