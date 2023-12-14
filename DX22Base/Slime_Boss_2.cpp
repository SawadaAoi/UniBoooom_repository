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

========================================== */


// =============== インクルード ===================
#include "Slime_Boss_2.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else


#endif
const float BOSS_2_SCALE = 6.0f;					// ボス１の大きさ
const float BOSS_2_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// ボス１のスピード
const int	BOSS_2_MAX_HP = 10;					// ボス１の最大HP
const float BOSS_2_SHADOW_SCALE = 12.0f;		// ボス１の影の大きさ

const float STATE_CHANGE_ATTACK_TIME = 5.0f;
const float MOVE_JUMP_TIME = 1.5f;
const float MOVE_JUMP_SPEED = 1.0f;
const float MOVE_TARGET_SHADOW_TIME = 4.0f;
const float MOVE_TARGETING_TIME = 3.0f;
const float MOVE_DROP_SPEED = -2.0f;
const float MOVE_RIGID_TIME = 3.0f;


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

CSlime_Boss_2::CSlime_Boss_2(TPos3d<float> pos, VertexShader * pVS, Model * pModel1, Model * pModel2)
	: CSlime_Boss_2()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pVS = pVS;
	m_StateModels[0] = pModel1;
	m_StateModels[1] = pModel2;

	m_pModel = m_StateModels[1];
	m_pShadow->SetPos(m_Transform.fPos);
}

CSlime_Boss_2::~CSlime_Boss_2()
{
}

void CSlime_Boss_2::Update(tagTransform3d playerTransform)
{
	m_PlayerParam = playerTransform;

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		MoveSwitch();
	}
	else
	{
		// 突撃状態は"吹き飛び"を考慮しない
		if (m_nMoveState != MOVE_STATE::NORMAL)
		{
			m_bHitMove = false;
		}
		else
		{
			HitMove(); //敵の吹き飛び移動
			m_pShadow->SetPos(m_Transform.fPos);
		}
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.y += m_move.y;
	m_Transform.fPos.z += m_move.z;


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

void CSlime_Boss_2::MoveSwitch()
{
	switch (m_nMoveState)
	{
	case MOVE_STATE::NORMAL:
		MoveNormal();

		break;
	case MOVE_STATE::JUMP:
		MoveJump();

		break;
	case MOVE_STATE::TARGET_SHADOW:
		MoveTargetShadow();

		break;
	case MOVE_STATE::DROP:
		MoveDrop();

		break;

	default:
		break;
	}

}

void CSlime_Boss_2::MoveNormal()
{
	// プレイヤーの座標を取得
	TPos3d<float> playerPos = m_PlayerParam.fPos;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

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


		m_nMoveCnt[MOVE_STATE::NORMAL]++;
		if ((STATE_CHANGE_ATTACK_TIME * 60) <= m_nMoveCnt[MOVE_STATE::NORMAL])
		{
			m_nMoveState = MOVE_STATE::JUMP;
			m_nMoveCnt[MOVE_STATE::NORMAL] = 0;
			m_fScaleShadow = BOSS_2_SHADOW_SCALE;
		}

	}
	else
	{
		RandomMove();	// ランダム移動
		m_nMoveCnt[MOVE_STATE::NORMAL] = 0;
	}
	m_pShadow->SetPos(m_Transform.fPos);

}

void CSlime_Boss_2::MoveJump()
{

	m_move.x = 0.0f;
	m_move.y = MOVE_JUMP_SPEED;
	m_move.z = 0.0f;

	m_fScaleShadow *= 0.9f;
	m_pShadow->SetScale({ m_fScaleShadow ,m_fScaleShadow ,m_fScaleShadow });
	m_pShadow->SetPos({ m_Transform.fPos.x,	m_pShadow->GetPos().y,m_Transform.fPos.z });

	m_nMoveCnt[MOVE_STATE::JUMP]++;

	if ((MOVE_JUMP_TIME * 60) <= m_nMoveCnt[MOVE_STATE::JUMP])
	{
		m_nMoveState = MOVE_STATE::TARGET_SHADOW;
		m_nMoveCnt[MOVE_STATE::JUMP] = 0;
		m_pShadow->SetScale(BOSS_2_SHADOW_SCALE);
	}

}

void CSlime_Boss_2::MoveTargetShadow()
{
	m_nMoveCnt[MOVE_STATE::TARGET_SHADOW]++;

	if (m_nMoveCnt[MOVE_STATE::TARGET_SHADOW] <= (MOVE_TARGETING_TIME * 60))
	{
		this->SetPos({ m_PlayerParam.fPos.x, this->GetPos().y, m_PlayerParam.fPos.z });
		m_pShadow->SetPos({ m_Transform.fPos.x,	m_pShadow->GetPos().y,m_Transform.fPos.z });
	}
	else if ((MOVE_TARGET_SHADOW_TIME * 60) <= m_nMoveCnt[MOVE_STATE::TARGET_SHADOW])
	{
		m_nMoveState = MOVE_STATE::DROP;
		m_nMoveCnt[MOVE_STATE::TARGET_SHADOW] = 0;
	}
}

void CSlime_Boss_2::MoveDrop()
{
	if (0.0f < m_Transform.fPos.y)
	{
		m_move.x = 0.0f;
		m_move.y = MOVE_DROP_SPEED;
		m_move.z = 0.0f;
	}
	else
	{
		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;
		this->SetPos({ m_Transform.fPos.x,	0.0f, m_Transform.fPos.z });

		m_nMoveCnt[MOVE_STATE::DROP]++;

		if ((MOVE_RIGID_TIME * 60) <= m_nMoveCnt[MOVE_STATE::DROP])
		{
			m_nMoveState = MOVE_STATE::NORMAL;
			m_nMoveCnt[MOVE_STATE::DROP] = 0;
		}
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

void CSlime_Boss_2::SetShadowPos()
{
	switch (m_nMoveState)
	{
	case MOVE_STATE::NORMAL:

		break;
	case MOVE_STATE::JUMP:
		m_pShadow->SetPos({ m_Transform.fPos.x,
							m_pShadow->GetPos().y,
							m_Transform.fPos.z });

		break;
	case MOVE_STATE::TARGET_SHADOW:
		m_pShadow->SetPos({ m_PlayerParam.fPos.x,
							m_PlayerParam.fPos.y,
							m_PlayerParam.fPos.z });

		break;
	case MOVE_STATE::DROP:
		m_pShadow->SetPos(m_Transform.fPos);
		break;

	default:
		break;
	}
}
