/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用拡縮付きアニメ背景実装
	---------------------------------------
	TitleBgAnimeScaling.cpp

	作成者	takagi

	変更履歴
	・2024/02/06 制作 takagi

========================================== */

// =============== インクルード ===================
#include "TitleBgAnimeScaling.h"		//自身のヘッダ
#include "TitleInitCounter.h"	//カウンタ使用
#include "Defines.h"			//画面情報用

// =============== 定数・マクロ定義 ===================
const TPos3d<float> POS{ static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f };	//位置
const TPos3d<float> SCALE(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f);				//小さいときの大きさ
const TTriType<float> SCALE_RATE_L = { 2.0f, 2.0f, 0.0f };															//拡大時の拡縮率を設定する

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：int, TDiType<int>, int = 1：継承元を参照してください。
	----------------------------------------
	戻値：なし
=========================================== */
CTitleBgAnimeScaling::CTitleBgAnimeScaling(int nSplitMax, TDiType<int> nSplit, int nCnt)
	:CDrawAnim(nSplitMax, nSplit, nCnt)	//委譲
{
	// =============== 初期化 ===================
	SetPos(POS);	//位置初期化
	SetSize(SCALE);	//大きさ初期化
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTitleBgAnimeScaling::~CTitleBgAnimeScaling()
{
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTitleBgAnimeScaling::Update()
{
	// =============== 変数宣言 ===================
	auto pCounter = CTitleInitCounter::GetThis().GetCounter().lock();	//カウンタ

	// =============== 更新 ===================
	if (pCounter && m_pfScaleShort && m_pfScaleLarge)	//ヌルチェック
	{
		auto fCheck = (*m_pfScaleLarge - *m_pfScaleShort) * pCounter->GetRate() + *m_pfScaleShort;
		CDrawAnim::SetSize(fCheck);	//カウンタ進行を利用した拡縮更新
	}
	CDrawAnim::Update();	//親の関数使用
}

/* ========================================
	大きさセッタ関数
	-------------------------------------
	内容：最小・最大の大きさ登録
	-------------------------------------
	引数1：const TTriType<float> & fScale：通常時の(最小)拡縮情報
	-------------------------------------
	戻値：なし
=========================================== */
void CTitleBgAnimeScaling::SetSize(const TTriType<float>& fScale)
{
	// =============== 初期化・動的確保 ===================
	if (m_pfScaleShort)	//ヌルチェック
	{
		*m_pfScaleShort = fScale;	//最小拡縮率初期化
	}
	else
	{
		m_pfScaleShort = std::make_shared<TTriType<float>>(fScale);	//最小拡縮率確保
	}
	if (m_pfScaleLarge)	//ヌルチェック
	{
		*m_pfScaleLarge = fScale;	//最小拡縮率初期化
	}
	else
	{
		m_pfScaleLarge = std::make_shared<TTriType<float>>(fScale);	//最大拡縮率確保
	}

	// =============== 拡縮情報反映 ===================
	if (m_pfScaleRateShort)	//ヌルチェック
	{
		*m_pfScaleShort *= *m_pfScaleRateShort;	//最小サイズ設定
	}
	if (m_pfScaleRateLarge)	//ヌルチェック
	{
		*m_pfScaleLarge *= *m_pfScaleRateLarge;	//最大サイズ設定
	}
	else
	{
		*m_pfScaleLarge *= SCALE_RATE_L;	//最大サイズ設定
	}

	// =============== 初期化 ===================
	CDrawAnim::SetSize(*m_pfScaleLarge);	//大きさ設定
}

/* ========================================
	拡縮率セッタ関数
	-------------------------------------
	内容：最小・最大の拡縮率登録
	-------------------------------------
	引数1：const std::array<TTriType<float>, 2>& fScaleRate：拡縮率[0:最小, 1:最大]
	-------------------------------------
	戻値：なし
=========================================== */
void CTitleBgAnimeScaling::SetScaleRate(const std::array<TTriType<float>, 2>& fScaleRate)
{
	// =============== 初期化・動的確保 ===================
	if (m_pfScaleRateShort)	//ヌルチェック
	{
		*m_pfScaleRateShort = fScaleRate.at(0);	//最小拡縮率初期化
	}
	else
	{
		m_pfScaleRateShort = std::make_shared<TTriType<float>>(fScaleRate.at(0));	//最小拡縮率確保
	}
	if (m_pfScaleRateLarge)	//ヌルチェック
	{
		*m_pfScaleRateLarge = fScaleRate.at(1);	//最小拡縮率初期化
	}
	else
	{
		m_pfScaleRateLarge = std::make_shared<TTriType<float>>(fScaleRate.at(1));	//最大拡縮率確保
	}

	// =============== 反映 ===================
	if (m_pfScaleShort)	//ヌルチェック
	{
		*m_pfScaleShort *= *m_pfScaleRateShort;	//最小サイズ設定
	}
	if (m_pfScaleLarge)	//ヌルチェック
	{
		*m_pfScaleLarge *= *m_pfScaleRateLarge;	//最大サイズ設定
	}
}