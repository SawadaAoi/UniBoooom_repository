/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  プレイヤー移動エフェクトヘッダー
   ---------------------------------------
   WalkEffect.h

   作成者 鄭 宇恩

   変更履歴
	・2024/01/30 WalkEffectクラス作成 Tei

========================================== */
#ifndef __WALK_EFFECT_H__
#define __WALK_EFFECT_H__

// =============== インクルード ===================
#include "Shader.h"			//シェーダークラス定義ヘッダー
#include "Transform3d.h"	//ワールド座標系情報ヘッダー
#include "CameraChase.h"	//カメラ定義ヘッダー
#include "LibEffekseer.h"	//effekseer用ヘッダー

// =============== クラス定義 =====================
class CWalkEffect
{
public:
	// ===メンバ関数宣言===
	CWalkEffect(TPos3d<float> fPos, TPos3d<float> fOldPos15,TPos3d<float> fOldPos30, TPos3d<float> fRadian, float fTime, float fNum, Effekseer::EffectRef walkEffect, const CCamera* pCamera);	//コンストラクタ
	~CWalkEffect();												// デストラクタ
	void Update();												// 更新関数
	void Draw();												// 描画関数
	void DisplayTimeAdd();										// プレイヤー移動エフェクト表示カウント加算処理関数
	
	
	// セット関数
	void SetCamera(const CCamera* pCamera);	// 他のオブジェクトと同一のカメラをセット

	// ゲット関数
	bool GetDelFlg();						// 削除フラグ取得処理関数

private:

	// ===メンバ変数宣言===
	tagTransform3d m_Transform;
	tagTransform3d m_OldTransform17f;	// 17フレーム前の位置
	tagTransform3d m_OldTransform25f;	// 25フレーム前の位置

	const CCamera*	m_pCamera;			// カメラのポインタ
	bool			m_bDelFlg;			// プレイヤー移動エフェクト終了フラグ
	int				m_nDelFrame;		// プレイヤー移動エフェクト表示カウント
	float			m_fEffectTime;		// プレイヤー移動エフェクト総時間
	float			m_fRandNum;			// 位置やサイズなどランダムの調整値
	float			m_fRadian;			// 角度

	Effekseer::EffectRef m_walkEffect;
	Effekseer::Handle m_efcWalkHandle;
};

#endif //__WALK_EFFECT_H__