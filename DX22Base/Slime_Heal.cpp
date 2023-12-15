/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ヒールスライム.cpp
	------------------------------------
	Slime_Heal.cpp
	------------------------------------
	作成者	鄭宇恩

	変更履歴
	・2023/12/04 cpp作成 Tei
	・2023/12/07 ゲームパラメータから一部定数移動 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_Heal.h"

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_HEAL_SCALE = 1.0f;						// スライム＿ヒールの大きさ(当たり判定含む)
const float LEVEL_HEAL_SPEED = ENEMY_MOVE_SPEED * 0.3f;		// 移動速度
const int	LEVEL_HEAL_ATTACK = 1;							// 攻撃力 （いる？
#endif
const float LEVEL_HEAL_SHADOW_SCALE = 2.0f;	// スライム＿ヒールの影の大きさ

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Heal::CSlime_Heal()
{
	m_Transform.fScale = { LEVEL_HEAL_SCALE,LEVEL_HEAL_SCALE ,LEVEL_HEAL_SCALE };
	m_Sphere.fRadius *= LEVEL_HEAL_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_HEAL;
	SetNormalSpeed();
	m_nAttack = LEVEL_HEAL_ATTACK;
	m_fScaleShadow = LEVEL_HEAL_SHADOW_SCALE;	// 影の大きさを設定
}

/* ========================================
	コンストラクタ関数(座標指定)
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：生成する座標
	引数2：シェーダーポインタ
	引数3：モデルポインタ
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_Heal::CSlime_Heal(TPos3d<float> pos, VertexShader * pVS, Model * pModel)
	:CSlime_Heal()
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
CSlime_Heal::~CSlime_Heal()
{

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
void CSlime_Heal::NormalMove()
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
void CSlime_Heal::SetNormalSpeed()
{
	m_fSpeed = LEVEL_HEAL_SPEED;	//移動速度に定数をセット

}
