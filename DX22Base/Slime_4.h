/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ4用ヘッダ
	------------------------------------
	Slime_4.h
	------------------------------------
	作成者　yamashita

	変更履歴
	・2023/11/08 作成 yamashita
	・2023/11/08 スライムの移動速度を設定する関数を継承 yamashita
	・2023/11/16 引数付きコンストラクタの引数に頂点シェーダーとモデルのポインタを追加 yamashita
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SLIME_4_H__	//Slime_4.hインクルードガード
#define	__SLIME_4_H__

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_4 :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_4();
	CSlime_4(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_4();
	void Update() override;

	void NormalMove() override;

	void SetNormalSpeed() override;
private:
	

};


#endif	//!__SLIME_4_H__