/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�}�b�v�����`
	---------------------------------------
	ControllMap.h
	---------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/23 ���� takagi

========================================== */

#ifndef __CONTROLL_MAP_H__	//ControllMap.h�C���N���[�h�K�[�h
#define __CONTROLL_MAP_H__

// =============== �O���[�o���ϐ��錾 ===================
static auto ACCESS_NULL_CHECK = [](auto pMap, int nKey)->bool
//auto pMap�Fstd::map<int, pointer*>�̂��ƁB
//int nKey�F���̎w�肵�����Y�����ԍ��B
{
	if (pMap.find(nKey) != pMap.end() && pMap.at(nKey))	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N
	{
		// =============== �� =====================
		return true;	//�A�N�Z�X�ł���E���g���k���łȂ�
	}
	else
	{
		// =============== �� =====================
		return false;	//�`�F�b�N�s�K��
	}
};	//std::map<int, pointer*>�̃A�N�Z�X�`�F�b�N�E�k���`�F�b�N���s���֐��I�u�W�F�N�g
static auto ACCESS_NULL_TYPE_CHECK = [](auto pMap, const int& nKey, const size_t& Typehash)->bool
//auto pMap				�Fstd::map<int, pointer*>�̂��ƁB
//const int& nKey		�F���̎w�肵�����Y�����ԍ��B
//const size_t& Typehash�F�^�`�F�b�N�������^ID�̃n�b�V���R�[�h�B
{
	// =============== ���� =====================
	if (pMap.find(nKey) != pMap.end() && pMap.at(nKey) && typeid(*pMap.at(nKey)).hash_code() == Typehash)	//�A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N
	{
		// =============== �� =====================
		return true;	//�A�N�Z�X�ł���E���g���k���łȂ��E�^����v���Ă���
	}
	else
	{
		// =============== �� =====================
		return false;	//�`�F�b�N�s�K��
	}
};	//std::map<int, pointer*>�̃A�N�Z�X�`�F�b�N�E�k���`�F�b�N�E�^�`�F�b�N���s���֐��I�u�W�F�N�g

#endif	//!__CONTROLL_MAP_H__