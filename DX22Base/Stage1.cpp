/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ1実装
	---------------------------------------
	Stage1.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/05 制作 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 Prot.cpp→Stage1.cpp takagi
	・2023/11/20 SceneGameから移植 nieda
	・2023/11/21 ゲーム開始時テクスチャ表示 nieda
	・2023/11/22 動くよう足りない変数など追加 nieda
	・2023/11/27 バグ修正 takagi
	・2023/11/29 ヒットストップ仕様変更対応 takagi
	・2023/12/03 カメラ更新の記述改訂 takagi
	・2023/12/05 ステージにポーズ実装 takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi
	・2023/12/07 ステージ→リザルト遷移方法切り替え実装 nieda
	・2023/12/07 ビュー行列取得にカメラ使用 takagi
	・2023/12/08 リザルトシーン遷移用に処理追加 takagi
	・2023/12/12 メンバ変数を親クラスに移動 yamashita
	・2023/12/14 BGMの管理をSceneManagerに移動 yamashita
	・2023/12/15 ゲームスタート表示を書き変え nieda
	・2023/12/18 デバッグモード削除反映 takagi
	・2024/01/01 親コンストラクタ呼び出し takagi
	・2024/01/15 GameFinish()関数修正・RecordData()関数追加 takagi
	・2024/01/25 ヒットエフェクト関係の処理追加 Tei

	========================================== */

// =============== インクルード ===================
#include "Stage1.h"	//自身のヘッダ
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//ヒットストップ
#include "Fade.h"

// =============== 定数・マクロ定義 ===================
const int STAGE_NUM = 1;	//ステージ番号

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CStage1::CStage1()
	:CStage(CUIStageManager::E_STAGE_1)	//親関数呼び出し
{
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress(), CFloor::Stage1);	// 床生成
	//================セット================
	m_pFloor->SetCamera(m_pCamera);
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
CStage1::~CStage1()
{
	// =============== 記録 =====================
	RecordData();	//データ記録

	// =============== 終了 =====================
	SAFE_DELETE(m_pFloor);
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
void CStage1::Update()
{
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
		m_pHitEffectMng->Update();		// ヒットエフェクトマネージャー更新
		m_pWalkEffectMng->Update();		// プレイヤー移動エフェクトマネージャー更新
	}

#if SCENE_TRANSITION
	if (m_pUIStageManager->GetStageFinish()->GetDispFlg())
	{
		if (IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_A))
		{
			m_bFinish = true;	// タイトルシーン終了フラグON
		}
	}
#else
	CStage::GameFinish();	// ステージ終了処理
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
void CStage1::Draw()
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
	if (m_pStartText->GetAnimFlg())
	{
		m_pStartText->Draw();
	}

	// ポーズ描画
	if (m_pPause)
	{
		m_pPause->Draw();
	}

	// エフェクト描画
	m_pHitEffectMng->Draw();
	m_pWalkEffectMng->Draw();

}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がステージ1であることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CStage1::E_TYPE CStage1::GetType() const
{
	// =============== 提供 ===================
	return CStage1::E_TYPE_STAGE1;	//自身の種類
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
CStage1::E_TYPE CStage1::GetNext() const
{
	// =============== 提供 ===================
	return CStage1::E_TYPE_RESULT;	//遷移先シーンの種類
}

/* ========================================
	データ記録関数
	----------------------------------------
	内容：リザルト用にデータ記録
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStage1::RecordData()
{
	// =============== 退避 =====================
	m_Data.nTotalScore = m_pUIStageManager->GetTotalScore();				// スコア退避

	// =============== データ登録 =====================
	if (m_Data.nHighScore[STAGE_NUM - 1] < m_Data.nTotalScore)	// ハイスコアを更新しているか？
	{
		m_Data.nHighScore[STAGE_NUM - 1] = m_Data.nTotalScore;	// ハイスコア更新
	}
	m_Data.nAliveTime = m_pUIStageManager->GetTimer()->GetErapsedTime();	// 経過時間退避
	m_Data.nMaxCombo = m_pUIStageManager->GetCombo()->GetMaxCombo();		// 最大コンボ数退避
	m_Data.bClearFlg = m_pUIStageManager->GetStageFinish()->GetClearFlg();	// ゲームクリアしたか
	if (m_pSlimeMng)	//ヌルチェック
	{
		m_Data.nTotalKill = m_pSlimeMng->GetTotalKillCnt();					// 総討伐数退避
		m_pSlimeMng->GetKillCntArray(m_Data.nKill);							// スライム別討伐数退避

	}
	m_Data.nStageNum = STAGE_NUM;	// プレイしたステージ番号
}