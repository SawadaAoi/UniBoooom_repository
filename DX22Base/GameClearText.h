/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームスタート描画用ヘッダ
	---------------------------------------
	GameClearText.h
	---------------------------------------
	作成者	nieda

	変更履歴
	・2023/12/17 新規作成 nieda
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __GAMECLEAR_TEXT_H__	//GameClearText.hインクルードガード
#define __GAMECLEAR_TEXT_H__

// =============== インクルード ===================
#include "DrawAnimation.h"

// =============== クラス定義 =====================
class CClearText :public CDrawAnim	//UIアニメーション
{
public:
	// ===プロトタイプ宣言===
	CClearText(CCamera*);	// コンストラクタ
	~CClearText() {};		// デストラクタ
protected:
	// ===メンバ変数宣言=====
};	//ゲームスタートUIアニメーション

#endif	//!__GAMECLEAR_TEXT_H__