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

========================================== */

// =============== インクルード ===================
#include "Stage1.h"	//自身のヘッダ
#include "CameraChase.h"
#include "Input.h"
#include "Line.h"
#include "HitStop.h"	//ヒットストップ
#include "Fade.h"

// =============== 定数定義 =======================
const int STARTSIGN_UV_NUM_X = 6;	// テクスチャの横の分割数
const int STARTSIGN_UV_NUM_Y = 9;	// テクスチャの縦の分割数

const float STARTSIGN_UV_POS_X = 1.0f / STARTSIGN_UV_NUM_X;		// 横のUV座標計算用
const float STARTSIGN_UV_POS_Y = 1.0f / STARTSIGN_UV_NUM_Y;		// 縦のUV座標計算用

// =============== デバッグモード ===================
#define USE_CAMERA_VIBRATION (true)
#define MODE_COORD_AXIS (true)			//座標軸映すかどうか
#define MODE_GROUND (false)				//座標軸映すかどうか
#if _DEBUG
#define TRY_USE_HIT_STOP (true)
#endif
#define USE_FADE_GAME (true)	//フェード試す
#define USE_PAUSE (false)	//ポーズ試す		※現在ポーズ中から戻ってくる手段を用意していないため要注意！

#if USE_FADE_GAME
#include "Fade.h"
#endif

#if USE_CAMERA_VIBRATION
#include "Input.h"
#endif

#if TRY_USE_HIT_STOP
#include "Input.h"
#endif

#if USE_PAUSE	//ポーズ臨時呼び出し
#include "Input.h"
#endif

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
	: m_nNum(0)
	, m_fSize(0.0f)
	, m_fResize(10.0f)
	, m_bStart(false), m_fUVPos(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntW(0)
	, m_nCntH(0)
	, m_bStartSign(false)
{
	// 頂点シェーダの読込
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/start_sprite.png")))
	{
		MessageBox(NULL, "スタートテキスト読み込み", "Error", MB_OK);
	}

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

#if MODE_COORD_AXIS
	// 軸線の表示
	CLine::Init();
#endif

	//================3dObject動的確保================

	//プレイヤー生成
	m_pPlayer = new CPlayer();

	//床生成
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress());

	// 爆発マネージャー生成
	m_pExplosionMng = new CExplosionManager();

	// スライムマネージャー生成
	m_pSlimeMng = new CSlimeManager(m_pPlayer);
	
	m_pHealItemMng = new CHealItemManager();

	//================2dObject動的確保================

	// コンボ数表示生成
	m_pCombo = new CCombo();

	//頭上スコアマネージャー生成
	m_pScoreOHMng = new CScoreOHManager();

	//トータルスコア生成
	m_pTotalScore = new CTotalScore();

	// タイマー生成
	m_pTimer = new CTimer();

	//ボスゲージ生成
	m_pBossgauge = new CBossgauge(m_pTimer->GetNowTime());

	//ステージ終了のUI表示
	m_pStageFin = new CStageFinish(m_pPlayer->GetHpPtr(), m_pTimer->GetTimePtr());

	//プレイヤーHPのUI生成
	m_pHpMng = new CHP_UI(m_pPlayer->GetHpPtr());
	
	//================System動的確保================

	//カメラ生成
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());

	//衝突判定チェック生成
	m_pCollision = new CCOLLISION();
	
#if MODE_GROUND
	m_pBox = new CBox();
#endif
#if USE_FADE_GAME
	m_pFade = new CFade(m_pCamera);
#endif

#if USE_PAUSE
	m_pPause = new CPause(m_pCamera);
