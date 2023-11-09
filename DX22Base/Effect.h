/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�G�t�F�N�g��`
	------------------------------------
	Effect.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2023/11/09 �쐬 takagi

========================================== */

#ifndef __EFFECT_H__
#define __EFFECT_H__

// =============== �C���N���[�h ===================
#include "EmitterManager.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class CEffect
{
protected:
	// ===�����o�ϐ��錾=====
	//pos��`
	CEmitterManager* m_pEmitterMng;	//�G�~�b�^�[�Ǘ�
public:
	// ===�v���g�^�C�v�錾===
	CEffect();						//�R���X�g���N�^
	CEffect(const CEffect& Obj);	//�R�s�[�R���X�g���N�^
	~CEffect();						//�f�X�g���N�^
};	//�p�[�e�B�N��

#endif	//!__EFFECT_H__