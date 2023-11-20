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
#include <Texture.h>
#include <vector>
#include "Camera.h"			//カメラ定義ヘッダー


// =============== クラス定義 =====================
class CScore
{
public:
	CScore(TPos3d<float> fPos,int nScore, float posY);
	~CScore();

	
	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	std::vector<int> digitsToArray(int score);	//引数の数字を各桁1ずつ配列に入れる
private:
	Texture* m_pScoreTexture;	//スコア表示用テクスチャポインタ
	tagTransform3d m_Transform;	//ワールド座標系に必要な情報

	std::vector<int> digits;	//各桁1ずつ入れるための配列
	std::vector<int> digitArray;//digitsをここに入れる
	int ArraySize;				//表示時のfor文で使用

	const CCamera*	m_pCamera;	//カメラのポインタ

};






#endif // __SCORE_H__