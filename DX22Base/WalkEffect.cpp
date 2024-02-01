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
const float WALK_EFFECT_STANDARD_ONE_FRAME = 1.67f * 60.0f;
const float WALK_EFFECT_SIZE = 0.075f;

// =============== インクルード ===================
#include "WalkEffect.h"

CWalkEffect::CWalkEffect(TPos3d<float> fPos, float fTime, Effekseer::EffectRef walkEffect, const CCamera * pCamera)
	: m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_pCamera(nullptr)
	, m_fEffectTime(fTime)
{
	//プレイヤー移動エフェクト初期化
	m_fEffectTime = fTime;		//エフェクトの総時間		
	m_Transform.fPos = fPos;	//エフェクトの位置
	m_walkEffect = walkEffect;	//エフェクトのEffekseerファイル
	m_pCamera = pCamera;
	m_efcWalkHandle = LibEffekseer::GetManager()->Play(m_walkEffect, 	//エフェクトの開始
		m_Transform.fPos.x,
		m_Transform.fPos.y,
		m_Transform.fPos.z);
	LibEffekseer::GetManager()->SetScale(m_efcWalkHandle, WALK_EFFECT_SIZE, WALK_EFFECT_SIZE, WALK_EFFECT_SIZE);	//エフェクトサイズ設定
	LibEffekseer::GetManager()->SetSpeed(m_efcWalkHandle, WALK_EFFECT_STANDARD_ONE_FRAME / m_fEffectTime);			//エフェクト再生速度設定
}

CWalkEffect::~CWalkEffect()
{
}

void CWalkEffect::Update()
{
	LibEffekseer::GetManager()->SetLocation(m_efcWalkHandle, m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z);
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
	if (m_fEffectTime * 2  <= m_nDelFrame)
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
