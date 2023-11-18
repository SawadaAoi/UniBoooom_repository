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

#ifndef __HP_MANAGER_H__
#define __HP_MANAGER_H__

// =============== インクルード ===================
#include "Texture.h"	// テクスチャ用ヘッダ

// =============== クラス定義 =====================
class CHpManager
{
public:
	// ===メンバ関数宣言===
	CHpManager(const int*);		// コンストラクタ
	~CHpManager();				// デストラクタ
	void Update();				// 更新処理
	void Draw();				// 描画処理
	void Draw2d(float, float, float, float, Texture*);	// 描画処理
private:
	// ===メンバ変数宣言===
	Texture* m_pTexture[2];		// テクスチャ用ポインタ
	const int* m_pnPlayerHp;	// プレイヤーのHP用ポインタ
	bool m_bLost;				// HP増減による表示切替用フラグ
};

#endif	// !__HP_MANAGER_H__
