/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	一様分布乱数定義
	------------------------------------
	UniformDistribution.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/28 制作 takagi

========================================== */

#ifndef ___UNIFORM_DISTRIBUTION_H___	//Random.hインクルードガード
#define ___UNIFORM_DISTRIBUTION_H___

// =============== インクルード ===================
#include "Random.h"	//親のヘッダ

// =============== テンプレートクラス定義 ===================
template<class Random>
class TUniformDistribution :public CRandom	//乱数
{
public:
	TUniformDistribution(const Random& Min, const Random& Max);	//コンストラクタ
private:
	const Random m_Min;	//最小値
	const Random m_Max;	//最大値
	Random Get();		//乱数取得
};	//テンプレートクラス：一様分離の乱数生成

// =============== 特殊テンプレートクラス定義 ===================
template<>
class TUniformDistribution<int> :public CRandom<int>	//乱数
{
public:
	TUniformDistribution(const int& Min, const int& Max);	//コンストラクタ
private:
	const int m_Min;	//最小値
	const int m_Max;	//最大値
	int Get();			//乱数取得
};	//テンプレートクラス：一様分離の乱数生成

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：const Random & Min：乱数の最小値(範囲内)
	引数2：const Random & Max：乱数の天井(範囲外)
	-------------------------------------
	戻値：なし
=========================================== */
template<class Random>	//テンプレート関数実装
TUniformDistribution<Random>::TUniformDistribution(const Random & Min, const Random & Max)
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
template<class Random>	//テンプレート関数実装
Random TUniformDistribution<Random>::Get()
{
	// =============== 提供 ===================
	return static_cast<Random>(std::uniform_real_distribution{ Min, Max }(ms_Engine));	//乱数結果
}

#endif // !___UNIFORM_DISTRIBUTION_H___