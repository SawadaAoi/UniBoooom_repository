/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�����G�t�F�N�g�`��p�w�b�_
	---------------------------------------
	UnionEffectText.h

	�쐬��
			Tei

	�ύX����
	�E2024/02/06 �N���X��`�쐬 Tei

========================================== */

#ifndef __UNION_EFFECT_TEXT_H__	
#define __UNION_EFFECT_TEXT_H__

// =============== �C���N���[�h ===================
#include "DrawAnimation.h"
#include "Pos3d.h"
#include "Texture.h"

// =============== �N���X��` =====================
class CUnionSmokeEffect :public CDrawAnim	//UI�A�j���[�V����
{
public:
	// ===�v���g�^�C�v�錾===
	CUnionSmokeEffect(TPos3d<float> pos, TPos3d<float> size, Texture* pTex, const CCamera* pCamera);	// �R���X�g���N�^
	~CUnionSmokeEffect();
	void Update();
	void Draw();
	void DisplayTimeAdd();					// �����G�t�F�N�g�\���J�E���g���Z�����֐�

	// �Q�b�g�֐�
	bool GetDelFlg();						// �폜�t���O�擾�����֐�


protected:
	// ===�����o�ϐ��錾=====
	CDrawAnim* m_pTexUnionSmoke;		// �����̉�
	bool			m_bDelFlg;			// �����G�t�F�N�g�I���t���O
	int				m_nDelFrame;		// �����G�t�F�N�g�\���J�E���g
	float			m_fEffectTime;		// �q�b�g�G�t�F�N�g������
};	

#endif	//!__UNION_EFFECT_TEXT_H__