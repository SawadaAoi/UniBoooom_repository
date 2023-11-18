/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	カメラ用抽象クラス実装
	------------------------------------
	Camera.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/10/24 仮制作 takagi
	・2023/11/02 メンバー変数追加 takagi
	・2023/11/04 更新関数の実装部分削除 takagi
	・2023/11/06 フラグ整理・コメント修正 takagi
	・2023/11/07 GetViewMatrix()関数にconst修飾子付与・コメント修正 takagi
	・2023/11/09 カメラの様々動作チェック。 takagi
	・2023/11/10 パラメタ修正 takagi
	・2023/11/11 define用ヘッダ追加 suzumura
	・2023/11/17 2D表示/3D表示の切換をコンストラクタでなくGetProjectionMatrix()関数で行うように変更 takagi
	・2023/11/18 2D表示のミスを訂正 takagi

========================================== */

// =============== インクルード ===================
#include "Camera.h"		//自身のヘッダ
#include "Defines.h"	//画面情報
#include "GameParameter.h"

// =============== 定数定義 =====================
const float ASPECT = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;	//画面比率(y / x)
const TPos3d<float> INIT_LOOK(0.0f, 0.0f, 0.0f);					//初期注視地点
const TTriType<float> INIT_UP_VECTOR(0.0f, 1.0f, 0.0f);				//カメラの上方向
#if MODE_GAME_PARAMETER
#else
const TPos3d<float> INIT_POS(0.0f, 1.6f, -3.0f);					//初期位置
const float INIT_ANGLE = DirectX::XMConvertToRadians(24.0f);        //カメラの角度
const float INIT_NEAR = 1.0f;										//画面手前初期z値
const float INIT_FAR = 150.0f;										//画面奥初期z値
const float INIT_RADIUS = 40.0f;									//カメラと注視点との距離(初期値)
#endif

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CCamera::CCamera()
	:m_fPos(INIT_POS)			//位置
	,m_fLook(INIT_LOOK)			//注視点
	,m_fUp(INIT_UP_VECTOR)		//上方ベクトル
	,m_fAngle(INIT_ANGLE)		//角度
	,m_fNear(INIT_NEAR)			//画面手前
	,m_fFar(INIT_FAR)			//画面奥
	,m_fRadius(INIT_RADIUS)		//注視点とカメラの距離
{
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CCamera::~CCamera()
{
}

/* ========================================
	フラグオン関数
	-------------------------------------
	内容：引数で立っているフラグを立てる
	-------------------------------------
	引数1：const unsigned char & ucBitFlag
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag |= ucBitFlag;	//フラグ操作
}

/* ========================================
	フラグオフ関数
	-------------------------------------
	内容：引数で立っているフラグを降ろす
	-------------------------------------
	引数1：const unsigned char & ucBitFlag
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag &= !ucBitFlag;	//フラグ操作
}

/* ========================================
	フラグセッタ関数
	-------------------------------------
	内容：引数で立っているフラグを逆転させる
	-------------------------------------
	引数1：const unsigned char & ucBitFlag
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag ^= ucBitFlag;	//フラグ操作
}

/* ========================================
	ビュー行列取得関数
	-------------------------------------
	内容：カメラのビュー行列を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetViewMatrix() const
{
	// =============== 変数宣言 ===================
	DirectX::XMFLOAT4X4 mat;

	// =============== ビュー行列の計算 ===================
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_fPos.x, m_fPos.y, m_fPos.z, 0.0f),		//カメラ位置
			DirectX::XMVectorSet(m_fLook.x, m_fLook.y, m_fLook.z, 0.0f),	//注視点
			DirectX::XMVectorSet(m_fUp.x, m_fUp.y, m_fUp.z, 0.0f)))			//アップベクトル
	);	//ビュー変換

	// =============== 提供 ===================
	return mat;	//行列提供
}

/* ========================================
	プロジェクション行列取得関数
	-------------------------------------
	内容：カメラのプロジェクション行列を提供
	-------------------------------------
	引数1：const E_DRAW_TYPE& eDraw：2D表示か3D表示か
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMFLOAT4X4 CCamera::GetProjectionMatrix(const E_DRAW_TYPE& eDraw) const
{
	// =============== 変数宣言 ===================
	DirectX::XMFLOAT4X4 mat;	//行列格納用

	// =============== プロジェクション行列の計算 ===================
	switch (eDraw)	//投影選択
	{
		// =============== 2D表示 ===================
	case E_DRAW_TYPE_2D:	//2Dのプロジェクション座標作成
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, m_fNear, m_fFar)));	//左下を原点(0,0)とした座標系
		break;	//分岐処理終了

		// =============== 3D表示 ===================
	case E_DRAW_TYPE_3D:	//3Dのプロジェクション座標作成
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
			DirectX::XMMatrixPerspectiveFovLH(m_fAngle, ASPECT, m_fNear, m_fFar)));	//3Dプロジェクション変換
		break;	//分岐処理終了
	}

	// =============== 提供 ===================
	return mat;	//行列提供
}

/* ========================================
	フラグ別処理関数
	-------------------------------------
	内容：フラグによって判断される各処理を実行する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::HandleFlag()
{
	// =============== 振動フラグ ===================
	if (m_ucFlag & E_BIT_FLAG_VIBRATION)
	{
		// =============== 振動 ===================
		Vibration();	//画面揺れ
	}
}

/* ========================================
	振動関数
	-------------------------------------
	内容：画面を振動させる
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CCamera::Vibration()
{
}