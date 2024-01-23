/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�񕜃A�C�e���Ǘ��p�w�b�_
	------------------------------------
	HealItemManager.h
	------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/27 h�쐬 yamashita
	�E2023/11/28 vector�Ń��X�g���쐬 yamashita
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __HEAL_ITEM_MANAGER_H__	//HealItemManager.h�C���N���[�h�K�[�h
#define __HEAL_ITEM_MANAGER_H__

// =============== �C���N���[�h�� =====================
#include "ObjectManager.h"	//�e�̃w�b�_
#include "HealItem.h"
#include "Model.h"
#include "Shader.h"

class CHealItemManager :public CObjectManager	//�I�u�W�F�N�g�Ǘ�
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
};	//�񕜃A�C�e���Ǘ�

#endif	//!__HEAL_ITEM_MANAGER_H__
