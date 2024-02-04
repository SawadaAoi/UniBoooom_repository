
/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  ヒットスライムエフェクト処理cpp
   ---------------------------------------
   HitSlimeEffect.h

   作成者 鄭 宇恩

   変更履歴
	・2024/01/25 HitSlimeEffectクラス作成 Tei
	・2024/02/01 表示の不具合を修正 sawada

========================================== */

// =============== インクルード ===================
#include "HitSlimeEffect.h"

// =============== 定数定義 =======================
const float HIT_EFFECT_STANDARD_ONE_FRAME = 0.8f * 60.0f;
const float HIT_EFFECT_SIZE = 0.6f;

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：生成時間
	引数3：ヒットのEffekseer
	引数4：カメラ
	-------------------------------------
	戻値：無し
=========================================== */
CHitSlimeEffect::CHitSlimeEffect(TPos3d<float> fPos, float fTime, Effekseer::EffectRef hitEffect, const CCamera * pCamera)
	: m_pCamera(nullptr)
	, m_bDelFlg(false)
	, m_fEffectTime(fTime)
	, m_nDelFrame(0)
{
	//ヒットエフェクト初期化
	m_fEffectTime = fTime;		//エフェクトの総時間		
	m_Transform.fPos = fPos;	//エフェクトの位置
	m_hitEffect = hitEffect;	//エフェクトのEffekseerファイル
	m_efcHitHandle = LibEffekseer::GetManager()->Play(m_hitEffect, 	//エフェクトの開始
		m_Transform.fPos.x,
		m_Transform.fPos.y,
		m_Transform.fPos.z);
	LibEffekseer::GetManager()->SetScale(m_efcHitHandle, HIT_EFFECT_SIZE, HIT_EFFECT_SIZE, HIT_EFFECT_SIZE);	//エフェクトサイズ設定
	LibEffekseer::GetManager()->SetSpeed(m_efcHitHandle, m_fEffectTime / HIT_EFFECT_STANDARD_ONE_FRAME );		//エフェクト再生速度設定
	m_pCamera = pCamera;

	//エフェクトの描画(一度カメラの描画を入れないと表示がおかしくなる為)
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット

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
CHitSlimeEffect::~CHitSlimeEffect()
{
	
}

/* ========================================
	更新関数
	-------------------------------------
	内容：ヒットエフェクトの更新処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CHitSlimeEffect::Update()
{
	DisplayTimeAdd();	//	ヒットエフェクト再生時間加算
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
void CHitSlimeEffect::Draw()
{
	//エフェクトの描画
	TPos3d<float> cameraPos = m_pCamera->GetPos();							//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット
}

/* ========================================
	ヒットエフェクト表示カウント加算処理関数
	-------------------------------------
	内容：ヒットエフェクト表示カウントを加算して再生秒数経ったら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CHitSlimeEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// フレーム加算

	// 再生秒数経ったら削除
	if (m_fEffectTime <= m_nDelFrame)
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
void CHitSlimeEffect::SetCamera(const CCamera * pCamera)
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
bool CHitSlimeEffect::GetDelFlg()
{
	return m_bDelFlg;
}
