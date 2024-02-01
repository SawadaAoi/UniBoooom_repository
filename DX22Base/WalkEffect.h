/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  �v���C���[�ړ��G�t�F�N�g�w�b�_�[
   ---------------------------------------
   WalkEffect.h

   �쐬�� �A �F��

   �ύX����
	�E2024/01/30 WalkEffect�N���X�쐬 Tei

========================================== */
#ifndef __WALK_EFFECT_H__
#define __WALK_EFFECT_H__

// =============== �C���N���[�h ===================
#include "Shader.h"			//�V�F�[�_�[�N���X��`�w�b�_�[
#include "Transform3d.h"	//���[���h���W�n���w�b�_�[
#include "CameraChase.h"	//�J������`�w�b�_�[
#include "LibEffekseer.h"	//effekseer�p�w�b�_�[

// =============== �N���X��` =====================
class CWalkEffect
{
public:
	// ===�����o�֐��錾===
	CWalkEffect(TPos3d<float> fPos, TPos3d<float> fRadian, float fTime, float fSize, Effekseer::EffectRef walkEffect, const CCamera* pCamera);	//�R���X�g���N�^
	~CWalkEffect();												// �f�X�g���N�^
	void Update();												// �X�V�֐�
	void Draw();												// �`��֐�
	void DisplayTimeAdd();										// �v���C���[�ړ��G�t�F�N�g�\���J�E���g���Z�����֐�
	
	
	// �Z�b�g�֐�
	void SetCamera(const CCamera* pCamera);	// ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g

	// �Q�b�g�֐�
	bool GetDelFlg();						// �폜�t���O�擾�����֐�

private:

	// ===�����o�ϐ��錾===
	tagTransform3d m_Transform;
	const CCamera*	m_pCamera;			// �J�����̃|�C���^
	bool			m_bDelFlg;			// �v���C���[�ړ��G�t�F�N�g�I���t���O
	int				m_nDelFrame;		// �v���C���[�ړ��G�t�F�N�g�\���J�E���g
	float			m_fEffectTime;		// �v���C���[�ړ��G�t�F�N�g������
	float			m_fRandSize;		// �����_���T�C�Y�����l
	float			m_fRadian;			// �p�x
	Effekseer::EffectRef m_walkEffect;
	Effekseer::Handle m_efcWalkHandle;
};

#endif //__WALK_EFFECT_H__