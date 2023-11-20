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
#include "ScoreOverHead.h"
#include "GameParameter.h"
#include "SlimeBase.h"

// =============== クラス定義 =====================
class CScoreOHManager
{
public:
	// ===メンバ関数宣言===
	CScoreOHManager();		//コンストラクタ
	~CScoreOHManager();		//デストラクタ

	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	void DisplayOverheadScore(TTriType<float> pos,int score, float height);			// スコアの生成
	void DisplayOverheadScore(TTriType<float> pos, E_SLIME_LEVEL level);			// スコアの生成
	void AddScore();			//スコア加算

	
protected:
	// ===メンバ変数宣言===
	CScoreOverHead* m_pScore[MAX_EXPLOSION_NUM];	//スコアの配列
	static int m_nTotalScore[5];	//トータルスコア//複数箇所対応	//倍率かける前

private:
	
};


#endif // !__SCORE_MANAGER_H__
