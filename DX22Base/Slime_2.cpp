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

========================================== */

// =============== インクルード ===================
#include "Slime_2.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;
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
{
	m_scale = { LEVEL2_SCALE,LEVEL2_SCALE ,LEVEL2_SCALE };
	m_sphere.radius *= LEVEL2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_2;
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
CSlime_2::CSlime_2(TPos3d<float> pos)
{
	m_pos = pos;			// 初期座標を指定
	m_sphere.pos = pos;
	m_scale = { LEVEL2_SCALE,LEVEL2_SCALE ,LEVEL2_SCALE };
	m_sphere.radius *= LEVEL2_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_2;
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

/* ========================================
	スピード決定関数
	-------------------------------------
	内容：スライムの移動速度を設定
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_2::SetSpeed()
{
	m_fSpeed = LEVEL2_SPEED;	//移動速度に定数をセット
}



