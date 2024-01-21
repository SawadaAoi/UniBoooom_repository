/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�A�C�e���̐e�N���X��`
	------------------------------------
	item.h
	------------------------------------
	�쐬�� yamashita

	�ύX����
	�E2023/11/27 h�쐬 yamashita
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __ITEM_H__	//Item.h�C���N���[�h�K�[�h
#define __ITEM_H__

// =============== �C���N���[�h ===================
#include "3dObject.h"
#include "Camera.h"

class CItem
	:public C3dObject
{
public:
	CItem();
	virtual ~CItem();

	void SetCamera(const CCamera* pCamera);
protected:
	const CCamera*	m_pCamera;
};



#endif	//!__ITEM_H__
