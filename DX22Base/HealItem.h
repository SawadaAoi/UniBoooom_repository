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
	・2023/11/23 h作成 yamashita
	・2023/11/23 構造体HEAL_ITEMを作成 yamashita
========================================== */


// =============== インクルード部 =====================
#include "Camera.h"
#include "Transform3d.h"
#include "Shader.h"
#include "Model.h"

#ifndef __HEART_ITEM_H__
#define __HEART_ITEM_H__

class CHealItem
{
public:
	CHealItem();
	~CHealItem();
	void Update();
	void Draw();

	void Create(TPos3d<float> pos);
	void SetCamera(const CCamera* pCamera);	//カメラセット関数


private:
	struct HEAL_ITEM
	{
		tagTransform3d m_Transform;	//ワールド座標系情報
		int		m_Cnt;				//消去されるまでの時間を測る
		bool	m_bUse;				//まだ存在してるかのチェック
	};

	// ===メンバ変数宣言=====
	std::vector<HEAL_ITEM> m_healItem;			//構造体のコンテナ
	Model* m_pModel;							//3Dモデル
	VertexShader* m_pVS;						//バーテックスシェーダーのポインタ
	const CCamera* m_pCamera;					//カメラのポインタ
};



#endif // !__HEART_ITEM_H__


