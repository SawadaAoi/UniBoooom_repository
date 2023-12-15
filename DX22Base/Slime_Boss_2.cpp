/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライム2.cpp
	------------------------------------
	Slime_Boss_2.cpp
	------------------------------------
	作成者	澤田蒼生

	変更履歴
	・2023/12/12 クラス作成 Sawada
	・2023/12/14 攻撃動作を追加 Sawada

========================================== */


// =============== インクルード ===================
#include "Slime_Boss_2.h"


// =============== 定数定義 =======================
const float BOSS_2_SCALE = 6.0f;					// ボス2の大きさ
const float BOSS_2_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// ボス2のスピード
const int	BOSS_2_MAX_HP = 10;						// ボス2の最大HP
const float BOSS_2_SHADOW_SCALE = 12.0f;			// ボス2の影の大きさ

const float STATE_CHANGE_ATTACK_INTERVAL	= 5.0f;		// 通常→攻撃の切り替え間隔
const float JUMP_CHAEGE_TIME				= 1.0f;		// ジャンプ前溜めの時間
const float JUMP_CHAEGE_SCALE_TIME			= 0.2f;		// ジャンプ前溜めの大きさ変更時間
const float JUMP_CHAEGE_SCALE_ADJUST		= 0.02f;	// ジャンプ前溜めの大きさ変更値
const float JUMP_TIME						= 1.5f;		// ジャンプ処理時間
const float JUMP_SPEED						= 1.0f;		// ジャンプスピード
const float JUMP_SHADOW_SIZE_MUL			= 0.9f;		// ジャンプ中の影の変更量
const float TARGET_SHADOW_TIME				= 4.0f;		// 影落とし中の時間
const float TARGET_SHADOW_PLYR_MOVE_TIME	= 3.0f;		// 影落とし中のプレイヤー追従時間
const float DROP_SPEED						= 2.0f;		// 落下処理スピード
const float DROP_RIGID_TIME					= 3.0f;		// 落下後硬直時間
const float DROP_RIGID_SCALE_TIME			= 0.2f;		// 落下後硬直の大きさ変更時間
const float DROP_RIGID_SCALE_ADJUST			= 0.01f;	// 落下後硬直の大きさ変更値




/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Boss_2::CSlime_Boss_2()
{
	m_nMoveState = MOVE_STATE::NORMAL;
	m_Transform.fScale = { BOSS_2_SCALE,BOSS_2_SCALE ,BOSS_2_SCALE };
	m_Sphere.fRadius *= BOSS_2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_BOSS;
	SetNormalSpeed();
	SetMaxHp();
	m_nHp = m_nMaxHp;
	m_nAttack = BOSS_1_ATTACK;
	m_pShadow->SetScale(BOSS_2_SHADOW_SCALE);	// 影の大きさを設定

	for (int i = 0; i < MOVE_STATE::MOVE_MAX; i++)m_nMoveCnt[i] = 0;
}

