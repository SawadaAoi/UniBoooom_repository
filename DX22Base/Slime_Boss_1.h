/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライム1定義
	------------------------------------
	Slime_Boss_1.h
	------------------------------------
	作成者	suzumura

	変更履歴
	・2023/11/17 クラス作成 suzumura
	・2023/11/23 突撃処理の追加 suzumura
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SLIME_BOSS_1_H__	//Slime_Boss_1.hインクルードガード
#define __SLIME_BOSS_1_H__

// =============== インクルード ===================
#include "Slime_BossBase.h"

// =============== 列挙定義 ===================
enum E_BOSS_1_STATE
{
	NORMAL = 0,
	CHARGE,
	ASSAULT
};

// =============== クラス定義 =====================
class CSlime_Boss_1 :
	public CSlime_BossBase
{
public:
	// ===プロトタイプ宣言===
	CSlime_Boss_1();
	CSlime_Boss_1(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_Boss_1();

	void Update() override;

	void NormalMove() override;
	void SetNormalSpeed() override;
	void SetMaxHp() override;

	void Charge(TPos3d<float> playerPos, TPos3d<float> movePos);	// 溜め関数
	void Assault();	// 突撃関数

private:
	void ResetAssault();
	// ===メンバ変数===
	int m_nFrame;		// Update内で扱うフレーム


	float m_assaultDistancePlayer;	// 突撃時のプレイヤー間の距離を保存
	TPos3d<float> m_assaultMovePos;	// 突撃時のMovePosを保存
};


#endif	//!__SLIME_BOSS_1_H__