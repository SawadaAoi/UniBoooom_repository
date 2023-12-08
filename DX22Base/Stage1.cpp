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
#define SCENE_TRANSITION(false)		// シーン遷移をボタン押下か自動化を切り替え（trueは自動)

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
	m_pPlayer = new CPlayer();							// プレイヤー生成
	m_pFloor = new CFloor(m_pPlayer->GetPosAddress());	// 床生成
	m_pExplosionMng = new CExplosionManager();			// 爆発マネージャー生成
	m_pSlimeMng = new CSlimeManager(m_pPlayer);			// スライムマネージャー生成
	m_pHealItemMng = new CHealItemManager();			// 回復アイテムマネージャー生成

	//================System動的確保================
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());	//カメラ生成
	m_pCollision = new CCOLLISION();							//衝突判定チェック生成

	//================2dObject動的確保================
	m_pUIStageManager = new CUIStageManager(m_pPlayer, m_pCamera, m_pSlimeMng);	// UIマネージャー生成

	
	
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
	// カメラ
	m_pPlayer->SetCamera(m_pCamera);
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pFloor->SetCamera(m_pCamera);
	m_pHealItemMng->SetCamera(m_pCamera);

	//スライムマネージャー　←　スコアマネージャー
	m_pSlimeMng->SetScoreOHMng(m_pUIStageManager->GetScoreMng());
	
	//爆発マネージャー　←　コンボ
	m_pExplosionMng->SetCombo(m_pUIStageManager->GetCombo());

	//スライムマネージャー　←　爆発マネージャー
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);

	// スライムマネージャー　←　回復アイテムマネージャ―
	m_pSlimeMng->SetHealMng(m_pHealItemMng);

	//爆発マネージャー　←　タイマー
	m_pSlimeMng->SetTimer(m_pUIStageManager->GetTimer());


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
	// =============== セーブ =====================
	m_Data.Save();	//ステージのデータセーブ

	SAFE_DELETE(m_pPause);
	if (m_pSpeaker)
	{
		m_pSpeaker->Stop();
		m_pSpeaker->DestroyVoice();
	}
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// スライムマネージャー削除
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pUIStageManager);

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
