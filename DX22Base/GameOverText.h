/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームスタート描画用ヘッダ
	---------------------------------------
	GameOverText.h

	作成者
			nieda

	変更履歴
	・2023/12/17 新規作成 nieda
	・2024/02/13 カメラ削除 takagi

========================================== */

#ifndef __GAMEOVER_TEXT_H__	//DrawAnimation.hインクルードガード
#define __GAMEOVER_TEXT_H__

// =============== インクルード ===================
#include "DrawAnimation.h"

// =============== クラス定義 =====================
class COverText :public CDrawAnim	//UIアニメーション
{
public:
	// ===プロトタイプ宣言===
	COverText();		// コンストラクタ
	~COverText() {};	// デストラクタ
protected:
	// ===メンバ変数宣言=====
};	//ゲームスタートUIアニメーション

#endif	//!__GAMEOVER_TEXT_H__
