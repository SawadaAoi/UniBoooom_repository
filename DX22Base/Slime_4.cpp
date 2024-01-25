/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ4用ソース
	------------------------------------
	Slime_4.cpp
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
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_4.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL4_SCALE = 4.0f;
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.85;
const int	LEVEL4_ATTACK = 2;	// 攻撃力
#endif
const float LEVEL_4_SHADOW_SCALE = 8.0f;	// スライム＿レベル４の影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_4::CSlime_4()
{
	m_Transform.fScale = { LEVEL4_SCALE,LEVEL4_SCALE ,LEVEL4_SCALE };
	m_Sphere.fRadius *= LEVEL4_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_4;
	SetNormalSpeed();
	m_nAttack = LEVEL4_ATTACK;
	m_fScaleShadow = LEVEL_4_SHADOW_SCALE;	// 影の大きさを設定
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
CSlime_4::CSlime_4(TPos3d<float> pos, VertexShader* pVS, Model* pModel)
	: CSlime_4()
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
CSlime_4::~CSlime_4()
{
}

void CSlime_4::Update()
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

	C3dObject::Update();
}

void CSlime_4::NormalMove()
{
	TPos3d<float> playerPos = m_PlayerTran->fPos;

	// 敵からエネミーの距離、角度を計算
	float distancePlayer = m_Transform.fPos.Distance(playerPos);

	// プレイヤーと距離が一定以内だったら
	if (distancePlayer < 5)
	{
		// プレイヤーへの角度を取得
		float rad = atan2f(playerPos.z - m_Transform.fPos.z, playerPos.x - m_Transform.fPos.x);
		// プレイヤーと反対方向に移動
		m_move.x = -(cosf(rad)) * m_fSpeed;
		m_move.z = -(sinf(rad)) * m_fSpeed;
		m_Transform.fRadian.y = atan2f(m_move.x, m_move.z);
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
void CSlime_4::SetNormalSpeed()
{
	m_fSpeed = LEVEL4_SPEED;	//移動速度に定数をセット
}



