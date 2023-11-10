/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���f���p�[�e�B�N����`
	------------------------------------
	ModelParticle.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2023/11/09 �쐬 takagi

========================================== */

#ifndef __QUAD_PARTICLE_H__
#define __QUAD_PARTICLE_H__

// =============== �C���N���[�h ===================
#include "Particle.h"	//�e�̃w�b�_
#include "Model.h"		//�����o�̃w�b�_

// =============== �N���X��` =====================
class CModelParticle :CParticle	//�p�[�e�B�N��
{
protected:
	// ===�����o�ϐ��錾=====
	//pos��`
	Model*m_pModel;	//3d���f��
public:
	// ===�v���g�^�C�v�錾===
	CModelParticle();							//�R���X�g���N�^
	CModelParticle(const CModelParticle& Obj);	//�R�s�[�R���X�g���N�^
	~CModelParticle();							//�f�X�g���N�^
	void Draw();								//�`��
};	//���f���p�[�e�B�N��

#endif	//!__QUAD_PARTICLE_H__