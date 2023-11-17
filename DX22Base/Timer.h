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

========================================== */
#ifndef __TIMER_H__
#define __TIMER_H__

// =============== インクルード ===================


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

private:
	void WaitTimeCheck();

	// ===メンバ変数宣言===
	bool m_bStartFlg;	// カウントダウン開始フラグ(false = 待機中) 
	bool m_bStopFlg;	// タイマーストップフラグ(true = stop)
	int m_nTimeCnt;		// 制限時間フレーム減算値
	int m_dWaitCnt;		// カウントダウン開始フレーム減算値

};


#endif // __TIMER_H__