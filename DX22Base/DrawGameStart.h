/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームスタート描画用ヘッダ
	---------------------------------------
	DrawAnimation.h

	作成者
			nieda

	変更履歴
	・2023/12/12 新規作成 nieda

========================================== */

#ifndef __DRAW_GAMESTART_H__	//DrawAnimation.hインクルードガード
#define __DRAW_GAMESTART_H__

// =============== インクルード ===================
#include "DrawAnimation.h"

// =============== クラス定義 =====================
class CDrawStart :public CDrawAnim	//UIアニメーション
{
public:
	// ===プロトタイプ宣言===
	CDrawStart(CCamera*);	// コンストラクタ
	~CDrawStart() {};		// デストラクタ
protected:
	// ===メンバ変数宣言=====
};	//ゲームスタートUIアニメーション

#endif	//!__DRAW_GAMESTART_H__


