/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライム.cpp
	------------------------------------
	Slime_Boss.cpp
	------------------------------------
	作成者	鈴村朋也

	変更履歴
	・2023/11/17 クラス作成 Suzumura
	・2023/11/23 突撃処理の追加 Suzumura
	・2023/11/28 影の大きさを設定する変数追加 nieda

========================================== */

// =============== インクルード ===================
#include "Slime_Boss_1.h"
#include "GameParameter.h"		//定数定義用ヘッダー
#include "Input.h"
// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_BOSS_1_SCALE = 6.0f;						// ボス１の大きさ
const float LEVEL_BOSS_1_SPEED = ENEMY_MOVE_SPEED * 1.5f;	// ボス１のスピード
const int BOSS_1_MAX_HP = 100;								// ボス１の最大HP

const float ASSAULT_DISTANCE = 0.2f;						// 突撃反応距離
const int ASSAULT_COOL_TIME = 10 * 60;						// 突撃クルータイム
const int ASSAULT_CHARGE_TIME = 2 * 60;						// 突撃チャージ時間
const int ASSAULT_TIME = 1.0f * 60;							// 突撃総時間
const float ASSAULT_SPEED = LEVEL_BOSS_1_SPEED * 15.0f;		// 突撃時のスピード
const int	BOSS_1_ATTACK = 2;	// 攻撃力

#endif
/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Boss_1::CSlime_Boss_1()
	:m_nFrame(0)
	,m_eState(NORMAL)
	,m_assaultDistancePlayer(0.0f)
	,m_assaultMovePos{0.0f,0.0f,0.0f}
{
	m_Transform.fScale = { LEVEL_BOSS_1_SCALE,LEVEL_BOSS_1_SCALE ,LEVEL_BOSS_1_SCALE };
	m_Sphere.fRadius *= LEVEL_BOSS_1_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_BOSS;
	SetNormalSpeed();
	SetMaxHp();
	m_nHp = m_nMaxHp;
	m_nAttack = BOSS_1_ATTACK;
	m_fScaleShadow = BOSS_1_SHADOW_SCALE;	// 影の大きさを設定

}

/* ========================================
	コンストラクタ関数(座標指定)
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成する座標
	引数2：頂点シェーダ
	引数3：生成するモデル
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Boss_1::CSlime_Boss_1(TPos3d<float> pos, VertexShader* pVS, Model* pModel)
	: CSlime_Boss_1()
{
	m_Transform.fPos = pos;			// 初期座標を指定
	m_pVS = pVS;
	m_pModel = pModel;
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
CSlime_Boss_1::~CSlime_Boss_1()
{
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：プレイヤー座標(TPos3d)
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_1::Update(tagTransform3d playerTransform)
{
	
	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		NormalMove(playerTransform);	// 通常行動処理
	}
	else
	{
		// チャージ中にぶっ飛ばされたらクールタイム等をリセット
		if (m_eState == CHARGE)
		{
			HitMove();		// 敵の吹き飛び移動
			ResetAssault();	// 突撃リセット
		}

		// 突撃状態は"吹き飛び"を考慮しない
		if (m_eState == ASSAULT)
		{
			m_bHitMove = false;
		}
		else
		{
			HitMove(); //敵の吹き飛び移動
		}
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x;
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

/* ========================================
	通常行動関数(ボス)
	----------------------------------------
	内容：プレイヤーを追跡する移動を行う(ボス)
	----------------------------------------
	引数1：プレイヤー座標(TPos3d)
	----------------------------------------
	戻値：無し
======================================== */
void CSlime_Boss_1::NormalMove(tagTransform3d playerTransform)
{
	TPos3d<float> movePos;
	TPos3d<float> playerPos = playerTransform.fPos;

	// フレーム加算
	m_nFrame++;

	// 状態によって動作を決定
	switch (m_eState)
	{
	//--ノーマル状態
	case NORMAL:
		// 変数宣言
		float distancePlayer;
		DirectX::XMFLOAT3 directionVector;
		DirectX::XMVECTOR direction;

		// 敵からエネミーの距離、角度を計算
		distancePlayer = m_Transform.fPos.Distance(playerPos);

		movePos = playerPos - m_Transform.fPos;	// プレイヤーへのベクトルを計算
		if (distancePlayer != 0)	//0除算回避
		{
			m_move.x = movePos.x / distancePlayer * m_fSpeed;
			m_move.z = movePos.z / distancePlayer * m_fSpeed;
		}
		// 敵からプレイヤーへのベクトル
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;

		// ベクトルを正規化して方向ベクトルを得る
		direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// 方向ベクトルから回転行列を計算
		m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);

		// クールタイムが終わってないならNORMALのまま
		if (m_nFrame <= ASSAULT_COOL_TIME)	break;

		// プレイヤーと距離が一定以内だったら
		if (distancePlayer > ASSAULT_DISTANCE)
		{
			m_eState = CHARGE;	// "チャージ"状態に遷移
			m_nFrame = 0;		// フレームリセット
		}
		break;

		//-- チャージ状態
	case CHARGE:
		Charge(playerPos, movePos);	// チャージ呼び出し
		break;

		//-- 突撃状態
	case ASSAULT:
		Assault();		// 突撃呼び出し

		break;

	}
}

