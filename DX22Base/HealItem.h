/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem用ヘッダ
	------------------------------------
	HealItem.h
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/27 h作成 yamashita
	・2023/11/27 Itemクラスを継承 yamashita

========================================== */


// =============== インクルード部 =====================
#include "Item.h"
#include "Model.h"
#include "Shader.h"

#ifndef __HEART_ITEM_H__
#define __HEART_ITEM_H__

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



#endif // !__HEART_ITEM_H__


