//Pos.cpp
//位置座標を管理するテンプレートクラスを実装

//＞更新履歴
//2023/10/31	制作
//2023/11/02	距離計算関数のreturn文に不足していた'('を添加
				//・引数のconst不足を解消・速度(メモリ効率)意識で引数を参照方式に変更・コメント修正
//2023/11/03	Distance()関数の不具合を修正
//2023/11/04	.cpp/.h分け



//＞インクルード部
#include "Pos.h"	//自身のヘッダ

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



/////
//＞コンストラクタ
//引数：なし
//戻り値：なし
//概要：生成時に行う処理
/////
template<class Pos>	//テンプレート関数実装
TPos<Pos>::TPos()
	:TTriType<Pos>()	//委譲
{
}

/////
//＞コンストラクタ
//引数１：const Pos & x：x軸上の位置の参照
//引数２：const Pos & y：y軸上の位置の参照
//引数３：const Pos & z：z軸上の位置の参照
//戻り値：なし
//概要：生成時に行う処理
/////
template<class Pos>	//テンプレート関数実装
TPos<Pos>::TPos(const Pos & x, const Pos & y, const Pos & z)
	:TTriType<Pos>(x, y, z)	//委譲
{
}

/////
//＞コピーコンストラクタ
//引数：const TPos & Obj：複製するデータ元の参照
//戻り値：なし
//概要：コピー時に行う処理
/////
template<class Pos>	//テンプレート関数実装
TPos<Pos>::TPos(const TPos & Obj)
	:TTriType<Pos>(Obj)	//委譲
{
}

/////
//＞デストラクタ
//引数：なし
//戻り値：なし
//概要：破棄時に行う処理
/////
template<class Pos>	//テンプレート関数実装
TPos<Pos>::~TPos()
{
}

/////
//＞距離計算
//引数：const TPos & Obj：距離を求める値の参照
//戻り値：自身と引数の距離
//概要：二点の位置情報をもとに距離を求める
/////
template<class Pos>	//テンプレート関数実装
Pos TPos<Pos>::Distance(const TPos & Obj)
{
	//＞変数宣言
	TPos Temp(*this - *Obj);
	//＞提供
	return (Pos)(pow((double)Temp.Total(), 0.5));	//計算結果
}