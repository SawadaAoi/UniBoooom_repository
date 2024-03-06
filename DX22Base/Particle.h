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
	・2024/02/13 カメラ削除 takagi

========================================== */

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// =============== クラス定義 =====================
class CParticle
{
public:
	// ===プロトタイプ宣言===
	CParticle();							//コンストラクタ
	CParticle(const CParticle& Obj);		//コピーコンストラクタ
	virtual ~CParticle();					//デストラクタ
	virtual void Draw() = 0;				//描画
};	//パーティクル

#endif	//!__PARTICLE_H__