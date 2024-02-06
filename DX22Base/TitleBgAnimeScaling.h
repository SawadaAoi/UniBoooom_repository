/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用拡縮付きアニメ背景定義
	---------------------------------------
	TitleBgAnimeScaling.h

	作成者	takagi

	変更履歴
	・2024/02/06 制作 takagi

========================================== */

#ifndef __TITLE_BG_ANIME_SCALING_H__	//BgTitle.hインクルードガード
#define __TITLE_BG_ANIME_SCALING_H__

// =============== インクルード =====================
#include "DrawAnimation.h"	//親のヘッダ
#include <memory.h>			//ptr管理
#include "DiType.h"			//引数型定義
#include <array>			//配列コンテナ

// =============== クラス定義 =====================
class CTitleBgAnimeScaling :public CDrawAnim	//アニメーション
{
public:
	// ===プロトタイプ宣言===
	virtual ~CTitleBgAnimeScaling();		//デストラクタ
	virtual void Update() override;	//更新
protected:
	CTitleBgAnimeScaling(int, TDiType<int>, int = 1);									//コンストラクタ
	virtual void SetSize(const TTriType<float>& fScale) final;							//大きさセッタ
	virtual void SetScaleRate(const std::array<TTriType<float>, 2>& fScaleRate) final;	//拡縮率セッタ
private:
	// ===変数宣言===========
	std::shared_ptr <TTriType<float>> m_pfScaleShort;		//拡縮管理：最小
	std::shared_ptr <TTriType<float>> m_pfScaleLarge;		//拡縮管理：最大
	std::shared_ptr <TTriType<float>> m_pfScaleRateShort;	//拡縮率管理：最小
	std::shared_ptr <TTriType<float>> m_pfScaleRateLarge;	//拡縮率管理：最大
};	//開始時ズームアウトするタイトル用オブジェクト

#endif	//!__TITLE_BG_ANIME_SCALING_H__