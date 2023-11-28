/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	一様分布乱数定義
	------------------------------------
	NormalDistribution.h
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/28 制作 takagi

========================================== */

#ifndef ___NORMAL_DISTRIBUTION_H___	//Random.hインクルードガード
#define ___NORMAL_DISTRIBUTION_H___

// =============== インクルード ===================
#include "Random.h"	//親のヘッダ

// =============== テンプレートクラス定義 ===================
template<class Random>
class TNormalDistribution :public CRandom	//乱数
{
public:
	TNormalDistribution(const Random& Min, const Random& Max);	//コンストラクタ
private:
	const Random m_Min;	//最小値
	const Random m_Max;	//最大値
	Random Get();		//乱数取得
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
TNormalDistribution<Random>::TNormalDistribution(const Random & Min, const Random & Max)
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
Random TNormalDistribution<Random>::Get()
{
	// =============== 提供 ===================
	return static_cast<Random>(std::normal_distribution{}(ms_Engine));	//乱数結果
}

#endif // !___NORMAL_DISTRIBUTION_H___