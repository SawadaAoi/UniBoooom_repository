/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	時間管理用ヘッダ
	------------------------------------
	Timer.h
	------------------------------------
	作成者	tei

	変更履歴
	・2023/11/14 h,作成 tei
	・2023/11/17 開始処理を複数種類追加、タイマーストップ実装 sawada
	・2023/12/07 ゲームパラメータに依存していたので修正・不足インクルード解消・ゲームパラメータから一部定数移動 takagi
	・2023/12/08 GetErapsedTime()関数追加 takagi
	・2024/01/01 継承用書き換え takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __TIMER_H__	//Timer.hインクルードガード
#define __TIMER_H__

// =============== 定数定義 ===================

// =============== インクルード ===================
#include <2dObject.h>
#include <Texture.h>
#include "Pos2d.h"	//二次元座標

// =============== 定数定義 ===================
const int STAGE_TIME = 180 * 60;	//ステージ制限時間（秒*フレーム）

// =============== クラス定義 =====================
class CTimer :public C2dObject	//2Dオブジェクト
{
protected:
	// ===列挙定義 ==========
	const enum TIME_STATE
	{
		STATE_FIRST = 0,
		STATE_SECOND,
		STATE_THIRD,
		STATE_MAX,
	};
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
protected:
	// ===メンバ変数宣言===
	int m_anMaxSlimeNum[STATE_MAX];				// 段階別スライムの最大生成数
	float m_afSlimeCreateInterval[STATE_MAX];	// 段階別スライム生成間隔
	float m_afSlimeMoveSpeed[STATE_MAX];		// 段階別スライムスピード
	float m_afSlimeParamChangeTime[STATE_MAX];	// 段階別スライム形態変化時間

private:
	// ===プロトタイプ宣言===
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
};	//タイマー


#endif	//!__TIMER_H__