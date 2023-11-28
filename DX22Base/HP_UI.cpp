/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HPテクスチャ表示管理用cpp
	------------------------------------
	HpManager.cpp
	------------------------------------
	作成者	仁枝潤哉

	変更履歴
	・2023/11/16 新規作成 Nieda
	・2023/11/28 半分ずつ減るように修正 Sawada

========================================== */

// =============== インクルード ===================
#include "HP_UI.h"					
#include "DirectXTex/TextureLoad.h"		
#include "Sprite.h"						
#include "Pos3d.h"						
#include "GameParameter.h"		
#include "Player.h"



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
	int hpNum = 0;	// 何個目のハートか(表示位置調整用)
	// 空のハートを表示
	for (int i = 1; i <= PLAYER_HP; i++)
	{
		// 奇数個目のライフかどうか
		if (i % 2 != 0)
		{	
			// 現在の表示ライフ位置が最大値でない(最大値が奇数の場合はハートを表示する(例:HP3の場合は5個表示する))
			if (i != PLAYER_HP)
			{
				continue;

			}
		}

		DirectX::XMFLOAT4X4 mat[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpNum * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
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
		Sprite::SetSize(DirectX::XMFLOAT2(HP_UI_SIZE.x, -HP_UI_SIZE.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[HEART_NONE]);
		Sprite::Draw();


		hpNum++;	// 表示したら位置を進める
	}

	HEART_STATE tex;	// 表示画像を指定する
	int hpCnt = 0;		// 偶数の時に進める(表示位置調整用)
	for (int i = 1; i <= *m_pPlayerHp; i++)
	{
		DirectX::XMFLOAT4X4 mat_Full[3];

		// ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpCnt * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ワールド行列（必要に応じて変数を増やしたり、複数処理を記述したりする）
		DirectX::XMStoreFloat4x4(&mat_Full[0], DirectX::XMMatrixTranspose(world));

		// ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat_Full[1], DirectX::XMMatrixIdentity());

		// プロジェクション行列には2Dとして表示するための行列を設定する
		// この行列で2Dのスクリーンの大きさが決まる
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// 平衡投影行列を設定
		DirectX::XMStoreFloat4x4(&mat_Full[2], DirectX::XMMatrixTranspose(proj));

		// 奇数の場合
		if (i % 2 != 0)
		{
			tex = HEART_HALF;	// ハート半分
		}
		// 偶数の場合
		else
		{
			tex = HEART_FULL;	// ハート1個分
			hpCnt++;

		}

		// スプライトの設定
		Sprite::SetWorld(mat_Full[0]);
		Sprite::SetView(mat_Full[1]);
		Sprite::SetProjection(mat_Full[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(HP_UI_SIZE.x, -HP_UI_SIZE.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[tex]);
		Sprite::Draw();


	}

}


