/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�w�i��`
	---------------------------------------
	BgTitle.h

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/17 �ŏ��g�傳�ꏙ�X�ɏk������悤�� takagi

========================================== */

#ifndef __BG_TITLE_H__	//BgTitle.h�C���N���[�h�K�[�h
#define __BG_TITLE_H__

// =============== �C���N���[�h =====================
#include "TitleObj.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CBgTitle :public CTitleObj	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CBgTitle(const int& nWaitTime = 0);							//�R���X�g���N�^
	~CBgTitle();												//�f�X�g���N�^
	void Update() override;										//�X�V
	void ChangeLtoS(const int& nFrame);							//�k��
private:
	// ===�ϐ��錾===========
	CFrameCnt* m_pCntLtoS;	//�k���J�E���^
};	//�^�C�g���p�w�i

#endif	//!__BG_TITLE_H__