/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�G�~�b�^�[(�p�[�e�B�N���Ǘ�)��`
	------------------------------------
	Emitter.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2023/11/09 �쐬 takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Particle.h"	//�����o�̃w�b�_

#ifndef __EMITTER_H__
#define __EMITTER_H__

// =============== �N���X��` =====================
class CEmitter
{
protected:
	// ===�����o�ϐ��錾=====
	//pos��`
	CParticle* m_pParticle;	//�p�[�e�B�N��
public:
	// ===�v���g�^�C�v�錾===
	CEmitter();						//�R���X�g���N�^
	CEmitter(const CEmitter& Obj);	//�R�s�[�R���X�g���N�^
	~CEmitter();					//�f�X�g���N�^
};	//�G�~�b�^�[

#endif	//!__EMITTER_H__