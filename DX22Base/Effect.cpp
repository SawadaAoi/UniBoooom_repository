/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	エフェクト実装
	------------------------------------
	Effect.cpp
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

// =============== インクルード ===================
#include "Effect.h"	//自身のヘッダ



/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CEffect::CEffect()
	:m_pEmitterMng(nullptr)	//エミッター管理
{
}

/* ========================================
	コピーコンストラクタ
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const CEffect & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
CEffect::CEffect(const CEffect & Obj)
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
CEffect::~CEffect()
{
}