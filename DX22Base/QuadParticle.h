/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�N�A�b�h�p�[�e�B�N��(�l�p��2d�|���S���A�r���{�[�h���g�p����)��`
	------------------------------------
	QuadParticle.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2023/11/09 �쐬 takagi

========================================== */

#ifndef __QUAD_PARTICLE_H__
#define __QUAD_PARTICLE_H__

// =============== �C���N���[�h ===================
#include "Particle.h"	//�e�̃w�b�_

// =============== �N���X��` =====================
class CQuadParticle :CParticle	//�p�[�e�B�N��
{
protected:
	// ===�����o�ϐ��錾=====
	//pos��`
	//Geometry����p�������N���X�FQuad
public:
	// ===�v���g�^�C�v�錾===
	CQuadParticle();							//�R���X�g���N�^
	CQuadParticle(const CQuadParticle& Obj);	//�R�s�[�R���X�g���N�^
	~CQuadParticle();							//�f�X�g���N�^
	void Draw();								//�`��
};	//�N�A�b�h�p�[�e�B�N��

#endif	//!__QUAD_PARTICLE_H__