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

========================================== */
#ifndef __TIMER_H__
#define __TIMER_H__

// =============== �C���N���[�h ===================


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

private:
	// ===�����o�ϐ��錾===
	int m_nTimeCnt;	//���Ԃ̃J�E���g�_�E��
	int m_nMinute;	//
	int m_nSecond;	//

};


#endif // __TIMER_H__