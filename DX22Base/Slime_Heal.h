/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ヒールスライム.h
	------------------------------------
	Slime_Heal.h
	------------------------------------
	作成者	鄭宇恩

	変更履歴
	・2023/12/04 クラス作成 Tei

========================================== */
#ifndef __SLIME_HEAL__H__
#define __SLIME_HEAL__H__

// =============== インクルード ===================
#include "SlimeBase.h"
#include "GameParameter.h"
#include "AnimeModel.h"
// =============== クラス定義 =====================
class CSlime_Heal :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_Heal();
	CSlime_Heal(TPos3d<float> pos, VertexShader* pVS, AnimeModel* pModel);
	~CSlime_Heal();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:

};


#endif __SLIME_HEAL__H__
