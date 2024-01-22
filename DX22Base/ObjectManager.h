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

========================================== */

#ifndef __OBJECT_MANAGER_H__	//ObjectManager.hインクルードガード
#define __OBJECT_MANAGER_H__

// =============== インクルード ===================
#include "Camera.h"		//メンバのヘッダ
#include <3dObject.h>	//メンバのヘッダ
#include <2dObject.h>	//メンバのヘッダ
//#include <ObjManager.h>	//メンバのヘッダ
#include <map>			//連想型配列

// =============== クラス定義 =====================
class CObjectManager
{
public:
	// ===列挙定義===========
	enum E_TYPE
	{
		E_TYPE_TITLE,			//タイトルシーン
		//E_TYPE_PROT,			//プロトタイプ
		E_TYPE_SELECT_STAGE,	//ステージセレクト
		E_TYPE_STAGE1,			//ステージ1
		E_TYPE_STAGE2,			//ステージ2
		E_TYPE_STAGE3,			//ステージ3
		E_TYPE_RESULT,			//リザルトシーン
		E_TYPE_MAX,				//要素数
		E_TYPE_NONE = -255,		//該当なし
		E_TYPE_PAST,			//前のシーン
		E_TYPE_FINISH_ALL,		//アプリ自体を終える
	};	//シーンの種類
public:
	// ===プロトタイプ宣言===
	CObjectManager();							//コンストラクタ
	virtual ~CObjectManager();					//デストラクタ
	virtual void Update();				//更新
	virtual void Draw();				//描画
	bool IsFin() const;					//終了確認
	virtual E_TYPE GetNext() const = 0;	//次のシーンゲッタ
	CCamera* GetCamera() const;			//カメラゲッタ

protected:
	// ===メンバ変数宣言=====
	std::map<int, CObject*> m_p3dObject;	//オブジェクト(各シーンで更新順に定義した列挙をキーとする)
	CCamera* m_pCamera;						//カメラ	deleteしない、ポインタは受け取り専用
};	//シーン

#endif	//!__OBJECT_MANAGER_H__