/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	エミッター管理定義
	------------------------------------
	EmitterManager.h
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

#ifndef __EMITER_MANAGER_H__
#define __EMITER_MANAGER_H__

// =============== インクルード ===================
#include "Emitter.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CEmitterManager
{
protected:
	// ===メンバ変数宣言=====
	//pos定義	//エフェクトの中心位置
	CEmitter* m_pEmitter;	//エミッター
public:
	// ===プロトタイプ宣言===
	CEmitterManager();								//コンストラクタ
	CEmitterManager(const CEmitterManager& Obj);	//コピーコンストラクタ
	~CEmitterManager();								//デストラクタ
};	//エミッター管理

#endif	//!__EMITER_MANAGER_H__