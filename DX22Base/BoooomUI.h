/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	boooom�\���p�w�b�_
	------------------------------------
	BoooomUI.h
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/20 h,�쐬 Tei
	�E2023/11/21 �\���ŕK�v�ȃ����o�ϐ��A�֐��쐬 Tei
	�E2024/02/09 �J�����폜 takagi
	�E2024/02/13 �J�����폜 takagi
	�E2024/02/20 �g�k�A�j���[�V�������� suzumura

========================================== */
#ifndef __BOOOOM_UI_H__
#define __BOOOOM_UI_H__

// =============== �C���N���[�h ===================
#include "Sprite.h"
#include <Texture.h>
#include "Pos3d.h"

// =============== �N���X��` =====================
class CBoooomUI
{
public:
	// ===�v���g�^�C�v�錾===
	CBoooomUI(TPos3d<float> pos, Texture* pTex, float fTime /*,const int& nFrame*/);
	~CBoooomUI();
	void Update();												//�X�V
	void Draw();

	void ScalingAnim();			//boooomUI�g�k�A�j���[�V�����֐�
	void DisplayTimeAdd();		//boooomUI�\���J�E���g���Z�����֐�
	bool GetDelFlg();			//�폜�t���O�擾�����֐�
private:
	// ===�����o�ϐ��錾===
	Texture* m_pBoooomTex;
	TPos3d<float> m_pos;			//�`��̈ʒu
	TPos3d<float> m_scale;			//�`��̃X�P�[���T�C�Y

	int			m_nDelFrame;		// BoooomUI�\���J�E���g
	bool		m_bDelFlg;			// �\���I���t���O
	float		m_fExplodeTime;		// ����������

	//-- �A�j���[�V�����֘A
	int m_nAnimFrame;	// �g�k�A�j���[�V�����J�E���g
	float m_fAnimRate;
	float m_fAddScaleX;	// ���Z�X�P�[��X
	float m_fAddScaleY;	// ���Z�X�P�[��Y
	float m_fScalingTime;
	float m_fAlpha;	//���l
	
};


#endif // __BOOOOM_UI_H__