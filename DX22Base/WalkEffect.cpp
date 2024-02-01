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
const float WALK_EFFECT_STANDARD_ONE_FRAME = 0.4f * 60.0f;
const float WALK_EFFECT_SIZE = 0.8f;

// =============== インクルード ===================
#include "WalkEffect.h"
#include <time.h>

CWalkEffect::CWalkEffect(TPos3d<float> fPos, TPos3d<float> fRadian, float fTime, float fSize, Effekseer::EffectRef walkEffect, const CCamera * pCamera)
	: m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_pCamera(nullptr)
	, m_fEffectTime(fTime)
	, m_fRandSize(0.0f)
{
	//プレイヤー移動エフェクト初期化
	m_fEffectTime = fTime;		//エフェクトの総時間		
	m_Transform.fPos = fPos;	//エフェクトの位置
	m_walkEffect = walkEffect;	//エフェクトのEffekseerファイル
	m_fRandSize = fSize;
	m_Transform.fRadian = fRadian;

	m_pCamera = pCamera;
	for (int i = 0; i < 5; i++)
	{
		LibEffekseer::GetManager()->Play(m_walkEffect, m_Transform.fPos.x+ m_fRandSize, m_Transform.fPos.y + 0.2f, m_Transform.fPos.z + m_fRandSize);
		LibEffekseer::GetManager()->SetRotation(m_efcWalkHandle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);
		LibEffekseer::GetManager()->SetSpeed(m_efcWalkHandle, WALK_EFFECT_STANDARD_ONE_FRAME / m_fEffectTime);			//エフェクト再生速度設定
		LibEffekseer::GetManager()->SetScale(m_efcWalkHandle, WALK_EFFECT_SIZE + m_fRandSize, WALK_EFFECT_SIZE + m_fRandSize, WALK_EFFECT_SIZE + m_fRandSize);	//エフェクトサイズ設定

	}
	
}

CWalkEffect::~CWalkEffect()
{
}

void CWalkEffect::Update()
{
	DisplayTimeAdd();
}

void CWalkEffect::Draw()
{
	//エフェクトの描画
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット
}

void CWalkEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// フレーム加算

// 再生秒数経ったら削除
	if (m_fEffectTime * 0.75f <= m_nDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}

}


void CWalkEffect::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

bool CWalkEffect::GetDelFlg()
{
	return m_bDelFlg;
}
