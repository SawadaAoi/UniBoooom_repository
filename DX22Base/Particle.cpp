/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	パーティクル実装
	------------------------------------
	Particle.cpp
	------------------------------------
	作成者 takagi

	変更履歴
	・2023/11/09 作成 takagi

========================================== */

// =============== インクルード ===================
#include "Particle.h"	//自身のヘッダ



/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CParticle::CParticle()
	:m_pCamera(nullptr)	//カメラ
{
}

/* ========================================
	コピーコンストラクタ
	-------------------------------------
	内容：コピー時に行う処理
	-------------------------------------
	引数1：const CParticle & Obj：コピー元の参照
	-------------------------------------
	戻値：なし
=========================================== */
CParticle::CParticle(const CParticle & Obj)
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
CParticle::~CParticle()
{
}

/* ========================================
	カメラ取得関数
	-------------------------------------
	内容：カメラを取得する
	-------------------------------------
	引数1：const CCamera* pCamera：使いたいカメラのアドレス
	-------------------------------------
	戻値：なし
=========================================== */
void CParticle::GetCamera(const CCamera* pCamera)
{
	// =============== 格納 ===================
	m_pCamera = pCamera;	//カメラのアドレスを格納
}