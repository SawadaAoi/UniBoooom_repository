/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem�p�w�b�_
	------------------------------------
	HealItem.h
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/27 h�쐬 yamashita
	�E2023/11/27 Item�N���X���p�� yamashita

========================================== */


// =============== �C���N���[�h�� =====================
#include "Item.h"
#include "Model.h"
#include "Shader.h"
#include "ShaderList.h"
#include "AnimeModel.h"

#ifndef __HEART_ITEM_H__
#define __HEART_ITEM_H__

class CHealItem
	:public CItem
{
public:
	CHealItem(TPos3d<float> pos, AnimeModel* pModel);
	~CHealItem() override;

	void Update();
	void Draw();
private:
	float m_fAnimeCnt;
	AnimeModel* m_pModel;
};



#endif // !__HEART_ITEM_H__


