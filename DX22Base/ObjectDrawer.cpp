/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�I�u�W�F�N�g�`�����
	---------------------------------------
	ObjectDrawer.cpp
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/24 ���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "ObjectDrawer.h"		//���g�̃w�b�_
#include "ControllMap.h"		//map����
#include "ZSort.h"				//Z�\�[�g�ŕ`�悷��
#include "MakeObjectVector.h"	//map��vector
#if _DEBUG
#include <Windows.h>	//���b�Z�[�W�{�b�N�X�p
#endif	//_!DEBUG

// =============== �O���[�o���ϐ��錾 ===================
std::map<unsigned int, CObject*> CObjectDrawer::m_pObject;	//�I�u�W�F�N�gnew/delete���ɑ��삳���R���e�i

/* ========================================
	�I�u�W�F�N�g�ǉ��֐�
	-------------------------------------
	���e�F�����Ŏ󂯎�����I�u�W�F�N�g�����g�̃R���e�i�ɒǉ�����
	-------------------------------------
	����1�FCObject* pObject�F�V�K�I�u�W�F�N�g
	-------------------------------------
	�ߒl�Fmap�̊i�[�ꏊ(�L�[)
=========================================== */
unsigned int CObjectDrawer::AddObject(CObject* pObject)
{
	// =============== �T�� =====================
	for (unsigned int unKey = (std::numeric_limits<unsigned int>::min)(); unKey < MAX_OBJECT; unKey++)	//�L�[�̋󂫂�T��
	{
		// =============== ���� =====================
		if (ACCESS_NULL_CHECK(m_pObject, unKey))	//�A�N�Z�X�E�k���`�F�b�N
		{
			// =============== �p�X =====================
			continue;	//���̌���
		}
		if (m_pObject.find(unKey) != m_pObject.end())	//�k���̒��g������
		{
			// =============== �폜 =====================
			m_pObject.erase(unKey);	//���I�m�ۂ��Ă���͂��Ȃ̂Ńk���̒��g�ُ͈�B�폜���ėv�f���i�[����ꏊ�Ƃ���
		}

		// =============== �i�[ =====================
		m_pObject.emplace(unKey, pObject);	//�A�h���X�i�[

		// =============== �I�� =====================
		return unKey;	//�i�[�ꏊ���w���L�[��
	}

	// =============== ���E���� =====================
#if _DEBUG
	std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
	MessageBox(nullptr, (ErrorSpot + "�I�u�W�F�N�g�̑��ݐ������E�𒴉߂��܂���").c_str(), "Error", MB_OK | MB_ICONERROR);				//�G���[�ʒm
#endif	//_!DEBUG
	return DEAD_KEY;	//�g�p���Ă��Ȃ��g���֒l�Ƃ��ĕԂ�
}

/* ========================================
	�I�u�W�F�N�g�����֐�
	-------------------------------------
	���e�F�����Ŏ󂯎�����Y�����̒��g�����g�̃R���e�i����폜����
	-------------------------------------
	����1�Fconst unsigned int & unKey�F�R���e�i�̃L�[
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CObjectDrawer::RemoveObject(const unsigned int & unKey)
{
	// =============== ���� =====================
	if (DEAD_KEY == unKey)	//�L�[�`�F�b�N
	{
		// =============== �I�� =====================
		return;	//�g�p����Ă��Ȃ��L�[�𖳎�
	}

	// =============== ���� =====================
	if (m_pObject.find(unKey) != m_pObject.end())	//�A�N�Z�X�`�F�b�N
	{
		if (m_pObject.at(unKey))	//�k���`�F�b�N
		{
//#if _DEBUG
//			std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";									//�G���[�ӏ�
//			MessageBox(nullptr, (ErrorSpot + "delete�Ɏ��s�����I�u�W�F�N�g��������܂����F" + typeid(*m_pObject.at(unKey)).name()).c_str(), "Error", MB_OK | MB_ICONERROR);	//�G���[�ʒm
//#else
//			delete m_pObject.at(unKey);	//�폜	���f�o�b�O���̓��������[�N�ɋC�Â��₷���悤�ɍ폜���Ȃ�
//#endif	//_!DEBUG
			//���z�肵�Ă����^�C�~���O���ς�����̂Ŗ�����
		}
		
		// =============== �폜 =====================
		m_pObject.erase(unKey);	//�I�u�W�F�N�g����
	}
}

#if _DEBUG
/* ========================================
	�֐��I�u�W�F�N�g���������֐�
	-------------------------------------
	���e�F�Ǘ����Ă���I�u�W�F�N�g�Ŏc���Ă�����̂����o���A�ʒm����B���������[�N�m�F�p�B
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CObjectDrawer::CheckAliveObject()
{
	// =============== �T�� =====================
	for (unsigned int unKey = (std::numeric_limits<unsigned int>::min)(); unKey < MAX_OBJECT; unKey++)	//�c���Ă���L�[��T��
	{
		// =============== ���� =====================
		if (ACCESS_NULL_CHECK(m_pObject, unKey))	//�A�N�Z�X�E�k���`�F�b�N
		{
			// =============== �p�X =====================
			continue;	//���̌���
		}
		if (m_pObject.find(unKey) != m_pObject.end())	//�k���̒��g������
		{
			MessageBox(nullptr, (static_cast<std::string>("�L�[�̂ݐ������Ă��܂��F") + std::to_string(unKey)).c_str(), "Error", MB_OK | MB_ICONERROR);							//�G���[�ʒm
		}
		else
		{
			MessageBox(nullptr, (static_cast<std::string>("���������[�N�̂����ꂪ����܂��F") + typeid(*m_pObject.at(unKey)).name()).c_str(), "Error", MB_OK | MB_ICONERROR);	//�G���[�ʒm
		}
	}
}
#endif	//_!DEBUG

/* ========================================
	�֐��I�u�W�F�N�g�`��֐�
	-------------------------------------
	���e�F�Ǘ����Ă���I�u�W�F�N�g���ׂĂ�Z�\�[�g�@�ŕ`��B
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CObjectDrawer::Draw()
{
	// =============== �ϐ��錾 =====================
	std::vector<const CObject*> pSubject;	//��ʑ�

	// =============== ������ =====================
	CMakeObjectVector::PushObjectVector(pSubject, m_pObject);	//�R���e�i������

	// =============== �`�� =====================
	CZSort::DrawWithZSort(pSubject);	//Z�\�[�g���g�p�����`��
}