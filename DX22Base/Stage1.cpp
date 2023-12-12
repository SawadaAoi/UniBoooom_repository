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

	========================================== */

// =============== インクルード ===================
#include "Stage1.h"	//自身のヘッダ
#include "CameraChase.h"
#include "Input.h"
#include "HitStop.h"	//ヒットストップ
#include "Fade.h"

// =============== 定数定義 =======================
const int STARTSIGN_UV_NUM_X = 6;	// テクスチャの横の分割数
const int STARTSIGN_UV_NUM_Y = 9;	// テクスチャの縦の分割数

const float STARTSIGN_UV_POS_X = 1.0f / STARTSIGN_UV_NUM_X;		// 横のUV座標計算用
const float STARTSIGN_UV_POS_Y = 1.0f / STARTSIGN_UV_NUM_Y;		// 縦のUV座標計算用

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
{
	//================BGMの設定================
	LoadBGM();
	//BGMの再生
	m_pBGMSpeaker = CSound::PlaySound(m_pBGM);		//BGMの再生
	m_pBGMSpeaker->SetVolume(BGM_VOLUME);			//音量の設定
	
	
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
	if (!m_bStart)	// シーン遷移後ゲームを開始するか判定
	{
		// タイトルから遷移後すぐゲーム開始にならないようにする処理
		m_nNum++;
		
		if (m_nNum > TIME_WAIT_START)	// フェード終了まで待って合図再生
		{
			m_bStartSign = true;
		}

		if (m_bStartSign)	// フェードが終了したらアニメーション再生開始
		{
			m_nCntSwitch++;
		}

		if (m_nCntSwitch > 1)	// 一定の間隔で切り替える
		{
			m_nCntSwitch = 0;		// カウントを初期化

			m_fUVPos.x = (STARTSIGN_UV_POS_X)* m_nCntW;		// 横方向のUV座標計算
			m_fUVPos.y = (STARTSIGN_UV_POS_Y)* m_nCntH;		// 縦方向のUV座標計算

			++m_nCntW;		// 横方向に座標を1つ進める
			if (m_nCntW == STARTSIGN_UV_NUM_X)	// テクスチャの右端まで行ったら 
			{
				m_nCntW = 0;	// カウントを初期化
				++m_nCntH;		// 縦に1進める
			}

			if (m_nCntH == STARTSIGN_UV_NUM_Y)		// テクスチャの下端まで行ったら
			{
				m_nCntH = 0;	// カウントを初期化
				m_nCntW = 0;
				m_bStart = true;	// アニメーション再生をOFF
			}
		}
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
void CStage1::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

	// スタート合図描画
	if (!m_bStart)
	{
		DirectX::XMFLOAT4X4 mat[2];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(START_POS_X, START_POS_Y, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		// ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());


		// スプライトの設定
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		if (m_pCamera)	//ヌルチェック
		{
			Sprite::SetProjection(m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D));	// 平行投影行列を設定
		}
		Sprite::SetSize(DirectX::XMFLOAT2(START_SCALE_X, START_SCALE_Y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVPos.x, m_fUVPos.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(STARTSIGN_UV_POS_X, STARTSIGN_UV_POS_Y));
		Sprite::SetTexture(m_pTexture);
		Sprite::Draw();
	}

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
   BGMのサウンドファイル読み込み関数
   -------------------------------------
   内容：BGMのサウンドファイルの読み込み
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：無し
=========================================== */
void CStage1::LoadBGM()
{
	m_pBGM = CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true);		//BGMの読み込み
}