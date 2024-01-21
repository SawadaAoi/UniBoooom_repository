/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームスタート描画用ヘッダ
	---------------------------------------
	GameStartText.h
	---------------------------------------
	作成者	nieda

	変更履歴
	・2023/12/12 新規作成 nieda
	・2023/12/17 名前変更 nieda
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __GAMESTART_TEXT_H__	//GameStartText.hインクルードガード
#define __GAMESTART_TEXT_H__

// =============== インクルード ===================
#include "DrawAnimation.h"

// =============== クラス定義 =====================
class CStartText :public CDrawAnim	//UIアニメーション
{
public:
	// ===プロトタイプ宣言===
	CStartText(CCamera*);	// コンストラクタ
	~CStartText() {};		// デストラクタ
protected:
	// ===メンバ変数宣言=====
};	//ゲームスタートUIアニメーション

#endif	//!__GAMESTART_TEXT_H__