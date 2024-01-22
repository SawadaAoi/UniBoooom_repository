/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	影表示用ソース
	---------------------------------------
	Shadow.cpp
	---------------------------------------
	作成者 nieda

	変更履歴
	・2023/11/27 制作 nieda
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修・MessageBox改善 takagi
	・2024/01/22 リファクタリング takagi

========================================== */

// =============== インクルード ===================
#include "Shadow.h"	// 自身のヘッダ

/* ========================================
   コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::CShadow()
{
	// =============== テクスチャ登録 ===================
	SetTexture("Assets/Texture/Shadow.png");	// 影テクスチャ読込
}

/* ========================================
   コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数1：大きさ
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::CShadow(float fScale)
   : CShadow::CShadow()
{
   m_Transform.fScale = { fScale ,fScale ,fScale };
}

/* ========================================
   デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::~CShadow()
{
}