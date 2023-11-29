/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	アイテムの親クラスh
	------------------------------------
	item.h
	------------------------------------
	作成者 yamashita

	変更履歴
	・2023/11/27 h作成 yamashita

========================================== */

#ifndef __ITEM_H__
#define __ITEM_H__

// =============== インクルード ===================
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
