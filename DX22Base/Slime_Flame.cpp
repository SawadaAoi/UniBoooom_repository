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

========================================== */

// =============== インクルード ===================
#include "Slime_Flame.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL_FLAME_SCALE = 1.0f;
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;
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
CSlime_Flame::CSlime_Flame()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/Golem/Golem.FBX", 0.01f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "Golem", "Error", MB_OK);	//ここでエラーメッセージ表示
	}

	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	m_Transform.fScale = { LEVEL_FLAME_SCALE,LEVEL_FLAME_SCALE ,LEVEL_FLAME_SCALE };
	m_sphere.fRadius *= LEVEL_FLAME_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_FLAME;
	SetNormalSpeed();

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
CSlime_Flame::CSlime_Flame(TPos3d<float> pos)
	: CSlime_Flame()
{
	m_Transform.fPos = pos;			// 初期座標を指定
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
	通常移動関数
	-------------------------------------
	内容：スライムの通常移動をオーバーライド
	-------------------------------------
	引数1：プレイヤー当たり判定(Sphere) ※使用してない
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_Flame::NormalMove(TPos3d<float> playerSphere)
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



