/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ステージ１用タイマー
	------------------------------------
	TimerStage3.cpp
	------------------------------------
	作成者 takagi

	変更履歴
	・2024/01/01 作成 takagi

========================================== */

// =============== インクルード ===================
#include "TimerStage3.h"	//自身のヘッダ



/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTimerStage3::CTimerStage3()
{
	// =============== 初期化 ===================
	for (int nCnt = STATE_FIRST; nCnt < STATE_SECOND; nCnt++)
	{
		m_anMaxSlimeNum[nCnt] = SLM_CREATE_NUM[nCnt];						// 段階別スライムの最大生成数
		m_afSlimeCreateInterval[nCnt] = SLM_CREATE_INTERVAL_TIME[nCnt];		// 段階別スライム生成間隔
		m_afSlimeMoveSpeed[nCnt] = SLM_MOVE_ADD_SPEED[nCnt];				// 段階別スライムスピード
		m_afSlimeParamChangeTime[nCnt] = SLM_PARAM_CHANGE_TIME[nCnt];		// 段階別スライム形態変化時間
	}
}