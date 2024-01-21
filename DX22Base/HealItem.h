/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	回復アイテム用ヘッダ
	------------------------------------
	HealItem.h
	------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/27 h作成 yamashita
	・2023/11/27 Itemクラスを継承 yamashita
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __HEAL_ITEM_H__	//HealItem.hインクルードガード
#define __HEAL_ITEM_H__

// =============== インクルード部 =====================
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


