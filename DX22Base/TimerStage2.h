/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	TimerStage2用ヘッダ
	------------------------------------
	TimerStage2.h
	------------------------------------
	作成者 takagi

	変更履歴
	・2024/01/01 作成 takagi

========================================== */

#ifndef __TIMER_STAGE_2_H__	//TimerStage2.hインクルードガード
#define __TIMER_STAGE_2_H__

// =============== インクルード ===================
#include "Timer.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTimerStage2 :public CTimer
{
public:
	// ===プロトタイプ宣言===
	CTimerStage2();	//コンストラクタ
private:
	// ===定数定義 ==========
	const float SLM_PARAM_CHANGE_TIME[CTimer::TIME_STATE::STATE_MAX] = { 60.0f, 120.0f, 180.0f };	// 経過時間の秒数
	const int	SLM_CREATE_NUM[STATE_MAX] = { 15, 20, 25 };											// 最大生成数(25はMAX_SLIME_NUM以下の値)
	const float SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 0.9f, 0.7f, 0.5f };							// 生成間隔
	const float SLM_MOVE_ADD_SPEED[STATE_MAX] = { 1.0f, 1.4f, 1.7f };								// 移動スピード
};

#endif // __TIMER_STAGE_2_H__