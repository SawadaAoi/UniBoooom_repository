/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	マップ操作定義
	---------------------------------------
	ControllMap.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/23 制作 takagi

========================================== */

#ifndef __CONTROLL_MAP_H__	//ControllMap.hインクルードガード
#define __CONTROLL_MAP_H__

// =============== グローバル変数宣言 ===================
static auto ACCESS_NULL_CHECK = [](auto pMap, int nKey)->bool
//auto pMap：std::map<int, pointer*>のこと。
//int nKey：↑の指定したい添え字番号。
{
	if (pMap.find(nKey) != pMap.end() && pMap.at(nKey))	//アクセスチェック・ヌルチェック
	{
		// =============== 提供 =====================
		return true;	//アクセスできる・中身がヌルでない
	}
	else
	{
		// =============== 提供 =====================
		return false;	//チェック不適合
	}
};	//std::map<int, pointer*>のアクセスチェック・ヌルチェックを行う関数オブジェクト
static auto ACCESS_NULL_TYPE_CHECK = [](auto pMap, const int& nKey, const size_t& Typehash)->bool
//auto pMap				：std::map<int, pointer*>のこと。
//const int& nKey		：↑の指定したい添え字番号。
//const size_t& Typehash：型チェックしたい型IDのハッシュコード。
{
	// =============== 検査 =====================
	if (pMap.find(nKey) != pMap.end() && pMap.at(nKey) && typeid(*pMap.at(nKey)).hash_code() == Typehash)	//アクセスチェック・ヌルチェック・型チェック
	{
		// =============== 提供 =====================
		return true;	//アクセスできる・中身がヌルでない・型が一致している
	}
	else
	{
		// =============== 提供 =====================
		return false;	//チェック不適合
	}
};	//std::map<int, pointer*>のアクセスチェック・ヌルチェック・型チェックを行う関数オブジェクト

#endif	//!__CONTROLL_MAP_H__