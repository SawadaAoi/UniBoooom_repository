/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ヒットスライムエフェクト管理ヘッダー
   ---------------------------------------
   HitSlimeEffectManager.h

   作成者 鄭 宇恩

   変更履歴
	・2024/01/25 HitSlimeEffectManagerクラス作成 Tei
	・2024/02/13 カメラ削除 takagi

========================================== */
#ifndef __HIT_SLIME_EFFECT_MANAGER_H__	
#define __HIT_SLIME_EFFECT_MANAGER_H__

// =============== 定数定義 =======================
const int	MAX_HIT_NUM = 5;	// 最大エフェクト生成数

// =============== インクルード ===================
#include "HitSlimeEffect.h"


// =============== クラス定義 =====================
class CHitSlimeEffectManager
{
public:
	// ===メンバ関数宣言===
	CHitSlimeEffectManager();		//コンストラクタ
	~CHitSlimeEffectManager();		//デストラクタ

	void Draw();		 			//描画関数
	void Update();

	CHitSlimeEffect* GetHitPtr(int num);				//ヒットエフェクト配列をゲット
	void Create(TTriType<float> pos);   		//ヒットエフェクト生成関数
	void DeleteCheck();							// 使ったエフェクトを削除関数


private:
	// ===メンバ変数宣言===
	CHitSlimeEffect* m_phitEffect[MAX_HIT_NUM];		//ヒットエフェクトの配列

	Effekseer::EffectRef m_hitEffect;			//ヒットのEffekseer
};

#endif // __HIT_SLIME_EFFECT_MANAGER_H__