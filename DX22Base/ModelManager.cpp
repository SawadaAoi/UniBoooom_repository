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

#include "ModelManager.h"
#include "ShaderList.h"

/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CModelManager::CModelManager()
{
	m_fModelSize[MODEL_PLAYER] = 1.0f;			// プレイヤーのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_BLUE] = 0.15f;		// 青スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_GREEN] = 0.15f;	// 緑スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_YELLOW] = 0.21f;	// 黄色スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_RED] = 0.18f;		// 赤スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_FLAME] = 0.3f;		// 炎スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_HEAL] = 0.45f;		// 回復スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_ROCK] = 0.5f;		// 岩スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_DEVIL] = 0.23f;	// デビルスライムのモデルサイズの倍率
	m_fModelSize[MODEL_ITEM_HEART] = 1.0f;		// 回復アイテムのハートのモデルサイズの倍率

	m_sFileName[MODEL_PLAYER]		 = "Assets/Model/player/pow.FBX";						// プレイヤーのモデルのファイル名
	m_sFileName[MODEL_SLIME_BLUE]	= "Assets/Model/slime/Blue/slime_blue_walk_1.0.fbx";	// 青スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_GREEN]	= "Assets/Model/slime/Green/slime_green_walk_1.0.fbx";	// 緑スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_YELLOW] = "Assets/Model/slime/Yellow/slime_yellow_walk_1.0.fbx";// 黄色スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_RED]	= "Assets/Model/slime/Red/slime_red_walk_1.0.fbx";		// 赤スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_FLAME]	= "Assets/Model/flameSlime/fire_walk.fbx";				// 炎スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_HEAL]	= "Assets/Model/healSlime/heal_walk.fbx";				// 回復スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_ROCK]	= "Assets/Model/boss_slime_rock/rock_walk_2.0.fbx";		// 岩スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_DEVIL]	= "Assets/Model/boss_slime_devil/devil_walk.fbx";		// デビルスライムのモデルのファイル名
	m_sFileName[MODEL_ITEM_HEART]	= "Assets/Model/heart/heart_1.FBX";						// 回復アイテムのハートのモデルのファイル名
	
	// 各モデルの読み込み
	for (int i = 0; i < (int)MODEL_MAX; i++)
	{
		// モデルの動的確保
		m_ModelList.emplace(MODEL_KIND(i), new AnimeModel());
		// モデルの読み込み
		if (!m_ModelList.at(MODEL_KIND(i))->Load(m_sFileName[MODEL_KIND(i)].c_str(), m_fModelSize[MODEL_KIND(i)], AnimeModel::XFlip)) {		//倍率と反転は省略可
			MessageBox(NULL, m_sFileName[MODEL_KIND(i)].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
		// 頂点シェーダーをセット
		m_ModelList.at((MODEL_KIND)i)->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));	
	}

	// アニメーション読み込み
	LoadAnime();
}

/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CModelManager::~CModelManager()
{
	// 動的確保したモノを削除
	for (int i = 0; i, MODEL_KIND(i); i++)
	{
		SAFE_DELETE(m_ModelList.at(MODEL_KIND(i)));
	}
}


/* ========================================
   関数：クラスの作成および取得関数
   ----------------------------------------
   内容：クラスをインスタンスして取得する(既に作成されている場合は作成しない)
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：このクラス
======================================== */
CModelManager & CModelManager::GetInstance()
{
	static CModelManager modelManager; return modelManager;
}

/* ========================================
   関数：アニメーション読み込み関数
   ----------------------------------------
   内容：それぞれのアニメーションを読み込む関数
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CModelManager::LoadAnime()
{

	for (int i = 0; i < CPlayer::MOTION_PLAYER_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_PLAYER)->AddAnimation(m_sPlayerMotion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_PLAYER)->GetAnimation(i))
		{
			MessageBox(NULL, m_sPlayerMotion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	//青スライムのアニメーション読み込み
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL1_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_BLUE)->AddAnimation(m_sLevel1_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_BLUE)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel1_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	//緑スライムのアニメーション読み込み
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL2_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_GREEN)->AddAnimation(m_sLevel2_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_GREEN)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel2_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	//黄色スライムのアニメーション読み込み
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL3_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_YELLOW)->AddAnimation(m_sLevel3_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_YELLOW)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel3_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	//赤スライムのアニメーション読み込み
	for (int i = 0; i < CSlimeBase::MOTION_LEVEL4_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_RED)->AddAnimation(m_sLevel4_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_RED)->GetAnimation(i))
		{
			MessageBox(NULL, m_sLevel4_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	// 炎スライムのアニメーション読み込み
	for (int i = 0; i < CSlimeBase::FLAME_SLIME_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_FLAME)->AddAnimation(m_sFlameSlime_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_FLAME)->GetAnimation(i))
		{
			MessageBox(NULL, m_sFlameSlime_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	// 回復スライムのアニメーション読み込み
	for (int i = 0; i < CSlimeBase::HEAL_SLIME_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_HEAL)->AddAnimation(m_sHealSlime_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_HEAL)->GetAnimation(i))
		{
			MessageBox(NULL, m_sHealSlime_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	// デビルスライムのアニメーション読み込み
	for (int i = 0; i < CSlime_BossBase::DEVIL_SLIME_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_DEVIL)->AddAnimation(m_sDevilSlime_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_DEVIL)->GetAnimation(i))
		{
			MessageBox(NULL, m_sDevilSlime_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}

	// 岩スライムのアニメーション読み込み
	for (int i = 0; i < CSlime_BossBase::ROCK_SLIME_MAX; i++)
	{
		//各アニメーションの読み込み
		m_ModelList.at(MODEL_SLIME_ROCK)->AddAnimation(m_sRockSlime_Motion[i].c_str());
		//読み込みに失敗したらエラーメッセージ
		if (!m_ModelList.at(MODEL_SLIME_ROCK)->GetAnimation(i))
		{
			MessageBox(NULL, m_sRockSlime_Motion[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}
}

/* ========================================
   関数：モデル取得関数
   ----------------------------------------
   内容：指定したモデルを取得する関数
   ----------------------------------------
   引数：モデルの種類
   ----------------------------------------
   戻値：モデルポインタ
======================================== */
AnimeModel * CModelManager::GetModelPtr(MODEL_KIND model)
{
	return m_ModelList.at(model);
}
