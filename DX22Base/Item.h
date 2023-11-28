/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�A�C�e���̐e�N���Xh
	------------------------------------
	item.h
	------------------------------------
	�쐬�� yamashita

	�ύX����
	�E2023/11/27 h�쐬 yamashita

========================================== */

#ifndef __ITEM_H__
#define __ITEM_H__

// =============== �C���N���[�h ===================
#include "Object.h"
#include "Camera.h"

class CItem
	:public CObject
{
public:
	CItem();
	virtual ~CItem();

	void SetCamera(const CCamera* pCamera);
protected:
	const CCamera*	m_pCamera;
};



#endif // !__ITEM_H__
