/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�p�[�e�B�N����`
	------------------------------------
	Particle.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2023/11/09 �쐬 takagi

========================================== */

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// =============== �C���N���[�h ===================
#include "Camera.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class CParticle
{
protected:
	// ===�����o�ϐ��錾=====
	//pos��`
	const CCamera* m_pCamera;	//�J����
public:
	// ===�v���g�^�C�v�錾===
	CParticle();							//�R���X�g���N�^
	CParticle(const CParticle& Obj);		//�R�s�[�R���X�g���N�^
	virtual ~CParticle();					//�f�X�g���N�^
	virtual void Draw() = 0;				//�`��
	void GetCamera(const CCamera* pCamera);	//�J�����擾
};	//�p�[�e�B�N��

#endif	//!__PARTICLE_H__