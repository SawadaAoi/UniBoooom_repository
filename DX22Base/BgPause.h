/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y�w�i��`
	---------------------------------------
	BgPause.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/10 ���� takagi
	�E2023/12/16 �R�����g�C�� takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __BG_PAUSE_H__	//BgPause.h�C���N���[�h�K�[�h
#define __BG_PAUSE_H__

// =============== �C���N���[�h =====================
#include "PauseObj.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CBgPause :public CPauseObj	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CBgPause(const int& nWaitTime = 0);	//�R���X�g���N�^
	~CBgPause();						//�f�X�g���N�^
private:
	// ===�v���g�^�C�v�錾===
	void CulculatePos(TPos3d<float>& fPos) override;	//�ʒu�Z�o
	PixelShader* m_pBgPs;								//�w�i�p�s�N�Z���V�F�[�_
	VertexShader* m_pBgVs;								//�w�i�p���_�V�F�[�_
};	//�|�[�Y�p�w�i

#endif	//!__BG_PAUSE_H__