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
#include "2dPolygon.h"

using namespace std;

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
	CHP_UI(const int* pPlayerHp, const CCamera* pCamera);		// コンストラクタ
	~CHP_UI();				// デストラクタ
	void Update();				// 更新処理
	void Draw();				// 描画処理


private:
	// ===メンバ変数宣言===
	Texture*	m_pTexture[HEART_MAX];		// テクスチャ用ポインタ
	const int*	m_pPlayerHp;				// プレイヤーのHP用ポインタ
	vector<C2dPolygon> m_HeartNone;
	vector<C2dPolygon> m_HeartFull;

};

#endif	// !__HP_UI_H__
