/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   汗エフェクトマネージャー クラス定義
   ---------------------------------------
   SweatEffectManager.h

   作成者：鄭宇恩

   変更履歴
	・2024/02/02 汗エフェクトマネージャークラス作成 Tei


=========================================== */
#ifndef __SWEAT_EFFECT_MANAGER_H__
#define __SWEAT_EFFECT_MANAGER_H__

// =============== インクルード ===================
#include "SweatEffect.h"

// =============== 定数定義 =======================
const int	MAX_SWEAT_EFFECT_NUM = 1;	// 最大エフェクト生成数

// =============== クラス定義 =====================
class CSweatEffectManager
{
public:
	CSweatEffectManager();
	~CSweatEffectManager();
	void Update(TTriType<float> pos);
	void Draw();
	void Create(TTriType<float> pos,  TTriType<float> radian);		// エフェクト生成

	void SetCamera(const CCamera* pCamera);		// 他のオブジェクトと同一のカメラをセット
	void DeleteCheck();							// 使ったエフェクトを削除関数

private:
	CSweatEffect* m_pSweatEffect[MAX_SWEAT_EFFECT_NUM];
	const CCamera* m_pCamera;					// カメラ
	//=======Effekseer=======
	Effekseer::EffectRef m_SweatEffect;
};


#endif // !__SWEAT_EFFECT_MANAGER_H__
