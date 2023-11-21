/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Timer�p�w�b�_
	------------------------------------
	Timer.h
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/14 h,�쐬 Tei
	�E2023/11/17 �J�n�����𕡐���ޒǉ��A�^�C�}�[�X�g�b�v���� Sawada

========================================== */
#ifndef __TIMER_H__
#define __TIMER_H__
// =============== �萔��` ===================

// =============== �C���N���[�h ===================
#include <Texture.h>
#include "GameParameter.h"

// =============== �N���X��` =====================
class CTimer
{
public:
	// ===�v���g�^�C�v�錾===
	CTimer();
	~CTimer();
	void Update();
	void Draw();

	int GetMinite();	//���ԁi���j�̎擾
	int GetSecond();	//���ԁi�b�j�̎擾
	void TimeStart();								//�^�C�}�[�J�n
	void TimeStart(float maxTime);					//�^�C�}�[�J�n(�������Ԑݒ�)
	void TimeStart(float maxTime, float waitTime);	//�^�C�}�[�J�n(�������Ԑݒ�A�҂����Ԃ���)
	void TimeStop();
	void TimeRestart();
	void DrawNumber(TPos2d<float> pos, int number);	//�����`��֐�

private:
	void WaitTimeCheck();

	// ===�����o�ϐ��錾===
	bool m_bStartFlg;	// �J�E���g�_�E���J�n�t���O(false = �ҋ@��) 
	bool m_bStopFlg;	// �^�C�}�[�X�g�b�v�t���O(true = stop)
	int m_nTimeCnt;		// �������ԃt���[�����Z�l
	int m_dWaitCnt;		// �J�E���g�_�E���J�n�t���[�����Z�l

	Texture* m_pShowTimer;	//�^�C�}�[�\���p�e�N�X�`���|�C���^
	Texture* m_pTimeBackground;
	Texture* m_pShowColon;
};


#endif // __TIMER_H__