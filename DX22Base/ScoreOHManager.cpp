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
#include "ScoreOHManager.h"
#include "GameParameter.h"
#include "Sphere.h"				//球定義ヘッダー　なんでか分からんけど付けたらましになる
// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else

#endif
/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CScoreOHManager::CScoreOHManager()
	: m_pCamera(nullptr)
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
CScoreOHManager::~CScoreOHManager()
{
	// メモリ削除
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		SAFE_DELETE(m_pScore[i]);
	}
}

void CScoreOHManager::Update()
{
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 未使用の爆発はスルー
		if (m_pScore[i] == nullptr)
		{
			continue;

		}

		m_pScore[i]->Update();
	}

	DeleteCheck();	// 削除チェック
}

void CScoreOHManager::Draw()
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
/* ========================================
	生成処理関数（赤同士の最初の爆破時）
	-------------------------------------
	内容：頭上スコアの生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：スコア
	引数3：スコア表示位置
	-------------------------------------
	戻値：なし
=========================================== */
void CScoreOHManager::DisplayOverheadScore(TTriType<float> pos,int score,float height)
{
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScoreOverHead(pos,score, height, LEVEL_4_EXPLODE_TIME,false);
		m_pScore[i]->SetCamera(m_pCamera);
		break;
	}
}
/* ========================================
	生成処理関数（爆破に巻き込まれたスライムのスコア）
	-------------------------------------
	内容：頭上スコアの生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：スコア
	引数3：スコア表示位置
	-------------------------------------
	戻値：なし
=========================================== */
void CScoreOHManager::DisplayOverheadScore(TTriType<float> pos, E_SLIME_LEVEL level)
{
	float height; int score;
	float ScoreTime;
	switch (level) {
	case LEVEL_1:		score = LEVEL_1_SCORE; height = LEVEL_1_HEIGHT; ScoreTime = LEVEL_1_EXPLODE_TIME; break;
	case LEVEL_2:		score = LEVEL_2_SCORE; height = LEVEL_2_HEIGHT; ScoreTime = LEVEL_2_EXPLODE_TIME; break;
	case LEVEL_3:		score = LEVEL_3_SCORE; height = LEVEL_3_HEIGHT; ScoreTime = LEVEL_3_EXPLODE_TIME; break;
	case LEVEL_4:		score = LEVEL_4_SCORE; height = LEVEL_4_HEIGHT; ScoreTime = LEVEL_4_EXPLODE_TIME; break;
	case LEVEL_FLAME:	score = LEVEL_1_SCORE; height = LEVEL_1_HEIGHT; ScoreTime = LEVEL_1_EXPLODE_TIME; break;
	}
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pScore[i] != nullptr) continue;

		m_pScore[i] = new CScoreOverHead(pos, score, height, ScoreTime,true);
		m_pScore[i]->SetCamera(m_pCamera);
		break;
	}
}

void CScoreOHManager::AddScore()
{

}
/* ========================================
	スコア削除関数
	----------------------------------------
	内容：スコアがあったらチェックしてから削除
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CScoreOHManager::DeleteCheck()
{
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 未使用のスコアはスルー
		if (m_pScore[i] == nullptr) continue;
		// 削除フラグがたってないスコアはスルー
		if (m_pScore[i]->GetDelFlg() == false) continue;

		delete m_pScore[i]; m_pScore[i] = nullptr;	// 爆発を削除する

	}
}
/* ========================================
   カメラのセット関数
   ----------------------------------------
   内容：プレイヤー追従カメラをセットする
   ----------------------------------------
   引数：カメラ
   ----------------------------------------
   戻値：なし
======================================== */
void CScoreOHManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;	//中身は変えられないけどポインタはかえれるのでヨシ！
}
