/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルロゴ定義
	---------------------------------------
	TitleLogo.h

	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/17 引数参照化 takagi
	・2024/02/02 リファクタリング takagi
	・2024/02/05 リファクタリング takagi

========================================== */

#ifndef __TITLE_LOGO_H__	//TitleLogo.hインクルードガード
#define __TITLE_LOGO_H__

// =============== インクルード =====================
#include "TitleInitZoomOut.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitleLogo :public CTitleInitZoomOut	//開始時ズームアウトするタイトル用平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CTitleLogo();					//コンストラクタ
	virtual ~CTitleLogo();			//デストラクタ
	virtual void Update() final;	//更新
};	//タイトルロゴ

#endif	//!__TITLE_LOGO_H__