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
	�E2024/02/13 �J�����폜 takagi

========================================== */

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

// =============== �N���X��` =====================
class CParticle
{
public:
	// ===�v���g�^�C�v�錾===
	CParticle();							//�R���X�g���N�^
	CParticle(const CParticle& Obj);		//�R�s�[�R���X�g���N�^
	virtual ~CParticle();					//�f�X�g���N�^
	virtual void Draw() = 0;				//�`��
};	//�p�[�e�B�N��

#endif	//!__PARTICLE_H__