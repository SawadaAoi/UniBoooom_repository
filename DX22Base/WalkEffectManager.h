/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  プレイヤー移動エフェクト管理ヘッダー
   ---------------------------------------
   WalkEffectManager.h

   作成者 鄭 宇恩

   変更履歴
	・2024/01/30 WalkEffectManagerクラス作成 Tei
	・2024/02/13 カメラ削除 takagi

========================================== */
#ifndef __WALK_EFFECT_MANAGER_H__	
#define __WALK_EFFECT_MANAGER_H__

// =============== 定数定義 =======================
const int	MAX_STEP_NUM = 10;	// 最大エフェクト生成数

// =============== インクルード ===================
#include "WalkEffect.h"

// =============== クラス定義 =====================
class CWalkEffectManager
{
public:
	// ===メンバ関数宣言===
	CWalkEffectManager();		// コンストラクタ
	~CWalkEffectManager();		// デストラクタ

	void Draw();		 			// 描画関数
	void Update();

	CWalkEffect* GetWalkPtr(int num);			// プレイヤー移動エフェクト配列をゲット
	void Create(tagTransform3d tTransForm);   // プレイヤー移動エフェクト生成関数
	void DeleteCheck();							// 使ったエフェクトを削除関数
	int GetRandom(int nRange);				// ランダムで加算値ゲット

private:
	// ===メンバ変数宣言===
	CWalkEffect* m_pwalkEffect[MAX_STEP_NUM];	// プレイヤー移動エフェクトの配列

	Effekseer::EffectRef m_walkEffect;			// プレイヤー移動のEffekseer
};

#endif // __WALK_EFFECT_MANAGER_H__