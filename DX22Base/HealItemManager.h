/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem管理用ヘッダ
	------------------------------------
	HealItemManager.h
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/27 h作成 yamashita
	・2023/11/28 vectorでリストを作成 yamashita

========================================== */
#ifndef __HEALITEM_MANAGER_H__
#define __HEALITEM_MANAGER_H__

// =============== インクルード部 =====================
#include "HealItem.h"
#include "Model.h"
#include "Shader.h"

class CHealItemManager
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
};

#endif // !__HEALITEM_MANAGER_H__
