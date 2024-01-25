/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	Zソート描画定義
	---------------------------------------
	MakeObjectVector.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/24 制作 takagi

========================================== */

#ifndef __MAKE_OBJECT_VECTOR_H__	//MakeObjectVector.hインクルードガード
#define __MAKE_OBJECT_VECTOR_H__

// =============== インクルード =====================
#include "Object.h"			//オブジェクト
#include "ObjectManager.h"	//オブジェクト管理
#include <vector>			//配列コンテナ
#include <algorithm>			//ソート用

// =============== クラス定義 =====================
class CMakeObjectVector
{
public:
	// ===プロトタイプ宣言===
	template<typename Key> static void PushObjectVector(std::vector<const CObject*>& pContainer, 
		const std::map<Key, CObject*>& pObject);				//オブジェクト格納
	template<typename Key> static void PushObjectVector(std::vector<const CObject*>& pContainer,
		const std::map<Key, const CObject*>& pObject);			//オブジェクト格納
	template<typename Key> static void PushObjectVector(std::vector<const CObject*>& pContainer,
		const std::map<Key, CObjectManager*>& pObjectManager);	//オブジェクト格納
};	//Zソート描画

/* ========================================
	オブジェクト格納関数
	-------------------------------------
	内容：引数2で受け取った描画物のアドレスを引数1で受け取った格納先に格納する
	-------------------------------------
	引数1：std::vector<const CObject*>& pContainer：格納先のコンテナ
	引数2：const std::map<Key, CObject*>& pObject：格納するオブジェクト
	-------------------------------------
	戻値：無し
=========================================== */
template<typename Key>	//テンプレート関数実装
void CMakeObjectVector::PushObjectVector(std::vector<const CObject*>& pContainer, const std::map<Key, CObject*>& pObject)
{
	// =============== 初期化 =====================
	for_each(pObject.begin(), pObject.end(), [&pContainer](std::pair<int, CObject*> pObject)->void {
		if (pObject.second)	//ヌルチェック
		{
			pContainer.emplace_back(pObject.second);	//オブジェクト追加
		}
	});	//被写体オブジェクトアドレスコピー
}

/* ========================================
	オブジェクト格納関数
	-------------------------------------
	内容：引数2で受け取った管理者が持つ描画物のアドレスを引数1で受け取った格納先に格納する
	-------------------------------------
	引数1：std::vector<const CObject*>& pContainer：格納先のコンテナ
	引数2：const std::map<Key, CObjectManager*>& pObjectManager：格納するオブジェクトを管理するもの
	-------------------------------------
	戻値：無し
=========================================== */
template<typename Key>	//テンプレート関数実装
void CMakeObjectVector::PushObjectVector(std::vector<const CObject*>& pContainer, const std::map<Key, CObjectManager*>& pObjectManager)
{
	for_each(pObjectManager.begin(), pObjectManager.end(), [&pContainer](std::pair<int, CObjectManager*> pObjectManager)->void {
		if (pObjectManager.second)	//ヌルチェック
		{
			pObjectManager.second->GetObjects(pContainer);	//オブジェクト追加
		}
	});	//管理されているオブジェクトアドレスコピー
}

#endif	//!__MAKE_OBJECT_VECTOR_H__