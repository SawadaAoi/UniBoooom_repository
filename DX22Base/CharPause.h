/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y������`
	---------------------------------------
	CharPause.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/09 ���� takagi
	�E2023/12/10 ����i�s takagi
	�E2023/12/16 �R�����g�C�� takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __CHAR_PAUSE_H__	//CharPause.h�C���N���[�h�K�[�h
#define __CHAR_PAUSE_H__

// =============== �C���N���[�h =====================
#include "PauseObj.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CCharPause :public CPauseObj	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CCharPause(const int& nWaitTime = 0);	//�R���X�g���N�^
private:
	// ===�ϐ��錾===
	float m_fMoveAngle;	//�P�U���ɂ������]�p[rad]
	// ===�v���g�^�C�v�錾===
	void CulculatePos(TPos3d<float>& fPos) override;	//�ʒu�Z�o
};	//�|�[�Y�p�̕���

#endif	//!__CHAR_PAUSE_H__