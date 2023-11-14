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

========================================== */

// =============== インクルード ===================
#include "hammer.h"				// 自身のヘッダ
#include "Sphere.h"				// 球体の情報用ヘッダ
#include "GameParameter.h"		// 定数定義用ヘッダー

// =============== 定数定義 =======================
const float ADJUST_DIRECTX_TO_COSINE = DirectX::XMConvertToRadians(90.0f);	// 三角関数とDirectX角度の差分(DirectXの角度は↑が0度、三角関数は→が0度)
const float ONE_FRAME_ADD_ANGLE = SWING_ANGLE / SWING_TIME_FRAME;			// 1フレームで移動する角度量


#if MODE_GAME_PARAMETER
#else
const float SWING_ANGLE			= DirectX::XMConvertToRadians(90.0f);	// ハンマーを振る範囲(扇形の角度の大きさ)
const float SWING_TIME_FRAME	= 0.15f * 60;							// ハンマーを振る時間(フレーム単位)
const float ROTATE_RADIUS		= 1.0f;									// ハンマーが回転するプレイヤーからの距離
const float HAMMER_COL_SIZE		= 0.75f;								// ハンマーの当たり判定の大きさ
const float HAMMER_SIZE			= 1.5f;									// ハンマーの大きさ
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
	: m_Transform({ 0.0f }, { HAMMER_SIZE }, { 0.0f, 0.0f, 0.0f })
	, m_pHammerGeo(nullptr)
	, m_tPlayerPos(0.0f,0.0f,0.0f)
	, m_fAngleNow(0)
	, m_dAddAngleCnt(0)

{
	m_pHammerGeo = new CSphere();							//ハンマーを仮表示するジオメトリー
	m_sphere.fRadius = HAMMER_COL_SIZE;
	m_sphere.fShift = { 0.0f,0.0f,0.0f };
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
   引数1：なそ
   ----------------------------------------
   戻値：ハンマーの有効無効
   ======================================== */
bool CHammer::Update()
{
	Swing();	//回転による移動関数

	// 設定値まで移動しきったら
	if (m_dAddAngleCnt >= SWING_TIME_FRAME)
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
void CHammer::Draw(const CCamera* pCamera)
{
	m_pHammerGeo->SetWorld(m_Transform.GetWorldMatrixSRT());			//ワールド座標にセット
	m_pHammerGeo->SetView(pCamera->GetViewMatrix());
	m_pHammerGeo->SetProjection(pCamera->GetProjectionMatrix());

	m_pHammerGeo->Draw();
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
	m_fAngleNow -= ONE_FRAME_ADD_ANGLE;	// ハンマー当たり判定角度移動		

	// 角度から座標を取得(プレイヤーの位置＋距離＋プレイヤーの周りの円状の位置)
	m_Transform.fPos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);	// 三角関数(反時計回り)とDirectX(時計回り)の角度の向きが逆なので反転する
	m_Transform.fPos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);

	m_dAddAngleCnt++;	// 角度変更フレームカウント加算

}

/* ========================================
   位置のゲット関数
   ----------------------------------------
   内容：ハンマーの位置を取得する
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：TPos3d<float> 
   ======================================== */
TPos3d<float> CHammer::GetPos()
{
	return m_Transform.fPos;
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
		+ ADJUST_DIRECTX_TO_COSINE	// ＋三角関数とDirectX角度の差分
		+ (SWING_ANGLE / 2);		// ＋ハンマーを振る角度の半分(扇形の右端からスタートする為)

	m_fAngleNow = StartAngle;	// 開始角度をセット

	m_tPlayerPos = pPos;		// プレイヤー座標をセット

	// 角度から座標を取得(プレイヤーの位置＋距離＋プレイヤーの周りの円状の位置)
	m_Transform.fPos.x = m_tPlayerPos.x + ROTATE_RADIUS * -cosf(m_fAngleNow);
	m_Transform.fPos.z = m_tPlayerPos.z + ROTATE_RADIUS * sinf(m_fAngleNow);


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
tagSphereInfo CHammer::GetSphere()
{
	return m_sphere;
}
