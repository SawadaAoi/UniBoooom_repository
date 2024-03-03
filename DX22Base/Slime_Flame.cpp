/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	フレイムスライムcpp
	------------------------------------
	Slime_Flame.cpp
	------------------------------------
	作成者	鈴村朋也

	変更履歴
	・2023/11/14 クラス作成 Suzumura
	・2023/11/14 炎スライム仕様の実装 Suzumura
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2023/11/28 影の大きさを設定する変数追加 nieda
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/01/18 炎スライムエフェクト追加 Tei
	・2024/02/09 UsingCamera使用 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_Flame.h"
#include "GameParameter.h"	//定数定義用ヘッダー
#include "UsingCamera.h"	//カメラ使用

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_FLAME_SCALE = 1.0f;
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;
const int	LEVEL_FLAME_ATTACK = 1;	// 攻撃力
#endif
const float LEVEL_FLAME_SHADOW_SCALE = 4.0f; // スライム＿フレイムの影の大きさ
const float FLAME_EFFECT_SCALE = 0.7f;		 // スライム＿フレイムの炎エフェクトの大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Flame::CSlime_Flame()
{
	m_Transform.fScale = { LEVEL_FLAME_SCALE,LEVEL_FLAME_SCALE ,LEVEL_FLAME_SCALE };
	m_Sphere.fRadius *= LEVEL_FLAME_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_FLAME;
	SetNormalSpeed();	
	m_nAttack = LEVEL_FLAME_ATTACK;
	m_fScaleShadow = LEVEL_FLAME_SHADOW_SCALE;	// 影の大きさを設定
}

/* ========================================
	コンストラクタ関数(座標指定)
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成する座標
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Flame::CSlime_Flame(TPos3d<float> pos, Effekseer::EffectRef flameSlimeEffect, AnimeModel* pModel)
	: CSlime_Flame()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pModel = pModel;

	// アニメーションのセット
	m_eCurAnime = (int)FLAME_SLIME_MOVE;	// 現在のアニメーションをセット
	m_pModel->Play(m_eCurAnime, true);

	// エフェクト初期化
	m_flameSlimeEffect = flameSlimeEffect;	//エフェクトをセット
	m_efcFlameHandle = LibEffekseer::GetManager()->Play(m_flameSlimeEffect, pos.x, pos.y, pos.z + 0.5f);	//エフェクトの開始
	LibEffekseer::GetManager()->SetScale(m_efcFlameHandle, FLAME_EFFECT_SCALE, FLAME_EFFECT_SCALE * 1.1f, FLAME_EFFECT_SCALE);	//エフェクトのサイズを設定
	LibEffekseer::GetManager()->SetRotation(m_efcFlameHandle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);					//エフェクトの回転角度を設定
	LibEffekseer::GetManager()->SetLocation(m_efcFlameHandle, pos.x, pos.y, pos.z);																	//エフェクトの位置を設定
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：
	-------------------------------------
	戻値：
=========================================== */
CSlime_Flame::~CSlime_Flame()
{
}

/* ========================================
	更新関数
	-------------------------------------
	内容：スライムの行動を毎フレーム更新する
	-------------------------------------
	引数1：プレイヤーの情報、スライムの移動速度
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_Flame::Update(tagTransform3d playerTransform, float fSlimeMoveSpeed)
{
	m_PlayerTran = playerTransform;	// プレイヤーの最新パラメータを取得
	m_fAnimeTime += ADD_ANIME;

	//エフェクト位置、回転角度更新
	LibEffekseer::GetManager()->SetLocation(m_efcFlameHandle, m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z + 0.5f);
	LibEffekseer::GetManager()->SetRotation(m_efcFlameHandle, m_Transform.fRadian.x, m_Transform.fRadian.y, m_Transform.fRadian.z);

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		// 現在のアニメーションが「移動」以外なら移動モーションに変更
		if (m_eCurAnime != (int)FLAME_SLIME_MOVE)
		{
			m_eCurAnime = (int)FLAME_SLIME_MOVE;
			m_fAnimeTime = 0.0f;	//アニメーションタイムのリセット
		}

		if (!m_bMvStpFlg  && m_nMvStpCnt == 0)	//停止フラグがoffなら
		{
			NormalMove();	//通常移動
		}
		else
		{
			MoveStop();	//爆発から逃げる
		}
	}
	else
	{
		//敵の吹き飛び移動
		HitMove();

		// 現在のアニメーションが「移動」以外なら移動モーションに変更
		if (m_eCurAnime != (int)FLAME_SLIME_HIT)
		{
			m_eCurAnime = (int)FLAME_SLIME_HIT;
			m_fAnimeTime = 0.0f;	//アニメーションタイムのリセット
		}
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x * fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z * fSlimeMoveSpeed;

	m_pShadow->SetPos(m_Transform.fPos);
	m_pShadow->SetScale(m_fScaleShadow);


	// エフェクトの描画
	TPos3d<float> cameraPos = CUsingCamera::GetThis().GetCamera()->GetPos();							//カメラ座標を取得
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3に変換
	LibEffekseer::SetViewPosition(fCameraPos);								//カメラ座標をセット
	LibEffekseer::SetCameraMatrix(CUsingCamera::GetThis().GetCamera()->GetViewWithoutTranspose(), CUsingCamera::GetThis().GetCamera()->GetProjectionWithoutTranspose());	//転置前のviewとprojectionをセット
}


/* ========================================
	通常移動関数
	-------------------------------------
	内容：スライムの通常移動をオーバーライド
	-------------------------------------
	引数1：プレイヤー当たり判定(Sphere) ※使用してない
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_Flame::NormalMove()
{
	RandomMove();	// ランダム移動

}

/* ========================================
	スピード決定関数
	-------------------------------------
	内容：スライムの移動速度を設定
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_Flame::SetNormalSpeed()
{
	m_fSpeed = LEVEL_FLAME_SPEED;	//移動速度に定数をセット
}



