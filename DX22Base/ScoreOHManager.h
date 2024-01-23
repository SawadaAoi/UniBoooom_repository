/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スコア管理ヘッダー
   ---------------------------------------
   ScoreOHManager.h
   ---------------------------------------
   作成者	yamamoto

   変更履歴
	・2023/11/17　作成 yamamoto
	・2023/11/25　使っていない関数を削除 yamamoto
	・2023/12/07 ゲームパラメータに依存していたので修正・不要箇所削除・定数定義 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __SCORE_OH_MANAGER_H__	//ScoreOHManager.hインクルードガード
#define __SCORE_OH_MANAGER_H__

// =============== インクルード ===================
#include "ObjectManager.h"	//親のヘッダ
#include "ScoreOverHead.h"
#include "ExplosionManager.h"	//最大爆発数定義
#include "SlimeBase.h"

// =============== 定数正義 ===================
const float SLIME_SCORE_HEIGHT = 4.0f;	//爆発時頭上スコアの表示位置

// =============== クラス定義 =====================
class CScoreOHManager :public CObjectManager	//オブジェクト管理
{
public:
	// ===メンバ関数宣言===
	CScoreOHManager();		//コンストラクタ
	~CScoreOHManager();		//デストラクタ
	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	void DisplayOverheadScore(TTriType<float> pos,int score, float height);			// スコアの生成
	void DisplayOverheadScore(TTriType<float> pos, E_SLIME_LEVEL level);			// スコアの生成
	void DeleteCheck();
protected:
	// ===メンバ変数宣言===
	CScoreOverHead* m_pScore[MAX_EXPLOSION_NUM];	//スコアの配列
	static int m_nTotalScore[5];	//トータルスコア//複数箇所対応	//倍率かける前
};	//スコア管理

#endif	//!__SCORE_OH_MANAGER_H__
