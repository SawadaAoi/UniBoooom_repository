/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HPテクスチャ表示管理用ヘッダ
	------------------------------------
	HpManager.h
	------------------------------------
	作成者	仁枝潤哉

	変更履歴
	・2023/11/16 新規作成 Nieda
	・2023/11/28 半分ずつ減るように修正 Sawada

========================================== */
#ifndef __HP_UI_H__
#define __HP_UI_H__

// =============== インクルード ===================
#include "Texture.h"	// テクスチャ用ヘッダ


// =============== クラス定義 =====================
class CHP_UI
{
public:
	enum HEART_STATE
	{
		HEART_FULL,
		HEART_HALF,
		HEART_NONE,
		HEART_MAX,
	};

public:
	// ===メンバ関数宣言===
	CHP_UI(const int* pPlayerHp);		// コンストラクタ
	~CHP_UI();				// デストラクタ
	void Update();				// 更新処理
	void Draw();				// 描画処理


private:
	// ===メンバ変数宣言===
	Texture*	m_pTexture[HEART_MAX];		// テクスチャ用ポインタ
	const int*	m_pPlayerHp;				// プレイヤーのHP用ポインタ


};

#endif	// !__HP_UI_H__
