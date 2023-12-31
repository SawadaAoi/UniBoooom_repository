/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	クアッドパーティクル(四角の2dポリゴン、ビルボードを使用する)実装
	------------------------------------
	QuadParticle.cpp
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

// =============== インクルード ===================
#include "QuadParticle.h"	//自身のヘッダ



/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CQuadParticle::CQuadParticle()
{
}

/* ========================================
	コピーコンストラクタ
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const CQuadParticle & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
CQuadParticle::CQuadParticle(const CQuadParticle & Obj)
{
}

/* ========================================
	デストラクタ
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CQuadParticle::~CQuadParticle()
{
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CQuadParticle::Draw()
{
	//TODO:逆行列使ってビルボード化して描画する
}