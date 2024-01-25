/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	シーン用抽象クラス実装
	---------------------------------------
	Scene.cpp
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 列挙追加・終了フラグ周り実装 takagi
	・2023/11/22 2D描画関数を追加 nieda
	・2023/11/23 サウンドファイル読み込み関数追加 nieda
	・2023/11/27 カメラ初期化 takagi
	・2023/12/07 ビュー行列取得にカメラ使用 takagi
	・2023/12/08 カメラがない時にUIが表示できない問題を修正
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2024/01/19 GetType()関数削除・その他リファクタリング takagi
	・2024/01/20 細かな修正 takagi
	・2024/01/21 コメント改修 takagi
	・2024/01/23 Zソート時複製物const化 takagi

========================================== */

// =============== インクルード ===================
#include "Scene.h"		//自身のヘッダ
#include "Delete.h"		//削除マクロ
#include <vector>		//配列コンテナ
#include <algorithm>	//ソート用
#include "ObjectDrawer.h"	//オブジェクト描画機構

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CScene::CScene()
	:m_pCamera(nullptr)	//カメラ
	,m_bFinish(false)	//シーン開始
{
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CScene::~CScene()
{
	// =============== 終了 =====================
	SAFE_DELETE_POINTER_MAP(m_p2dObjectOnScreen);	//オブジェクト削除
	SAFE_DELETE_POINTER_MAP(m_pObjectManager);		//オブジェクト削除
	SAFE_DELETE_POINTER_MAP(m_p2dObjectOnWorld);	//オブジェクト削除
	SAFE_DELETE_POINTER_MAP(m_p3dObject);			//オブジェクト削除
	SAFE_DELETE(m_pCamera);							//カメラ削除
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CScene::Update()
{
	// =============== 更新 =====================
	if (m_pCamera)	//ヌルチェック
	{
		m_pCamera->Update();	//カメラ更新
	}
	for_each(m_p3dObject.begin(), m_p3dObject.end(), [](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//ヌルチェック
		{
			pObject.second->Update();	//オブジェクト更新
		}
	});	//3Dオブジェクト更新
	for_each(m_p2dObjectOnWorld.begin(), m_p2dObjectOnWorld.end(), [](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//ヌルチェック
		{
			pObject.second->Update();	//オブジェクト更新
		}
	});	//3D表示2Dオブジェクト更新
	for_each(m_pObjectManager.begin(), m_pObjectManager.end(), [](std::pair<int, CObjectManager*> pObjectManager)->void {
		if (pObjectManager.second)	//ヌルチェック
		{
			pObjectManager.second->Update();	//マネージャ更新
		}
	});	//マネージャ更新
	for_each(m_p2dObjectOnScreen.begin(), m_p2dObjectOnScreen.end(), [](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//ヌルチェック
		{
			pObject.second->Update();	//オブジェクト更新
		}
	});	//2D表示2Dオブジェクト更新
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CScene::Draw() const
{
	//// =============== 変数宣言 =====================
	//std::vector<const CObject*> Subject;	//被写体

	//// =============== 初期化 =====================
	//for_each(m_p3dObject.begin(), m_p3dObject.end(), [&Subject](std::pair<int, CObject*> pObject)->void {
	//	if (pObject.second)	//ヌルチェック
	//	{
	//		Subject.emplace_back(pObject.second);	//オブジェクト追加
	//	}
	//});	//被写体3Dオブジェクトアドレスコピー
	//for_each(m_p2dObjectOnWorld.begin(), m_p2dObjectOnWorld.end(), [&Subject](std::pair<int, CObject*> pObject)->void {
	//	if (pObject.second)	//ヌルチェック
	//	{
	//		Subject.emplace_back(pObject.second);	//オブジェクト追加
	//	}
	//});	//被写体2Dオブジェクトアドレスコピー
	//for_each(m_pObjectManager.begin(), m_pObjectManager.end(), [&Subject](std::pair<int, CObjectManager*> pObjectManager)->void {
	//	if (pObjectManager.second)	//ヌルチェック
	//	{
	//		pObjectManager.second->GetObjects(Subject);	//オブジェクト追加
	//	}
	//});	//管理されているオブジェクトアドレスコピー

	//// =============== Zソート =====================
	//std::sort(Subject.begin(), Subject.end(), [](const CObject* pFirst, const CObject* pSecond)->bool {
	//	return pFirst && pSecond					//ヌルチェック
	//		? pFirst->GetPosZ() > pFirst->GetPosZ()	//奥のものから描画(等価の場合は入れ替えない)
	//		: false;								//片方はnullなので比較する必要がない
	//});	//オブジェクトのソート

	//// =============== 3D空間描画 =====================
	//for_each(Subject.begin(), Subject.end(), [](const CObject* pObject)->void {
	//	if (pObject)	//ヌルチェック
	//	{
	//		pObject->Draw();	//描画
	//	}
	//});	//ソート順に描画

	//// =============== 2D空間描画 =====================
	//for_each(m_p2dObjectOnScreen.begin(), m_p2dObjectOnScreen.end(), [](std::pair<int, const CObject*> pObject)->void {
	//	if (pObject.second)	//ヌルチェック
	//	{
	//		pObject.second->Draw();	//オブジェクト描画
	//	}
	//});	//キー順に描画

	CObjectDrawer::Draw();
}

/* ========================================
	終了確認関数
	----------------------------------------
	内容：シーンをやめるかどうかのフラグを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：true:シーンをやめたい / false:シーンを続けたい
=========================================== */
bool CScene::IsFin() const
{
	// =============== 提供 =====================
	return m_bFinish;	//終了要求フラグ
}

/* ========================================
   カメラポインタ取得関数
   -------------------------------------
   内容：カメラクラスのポインタ取得
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：無し
=========================================== */
CCamera* CScene::GetCamera() const
{
	// =============== 提供 =====================
	return m_pCamera;	//カメラ提供
}