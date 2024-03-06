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
	・2023/11/09 当たり判定用のSphereのゲット関数を追加 yamashita
	・2023/11/11 parameter用ヘッダ追加 suzumura
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/14 全体的に処理の流れが分かりづらかったので修正 Sawada
	・2023/11/15 Objectクラスを継承したので修正　yamamoto
	・2023/11/23 ジオメトリーからモデルに差し替え　yamashita
	・2023/11/29 Interval追加　yamamoto
	・2023/12/01 IntervalをSwingSpeedに変更　yamamoto
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/02/08 振る速度の増減について処理を修正 sawada
	・2024/02/09 UsingCamera使用 takagi

========================================== */

// =============== インクルード ===================
#include "hammer.h"				// 自身のヘッダ
#include "Sphere.h"				// 球体の情報用ヘッダ
#include "GameParameter.h"		// 定数定義用ヘッダー
#include "TriType.h"
#include "UsingCamera.h"		//カメラ使用

// =============== 定数定義 =======================
const float HALF_PI = 3.141592f / 2;	//ハンマーの開始地点のラジアン角(要修正)

const TTriType<float> HAMMER_DISP_ANGLE = {	// ハンマーの表示角度
	DirectX::XMConvertToRadians(180.0f),
	DirectX::XMConvertToRadians(0.0f) ,
	DirectX::XMConvertToRadians(0.0f) };

const float SWING_ANGLE = DirectX::XMConvertToRadians(130.0f);		//ハンマーを振る範囲(扇形の角度の大きさ)
#if MODE_GAME_PARAMETER
#else
const float SWING_TIME_FRAME = 0.15f * 60;						// ハンマーを振る時間(フレーム単位)
const float ROTATE_RADIUS = 1.0f;								// ハンマーが回転するプレイヤーからの距離
const float HAMMER_COL_SIZE = 0.75f;							// ハンマーの当たり判定の大きさ
const float HAMMER_SIZE = 1.5f;									// ハンマーの大きさ

const float SwingSpeed_INITIAL = 0.2f;									//ハンマー初期間隔
const float SWING_TIME_ADD_MULT = 3.2f;									//ハンマーを一回振るときに乗算される値
const float SWING_TIME_MINUS_MULT = 0.97f;								//毎フレームハンマーを振る間隔を短くさせる値
const float SWING_TIME_MAX = 50.0f;								//毎フレームハンマーを振る間隔を短くさせる値
#endif

const float ADJUST_DIRECTX_TO_COSINE = DirectX::XMConvertToRadians(90.0f);	// 三角関数とDirectX角度の差分(DirectXの角度は↑が0度、三角関数は→が0度)
const float FIRST_ADD_ANGLE = SWING_ANGLE / SWING_TIME_MIN;

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
	: m_tPlayerPos(0.0f,0.0f,0.0f)
	, m_fAngleNow(0)
	, m_dAddAngleCnt(0)
	, m_nSwingTimeFrame(SWING_TIME_MIN)
	, m_fSwingSpeed(1.0f)
{
	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1フレームの加算角度を計算

	m_Sphere.fRadius	= HAMMER_COL_SIZE;
	m_Transform.fScale	= HAMMER_SIZE;
	m_Transform.fRadian = HAMMER_DISP_ANGLE;

	m_fSwingSpeed = m_nSwingTimeFrame / SWING_TIME_MIN;

	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pSphere = new CSphere();
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
	SAFE_DELETE(m_pSphere);

	SAFE_DELETE(m_pVS);
}

/* ========================================
   更新関数
   ----------------------------------------
   内容：更新を行う
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：ハンマーの有効無効
   ======================================== */
bool CHammer::Update()
{
	Swing();		//回転による移動関数

	// 設定値まで移動しきったら
	if (m_nSwingTimeFrame <= m_dAddAngleCnt  )
	{
		m_dAddAngleCnt = 0;		// 角度変更フレームカウントリセット
		
		return false;
	}
	// 移動中はtrueを返す
	else
	{
		return true;
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
void CHammer::Draw()
{
	if (m_pSphere)
	{
		DirectX::XMFLOAT4X4 mat;
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(3.0f, 3.0f, 3.0f) *
			DirectX::XMMatrixRotationY(m_Transform.fRadian.y) *
			DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));

		m_pSphere->SetWorld(mat);
		m_pSphere->SetView(CUsingCamera::GetThis().GetCamera()->GetViewMatrix());
		m_pSphere->SetProjection(CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix());


		// レンダーターゲット、深度バッファの設定
		RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
		DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
		SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

		m_pSphere->Draw();
	}
}

