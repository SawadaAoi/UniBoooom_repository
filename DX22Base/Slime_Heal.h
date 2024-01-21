/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ヒールスライム定義
	------------------------------------
	Slime_Heal.h
	------------------------------------
	作成者	tei

	変更履歴
	・2023/12/04 クラス作成 tei
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SLIME_HEAL_H__	//Slime_Heal.hインクルードガード
#define __SLIME_HEAL_H__

// =============== インクルード ===================
#include "SlimeBase.h"
#include "GameParameter.h"

// =============== クラス定義 =====================
class CSlime_Heal :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_Heal();
	CSlime_Heal(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_Heal();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:

};


#endif	//!__SLIME_HEAL_H__