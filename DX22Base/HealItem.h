/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�񕜃A�C�e���p�w�b�_
	------------------------------------
	HealItem.h
	------------------------------------
	�쐬��	yamashita

	�ύX����
	�E2023/11/27 h�쐬 yamashita
	�E2023/11/27 Item�N���X���p�� yamashita
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __HEAL_ITEM_H__	//HealItem.h�C���N���[�h�K�[�h
#define __HEAL_ITEM_H__

// =============== �C���N���[�h�� =====================
#include "Item.h"
#include "Model.h"
#include "Shader.h"

class CHealItem
	:public CItem
{
public:
	CHealItem(TPos3d<float> pos,Model* pModel,VertexShader* pVS);
	~CHealItem() override;

	void Update();
	void Draw();
private:
	float m_fAnimeCnt;
	Model* m_pModel;
	VertexShader* m_pVS;
};



#endif	//!__HEAL_ITEM_H__