/* ========================================
	チャージを行う関数
	-------------------------------------
	内容：ボスが突撃のためのチャージを行う処理
	-------------------------------------
	引数1：プレイヤー座標(TPos3d)
	引数2：プレイヤーの移動量(TPos3d)
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_1::Charge(TPos3d<float> playerPos, TPos3d<float> movePos)
{
	// 変数宣言
	float distancePlayer;
	DirectX::XMFLOAT3 directionVector;
	DirectX::XMVECTOR direction;

	// 敵からエネミーの距離、角度を計算
	distancePlayer = m_Transform.fPos.Distance(playerPos);
	movePos = playerPos - m_Transform.fPos;	// プレイヤーへのベクトルを計算

	if (distancePlayer != 0)	//0除算回避
	{
		// チャージ中は速度０
		m_fSpeed = 0;	
		m_move.x = movePos.x / distancePlayer * m_fSpeed;
		m_move.z = movePos.z / distancePlayer * m_fSpeed;
	}

	// 敵からプレイヤーへのベクトル
	directionVector.x = m_Transform.fPos.x - playerPos.x;
	directionVector.y = m_Transform.fPos.y - playerPos.y;
	directionVector.z = m_Transform.fPos.z - playerPos.z;

	// ベクトルを正規化して方向ベクトルを得る
	direction = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
	// 方向ベクトルから回転行列を計算
	m_Transform.fRadian.y = atan2(-directionVector.x, -directionVector.z);

	// チャージタイムが終わったら"突撃"
	if (m_nFrame >= ASSAULT_CHARGE_TIME)
	{
		m_assaultDistancePlayer = distancePlayer;	// 現状の距離を保存
		m_assaultMovePos = movePos;					// 移動量を保存
		m_eState = ASSAULT;							// "突撃"状態へ
		m_nFrame = 0;								// フレームリセット
	}
}

/* ========================================
	ボスが"突撃"を行う関数
	-------------------------------------
	内容：ボスが突撃攻撃を行う処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_1::Assault()
{
	if (m_assaultDistancePlayer != 0)	//0除算回避
	{
		m_fSpeed = ASSAULT_SPEED;	// 突撃中のスピードに変更
		m_move.x = m_assaultMovePos.x / m_assaultDistancePlayer * m_fSpeed;
		m_move.z = m_assaultMovePos.z / m_assaultDistancePlayer * m_fSpeed;
	}

	// 突撃時間が終了
	if (m_nFrame >= ASSAULT_TIME)
	{
		ResetAssault();	// 突撃リセット
	}
}

/* ========================================
	"突撃"のリセットを行う関数
	-------------------------------------
	内容：突撃をリセットしたいときに一括で呼ぶ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_Boss_1::ResetAssault()
{
	m_eState = NORMAL;	// "ノーマル"状態へ
	SetNormalSpeed();	// スピードを通常状態に戻す
	m_nFrame = 0;		//フレームリセット
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
void CSlime_Boss_1::SetNormalSpeed()
{
	m_fSpeed = LEVEL_BOSS_1_SPEED;	//移動速度に定数をセット
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
void CSlime_Boss_1::SetMaxHp()
{
	m_nMaxHp = BOSS_1_MAX_HP;
}