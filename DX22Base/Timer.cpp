/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�Q�[���^�C�}�[
	------------------------------------
	Timer.cpp
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/14 cpp,�쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "Timer.h"

// =============== �萔��` =======================
const int STAGE_TIME = 180 * 60;	//�X�e�[�W�������ԁi�b*�t���[���j

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
		// TODO�Q�[���I������
	}
}

void CTimer::Draw()
{
	//TODO���Ԃ̕`��
}

int CTimer::GetMinite()
{
	m_nMinute = m_nTimeCnt / 3600;	//�� = ���^�C������i60�b * 60�t���[���j

	return m_nMinute;
}

int CTimer::GetSecond()
{
	m_nSecond = m_nTimeCnt % 3600;	//�b = ���̕����𔲂��̎c��

	return m_nSecond;
}
