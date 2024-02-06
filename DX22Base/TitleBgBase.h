/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用背景定義
	---------------------------------------
	TitleBgBase.h

	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/17 最初拡大され徐々に縮小するように takagi
	・2024/02/05 リファクタリング takagi

========================================== */

#ifndef __TITLE_BG_BASE_H__	//TitleBgBase.hインクルードガード
#define __TITLE_BG_BASE_H__

// =============== インクルード =====================
#include "TitleInitZoomOut.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitleBgBase :public CTitleInitZoomOut	//開始時ズームアウトするタイトル用平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CTitleBgBase();				//コンストラクタ
	virtual ~CTitleBgBase();	//デストラクタ
};	//タイトル用背景

#endif	//!__TITLE_BG_BASE_H__