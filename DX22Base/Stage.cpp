/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ用抽象クラス実装
	!memo：当たり判定関連の処理はCollisionOfStage.cppに記載
	---------------------------------------
	Stage.cpp
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/01 サウンドの読み込み yamashita
	・2023/12/04 ポーズクラス追加・デストラクタ復活 takagi
	・2023/12/05 コメント修正 takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2023/12/15 ゲームスタート表示書き変えに伴い必要なくなった変数削除 nieda
	・2023/12/15 フェード削除 takagi
	・2023/12/18 ポーズ動的確保 takagi
	・2023/12/28 BattleData格納処理をまとめた関数を追加	Sawada
	・2024/01/01 ステージ分岐 Takagi
	・2024/01/19 GetType()関数削除・その他リファクタリング takagi
	・2024/01/21 コメント改修 takagi
	・2024/01/23 親関数呼出 takagi

========================================== */

// =============== インクルード ===================
#include "Stage.h"			//自身のヘッダ
#include "HitStop.h"		//ヒットストップ
#include "ControllMap.h"	//map操作
#if _DEBUG
#include <Windows.h>		//メッセージボックス用
#endif
#include "BossArrow.h"

//* ========================================
//	コンストラクタ
//	----------------------------------------
//	内容：生成時に行う処理
//	----------------------------------------
//	引数1：なし
//	----------------------------------------
//	戻値：なし
//=========================================== */
CStage::CStage()
	:m_pPause(nullptr)	//ポーズ画面
{

	// =============== 動的確保 =====================
	m_pCamera = new CCameraChase();											//カメラ
	m_p3dObject.emplace(E_3D_PLAYER, new CPlayer());						//プレイヤー
	m_p2dObjectOnWorld.emplace(E_2D_ON_WORLD_BOSS_ARROW, new CBossArrow());	//ボス方向指針
	m_p2dObjectOnWorld.emplace(E_2D_ON_WORLD_BOSS_GAUGE, new CBossGauge());	//ボスゲージ
	m_pObjectManager.emplace(E_MANAGER_SLIME, new CSlimeManager());			//スライム管理
	m_pObjectManager.emplace(E_MANAGER_EXPLOSION, new CExplosionManager());	//爆発管理
	m_pObjectManager.emplace(E_MANAGER_SCORE_OH, new CScoreOHManager());	//ScoreOH管理	//TODO:修正
	m_pObjectManager.emplace(E_MANAGER_HEAL_ITEM, new CHealItemManager());	//回復アイテム管理
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_OPENING, new CStartText());		//開始表示
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_FINISH, new CStageFinish());		//終了表示
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_TOTAL_SCORE, new CTotalScore());	//総スコア
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_COMBO, new CCombo());		//コンボ数
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_HP, new CHP_UI());			//HP
	m_p2dObjectOnScreen.emplace(E_2D_ON_SCREEN_TIMER, new CTimer());		//時間

	// =============== 初期化 =====================
	if (m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_pCamera).hash_code() == typeid(CCameraChase).hash_code() &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CCameraChase*>(m_pCamera)->SetTarget(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER))->GetPosAddress());	//注視点登録
	}
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_HP, typeid(CHP_UI).hash_code())
		&& ACCESS_NULL_TYPE_CHECK(m_p3dObject, E_3D_PLAYER, typeid(CPlayer).hash_code()))	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CHP_UI*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_HP))->SetPlayerHp(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER))->GetHpPtr());	//HPアドレス登録
	}
	for (auto Iterator = m_p3dObject.begin(); Iterator != m_p3dObject.end(); Iterator++)
	{
		if (Iterator->second)	//ヌルチェック
		{
			(Iterator->second)->SetCamera(m_pCamera);	//カメラセット
		}
	};	//3Dオブジェクトカメラ登録
	for (auto Iterator = m_p2dObjectOnWorld.begin(); Iterator != m_p2dObjectOnWorld.end(); Iterator++)
	{
		if (Iterator->second)	//ヌルチェック
		{
			(Iterator->second)->SetCamera(m_pCamera);	//カメラセット
		}
	};	//3D表示2Dオブジェクトカメラ登録
	for (auto Iterator = m_pObjectManager.begin(); Iterator != m_pObjectManager.end(); Iterator++)
	{
		if (Iterator->second)	//ヌルチェック
		{
			(Iterator->second)->SetCamera(m_pCamera);	//カメラセット
		}
	};	//マネージャカメラ登録
	for (auto Iterator = m_p2dObjectOnScreen.begin(); Iterator != m_p2dObjectOnScreen.end(); Iterator++)
	{
		if (Iterator->second)	//ヌルチェック
		{
			(Iterator->second)->SetCamera(m_pCamera);	//カメラセット
		}
	};	//2D表示2Dオブジェクトカメラ登録
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetPlayer(static_cast<CPlayer*>(m_p3dObject.at(E_3D_PLAYER)));	//プレイヤー登録
	}	//スライムマネージャー　←　プレイヤー
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_pObjectManager.find(E_MANAGER_SCORE_OH) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SCORE_OH) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SCORE_OH)).hash_code() == typeid(CScoreOHManager).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetScoreOHMng(static_cast<CScoreOHManager*>(m_pObjectManager.at(E_MANAGER_SCORE_OH)));	//プレイヤー登録
	}	//スライムマネージャー　←　スコアマネージャー
	if (m_pObjectManager.find(E_MANAGER_EXPLOSION) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_EXPLOSION) &&
		typeid(*m_pObjectManager.at(E_MANAGER_EXPLOSION)).hash_code() == typeid(CExplosionManager).hash_code() &&
		m_p2dObjectOnScreen.find(E_2D_ON_SCREEN_COMBO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO) &&
		typeid(*m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO)).hash_code() == typeid(CCombo).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CExplosionManager*>(m_pObjectManager.at(E_MANAGER_EXPLOSION))->SetCombo(static_cast<CCombo*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO)));	//プレイヤー登録
	}	//爆発マネージャー　←　コンボ
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_pObjectManager.find(E_MANAGER_EXPLOSION) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_EXPLOSION) &&
		typeid(*m_pObjectManager.at(E_MANAGER_EXPLOSION)).hash_code() == typeid(CExplosionManager).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetExplosionMng(static_cast<CExplosionManager*>(m_pObjectManager.at(E_MANAGER_EXPLOSION)));	//プレイヤー登録
	}	//スライムマネージャー　←　爆発マネージャー
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_pObjectManager.find(E_MANAGER_HEAL_ITEM) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_HEAL_ITEM) &&
		typeid(*m_pObjectManager.at(E_MANAGER_HEAL_ITEM)).hash_code() == typeid(CHealItemManager).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetHealMng(static_cast<CHealItemManager*>(m_pObjectManager.at(E_MANAGER_HEAL_ITEM)));	//プレイヤー登録
	}	//スライムマネージャー　←　回復アイテムマネージャ―
	if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_SLIME) &&
		//m_p2dObjectOnScreen.find(E_2D_ON_SCREEN_COMBO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_COMBO) &&
		typeid(*m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_TIMER)).hash_code() == typeid(CCombo).hash_code())
	{
		static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME))->SetHealMng(static_cast<CHealItemManager*>(m_pObjectManager.at(E_2D_ON_SCREEN_TIMER)));	//プレイヤー登録
	}	//スライムマネージャー　←　タイマー

	// =============== データ受け継ぎ =====================
	m_Data.Load();	//ファイルに上がっている情報を読み込む

	// =============== データ受け継ぎ =====================
	if (m_pObjectManager.find(E_MANAGER_SLIME) != m_pObjectManager.end() && m_pObjectManager.at(E_MANAGER_SLIME) &&
		typeid(*m_pObjectManager.at(E_MANAGER_SLIME)).hash_code() == typeid(CSlimeManager).hash_code() &&
		m_p3dObject.find(E_3D_PLAYER) != m_p3dObject.end() && m_p3dObject.at(E_3D_PLAYER) &&
		typeid(*m_p3dObject.at(E_3D_PLAYER)).hash_code() == typeid(CPlayer).hash_code())	//アクセスチェック・ヌルチェック・型チェック
	{
		auto func = [](CSlimeManager* pSlimeMng) {pSlimeMng->Create(pSlimeMng->GetRandomLevel()); };	//ランダム生成用ラムダ式
		func(static_cast<CSlimeManager*>(m_pObjectManager.at(E_MANAGER_SLIME)));	//スライムランダム生成
	}	//スライムマネージャー　←　プレイヤー

	Update();
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
CStage::~CStage()
{
	// =============== セーブ =====================
	m_Data.Save();	//ステージのデータセーブ

	// =============== 終了 ===================
	SAFE_DELETE(m_pPause);
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
void CStage::Update()
{
	// =============== 検査 =====================
	if (ACCESS_NULL_TYPE_CHECK(m_p2dObjectOnScreen, E_2D_ON_SCREEN_FINISH, typeid(CStageFinish).hash_code()))	//アクセス・ヌル・型チェック
	{
		if (static_cast<CStageFinish*>(m_p2dObjectOnScreen.at(E_2D_ON_SCREEN_FINISH))->GetGameEndFlg())	//ゲームが終了したか
		{
			// =============== フラグ管理 =====================
			m_bFinish = true;	// タイトルシーン終了フラグON

			// =============== 終了 =====================
			return;	//処理中断
		}
	}

	// =============== ヒットストップ検査 ===================
	if (!CHitStop::IsStop())	//ヒットストップ時処理しない
	{
		// =============== 検査 =====================
		if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_EXPLOSION))	//アクセス・ヌルチェック
		{
			(m_pObjectManager.at(E_MANAGER_EXPLOSION))->Update();	//ゲームが終了したか
		}
		if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_HEAL_ITEM))	//アクセス・ヌルチェック
		{
			(m_pObjectManager.at(E_MANAGER_HEAL_ITEM))->Update();	//ゲームが終了したか
		}
		if (ACCESS_NULL_CHECK(m_pObjectManager, E_MANAGER_HEAL_ITEM))	//アクセス・ヌルチェック
		{
			(m_pObjectManager.at(E_MANAGER_HEAL_ITEM))->Update();	//ゲームが終了したか
		}
	}

	// =============== 更新 =====================
	CScene::Update();	//親関数呼び出し
	Collision();		// 当たり判定更新
}