/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	TimerStage3�p�w�b�_
	------------------------------------
	TimerStage3.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2024/01/01 �쐬 takagi

========================================== */

#ifndef __TIMER_STAGE_3_H__	//TimerStage3.h�C���N���[�h�K�[�h
#define __TIMER_STAGE_3_H__

// =============== �C���N���[�h ===================
#include "Timer.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTimerStage3 :public CTimer
{
public:
	// ===�v���g�^�C�v�錾===
	CTimerStage3();	//�R���X�g���N�^
private:
	// ===�萔��` ==========
	const float SLM_PARAM_CHANGE_TIME[CTimer::TIME_STATE::STATE_MAX] = { 60.0f, 120.0f, 180.0f };	// �o�ߎ��Ԃ̕b��
	const int	SLM_CREATE_NUM[STATE_MAX] = { 25, 30, 30 };											// �ő吶����(25��MAX_SLIME_NUM�ȉ��̒l)
	const float SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 0.5f, 0.3f, 0.1f };							// �����Ԋu
	const float SLM_MOVE_ADD_SPEED[STATE_MAX] = { 1.0f, 1.5f, 2.0f };								// �ړ��X�s�[�h
};

#endif // __TIMER_STAGE_3_H__