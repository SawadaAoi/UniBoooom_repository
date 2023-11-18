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
#include "HpManager.h"
#include "DirectXTex/TextureLoad.h"
#include "Sprite.h"
#include "Pos3d.h"
#include "GameParameter.h"

// =============== 定数定義 =======================


/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数：プレイヤーのHPのアドレス
	-------------------------------------
	戻値：なし
=========================================== */
CHpManager::CHpManager(const int* nHp)
	:m_bLost(false)
{
	m_pnPlayerHp = nHp;		// プレイヤーのHPのアドレスを格納

	m_pTexture[0] = new Texture();
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/HP_Full_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Full_1.png", "Error", MB_OK);
	}

	m_pTexture[1] = new Texture();
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/HP_Lost_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Lost_1.png", "Error", MB_OK);
	}
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
CHpManager::~CHpManager()
{
	SAFE_DELETE(m_pTexture[0]);
	SAFE_DELETE(m_pTexture[1]);
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
void CHpManager::Update()
{
	for (int i = PLAYER_HP; i >= *m_pnPlayerHp; --i)
	{
		m_bLost ^= 1;
	}
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
void CHpManager::Draw()
{
	for (int i = 0; i < *m_pnPlayerHp; ++i)
	{
		// HPのテクスチャを表示
		Draw2d(DRAW_POSX * (i + DRAW_FIRSTPOSX) * DRAW_GAP, DRAW_POSY, DRAW_HEIGHT, DRAW_WIDTH, m_pTexture[0]);
	}

	for (int j = PLAYER_HP; j > *m_pnPlayerHp; --j)
	{
		// HPのテクスチャを表示
		Draw2d(DRAW_POSX * (j + DRAW_FIRSTPOSX - 1) * DRAW_GAP, DRAW_POSY, DRAW_HEIGHT, DRAW_WIDTH, m_pTexture[1]);
	}
}

/* ========================================
	2D描画関数
	-------------------------------------
	内容：テクスチャの描画処理
	-------------------------------------
	引数1：表示位置のX座標
	-------------------------------------
	引数2：表示位置のY座標
	-------------------------------------
	引数3：表示するテクスチャの縦幅
	-------------------------------------
	引数4：表示するテクスチャの横幅
	-------------------------------------
	引数5：表示するテクスチャのポインタ
	-------------------------------------
	戻値：なし
========================================== = */
void CHpManager::Draw2d(float posX, float posY, float h, float w, Texture *pTexture)
{
	DirectX::XMFLOAT4X4 mat[3];

	// ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(posX, posY, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
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
	Sprite::SetSize(DirectX::XMFLOAT2(h, -w));
	Sprite::SetTexture(pTexture);
	Sprite::Draw();
}
