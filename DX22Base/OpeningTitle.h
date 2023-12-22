/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用オープニング定義
	---------------------------------------
	OpeningTitle.h

	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi

========================================== */

#ifndef __OPENING_TITLE_H__	//OpeningTitle.hインクルードガード
#define __OPENING_TITLE_H__

// =============== インクルード =====================
#include "TitleAnime.h"	//親のヘッダ

// =============== クラス定義 =====================
class COpeningTitle :public CTitleAnime	//アニメーション
{
public:
	// ===プロトタイプ宣言===
	COpeningTitle();	//コンストラクタ
	~COpeningTitle();	//デストラクタ
private:
};	//タイトル開始映像

#endif	//!__OPENING_TITLE_H__