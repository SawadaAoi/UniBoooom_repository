/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スコアヘッダー
   ---------------------------------------
   Score.h

   作成者 山本　凱翔

   変更履歴
	・2023/11/17　作成 yamamoto
========================================== */
#ifndef __SCORE_H__
#define __SCORE_H__
// =============== インクルード ===================
#include "Transform3d.h"	//ワールド座標系情報ヘッダー
#include <Texture.h>
#include <vector>
#include "Camera.h"			//カメラ定義ヘッダー


// =============== クラス定義 =====================
class CScoreOverHead
{
public:
	CScoreOverHead(TPos3d<float> fPos,int nScore, float posY, float Time, bool delayFlg);
	~CScoreOverHead();

	
	void Update();		 		//更新関数
	void Draw();		 		//描画関数
	void Delay();				//スコア表示遅延処理
	void DisplayTimeAdd();		// スコア表示カウント加算処理関数
	std::vector<int> digitsToArray(int score);	//引数の数字を各桁1ずつ配列に入れる
	bool GetDelFlg();
	void SetCamera(const CCamera * pCamera);
private:
	Texture* m_pScoreTexture;	//スコア表示用テクスチャポインタ
	tagTransform3d m_Transform;	//ワールド座標系に必要な情報

	std::vector<int> digits;	//各桁1ずつ入れるための配列
	std::vector<int> digitArray;//digitsをここに入れる
	int nArraySize;				//表示時のfor文で使用
	float m_fExplodeTime;		//頭上スコア表示時間
	float m_fDelFrame;			//表示経過時間
	bool m_bDelFlg;				//削除フラグ
	bool m_bDelayFlg;			//スコア表示遅延フラグ
	int m_nDelayCnt;			//遅延をカウント
	const CCamera*	m_pCamera;	//カメラのポインタ

};






#endif // __SCORE_H__