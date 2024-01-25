/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	オブジェクト描画実装
	---------------------------------------
	ObjectDrawer.cpp
	---------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/24 制作 takagi

========================================== */

// =============== インクルード ===================
#include "ObjectDrawer.h"		//自身のヘッダ
#include "ControllMap.h"		//map操作
#include "ZSort.h"				//Zソートで描画する
#include "MakeObjectVector.h"	//map→vector
#if _DEBUG
#include <Windows.h>	//メッセージボックス用
#endif	//_!DEBUG

// =============== グローバル変数宣言 ===================
std::map<unsigned int, CObject*> CObjectDrawer::m_pObject;	//オブジェクトnew/delete時に操作されるコンテナ

/* ========================================
	オブジェクト追加関数
	-------------------------------------
	内容：引数で受け取ったオブジェクトを自身のコンテナに追加する
	-------------------------------------
	引数1：CObject* pObject：新規オブジェクト
	-------------------------------------
	戻値：mapの格納場所(キー)
=========================================== */
unsigned int CObjectDrawer::AddObject(CObject* pObject)
{
	// =============== 探索 =====================
	for (unsigned int unKey = (std::numeric_limits<unsigned int>::min)(); unKey < MAX_OBJECT; unKey++)	//キーの空きを探す
	{
		// =============== 検査 =====================
		if (ACCESS_NULL_CHECK(m_pObject, unKey))	//アクセス・ヌルチェック
		{
			// =============== パス =====================
			continue;	//次の候補へ
		}
		if (m_pObject.find(unKey) != m_pObject.end())	//ヌルの中身が存在
		{
			// =============== 削除 =====================
			m_pObject.erase(unKey);	//動的確保しているはずなのでヌルの中身は異常。削除して要素を格納する場所とする
		}

		// =============== 格納 =====================
		m_pObject.emplace(unKey, pObject);	//アドレス格納

		// =============== 終了 =====================
		return unKey;	//格納場所を指すキー提供
	}

	// =============== 限界超過 =====================
#if _DEBUG
	std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
	MessageBox(nullptr, (ErrorSpot + "オブジェクトの存在数が限界を超過しました").c_str(), "Error", MB_OK | MB_ICONERROR);				//エラー通知
#endif	//_!DEBUG
	return DEAD_KEY;	//使用していない枠を代替値として返す
}

/* ========================================
	オブジェクト除去関数
	-------------------------------------
	内容：引数で受け取った添え字の中身を自身のコンテナから削除する
	-------------------------------------
	引数1：const unsigned int & unKey：コンテナのキー
	-------------------------------------
	戻値：なし
=========================================== */
void CObjectDrawer::RemoveObject(const unsigned int & unKey)
{
	// =============== 検査 =====================
	if (DEAD_KEY == unKey)	//キーチェック
	{
		// =============== 終了 =====================
		return;	//使用されていないキーを無視
	}

	// =============== 検査 =====================
	if (m_pObject.find(unKey) != m_pObject.end())	//アクセスチェック
	{
		if (m_pObject.at(unKey))	//ヌルチェック
		{
//#if _DEBUG
//			std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";									//エラー箇所
//			MessageBox(nullptr, (ErrorSpot + "deleteに失敗したオブジェクトが見つかりました：" + typeid(*m_pObject.at(unKey)).name()).c_str(), "Error", MB_OK | MB_ICONERROR);	//エラー通知
//#else
//			delete m_pObject.at(unKey);	//削除	※デバッグ中はメモリリークに気づきやすいように削除しない
//#endif	//_!DEBUG
			//↑想定していたタイミングが変わったので無効化
		}
		
		// =============== 削除 =====================
		m_pObject.erase(unKey);	//オブジェクト除去
	}
}

#if _DEBUG
/* ========================================
	関数オブジェクト生存検査関数
	-------------------------------------
	内容：管理しているオブジェクトで残っているものを検出し、通知する。メモリリーク確認用。
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CObjectDrawer::CheckAliveObject()
{
	// =============== 探索 =====================
	for (unsigned int unKey = (std::numeric_limits<unsigned int>::min)(); unKey < MAX_OBJECT; unKey++)	//残っているキーを探す
	{
		// =============== 検査 =====================
		if (ACCESS_NULL_CHECK(m_pObject, unKey))	//アクセス・ヌルチェック
		{
			// =============== パス =====================
			continue;	//次の候補へ
		}
		if (m_pObject.find(unKey) != m_pObject.end())	//ヌルの中身が存在
		{
			MessageBox(nullptr, (static_cast<std::string>("キーのみ生存しています：") + std::to_string(unKey)).c_str(), "Error", MB_OK | MB_ICONERROR);							//エラー通知
		}
		else
		{
			MessageBox(nullptr, (static_cast<std::string>("メモリリークのおそれがあります：") + typeid(*m_pObject.at(unKey)).name()).c_str(), "Error", MB_OK | MB_ICONERROR);	//エラー通知
		}
	}
}
#endif	//_!DEBUG

/* ========================================
	関数オブジェクト描画関数
	-------------------------------------
	内容：管理しているオブジェクトすべてをZソート法で描画。
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CObjectDrawer::Draw()
{
	// =============== 変数宣言 =====================
	std::vector<const CObject*> pSubject;	//被写体

	// =============== 初期化 =====================
	CMakeObjectVector::PushObjectVector(pSubject, m_pObject);	//コンテナ初期化

	// =============== 描画 =====================
	CZSort::DrawWithZSort(pSubject);	//Zソートを使用した描画
}