/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X�e�[�W�P�p�^�C�}�[
	------------------------------------
	TimerStage3.cpp
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2024/01/01 �쐬 takagi

========================================== */

// =============== �C���N���[�h ===================
#include "TimerStage3.h"	//���g�̃w�b�_



/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTimerStage3::CTimerStage3()
{
	// =============== ������ ===================
	for (int nCnt = STATE_FIRST; nCnt < STATE_SECOND; nCnt++)
	{
		m_anMaxSlimeNum[nCnt] = SLM_CREATE_NUM[nCnt];						// �i�K�ʃX���C���̍ő吶����
		m_afSlimeCreateInterval[nCnt] = SLM_CREATE_INTERVAL_TIME[nCnt];		// �i�K�ʃX���C�������Ԋu
		m_afSlimeMoveSpeed[nCnt] = SLM_MOVE_ADD_SPEED[nCnt];				// �i�K�ʃX���C���X�s�[�h
		m_afSlimeParamChangeTime[nCnt] = SLM_PARAM_CHANGE_TIME[nCnt];		// �i�K�ʃX���C���`�ԕω�����
	}
}