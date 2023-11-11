/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Hammer用cpp
	------------------------------------
	Hammer.cpp
	------------------------------------
	作成者
		山本凱翔
	変更履歴
	・2023/11/08 コメント追加 yamashita
	・2023/11/08 できる限りの変数はメンバイニシャライザで初期化 yamashita
	・2023/11/08 定数HALF_PI、ANGULAR_ANGLE、ROTATE_RADIUSを定義 yamashita
	・2023/11/08 Updateに書かれていた処理をSwing関数に分けた　yamashita
	・2023/11/08 動的確保したポインタをdeleteからSAFE_DELETEに変更　yamashita
	・2023/11/09? 当たり判定用のSphereのゲット関数を追加 yamashita
	・2023/11/11 parameter用ヘッダ追加 suzumura
========================================== */

// =============== インクルード ===================
#include "hammer.h"				// 自身のヘッダ
#include "Sphere.h"				// 球体の情報用ヘッダ
#include "GameParameter.h"		// 定数定義用ヘッダー

// =============== 定数定義 =======================
const float HALF_PI = 3.141592f / 2;	//ハンマーの開始地点のラジアン角(要修正)

#if MODE_GAME_PARAMETER
#else
const float ANGULAR_ANGLE = 0.1f;		//毎フレーム移動する角度量
const float ROTATE_RADIUS = 1.0f;		//ハンマーが回転するプレイヤーからの距離
const float HAMMER_SIZE = 1.0f;			//ハンマーの当たり判定の大きさ
#endif

/* ========================================
   コンストラクタ関数
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CHammer::CHammer()
	:m_pos{ 0.0f,0.0f,0.0f }
	,m_stateangle(0.0f)
	, m_nowangle(HALF_PI)
	, m_bHammer(false)
	, m_pHammerGeo(nullptr)
{
	m_T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	//移動の変換行列の初期化
	m_S = DirectX::XMMatrixScaling(0.0f, 0.0f, 0.0f);		//拡縮の変換行列の初期化
	m_S = DirectX::XMMatrixRotationY(0.0f);					//Y軸の回転の変換行列の初期化
	m_pHammerGeo = new CSphere();							//ハンマーを仮表示するジオメトリー
	m_sphere.pos = {0.0f, 0.0f, 0.0f};
	m_sphere.radius = 0.5f;
}

/* ========================================
   デストラクタ関数
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
CHammer::~CHammer()
{
	SAFE_DELETE(m_pHammerGeo);
}

/* ========================================
   更新関数
   ----------------------------------------
   内容：更新を行う
   ----------------------------------------
   引数1：ハンマーの位置情報
   引数2：ハンマーの角度
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::Update(TPos3d<float> pPos, float angle)
{
	Swing(pPos,angle);	//回転による移動関数

	//現在角度が0になったら動作終了
	if (m_nowangle <= 0.0f)
	{
		m_bHammer = false;		//ハンマーの使用フラグをOFF
		m_nowangle = HALF_PI;	//ハンマーの現在角度を初期値に戻す
	}
}

/* ========================================
   描画関数
   ----------------------------------------
   内容：描画を行う
   ----------------------------------------
   引数：Cameraクラスのポインタ
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::Draw(const CCamera* pCamera)
{
	m_T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);	//ハンマーの座標を移動の行列に格納
	DirectX::XMMATRIX mat = m_T;			//移動の行列を格納
	mat = DirectX::XMMatrixTranspose(mat);	//転置
	DirectX::XMFLOAT4X4 fMat;				//行列の格納先
	DirectX::XMStoreFloat4x4(&fMat, mat);	//XMFLOAT4X4に変換
	m_pHammerGeo->SetWorld(fMat);			//ワールド座標にセット
	m_pHammerGeo->SetView(pCamera->GetViewMatrix());
	m_pHammerGeo->SetProjection(pCamera->GetProjectionMatrix());

	m_pHammerGeo->Draw();
}

/* ========================================
   フラグのゲット関数
   ----------------------------------------
   内容：ハンマーを振っている状態か取得する
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：bool
   ======================================== */
bool CHammer::Gethammer()
{
	return m_bHammer;
}

/* ========================================
   ハンマーの回転関数
   ----------------------------------------
   内容：ハンマーの回転による移動の処理
   ----------------------------------------
   引数1：プレイヤーのポジション
   引数2：プレイヤーの向いてる角度
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::Swing(TPos3d<float> pPos, float angle)
{
	m_bHammer = true;		//ハンマーの使用フラグをON
	m_stateangle = angle;	//-2.5f ;	//振り始めの角度	

	m_nowangle -= ANGULAR_ANGLE;				//現在の角度量から移動する角度の分移動
	float azimuth = m_stateangle + m_nowangle; // 方位角（角度）
	float inclination = 1.0f; // 仰角
	azimuth -= inclination;
	// 球面座標から直交座標系への変換
	m_pos.x = pPos.x + ROTATE_RADIUS * sin(azimuth);

	//m_pos.y = pPos.y + ROTATE_RADIUS * cos(inclination);	//たぶん真横に振るのでY座標は動かさないのでコメントアウト /山下凌佑
	m_pos.z = pPos.z + ROTATE_RADIUS * cos(azimuth);

	m_sphere.pos = m_pos;		//当たり判定用の球体に座標をコピー
}

/* ========================================
   Sphereのゲット関数
   ----------------------------------------
   内容：Sphereを返す処理
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：当たり判定の球体
   ======================================== */
CSphereInfo::Sphere CHammer::GetSphere()
{
	return m_sphere;
}
