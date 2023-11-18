/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スコア管理ヘッダー
   ---------------------------------------
   ScoreManager.h

   作成者 山本　凱翔

   変更履歴
	・2023/11/17　作成
========================================== */
#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__

// =============== インクルード ===================
#include "Score.h"
#include "GameParameter.h"

// =============== クラス定義 =====================
class CScoreManager
{
public:
	// ===メンバ関数宣言===
	CScoreManager();		//コンストラクタ
	~CScoreManager();		//デストラクタ

	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	void CreateScore(TTriType<float> pos,float time, int score);			//スコアの生成
	void AddScore();			//スコア加算

	
protected:
	// ===メンバ変数宣言===
	CScore* m_pScore[MAX_EXPLOSION_NUM];	//スコアの配列
	static int m_nTotalScore[5];	//トータルスコア//複数箇所対応
private:
	
};


#endif // !__SCORE_MANAGER_H__
