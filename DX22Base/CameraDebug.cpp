/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	追跡カメラ実装
	------------------------------------
	CameraDebug.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/04 制作 takagi
	・2023/11/06 コーディング規約適用・追跡対象登録機構作成

========================================== */



// =============== インクルード ===================
#include "CameraDebug.h"	//自身のヘッダ
#include "Input.h"			//入力受付

// =============== 定数定義 ===================
const float SPEED = 0.1f;	//カメラの速度



/* ========================================
	コンストラクタ
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CCameraDebug::CCameraDebug()
{
}

/* ========================================
	デストラクタ
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
	// ↑↓→←Shift、Ctrlでカメラの注視点を動かす
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

	// W,A,S,D,Q,Eでカメラの位置を動かす
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
	if (IsKeyPress('Q'))
	{
		m_fRadius += SPEED;
	}
	if (IsKeyPress('E'))
	{
		m_fRadius -= SPEED;
	}

	//角度・距離・注視点からカメラの位置を計算
	m_fPos = {
		cosf(m_fRadY) * sinf(m_fRadXZ) * m_fRadius + m_fLook.x,
		sinf(m_fRadY) * m_fRadius,
		cosf(m_fRadY) * cosf(m_fRadXZ) * m_fRadius + m_fLook.z
	};
}