/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	結合エフェクトマネージャ―ヘッダ
	---------------------------------------
	UnionSmokeEffectManager.h

	作成者
			Tei

	変更履歴
	・2024/02/06 クラス定義作成 Tei
	・2024/02/13 カメラ削除 takagi

========================================== */

#ifndef __UNION_SMOKE_EFFECT_MANAGER_H__
#define __UNION_SMOKE_EFFECT_MANAGER_H__

// =============== インクルード ===================
#include "UnionSmokeEffect.h"

// =============== 定数定義 ===================
const int MAX_UNION_SMOKE_NUM = 55;

// =============== クラス定義 =====================
class CUnionSmokeEffectManager
{
public:
	// ===列挙定義===========
	enum E_SMOKE	// 表示画像
	{
		GREEN_SMOKE,	// 結合煙の画像（緑）
		YELLOW_SMOKE,	// 結合煙の画像（黄）
		RED_SMOKE,		// 結合煙の画像（赤）

		SMOKE_MAX,
	};
public:
	CUnionSmokeEffectManager();
	~CUnionSmokeEffectManager();
	void Create(TPos3d<float> fpos, int slimelevel);
	void Update();
	void Draw();
	void DeleteCheck();							// 使ったエフェクトを削除関数

private:
	CUnionSmokeEffect* m_pUnionSmokeEffect[MAX_UNION_SMOKE_NUM];
	Texture* m_pTexture[SMOKE_MAX];
};



#endif //!__UNION_SMOKE_EFFECT_MANAGER_H__