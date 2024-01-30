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
	・2023/11/23 Hp関係を追加 Suzumura
	・2023/11/23 点滅処理実装 Suzumura
	・2023/11/27 HPテクスチャ追加 Suzumura
========================================== */
#ifndef __SLIME_BOSS_BASE__H__
#define __SLIME_BOSS_BASE__H__

// =============== インクルード ===================
#include "SlimeBase.h"
#include "GameParameter.h"		//定数定義用ヘッダー
// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const int BOSS_DAMAGE_FLASH_FRAME = 0.1 * 60;		// ダメージ受けた際の点滅フレーム(無敵ではない)
const int BOSS_DAMAGE_FLASH_TOTAL_FRAME = 0.5 * 60;	// ダメージを受けた際の点滅を何フレーム行うか
#endif

// =============== クラス定義 =====================
class CSlime_BossBase :
	public CSlimeBase
{
public:
	// ===== 列挙 =====
	enum ROCK_SLIME_MOTION	// 岩スライムのモーション
	{
		ROCK_SLIME_MOVE,	// 移動
		ROCK_SLIME_HIT,		// 叩かれたとき
		ROCK_SLIME_ROLLING,	// 回転攻撃

		ROCK_SLIME_MAX,
	};

	// ===プロトタイプ宣言======
	CSlime_BossBase();
	~CSlime_BossBase();

	virtual void Update(tagTransform3d playerTransform);
	void Draw() override;

	void Warp(TPos3d<float> playerPos);	// ワープ関数 TODO:未実装

	void Damage(int num);		// ダメージ関数
	bool IsDead();				// 死んでいるかどうか
	virtual void SetMaxHp() = 0;

	int GetMoveState();

protected:
	// ===メンバ変数======
	int m_nMoveState;	// 継承先の各Bossで列挙型を作って入れる(共通で0は通常)

	int m_nMaxHp;		// 最大HPはボスによって変更したいためprotectedに
	int m_nHp;			// 現HP

	int m_nInvFrame;	// 点滅で扱うフレーム
	bool m_bDrawFlg;	// 描画を行うかどうかのフラグ
	bool m_bFlash;		// ダメージを受けて一定時間点滅させるためのフラグ

	bool m_bDead;		// 死んでいるかどうか
	Texture* m_pBossHpTexture;
	Texture* m_pHpFrameTexture;
private:
};


#endif //__SLIME_BOSS_BASE__H__
