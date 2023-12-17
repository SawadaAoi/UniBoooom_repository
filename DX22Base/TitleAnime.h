/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�A�j���[�V������`
	---------------------------------------
	TitleAnime.h

	�쐬��	takagi

	�ύX����
	�E2023/12/16 ���� takagi
	�E2023/12/17 �����Q�Ɖ� takagi

========================================== */

#ifndef __TITLE_ANIME_H__	//TitleAnime.h�C���N���[�h�K�[�h
#define __TITLE_ANIME_H__

// =============== �C���N���[�h =====================
#include "DrawAnimation.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CTitleAnime :public CDrawAnim	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	~CTitleAnime();												//�f�X�g���N�^
	void Update() override;										//�X�V
	void Draw(const E_DRAW_MODE& eMode = E_DRAW_MODE_NORMAL) override;	//�`��
protected:
	// ===�v���g�^�C�v�錾===
	CTitleAnime(const int& nSplitMax, const TDiType<int>& nSplit, const int& nWaitTime = 0, const int& nCnt = 0);	//�R���X�g���N�^
private:
	// ===�����o�ϐ��錾=====
	int* m_pnWaitTime;	//�����ҋ@���Ԍv��
};	//�^�C�g���p�A�j��

#endif	//!__TITLE_ANIME_H__