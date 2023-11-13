/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	デバッグ用カメラ実装
	------------------------------------
	CameraDebug.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/04 制作 takagi
	・2023/11/06 コーディング規約適用・追跡対象登録機構作成 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/10 変数追加 takagi

========================================== */



// =============== インクルード ===================
#include "CameraDebug.h"	//自身のヘッダ
#include "Input.h"			//入力受付

// =============== 定数定義 ===================
const float SPEED = 0.1f;	//カメラの速度
const float INIT_RADIAN_XZ = 0.0f;									//X-Z面の初期ラジアン角
const float INIT_RADIAN_Y = 0.0f;									//Y-XZ面の初期ラジアン角


/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CCameraDebug::CCameraDebug()
	:m_fRadXZ(INIT_RADIAN_XZ)	//X-Z面の回転角
	, m_fRadY(INIT_RADIAN_Y)		//Y-XZ面の回転角
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
CCameraDebug::~CCameraDebug()
{
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CCameraDebug::Update()
{
	// =============== 注視点操作 =====================
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_UP))
	{
		m_fLook.z += SPEED;
	}
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_DOWN))
	{
		m_fLook.z -= SPEED;
	}
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_RIGHT))
	{
		m_fLook.x -= SPEED;
	}
	if ((IsKeyPress(VK_CONTROL) | IsKeyPress(VK_SHIFT)) & IsKeyPress(VK_LEFT))
	{
		m_fLook.x += SPEED;
	}

	// =============== カメラ回転 =====================
	if (IsKeyPress('W'))
	{
		m_fRadY += SPEED;
	}
	if (IsKeyPress('S'))
	{
		m_fRadY -= SPEED;
	}
	if (IsKeyPress('A'))
	{
		m_fRadXZ -= SPEED;
	}
	if (IsKeyPress('D'))
	{
		m_fRadXZ += SPEED;
	}

	// =============== 注視点からの距離操作 =====================
	if (IsKeyPress('Q'))
	{
		m_fRadius += SPEED;
	}
	if (IsKeyPress('E'))
	{
		m_fRadius -= SPEED;
	}

	// =============== カメラ位置割り出し =====================
	m_fPos = {
		cosf(m_fRadY) * sinf(m_fRadXZ) * m_fRadius + m_fLook.x,	//x座標
		sinf(m_fRadY) * m_fRadius,								//y座標
		cosf(m_fRadY) * cosf(m_fRadXZ) * m_fRadius + m_fLook.z	//z座標
	};
}