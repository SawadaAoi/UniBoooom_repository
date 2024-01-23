/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フレイムスライムh
	------------------------------------
	Slime_Flame.h
	------------------------------------
	作成者	鈴村朋也

	変更履歴
	・2023/11/14 クラス作成 Suzumura
	・2023/11/14 NormalMoveをオーバーライドして作成 Suzumura
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2024/01/18 炎スライムエフェクト追加 Tei

========================================== */
#ifndef __SLIME_FLAME__H__
#define __SLIME_FLAME__H__

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_Flame :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_Flame();
	CSlime_Flame(TPos3d<float> pos, Effekseer::EffectRef flameSlimeEffect, VertexShader* pVS, Model* pModel);
	~CSlime_Flame();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:
	////=======Effekseer=======
	//Effekseer::EffectRef m_flameSlimeEffect;
	//Effekseer::Handle m_efcslimeHnadle;
};


#endif __SLIME_FLAME__H__
