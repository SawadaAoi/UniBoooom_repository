#ifndef __SLIME_3__H__
#define __SLIME_3__H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ3用ヘッダ
	------------------------------------
	Slime_3.h
	------------------------------------
	作成者　山下凌佑

	変更履歴
	・2023/11/08 作成 山下凌佑
	・2023/11/08 スライムの移動速度を設定する関数を継承 山下凌佑

========================================== */

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_3 :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_3();
	CSlime_3(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_3();

	void SetNormalSpeed() override;
private:

};


#endif __SLIME_3__H__