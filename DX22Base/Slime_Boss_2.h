/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライム2.h
	------------------------------------
	Slime_Boss_2.h
	------------------------------------
	作成者	澤田蒼生

	変更履歴
	・2023/12/11 クラス作成 Sawada

========================================== */
#ifndef __SLIME_BOSS_2__H__
#define __SLIME_BOSS_2__H__

// =============== インクルード ===================
#include "Slime_BossBase.h"


// =============== クラス定義 =====================
class CSlime_Boss_2 :
	public CSlime_BossBase
{
public:
	// =============== 列挙定義 ===================
	enum MOVE_STATE
	{
		NORMAL = 0,
		JUMP_CHARGE,
		JUMP,
		TARGET_SHADOW,
		DROP,
		DROP_RIGID,

		MOVE_MAX,
	};
public:
	// ===プロトタイプ宣言===
	CSlime_Boss_2();
	CSlime_Boss_2(TPos3d<float> pos, VertexShader* pVS, AnimeModel* pModel);
	~CSlime_Boss_2();

	void Update(tagTransform3d playerTransform) override;



	void SetNormalSpeed() override;
	void SetMaxHp() override;

private:
	// ===プロトタイプ宣言===
	void MoveSwitch();
	void MoveNormal();
	void MoveJumpCharge();
	void MoveJump();
	void MoveTargetShadow();
	void MoveDrop();
	void MoveDropRigid();

	// ===メンバ変数===
	int m_nMoveCnt[MOVE_MAX];		// 移動処理のフレーム加算値
	bool m_nMoveFlg[MOVE_MAX];		// 移動処理のフレーム加算値
	tagTransform3d m_PlayerParam;


	float m_assaultDistancePlayer;	// 突撃時のプレイヤー間の距離を保存
	TPos3d<float> m_assaultMovePos;	// 突撃時のMovePosを保存
};


#endif //__SLIME_BOSS_2__H__
