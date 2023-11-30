/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライム.h
	------------------------------------
	Slime_Boss.h
	------------------------------------
	作成者	鈴村朋也

	変更履歴
	・2023/11/17 クラス作成 Suzumura
	・2023/11/23 突撃処理の追加 Suzumura

========================================== */
#ifndef __SLIME_BOSS_1__H__a
#define __SLIME_BOSS_1__H__

// =============== インクルード ===================
#include "Slime_BossBase.h"

// =============== 列挙定義 ===================
enum E_BOSS_1_STATE
{
	NORMAL,
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
	CSlime_Boss_1(TPos3d<float> pos, VertexShader* pVS, Model* pModel1, Model* pModel2);
	~CSlime_Boss_1();

	void Update(tagTransform3d playerTransform) override;

	void NormalMove(tagTransform3d playerTransform) override;
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
	Model* m_StateModels[2];
	E_BOSS_1_STATE m_eState;
};


#endif //__SLIME_BOSS_1__H__
