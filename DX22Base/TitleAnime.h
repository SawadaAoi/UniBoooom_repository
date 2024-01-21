/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用アニメーション定義
	---------------------------------------
	TitleAnime.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/17 引数参照化 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __TITLE_ANIME_H__	//TitleAnime.hインクルードガード
#define __TITLE_ANIME_H__

// =============== インクルード =====================
#include "DrawAnimation.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTitleAnime :public CDrawAnim	//平面オブジェ
{
public:
	// ===プロトタイプ宣言===
	~CTitleAnime();			//デストラクタ
	void Update() override;	//更新
	void Draw() override;	//描画
protected:
	// ===プロトタイプ宣言===
	CTitleAnime(const int& nSplitMax, const TDiType<int>& nSplit, const int& nWaitTime = 0, const int& nCnt = 0);	//コンストラクタ
private:
	// ===メンバ変数宣言=====
	int* m_pnWaitTime;	//初動待機時間計測
};	//タイトル用アニメ

#endif	//!__TITLE_ANIME_H__