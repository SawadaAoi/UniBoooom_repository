/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	モデル管理クラス
	---------------------------------------
	ModelManager.h

	作成者
			yamashita

	変更履歴
	・2024/02/08 新規作成

========================================== */

#ifndef __MODEL_MANAGER_H__
#define __MODEL_MANAGER_H__

enum MODEL_KIND
{
	// プレイヤー
	MODEL_PLAYER,
	// スライム
	MODEL_SLIME_BLUE,
	MODEL_SLIME_GREEN,
	MODEL_SLIME_YELLOW,
	MODEL_SLIME_RED,
	MODEL_SLIME_FLAME,
	MODEL_SLIME_HEAL,
	MODEL_SLIME_ROCK,
	MODEL_SLIME_DEVIL,
	// アイテム
	MODEL_ITEM_HEART,

	MODEL_MAX,
};

// =============== インクルード ===================
#include "AnimeModel.h"
#include <unordered_map>
#include <string>

using namespace std;

class CModelManager
{
private:
	CModelManager();
	CModelManager(const CModelManager& em) {}
	CModelManager& operator=(const CModelManager& em) { return *this; }


public:
	~CModelManager() {};
	// 使用するためにこれを呼ぶ
	static CModelManager& GetInstance();
	// 呼び出しをマクロにして簡略化
#define GetModelMng CModelManager::GetInstance()

	// メンバ変数
	unordered_map<MODEL_KIND, AnimeModel*> m_pModelList;
	string m_sFileName[MODEL_MAX];
	float m_fModelSize[MODEL_MAX];
};


#endif // !__MODEL_MANAGER_H__