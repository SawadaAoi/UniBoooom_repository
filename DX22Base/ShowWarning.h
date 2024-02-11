/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�o���x���w�b�_
	------------------------------------
	ShowWarning.h
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2024/02/11 �N���X��`�쐬 Tei

========================================== */
#ifndef __SHOW_WARNING_H__
#define __SHOW_WARNING_H__

// =============== �C���N���[�h ===================
#include <Texture.h>
#include "Pos2d.h"	//�񎟌����W
#include "Timer.h"
#include "SlimeManager.h"


// =============== �N���X��` =====================
class CShowWarning
{
public:
	CShowWarning();
	~CShowWarning();
	void Update();
	void Draw();
	void DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// �x���w�i�`��
	void DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// �x�������`��
	void DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, Texture* pBoss);		// �x����z���`��
	void ArrangementAdjust();		//��z�������֐�

	// �Z�b�g�֐�
	void SetTimer(CTimer* pTimer);
	void SetSlimeMng(CSlimeManager* pBoss);

private:
	CTimer* m_pTimer;
	Texture* m_pWarningBG;		// �x��BG
	Texture* m_pWarningTex;		// �x������
	Texture* m_pBossS2;			// �X�e�[�W�Q�{�X�̎�z��
	Texture* m_pBossS3;			// �X�e�[�W�R�{�X�̎�z��
	CSlimeManager* m_pBoss;
	float m_fBGMove;			// �x���w�i�ړ���
	float m_fTopTexMove;		// ��x�������ړ���
	float m_fBotTexMove;		// ���x�������ړ���
	float m_fBGAlpha;			// �x���w�i�̓����x
	float m_fArrangementAlpha;	// ��z���̃��l
	TPos2d<float> m_fArrangementSizeAdjust;	// ��z���T�C�Y������
	
};





#endif // !__SHOW_WARNING_H__
