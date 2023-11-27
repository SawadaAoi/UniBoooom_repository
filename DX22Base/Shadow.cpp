/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	影表示用cpp
	---------------------------------------
	Shadow.cpp

	作成者 nieda

	変更履歴
	・2023/11/27 制作 nieda

========================================== */

// =============== インクルード ===================
#include "Shadow.h"			// 自身のヘッダ
#include "Sprite.h"			// 表示用ヘッダ
#include "GameParameter.h"	// 定数定義用ヘッダ


/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::CShadow()
	: m_bDisp(true)	// 表示判定
{
	// 影テクスチャ読込
	m_pTextureShadow = new Texture();
	if (FAILED(m_pTextureShadow->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "Shadow.png", "Error", MB_OK);
	}

	m_pObject = new CObject();	// オブジェクト生成
}

/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::~CShadow()
{
	SAFE_DELETE(m_pObject);			// オブジェクト破棄
	SAFE_DELETE(m_pTextureShadow);	// テクスチャ破棄
}

/* ========================================
   更新処理関数関数
   ----------------------------------------
   内容：更新処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CShadow::Update()
{
	// 一旦作ってみた
}

/* ========================================
   描画処理関数
   ----------------------------------------
   内容：描画処理
   ----------------------------------------
   引数1：プレイヤーの現在位置
   引数2：表示するテクスチャの大きさ
   引数3：カメラクラスのポインタ
   ----------------------------------------
   戻値：なし
======================================== */
void CShadow::Draw(tagTransform3d m_Pos, float fScale, CCamera* pCamera)
{
	if (m_bDisp)	// 表示フラグがONの場合
	{
		// 移動行列を求める
		DirectX::XMMATRIX mat_shadow = DirectX::XMMatrixTranslation(m_Pos.fPos.x, m_Pos.fPos.z, m_Pos.fPos.y) * DirectX::XMMatrixRotationX(PI / 2);
		DirectX::XMFLOAT4X4 world;	// 読み取り用の行列の宣言
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat_shadow));	// 格納する
		Sprite::SetWorld(world);								// ワールド行列の設定
		Sprite::SetView(pCamera->GetViewMatrix());				// ビュー行列の設定
		Sprite::SetProjection(pCamera->GetProjectionMatrix());	// プロジェクション行列の設定
		Sprite::SetSize(DirectX::XMFLOAT2(fScale, fScale));		// サイズを設定
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));		// UVの位置
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));		// UVの分割数
		Sprite::SetTexture(m_pTextureShadow);					// テクスチャを設定
		Sprite::Draw();											// スプライトを描画
	}
}
