//CPP用----------------------------------------------------
/*========================================
HEW/UniBoooom!!
---------------------------------------
爆発用cpp
---------------------------------------
Explosion.cpp

TeiUon

変更履歴
・2023/11/03 cpp作成 / 鄭 宇恩
・2023/11/05 爆発cppの初期設定　/ 鄭 宇恩
・2023/11/06 爆発のモデル設定、描画、位置
	とboolの設定と取得関数制作 / 鄭 宇恩

======================================== */


//=============== インクルード ===================
#include "Explosion.h"
#include "Geometry.h"


//=============== 定数定義 =======================

//=============== プロトタイプ宣言 ===============

//=============== グローバル変数定義 =============


CExplosion::CExplosion()
	:m_pModel(nullptr)
	,m_pVS(nullptr)
	,m_pos(0.0f, 0.0f, 0.0f)
	,m_fSize(1.0f)
	,m_bExploded(false)
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	
	
	
	if (!m_pModel->Load("Assets/Model/Golem/Golem.FBX", 1.0f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "Golem", "Error", MB_OK);	//ここでエラーメッセージ表示
	}

	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);
	
}

CExplosion::~CExplosion()
{
	
	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}
	
}

/*========================================
関数：Update関数
----------------------------------------
内容：爆発内の更新処理
----------------------------------------
引数：一旦なし
----------------------------------------
戻値：一旦なし
======================================== */
void CExplosion::Update()
{
	
}


/*========================================
関数：Draw関数
----------------------------------------
内容：爆発の描画処理
----------------------------------------
引数：なし
----------------------------------------
戻値：なし
======================================== */

void CExplosion::Draw()
{
	
	
	// 使用してないならreturn
	if (m_bExploded == false) return;
	
	DirectX::XMFLOAT4X4 mat[3];

	//-- ワールド行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(3.0f, 3.0f, 3.0f);			//移動行列
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);		// 大きさを変更
	DirectX::XMMATRIX world = T * S;										//ワールド行列の設定
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
		
	//--モデル表示
	if (m_pModel)
	{
		m_pModel->Draw();
	}
}

/*========================================
関数：GetExplode関数
----------------------------------------
内容：爆発するフラグを取得
----------------------------------------
引数：なし
----------------------------------------
戻値：なし
======================================== */
bool CExplosion::GetExplode()
{
	return false;	//どうしようわからないから一旦falseに
}

/*========================================
関数：GetPos関数
----------------------------------------
内容：爆発の位置を取得
----------------------------------------
引数：なし
----------------------------------------
戻値：なし
======================================== */
TTriType<float> CExplosion::GetPos()
{
	return m_pos;
}

/*========================================
関数：SetExplode関数
----------------------------------------
内容：スライムを爆発に設定
----------------------------------------
引数：bool(爆発かどうか)
----------------------------------------
戻値：なし
======================================== */
void CExplosion::SetExplode(bool YN)
{
	m_bExploded = YN;
}
/*========================================
関数：SetPos関数
----------------------------------------
内容：爆発の位置を設定
----------------------------------------
引数：スライム結合の位置
----------------------------------------
戻値：なし
======================================== */
void CExplosion::SetPos(TTriType<float> pos)
{
	m_pos = pos;
}