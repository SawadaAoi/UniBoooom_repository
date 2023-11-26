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
	・2023/11/16 シーン遷移の流れを実装 takagi
	・2023/11/17 過去シーンに戻る処理を追加 takagi
	・2023/11/23 フェード機能追加 takagi

========================================== */

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// =============== インクルード ===================
#include "Scene.h"	//メンバのヘッダ
#include "Fade.h"	//メンバのヘッダ

// =============== クラス定義 =====================
class CSceneManager	//管理
{
public:
	// ===プロトタイプ宣言===
	CSceneManager();		//コンストラクタ
	~CSceneManager();		//デストラクタ
	void Update();			//更新
	void Draw();		//描画
	bool IsFin() const;		//終了確認
private:
	// ===メンバ変数宣言=====
	CScene* m_pScene;				//シーン
	CScene::E_TYPE m_ePastScene;	//前のシーン
	CScene::E_TYPE m_eNextScene;	//シーン遷移先
	bool m_bFinish;					//終了予約用(trueで終了)
	CFade* m_pFade;					//フェード

	// ===プロトタイプ宣言===
	void ChangeScene();		//シーン変更
	void MakeNewScene();	//新シーン動的確保
};	//シーン管理

#endif	//!__SCENE_MANAGER_H__