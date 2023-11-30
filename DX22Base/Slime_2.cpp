/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ2用cpp
	------------------------------------
	Slime_2.cpp
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
	・2023/11/28 影の大きさを設定する変数追加 nieda

========================================== */

// =============== インクルード ===================
#include "Slime_2.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;
const int	LEVEL2_ATTACK = 1;	// 攻撃力

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
CSlime_2::CSlime_2()
	: m_AtcMoveType(ATTACK_CHARGE)
	, m_nChargeCnt(0)
	, m_nTackleCnt(0)
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

void CSlime_2::Update(tagTransform3d playerTransform)
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
void CSlime_2::NormalMove(tagTransform3d playerTransform)
{

	TPos3d<float> playerPos = playerTransform.fPos;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < MOVE_DISTANCE_PLAYER)
	{

		switch (m_AtcMoveType)
		{
		case CSlime_2::ATTACK_CHARGE:


			break;
		case CSlime_2::ATTACK_TACKLE:
			break;
		}
	}
	else
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
void CSlime_2::SetNormalSpeed()
{
	m_fSpeed = LEVEL2_SPEED;	//移動速度に定数をセット
}



