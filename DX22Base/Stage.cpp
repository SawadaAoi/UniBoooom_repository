/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ用抽象クラス実装
	!memo：当たり判定関連の処理はCollisionOfStage.cppに記載
	---------------------------------------
	Stage.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/01 サウンドの読み込み yamashita
	・2023/12/04 ポーズクラス追加・デストラクタ復活 takagi
	・2023/12/05 コメント修正 takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi

========================================== */

// =============== インクルード ===================
#include "Stage.h"	//自身のヘッダ
#include "Line.h"

// =============== デバッグモード ===================
#define USE_CAMERA_VIBRATION (true)
#define MODE_COORD_AXIS (true)			//座標軸映すかどうか
#define MODE_GROUND (false)				//座標軸映すかどうか
#if _DEBUG
#define TRY_USE_HIT_STOP (true)
#endif
#define USE_FADE_GAME (true)	//フェード試す
#define USE_PAUSE (true)	//ポーズ試す		※現在ポーズ中から戻ってくる手段を用意していないため要注意！
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


///* ========================================
//	コンストラクタ
//	----------------------------------------
//	内容：生成時に行う処理
//	----------------------------------------
//	引数1：なし
//	----------------------------------------
//	戻値：なし
//=========================================== */
CStage::CStage()
	:m_pVs(nullptr)
	, m_pPlayer(nullptr)
	, m_pBox(nullptr)
	, m_pSlimeMng(nullptr)
	, m_pCollision(nullptr)
	, m_pExplosionMng(nullptr)
	, m_pFloor(nullptr)
	, m_pFade(nullptr)
	, m_pTexture(nullptr)
	, m_pScoreOHMng(nullptr)
	, m_pHealItemMng(nullptr)
	, m_pUIStageManager(nullptr)
	, m_pPause(nullptr)	//ポーズ
	, m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	, m_nNum(0)
	, m_fSize(0.0f)
	, m_fResize(10.0f)
	, m_bStart(false), m_fUVPos(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntW(0)
	, m_nCntH(0)
	, m_bStartSign(false)
	, m_pSEHitHammer(nullptr)
	, m_pSEHitHammerSpeaker(nullptr)
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

	//ステージ内で扱うSEのロード
	LoadSE();
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

#if MODE_COORD_AXIS
// 軸線の表示
	CLine::Uninit();
#endif

	// =============== 終了 ===================
	SAFE_DELETE(m_pVs);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pBox);
	SAFE_DELETE(m_pSlimeMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pTexture);
	SAFE_DELETE(m_pScoreOHMng);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pPause);
	SAFE_DELETE(m_pUIStageManager);
	SAFE_DELETE(m_pSEHitHammer);
	SAFE_DELETE(m_pSEHitHammerSpeaker);
}

///* ========================================
//	更新関数
//	----------------------------------------
//	内容：更新処理
//	----------------------------------------
//	引数1：なし
//	----------------------------------------
//	戻値：なし
//=========================================== */
//void CStage::Update()
//{
//}
//
///* ========================================
//	描画関数
//	----------------------------------------
//	内容：描画処理
//	----------------------------------------
//	引数1：なし
//	----------------------------------------
//	戻値：なし
//	======================================== */
//	//!memo(見たら消してー)：constが邪魔になったら外してね(.hの方も)
//void CStage::Draw() const
//{
//}

/* ========================================
   SEのサウンドファイル読み込み関数
   -------------------------------------
   内容：SEのサウンドファイルの読み込み
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：無し
=========================================== */
void CStage::LoadSE()
{
	m_pSEHitHammer = CSound::LoadSound("Assets/Sound/SE/Smash.mp3");		//SEの読み込み
}
