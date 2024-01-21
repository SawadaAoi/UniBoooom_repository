/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HPテクスチャ表示管理用ヘッダ
	------------------------------------
	HP_UI.h
	------------------------------------
	作成者	nieda

	変更履歴
	・2023/11/16 新規作成 nieda
	・2023/11/28 半分ずつ減るように修正 sawada
	・2023/11/16 新規作成 nieda
	・2023/11/29 アニメーション再生用変数追加 nieda
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __HP_UI_H__	//HP_UI.hインクルードガード
#define __HP_UI_H__

// =============== インクルード ===================
#include "Texture.h"	// テクスチャ用ヘッダ


// =============== クラス定義 =====================
class CHP_UI
{
public:
	enum HEART_STATE
	{
		HEART_FULL,			// 満タンのハート
		HEART_HALF,			// 半分のハート
		HEART_NONE,			// 空のハート
		HEART_FH_ANIM,		// ハートが満タン→半分に減るアニメーション
		HEART_HE_ANIM,		// ハートが半分→空に減るアニメーション
		HEART_MAX,			// ハートのテクスチャの最大数
	};

public:
	// ===メンバ関数宣言===
	CHP_UI(const int* pPlayerHp);		// コンストラクタ
	~CHP_UI();							// デストラクタ
	void Update();				// 更新処理
	void Draw();				// 描画処理


private:
	// ===メンバ変数宣言===
	Texture*	m_pTexture[HEART_MAX];		// テクスチャ用ポインタ
	const int*	m_pPlayerHp;				// プレイヤーのHP用ポインタ
	int m_nPlayerOldHp;						// 変更前のHPを格納
	bool m_bPlayAnim;	// HPのアニメーションを再生するか判定

	int m_nCnt;			// アニメーション切り替えカウント用
	float m_fUVposX;	// テクスチャの横分割数
	float m_fUVposY;	// テクスチャの縦分割数
	int m_nCntWidth;	// テクスチャの横分割数カウント用
	int m_nCntHeight;	// テクスチャの縦分割数カウント用
};

#endif	//!__HP_UI_H__