/* ========================================
   ハンマー回転関数
   ----------------------------------------
   内容：ハンマーの回転による移動の処理
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::Swing()
{
	m_fAngleNow -= m_fAddAngle;	// ハンマー当たり判定角度移動		

	// 角度から座標を取得(プレイヤーの位置＋距離＋プレイヤーの周りの円状の位置)
	m_Transform.fPos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);	// 三角関数(反時計回り)とDirectX(時計回り)の角度の向きが逆なので反転する
	m_Transform.fPos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

	m_Transform.fRadian.y = m_fAngleNow - DirectX::XMConvertToRadians(90.0f);

	m_dAddAngleCnt++;	// 角度変更フレームカウント加算

}
/* ========================================
   ハンマーの回転関数
   ----------------------------------------
   内容：攻撃処理を開始する
   ----------------------------------------
   引数1：プレイヤー座標
   引数2：プレイヤーの向き
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::AttackStart(TPos3d<float>pPos, float angle)
{
	float StartAngle =
		  angle						// プレイヤーの向き
		+ DirectX::XMConvertToRadians(180.0f)
		+ ADJUST_DIRECTX_TO_COSINE	// ＋三角関数とDirectX角度の差分
		+ (SWING_ANGLE / 2);		// ＋ハンマーを振る角度の半分(扇形の右端からスタートする為)

	m_fAngleNow = StartAngle;	// 開始角度をセット

	m_tPlayerPos = pPos;		// プレイヤー座標をセット

	// 角度から座標を取得(プレイヤーの位置＋距離＋プレイヤーの周りの円状の位置)
	m_Transform.fPos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);
	m_Transform.fPos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

}
/* ========================================
   ハンマースイングスピード遅延関数
   ----------------------------------------
   内容：ハンマーのスイングスピードを遅くする
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::SwingSpeedSlow()
{
	m_nSwingTimeFrame = m_nSwingTimeFrame * SWING_TIME_ADD_MULT;	// 一振りに掛かる時間を増やす

	// 振る時間が最大値を超えた場合
	if (SWING_TIME_MAX <= m_nSwingTimeFrame)
	{
		m_nSwingTimeFrame = SWING_TIME_MAX;
	}


	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1フレームの加算角度を計算
	m_fSwingSpeed = m_fAddAngle / FIRST_ADD_ANGLE;			// 現在のハンマーの一振りの速度計算
}

/* ========================================
   チャージハンマースイングスピード遅延関数
   ----------------------------------------
   内容：チャージハンマー時のスイングスピードを遅くする
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::SwingSpeedSlow_Charge()
{

	m_nSwingTimeFrame = m_nSwingTimeFrame * SWING_TIME_ADD_MULT_CHARGE;	// 一振りに掛かる時間を増やす

	// 振る時間が最大値を超えた場合
	if (SWING_TIME_MAX <= m_nSwingTimeFrame)
	{
		m_nSwingTimeFrame = SWING_TIME_MAX;
	}

	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1フレームの加算角度を計算
	m_fSwingSpeed = m_fAddAngle / FIRST_ADD_ANGLE;			// 現在のハンマーの一振りの速度計算
}
/* ========================================
   ハンマーのスイングスピード加速関数
   ----------------------------------------
   内容：ハンマーのスイングスピードを速くする
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：なし
   ======================================== */
void CHammer::SwingSpeedFast()
{
	m_nSwingTimeFrame = m_nSwingTimeFrame * SWING_TIME_MINUS_MULT;	// 一振りに掛かる時間を減らす

	// 振る時間が最小値を下回った場合
	if (m_nSwingTimeFrame <= SWING_TIME_MIN)
	{
		m_nSwingTimeFrame = SWING_TIME_MIN;
	}


	m_fAddAngle = float(SWING_ANGLE / m_nSwingTimeFrame);	// 1フレームの加算角度を計算
	m_fSwingSpeed = m_fAddAngle / FIRST_ADD_ANGLE;			// 現在のハンマーの一振りの速度計算
}

/* ========================================
   ハンマー速度取得関数
   ----------------------------------------
   内容：ハンマーの速度を取得
   ----------------------------------------
   引数1：なし
   ----------------------------------------
   戻値：ハンマーを速度(初期値が1.0)
   ======================================== */
float CHammer::GetSwingSpeed()
{
	return m_fSwingSpeed;
}