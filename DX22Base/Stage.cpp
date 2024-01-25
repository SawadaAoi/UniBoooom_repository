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
	, m_pPlayer(nullptr)
	, m_pBox(nullptr)
	, m_pSlimeMng(nullptr)
	, m_pCollision(nullptr)
	, m_pExplosionMng(nullptr)
	, m_pTexture(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pHealItemMng(nullptr)
	,m_pFloor(nullptr)
{
	// =============== 動的確保 =====================
	m_pCamera = new CCameraChase();						//カメラ
	//================3dObject動的確保================
	m_pPlayer = new CPlayer();							// プレイヤー生成
	if (typeid(m_pCamera).hash_code() == typeid(CCameraChase).hash_code())
	{
		static_cast<CCameraChase*>(m_pCamera)->SetTarget(m_pPlayer->GetPosAddress());	//カメラ生成
	}
	m_pExplosionMng = new CExplosionManager();			// 爆発マネージャー生成
	m_pSlimeMng = new CSlimeManager();			// スライムマネージャー生成
	m_pSlimeMng->SetPlayer(m_pPlayer);
	m_pHealItemMng = new CHealItemManager();			// 回復アイテムマネージャー生成
	//================System動的確保================

	m_pCollision = new CCollision();					//衝突判定チェック生成
	m_pStartText = new CStartText();
	m_pStartText->SetCamera(m_pCamera);
	//================セット================
	// カメラ
	m_pPlayer->SetCamera(m_pCamera);
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pHealItemMng->SetCamera(m_pCamera);
	m_pPause = new CPause(m_pCamera);
	//スライムマネージャー　←　スコアマネージャー
	m_pSlimeMng->SetScoreOHMng(m_pScoreOHMng);
	//爆発マネージャー　←　コンボ
	m_pExplosionMng->SetCombo(m_pCombo);
	//スライムマネージャー　←　爆発マネージャー
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);
	// スライムマネージャー　←　回復アイテムマネージャ―
	m_pSlimeMng->SetHealMng(m_pHealItemMng);
	//爆発マネージャー　←　タイマー
	m_pSlimeMng->SetTimer(m_pTimer);
	// データ受け継ぎ
	m_Data.Load();	//ファイルに上がっている情報を読み込む
	
	
	m_pTimer = new CTimer;
	m_pTimer->SetCamera(m_pCamera);
	m_pBossGauge = new CBossGauge();
	m_pBossGauge->SetCamera(m_pCamera);
	m_pBossGauge->SetTimer(m_pTimer);
	m_pBossGauge->SetSlimeManager(m_pSlimeMng);
	m_pHpMng = new CHP_UI();
	m_pHpMng->SetCamera(m_pCamera);
	m_pHpMng->SetPlayerHp(m_pPlayer->GetHpPtr());
	m_pTotalScore = new CTotalScore();
	m_pTotalScore->SetCamera(m_pCamera);
	m_pScoreOHMng = new CScoreOHManager();
	m_pScoreOHMng->SetCamera(m_pCamera);
	m_pStageFin = new CStageFinish();
	m_pStageFin->SetCamera(m_pCamera);
	m_pStageFin->SetTime(m_pTimer->GetTimePtr());
	m_pStageFin->SetPlHp(m_pPlayer->GetHpPtr());
	m_pBossArrow = new CBossArrow();
	m_pBossArrow->SetCamera(m_pCamera);
	m_pBossArrow->SetSlimeMng(m_pSlimeMng);
	m_pBossArrow->SetPlayer(m_pPlayer);
	m_pCombo = new CCombo();
	m_pCombo->SetCamera(m_pCamera);
	m_pCombo->SetTotalScore(m_pTotalScore);

	m_pTimer->TimeStart();

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
	if (m_pStageFin)
	{
		if(m_pStageFin->GetGameEndFlg())
		{
			// =============== フラグ管理 =====================
			m_bFinish = true;	// タイトルシーン終了フラグON

			// =============== 終了 =====================
			return;	//処理中断
		}
	}

	if (m_pStartText->GetAnimFlg())	// シーン遷移後ゲームを開始するか判定
	{
		m_pStartText->Update();
	}
	else
	{
		// カメラ更新
		m_pCamera->Update();

		//ポーズ更新
		if (m_pPause)	//ヌルチェック
		{
			m_pPause->Update();	//ポーズ更新
			if (m_pPause->IsPause())	//ポーズ中
			{
				return;	//処理中断
			}
			m_bFinish = m_pPause->IsFin();	//終了判定
		}

		// =============== ヒットストップ検査 ===================
		if (!CHitStop::IsStop())	//ヒットストップ時処理しない
		{
			// プレイヤー更新
			m_pPlayer->Update();	//プレイヤー更新

			// スライムマネージャー更新
			m_pSlimeMng->Update(m_pExplosionMng);
		}

		m_pFloor->Update();				// 床更新
		m_pExplosionMng->Update();		// 爆発マネージャー更新
		m_pHealItemMng->Update();		// 回復アイテム更新
		m_pTimer->Update();
		m_pStageFin->Update();
		m_pCombo->Update();
		m_pHpMng->Update();
		m_pBossGauge->Update();
		m_pScoreOHMng->Update();
		m_pBossArrow->Update();
		Collision();					// 当たり判定更新
	}

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
void CStage::Draw() const
{
//	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
//	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
//	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
//
	//床の描画
	m_pFloor->Draw();

	// スライムマネージャー描画
	m_pSlimeMng->Draw();

	// プレイヤー描画
	m_pPlayer->Draw();

	LibEffekseer::Draw();

	//爆発マネージャー描画
	m_pExplosionMng->Draw();

	//回復アイテム描画
	m_pHealItemMng->Draw();
	
	//UIマネージャー描画
	m_pTimer->Draw();
	m_pBossGauge->Draw();
	m_pHpMng->Draw();
	m_pTotalScore->Draw();
	m_pScoreOHMng->Draw();
	m_pStageFin->Draw();
	m_pBossArrow->Draw();
	m_pCombo->Draw();

	// スタート合図描画
	if (m_pStartText->GetAnimFlg())
	{
		m_pStartText->Draw();
	}

	//ポーズ描画
	if (m_pPause)
	{
		m_pPause->Draw();
	}
}