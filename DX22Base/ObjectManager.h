/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�V�[���p���ۃN���X��`
	---------------------------------------
	ObjectManager.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/21 ���� takagi
	�E2024/01/23 ����i�s takagi

========================================== */

#ifndef __OBJECT_MANAGER_H__	//ObjectManager.h�C���N���[�h�K�[�h
#define __OBJECT_MANAGER_H__

// =============== �C���N���[�h ===================
#include "Camera.h"	//�����o�̃w�b�_
#include "Object.h"	//�����o�̃w�b�_
#include <vector>	//�A�z�^�z��

// =============== �N���X��` =====================
class CObjectManager
{
public:
	// ===�v���g�^�C�v�錾===
	CObjectManager();													//�R���X�g���N�^
	virtual ~CObjectManager();											//�f�X�g���N�^
	virtual void Update();												//�X�V
	virtual void SetCamera(const CCamera* pCamera);						//�J�����Z�b�^
	virtual void GetObjects(std::vector<const CObject*>& Object) final;	//�I�u�W�F�N�g�Q�b�^
protected:
	// ===�����o�ϐ��錾=====
	std::vector<CObject*> m_pObject;	//�I�u�W�F�N�g
	const CCamera* m_pCamera;			//�J����	delete���Ȃ��A�|�C���^�͎󂯎���p
};	//�}�l�[�W��

#endif	//!__OBJECT_MANAGER_H__