#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "Box.h"
#include "SlimeManager.h"
#include "SlimeBase.h"
#include "Explosion.h"
#include "ExplosionManager.h"

CExplosionManager* g_pExplodeMng;

SceneGame::SceneGame()
{
	
	// 頂点シェーダの読込
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}


	// モデルの読み込み
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/eyeBat/eyeBat.FBX", 0.075f, Model::XFlip))	//倍率指定と反転設定は省略可
	{
		MessageBox(NULL, "eyeBat", "Error", MB_OK);	//エラーメッセージの表示
	}
	m_pBox = new CBox;
	m_pPlayer = new CBox;
	
	m_pModel->SetVertexShader(m_pVS);	// 頂点シェーダをモデルにセット

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	

	m_pCamera = new CCameraDebug() ;

	// スライムマネージャー生成
	m_pSlimeMng = new CSlimeManager();
}

SceneGame::~SceneGame()
{
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

	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pBox)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pVS) {
		delete m_pVS;
		m_pVS = nullptr;
	}
	
}

 
void SceneGame::Update(float tick)
{
	m_pCamera->Update();

	// スライムマネージャー更新
	m_pSlimeMng->Update();
}

void SceneGame::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	// --- ワールド行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	// 位置を移動
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);		// 大きさを変更
	DirectX::XMMATRIX world = T * S;
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);
	
	//--ビュー行列の計算
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),	 // カメラの位置
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	 // カメラが注目している位置
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));	 // カメラの上方向
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat[1], view);

	//-- プロジェクション行列の計算 
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f),	// 縦方向の画角
		16.0f / 9.0f,						// アスペクト比
		0.1f,								// 画面に写り始める距離
		100.0f);							// 写せる限界距離
	proj = DirectX::XMMatrixTranspose(proj);
	DirectX::XMStoreFloat4x4(&mat[2], proj);


	// 行列をシェーダーへ 
	m_pVS->WriteBuffer(0, mat);

	// Genetory 用の 変換行列を設定
	if (m_pBox)
	{

		m_pBox->SetWorld(mat[0]);
		m_pBox->SetView(mat[1]);
		m_pBox->SetProjection(mat[2]);

		m_pBox->Draw();
	}
	// モデルの描画
	if (m_pModel)
	{
		m_pModel->Draw();
	}


	// Genetory 用の変換行列を計算
	T = DirectX::XMMatrixTranslation(0.0f, -0.05f, 0.0f);	// 位置を移動
	S = DirectX::XMMatrixScaling(5.0f, 0.1f, 5.0f);		// 大きさを変更
	world = T * S;	// 全ての行列を一つにする
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	
	// Genetory 用の 変換行列を設定
	if (m_pBox)
	{

		m_pBox->SetWorld(mat[0]);
		m_pBox->SetView(mat[1]);
		m_pBox->SetProjection(mat[2]);

		m_pBox->Draw();
	}
	
	// スライムマネージャー描画
	m_pSlimeMng->Draw();
	
	//爆発マネージャー描画
	g_pExplodeMng->Draw();
	
}
