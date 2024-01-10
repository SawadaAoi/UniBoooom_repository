/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	TimerStage3用ヘッダ
	------------------------------------
	TimerStage3.h
	------------------------------------
	作成者 takagi

	変更履歴
	・2024/01/01 作成 takagi

========================================== */

#ifndef __TIMER_STAGE_3_H__	//TimerStage3.hインクルードガード
#define __TIMER_STAGE_3_H__

// =============== インクルード ===================
#include "Timer.h"	//親のヘッダ

// =============== クラス定義 =====================
class CTimerStage3 :public CTimer
{
public:
	// ===プロトタイプ宣言===
	CTimerStage3();	//コンストラクタ
private:
	// ===定数定義 ==========
	const float SLM_PARAM_CHANGE_TIME[CTimer::TIME_STATE::STATE_MAX] = { 60.0f, 120.0f, 180.0f };	// 経過時間の秒数
	const int	SLM_CREATE_NUM[STATE_MAX] = { 25, 30, 30 };											// 最大生成数(25はMAX_SLIME_NUM以下の値)
	const float SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 0.5f, 0.3f, 0.1f };							// 生成間隔
	const float SLM_MOVE_ADD_SPEED[STATE_MAX] = { 1.0f, 1.5f, 2.0f };								// 移動スピード
};

#endif // __TIMER_STAGE_3_H__