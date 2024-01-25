/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�I�u�W�F�N�g�`���`
	---------------------------------------
	ObjectDrawer.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/21 ���� takagi
	�E2024/01/23 ����i�s takagi

========================================== */

#ifndef __OBJECT_DRAWER_H__	//ObjectDrawer.h�C���N���[�h�K�[�h
#define __OBJECT_DRAWER_H__

// =============== �C���N���[�h ===================
#include "Object.h"	//�I�u�W�F�N�g
#include <vector>	//�z��R���e�i
#include <climits>	//

// =============== �N���X��` =====================
class CObjectDrawer
{
private:
	// ===�萔��`===========
	static const unsigned int DEAD_KEY = (std::numeric_limits<unsigned int>::max)();	//�g�p���Ȃ��L�[
	static const unsigned int MAX_OBJECT = DEAD_KEY - 1;								//�����ɑ��݂ł���I�u�W�F�N�g�̍ő吔
public:
	// ===�v���g�^�C�v�錾===
	static unsigned int AddObject(CObject* pObject);		//�V�K�I�u�W�F�N�g�ǉ�
	static void RemoveObject(const unsigned int& unKey);	//�I�u�W�F�N�g����
#if _DEBUG
	static void CheckAliveObject();							//�����I�u�W�F�N�g����
#endif	//_!DEBUG
	static void Draw();										//�`��
private:
	// ===�����o�ϐ��錾=====
	static std::map<unsigned int, CObject*> m_pObject;	//�I�u�W�F�N�gnew/delete���ɑ��삳���R���e�i
	//static std::vector<CObject*> m_pObject;			//�I�u�W�F�N�gnew/delete���ɑ��삳���R���e�i
};	//�I�u�W�F�N�g�`��

#endif	//!__OBJECT_DRAWER_H__