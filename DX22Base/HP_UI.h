/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HPテクスチャ表示管理用ヘッダ
	------------------------------------
	HpManager.h
	------------------------------------
	作成者	仁枝潤哉

	変更履歴
	・2023/11/16 新規作成 仁枝潤哉

========================================== */
#ifndef __HP_UI_H__
#define __HP_UI_H__

// =============== インクルード ===================
#include "Texture.h"	// テクスチャ用ヘッダ
#include <vector>

// =============== クラス定義 =====================
class CHP_UI
{
public:
	enum HEART_STATE
	{
		HEART_FULL,
		HEART_NONE,
		HEART_MAX,
	};

public:
	// ===メンバ関数宣言===
	CHP_UI(const int* pPlayerHp);		// コンストラクタ
	~CHP_UI();				// デストラクタ
	void Update();				// 更新処理
	void Draw();				// 描画処理
	void Draw2d(float, float, float, float, Texture*);	// 描画処理

	void SetHpTexture();

private:
	// ===メンバ変数宣言===
	Texture*	m_pTexture[HEART_MAX];		// テクスチャ用ポインタ
	std::vector<HEART_STATE>	m_HpState;
	const int*	m_pPlayerHp;				// プレイヤーのHP用ポインタ

};

#endif	// !__HP_UI_H__
