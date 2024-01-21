/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ1用ヘッダ
	------------------------------------
	Slime_1.h
	------------------------------------
	作成者　sawada

	変更履歴
	・2023/11/08 作成 sawada
	・2023/11/08 スライムの移動速度を設定する関数を継承 yamashita
	・2023/11/16 引数付きコンストラクタの引数に頂点シェーダーとモデルのポインタを追加 yamashita
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SLIME_1_H__	//Slime_1.hインクルードガード
#define __SLIME_1_H__

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


#endif	//!__SLIME_1_H__