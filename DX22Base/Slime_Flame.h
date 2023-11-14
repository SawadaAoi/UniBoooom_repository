/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フレイムスライムh
	------------------------------------
	Slime_Flame.h
	------------------------------------
	作成者	鈴村朋也

	変更履歴
	・2023/11/14 クラス作成
	・2023/11/14 NormalMoveをオーバーライドして作成

========================================== */
#ifndef __SLIME_FRAME__H__
#define __SLIME_FRAME__H__

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_Flame :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_Flame();
	CSlime_Flame(TPos3d<float> pos);
	~CSlime_Flame();
	void NormalMove(TPos3d<float> playerSphere) override;
	void SetNormalSpeed() override;

private:

};


#endif __SLIME_FRAME__H__
