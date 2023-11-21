/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ゲームシーン用cpp
	------------------------------------
	GameScene.cpp
	------------------------------------
	作成者 澤田蒼生

	変更履歴
	・2023/11/08 コメント追加、無駄な箇所を削除　澤田蒼生
	・2023/11/09 カメラの様々動作チェック。メインから軸線奪取。地面追加。 髙木駿輔
	・2023/11/10 カメラをスライムと爆発にも渡すようにした・lineのメモリリーク対策 髙木駿輔
	・2023/11/17 振動機能呼び出しデバッグモード追加 takagi
	・2023/11/18 BGMの再生 yamashita
  ・2023/11/18~20 フェード試した 髙木駿輔
	・2023/11/21 フェード更新呼び出し 髙木駿輔
  ・2023/11/21 コンボ用のメンバ変数を追加 Sawada

========================================== */

// =============== デバッグモード ===================
#define USE_CAMERA_VIBRATION (false)
#define MODE_COORD_AXIS (true)			//座標軸映すかどうか
#define MODE_GROUND (false)				//座標軸映すかどうか
#if _DEBUG
#define TRY_USE_HIT_STOP (true)
#endif
#define USE_FADE_GAME (true)	//フェード試す

#if USE_FADE_GAME
#include "Fade.h"
#endif

#if USE_CAMERA_VIBRATION
#include "Input.h"
#endif

#if TRY_USE_HIT_STOP
#include "HitStop.h"
#include "Input.h"
#endif


// =============== インクルード ===================
#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "CameraChase.h"
#include "Pos3d.h"
#include "Box.h"
#include "Line.h"
#include "Defines.h"
#include "GameParameter.h"



// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float BGM_VOLUME = 0.02f;
#endif

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
SceneGame::SceneGame()
{
	// 頂点シェーダの読込
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

#if MODE_COORD_AXIS
	// 軸線の表示
	CLine::Init();
#endif

	m_pCollision = new CCOLLISION();
	m_pPlayer = new CPlayer();
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress()) ;
	m_pPlayer->SetCamera(m_pCamera);

#if MODE_GROUND
	m_pBox = new CBox();
#endif


	m_pFloor = new CFloor();
	m_pFloor->SetCamera(m_pCamera);
	// スライムマネージャー生成
	m_pSlimeMng = new CSlimeManager();
	m_pSlimeMng->SetCamera(m_pCamera);


	// コンボ数表示生成
	m_pCombo = new CCombo();

	// 爆発マネージャー生成
	m_pExplosionMng = new CExplosionManager();
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pExplosionMng->SetCombo(m_pCombo);

	// タイマー生成
	m_pTimer = new CTimer();
	m_pTimer->TimeStart();
	//ステージ終了のUI表示
	m_pStageFin = new CStageFinish(m_pPlayer->GetHP(),m_pTimer->GetTimePtr());

#if USE_FADE_GAME
	m_pFade = new CFade(m_pCamera);
#endif
	//pTex->Create("Assets/NoStar.png");
	//m_pFade->SetTexture(pTex);
	//pps->Load("Assets/Shader/PsFade.cso");
	//m_pFade->SetPixelShader(pps);
	//pvs->Load("Assets/Shader/VsFade.cso");
	//m_pFade->SetVertexShader(pvs);

	LoadSound();
	//BGMの再生
	m_pSpeaker = CSound::PlaySound(m_pBGM);		//BGMの再生
	m_pSpeaker->SetVolume(BGM_VOLUME);			//音量の設定
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
SceneGame::~SceneGame()
{
	if (m_pSpeaker)
	{
		m_pSpeaker->Stop();
		m_pSpeaker->DestroyVoice();
	}
	SAFE_DELETE(m_pStageFin);
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pFade);
  SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// スライムマネージャー削除
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);
#if MODE_COORD_AXIS
	// 軸線の表示
	CLine::Uninit();
#endif
	SAFE_DELETE(m_pVs);
}


