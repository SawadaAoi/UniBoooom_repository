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

========================================== */

// =============== インクルード ===================
#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "CameraChase.h"
#include "Pos.h"
#include "Box.h"
#include "Line.h"
#include "Defines.h"

// =============== デバッグモード =======================
#define MODE_COORD_AXIS (true)	//座標軸映すかどうか
#define MODE_GROUND (true)	//座標軸映すかどうか

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


	m_pCollision = new CCOLLISION();
	m_pPlayer = new CPlayer();
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress()) ;
	m_pPlayer->GetCamera(m_pCamera);

#if MODE_GROUND
	m_pBox = new CBox();
#endif

	// スライムマネージャー生成
	m_pSlimeMng = new CSlimeManager();
	m_pExplosionMng = new CExplosionManager();
}

SceneGame::~SceneGame()
{
	if (m_pExplosionMng)
	{
		delete m_pExplosionMng;
		m_pExplosionMng = nullptr;
	}

	// スライムマネージャー削除
	if (m_pSlimeMng)
	{
		delete m_pSlimeMng;
		m_pSlimeMng = nullptr;
	}
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

#if MODE_COORD_AXIS
	// 軸線の表示
	CLine::Init();
#endif
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
	SAFE_DELETE(m_pExplodeMng);
	SAFE_DELETE(m_pSlimeMng);	// スライムマネージャー削除
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pVs);

}

/* ========================================
   更新処理関数
   -------------------------------------
   内容：更新処理
   -------------------------------------
   引数1：無し
   -------------------------------------
   戻値：無し
=========================================== */
void SceneGame::Update(float tick)
{
	m_pCamera->Update();
	m_pPlayer->Update();
	// スライムマネージャー更新
	m_pSlimeMng->Update();
	m_pExplodeMng->Update();
	m_pCamera->Update();

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
	CLine::Init();
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
	

	// スライムマネージャー描画
	m_pSlimeMng->Draw();
	m_pPlayer->Draw();
	
	//爆発マネージャー描画
	m_pExplodeMng->Draw();	
	
}