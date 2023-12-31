/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン管理定義
	---------------------------------------
	SceneManager.h

	作成者	takagi

	変更履歴
	・2023/10/24	仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi

========================================== */

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// =============== インクルード ===================
#include "Scene.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CSceneManager	//管理
{
public:
	// ===プロトタイプ宣言===
	CSceneManager();		//コンストラクタ
	~CSceneManager();		//デストラクタ
	void Update();			//更新
	void Draw() const;		//描画
private:
	// ===メンバ変数宣言=====
	CScene* m_pScene;	//シーン
};	//シーン管理

#endif	//!__SCENE_MANAGER_H__