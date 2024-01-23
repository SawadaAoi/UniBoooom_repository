/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���ԊǗ��p�w�b�_
	------------------------------------
	Timer.h
	------------------------------------
	�쐬��	tei

	�ύX����
	�E2023/11/14 h,�쐬 tei
	�E2023/11/17 �J�n�����𕡐���ޒǉ��A�^�C�}�[�X�g�b�v���� sawada
	�E2023/12/07 �Q�[���p�����[�^�Ɉˑ����Ă����̂ŏC���E�s���C���N���[�h�����E�Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2023/12/08 GetErapsedTime()�֐��ǉ� takagi
	�E2024/01/01 �p���p�������� takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __TIMER_H__	//Timer.h�C���N���[�h�K�[�h
#define __TIMER_H__

// =============== �萔��` ===================

// =============== �C���N���[�h ===================
#include <2dObject.h>
#include <Texture.h>
#include "Pos2d.h"	//�񎟌����W

// =============== �萔��` ===================
const int STAGE_TIME = 180 * 60;	//�X�e�[�W�������ԁi�b*�t���[���j

// =============== �N���X��` =====================
class CTimer :public C2dObject	//2D�I�u�W�F�N�g
{
protected:
	// ===�񋓒�` ==========
	const enum TIME_STATE
	{
		STATE_FIRST = 0,
		STATE_SECOND,
		STATE_THIRD,
		STATE_MAX,
	};
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

	int* GetTimePtr();
	int GetMaxSlimeNum();							// �X���C���ő吶�������擾
	int GetSlimeCreateInterval();					// �X���C�������Ԋu���擾
	float GetSlimeMoveSpeed();						// �X���C���X�s�[�h���擾
	int GetErapsedTime();							//�o�ߎ��Ԃ��擾
protected:
	// ===�����o�ϐ��錾===
	int m_anMaxSlimeNum[STATE_MAX];				// �i�K�ʃX���C���̍ő吶����
	float m_afSlimeCreateInterval[STATE_MAX];	// �i�K�ʃX���C�������Ԋu
	float m_afSlimeMoveSpeed[STATE_MAX];		// �i�K�ʃX���C���X�s�[�h
	float m_afSlimeParamChangeTime[STATE_MAX];	// �i�K�ʃX���C���`�ԕω�����

private:
	// ===�v���g�^�C�v�錾===
	void WaitTimeCheck();
	void ChangeSlimeParam();

	// ===�����o�ϐ��錾===
	bool m_bStartFlg;			// �J�E���g�_�E���J�n�t���O(false = �ҋ@��) 
	bool m_bStopFlg;			// �^�C�}�[�X�g�b�v�t���O(true = stop)
	int m_nTimeCnt;				// �������ԃt���[�����Z�l
	int m_dWaitCnt;				// �J�E���g�_�E���J�n�t���[�����Z�l
	int m_nMaxSlimeNum;			// �X���C���̍ő吶����
	int m_nSlimeCreateInterval;	// �X���C�������Ԋu
	float m_fSlimeMoveSpeed;	// �X���C���X�s�[�h

	Texture* m_pTextureNum;	//�^�C�}�[�\���p�e�N�X�`���|�C���^
	Texture* m_pTextureBG;
	Texture* m_pTextureColon;
};	//�^�C�}�[


#endif	//!__TIMER_H__