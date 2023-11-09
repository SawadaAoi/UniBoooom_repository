/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	クアッドパーティクル(四角の2dポリゴン、ビルボードを使用する)定義
	------------------------------------
	QuadParticle.h
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

#ifndef __QUAD_PARTICLE_H__
#define __QUAD_PARTICLE_H__

// =============== インクルード ===================
#include "Particle.h"	//親のヘッダ

// =============== クラス定義 =====================
class CQuadParticle :CParticle	//パーティクル
{
protected:
	// ===メンバ変数宣言=====
	//pos定義
	//Geometryから継承したクラス：Quad
public:
	// ===プロトタイプ宣言===
	CQuadParticle();							//コンストラクタ
	CQuadParticle(const CQuadParticle& Obj);	//コピーコンストラクタ
	~CQuadParticle();							//デストラクタ
	void Draw();								//描画
};	//クアッドパーティクル

#endif	//!__QUAD_PARTICLE_H__