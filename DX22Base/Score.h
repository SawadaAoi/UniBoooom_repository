/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スコアヘッダー
   ---------------------------------------
   Score.h

   作成者 山本　凱翔

   変更履歴
	・2023/11/17　作成
========================================== */
#ifndef __SCORE_H__
#define __SCORE_H__
// =============== インクルード ===================
#include "Transform3d.h"	//ワールド座標系情報ヘッダー
// =============== クラス定義 =====================
class CScore
{
public:
	CScore(TPos3d<float> fPos,float fTime,int nScore);
	~CScore();

	void Update();		 		//更新関数
	void Draw();		 		//描画関数

private:

};






#endif // __SCORE_H__