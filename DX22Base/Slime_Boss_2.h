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
		MOVE_NORMAL = 0,
		MOVE_JUMP,
		MOVE_TARGET_SHADOW,
		MOVE_DROP,

		MOVE_MAX,
	};
public:
	// ===プロトタイプ宣言===
	CSlime_Boss_2();
	CSlime_Boss_2(TPos3d<float> pos, VertexShader* pVS, Model* pModel1, Model* pModel2);
	~CSlime_Boss_2();

	void Update(tagTransform3d playerTransform) override;
	void NormalMove(tagTransform3d playerTransform) override;

	void MoveJump();
	void MoveTargetShadow();
	void MoveDrop();

	void SetNormalSpeed() override;
	void SetMaxHp() override;


private:
	// ===メンバ変数===
	int m_nMoveCnt[MOVE_MAX];		// 移動処理のフレーム加算値



	float m_assaultDistancePlayer;	// 突撃時のプレイヤー間の距離を保存
	TPos3d<float> m_assaultMovePos;	// 突撃時のMovePosを保存
	Model* m_StateModels[2];
};


#endif //__SLIME_BOSS_2__H__
