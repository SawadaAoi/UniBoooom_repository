/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  プレイヤー移動エフェクト処理cpp
   ---------------------------------------
   WalkEffect.cpp

   作成者 鄭 宇恩

   変更履歴
	・2024/01/30 WalkEffectクラス作成 Tei

========================================== */

// =============== 定数定義 =======================
const float WALK_EFFECT_STANDARD_ONE_FRAME = 0.1f * 60.0f;
const float WALK_EFFECT_SIZE = 0.9f;

// =============== インクルード ===================
#include "WalkEffect.h"
#include <time.h>

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：プレイイヤーの位置
	引数2：プレイヤー17フレーム前の位置
	引数3：プレイヤー25フレ―ム前の位置
	引数4：プレイヤーの角度
	引数5：エフェクトの総時間
	引数6：位置とサイズ調整用乱数
	引数7：エフェクトのeffekseerファイル
	引数8：カメラポインタ
	-------------------------------------
	戻値：なし
=========================================== */
CWalkEffect::CWalkEffect(TPos3d<float> fPos, TPos3d<float> fOldPos15, TPos3d<float> fOldPos30, TPos3d<float> fRadian, float fTime, float fNum, Effekseer::EffectRef walkEffect, const CCamera * pCamera)
	: m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_pCamera(nullptr)
	, m_fEffectTime(fTime)
	, m_fRandNum(fNum)
{
	//プレイヤー移動エフェクト初期化
	m_fEffectTime = fTime;			//エフェクトの総時間		
	m_OldTransform17f.fPos = fOldPos15;	//プレイヤー15フレーム前の位置
	m_OldTransform25f.fPos = fOldPos30; //プレイヤー30フレーム前の位置
	m_Transform.fPos = fPos;		//プレイヤーの位置
	m_Transform.fRadian = fRadian;	//エフェクトの角度
	m_walkEffect = walkEffect;		//エフェクトのEffekseerファイル
	
	m_pCamera = pCamera;
	//移動エフェクトの煙を濃くするために、同じところで3回生成する
	for (int i = 0; i < 3; i++)
	{
		LibEffekseer::GetManager()->Play(m_walkEffect, m_OldTransform17f.fPos.x+ m_fRandNum, m_OldTransform17f.fPos.y + 0.2f, m_OldTransform17f.fPos.z + m_fRandNum);
		LibEffekseer::GetManager()->Play(m_walkEffect, m_OldTransform25f.fPos.x, m_OldTransform25f.fPos.y + 0.15f, m_OldTransform25f.fPos.z);
		LibEffekseer::GetManager()->SetScale(m_efcWalkHandle, WALK_EFFECT_SIZE + m_fRandNum, WALK_EFFECT_SIZE + m_fRandNum, WALK_EFFECT_SIZE + m_fRandNum);	//エフェクトサイズ設定
	}
	LibEffekseer::GetManager()->SetSpeed(m_efcWalkHandle, WALK_EFFECT_STANDARD_ONE_FRAME / m_fEffectTime);			//エフェクト再生速度設定
	LibEffekseer::GetManager()->SetRotation(m_efcWalkHandle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);	//エフェクトの回転を設定

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
CWalkEffect::~CWalkEffect()
{
}

/* ========================================
	更新関数
	-------------------------------------
	内容：移動エフェクトの更新処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CWalkEffect::Update()
{
	DisplayTimeAdd();	// 移動エフェクト再生時間加算
}

/* ========================================
	描画関数
	-------------------------------------
	内容：ヒットエフェクトの描画処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CWalkEffect::Draw()
{
	//エフェクトの描画
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット
}

/* ========================================
	移動エフェクト表示カウント加算処理関数
	-------------------------------------
	内容：移動エフェクト表示カウントを加算して再生秒数経ったら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CWalkEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// フレーム加算

// 再生秒数経ったら削除
	if (m_fEffectTime  <= m_nDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}

}

/* ========================================
	カメラ情報セット関数
	----------------------------------------
	内容：描画処理で使用するカメラ情報セット
	----------------------------------------
	引数1：カメラポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CWalkEffect::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	削除フラグ取得処理関数
	-------------------------------------
	内容：削除フラグを取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：削除フラグ(bool)
=========================================== */
bool CWalkEffect::GetDelFlg()
{
	return m_bDelFlg;
}
