/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス実装
   ---------------------------------------
   SlimeBase.cpp

   作成者：鈴村 朋也

   変更履歴
   ・2023/11/04 スライムベースクラス作成 /鈴村 朋也
   ・2023/11/06 インクルード誤字の修正 / 鄭 宇恩
   ======================================== */

  // =============== インクルード ===================
#include "SlimeBase.h"
#include "Geometry.h"
#include "Model.h"

// =============== 定数定義 =======================

// =============== プロトタイプ宣言 ===============

// =============== グローバル変数定義 =============

// =============== コンストラクタ =============
CSlimeBase::CSlimeBase()
	:m_pModel(nullptr)
	,m_pVS(nullptr)
	,m_pos(0.0f,0.0f,0.0f)
	,m_move(0.0f, 0.0f, 0.0f)
	,m_scale(1.0f,1.0f,1.0f)
	,m_playerPos(0.0f, 0.0f, 0.0f)
	,m_bUse(false)

{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/eyeBat/eyeBat.FBX", 0.075f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "eyeBat", "Error", MB_OK);	//ここでエラーメッセージ表示
	}

	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);
}

// =============== デストラクタ =================
CSlimeBase::~CSlimeBase()
{

	// Model削除
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}
}

/*
 ========================================
   関数 Update()
 ----------------------------------------
   内容：更新処理
 ======================================== */
void CSlimeBase::Update()
{
	// 使用してないならreturn
	if (m_bUse == false) return;

	//==== プレイヤー追従 処理 ====
	// -- X軸
	if (m_playerPos.x > m_pos.x)
	{
		m_move.x = ENEMY_MOVE_SPEED;
	}
	else if (m_playerPos.x < m_pos.x)
	{
		m_move.x = -ENEMY_MOVE_SPEED;
	}

	// -- Y軸
	if (m_playerPos.y > m_pos.y)
	{
		m_move.y = ENEMY_MOVE_SPEED;
	}
	else if (m_playerPos.y < m_pos.y)
	{
		m_move.y = -ENEMY_MOVE_SPEED;
	}

	// -- Z軸
	if (m_playerPos.z > m_pos.z)
	{
		m_move.z = ENEMY_MOVE_SPEED;
	}
	else if (m_playerPos.z < m_pos.z)
	{
		m_move.z = -ENEMY_MOVE_SPEED;
	}

	// -- 座標更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

}

/*
 ========================================
   関数 Draw()
 ----------------------------------------
   内容：描画処理
 ======================================== */
void CSlimeBase::Draw()
{
	// 使用してないならreturn
	if (m_bUse == false) return;

	DirectX::XMFLOAT4X4 mat[3];

	//-- ワールド行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);			//移動行列
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);		//拡大縮小行列
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationY(0.0f);		//回転行列
	DirectX::XMMATRIX world = S * T * R;										//ワールド行列の設定
	world = DirectX::XMMatrixTranspose(world);								//転置行列に変換
	DirectX::XMStoreFloat4x4(&mat[0], world);								//XMMATRIX型(world)からXMFLOAT4X4型(mat[0])へ変換して格納

	//-- ビュー行列の計算
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)); //ビュー行列の設定
	view = DirectX::XMMatrixTranspose(view);		//転置行列に変換
	DirectX::XMStoreFloat4x4(&mat[1], view);		//XMMATRIX型(view)からXMFLOAT4X4型(mat[1])へ変換して格納

	//-- プロジェクション行列の計算
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f), (float)16 / 9, 0.1f, 100.0f); //プロジェクショ行列の設定
	proj = DirectX::XMMatrixTranspose(proj);	//転置行列に変換
	DirectX::XMStoreFloat4x4(&mat[2], proj);	//XMMATRIX型(proj)からXMFLOAT4X4型(mat[2])へ変換して格納

	//-- 行列をシェーダーへ設定
	m_pVS->WriteBuffer(0, mat);

	//-- モデル表示
	if (m_pModel) {
		m_pModel->Draw();
	}
}

TTriType<float> CSlimeBase::GetPos()
{
	return m_pos;
}

bool CSlimeBase::GetUse()
{
	return m_bUse;
}

void CSlimeBase::SetPos(TTriType<float> pos)
{
	m_pos = pos;
}

void CSlimeBase::SetUse(bool onoff)
{
	m_bUse = onoff;
}




