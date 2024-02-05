/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	汗エフェクトクラス定義
	------------------------------------
	SweatEffect.h
	------------------------------------
	作成者	鄭宇恩

	変更履歴
	・2024/02/02 汗エフェクトクラス作成 Tei

========================================== */
#ifndef __SWEAT_EFFECT_H__
#define __SWEAT_EFFECT_H__

// =============== インクルード ===================
#include "Shader.h"			//シェーダークラス定義ヘッダー
#include "Transform3d.h"	//ワールド座標系情報ヘッダー
#include "CameraChase.h"	//カメラ定義ヘッダー
#include "LibEffekseer.h"	//effekseer用ヘッダー

class CSweatEffect
{
public:
	CSweatEffect(TPos3d<float> fPos, TPos3d<float> fRadian, float fTime, Effekseer::EffectRef sweatEffect, const CCamera* pCamera);
	~CSweatEffect();
	void Update(TPos3d<float> fPos);
	void Draw();
	void DisplayTimeAdd();					// 汗エフェクト表示カウント加算処理関数

	//  セット関数
	void SetCamera(CCamera* pCamera);

	// ゲット関数
	bool GetDelFlg();						// 削除フラグ取得処理関数

private:
	
	// ===メンバ変数宣言===
	tagTransform3d m_Transform;
	const CCamera*	m_pCamera;			// カメラのポインタ
	bool			m_bDelFlg;			// ヒットエフェクト終了フラグ
	int				m_nDelFrame;		// ヒットエフェクト表示カウント
	float			m_fEffectTime;		// ヒットエフェクト総時間

	//=======Effekseer=======
	Effekseer::EffectRef m_SweatEffect;
	Effekseer::Handle m_efcSweatHnadle;
};

#endif //_SWEAT_EFFECT_H__