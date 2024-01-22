/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	TimerStage2�p�w�b�_
	------------------------------------
	TimerStage2.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2024/01/01 �쐬 takagi

========================================== */

#ifndef __TIMER_STAGE_2_H__	//TimerStage2.h�C���N���[�h�K�[�h
#define __TIMER_STAGE_2_H__

// =============== �C���N���[�h ===================
#include "Timer.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTimerStage2 :public CTimer
{
public:
	// ===�v���g�^�C�v�錾===
	CTimerStage2();	//�R���X�g���N�^
private:
	// ===�萔��` ==========
	const float SLM_PARAM_CHANGE_TIME[CTimer::TIME_STATE::STATE_MAX] = { 60.0f, 120.0f, 180.0f };	// �o�ߎ��Ԃ̕b��
	const int	SLM_CREATE_NUM[STATE_MAX] = { 15, 20, 25 };											// �ő吶����(25��MAX_SLIME_NUM�ȉ��̒l)
	const float SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 0.9f, 0.7f, 0.5f };							// �����Ԋu
	const float SLM_MOVE_ADD_SPEED[STATE_MAX] = { 1.0f, 1.4f, 1.7f };								// �ړ��X�s�[�h
};

#endif // __TIMER_STAGE_2_H__