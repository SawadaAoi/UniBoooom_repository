/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	影表示用cpp
	---------------------------------------
	Shadow.cpp

	作成者 nieda

	変更履歴
	・2023/11/27 制作 nieda
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/02/13 UsingCamera使用 takagi

========================================== */

// =============== インクルード ===================
#include "Shadow.h"			// 自身のヘッダ
#include "Sprite.h"			// 表示用ヘッダ
#define _USE_MATH_DEFINES	// 円周率
#include <math.h>			// 円周率
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 ===================
const float PI = 3.14159f;					// 円周率


/* ========================================
   コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::CShadow()
	: m_bDisp(true)	// 表示判定
{
	// 影テクスチャ読込
	m_pTextureShadow = new Texture();
	if (FAILED(m_pTextureShadow->Create("Assets/Texture/Direction/Shadow/Shadow.png")))
	{
		MessageBox(NULL, "Shadow.png", "Error", MB_OK);
	}

}

/* ========================================
   コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数1：大きさ
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::CShadow(float fScale)
   : CShadow::CShadow()
{
   m_Transform.fScale = { fScale ,fScale ,fScale };
}

/* ========================================
   デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
======================================== */
CShadow::~CShadow()
{
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
	m_bDisp ^= 1;	// 表示、非表示の切り替え
}

/* ========================================
   描画処理関数
   ----------------------------------------
   内容：描画処理
   ----------------------------------------
   引数1：プレイヤーの現在位置
   引数2：表示するテクスチャの大きさ
   ----------------------------------------
   戻値：なし
======================================== */
void CShadow::Draw(tagTransform3d m_Pos, float fScale)
{
	if (m_bDisp)	// 表示フラグがONの場合
	{		
		DirectX::XMMATRIX mat_shadow = DirectX::XMMatrixTranslation(m_Pos.fPos.x, m_Pos.fPos.z, m_Pos.fPos.y) * DirectX::XMMatrixRotationX(PI / 2);	// 移動行列を求める
		DirectX::XMFLOAT4X4 world;	// 読み取り用の行列の宣言
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat_shadow));	// 格納する
		Sprite::SetWorld(world);															// ワールド行列の設定
		Sprite::SetView(CUsingCamera::GetThis().GetCamera()->GetViewMatrix());				// ビュー行列の設定
		Sprite::SetProjection(CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix());	// プロジェクション行列の設定
		Sprite::SetSize(DirectX::XMFLOAT2(fScale, fScale));		// サイズを設定
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));		// UVの位置
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));		// UVの分割数
		Sprite::SetTexture(m_pTextureShadow);					// テクスチャを設定
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f,1.0f,1.0f,0.6f));// 透明度を下げる
		Sprite::Draw();											// スプライトを描画
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));// 透明度を戻す(他に影響を出さないため)
	}
}

/* ========================================
   描画処理関数
   ----------------------------------------
   内容：描画処理
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CShadow::Draw()
{
	if (m_bDisp)	// 表示フラグがONの場合
	{
		DirectX::XMMATRIX mat_shadow = DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.z, m_Transform.fPos.y) * DirectX::XMMatrixRotationX(PI / 2);	// 移動行列を求める
		DirectX::XMFLOAT4X4 world;	// 読み取り用の行列の宣言
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat_shadow));	// 格納する
		Sprite::SetWorld(world);															// ワールド行列の設定
		Sprite::SetView(CUsingCamera::GetThis().GetCamera()->GetViewMatrix());				// ビュー行列の設定
		Sprite::SetProjection(CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix());	// プロジェクション行列の設定
		Sprite::SetSize(DirectX::XMFLOAT2(m_Transform.fScale.x, m_Transform.fScale.z));		// サイズを設定
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));		// UVの位置
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));		// UVの分割数
		Sprite::SetTexture(m_pTextureShadow);					// テクスチャを設定
		Sprite::Draw();											// スプライトを描画
	}
}
