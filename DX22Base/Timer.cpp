/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ゲームタイマー
	------------------------------------
	Timer.cpp
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/14 cpp,作成 Tei

========================================== */

// =============== インクルード ===================
#include "Timer.h"

// =============== 定数定義 =======================
const int STAGE_TIME = 180 * 60;	//ステージ制限時間（秒*フレーム）

CTimer::CTimer()
	:m_nTimeCnt(STAGE_TIME)
{

}

CTimer::~CTimer()
{
}

void CTimer::Update()
{
	m_nTimeCnt--;
	if (m_nTimeCnt == 0)
	{
		// TODOゲーム終了処理
	}
}

void CTimer::Draw()
{
	//TODO時間の描画
}

int CTimer::GetMinite()
{
	m_nMinute = m_nTimeCnt / 3600;	//分 = 総タイム割る（60秒 * 60フレーム）

	return m_nMinute;
}

int CTimer::GetSecond()
{
	m_nSecond = m_nTimeCnt % 3600;	//秒 = 分の部分を抜くの残り

	return m_nSecond;
}
