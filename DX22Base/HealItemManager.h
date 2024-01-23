/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	回復アイテム管理用ヘッダ
	------------------------------------
	HealItemManager.h
	------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/27 h作成 yamashita
	・2023/11/28 vectorでリストを作成 yamashita
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __HEAL_ITEM_MANAGER_H__	//HealItemManager.hインクルードガード
#define __HEAL_ITEM_MANAGER_H__

// =============== インクルード部 =====================
#include "ObjectManager.h"	//親のヘッダ
#include "HealItem.h"
#include "Model.h"
#include "Shader.h"

class CHealItemManager :public CObjectManager	//オブジェクト管理
{
public:
	CHealItemManager();
	~CHealItemManager();

	void Update();
	void Draw();
	void Create(TPos3d<float> pos);

	std::vector<CHealItem*>* GetHealItemConPtr();

	void SetCamera(const CCamera* pCamera);
private:
	std::vector<CHealItem*> m_pHealItemList;
	Model* m_pModel;
	VertexShader* m_pVS;
	const CCamera* m_pCamera;
};	//回復アイテム管理

#endif	//!__HEAL_ITEM_MANAGER_H__
