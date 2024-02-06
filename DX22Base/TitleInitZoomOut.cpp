/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用開始時ズームアウト実装
	---------------------------------------
	TitleInitZoomOut.cpp

	作成者	takagi

	変更履歴
	・2024/02/02 制作 takagi

========================================== */

// =============== インクルード ===================
#include "TitleInitZoomOut.h"	//自身のヘッダ
#include "TitleInitCounter.h"	//カウンタ使用

// =============== 定数・マクロ定義 ===================
const TTriType<float> SCALE_RATE_L = {2.0f, 2.0f, 0.0f};	//拡大時の拡縮率を設定する

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTitleInitZoomOut::CTitleInitZoomOut()
{
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
CTitleInitZoomOut::~CTitleInitZoomOut()
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
void CTitleInitZoomOut::Update()
{
	// =============== 変数宣言 ===================
	auto pCounter = CTitleInitCounter::GetThis().GetCounter().lock();	//カウンタ

	// =============== 更新 ===================
	if (pCounter && m_pfScaleShort && m_pfScaleLarge)	//ヌルチェック
	{
		auto fCheck = (*m_pfScaleLarge - *m_pfScaleShort) * pCounter->GetRate() + *m_pfScaleShort;
		CTitleObj::SetSize(fCheck);	//カウンタ進行を利用した拡縮更新
	}
	CTitleObj::Update();	//親の関数使用
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
void CTitleInitZoomOut::SetSize(const TTriType<float>& fScale)
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
	CTitleObj::SetSize(*m_pfScaleLarge);	//大きさ設定
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
void CTitleInitZoomOut::SetScaleRate(const std::array<TTriType<float>, 2>& fScaleRate)
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