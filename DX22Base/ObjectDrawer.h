/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	オブジェクト描画定義
	---------------------------------------
	ObjectDrawer.h
	---------------------------------------
	作成者	takagi

	変更履歴
	・2024/01/21 制作 takagi
	・2024/01/23 制作進行 takagi

========================================== */

#ifndef __OBJECT_DRAWER_H__	//ObjectDrawer.hインクルードガード
#define __OBJECT_DRAWER_H__

// =============== インクルード ===================
#include "Object.h"	//オブジェクト
#include <vector>	//配列コンテナ
#include <climits>	//

// =============== クラス定義 =====================
class CObjectDrawer
{
private:
	// ===定数定義===========
	static const unsigned int DEAD_KEY = (std::numeric_limits<unsigned int>::max)();	//使用しないキー
	static const unsigned int MAX_OBJECT = DEAD_KEY - 1;								//同時に存在できるオブジェクトの最大数
public:
	// ===プロトタイプ宣言===
	static unsigned int AddObject(CObject* pObject);		//新規オブジェクト追加
	static void RemoveObject(const unsigned int& unKey);	//オブジェクト除去
#if _DEBUG
	static void CheckAliveObject();							//生存オブジェクト検査
#endif	//_!DEBUG
	static void Draw();										//描画
private:
	// ===メンバ変数宣言=====
	static std::map<unsigned int, CObject*> m_pObject;	//オブジェクトnew/delete時に操作されるコンテナ
	//static std::vector<CObject*> m_pObject;			//オブジェクトnew/delete時に操作されるコンテナ
};	//オブジェクト描画

#endif	//!__OBJECT_DRAWER_H__