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
	・2023/11/20 Damage、IsDead関数を追加 Suzumura
	・2023/11/23 MaxHp関係を追加 Suzumura

========================================== */
#ifndef __SLIME_BOSS_BASE__H__
#define __SLIME_BOSS_BASE__H__

// =============== インクルード ===================
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CSlime_BossBase :
	public CSlimeBase
{
public:
	// ===プロトタイプ宣言======
	CSlime_BossBase();
	~CSlime_BossBase();


	void Warp(TPos3d<float> playerPos);	// ワープ関数 TODO:未実装

	void Damage(int num);		// ダメージ関数
	bool IsDead();				// 死んでいるかどうか

	virtual void SetMaxHp() = 0;

protected:
	// ===メンバ変数======
	int m_nMaxHp;	//最大HPはボスによって変更したいためprotectedに

private:

	int m_nHp;
	bool m_bDead;
};


#endif //__SLIME_BOSS_BASE__H__
