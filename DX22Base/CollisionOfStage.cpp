/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージの当たり判定処理実装
	---------------------------------------
	CollisionOfStage.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/11/29 ヒットストップ仕様変更対応 takagi
	・2023/11/30 ヒットストップをハンマー激突時に変更 takagi
	・2023/12/01 ハンマーとスライムの当たり判定持にSEを再生 yamashita
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2023/12/15 SEの変数を削除 yamashita

========================================== */

// =============== インクルード ===================
#include "Stage.h"	//自身のヘッダ
#include "GameParameter.h"
#include "HitStop.h"	//ヒットストップ
#include "Slime_4.h"	//赤スライム種分けよう
#include <typeinfo.h>	//typeid使用

// =============== 定数定義 =======================
const float HAMMER_HIT_MOVE_SPEED = 1.0f;		// ハンマーに吹き飛ばされた時のスピード
const float HIT_HAMMER_VOLUME = 0.3f;

/* ========================================
   当たり判定まとめ関数
   ----------------------------------------
   内容：Stage当たり判定をまとめる関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::Collision()
{
	// =============== ヒットストップ検査 ===================
	if (!CHitStop::IsStop())	//ヒットストップ時処理しない
	{
		PlayerSlimeCollision();
		PlayerBossCollision();
		HammerSlimeCollision();
		HammerBossCollision();
		SlimeSlimeCollision();
		SlimeBossCollision();
		BossSlimeCollision();
		BossBossCollision();
	}
	ExplosionSlimeCollision();
	ExplosionBossCollision();
	BossBossNormalMoveCollision();
	SlimeBossNormalMoveCollision();
	BossSlimeNormalMoveCollision();
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
void CStage::PlayerSlimeCollision()
{
	if (m_pPlayer->GetCollide()) return;	//	無敵時間の時はスルー

	// スライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// スライム情報

		if (pSlimeNow == nullptr)				continue;	// 無効なスライムはスルー

		// スライムとハンマーが衝突した場合
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetSphere(), pSlimeNow->GetSphere(), m_pPlayer->GetPos(), pSlimeNow->GetPos()))
		{
			m_pPlayer->Damage(pSlimeNow->GetAttack());
			return;
		}
	}
}
/* ========================================
   プレイヤーボス当たり判定関数
   ----------------------------------------
   内容：プレイヤーとボスが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::PlayerBossCollision()
{
	if (m_pPlayer->GetCollide()) return;	//	無敵時間の時はスルー

// ボススライム
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossNow = m_pSlimeMng->GetBossSlimePtr(i);	// スライム情報

		if (pBossNow == nullptr)				continue;	// 無効なスライムはスルー

		// ボスとハンマーが衝突した場合
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetSphere(), pBossNow->GetSphere(), m_pPlayer->GetPos(), pBossNow->GetPos()))
		{
			m_pPlayer->Damage(pBossNow->GetAttack());
			return;
		}
	}
}

/* ========================================
   回復アイテム当たり判定関数
   ----------------------------------------
   内容：回復アイテムとプレイヤーの当たり判定
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::PlayerHealItemCollision()
{
	std::vector<CHealItem*>* pHealItemList = m_pHealItemMng->GetHealItemConPtr();
	if (pHealItemList->size() == 0) { return; }	//中身が空ならスキップ

	for (auto i = pHealItemList->begin(); i != pHealItemList->end();)
	{
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetSphere(), (*i)->GetSphere(), m_pPlayer->GetPos(), (*i)->GetPos()))
		{
			delete (*i);
			i = pHealItemList->erase(i);	//アイテムの消去
			m_pPlayer->Healing();		//プレイヤーのHPの回復
		}
		else
		{
			i++;	//アイテムが機内場合はイテレータを進める
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
void CStage::HammerSlimeCollision()
{
	CHammer* playerHammer = m_pPlayer->GetHammerPtr();	// プレイヤーのハンマー

	if (m_pPlayer->GetAttackFlg() == false) return;	// ハンマー攻撃してない場合は返す

	// スライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// スライム情報

		if (pSlimeNow == nullptr)				continue;	// 無効なスライムはスルー
		if (pSlimeNow->GetHitMoveFlg() == true)	continue; 	// 吹飛状態のスライムはスルー

		// スライムとハンマーが衝突した場合
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pSlimeNow->GetSphere(), playerHammer->GetPos(), pSlimeNow->GetPos()))
		{
			//赤スライムと激突したときだけヒットストップの時間を長くする
			if (typeid(CSlime_4) == typeid(*pSlimeNow))
			{
				CHitStop::UpFlag(CHitStop::E_BIT_FLAG_STOP_NORMAL);	//ヒットストップ
			}
			else
			{
				CHitStop::UpFlag(CHitStop::E_BIT_FLAG_STOP_SOFT);	//ヒットストップ
			}
			float fAngleSlime
				= m_pPlayer->GetTransform().Angle(pSlimeNow->GetTransform());	// スライムが飛ぶ角度を取得

			pSlimeNow->HitMoveStart(HAMMER_HIT_MOVE_SPEED, fAngleSlime);	// スライムを飛ばす
			m_pPlayer->PlaySE(CPlayer::SE_HIT_HAMMER, HIT_HAMMER_VOLUME);	//ハンマーとスライムの接触SEを再生
		}
	}
}
/* ========================================
   ハンマーボス当たり判定関数
   ----------------------------------------
   内容：ハンマーとボスが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::HammerBossCollision()
{
	CHammer* playerHammer = m_pPlayer->GetHammerPtr();	// プレイヤーのハンマー

	if (m_pPlayer->GetAttackFlg() == false) return;	// ハンマー攻撃してない場合は返す

	// ボススライム
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossNow = m_pSlimeMng->GetBossSlimePtr(i);	// スライム情報

		if (pBossNow == nullptr)				continue;	// 無効なスライムはスルー
		if (pBossNow->GetHitMoveFlg() == true)	continue; 	// 吹飛状態のスライムはスルー

		// スライムとハンマーが衝突した場合
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pBossNow->GetSphere(), playerHammer->GetPos(), pBossNow->GetPos()))
		{
			CHitStop::UpFlag(CHitStop::E_BIT_FLAG_STOP_NORMAL);	//ヒットストップ
			float fAngleSlime
				= m_pPlayer->GetTransform().Angle(pBossNow->GetTransform());	// スライムが飛ぶ角度を取得

			pBossNow->HitMoveStart(HAMMER_HIT_MOVE_SPEED, fAngleSlime);	// スライムを飛ばす
			m_pPlayer->PlaySE(CPlayer::SE_HIT_HAMMER, HIT_HAMMER_VOLUME);	//ハンマーとスライムの接触SEを再生
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
void CStage::SlimeSlimeCollision()
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
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pSlimeTarget->GetSphere(), pSlimeFly->GetPos(), pSlimeTarget->GetPos()))
			{

				m_pSlimeMng->HitBranch(i, j, m_pExplosionMng);	// 爆発処理、結合処理(スライム同士の情報によって処理を変える)
				break;
			}
		}
	}
}

/* ========================================
   スライム→ボスの当たり判定関数(吹飛状態)
   ----------------------------------------
   内容：スライムからボスに衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::SlimeBossCollision()
{
	// 衝突するスライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeFly = m_pSlimeMng->GetSlimePtr(i);	// 衝突するスライムのポインタ

		if (pSlimeFly == nullptr)					continue;	// 無効なスライムはスルー
		if (pSlimeFly->GetHitMoveFlg() == false)	continue; 	// 通常状態のスライムはスルー

		// 衝突されるボス
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pBossTarget = m_pSlimeMng->GetBossSlimePtr(j);	// 衝突されるスライムのポインタ

			if (pBossTarget == nullptr)					continue;	// 無効なスライムはスルー
			if (pBossTarget->GetHitMoveFlg() == true)	continue; 	// 通常状態のスライムはスルー

			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pBossTarget->GetSphere(), pSlimeFly->GetPos(), pBossTarget->GetPos()))
			{

				m_pSlimeMng->HitSlimeBossBranch(i, j, m_pExplosionMng);	// 爆発処理、結合処理(スライム同士の情報によって処理を変える)
				break;
			}
		}
	}
}
/* ========================================
   ボス→スライム当たり判定関数(吹飛状態)
   ----------------------------------------
   内容：ボスとスライムが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::BossSlimeCollision()
{
	// 衝突するボス
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossFly = m_pSlimeMng->GetBossSlimePtr(i);	// 衝突するスライムのポインタ

		if (pBossFly == nullptr)					continue;	// 無効なスライムはスルー
		if (pBossFly->GetHitMoveFlg() == false)		continue; 	// 通常状態のスライムはスルー

		// 衝突されるスライム
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// 衝突されるスライムのポインタ

			if (pSlimeTarget == nullptr)				continue;	// 無効なスライムはスルー
			if (pSlimeTarget->GetHitMoveFlg() == true)	continue; 	// 通常状態のスライムはスルー


			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pBossFly->GetSphere(), pSlimeTarget->GetSphere(), pBossFly->GetPos(), pSlimeTarget->GetPos()))
			{

				m_pSlimeMng->HitBossSlimeBranch(i, j, m_pExplosionMng);	// 爆発処理、結合処理(スライム同士の情報によって処理を変える)
				break;
			}
		}

	}
}
/* ========================================
   ボス同士当たり判定関数(吹飛状態)
   ----------------------------------------
   内容：ボスとボスが衝突した際に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::BossBossCollision()
{
	// 衝突するボス
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossFly = m_pSlimeMng->GetBossSlimePtr(i);	// 衝突するスライムのポインタ

		if (pBossFly == nullptr)					continue;	// 無効なスライムはスルー
		if (pBossFly->GetHitMoveFlg() == false)		continue; 	// 通常状態のスライムはスルー

		// 衝突されるボス
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pBossTarget = m_pSlimeMng->GetBossSlimePtr(j);	// 衝突されるスライムのポインタ

			if (pBossTarget == nullptr)					continue;	// 無効なスライムはスルー
			if (i == j)									continue;	// 自分と同じスライムはスルー
			if (pBossTarget->GetHitMoveFlg() == true)	continue; 	// 通常状態のスライムはスルー


			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pBossFly->GetSphere(), pBossTarget->GetSphere(), pBossFly->GetPos(), pBossTarget->GetPos()))
			{

				m_pSlimeMng->HitBossBossBranch(i, j, m_pExplosionMng);	// 爆発処理、結合処理(スライム同士の情報によって処理を変える)
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
void CStage::ExplosionBossCollision()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; ++i)    // 爆発
	{
		CExplosion* pExplosion = m_pExplosionMng->GetExplosionPtr(i);    // 衝突する爆発のポインタ
		if (pExplosion == nullptr) { continue; }    // 未使用の爆発はスルー

		for (int j = 0; j < MAX_BOSS_SLIME_NUM; ++j)    // スライム
		{
			CSlime_BossBase* pBossTarget = m_pSlimeMng->GetBossSlimePtr(j);    // 衝突されるスライムのポインタ

			if (pBossTarget == nullptr)    continue;    // 無効なスライムはスルー

			if (m_pCollision->CheckCollisionSphere(pExplosion->GetSphere(), pBossTarget->GetSphere(), pExplosion->GetPos(), pBossTarget->GetPos()))
			{
				m_pSlimeMng->TouchBossExplosion(j, m_pExplosionMng, i);// スライムの爆発処理
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
void CStage::ExplosionSlimeCollision()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; ++i)	// 爆発
	{
		CExplosion* pExplosion = m_pExplosionMng->GetExplosionPtr(i);	// 衝突する爆発のポインタ
		if (pExplosion == nullptr) { continue; }	// 未使用の爆発はスルー

		for (int j = 0; j < MAX_SLIME_NUM; ++j)	// スライム
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// 衝突されるスライムのポインタ

			if (pSlimeTarget == nullptr)	continue;	// 無効なスライムはスルー

			if (m_pCollision->CheckCollisionSphere(pExplosion->GetSphere(), pSlimeTarget->GetSphere(), pExplosion->GetPos(), pSlimeTarget->GetPos()))
			{
				m_pSlimeMng->TouchExplosion(j, m_pExplosionMng, pExplosion->GetComboNum());// スライムの爆発処理
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
void CStage::SlimeSlimeNormalMoveCollision()
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

			//if (int(pStandSlime->GetSlimeLevel()) < int(pMoveSlime->GetSlimeLevel())) continue;
			// スライム同士が衝突した場合(青、緑、炎)
			if (int(pStandSlime->GetSlimeLevel()) <= 3 && int(pMoveSlime->GetSlimeLevel()) <= 3)
			{
				if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandSlime->GetSphere(), pMoveSlime->GetPos(), pStandSlime->GetPos()))
				{
					m_pSlimeMng->PreventSlimeSlimeOverlap(pMoveSlime, pStandSlime);	//スライムの位置を押し戻す処理

					break;
				}
			}
			else
			{//（黄色または赤のどちらかがはいってたらこっち）
				if (int(pStandSlime->GetSlimeLevel()) < int(pMoveSlime->GetSlimeLevel())) continue;
				if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandSlime->GetSphere(), pMoveSlime->GetPos(), pStandSlime->GetPos()))
				{
					m_pSlimeMng->PreventSlimeSlimeOverlap(pMoveSlime, pStandSlime);	//スライムの位置を押し戻す処理

					break;
				}
			}
		}
	}
}
/* ========================================
   スライム→ボス重複防止関数
   ----------------------------------------
   内容：スライムからボスが通常移動で重ならないようにする関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::SlimeBossNormalMoveCollision()
{
	// 衝突するスライム
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pMoveSlime = m_pSlimeMng->GetSlimePtr(i);	//移動するスライムのポインタ

		if (pMoveSlime == nullptr)					continue;	// 無効なスライムはスルー
		if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// 吹き飛び中のスライムはスルー

		// 衝突されるボス
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pStandBoss = m_pSlimeMng->GetBossSlimePtr(j);	// 止まっているスライムのポインタ

			if (pStandBoss == nullptr)					continue;	// 無効なスライムはスルー
			if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// 吹き飛び中のスライムはスルー

			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandBoss->GetSphere(), pMoveSlime->GetPos(), pStandBoss->GetPos()))
			{
				m_pSlimeMng->PreventSlimeBossOverlap(pMoveSlime, pStandBoss);	//スライムの位置を押し戻す処理


				break;
			}
		}

	}
}
/* ========================================
   ボス→スライム重複防止関数
   ----------------------------------------
   内容：ボスからスライムが通常移動で重ならないようにする関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::BossSlimeNormalMoveCollision()
{
	// 衝突するボス
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pMoveBoss = m_pSlimeMng->GetBossSlimePtr(i);	//移動するスライムのポインタ

		if (pMoveBoss == nullptr)					continue;	// 無効なスライムはスルー
		if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// 吹き飛び中のスライムはスルー

		// 衝突されるスライム
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pStandSlime = m_pSlimeMng->GetSlimePtr(j);	// 止まっているスライムのポインタ

			if (pStandSlime == nullptr)					continue;	// 無効なスライムはスルー
			if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// 吹き飛び中のスライムはスルー

			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pMoveBoss->GetSphere(), pStandSlime->GetSphere(), pMoveBoss->GetPos(), pStandSlime->GetPos()))
			{
				m_pSlimeMng->PreventBossSlimeOverlap(pMoveBoss, pStandSlime);	//スライムの位置を押し戻す処理


				break;
			}
		}

	}
}
/* ========================================
   ボス→ボス重複防止関数
   ----------------------------------------
   内容：ボスからボスが通常移動で重ならないようにする関数
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CStage::BossBossNormalMoveCollision()
{
	// 衝突するボス
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pMoveBoss = m_pSlimeMng->GetBossSlimePtr(i);	//移動するスライムのポインタ

		if (pMoveBoss == nullptr)					continue;	// 無効なスライムはスルー
		if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// 吹き飛び中のスライムはスルー

		// 衝突されるボス
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pStandBoss = m_pSlimeMng->GetBossSlimePtr(j);	// 止まっているスライムのポインタ

			if (pStandBoss == nullptr)					continue;	// 無効なスライムはスルー
			if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// 吹き飛び中のスライムはスルー
			if (i == j)									continue;	// 自分と同じスライムはスルー

			// スライム同士が衝突した場合
			if (m_pCollision->CheckCollisionSphere(pMoveBoss->GetSphere(), pStandBoss->GetSphere(), pMoveBoss->GetPos(), pStandBoss->GetPos()))
			{
				m_pSlimeMng->PreventBossBossOverlap(pMoveBoss, pStandBoss);	//スライムの位置を押し戻す処理


				break;
			}
		}

	}
}
