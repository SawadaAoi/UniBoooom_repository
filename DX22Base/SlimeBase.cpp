/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス実装
   ---------------------------------------
   SlimeBase.cpp

   作成者：鈴村 朋也

   変更履歴
   ・2023/11/04 スライムベースクラス作成 /鈴村 朋也
   ・2023/11/06 ハンマーもしくは敵により吹っ飛ばされる関数を追加	/山下凌佑

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
	//,m_pos(0.0f,0.0f,0.0f)
	//,m_sphere{(0.0f,0.0f,0.0f),0.0f}
	,m_move(0.0f, 0.0f, 0.0f)
	,m_scale(1.0f,1.0f,1.0f)
	,m_fVecAngle(0.0f)
	//,m_playerPos(0.0f, 0.0f, 0.0f)
	,m_bUse(false)
	,m_bHitMove(false)
	,m_anglePlayer(0.0f)
	,m_distancePlayer(0.0f)
	, m_fSpeed(ENEMY_MOVE_SPEED)

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

	//球初期化
	m_sphere.pos = { 0.0f, 0.0f, 0.0f };
	m_sphere.radius = 0.0f;

	//球(player)初期化
	m_playerSphere.pos = { 0.0f, 0.0f, 0.0f };
	m_playerSphere.radius = 0.0f;


	

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

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		//== 追従処理 ==
		// 敵からエネミーの距離、角度を計算
		m_distancePlayer = m_sphere.Distance(m_playerSphere);
		m_anglePlayer = m_sphere.Angle(m_playerSphere);

		TTriType<float> movePos = m_playerSphere.pos - m_sphere.pos;
		if (m_distancePlayer != 0)	//0除算回避
		{
			m_move.x = movePos.x / m_distancePlayer * m_fSpeed;
			m_move.z = movePos.z / m_distancePlayer * m_fSpeed;
		}
	}
	else
	{
		//敵の吹き飛び移動
		HitMove();
	}

	// -- 座標更新
	m_sphere.pos.x += m_move.x;
	m_sphere.pos.z += m_move.z;
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
	//DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);			//移動行列
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_sphere.pos.x, m_sphere.pos.y, m_sphere.pos.z);			//移動行列

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

CSphereInfo::Sphere CSlimeBase::GetPos()
{
	return m_sphere;
}

/*
TTriType<float> CSlimeBase::GetPos()
{
	return m_pos;
}
*/
bool CSlimeBase::GetUse()
{
	return m_bUse;
}

/* ========================================
	ハンマーか敵に吹っ飛ばされて実際に移動量を確定する関数
	----------------------------------------
	内容：X方向とZ方向の移動量を確定する処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::HitMove()
{
	//敵キャラの移動速度と移動角度に応じてX方向とZ方向の移動量を決める
	m_move.x = cos(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);
	m_move.z = sin(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);

	//舞フレームの速度の減算処理
	m_fSpeed -= MOVE_RESIST;
	if (m_fSpeed <= 0)	//速度が0以下になったら
	{
		m_fSpeed = ENEMY_MOVE_SPEED;	//敵は通常の移動速度になり通常移動する
		m_bHitMove = false;
	}
}

/* ========================================
	ハンマーか敵に吹っ飛ばされる関数
	----------------------------------------
	内容：引数に応じて飛ぶ方向と移動速度を決める処理
	----------------------------------------
	引数1：速度
	引数2：角度
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::HitMoveStart(float speed, float angle)
{
	m_fSpeed = speed;		//移動量を入れる
	m_fVecAngle = angle;		//移動方向を入れる
	m_bHitMove = true;		//吹き飛び状態をONにする
}

//void CSlimeBase::SetPos(TTriType<float> pos)
//{
//	m_pos = pos;
//}

void CSlimeBase::SetPos(CSphereInfo::Sphere sphere)
{
	m_sphere.pos = sphere.pos;
}

void CSlimeBase::SetUse(bool onoff)
{
	m_bUse = onoff;
}

void CSlimeBase::SetPlayer(CSphereInfo::Sphere player)
{
	m_playerSphere = player;
}




