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

========================================== */

// =============== インクルード ===================
#include "SceneGameCollision.h"

// =============== 定数定義 =======================

// =============== プロトタイプ宣言 ===============

// =============== グローバル変数定義 =============


/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CSceneGameCollision::CSceneGameCollision()
{
	m_pCollision = new CCOLLISION();
}

/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CSceneGameCollision::~CSceneGameCollision()
{
	if (m_pCollision)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
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
void CSceneGameCollision::PlayerSlimeCollision()
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
void CSceneGameCollision::HammerSlimeCollision()
{

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
void CSceneGameCollision::SlimeSlimeCollision()
{

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
void CSceneGameCollision::ExplosionSlimeCollision()
{

}
