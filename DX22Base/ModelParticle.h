/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	モデルパーティクル定義
	------------------------------------
	ModelParticle.h
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

#ifndef __QUAD_PARTICLE_H__
#define __QUAD_PARTICLE_H__

// =============== インクルード ===================
#include "Particle.h"	//親のヘッダ
#include "Model.h"		//メンバのヘッダ

// =============== クラス定義 =====================
class CModelParticle :CParticle	//パーティクル
{
protected:
	// ===メンバ変数宣言=====
	//pos定義
	Model*m_pModel;	//3dモデル
public:
	// ===プロトタイプ宣言===
	CModelParticle();							//コンストラクタ
	CModelParticle(const CModelParticle& Obj);	//コピーコンストラクタ
	~CModelParticle();							//デストラクタ
	void Draw();								//描画
};	//モデルパーティクル

#endif	//!__QUAD_PARTICLE_H__