/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	エミッター管理実装
	------------------------------------
	EmitterManager.cpp
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

// =============== インクルード ===================
#include "EmitterManager.h"	//自身のヘッダ



/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CEmitterManager::CEmitterManager()
	:m_pEmitter(nullptr)	//エミッター
{
}

/* ========================================
	コピーコンストラクタ
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const CEmitterManager & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
CEmitterManager::CEmitterManager(const CEmitterManager & Obj)
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
CEmitterManager::~CEmitterManager()
{
}