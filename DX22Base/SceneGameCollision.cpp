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
	for (int i = 0; i < MAX_SLIME_1; ++i)	// 自分スライム
	{
		if (/*吹飛状態のスライムはスルー*/) { continue; }	// 吹飛状態のスライムはスルー
			// スライムとハンマーが当たっている場合
			if (m_pCollision->CheckCollisionSphere(/*ハンマー.スフィア, スライム[添え字].スフィア*/))
			{
				float fAngleSlime;  // スライムが飛ぶ角度を入れる変数
				fAngleSlime = 0.0f;//プレイヤー.スフィア.Angle(スライム[添え字].スフィア)
				//スライム[添え字].HitMoveStart(移動スピード、スライム吹飛角度)
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
	for (int i = 0; i < MAX_SLIME_1; ++i)	// 自分スライム
	{
		if (/*通常状態のスライムはスルー*/) { continue; }	// 通常状態のスライムはスルー

			for (int j = 0; j < MAX_SLIME_1; ++j)	// 相手スライム
			{
				if (i == j) { continue; }	// 自分スライムと相手スライムの添え字が同じ場合スルー
					if (m_pCollision->CheckCollisionSphere(
						//自分スライム[添え字].スフィア, 相手スライム[添え字].スフィア))
					{
						//HitBranch(自分スライムの[添え字]、相手スライムの[添え字])
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
		if (/*未使用の爆発はスルー*/) { continue; }	// 未使用の爆発はスルー

			for (int j = 0; j < MAX_SLIME_1; ++j)	// スライム
			{
				if (m_pCollision->CheckCollisionSphere(/*爆発[添え字].スフィア, スライム[添え字].スフィア*/))
				{
					//スライムマネージャーのスライムの爆発処理
				}
			}

	}
}