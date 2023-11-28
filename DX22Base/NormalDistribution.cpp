/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	一様分布乱数実装
	------------------------------------
	NormalDistribution.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/28 制作 takagi

========================================== */

// =============== インクルード ===================
#include "NormalDistribution.h"	//自身のヘッダ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：const int & Min：乱数の最小値(範囲内)
	引数2：const int & Max：乱数の天井(範囲内)
	-------------------------------------
	戻値：なし
=========================================== */
TNormalDistribution<int>::TNormalDistribution(const int & Min, const int & Max)	//特殊化テンプレート関数実装
	:m_Min(Min)	//最小値
	,m_Max(Max)	//最大値
{
}

/* ========================================
	乱数取得関数
	-------------------------------------
	内容：分布に従った乱数を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
int TNormalDistribution<int>::Get()	//特殊化テンプレート関数実装
{
	std::uniform_int_distribution<> Rand{ m_Min, m_Max };	//乱数生成
	return Rand(ms_Engine);									//指定分布で乱数取得
}