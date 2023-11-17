/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	スライムサイズ1用cpp
	------------------------------------
	Slime_1.cpp
	------------------------------------
	作成者	澤田

	変更履歴
	・2023/11/08 作成 sawada
	・2023/11/08 大きさの定数を定義	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 スライムの移動速度を大きさごとに変更する関数を作成	yamashita
	・2023/11/08 コンストラクタでレベルごとのパラメータをセット	yamashita
	・2023/11/11 define用ヘッダ追加 suzumura
	・2023/11/14 Baseからモデル、シェーダの読み込みを移動 Suzumura
	・2023/11/14 SphereInfoの変更に対応 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_1.h"
#include "GameParameter.h"		//定数定義用ヘッダー

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float LEVEL1_SCALE = 1.0f;
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;
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
CSlime_1::CSlime_1()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/eyeBat/eyeBat.FBX", 0.1f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "eyeBat", "Error", MB_OK);	//ここでエラーメッセージ表示
	}

	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	m_Transform.fScale = { LEVEL1_SCALE,LEVEL1_SCALE ,LEVEL1_SCALE };
	m_sphere.fRadius *= LEVEL1_SCALE;
	m_eSlimeSize = E_SLIME_LEVEL::LEVEL_1;
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
CSlime_1::CSlime_1(TPos3d<float> pos)
	: CSlime_1()
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
CSlime_1::~CSlime_1()
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
void CSlime_1::SetNormalSpeed()
{
	m_fSpeed = LEVEL1_SPEED;	//移動速度に定数をセット
}