#endif

	//================セット================

	//プレイヤー　←　カメラ
	m_pPlayer->SetCamera(m_pCamera);

	//爆発マネージャー　←　カメラ
	m_pExplosionMng->SetCamera(m_pCamera);

	//スライムマネージャー　←　カメラ
	m_pSlimeMng->SetCamera(m_pCamera);

	//床　←　カメラ
	m_pFloor->SetCamera(m_pCamera);

	//頭上スコアマネージャー　←　カメラ
	m_pScoreOHMng->SetCamera(m_pCamera);

	m_pHealItemMng->SetCamera(m_pCamera);

	//スライムマネージャー　←　スコアマネージャー
	m_pSlimeMng->SetScoreOHMng(m_pScoreOHMng);
	
	//爆発マネージャー　←　コンボ
	m_pExplosionMng->SetCombo(m_pCombo);

	//スライムマネージャー　←　爆発マネージャー
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);

	//コンボ　←　トータルスコア
	m_pCombo->SetTotalScore(m_pTotalScore);

	//ボスゲージ　←　スライムマネージャー
	m_pBossgauge->SetSlimeManager(m_pSlimeMng);

	//爆発マネージャー　←　タイマー
	m_pSlimeMng->SetTimer(m_pTimer);

	m_pSlimeMng->SetHealMng(m_pHealItemMng);

	//================タイマースタート================
	m_pTimer->TimeStart();

	//================BGMの設定================
	LoadSound();
	//BGMの再生
	m_pSpeaker = CSound::PlaySound(m_pBGM);		//BGMの再生
	m_pSpeaker->SetVolume(BGM_VOLUME);			//音量の設定
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
	SAFE_DELETE(m_pPause);
	if (m_pSpeaker)
	{
		m_pSpeaker->Stop();
		m_pSpeaker->DestroyVoice();
	}
	SAFE_DELETE(m_pStageFin);
	SAFE_DELETE(m_pHpMng);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pBossgauge);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pCombo);
	SAFE_DELETE(m_pSlimeMng);	// スライムマネージャー削除
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pTotalScore);

#if MODE_COORD_AXIS
	// 軸線の表示
	CLine::Uninit();
#endif
	SAFE_DELETE(m_pVs);

	//SAFE_DELETE(m_pDirectWrite);

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
			if (IsKeyPress('P'))
			{
				m_pPause->Boot();
			}
			if (m_pPause->IsPause())	//ポーズ中
			{
				m_pPause->Update();

				return;	//処理中断
			}
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

		//床更新
		m_pFloor->Update();

		// 爆発マネージャー更新
		m_pExplosionMng->Update();

		m_pHealItemMng->Update();

		// タイマー更新
		m_pTimer->Update();

		// ステージ終了更新
		m_pStageFin->Update();

		// コンボ更新
		m_pCombo->Update();

		//頭上スコア更新
		m_pScoreOHMng->Update();

		// HPマネージャー更新
		m_pHpMng->Update();

		//ボスの出現ゲージ更新
		m_pBossgauge->Update();

		// 当たり判定更新
		Collision();
		
		// 回復アイテム取る判定
		PlayerHealItemCollision();
		
	}

#if USE_FADE_GAME
	m_pFade->Update();
#endif

	if (m_pStageFin->GetDispFlg())
	{
		if (IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_A))
		{
			m_bFinish = true;	// タイトルシーン終了フラグON
		}
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
void CStage1::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

	// スタート合図描画
	if (!m_bStart)
	{
		DirectX::XMFLOAT4X4 mat[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(START_POS_X, START_POS_Y, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		// ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

		// プロジェクション行列には2Dとして表示するための行列を設定する
		// この行列で2Dのスクリーンの大きさが決まる
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// 平衡投影行列を設定
		DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));


		// スプライトの設定
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(START_SCALE_X, -START_SCALE_Y));
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

	m_pHealItemMng->Draw();



	//タイマー描画
	SetRenderTargets(1, &pRTV, nullptr);

	//ステージ終了時の結果を描画
	m_pStageFin->Draw();

	// タイマー描画
	m_pTimer->Draw();

	// HPマネージャー描画
	m_pHpMng->Draw();

	// コンボ描画
	m_pCombo->Draw();
	
	//トータルスコア描画
	m_pTotalScore->Draw();

	//ボスゲージ描画
	m_pBossgauge->Draw();

	//頭上スコアマネージャー描画
	m_pScoreOHMng->Draw();
//
//#if USE_FADE_GAME
//	m_pFade->Draw();
//#endif
//
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
