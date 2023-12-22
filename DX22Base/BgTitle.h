/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用背景定義
	---------------------------------------
	BgTitle.h

	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/17 最初拡大され徐々に縮小するように takagi

========================================== */

#ifndef __BG_TITLE_H__	//BgTitle.hインクルードガード
#define __BG_TITLE_H__

// =============== インクルード =====================
#include "TitleObj.h"	//親のヘッダ

// =============== クラス定義 =====================
class CBgTitle :public CTitleObj	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	CBgTitle(const int& nWaitTime = 0);							//コンストラクタ
	~CBgTitle();												//デストラクタ
	void Update() override;										//更新
	void ChangeLtoS(const int& nFrame);							//縮小
private:
	// ===変数宣言===========
	CFrameCnt* m_pCntLtoS;	//縮小カウンタ
};	//タイトル用背景

#endif	//!__BG_TITLE_H__