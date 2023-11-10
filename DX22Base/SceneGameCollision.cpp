/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	SceneGame内当たり判定用cpp
	------------------------------------
	SceneGameCollision.cpp
	------------------------------------
	作成者 仁枝潤哉

	変更履歴
	・2023/11/07 新規作成 仁枝潤哉
	・2023/11/08 HammerSlimeCollision関数
				 SlimeSlimeCollision関数
				 ExplosionSlimeCollision関数
				 内容追記	仁枝潤哉
========================================== */

// =============== インクルード ===================
#include "SceneGame.h"

// =============== 定数定義 =======================

// =============== プロトタイプ宣言 ===============

// =============== グローバル変数定義 =============


/* ========================================
   関数：SceneGameCollision関数
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
}

/* ========================================
   関数：PlayerSlimeCollision関数
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
	for (int i = 0; i < MAX_SLIME; i++)
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
   関数：HammerSlimeCollision関数
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
	for (int i = 0; i < MAX_SLIME; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// スライム情報

		if (pSlimeNow == nullptr)				continue;	// 無効なスライムはスルー
		if (pSlimeNow->GetHitMoveFlg()==true)	continue; 	// 吹飛状態のスライムはスルー

		// スライムとハンマーが衝突した場合
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pSlimeNow->GetSphere()))
		{
			float fAngleSlime
				= m_pPlayer->GetPlayerSphere().Angle(pSlimeNow->GetSphere());	// スライムが飛ぶ角度を取得

			pSlimeNow->HitMoveStart(1.0,fAngleSlime);	// スライムを飛ばす
		}
	}
}

/* ========================================
   関数：SlimeSlimeCollision関数
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
	for (int i = 0; i < MAX_SLIME; i++)
	{
		CSlimeBase* pSlimeFly = m_pSlimeMng->GetSlimePtr(i);	// 衝突するスライムのポインタ

		if (pSlimeFly == nullptr)					continue;	// 無効なスライムはスルー
		if (pSlimeFly->GetHitMoveFlg() == false)	continue; 	// 通常状態のスライムはスルー

		// 衝突されるスライム
		for (int j = 0; j < MAX_SLIME; j++)
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// 衝突されるスライムのポインタ

			if (pSlimeTarget == nullptr)	continue;	// 無効なスライムはスルー
			if (i == j)						continue;	// 自分と同じスライムはスルー

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
   関数：ExplosionSlimeCollision関数
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

		for (int j = 0; j < MAX_SLIME; ++j)	// スライム
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