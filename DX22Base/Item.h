/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	アイテムの親クラス定義
	------------------------------------
	item.h
	------------------------------------
	作成者 yamashita

	変更履歴
	・2023/11/27 h作成 yamashita
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __ITEM_H__	//Item.hインクルードガード
#define __ITEM_H__

// =============== インクルード ===================
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
