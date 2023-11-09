/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	パーティクル定義
	------------------------------------
	Particle.h
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// =============== インクルード ===================
#include "Camera.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CParticle
{
protected:
	// ===メンバ変数宣言=====
	//pos定義
	const CCamera* m_pCamera;	//カメラ
public:
	// ===プロトタイプ宣言===
	CParticle();							//コンストラクタ
	CParticle(const CParticle& Obj);		//コピーコンストラクタ
	virtual ~CParticle();					//デストラクタ
	virtual void Draw() = 0;				//描画
	void GetCamera(const CCamera* pCamera);	//カメラ取得
};	//パーティクル

#endif	//!__PARTICLE_H__