/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   トータルスコアヘッダー
   ---------------------------------------
   TotalScore.h

   作成者 山本　凱翔

   変更履歴
	・2023/11/22　作成
========================================== */
#ifndef __TOTALSCORE_H__
#define __TOTALSCORE_H__

// =============== インクルード ===================
#include <Texture.h>
#include "GameParameter.h"

// =============== クラス定義 =====================
class CTotalScore
{
public:
	CTotalScore();
	~CTotalScore();

	void Draw();		 		//描画関数
	void AddScore(int Score);
	int GetTotalScore();
private:
	int m_nTotalScore;	
	Texture* m_pToScoreTexture;
};




#endif // !__TOTALSCORE_H__

