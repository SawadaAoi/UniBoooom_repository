/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用アニメ背景定義
	---------------------------------------
	BgTitleAnime.h

	作成者	takagi

	変更履歴
	・2024/01/29 制作 takagi

========================================== */

#ifndef __BG_TITLE_ANIME_H__	//BgTitleAnime.hインクルードガード
#define __BG_TITLE_ANIME_H__

// =============== インクルード =====================
#include "TitleAnime.h"	//親のヘッダ

// =============== クラス定義 =====================
class CBgTitleAnime :public CTitleAnime	//アニメーション
{
public:
	// ===プロトタイプ宣言===
	CBgTitleAnime();													//コンストラクタ
	~CBgTitleAnime();													//デストラクタ
	void Update() override;												//更新
	void Draw(const E_DRAW_MODE & eMode = E_DRAW_MODE_NORMAL) override;	//描画
	void ChangeLtoS(const int& nFrame);									//縮小
private:
	// ===変数宣言===========
	CFrameCnt* m_pCntLtoS;	//縮小カウンタ
};	//タイトル開始映像

#endif	//!__BG_TITLE_ANIME_H__