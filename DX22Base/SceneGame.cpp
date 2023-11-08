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

========================================== */

// =============== インクルード ===================
#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "CameraChase.h"
#include "Pos.h"
#include "Box.h"


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
	m_pCamera = new CCameraChase(&m_pPlayer->GetPos()) ;

	// スライムマネージャー生成
	m_pSlimeMng = new CSlimeManager();

	m_pExplodeMng = new CExplosionManager();
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
	DirectX::XMFLOAT4X4 mat[3];

	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	// 行列をシェーダーへ 
	m_pVs->WriteBuffer(0, mat);

	m_pPlayer->Draw();
	// スライムマネージャー描画
	m_pSlimeMng->Draw();
	
	//爆発マネージャー描画
	m_pExplodeMng->Draw();	
	
}