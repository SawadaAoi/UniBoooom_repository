/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	プレイヤー移動エフェクト管理用cpp
	---------------------------------------
	WalkEffectManager.cpp

	作成者	鄭 宇恩

	変更履歴
	・2024/01/30 WalkEffectManagerクラス作成 Tei

========================================== */

// =============== インクルード ===================
#include "WalkEffectManager.h"

// =============== 定数定義 =======================
const float TOTAL_WALK_EFFECT_TIME = 10.0f;

CWalkEffectManager::CWalkEffectManager()
{
	
	// プレイヤー移動エフェクト配列の初期化
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		m_pwalkEffect[i] = nullptr;
	}

	//エフェクト初期化
	m_walkEffect = LibEffekseer::Create("Assets/Effect/walk_effect/step_smoke.efkefc");
}

CWalkEffectManager::~CWalkEffectManager()
{
	// メモリ削除
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		SAFE_DELETE(m_pwalkEffect[i]);
	}
}

void CWalkEffectManager::Draw()
{
	// ヒットエフェクトの検索
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// 未使用のプレイヤー移動エフェクトはスルー
		if (m_pwalkEffect[i] == nullptr) continue;

		m_pwalkEffect[i]->Draw(); // プレイヤー移動エフェクトの描画

		break;
	}
}

void CWalkEffectManager::Update()
{
	// プレイヤー移動エフェクトを検索
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// 未使用のプレイヤー移動エフェクトはスルー
		if (m_pwalkEffect[i] == nullptr) continue;
		m_pwalkEffect[i]->Update();
		
	}
	DeleteCheck();	// 削除チェック
	
}

CWalkEffect * CWalkEffectManager::GetWalkPtr(int num)
{
	if (!m_pwalkEffect[num]) { return nullptr; }
	return m_pwalkEffect[num];
}

void CWalkEffectManager::Create(TTriType<float> pos)
{
	// プレイヤー移動エフェクトを検索
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// 使用済みのプレイヤー移動エフェクトはスルー
		if (m_pwalkEffect[i] != nullptr) continue;

		// 座標、エフェクト時間、Effekseerファイル、カメラを指定して生成
		m_pwalkEffect[i] = new CWalkEffect(pos, TOTAL_WALK_EFFECT_TIME, m_walkEffect, m_pCamera);
		m_pwalkEffect[i]->SetCamera(m_pCamera);		//カメラセット
		break;
	}
}

void CWalkEffectManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

void CWalkEffectManager::DeleteCheck()
{
	// プレイヤー移動エフェクトを検索
	for (int i = 0; i < MAX_STEP_NUM; i++)
	{
		// 未使用のプレイヤー移動エフェクトはスルー
		if (m_pwalkEffect[i] == nullptr) continue;
		// 削除フラグがたってないプレイヤー移動エフェクトはスルー
		if (m_pwalkEffect[i]->GetDelFlg() == false) continue;

		delete m_pwalkEffect[i]; m_pwalkEffect[i] = nullptr;	// プレイヤー移動エフェクトを削除する

	}
}