/* ========================================
   更新処理関数
   -------------------------------------
   内容：更新処理
   -------------------------------------
   引数1：ティック数?(未使用)
   -------------------------------------
   戻値：無し
=========================================== */
void SceneGame::Update(float tick)
{

#if TRY_USE_HIT_STOP
	CHitStop::Update();	//ヒットストップ更新
	//Effect更新、その他必要なもの
	if (CHitStop::IsStop())	//ストップ検査
	{
		return;	//処理中断
	}
#endif
#if USE_CAMERA_VIBRATION
	if (IsKeyTrigger('1'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK);
	}
	if (IsKeyTrigger('2'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);
	}
	if (IsKeyTrigger('3'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_SIDE_WEAK);
	}
	if (IsKeyTrigger('4'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
	}
#endif
#if TRY_USE_HIT_STOP
	if (IsKeyTrigger('Z'))
	{
		CHitStop::UpFlag(CHitStop::E_BIT_FLAG_STOP_SOFT);	//フラグオン
	}
#endif
	m_pCamera->Update();
	m_pPlayer->Update();
	m_pSlimeMng->SetPlayerPos(m_pPlayer->GetPos());

	// スライムマネージャー更新
	m_pSlimeMng->Update(m_pExplosionMng);
	m_pExplosionMng->Update();
	m_pTimer->Update();
	m_pStageFin->Update();
	m_pCombo->Update();

	SceneGameCollision();

#if USE_FADE_GAME
	m_pFade->Update();
#endif
}

/* ========================================
   描画処理関数
   -------------------------------------
   内容：描画処理
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：無し
=========================================== */
void SceneGame::Draw()
{
#if MODE_COORD_AXIS
	// 軸線の表示
	CLine::SetView(m_pCamera->GetViewMatrix());
	CLine::SetProjection(m_pCamera->GetProjectionMatrix());
	// グリッド
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
	}
	// 軸
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(size, 0, 0), DirectX::XMFLOAT4(1, 0, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, size, 0), DirectX::XMFLOAT4(0, 1, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, size), DirectX::XMFLOAT4(0, 0, 1, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(-size, 0, 0), DirectX::XMFLOAT4(0, 0, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -size), DirectX::XMFLOAT4(0, 0, 0, 1));

	CLine::Draw();
#endif

#if MODE_GROUND
	DirectX::XMFLOAT4X4 mat[3];

	//Geometory用の変換行列を設定
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, -0.5f * 0.1f, 0.0f);	//グリッドよりも下に来るように移動
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(100.0f, 0.1f, 100.0f);		//地面となるように、前後左右に広く上下に狭い
	DirectX::XMMATRIX world = S * T;											//全ての行列を一つにまとめる
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);	//matをfMatに格納
	m_pBox->SetWorld(mat[0]);	//ボックスに変換行列を設定

	//Geometory用の変換行列を設定
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pBox->SetView(mat[1]);		//ボックスに変換行列を設定
	m_pBox->SetProjection(mat[2]);	//ボックスに変換行列を設定

	//// 行列をシェーダーへ 
	//m_pVs->WriteBuffer(0, mat);

	m_pBox->Draw();
#endif
	
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	//床の描画
	m_pFloor->Draw();
	// スライムマネージャー描画
	m_pSlimeMng->Draw();
	m_pPlayer->Draw();
	
	//爆発マネージャー描画
	m_pExplosionMng->Draw();

	//タイマー描画

	SetRenderTargets(1, &pRTV, nullptr);
	m_pStageFin->Draw();

	m_pTimer->Draw();
	m_pCombo->Draw();


#if USE_FADE_GAME
	m_pFade->Draw();
#endif
  
}

/* ========================================
   サウンドファイル読み込み関数
   -------------------------------------
   内容：サウンドファイルの読み込み
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：無し
=========================================== */
void SceneGame::LoadSound()
{
	m_pBGM = CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true);		//BGMの読み込み
	m_pSEHitHammer = CSound::LoadSound("Assets/Sound/SE/Smash.mp3");		//SEの読み込み
}