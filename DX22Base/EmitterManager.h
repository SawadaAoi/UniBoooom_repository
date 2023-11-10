/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�G�~�b�^�[�Ǘ���`
	------------------------------------
	EmitterManager.h
	------------------------------------
	�쐬�� takagi

	�ύX����
	�E2023/11/09 �쐬 takagi

========================================== */

#ifndef __EMITER_MANAGER_H__
#define __EMITER_MANAGER_H__

// =============== �C���N���[�h ===================
#include "Emitter.h"	//�����o�̃w�b�_

// =============== �N���X��` =====================
class CEmitterManager
{
protected:
	// ===�����o�ϐ��錾=====
	//pos��`	//�G�t�F�N�g�̒��S�ʒu
	CEmitter* m_pEmitter;	//�G�~�b�^�[
public:
	// ===�v���g�^�C�v�錾===
	CEmitterManager();								//�R���X�g���N�^
	CEmitterManager(const CEmitterManager& Obj);	//�R�s�[�R���X�g���N�^
	~CEmitterManager();								//�f�X�g���N�^
};	//�G�~�b�^�[�Ǘ�

#endif	//!__EMITER_MANAGER_H__