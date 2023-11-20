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
	・2023/11/18~20 フェード試した 髙木駿輔
	・2023/11/21 フェード更新呼び出し 髙木駿輔

========================================== */

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

//Texture* pTex = new Texture;
//PixelShader* pps = new PixelShader;
//VertexShader* pvs = new VertexShader;

// =============== デバッグモード =======================
#define MODE_COORD_AXIS (true)	//座標軸映すかどうか
#define MODE_GROUND (false)	//座標軸映すかどうか
#define USE_FADE_GAME (true)	//フェード試す

#if USE_FADE_GAME
#include "Fade.h"
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
SceneGame::SceneGame(DirectWrite* pDirectWrite)
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
	SetDirectWrite(pDirectWrite);

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
	m_pExplosionMng = new CExplosionManager();
	m_pExplosionMng->SetCamera(m_pCamera);

	// タイマー生成
	m_pTimer = new CTimer();
	m_pTimer->TimeStart();

#if USE_FADE_GAME
	m_pFade = new CFade(m_pCamera);
#endif
	//pTex->Create("Assets/NoStar.png");
	//m_pFade->SetTexture(pTex);
	//pps->Load("Assets/Shader/PsFade.cso");
	//m_pFade->SetPixelShader(pps);
	//pvs->Load("Assets/Shader/VsFade.cso");
	//m_pFade->SetVertexShader(pvs);
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
	if(m_pFade)
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
	m_pCamera->Update();
	m_pPlayer->Update();
	m_pSlimeMng->SetPlayerPos(m_pPlayer->GetPos());

	// スライムマネージャー更新
	m_pSlimeMng->Update(m_pExplosionMng);
	m_pExplosionMng->Update();
	m_pTimer->Update();

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
	
	//床の描画
	m_pFloor->Draw();
	// スライムマネージャー描画
	m_pSlimeMng->Draw();
	m_pPlayer->Draw();
	
	//爆発マネージャー描画
	m_pExplosionMng->Draw();

	//タイマー描画
	m_pTimer->Draw();
	

	//DirectX::XMFLOAT4X4 matrix;
	//DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(100.0f, 220.0f, 10.0f);
	//DirectX::XMStoreFloat4x4(&matrix, DirectX::XMMatrixTranspose(world));
	//m_pFade->SetWorld(matrix);
	//m_pFade->SetView(m_pCamera->GetViewMatrix());
	//m_pFade->SetProjection(m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D));
	//m_pFade->SetSize(DirectX::XMFLOAT2(300.0f, 300.0f));

#if USE_FADE_GAME
	m_pFade->Draw();
#endif
}


void SceneGame::SetDirectWrite(DirectWrite* pDirectWrite)
{
	m_pDirectWrite = pDirectWrite;
}
