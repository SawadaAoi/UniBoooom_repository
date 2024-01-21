/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フレイムスライム定義
	------------------------------------
	Slime_Flame.h
	------------------------------------
	作成者	suzumura

	変更履歴
	・2023/11/14 クラス作成 suzumura
	・2023/11/14 NormalMoveをオーバーライドして作成 suzumura
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SLIME_FLAME_H__	//Slime_Flame.hインクルードガード
#define __SLIME_FLAME_H__

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_Flame :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_Flame();
	CSlime_Flame(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_Flame();
	void NormalMove() override;
	void SetNormalSpeed() override;

private:

};


#endif	//!__SLIME_FLAME_H__
