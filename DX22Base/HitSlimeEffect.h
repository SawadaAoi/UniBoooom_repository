/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  ヒットスライムエフェクトヘッダー
   ---------------------------------------
   HitSlimeEffect.h

   作成者 鄭 宇恩

   変更履歴
	・2024/01/25 HitSlimeEffectクラス作成 Tei
	・2024/02/13 カメラ削除 takagi

========================================== */
#ifndef __HIT_SLIME_EFFECT_H__	
#define __HIT_SLIME_EFFECT_H__

// =============== インクルード ===================
#include "Shader.h"			//シェーダークラス定義ヘッダー
#include "Transform3d.h"	//ワールド座標系情報ヘッダー
#include "LibEffekseer.h"	//effekseer用ヘッダー

// =============== クラス定義 =====================

class CHitSlimeEffect
{
public:
	// ===メンバ関数宣言===
	CHitSlimeEffect(TPos3d<float> fPos, float fTime, Effekseer::EffectRef hitEffect);	//コンストラクタ
	~CHitSlimeEffect();												// デストラクタ
	void Update();												// 更新関数
	void Draw();												// 描画関数
	void DisplayTimeAdd();										// ヒットエフェクト表示カウント加算処理関数

	// ゲット関数
	bool GetDelFlg();						// 削除フラグ取得処理関数

private:

	// ===メンバ変数宣言===
	tagTransform3d m_Transform;
	bool			m_bDelFlg;			// ヒットエフェクト終了フラグ
	int				m_nDelFrame;		// ヒットエフェクト表示カウント
	float			m_fEffectTime;		// ヒットエフェクト総時間

	Effekseer::EffectRef m_hitEffect;	
	Effekseer::Handle m_efcHitHandle;	
};

#endif // __HIT_SLIME_EFFECT_H__