/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライム2.cpp
	------------------------------------
	Slime_Boss_2.cpp
	------------------------------------
	作成者	澤田蒼生

	変更履歴
	・2023/12/12 クラス作成 Sawada

========================================== */


// =============== インクルード ===================
#include "Slime_Boss_2.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
							

#endif
const float BOSS_2_SCALE = 6.0f;					// ボス１の大きさ
const float BOSS_2_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// ボス１のスピード
const int	BOSS_2_MAX_HP = 100;					// ボス１の最大HP
const float BOSS_2_SHADOW_SCALE = 12.0f;		// ボス１の影の大きさ


CSlime_Boss_2::CSlime_Boss_2()
{
	m_nMoveState = MOVE_STATE::MOVE_NORMAL;
	m_Transform.fScale = { BOSS_2_SCALE,BOSS_2_SCALE ,BOSS_2_SCALE };
	m_Sphere.fRadius *= BOSS_2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_BOSS;
	SetNormalSpeed();
	SetMaxHp();
	m_nHp = m_nMaxHp;
	m_nAttack = BOSS_1_ATTACK;
	m_fScaleShadow = BOSS_2_SHADOW_SCALE;	// 影の大きさを設定

	for (int i = 0; i < MOVE_STATE::MOVE_MAX; i++)m_nMoveCnt[i] = 0;
}

CSlime_Boss_2::CSlime_Boss_2(TPos3d<float> pos, VertexShader * pVS, Model * pModel1, Model * pModel2)
{
}

CSlime_Boss_2::~CSlime_Boss_2()
{
}

void CSlime_Boss_2::Update(tagTransform3d playerTransform)
{
	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		NormalMove(playerTransform);	// 通常行動処理
	}
	else
	{
		// チャージ中にぶっ飛ばされたらクールタイム等をリセット
		if (m_nMoveState == CHARGE)
		{
			HitMove();		// 敵の吹き飛び移動
			ResetAssault();	// 突撃リセット
		}

		// 突撃状態は"吹き飛び"を考慮しない
		if (m_nMoveState == ASSAULT)
		{
			m_bHitMove = false;
		}
		else
		{
			HitMove(); //敵の吹き飛び移動
		}
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.z += m_move.z;

	// ダメージ発生中じゃないなら点滅処理を行わない
	if (m_bFlash == false) return;
	// 点滅処理
	m_nInvFrame++;						//毎フレームでカウントを追加
	if (0 == m_nInvFrame % BOSS_DAMAGE_FLASH_FRAME)
	{
		// 描画するかしない切り替え
		if (m_bDrawFlg)
		{
			m_bDrawFlg = false;	// true→false
		}
		else
		{
			m_bDrawFlg = true;	// false→true
		}

	}
	// 総点滅時間を過ぎたら終了
	if (m_nInvFrame >= BOSS_DAMAGE_FLASH_TOTAL_FRAME)
	{
		m_bFlash = false;
		m_nInvFrame = 0;
		m_bDrawFlg = true;
	}
}

void CSlime_Boss_2::NormalMove(tagTransform3d playerTransform)
{
}

void CSlime_Boss_2::MoveJump()
{
}

void CSlime_Boss_2::MoveTargetShadow()
{
}

void CSlime_Boss_2::MoveDrop()
{
}

/* ========================================
	スピード決定関数
	-------------------------------------
	内容：スライムの移動速度を設定
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::SetNormalSpeed()
{
	m_fSpeed = BOSS_2_SPEED;	//移動速度に定数をセット
}

/* ========================================
	マックスHP決定関数
	-------------------------------------
	内容：スライムのMAXHPを設定
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::SetMaxHp()
{
	m_nMaxHp = BOSS_2_MAX_HP;
}
