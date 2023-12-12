/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UI�A�j���[�V�����`��p�w�b�_
	---------------------------------------
	DrawAnimation.h

	�쐬��
			nieda

	�ύX����
	�E2023/12/08 �V�K�쐬 nieda
	�E2023/12/09 ���� nieda
	�E2023/12/11 ���� nieda
	�E2023/12/12 tkg�搶�̎w���ɂ��2dpolygon�ɑΉ� nieda

========================================== */

#ifndef __DRAW_ANIMATION_H__	//DrawAnimation.h�C���N���[�h�K�[�h
#define __DRAW_ANIMATION_H__

// =============== �C���N���[�h ===================
#include "Pos2d.h"
#include "Texture.h"
#include "CameraChase.h"
#include "2dPolygon.h"
#include "GameParameter.h"
#include "Transform3d.h"

// =============== �N���X��` =====================
class CDrawAnim :public C2dPolygon	//���ʃI�u�W�F
{
public:
	// ===�v���g�^�C�v�錾===
	CDrawAnim(const char*, CCamera*, int, TDiType<int>, int);	// �R���X�g���N�^
	~CDrawAnim() {};		// �f�X�g���N�^
	void Update();		// �X�V�֐�
	void Draw();		// �X�V�֐�

protected:
	// ===�����o�ϐ��錾=====
	Texture* m_pTexture;
	int m_nNumAnim;				// �A�j���[�V�����ԍ�
	int m_nNumAnimMax;			// �A�j���[�V�����̍ő吔
	TDiType<int> m_NumCut;		// ������
	TDiType<float> m_fUvpos;	// UV���W
	TDiType<float> m_fUvscale;	// UV�����T�C�Y�i�[�p
	int m_nCntSwitch;			// �A�j���[�V�����̐ؑ֊Ԋu
	bool bRoop;					// ���[�v����t���O
};	//UI�A�j���[�V����

#endif	//!__DRAW_ANIMATION_H__

