/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�X�g���b�v(�я�)�p�[�e�B�N����`
	------------------------------------
	StripeParticle.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2023/11/09 �쐬 takagi

========================================== */

#ifndef __STRIP_PARTICLE_H__
#define __STRIP_PARTICLE_H__

// =============== �C���N���[�h ===================
#include "Particle.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CStripeParticle	:CParticle	//�p�[�e�B�N��
{
protected:
	// ===�����o�ϐ��錾=====
	//pos��`
public:
	// ===�v���g�^�C�v�錾===
	CStripeParticle();								//�R���X�g���N�^
	CStripeParticle(const CStripeParticle& Obj);	//�R�s�[�R���X�g���N�^
	~CStripeParticle();								//�f�X�g���N�^
	void Draw();									//�`��
};	//�X�g���b�v�p�[�e�B�N��

#endif	//!__STRIP_PARTICLE_H__