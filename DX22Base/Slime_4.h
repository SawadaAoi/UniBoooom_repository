#ifndef __SLIME_4__H__
#define __SLIME_4__H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ4用ヘッダ
	------------------------------------
	Slime_4.h
	------------------------------------
	作成者　山下凌佑

	変更履歴
	・2023/11/08 作成 山下凌佑
	・2023/11/08 スライムの移動速度を設定する関数を継承 山下凌佑

========================================== */

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_4 :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_4();
	CSlime_4(TPos3d<float> pos);
	~CSlime_4();

	void SetNormalSpeed() override;
private:

};


#endif __SLIME_4__H__
