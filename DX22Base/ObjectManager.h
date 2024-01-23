/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン用抽象クラス定義
	---------------------------------------
	ObjectManager.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/21 制作 takagi
	・2024/01/23 制作進行 takagi

========================================== */

#ifndef __OBJECT_MANAGER_H__	//ObjectManager.hインクルードガード
#define __OBJECT_MANAGER_H__

// =============== インクルード ===================
#include "Camera.h"	//メンバのヘッダ
#include "Object.h"	//メンバのヘッダ
#include <vector>	//連想型配列

// =============== クラス定義 =====================
class CObjectManager
{
public:
	// ===プロトタイプ宣言===
	CObjectManager();													//コンストラクタ
	virtual ~CObjectManager();											//デストラクタ
	virtual void Update();												//更新
	virtual void SetCamera(const CCamera* pCamera);						//カメラセッタ
	virtual void GetObjects(std::vector<const CObject*>& Object) final;	//オブジェクトゲッタ
protected:
	// ===メンバ変数宣言=====
	std::vector<CObject*> m_pObject;	//オブジェクト
	const CCamera* m_pCamera;			//カメラ	deleteしない、ポインタは受け取り専用
};	//マネージャ

#endif	//!__OBJECT_MANAGER_H__