/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ストリップ(帯状)パーティクル定義
	------------------------------------
	StripeParticle.h
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

#ifndef __STRIP_PARTICLE_H__
#define __STRIP_PARTICLE_H__

// =============== インクルード ===================
#include "Particle.h"	//親のヘッダ

// =============== クラス定義 =====================
class CStripeParticle	:CParticle	//パーティクル
{
protected:
	// ===メンバ変数宣言=====
	//pos定義
public:
	// ===プロトタイプ宣言===
	CStripeParticle();								//コンストラクタ
	CStripeParticle(const CStripeParticle& Obj);	//コピーコンストラクタ
	~CStripeParticle();								//デストラクタ
	void Draw();									//描画
};	//ストリップパーティクル

#endif	//!__STRIP_PARTICLE_H__