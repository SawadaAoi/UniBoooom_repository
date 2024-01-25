/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	Z�\�[�g�`���`
	---------------------------------------
	MakeObjectVector.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/24 ���� takagi

========================================== */

#ifndef __MAKE_OBJECT_VECTOR_H__	//MakeObjectVector.h�C���N���[�h�K�[�h
#define __MAKE_OBJECT_VECTOR_H__

// =============== �C���N���[�h =====================
#include "Object.h"			//�I�u�W�F�N�g
#include "ObjectManager.h"	//�I�u�W�F�N�g�Ǘ�
#include <vector>			//�z��R���e�i
#include <algorithm>			//�\�[�g�p

// =============== �N���X��` =====================
class CMakeObjectVector
{
public:
	// ===�v���g�^�C�v�錾===
	template<typename Key> static void PushObjectVector(std::vector<const CObject*>& pContainer, 
		const std::map<Key, CObject*>& pObject);				//�I�u�W�F�N�g�i�[
	template<typename Key> static void PushObjectVector(std::vector<const CObject*>& pContainer,
		const std::map<Key, const CObject*>& pObject);			//�I�u�W�F�N�g�i�[
	template<typename Key> static void PushObjectVector(std::vector<const CObject*>& pContainer,
		const std::map<Key, CObjectManager*>& pObjectManager);	//�I�u�W�F�N�g�i�[
};	//Z�\�[�g�`��

/* ========================================
	�I�u�W�F�N�g�i�[�֐�
	-------------------------------------
	���e�F����2�Ŏ󂯎�����`�敨�̃A�h���X������1�Ŏ󂯎�����i�[��Ɋi�[����
	-------------------------------------
	����1�Fstd::vector<const CObject*>& pContainer�F�i�[��̃R���e�i
	����2�Fconst std::map<Key, CObject*>& pObject�F�i�[����I�u�W�F�N�g
	-------------------------------------
	�ߒl�F����
=========================================== */
template<typename Key>	//�e���v���[�g�֐�����
void CMakeObjectVector::PushObjectVector(std::vector<const CObject*>& pContainer, const std::map<Key, CObject*>& pObject)
{
	// =============== ������ =====================
	for_each(pObject.begin(), pObject.end(), [&pContainer](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//�k���`�F�b�N
		{
			pContainer.emplace_back(pObject.second);	//�I�u�W�F�N�g�ǉ�
		}
	});	//��ʑ̃I�u�W�F�N�g�A�h���X�R�s�[
}

/* ========================================
	�I�u�W�F�N�g�i�[�֐�
	-------------------------------------
	���e�F����2�Ŏ󂯎�����Ǘ��҂����`�敨�̃A�h���X������1�Ŏ󂯎�����i�[��Ɋi�[����
	-------------------------------------
	����1�Fstd::vector<const CObject*>& pContainer�F�i�[��̃R���e�i
	����2�Fconst std::map<Key, CObjectManager*>& pObjectManager�F�i�[����I�u�W�F�N�g���Ǘ��������
	-------------------------------------
	�ߒl�F����
=========================================== */
template<typename Key>	//�e���v���[�g�֐�����
void CMakeObjectVector::PushObjectVector(std::vector<const CObject*>& pContainer, const std::map<Key, CObjectManager*>& pObjectManager)
{
	for_each(pObjectManager.begin(), pObjectManager.end(), [&pContainer](std::pair<int, CObjectManager*> pObjectManager)->void {
		if (pObjectManager.second)	//�k���`�F�b�N
		{
			pObjectManager.second->GetObjects(pContainer);	//�I�u�W�F�N�g�ǉ�
		}
	});	//�Ǘ�����Ă���I�u�W�F�N�g�A�h���X�R�s�[
}

#endif	//!__MAKE_OBJECT_VECTOR_H__