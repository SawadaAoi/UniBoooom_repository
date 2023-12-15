/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Timer用ヘッダ
	------------------------------------
	Timer.h
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/14 h,作成 Tei
	・2023/11/17 開始処理を複数種類追加、タイマーストップ実装 Sawada
	・2023/12/07 ゲームパラメータに依存していたので修正・不足インクルード解消・ゲームパラメータから一部定数移動 takagi
	・2023/12/08 GetErapsedTime()関数追加 takagi

========================================== */
#ifndef __TIMER_H__
#define __TIMER_H__
// =============== 定数定義 ===================

// =============== インクルード ===================
#include <Texture.h>
#include "Pos2d.h"	//二次元座標

// =============== 定数定義 ===================
const int STAGE_TIME = 18000 * 60;	//ステージ制限時間（秒*フレーム）

// =============== クラス定義 =====================
class CTimer
{
public:
	// ===プロトタイプ宣言===
	CTimer();
	~CTimer();
	void Update();
	void Draw();

	int GetMinite();	//時間（分）の取得
	int GetSecond();	//時間（秒）の取得
	void TimeStart();								//タイマー開始
	void TimeStart(float maxTime);					//タイマー開始(制限時間設定)
	void TimeStart(float maxTime, float waitTime);	//タイマー開始(制限時間設定、待ち時間あり)
	void TimeStop();
	void TimeRestart();
	void DrawNumber(TPos2d<float> pos, int number);	//数字描画関数

	int* GetTimePtr();
	int GetMaxSlimeNum();							// スライム最大生成数を取得
	int GetSlimeCreateInterval();					// スライム生成間隔を取得
	float GetSlimeMoveSpeed();						// スライムスピードを取得
	int GetErapsedTime();							//経過時間を取得

private:
	void WaitTimeCheck();
	void ChangeSlimeParam();

	// ===メンバ変数宣言===
	bool m_bStartFlg;			// カウントダウン開始フラグ(false = 待機中) 
	bool m_bStopFlg;			// タイマーストップフラグ(true = stop)
	int m_nTimeCnt;				// 制限時間フレーム減算値
	int m_dWaitCnt;				// カウントダウン開始フレーム減算値
	int m_nMaxSlimeNum;			// スライムの最大生成数
	int m_nSlimeCreateInterval;	// スライム生成間隔
	float m_fSlimeMoveSpeed;	// スライムスピード

	Texture* m_pTextureNum;	//タイマー表示用テクスチャポインタ
	Texture* m_pTextureBG;
	Texture* m_pTextureColon;
};


#endif // __TIMER_H__