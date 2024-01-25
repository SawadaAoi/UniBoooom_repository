/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	Z�\�[�g�`�����
	---------------------------------------
	ZSort.cpp
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/24 ���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "ZSort.h"		//���g�̃w�b�_
#include <algorithm>	//�\�[�g�p

/* ========================================
	Z�\�[�g�`��֐�
	-------------------------------------
	���e�F�����Ŏ󂯎�����`�敨��Z�l�Ń\�[�g�����̂��̂���`�悷��
	-------------------------------------
	����1�Fstd::vector<const CObject*>& Object�F�`�敨
	-------------------------------------
	�ߒl�F����
=========================================== */
void CZSort::DrawWithZSort(std::vector<const CObject*>& pObject)
{
	// =============== Z�\�[�g =====================
	std::sort(pObject.begin(), pObject.end(), [](const CObject* pFirst, const CObject* pSecond)->bool {
		return pFirst && pSecond					//�k���`�F�b�N
			? pFirst->GetPosZ() > pFirst->GetPosZ()	//���̂��̂���`��(�����̏ꍇ�͓���ւ��Ȃ�)
			: false;								//�Е���null�Ȃ̂Ŕ�r����K�v���Ȃ�
	});	//�I�u�W�F�N�g�̃\�[�g

	// =============== 3D��ԕ`�� =====================
	for_each(pObject.begin(), pObject.end(), [](const CObject* pObject)->void {
		if (pObject)	//�k���`�F�b�N
		{
			pObject->Draw();	//�`��
		}
	});	//�\�[�g���ɕ`��
}