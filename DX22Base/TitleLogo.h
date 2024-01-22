/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g�����S��`
	---------------------------------------
	TitleLogo.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/17 �����Q�Ɖ� takagi
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi
	�E2024/01/22 Draw()�֐�const�� takagi

========================================== */

#ifndef __TITLE_LOGO_H__	//TitleLogo.h�C���N���[�h�K�[�h
#define __TITLE_LOGO_H__

// =============== �C���N���[�h =====================
#include "TitleAnime.h"	//�e�̃w�b�_
#include "FrameCnt.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class CTitleLogo :public CTitleAnime	//�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	CTitleLogo(const int& nWaitTime = 0);								//�R���X�g���N�^
	~CTitleLogo();														//�f�X�g���N�^
	void Update() override;												//�X�V
	void Draw() const override;											//�`��
	void ChangeLtoS(const int& nFrame);									//�k��
private:
	// ===�ϐ��錾===========
	CFrameCnt* m_pCntLtoS;	//�k���J�E���^
};	//�^�C�g�����S

#endif	//!__TITLE_LOGO_H__