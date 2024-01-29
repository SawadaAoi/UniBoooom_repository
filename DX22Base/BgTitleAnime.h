/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�A�j���w�i��`
	---------------------------------------
	BgTitleAnime.h

	�쐬��	takagi

	�ύX����
	�E2024/01/29 ���� takagi

========================================== */

#ifndef __BG_TITLE_ANIME_H__	//BgTitleAnime.h�C���N���[�h�K�[�h
#define __BG_TITLE_ANIME_H__

// =============== �C���N���[�h =====================
#include "TitleAnime.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CBgTitleAnime :public CTitleAnime	//�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	CBgTitleAnime();													//�R���X�g���N�^
	~CBgTitleAnime();													//�f�X�g���N�^
	void Update() override;												//�X�V
	void Draw(const E_DRAW_MODE & eMode = E_DRAW_MODE_NORMAL) override;	//�`��
	void ChangeLtoS(const int& nFrame);									//�k��
private:
	// ===�ϐ��錾===========
	CFrameCnt* m_pCntLtoS;	//�k���J�E���^
};	//�^�C�g���J�n�f��

#endif	//!__BG_TITLE_ANIME_H__