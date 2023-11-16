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
	void TimeStart();	//�^�C�}�[�J�E���g�J�n�O�̑҂��ԁi�b�j
	void TimeStart(float maxTime);	//�^�C�}�[�J�E���g�J�n�O�̑҂��ԁi�b�j
	void TimeStart(float maxTime, float waitTime);	//�^�C�}�[�J�E���g�J�n�O�̑҂��ԁi�b�j

private:
	void WaitTimeCheck();

	// ===�����o�ϐ��錾===
	bool m_bStartFlg;	//�J�E���g�_�E���J�n�t���O

	int m_nTimeCnt;			//���Ԃ̃J�E���g�_�E��
	int m_dWaitCnt;	//�J�E���g�_�E���J�n�t���O

};


#endif // __TIMER_H__