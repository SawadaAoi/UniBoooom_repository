/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スライムベース クラス実装
	---------------------------------------
	SlimeBase.cpp
	
	作成者：鈴村 朋也
	
	変更履歴
	・2023/11/04 スライムベースクラス作成 Suzumura
	・2023/11/06 ハンマーもしくは敵により吹っ飛ばされる関数を追加 Yamashita
	・2023/11/06 インクルード誤字の修正 Tei
	・2023/11/08 GetPos→GetSphereに名前を変更 Yamashita
	・2023/11/08 定数定義がヘッダーにあったのでcppに移動 Yamashita
	・2023/11/08 コメントを追加 Sawada
	・2023/11/09 プレイヤー追跡移動変更 Sawada
	・2023/11/09 Update,NormalMoveの引数変更 Sawada
	・2023/11/11 parameter用ヘッダ追加 Suzumura
	・2023/11/12 プレイヤーの方向を向きながら進むように変更  Yamamoto
	・2023/11/12 ランダム移動を追加  Sawada
	・2023/11/13 GetScale関数を追加 Suzumura
	
========================================== */

// =============== インクルード ===================
#include "SlimeBase.h"
#include "Geometry.h"
#include "GameParameter.h"		//定数定義用ヘッダー


// =============== 定数定義 =======================
const float REFLECT_RATIO = 0.1f;				//スライムがスライムを吹き飛ばした際に吹き飛ばした側のスライムの移動量を変える割合

#if MODE_GAME_PARAMETER
#else
const float SPEED_DOWN_RATIO = 0.7f;			// スライムが接触して吹き飛ぶ際にかかる移動速度の変化の割合	RATIO=>割合
const float MOVE_RESIST = 0.05f;				// 吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値
const float MOVE_DISTANCE_PLAYER = 15;			// プレイヤー追跡移動に切り替える距離
const float SLIME_BASE_RADIUS = 0.5f;			// スライムの基準の大きさ
const int	RANDOM_MOVE_SWITCH_TIME = 5 * 60;	// ランダム移動の方向切り替え
#endif

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
	, m_RanMoveCnt(RANDOM_MOVE_SWITCH_TIME)	// 初期

{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/eyeBat/eyeBat.FBX", 0.1f, Model::XFlip)) {		//倍率と反転は省略可
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
	m_sphere.radius = SLIME_BASE_RADIUS;

	int random = abs(rand() % 360);	//ランダムに0～359の数字を作成
	m_Ry = DirectX::XMMatrixRotationY(random);
	
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
	引数1：プレイヤー当たり判定(Sphere)
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeBase::Update(TPos3d<float> playerSphere)
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
	引数1：カメラ
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeBase::Draw(const CCamera* pCamera)
{

	DirectX::XMFLOAT4X4 mat[3];

	//-- ワールド行列の計算
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);			//移動行列
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);		//拡大縮小行列

	DirectX::XMMATRIX world = m_Ry * S * T ;					//ワールド行列の設定
	world = DirectX::XMMatrixTranspose(world);					//転置行列に変換
	DirectX::XMStoreFloat4x4(&mat[0], world);					//XMMATRIX型(world)からXMFLOAT4X4型(mat[0])へ変換して格納


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
	引数1：プレイヤー当たり判定(Sphere)
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::NormalMove(TPos3d<float> playerPos)
{
	// 敵からエネミーの距離、角度を計算
	float distancePlayer	= m_pos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER) 
	{
		TPos3d<float> movePos;
		movePos = playerPos - m_pos;	// プレイヤーへのベクトルを計算
		if (distancePlayer != 0)	//0除算回避
		{
			m_move.x = movePos.x / distancePlayer * m_fSpeed;
			m_move.z = movePos.z / distancePlayer * m_fSpeed;
		}
		// 敵からプレイヤーへのベクトル
		DirectX::XMFLOAT3 directionVector;
		directionVector.x = m_pos.x-playerPos.x;
		directionVector.y = m_pos.y-playerPos.y;
		directionVector.z = m_pos.z-playerPos.z;

		// ベクトルを正規化して方向ベクトルを得る
		DirectX::XMVECTOR direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// 方向ベクトルから回転行列を計算
		m_Ry = DirectX::XMMatrixRotationY(std::atan2(directionVector.x, directionVector.z));
	}
	else
	{
		RandomMove();	// ランダム移動

	}

}

/* ========================================
	ランダム移動関数
	----------------------------------------
	内容：360度にランダム移動を行う
	----------------------------------------
	引数1：無し
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeBase::RandomMove()
{
	m_RanMoveCnt++;		// 移動方向切り替え間隔時間加算

	// 移動方向切り替え時間が経ったら
	if (m_RanMoveCnt >= RANDOM_MOVE_SWITCH_TIME)
	{
		int ranAngle = rand() % 360;	// 移動方向決定

		// 角度方向に移動する
		m_move.x = -cosf(DirectX::XMConvertToRadians(ranAngle)) * m_fSpeed;
		m_move.z = sinf(DirectX::XMConvertToRadians(ranAngle)) * m_fSpeed;

		// 向きを変える
		m_Ry = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(ranAngle + 90));

		m_RanMoveCnt = 0;	// 加算値をリセット
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
		m_bHitMove = false;				//吹き飛び状態のフラグをOFFにする
		SetNormalSpeed();	// 継承した関数を使用して大きさごとのスピードをセットする
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
	引数1：当たり判定(Sphere)
	-------------------------------------
	戻値：なし
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
	m_sphere.pos = pos;
}

/* ========================================
	カメラ情報セット関数
	----------------------------------------
	内容：描画処理で使用するカメラ情報セット
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeBase::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
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
	スライムサイズ取得関数
	----------------------------------------
	内容：スライムのサイズを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：スライムのサイズ
======================================== */
TTriType<float> CSlimeBase::GetScale()
{
	return m_scale;
}


/* ========================================
	吹飛状態フラグ取得関数
	----------------------------------------
	内容：吹飛状態フラグを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：吹飛状態フラグ
======================================== */
bool CSlimeBase::GetHitMoveFlg()
{
	return m_bHitMove;
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








