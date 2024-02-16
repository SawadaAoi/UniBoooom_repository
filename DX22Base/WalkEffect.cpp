/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
  プレイヤー移動エフェクト処理cpp
   ---------------------------------------
   WalkEffect.cpp

   作成者 鄭 宇恩

   変更履歴
	・2024/01/30 WalkEffectクラス作成 Tei
	・2024/02/13 UsingCamera使用 takagi

========================================== */

// =============== 定数定義 =======================
const float WALK_EFFECT_STANDARD_ONE_FRAME = 0.1f * 60.0f;
const float WALK_EFFECT_SIZE = 0.9f;
const float WALK_EFFECT_HEIGHT = 0.5f;
const int	WALK_EFFECT_ALPHA = 3;	// エフェクトの濃さ(元々が薄いので重ねて表示)

// =============== インクルード ===================
#include "WalkEffect.h"
#include <time.h>
#include "UsingCamera.h"	//カメラ使用

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：プレイヤーの	トランスフォーム
	引数2：エフェクトの総時間
	引数3：位置調整用乱数
	引数4：エフェクトのeffekseerファイル
	-------------------------------------
	戻値：なし
=========================================== */
CWalkEffect::CWalkEffect(tagTransform3d tTransForm, int nDelFrame, float fPosRan, Effekseer::EffectRef walkEffect)
	: m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_fDispMaxFlame(nDelFrame)
{
	//プレイヤー移動エフェクト初期化
	m_walkEffect = walkEffect;		//エフェクトのEffekseerファイル
	
	//移動エフェクトの煙を濃くするために、同じところで3回生成する
	for (int j = 0; j < WALK_EFFECT_ALPHA; j++)
	{
		m_efcWalkHandle = LibEffekseer::GetManager()->Play(
			m_walkEffect, tTransForm.fPos.x + fPosRan, tTransForm.fPos.y + WALK_EFFECT_HEIGHT, tTransForm.fPos.z + fPosRan);

		LibEffekseer::GetManager()->SetScale(m_efcWalkHandle,
			WALK_EFFECT_SIZE,
			WALK_EFFECT_SIZE,
			WALK_EFFECT_SIZE);	//エフェクトサイズ設定

		LibEffekseer::GetManager()->SetSpeed(m_efcWalkHandle, WALK_EFFECT_STANDARD_ONE_FRAME * 0.05f);			//エフェクト再生速度設定
	}

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
	TPos3d<float> cameraPos = CUsingCamera::GetThis().GetCamera()->GetPos();							//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(CUsingCamera::GetThis().GetCamera()->GetViewWithoutTranspose(), CUsingCamera::GetThis().GetCamera()->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット
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
	if (m_fDispMaxFlame  <= m_nDelFrame)
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
bool CWalkEffect::GetDelFlg()
{
	return m_bDelFlg;
}
