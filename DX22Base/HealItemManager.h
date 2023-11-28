/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem�Ǘ��p�w�b�_
	------------------------------------
	HealItemManager.h
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/27 h�쐬 yamashita
	�E2023/11/28 vector�Ń��X�g���쐬 yamashita

========================================== */
#ifndef __HEALITEM_MANAGER_H__
#define __HEALITEM_MANAGER_H__

// =============== �C���N���[�h�� =====================
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
