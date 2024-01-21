/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ2用ヘッダ
	------------------------------------
	Slime_2.h
	------------------------------------
	作成者　yamashita

	変更履歴
	・2023/11/08 作成 yamashita
	・2023/11/08 スライムの移動速度を設定する関数を継承 yamashita
	・2023/11/16 引数付きコンストラクタの引数に頂点シェーダーとモデルのポインタを追加 yamashita
	・2023/12/01 タックルの挙動を追加 yamashita
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SLIME_2_H__	//Slime_2.hインクルードガード
#define __SLIME_2_H__

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_2 :
	public CSlimeBase
{

public:
	enum ATTACK_MOVE_TYPE
	{
		ATTACK_NONE,		// 初期状態
		ATTACK_CHARGE,	// 突進前の溜め
		ATTACK_TACKLE,	// 突進
	};
public:
	// ===プロトタイプ宣言===
	CSlime_2();
	CSlime_2(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_2();
	void Update() override;
	void NormalMove() override;

	void SetNormalSpeed() override;
private:
	ATTACK_MOVE_TYPE m_AtcMoveType;
	int m_nChargeCnt;
	int m_nTackleCnt;
	int m_nAtkInterval;
	DirectX::XMVECTOR tackleDirection;
};


#endif	//!__SLIME_2_H__