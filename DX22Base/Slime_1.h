/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ1用ヘッダ
	------------------------------------
	Slime_1.h
	------------------------------------
	作成者　澤田

	変更履歴
	・2023/11/08 作成 澤田蒼生
	・2023/11/08 スライムの移動速度を設定する関数を継承 山下凌佑

========================================== */
#ifndef __SLIME_1__H__
#define __SLIME_1__H__

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_1 :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_1();
	CSlime_1(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_1();

	void SetNormalSpeed() override;
private:

};


#endif __SLIME_1__H__