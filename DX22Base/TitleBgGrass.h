/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用アニメ背景定義(草パターン)
	---------------------------------------
	TitleBgGrass.h

	作成者	takagi

	変更履歴
	・2024/01/29 制作 takagi
	・2024/02/06 制作進行 takagi

========================================== */

#ifndef __TITLE_BG_GRASS_H__	//TitleBgGrass.hインクルードガード
#define __TITLE_BG_GRASS_H__

// =============== インクルード =====================
#include "TitleBgAnimeScaling.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitleBgGrass :public CTitleBgAnimeScaling	//背景アニメーション
{
public:
	// ===プロトタイプ宣言===
	CTitleBgGrass();	//コンストラクタ
	~CTitleBgGrass();	//デストラクタ
};	//タイトル開始映像

#endif	//!__TITLE_BG_GRASS_H__