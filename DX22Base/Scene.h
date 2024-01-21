/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン用抽象クラス定義
	---------------------------------------
	Scene.h
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/10/26 GetType()関数の戻り値を修正 takagi
	・2023/11/04 列挙中身追加 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 列挙追加・GetNext()関数追加・終了フラグ周り実装・コメント修正 takagi
	・2023/11/17 列挙中身追加 takagi
	・2023/11/22 2D描画関数宣言 nieda
	・2023/11/23 サウンドファイル読み込み関数用変数追加 nieda
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2023/12/15 列挙中身追加 takagi
	・2024/01/19 GetType()関数削除・その他リファクタリング takagi
	・2024/01/20 コメント改修 takagi

========================================== */

#ifndef __SCENE_H__	//Scene.hインクルードガード
#define __SCENE_H__

// =============== インクルード ===================
#include "Camera.h"		//メンバのヘッダ
#include <3dObject.h>	//メンバのヘッダ
#include <2dObject.h>	//メンバのヘッダ
//#include <ObjManager.h>	//メンバのヘッダ
#include <map>			//連想型配列

// =============== クラス定義 =====================
class CScene
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
	CScene();							//コンストラクタ
	virtual ~CScene();					//デストラクタ
	virtual void Update();				//更新
	virtual void Draw();				//描画
	bool IsFin() const;					//終了確認
	virtual E_TYPE GetNext() const = 0;	//次のシーンゲッタ
	CCamera* GetCamera() const;			//カメラゲッタ
protected:
	// ===メンバ変数宣言=====
	std::map<int, C3dObject*> m_p3dObject;	//オブジェクト(各シーンで更新順に定義した列挙をキーとする)
	std::map<int, C2dObject*> m_p2dObject;
	bool m_bFinish;						//終了予約用(trueで終了)
	CCamera* m_pCamera;					//カメラ
};	//シーン

#endif	//!__SCENE_H__