/* ========================================
	コンストラクタ関数(座標指定)
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成する座標
	引数2：頂点シェーダ
	引数3：生成するモデル
	引数4：生成するモデル
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Boss_2::CSlime_Boss_2(TPos3d<float> pos, VertexShader * pVS, Model * pModel)
	: CSlime_Boss_2()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pVS = pVS;

	m_pModel = pModel;
	m_pShadow->SetPos(m_Transform.fPos);
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
CSlime_Boss_2::~CSlime_Boss_2()
{

}


/* ========================================
	更新関数
	-------------------------------------
	内容：毎フレーム呼ばれる更新
	-------------------------------------
	引数1：プレイヤーのtransform(座標、大きさ、角度)
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::Update(tagTransform3d playerTransform)
{
	m_PlayerParam = playerTransform;	// プレイヤーの最新transformをメンバ変数にセット

	// 通常の移動状態の時
	if (!m_bHitMove)	
	{
		MoveSwitch();	// 通常移動切り替え
	}
	// ハンマーで殴られた時
	else
	{
		// 突撃状態は"吹き飛び"を考慮しない
		if (m_nMoveState != MOVE_STATE::NORMAL)
		{
			m_bHitMove = false;
		}
		else
		{
			HitMove();							// 敵の吹き飛び移動
			m_pShadow->SetPos(m_Transform.fPos);// 吹き飛び移動中の影の座標の更新
		}
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.y += m_move.y;
	m_Transform.fPos.z += m_move.z;

// ダメージ処理------------

	// ダメージ発生中じゃないなら点滅処理を行わない
	if (m_bFlash == false) return;
	// 点滅処理
	m_nInvFrame++;						//毎フレームでカウントを追加
	if (0 == m_nInvFrame % BOSS_DAMAGE_FLASH_FRAME)
	{
		// 描画するかしない切り替え
		if (m_bDrawFlg)
		{
			m_bDrawFlg = false;	// true→false
		}
		else
		{
			m_bDrawFlg = true;	// false→true
		}

	}
	// 総点滅時間を過ぎたら終了
	if (m_nInvFrame >= BOSS_DAMAGE_FLASH_TOTAL_FRAME)
	{
		m_bFlash = false;
		m_nInvFrame = 0;
		m_bDrawFlg = true;
	}
}

/* ========================================
	通常移動切り替え関数
	-------------------------------------
	内容：移動を切り替える
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::MoveSwitch()
{
	switch (m_nMoveState)
	{
	// 移動処理
	case MOVE_STATE::NORMAL:
		MoveNormal();

		break;
	// ジャンプ予備動作処理
	case MOVE_STATE::JUMP_CHARGE:
		MoveJumpCharge();

		break;

	// ジャンプ処理
	case MOVE_STATE::JUMP:
		MoveJump();

		break;

	// 落下位置決定処理
	case MOVE_STATE::TARGET_SHADOW:
		MoveTargetShadow();

		break;

	// 落下処理
	case MOVE_STATE::DROP:
		MoveDrop();

		break;
	
	// 落下硬直処理
	case MOVE_STATE::DROP_RIGID:
		MoveDropRigid();

		break;
	}

}


/* ========================================
	通常移動関数
	-------------------------------------
	内容：ランダム移動とプレイヤー追跡移動を行う
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::MoveNormal()
{
	TPos3d<float> playerPos = m_PlayerParam.fPos;					// プレイヤーの座標を取得
	float distancePlayer	= m_Transform.fPos.Distance(playerPos);	// 敵からエネミーの距離、角度を計算

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		TPos3d<float> movePos;
		movePos = playerPos - m_Transform.fPos;	// プレイヤーへのベクトルを計算
		if (distancePlayer != 0)	//0除算回避
		{
			m_move.x = movePos.x / distancePlayer * m_fSpeed;
			m_move.z = movePos.z / distancePlayer * m_fSpeed;
		}
		// 敵からプレイヤーへのベクトル
		DirectX::XMFLOAT3 directionVector;
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;

		// ベクトルを正規化して方向ベクトルを得る
		DirectX::XMVECTOR direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// 方向ベクトルから回転行列を計算
		m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);

		// 攻撃処理に切り替え
		m_nMoveCnt[MOVE_STATE::NORMAL]++;
		// 攻撃処理→ジャンプ　切り替え時間
		if ((STATE_CHANGE_ATTACK_INTERVAL * 60) <= m_nMoveCnt[MOVE_STATE::NORMAL])
		{
			m_nMoveState = MOVE_STATE::JUMP_CHARGE;		// 状態を切り替え
			m_nMoveCnt[MOVE_STATE::NORMAL] = 0;		// 加算をリセット
		}

	}
	else
	{
		RandomMove();	// ランダム移動
		m_nMoveCnt[MOVE_STATE::NORMAL] = 0;	
	}

	m_pShadow->SetPos(m_Transform.fPos);	// 影の座標を移動	

}


/* ========================================
	ジャンプ予備動作関数
	-------------------------------------
	内容：ジャンプ前の溜め動作処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::MoveJumpCharge()
{
	m_nMoveCnt[MOVE_STATE::JUMP_CHARGE]++;

	// ジャンプ前にボスの見た目が少し潰れる
	if (m_nMoveCnt[MOVE_STATE::JUMP_CHARGE] <= (JUMP_CHAEGE_SCALE_TIME * 60))
	{
		m_Transform.fScale.x *= 1.0f + JUMP_CHAEGE_SCALE_ADJUST;
		m_Transform.fScale.z *= 1.0f + JUMP_CHAEGE_SCALE_ADJUST;
		m_Transform.fScale.y *= 1.0f - JUMP_CHAEGE_SCALE_ADJUST;
	}

	// ジャンプ→落下位置ターゲット　切り替え時間
	if ((JUMP_CHAEGE_TIME * 60) <= m_nMoveCnt[MOVE_STATE::JUMP_CHARGE])
	{
		m_nMoveState = MOVE_STATE::JUMP;			// 状態を切り替え
		m_nMoveCnt[MOVE_STATE::JUMP_CHARGE] = 0;	// 加算をリセット

		this->SetScale({ BOSS_2_SCALE, BOSS_2_SCALE, BOSS_2_SCALE });	// 大きさを戻しておく
	}

	m_pShadow->SetPos(m_Transform.fPos);	// 影の座標を移動	

}

/* ========================================
	ジャンプ関数
	-------------------------------------
	内容：垂直にジャンプを行う
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::MoveJump()
{
	// 移動量をセットする
	m_move.x = 0.0f;
	m_move.y = JUMP_SPEED;		// 真上に移動
	m_move.z = 0.0f;

	// 上昇に合わせて影を小さくする
	m_fScaleShadow *= JUMP_SHADOW_SIZE_MUL;
	m_pShadow->SetScale({ m_fScaleShadow ,m_fScaleShadow ,m_fScaleShadow });
	m_pShadow->SetPos({ m_Transform.fPos.x,	m_pShadow->GetPos().y,m_Transform.fPos.z });	// ボスに合わせて上に行かない様にY座標の位置はそのまま

	m_nMoveCnt[MOVE_STATE::JUMP]++;
	// ジャンプ→落下位置ターゲット　切り替え時間
	if ((JUMP_TIME * 60) <= m_nMoveCnt[MOVE_STATE::JUMP])
	{
		m_nMoveState = MOVE_STATE::TARGET_SHADOW;	// 状態を切り替え
		m_nMoveCnt[MOVE_STATE::JUMP] = 0;		 	// 加算をリセット
		m_pShadow->SetScale(BOSS_2_SHADOW_SCALE);	// 影の大きさは戻しておく
	}

}

/* ========================================
	落下位置ターゲット処理関数
	-------------------------------------
	内容：数秒間プレイヤー位置に落下位置を狙い定める
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::MoveTargetShadow()
{
	m_nMoveCnt[MOVE_STATE::TARGET_SHADOW]++;

	// 数秒間の間だけプレイヤーの座標を追従して狙いを定める
	if (m_nMoveCnt[MOVE_STATE::TARGET_SHADOW] <= (TARGET_SHADOW_PLYR_MOVE_TIME * 60))
	{
		this->SetPos({ m_PlayerParam.fPos.x, this->GetPos().y, m_PlayerParam.fPos.z });			// ボス移動
		m_pShadow->SetPos({ m_Transform.fPos.x,	m_pShadow->GetPos().y,m_Transform.fPos.z });	// 影移動
	}
	// 落下位置ターゲット → 落下 切り替え
	else if ((TARGET_SHADOW_TIME * 60) <= m_nMoveCnt[MOVE_STATE::TARGET_SHADOW])
	{
		m_nMoveState = MOVE_STATE::DROP;				// 状態を切り替え
		m_nMoveCnt[MOVE_STATE::TARGET_SHADOW] = 0;		// 加算をリセット
	}
}

/* ========================================
	落下処理関数
	-------------------------------------
	内容：影の位置にめがけて落下する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::MoveDrop()
{
	m_move.x = 0.0f;
	m_move.y = -DROP_SPEED;
	m_move.z = 0.0f;

	// 地面に着地した場合
	if ( m_Transform.fPos.y < 0.0f)
	{
		// 移動量は0にする
		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;

		// y座標を地面に設置した状態で固定
		this->SetPos({ m_Transform.fPos.x,	0.0f, m_Transform.fPos.z });

		m_nMoveState = MOVE_STATE::DROP_RIGID;	// 状態を切り替え
		m_nMoveCnt[MOVE_STATE::DROP] = 0; 	// 加算をリセット

	}
}

/* ========================================
	落下硬直処理関数
	-------------------------------------
	内容：落下後に暫く硬直する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::MoveDropRigid()
{
	m_nMoveCnt[MOVE_STATE::DROP_RIGID]++;

	// 着地後にボスの見た目が少し潰れる
	if (m_nMoveCnt[MOVE_STATE::DROP_RIGID] <= (DROP_RIGID_SCALE_TIME * 60))
	{
		m_Transform.fScale.x *= 1.0f + DROP_RIGID_SCALE_ADJUST;
		m_Transform.fScale.z *= 1.0f + DROP_RIGID_SCALE_ADJUST;
		m_Transform.fScale.y *= 1.0f - DROP_RIGID_SCALE_ADJUST;
	}
	else
	{
		this->SetScale({ BOSS_2_SCALE, BOSS_2_SCALE, BOSS_2_SCALE });	// 大きさを戻しておく
	}


	// 落下移動 → 通常移動切り替え
	if ((DROP_RIGID_TIME * 60) <= m_nMoveCnt[MOVE_STATE::DROP_RIGID])
	{
		m_nMoveState = MOVE_STATE::NORMAL;	// 状態を切り替え
		m_nMoveCnt[MOVE_STATE::DROP_RIGID] = 0; 	// 加算をリセット

	}
}

/* ========================================
	スピード決定関数
	-------------------------------------
	内容：スライムの移動速度を設定
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::SetNormalSpeed()
{
	m_fSpeed = BOSS_2_SPEED;	//移動速度に定数をセット
}

/* ========================================
	マックスHP決定関数
	-------------------------------------
	内容：スライムのMAXHPを設定
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_2::SetMaxHp()
{
	m_nMaxHp = BOSS_2_MAX_HP;
}


