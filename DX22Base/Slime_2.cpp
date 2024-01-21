/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ2用ソース
	------------------------------------
	Slime_2.cpp
	------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/08 作成 yamashita
	・2023/11/08 大きさの定数を定義	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 コンストラクタでレベルごとのパラメータをセット	yamashita
	・2023/11/11 parameter用ヘッダ追加 suzumura
	・2023/11/14 Baseからモデル、シェーダの読み込みを移動 suzumura
	・2023/11/14 SphereInfoの変更に対応 takagi
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2023/11/28 影の大きさを設定する変数追加 nieda
	・2023/12/01 タックルの挙動を追加 yamashita
	・2023/12/07 ゲームパラメータから一部定数移動 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_2.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
const int	LEVEL2_ATTACK = 1;						// 攻撃力
#if MODE_GAME_PARAMETER
#else
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;
#endif
const float LEVEL_2_SHADOW_SCALE = 2.5f;	// スライム＿レベル２の影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_2::CSlime_2()
	: m_AtcMoveType(ATTACK_NONE)
	, m_nChargeCnt(0)
	, m_nTackleCnt(0)
	, m_nAtkInterval(0)
	, tackleDirection{0.0f,0.0f,0.0f,0.0f}
{
	m_Transform.fScale = { LEVEL2_SCALE,LEVEL2_SCALE ,LEVEL2_SCALE };
	m_Sphere.fRadius *= LEVEL2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_2;
	SetNormalSpeed();
	m_nAttack = LEVEL2_ATTACK;
	m_fScaleShadow = LEVEL_2_SHADOW_SCALE;	// 影の大きさを設定
}

/* ========================================
	コンストラクタ関数(座標指定)
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成する座標
	引数2：頂点シェーダーのポインタ
	引数3：モデルのポインタ
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_2::CSlime_2(TPos3d<float> pos,VertexShader* pVS,Model* pModel)
	: CSlime_2()
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
	引数1：
	-------------------------------------
	戻値：
=========================================== */
CSlime_2::~CSlime_2()
{
}

void CSlime_2::Update()
{
	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		if (!m_bEscape  && m_nEscapeCnt == 0)	//逃げるフラグがoffなら
		{
			NormalMove();	//通常異動
		}
		else
		{
			Escape();	//爆発から逃げる
		}
	}
	else
	{
		//敵の吹き飛び移動
		HitMove();
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x;// *fSlimeMoveSpeed;
	m_Transform.fPos.z += m_move.z;// *fSlimeMoveSpeed;
}

/* ========================================
	通常移動関数
	----------------------------------------
	内容：プレイヤーを追跡する移動を行う
	----------------------------------------
	引数1：プレイヤー当たり判定(Sphere)
	----------------------------------------
	戻値：なし
======================================== */
void CSlime_2::NormalMove()
{

	TPos3d<float> playerPos = m_PlayerTran->fPos;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		if (m_nAtkInterval > LEVEL2_ATTACK_INTERVAL && m_AtcMoveType == ATTACK_NONE)
		{
			m_AtcMoveType = ATTACK_CHARGE;
			m_nAtkInterval = 0;
			return;
		}
	}

	//状態による分岐処理
	switch (m_AtcMoveType)
	{
	case(ATTACK_NONE):	//通常状態の時
		m_nAtkInterval++;
		CSlimeBase::NormalMove();

		return;
	case (ATTACK_CHARGE):
		if (m_nChargeCnt > LEVEL2_ATTACK_CHARGE_CNT)
		{	//チャージの時間を超えていたらタックル状態に移行する
			m_AtcMoveType = ATTACK_TACKLE;
			m_nChargeCnt = 0;
		}
		else 
		{ //まだだったらカウントを溜める
			m_nChargeCnt++; 
			CSlimeBase::NormalMove();

		}	

		//タックルの角度を確定
		// 敵からプレイヤーへのベクトル
		DirectX::XMFLOAT3 directionVector;
		directionVector.x = m_Transform.fPos.x - playerPos.x;
		directionVector.y = m_Transform.fPos.y - playerPos.y;
		directionVector.z = m_Transform.fPos.z - playerPos.z;
		
		// ベクトルを正規化して方向ベクトルを得る
		tackleDirection = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&directionVector));
		// 方向ベクトルから回転行列を計算
		m_Transform.fRadian.y = (atan2(-tackleDirection.m128_f32[0], -tackleDirection.m128_f32[2]));

		//移動を0に
		m_move = TTriType<float>(0.0f, 0.0f, 0.0f);

		return;
	case (ATTACK_TACKLE):
		if (m_nTackleCnt < LEVEL2_ATTACK_TACKLE_CNT)
		{	//タックル時間に満たないならタックル継続
			m_nTackleCnt++;
			m_move.x = sin(m_Transform.fRadian.y) * LEVEL2_TACKLE_SPEED;
			m_move.z = cos(m_Transform.fRadian.y) * LEVEL2_TACKLE_SPEED;

			return;
		}
		else //タックル時間を超えていればタックル終了
		{
			m_AtcMoveType = ATTACK_NONE;
			m_nTackleCnt = 0;
			CSlimeBase::NormalMove();
		}
		break;
	}

	//上記のどのifにも当てはまらない場合ランダム移動
	RandomMove();
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
void CSlime_2::SetNormalSpeed()
{
	m_fSpeed = LEVEL2_SPEED;	//移動速度に定数をセット
}



