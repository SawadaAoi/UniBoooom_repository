/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ2実装
	---------------------------------------
	Stage2.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 Stage1の内容をコピー yamashita
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2023/12/15 ゲームスタート表示を書き変え nieda

========================================== */

// =============== インクルード ===================
#include "Stage2.h"	//自身のヘッダ
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//ヒットストップ
#include "Fade.h"

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CStage2::CStage2()
{
	m_pFloor->SetFloorModel(CFloor::StageKinds::Stage2);

	m_pUIStageManager->GetBossGauge()->AddBossGauge(BOSS_GAUGE_S2[0].BossNum, BOSS_GAUGE_S2[0].startTime, BOSS_GAUGE_S2[0].maxTime);
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
CStage2::~CStage2()
{
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
void CStage2::Update()
{
	if (m_pDrawStart->GetAnimFlg())	// シーン遷移後ゲームを開始するか判定
	{
		m_pDrawStart->Update();
	}
	else
	{
		// カメラ更新
		m_pCamera->Update();

		//ポーズ更新
#if USE_PAUSE
		if (m_pPause)	//ヌルチェック
		{
			m_pPause->Update();	//ポーズ更新
			if (m_pPause->IsPause())	//ポーズ中
			{
				return;	//処理中断
			}
			m_bFinish = m_pPause->IsFin();	//終了判定
		}
#endif

		// =============== ヒットストップ検査 ===================
		if (!CHitStop::IsStop())	//ヒットストップ時処理しない
		{
			// プレイヤー更新
			m_pPlayer->Update();	//※カメラ更新含

			// スライムマネージャー更新
			m_pSlimeMng->Update(m_pExplosionMng);
		}

		m_pFloor->Update();				// 床更新
		m_pExplosionMng->Update();		// 爆発マネージャー更新
		m_pHealItemMng->Update();		// 回復アイテム更新
		m_pUIStageManager->Update();	// UIマネージャー更新
		PlayerHealItemCollision();		// 回復アイテム取る判定
		Collision();					// 当たり判定更新


	}

#if USE_FADE_GAME
	m_pFade->Update();
#endif

#if SCENE_TRANSITION
	if (m_pUIStageManager->GetStageFinish()->GetDispFlg())
	{
		if (IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_A))
		{
			m_bFinish = true;	// タイトルシーン終了フラグON
		}
	}
#else
	if (m_pUIStageManager->GetStageFinish()->GetDeleteDispFlg())
	{
		// =============== フラグ管理 =====================
		m_bFinish = true;	// タイトルシーン終了フラグON

		// =============== 退避 =====================
		m_Data.nTotalScore = m_pUIStageManager->GetTotalScore();			//スコア退避
		m_Data.nAliveTime = m_pUIStageManager->GetTimer()->GetErapsedTime();	//経過時間退避
		if (m_pSlimeMng)	//ヌルチェック
		{
			m_Data.nKill = m_pSlimeMng->GetKillCnt();						//討伐数退避
		}
	}
#endif
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
//!memo(見たら消してー)：constが邪魔になったら外してね(.hの方も)
void CStage2::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

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

	//2D描画変換
	SetRenderTargets(1, &pRTV, nullptr);

	//UIマネージャー描画
	m_pUIStageManager->Draw();

	// スタート合図描画
	if (m_pDrawStart->GetAnimFlg())
	{
		m_pDrawStart->Draw();
	}

#if USE_FADE_GAME
	m_pFade->Draw();
#endif
#if USE_PAUSE
	if (m_pPause)
	{
		m_pPause->Draw();
	}
#endif
}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がステージ2であることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CStage2::E_TYPE CStage2::GetType() const
{
	// =============== 提供 ===================
	return CStage2::E_TYPE_STAGE2;	//自身の種類
}

/* ========================================
	次シーンゲッタ
	----------------------------------------
	内容：遷移したいシーンが何かを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：遷移先シーンの種類
=========================================== */
CStage2::E_TYPE CStage2::GetNext() const
{
	// =============== 提供 ===================
	return CStage2::E_TYPE_RESULT;	//遷移先シーンの種類
}