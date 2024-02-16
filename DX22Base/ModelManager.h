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
#include "SlimeBase.h"
#include "Slime_BossBase.h"
#include "Player.h"

using namespace std;

class CModelManager
{
private:
	CModelManager();
	CModelManager(const CModelManager& em) {}
	CModelManager& operator=(const CModelManager& em) { return *this; }


public:
	~CModelManager();
	// 使用するためにこれを呼ぶ
	static CModelManager& GetInstance();
	// 呼び出しをマクロにして簡略化
#define GetModelMng CModelManager::GetInstance()
	void LoadAnime();
	AnimeModel* GetModelPtr(MODEL_KIND model);	// モデル取得関数

	// メンバ変数
	unordered_map<MODEL_KIND, AnimeModel*> m_ModelList;
	string m_sFileName[MODEL_MAX];
	float m_fModelSize[MODEL_MAX];

	//========== アニメ ==========
	// プレイヤー
	const std::string m_sPlayerMotion[CPlayer::MOTION_PLAYER_MAX] = {	//アニメーションのファイル
		"Assets/Model/player/wait_end.FBX",			//待機
		"Assets/Model/player/dash_v2.FBX",				//移動
		"Assets/Model/player/POW.FBX",				//スイング
		"Assets/Model/player/ChargeDash_v1.FBX",				//チャージ状態
		"Assets/Model/player/down.fbx",				//死亡

	};

	// 青スライム
	const std::string m_sLevel1_Motion[CSlimeBase::MOTION_LEVEL1_MAX] = {
		"Assets/Model/slime/Blue/slime_blue_walk_1.0.fbx",		// レベル1スライムの移動モーション
		"Assets/Model/slime/Blue/slime_blue_damaged_1.1.fbx",	// レベル1スライムの叩かれたときのモーション
	};

	// 緑スライム
	const std::string m_sLevel2_Motion[CSlimeBase::MOTION_LEVEL2_MAX] = {
	"Assets/Model/slime/Green/slime_green_walk_1.0.fbx",		// レベル2スライムの移動モーション
	"Assets/Model/slime/Green/slime_green_damaged_1.0.fbx",		// レベル2スライムの叩かれたときのモーション
	"Assets/Model/slime/Green/slime_green_rush_1.0.fbx",		// レベル2スライムの攻撃モーション
	};

	// 黄色スライム
	const std::string m_sLevel3_Motion[CSlimeBase::MOTION_LEVEL3_MAX] = {
	"Assets/Model/slime/Yellow/slime_yellow_walk_1.0.fbx",		// レベル3スライムの移動モーション
	"Assets/Model/slime/Yellow/slime_yellow_damaged_1.0.fbx",	// レベル3スライムの叩かれたときのモーション
	"Assets/Model/slime/Yellow/slime_yellow_mekakushi_1.1.fbx",	// レベル3スライム静止状態のモーション
	};

	// 赤スライム
	const std::string m_sLevel4_Motion[CSlimeBase::MOTION_LEVEL4_MAX] = {
		"Assets/Model/slime/Red/slime_red_walk_1.0.fbx",		// レベル1スライムの移動モーション
		"Assets/Model/slime/Red/slime_red_damaged_1.0.fbx",	// レベル1スライムの叩かれたときのモーション
	};

	// 炎スライム
	const std::string m_sFlameSlime_Motion[CSlimeBase::FLAME_SLIME_MAX] = {
		"Assets/Model/flameSlime/fire_walk.fbx",	// 炎スライムの移動モーション
		"Assets/Model/flameSlime/fire_damaged.fbx",	// 炎スライムの被ダメモーション
	};

	// ヒールスライム
	const std::string m_sHealSlime_Motion[CSlimeBase::HEAL_SLIME_MAX] = {
		"Assets/Model/healSlime/heal_walk.fbx",		// ヒールスライムの移動モーション
		"Assets/Model/healSlime/heal_damaged.fbx",	// ヒールスライムの被ダメモーション
	};

	// 岩スライム
	const std::string m_sRockSlime_Motion[CSlime_BossBase::ROCK_SLIME_MAX] = {
		"Assets/Model/boss_slime_rock/rock_walk_1.1.fbx",		// 岩スライムの移動モーション
		"Assets/Model/boss_slime_rock/rock_damaged_2.0.fbx",	// 岩スライムの被ダメモーション
		"Assets/Model/boss_slime_rock/rock_rolling_2.0.fbx",	// 岩スライムの攻撃モーション
	};

	// デビルスライム
	const std::string m_sDevilSlime_Motion[CSlime_BossBase::DEVIL_SLIME_MAX] = {
		"Assets/Model/boss_slime_devil/devil_walk.fbx",		// デビルスライムの移動モーション
		"Assets/Model/boss_slime_devil/devil_damaged.fbx",	// デビルスライムの被ダメモーション
	};
};


#endif // !__MODEL_MANAGER_H__