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
	�E2024/02/20 ��z���`�撲�� Tei

========================================== */
#ifndef __SHOW_WARNING_H__
#define __SHOW_WARNING_H__

// =============== �C���N���[�h ===================
#include <Texture.h>
#include "Pos2d.h"	//�񎟌����W
#include "Timer.h"
#include "SlimeManager.h"

class CUIStageManager;

// =============== �N���X��` =====================
class CShowWarning
{
public:
	CShowWarning(int nStageNum);
	~CShowWarning();
	void Update();
	void Draw();
	void DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// �x���w�i�`��
	void DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove);			// �x�������`��
	void DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, TPos2d<float> fScale, Texture* pBoss);		// �x����z���`��
	void ShowArrangement();		//��z�������֐�
	void ArrangementColorMotion(float fColor, int nFlame, float fAlpha);	// ��z���F�����֐�
	void ArrangementScaleMotion(TPos2d<float> fSize, int nFlame, float fAlpha);	// ��z���g�k�֐�


	void StartShowWarning();
	void SetUIStageManagerPtr(CUIStageManager* pUIMng);

	// �Q�b�^�[�֐�
	bool GetDispFlg();

private:
	Texture* m_pWarningBG;		// �x��BG
	Texture* m_pWarningTex;		// �x������
	Texture* m_pBossS2;			// �X�e�[�W�Q�{�X�̎�z��
	Texture* m_pBossS3;			// �X�e�[�W�R�{�X�̎�z��
	float m_fBGMove;			// �x���w�i�ړ���
	float m_fTopTexMove;		// ��x�������ړ���
	float m_fBotTexMove;		// ���x�������ړ���
	float m_fBGAlpha;			// �x���w�i�̓����x
	float m_fArrangementAlpha;	// ��z���̃��l
	float m_fArrangementColorAdjust;
	TPos2d<float> m_fArrangementScaleAdjust;	// ��z���X�P�[��������
	int m_nArrangementCnt;		// ��z�������p�J�E���g
	bool m_bArrangementShow;	// ��z���\���t���O


	int m_nStageNum;			// �X�e�[�W�ԍ�
	bool m_bDispFlg;			// �x���\���t���O
	int m_nDispCnt;				// �\�����Z�l

	TPos2d<float> m_fArrangementSizeAdjust;	// ��z���T�C�Y������
	CUIStageManager* m_pUIMng;
};





#endif // !__SHOW_WARNING_H__
