/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ3用cpp
	------------------------------------
	Slime_3.cpp
	------------------------------------
	作成者	山下凌佑

	変更履歴
	・2023/11/08 作成 yamashita
	・2023/11/08 大きさの定数を定義	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 コンストラクタでレベルごとのパラメータをセット	yamashita
	・2023/11/11 parameter用ヘッダ追加 suzumura
	・2023/11/14 Baseからモデル、シェーダの読み込みを移動 Suzumura
	・2023/11/14 SphereInfoの変更に対応 takagi
	・2023/11/15 スライムのモデルと頂点シェーダーをmanagerから受け取るように変更 yamashita
	・2023/11/16 引数付きコンストラクタの引数に頂点シェーダーとモデルのポインタを追加 山下凌佑
	・2023/11/28 影の大きさを設定する変数追加 nieda
	・2023/11/30 プレイヤーに見られていたら止まる処理を追加 yamashita

========================================== */

// =============== インクルード ===================
#include "Slime_3.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL3_SCALE = 3.0f;
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.90;
const int	LEVEL3_ATTACK = 1;	// 攻撃力
const float LEVEL3_STOP_RANGE = DirectX::XMConvertToRadians(20.0f);	// スライムが止まる角度の範囲
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
CSlime_3::CSlime_3()
{
	m_Transform.fScale = { LEVEL3_SCALE,LEVEL3_SCALE ,LEVEL3_SCALE };
	m_Sphere.fRadius *= LEVEL3_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_3;
	SetNormalSpeed();
	m_nAttack = LEVEL3_ATTACK;
	m_fScaleShadow = LEVEL_3_SHADOW_SCALE;	// 影の大きさを設定
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
CSlime_3::CSlime_3(TPos3d<float> pos, VertexShader* pVS, Model* pModel)
	: CSlime_3()
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
CSlime_3::~CSlime_3()
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
void CSlime_3::Update(tagTransform3d playerTransform)
{
	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		if (!m_bEscape  && m_nEscapeCnt == 0)	//逃げるフラグがoffなら
		{
			NormalMove(playerTransform);	//通常異動
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
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.z += m_move.z;
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
void CSlime_3::NormalMove(tagTransform3d playerTransform)
{
	TPos3d<float> playerPos = playerTransform.fPos;
	TTriType<float> playerRad = playerTransform.fRadian;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{
		//プレイヤーがスライムの方向を向いているか確認
	 	float checkRad = playerTransform.Angle(m_Transform);
		float adjustPlayerRad = playerRad.y - DirectX::XMConvertToRadians(90.0f);
		float diffRad = abs(checkRad) - abs(adjustPlayerRad);
		//プレイヤーの向いている方向がスライムの止まる角度の中だったら
		if (abs(diffRad) < LEVEL3_STOP_RANGE)
		{
			m_move = TTriType<float>(0.0f, 0.0f, 0.0f);
			m_Transform.fRadian.y = -(m_Transform.Angle(playerTransform) - DirectX::XMConvertToRadians(90.0f));
		}
		else	//プレイヤーがスライムと別の方向を向いていたら
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
		}
	}
	else	//索敵範囲外だったら
	{
		RandomMove();	// ランダム移動

	}
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
void CSlime_3::SetNormalSpeed()
{
	m_fSpeed = LEVEL3_SPEED;	//移動速度に定数をセット
}



