/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  �q�b�g�X���C���G�t�F�N�g�w�b�_�[
   ---------------------------------------
   HitSlimeEffect.h

   �쐬�� �A �F��

   �ύX����
	�E2024/01/25 HitSlimeEffect�N���X�쐬 Tei

========================================== */
#ifndef __HIT_SLIME_EFFECT_H__	
#define __HIT_SLIME_EFFECT_H__

// =============== �C���N���[�h ===================
#include "Shader.h"			//�V�F�[�_�[�N���X��`�w�b�_�[
#include "Transform3d.h"	//���[���h���W�n���w�b�_�[
#include "CameraChase.h"	//�J������`�w�b�_�[
#include "LibEffekseer.h"	//effekseer�p�w�b�_�[

// =============== �N���X��` =====================

class CHitSlimeEffect
{
public:
	// ===�����o�֐��錾===
	CHitSlimeEffect(TPos3d<float> fPos, float fTime, Effekseer::EffectRef hitEffect, const CCamera* pCamera);	//�R���X�g���N�^
	~CHitSlimeEffect();												// �f�X�g���N�^
	void Update();												// �X�V�֐�
	void Draw();												// �`��֐�
	void DisplayTimeAdd();										// �q�b�g�G�t�F�N�g�\���J�E���g���Z�����֐�


	// �Z�b�g�֐�
	void SetCamera(const CCamera* pCamera);	// ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g

	// �Q�b�g�֐�
	bool GetDelFlg();						// �폜�t���O�擾�����֐�

private:

	// ===�����o�ϐ��錾===
	tagTransform3d m_Transform;
	const CCamera*	m_pCamera;			// �J�����̃|�C���^
	bool			m_bDelFlg;			// �q�b�g�G�t�F�N�g�I���t���O
	int				m_nDelFrame;		// �q�b�g�G�t�F�N�g�\���J�E���g
	float			m_fEffectTime;		// �q�b�g�G�t�F�N�g������

	Effekseer::EffectRef m_hitEffect;	
	Effekseer::Handle m_efcHitHandle;	
};

#endif // __HIT_SLIME_EFFECT_H__