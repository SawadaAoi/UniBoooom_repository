/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スコア管理用cpp
	---------------------------------------
	ScoreManager.cpp

	作成者	山本凱翔

	変更履歴
	・2023/11/18　作成

========================================== */

// =============== インクルード ===================
#include "ScoreManager.h"
#include "GameParameter.h"
#include "Sphere.h"				//球定義ヘッダー　なんでか分からんけど付けたらましになる

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CScoreManager::CScoreManager()
{
	// スコア配列の初期化
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		m_pScore[i] = nullptr;
	}
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
CScoreManager::~CScoreManager()
{
	// メモリ削除
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		SAFE_DELETE(m_pScore[i]);
	}
}

void CScoreManager::Update()
{
}

void CScoreManager::Draw()
{
	// slimeの上に表示するスコアの検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 未使用のスコアはスルー
		if (m_pScore[i] == nullptr) continue;
	
		m_pScore[i]->Draw(); // 爆発の描画
	}

	//トータルスコアの表示

}

void CScoreManager::CreateScore(TTriType<float> pos,int score,float posY)
{
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScore(pos,score,posY);
	}
}

void CScoreManager::AddScore()
{

}
