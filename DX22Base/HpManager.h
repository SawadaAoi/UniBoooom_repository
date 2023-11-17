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
#include "HpUI.h"

// =============== 定数定義 =======================
#define MAX_HP	(5)

// =============== クラス定義 =====================
class ChpManager
{
public:
	// ===メンバ関数宣言===
	ChpManager();
	~ChpManager();
	void Update();
	void Draw();
private:
	// ===メンバ変数宣言===
	CHpUI* m_pUI[MAX_HP];
	int m_playerHP;
	int m_playerOldHP;
};

#endif	// !__HP_MANAGER_H__
