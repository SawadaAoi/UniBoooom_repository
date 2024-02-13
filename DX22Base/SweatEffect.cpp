/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  汗エフェクトクラス 実装
   ---------------------------------------
   SweatEffect.cpp

   作成者 鄭 宇恩

   変更履歴
	・2024/02/02 HitSlimeEffectクラス作成 Tei
	・2024/02/13 UsingCamera使用 takagi

========================================== */

// =============== インクルード ===================
#include "SweatEffect.h"
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 =======================
const float SWEAT_EFFECT_STANDARD_ONE_FRAME = 0.467f * 60.0f;	
const float SWEAT_EFFECT_SIZE = 0.5f;			// エフェクトサイズ
const float SWEAT_EFFECT_SPEED = 1.3f;


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：座標
	引数2：角度
	引数3：エフェクト総時間
	引数4：エフェクトファイル
	----------------------------------------
	戻値：なし
=========================================== */
CSweatEffect::CSweatEffect(TPos3d<float> fPos, TPos3d<float> fRadian, float fTime, Effekseer::EffectRef sweatEffect)
	: m_fEffectTime(fTime)
	, m_bDelFlg(false)
	, m_nDelFrame(0)
{
	// エフェクト初期化
	m_Transform.fPos = fPos;
	m_Transform.fRadian = fRadian;
	m_SweatEffect = sweatEffect;
	m_efcSweatHnadle = LibEffekseer::GetManager()->Play(m_SweatEffect, m_Transform.fPos.x, m_Transform.fPos.y + 6.5f, m_Transform.fPos.z);	// エフェクトの開始
	LibEffekseer::GetManager()->SetScale(m_efcSweatHnadle, SWEAT_EFFECT_SIZE, SWEAT_EFFECT_SIZE , SWEAT_EFFECT_SIZE);	// エフェクトのサイズを設定
 	LibEffekseer::GetManager()->SetRotation(m_efcSweatHnadle, m_Transform.fRadian.x ,90.0f, m_Transform.fRadian.z);		// Y軸90度で固定する
	LibEffekseer::GetManager()->SetSpeed(m_efcSweatHnadle, SWEAT_EFFECT_SPEED);
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CSweatEffect::~CSweatEffect()
{
	LibEffekseer::GetManager()->StopEffect(m_efcSweatHnadle);
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：座標
	----------------------------------------
	戻値：なし
=========================================== */
void CSweatEffect::Update(TPos3d<float> fPos)
{
	m_Transform.fPos = fPos;
	LibEffekseer::GetManager()->SetLocation(m_efcSweatHnadle, m_Transform.fPos.x, m_Transform.fPos.y + 6.5f, m_Transform.fPos.z);
	DisplayTimeAdd();
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CSweatEffect::Draw()
{
	//エフェクトの描画
	TPos3d<float> cameraPos = CUsingCamera::GetThis().GetCamera()->GetPos();							//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(CUsingCamera::GetThis().GetCamera()->GetViewWithoutTranspose(), CUsingCamera::GetThis().GetCamera()->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット
}

/* ========================================
	汗エフェクト表示カウント加算処理関数
	-------------------------------------
	内容：汗エフェクト表示カウントを加算して再生秒数経ったら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSweatEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// フレーム加算

	// 再生秒数経ったら削除
	if (m_fEffectTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}
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
bool CSweatEffect::GetDelFlg()
{
	return m_bDelFlg;
}
