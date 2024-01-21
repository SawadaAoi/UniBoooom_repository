/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ3用ヘッダ
	------------------------------------
	Slime_3.h
	------------------------------------
	作成者　yamashita

	変更履歴
	・2023/11/08 作成 yamashita
	・2023/11/08 スライムの移動速度を設定する関数を継承 yamashita
	・2023/11/30 UpdateとNormalMoveをoverride yamashita
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SLIME_3_H__	//Slime_3.hインクルードガード
#define __SLIME_3_H__

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

	void Update();
	void NormalMove() final;	// 通常時の移動処理

	void SetNormalSpeed() override;
private:

};


#endif	//!__SLIME_3_H__