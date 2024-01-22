/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルロゴ定義
	---------------------------------------
	TitleLogo.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/17 引数参照化 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi
	・2024/01/22 Draw()関数const化 takagi

========================================== */

#ifndef __TITLE_LOGO_H__	//TitleLogo.hインクルードガード
#define __TITLE_LOGO_H__

// =============== インクルード =====================
#include "TitleAnime.h"	//親のヘッダ
#include "FrameCnt.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CTitleLogo :public CTitleAnime	//アニメーション
{
public:
	// ===プロトタイプ宣言===
	CTitleLogo(const int& nWaitTime = 0);								//コンストラクタ
	~CTitleLogo();														//デストラクタ
	void Update() override;												//更新
	void Draw() const override;											//描画
	void ChangeLtoS(const int& nFrame);									//縮小
private:
	// ===変数宣言===========
	CFrameCnt* m_pCntLtoS;	//縮小カウンタ
};	//タイトルロゴ

#endif	//!__TITLE_LOGO_H__