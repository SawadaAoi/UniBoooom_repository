/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	追跡カメラ実装
	------------------------------------
	CameraChase.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/11/04 制作 takagi
	・2023/11/06 コーディング規約適用・追跡対象登録機構作成 takagi
	・2023/11/07 GetViewMatrix()関数にconst修飾子付与・コメント修正 takagi
	・2023/11/08 TPos修正 takagi
	・2023/11/09 微調整 takagi
	・2023/11/10 パラメタ修正 takagi
	・2023/11/18 振動フラグ処理 takagi
	・2023/11/29 大文字・小文字の修正 takagi
	・2023/12/03 位置ゲッタ用調整 takagi
	・2023/12/04 GetViewWithoutTransposeの戻り値を変更 yamashita
	・2023/12/16 ズーム機能に対応 takagi
	・2024/01/21 Player内で更新しなくても良い様に変更・リファクタリング takagi
	・2024/01/25 GetViewWithoutTranspose()関数内で初期化しないパターンを修正 takagi
	・2024/02/15 カメラ移動 takagi

========================================== */

// =============== インクルード ===================
#include "CameraChase.h"	//自身のヘッダ
#include "Input.h"			//入力受付

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：生成時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CCameraChase::CCameraChase()
	:m_pTarget(nullptr)	//追跡対象(追跡のみを行い値を変更できないようconst修飾子にしている)
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
CCameraChase::~CCameraChase()
{
}

/* ========================================
	更新関数
	-------------------------------------
	内容：更新処理　※このオブジェクトより先に追跡対象の更新必要あり
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CCameraChase::Update()
{
	// =============== フラグ処理 ===================
	HandleFlag();	//フラグ内容処理

	// =============== ずらし ===================
	Shift();	//ずらし

	// =============== 距離更新 ===================
	Zoom();	//距離更新

	// =============== 位置更新 ===================
	m_fPos = GetPos();	//自身の位置更新
}

/* ========================================
	転置無しプロジェクション行列取得関数
	-------------------------------------
	内容：転置していないプロジェクション行列(2D固定)を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：作成した行列
=========================================== */
DirectX::XMFLOAT4X4 CCameraChase::GetViewWithoutTranspose() const
{
	// =============== 変数宣言 ===================
	DirectX::XMFLOAT4X4 View;	//行列格納用

	// =============== ビュー行列の計算 ===================
	if (m_pTarget)	//ヌルチェック
	{
		DirectX::XMStoreFloat4x4(&View, DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_pTarget->x + m_fOffsetVibrateEye.x
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_POS * cosf(*m_pfShiftAngle) *
				(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//イーズイン
					: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
						: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//イーズアウト
					: 0.0f),	//ヌル
				m_pTarget->y + m_fRadius * sinf(m_fAngle),
				m_pTarget->z + m_fOffsetVibrateEye.y - m_fRadius * cosf(m_fAngle)
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_POS * sinf(*m_pfShiftAngle) *
				(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//イーズイン
					: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
						: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//イーズアウト
					: 0.0f),	//ヌル
				0.0f),													//カメラ相対位置
			DirectX::XMVectorSet(m_pTarget->x + m_fOffsetVibrateLook.x
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_LOOK * cosf(*m_pfShiftAngle) * 
					(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//イーズイン
						: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
							: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//イーズアウト
					: 0.0f),	//ヌル
				m_pTarget->y,
				m_pTarget->z + m_fOffsetVibrateLook.y
				+ (m_pfShiftAngle && m_pShiftFrameCnt ? SHIFT_LOOK * sinf(*m_pfShiftAngle) *
				(m_bShiftIn ? sqrtf(1.0f - powf(m_pShiftFrameCnt->GetRate() - 1.0f, 2.0f))	//イーズイン
					: (m_pShiftFrameCnt->GetRate() < 0.5f ? 2.0f * m_pShiftFrameCnt->GetRate() * m_pShiftFrameCnt->GetRate()
						: 1.0f - powf(-2.0f * m_pShiftFrameCnt->GetRate() + 2.0f, 2.0f) / 2.0f))	//イーズアウト
					: 0.0f),	//ヌル
				0.0f),													//注視点
			DirectX::XMVectorSet(m_fUp.x, m_fUp.y, m_fUp.z, 0.0f)));	//アップベクトル
	}
	else
	{
		View = CCamera::GetViewWithoutTranspose();	//委譲
	}

	// =============== 提供 ===================
	return View;	//ビュー座標系
}

/* ========================================
	位置ゲッタ関数
	-------------------------------------
	内容：カメラ位置を提供
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：現在位置
=========================================== */
TPos3d<float> CCameraChase::GetPos() const
{
	// =============== 提供 ===================
	if (m_pTarget)	//ヌルチェック
	{
		return {
			m_pTarget->x + m_fOffsetVibrateEye.x,								//x座標
			m_pTarget->y + m_fRadius * sinf(m_fAngle),							//y座標
			m_pTarget->z + m_fOffsetVibrateEye.y - m_fRadius * cosf(m_fAngle)	//z座標
		};	//注視点との相対位置
	}
	else
	{
		return m_fPos;	//自身がいる絶対位置
	}
}

/* ========================================
	追跡対象登録関数
	-------------------------------------
	内容：追跡対象の位置変数のアドレスを登録
	-------------------------------------
	引数1：const TPos3d<float>* pPos：追跡対象の位置アドレス
	-------------------------------------
	戻値：なし
=========================================== */
void CCameraChase::SetTarget(const TPos3d<float>* pPos)
{
	// =============== アドレス変更 ===================
	m_pTarget = pPos;	//追跡対象登録

	// =============== 初期化 ===================
	m_fPos = GetPos();	//初期対象位置を自身位置に反映
}