/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ゲームシーンのステージ１用cpp
	------------------------------------
	SceneGameStage1.h
	------------------------------------
	作成者 仁枝潤哉

	変更履歴
	・2023/11/17 新規作成 仁枝潤哉

========================================== */

// =============== インクルード ===================
#include "SceneGameStage1.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "CameraChase.h"
#include "Pos3d.h"
#include "Box.h"
#include "Line.h"
#include "Defines.h"

// =============== デバッグモード =======================
#define MODE_COORD_AXIS (true)	//座標軸映すかどうか
#define MODE_GROUND (false)	//座標軸映すかどうか

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSceneGameStage1::CSceneGameStage1(DirectWrite* pDirectWrite)
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

	m_pPlayer = new CPlayer();
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());
	m_pPlayer->SetCamera(m_pCamera);

#if MODE_GROUND
	m_pBox = new CBox();
#endif

	// スライムマネージャー生成
	m_pSlimeMng = new CSlimeManager();
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pExplosionMng = new CExplosionManager();
	m_pExplosionMng->SetCamera(m_pCamera);

	// HPマネージャー生成
	m_pHpMng = new ChpManager;

	m_pColOfStg = new CCollisionOfStage();
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSceneGameStage1::~CSceneGameStage1()
{
	SAFE_DELETE(m_pHpMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// スライムマネージャー削除
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
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
   引数：無し
   -------------------------------------
   戻値：無し
=========================================== */
void CSceneGameStage1::Update()
{
	m_pCamera->Update();
	m_pPlayer->Update();
	m_pSlimeMng->SetPlayerPos(m_pPlayer->GetPos());

	// スライムマネージャー更新
	m_pSlimeMng->Update(m_pExplosionMng);
	m_pExplosionMng->Update();
	m_pCamera->Update();

	m_pColOfStg->CollisionOfStage();
}

/* ========================================
   描画処理関数
   -------------------------------------
   内容：描画処理
   -------------------------------------
   引数：無し
   -------------------------------------
   戻値：無し
=========================================== */
void CSceneGameStage1::Draw()
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


	// スライムマネージャー描画
	m_pSlimeMng->Draw();
	m_pPlayer->Draw();

	//爆発マネージャー描画
	m_pExplosionMng->Draw();

	// HPマネージャー描画
	m_pHpMng->Draw();
}

void CSceneGameStage1::SetDirectWrite(DirectWrite* pDirectWrite)
{
	m_pDirectWrite = pDirectWrite;
}

