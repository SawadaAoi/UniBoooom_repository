/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	SceneGame内当たり判定用cpp
	------------------------------------
	SceneGameCollision.cpp
	------------------------------------
	作成者 仁枝潤哉

	変更履歴
	・2023/11/07 新規作成 Nieda
	・2023/11/08 コメント修正	Nieda
	・2023/11/12 スライム同士重複防止関数追加	Yamashita

========================================== */

// =============== インクルード ===================
#include "SceneGame.h"
#include "GameParameter.h"

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float HAMMER_HIT_MOVE_SPEED = 1.0f;		// ハンマーに飛ばされた時のスピード

#endif 

// =============== プロトタイプ宣言 ===============

// =============== グローバル変数定義 =============


/* ========================================
   シーンゲーム当たり判定まとめ関数
   ----------------------------------------
   内容：SceneGame当たり判定をまとめる関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void SceneGame::SceneGameCollision()
{
	PlayerSlimeCollision();
	HammerSlimeCollision();
	SlimeSlimeCollision();
	ExplosionSlimeCollision();
	SlimeSlimeNormalMoveCollision();
}

/* ========================================
   プレイヤースライム当たり判定関数
   ----------------------------------------
   内容：プレイヤーとスライムが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void SceneGame::PlayerSlimeCollision()
{
	if (m_pPlayer->GetCollide()) return;	//	無敵時間の時はスルー

	// スライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// スライム情報

		if (pSlimeNow == nullptr)				continue;	// 無効なスライムはスルー

		// スライムとハンマーが衝突した場合
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetPlayerSphere(), pSlimeNow->GetSphere()))
		{
			m_pPlayer->Damage();
		}
	}
}

/* ========================================
   ハンマースライム当たり判定関数
   ----------------------------------------
   内容：ハンマーとスライムが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void SceneGame::HammerSlimeCollision()
{
	CHammer* playerHammer = m_pPlayer->GetHammer();	// プレイヤーのハンマー

	if (m_pPlayer->GetHammerFlg() == false) return;	// ハンマー攻撃してない場合は返す

	// スライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// スライム情報

		if (pSlimeNow == nullptr)				continue;	// 無効なスライムはスルー
		if (pSlimeNow->GetHitMoveFlg()==true)	continue; 	// 吹飛状態のスライムはスルー

		// スライムとハンマーが衝突した場合
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pSlimeNow->GetSphere()))
		{
			float fAngleSlime
				= m_pPlayer->GetPlayerSphere().Angle(pSlimeNow->GetSphere());	// スライムが飛ぶ角度を取得

			pSlimeNow->HitMoveStart(HAMMER_HIT_MOVE_SPEED,fAngleSlime);	// スライムを飛ばす
		}
	}
}

/* ========================================
   スライム同士当たり判定関数(吹飛状態)
   ----------------------------------------
   内容：スライムとスライムが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void SceneGame::SlimeSlimeCollision()
{
	// 衝突するスライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeFly = m_pSlimeMng->GetSlimePtr(i);	// 衝突するスライムのポインタ

		if (pSlimeFly == nullptr)					continue;	// 無効なスライムはスルー
		if (pSlimeFly->GetHitMoveFlg() == false)	continue; 	// 通常状態のスライムはスルー

		// 衝突されるスライム
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// 衝突されるスライムのポインタ

			if (pSlimeTarget == nullptr)	continue;	// 無効なスライムはスルー
			if (i == j)						continue;	// 自分と同じスライムはスルー
			if (pSlimeTarget->GetHitMoveFlg() == true)	continue; 	// 通常状態のスライムはスルー


			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pSlimeTarget->GetSphere()))
			{

				m_pSlimeMng->HitBranch(i, j,m_pExplosionMng);	// 爆発処理、結合処理(スライム同士の情報によって処理を変える)
				break;
			}
		}

	}
}

/* ========================================
   爆発スライム当たり判定関数
   ----------------------------------------
   内容：爆発とスライムが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void SceneGame::ExplosionSlimeCollision()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; ++i)	// 爆発
	{
		CExplosion* pExplosion = m_pExplosionMng->GetExplosionPtr(i);	// 衝突する爆発のポインタ
		if (pExplosion == nullptr) { continue; }	// 未使用の爆発はスルー

		for (int j = 0; j < MAX_SLIME_NUM; ++j)	// スライム
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// 衝突されるスライムのポインタ

			if (pSlimeTarget == nullptr)	continue;	// 無効なスライムはスルー

			if (m_pCollision->CheckCollisionSphere(pExplosion->GetSphere(), pSlimeTarget->GetSphere()))
			{
				m_pSlimeMng->TouchExplosion(j, m_pExplosionMng);// スライムの爆発処理
				break;
			}
		}

	}
}

/* ========================================
   スライム同士重複防止関数
   ----------------------------------------
   内容：スライム同士が通常移動で重ならないようにする関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void SceneGame::SlimeSlimeNormalMoveCollision()
{
	// 衝突するスライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pMoveSlime = m_pSlimeMng->GetSlimePtr(i);	//移動するスライムのポインタ

		if (pMoveSlime == nullptr)					continue;	// 無効なスライムはスルー
		if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// 吹き飛び中のスライムはスルー

		// 衝突されるスライム
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pStandSlime = m_pSlimeMng->GetSlimePtr(j);	// 止まっているスライムのポインタ

			if (pStandSlime == nullptr)					continue;	// 無効なスライムはスルー
			if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// 吹き飛び中のスライムはスルー
			if (i == j)									continue;	// 自分と同じスライムはスルー

			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandSlime->GetSphere()))
			{
				m_pSlimeMng->PreventOverlap(pMoveSlime, pStandSlime);	//スライムの位置を押し戻す処理


				break;
			}
		}

	}
}