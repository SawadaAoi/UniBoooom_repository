/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HPテクスチャ表示管理用cpp
	------------------------------------
	HpManager.cpp
	------------------------------------
	作成者	仁枝潤哉

	変更履歴
	・2023/11/16 新規作成 仁枝潤哉

========================================== */

// =============== インクルード ===================
#include "HP_UI.h"					
#include "DirectXTex/TextureLoad.h"		
#include "Sprite.h"						
#include "Pos3d.h"						
#include "GameParameter.h"		
#include "Player.h"


// =============== 定数定義 =======================
//const bool HALF_FLAG = false;

// =============== グローバル変数定義 =============
//int g_addLife = 2;
//int g_HpAdjust = 2;

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数：プレイヤーのHPのアドレス
	-------------------------------------
	戻値：なし
=========================================== */
CHP_UI::CHP_UI(const int* pPlayerHp)
{

	m_pTexture[HEART_FULL] = new Texture();	// HPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_FULL]->Create("Assets/Texture/HP_Full_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Full_1.png", "Error", MB_OK);
	}

	m_pTexture[HEART_HALF] = new Texture();	// HPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_HALF]->Create("Assets/Texture/HP_Half.png")))
	{
		MessageBox(NULL, "HpUI HP_Full_1.png", "Error", MB_OK);
	}


	m_pTexture[HEART_NONE] = new Texture();	// 空のHPのテクスチャ読み込み
	if (FAILED(m_pTexture[HEART_NONE]->Create("Assets/Texture/HP_Lost_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Lost_1.png", "Error", MB_OK);
	}

	m_pPlayerHp = pPlayerHp;

/*
	if (HALF_FLAG)
	{
		g_addLife = 1;
		g_HpAdjust = 1;
	}*/


	
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
CHP_UI::~CHP_UI()
{
	SAFE_DELETE(m_pTexture[HEART_FULL]);
	SAFE_DELETE(m_pTexture[HEART_HALF]);
	SAFE_DELETE(m_pTexture[HEART_NONE]);
}

/* ========================================
	更新関数
	-------------------------------------
	内容：HPの更新処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CHP_UI::Update()
{
	//後々演出など記述
}

/* ========================================
	描画関数
	-------------------------------------
	内容：HPの描画処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CHP_UI::Draw()
{

	for (int i = 0; i < PLAYER_HP; i++)
	{

		DirectX::XMFLOAT4X4 mat[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(DRAW_POSX + (i * DRAW_WIDTH), DRAW_POSY, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
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
		Sprite::SetSize(DirectX::XMFLOAT2(DRAW_HEIGHT, -DRAW_WIDTH));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[HEART_NONE]);
		Sprite::Draw();

	}


	for (int i = 0; i < *m_pPlayerHp; i++)
	{
	
		DirectX::XMFLOAT4X4 mat_Full[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(DRAW_POSX + (i * DRAW_WIDTH), DRAW_POSY, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
		DirectX::XMStoreFloat4x4(&mat_Full[0], DirectX::XMMatrixTranspose(world));

		// ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat_Full[1], DirectX::XMMatrixIdentity());

		// プロジェクション行列には2Dとして表示するための行列を設定する
		// この行列で2Dのスクリーンの大きさが決まる
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// 平衡投影行列を設定
		DirectX::XMStoreFloat4x4(&mat_Full[2], DirectX::XMMatrixTranspose(proj));


		// スプライトの設定
		Sprite::SetWorld(mat_Full[0]);
		Sprite::SetView(mat_Full[1]);
		Sprite::SetProjection(mat_Full[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(DRAW_HEIGHT, -DRAW_WIDTH));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[HEART_FULL]);
		Sprite::Draw();


	}

}


