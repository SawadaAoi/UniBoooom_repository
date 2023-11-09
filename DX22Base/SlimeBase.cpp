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
	・2023/11/08 GetPos→GetSphereに名前を変更 / 山下凌佑
	・2023/11/08 定数定義がヘッダーにあったのでcppに移動 / 山下凌佑
	・2023/11/08 コメントを追加　澤田蒼生
	・2023/11/09 プレイヤー追跡移動変更

========================================== */

// =============== インクルード ===================
#include "SlimeBase.h"
#include "Geometry.h"

// =============== 定数定義 =======================
const float ENEMY_MOVE_SPEED = 0.01f;
const float SPEED_DOWN_RATIO = 0.6f;	//スライムが接触して吹き飛ぶ際にかかる移動速度の変化の割合	RATIO=>割合
const float MOVE_RESIST = 0.1f;		//吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値
const float REFLECT_RATIO = 0.1f;	//スライムがスライムを吹き飛ばした際に吹き飛ばした側のスライムの移動量を変える割合
const float MOVE_DISTANCE_PLAYER = 20;	// プレイヤー追跡移動に切り替える距離

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlimeBase::CSlimeBase()
	: m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_move(0.0f, 0.0f, 0.0f)
	, m_fSpeed(ENEMY_MOVE_SPEED)
	, m_scale(1.0f,1.0f,1.0f)
	, m_pos(0.0f,0.0f,0.0f)
	, m_fVecAngle(0.0f)
	, m_bHitMove(false)
	, m_eSlimeSize(LEVEL_1)	//後でSLIME_NONEにする <=TODO

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

	//当たり判定(自分)初期化
	m_sphere.pos = { 0.0f, 0.0f, 0.0f };
	m_sphere.radius = 0.0f;
	
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
CSlimeBase::~CSlimeBase()
{

	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);

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
void CSlimeBase::Update(CSphereInfo::Sphere playerSphere)
{

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		NormalMove(playerSphere);
	}
	else
	{
		//敵の吹き飛び移動
		HitMove();
	}

	// -- 座標更新
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	m_sphere.pos = m_pos;	// 当たり判定の位置を座標に合わせる
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
void CSlimeBase::Draw(const CCamera* pCamera)
{

	DirectX::XMFLOAT4X4 mat[3];

	//-- ワールド行列の計算
	//DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);			//移動行列
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);			//移動行列

	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);		//拡大縮小行列
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationY(0.0f);		//回転行列
	DirectX::XMMATRIX world = S * T * R;										//ワールド行列の設定
	world = DirectX::XMMatrixTranspose(world);								//転置行列に変換
	DirectX::XMStoreFloat4x4(&mat[0], world);								//XMMATRIX型(world)からXMFLOAT4X4型(mat[0])へ変換して格納

	////-- ビュー行列の計算
	//DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
	//	DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
	//	DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)); //ビュー行列の設定
	//view = DirectX::XMMatrixTranspose(view);		//転置行列に変換
	//DirectX::XMStoreFloat4x4(&mat[1], view);		//XMMATRIX型(view)からXMFLOAT4X4型(mat[1])へ変換して格納

	////-- プロジェクション行列の計算
	//DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
	//	DirectX::XMConvertToRadians(60.0f), (float)16 / 9, 0.1f, 100.0f); //プロジェクショ行列の設定
	//proj = DirectX::XMMatrixTranspose(proj);	//転置行列に変換
	//DirectX::XMStoreFloat4x4(&mat[2], proj);	//XMMATRIX型(proj)からXMFLOAT4X4型(mat[2])へ変換して格納

	mat[1] = pCamera->GetViewMatrix();
	mat[2] = pCamera->GetProjectionMatrix();
	

	//-- 行列をシェーダーへ設定
	m_pVS->WriteBuffer(0, mat);

	//-- モデル表示
	if (m_pModel) {
		m_pModel->Draw();
	}
}


/* ========================================
	通常移動関数
	----------------------------------------
	内容：プレイヤーを追跡する移動を行う
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::NormalMove(CSphereInfo::Sphere playerSphere)
{
	//== 追従処理 ==
	// 敵からエネミーの距離、角度を計算
	float distancePlayer	= m_sphere.Distance(playerSphere);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER) 
	{
		TTriType<float> movePos = playerSphere.pos - m_pos;
		if (distancePlayer != 0)	//0除算回避
		{
			m_move.x = movePos.x / distancePlayer * m_fSpeed;
			m_move.z = movePos.z / distancePlayer * m_fSpeed;
		}
	}
	else
	{
		m_move.x = 0;
		m_move.z = 0;

	}

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

	m_fSpeed -= MOVE_RESIST;	//毎フレームの速度の減算処理
	if (m_fSpeed <= 0)	//速度が0以下になったら
	{
		m_fSpeed = ENEMY_MOVE_SPEED;	//敵は通常の移動速度になり通常移動する
		m_bHitMove = false;				//吹き飛び状態のフラグをOFFにする
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

/* ========================================
	反発関数
	----------------------------------------
	内容：スライムに反発の割合を乗算する処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::Reflect()
{
	m_fSpeed *= REFLECT_RATIO;
}

/* ========================================
	当たり判定取得関数
	-------------------------------------
	内容：スライムの当たり判定返す
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：当たり判定(Sphere)
=========================================== */
CSphereInfo::Sphere CSlimeBase::GetSphere()
{
	return m_sphere;
}

/* ========================================
	当たり判定セット関数
	-------------------------------------
	内容：当たり判定をセットする(追跡処理に使用する)
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：当たり判定
=========================================== */
void CSlimeBase::SetSphere(CSphereInfo::Sphere Sphere)
{
	m_sphere = Sphere;
}

/* ========================================
	座標セット関数
	-------------------------------------
	内容：スライムの座標をセットする
	-------------------------------------
	引数1：座標(x,y,z)
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeBase::SetPos(TPos3d<float> pos)
{
	m_pos = pos;
}

/* ========================================
	座標取得関数
	-------------------------------------
	内容：スライムの座標を返す
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：座標(x,y,z)
=========================================== */
TPos3d<float> CSlimeBase::GetPos()
{
	return m_pos;
}


/* ========================================
	スライムレベル取得関数
	----------------------------------------
	内容：スライムのレベルを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：スライムのレベル
======================================== */
E_SLIME_LEVEL CSlimeBase::GetSlimeLevel()
{
	return m_eSlimeSize;
}

/* ========================================
	移動速度取得関数
	----------------------------------------
	内容：スライムの移動速度を返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：スライムの移動速度
======================================== */
float CSlimeBase::GetSpeed()
{
	return m_fSpeed;
}








