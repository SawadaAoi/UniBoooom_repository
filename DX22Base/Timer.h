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
	void TimeStart();	//タイマーカウント開始前の待つ時間（秒）
	void TimeStart(float maxTime);	//タイマーカウント開始前の待つ時間（秒）
	void TimeStart(float maxTime, float waitTime);	//タイマーカウント開始前の待つ時間（秒）

private:
	void WaitTimeCheck();

	// ===メンバ変数宣言===
	bool m_bStartFlg;	//カウントダウン開始フラグ

	int m_nTimeCnt;			//時間のカウントダウン
	int m_dWaitCnt;	//カウントダウン開始フラグ

};


#endif // __TIMER_H__