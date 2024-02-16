/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	汗エフェクト管理用cpp
	---------------------------------------
	SweatEffectManager.cpp

	作成者	鄭 宇恩

	変更履歴
	・2024/02/02 SweatEffectManagerクラス作成 Tei
	・2024/02/13 カメラ削除 takagi

========================================== */

// =============== インクルード ===================
#include "SweatEffectManager.h"

// =============== 定数定義 =======================
const float TOTAL_SWEAT_EFFECT_TIME = 0.75f * 60.0f;

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CSweatEffectManager::CSweatEffectManager()
{
	// 汗エフェクト配列の初期化
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		m_pSweatEffect[i] = nullptr;
	}
	//エフェクト初期化
	m_SweatEffect = LibEffekseer::Create("Assets/Effect/sweat/HEW_sweat.efkefc");
}

/* ========================================
	関数：デストラクタ
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CSweatEffectManager::~CSweatEffectManager()
{
	// メモリ削除
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		SAFE_DELETE(m_pSweatEffect[i]);
	}
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：汗エフェクトマネージャーの更新処理
	-------------------------------------
	引数1：座標
	-------------------------------------
	戻値：なし
=========================================== */
void CSweatEffectManager::Update(TTriType<float> pos)
{
	// 汗エフェクトを検索
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// 未使用の汗エフェクトはスルー
		if (m_pSweatEffect[i] == nullptr) continue;
		m_pSweatEffect[i]->Update(pos);
	}
	DeleteCheck();	// 削除チェック
}

/* ========================================
	関数：描画関数
	----------------------------------------
	内容：汗エフェクトマネージャーの描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSweatEffectManager::Draw()
{
	// 汗エフェクトの検索
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// 未使用の汗エフェクトはスルー
		if (m_pSweatEffect[i] == nullptr) continue;

		m_pSweatEffect[i]->Draw(); // 汗エフェクトの描画

	}
}

/* ========================================
	生成処理関数
	-------------------------------------
	内容：汗エフェクトの生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：生成角度(x,y,z)
	-------------------------------------
	戻値：なし
=========================================== */
void CSweatEffectManager::Create(TTriType<float> pos,  TTriType<float> radian)
{
	// 汗エフェクトを検索
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// 使用済みの汗エフェクトはスルー
		if (m_pSweatEffect[i] != nullptr) continue;
		// 座標、角度、エフェクト時間、Effekseerファイル、カメラを指定して生成
		m_pSweatEffect[i] = new CSweatEffect(pos, radian, TOTAL_SWEAT_EFFECT_TIME, m_SweatEffect);
	}
		

}

/* ========================================
	汗エフェクト削除関数
	----------------------------------------
	内容：汗エフェクトが生成したらチェックしてから削除
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSweatEffectManager::DeleteCheck()
{
	// 汗エフェクトを検索
	for (int i = 0; i < MAX_SWEAT_EFFECT_NUM; i++)
	{
		// 未使用の汗エフェクトはスルー
		if (m_pSweatEffect[i] == nullptr) continue;
		// 削除フラグがたってない汗エフェクトはスルー
		if (m_pSweatEffect[i]->GetDelFlg() == false) continue;

		SAFE_DELETE(m_pSweatEffect[i]);	// 汗エフェクトを削除する
	}

}


