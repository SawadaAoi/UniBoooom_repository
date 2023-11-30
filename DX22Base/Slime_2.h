#ifndef __SLIME_2__H__
#define __SLIME_2__H__
/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ2用ヘッダ
	------------------------------------
	Slime_2.h
	------------------------------------
	作成者　山下凌佑

	変更履歴
	・2023/11/08 作成 山下凌佑
	・2023/11/08 スライムの移動速度を設定する関数を継承 山下凌佑
	・2023/11/16 引数付きコンストラクタの引数に頂点シェーダーとモデルのポインタを追加 山下凌佑

========================================== */

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_2 :
	public CSlimeBase
{

public:
	enum ATTACK_MOVE_TYPE
	{
		ATTACK_CHARGE,	// 突進前の溜め
		ATTACK_TACKLE,	// 突進
	};
public:
	// ===プロトタイプ宣言===
	CSlime_2();
	CSlime_2(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_2();
	void Update(tagTransform3d playerTransform) override;
	void NormalMove(tagTransform3d playerTransform) override;

	void SetNormalSpeed() override;
private:
	ATTACK_MOVE_TYPE m_AtcMoveType;
	int m_nChargeCnt;
	int m_nTackleCnt;
};


#endif __SLIME_2__H__