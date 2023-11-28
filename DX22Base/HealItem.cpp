/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem用ヘッダ
	------------------------------------
	HealItem.cpp
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/27 cpp作成 yamashita
	・2023/11/28 上下に動く挙動を追加 yamashita
	・2023/11/28 回転の挙動を追加 yamashita

========================================== */

// =============== インクルード ===================
#include "HealItem.h"
#include "GameParameter.h"

// =============== 定数定義 ===================
#if MODE_GAME_PARAMETER

#else
const int	MOVE_INTERVAL = 60;
const int	MOVE_INTERVAL = 2;				//  アニメーションの周期
const int	COUNT_UP = 6;					//  1秒で360になるように調整
const float	HEALITEM_MOVE_Y = 1.0f;			//  移動する高さ
const float	HEALITEM_HEIGHT = 1.0f;			//  
#endif

/* ========================================
   コンストラクタ
   ----------------------------------------
   内容：開始処理
   ----------------------------------------
   引数：生成する座標、モデルのポインタ、頂点シェーダーのポインタ
   ----------------------------------------
   戻値：なし
======================================== */
CHealItem::CHealItem(TPos3d<float> pos, Model* pModel, VertexShader* pVS)
	:m_fAnimeCnt(0.0f)
	,m_pModel(nullptr)
	,m_pVS(nullptr)
{
	m_Transform.fPos = pos;
	m_Transform.fPos.y = HEALITEM_HEIGHT;		//表示される初期の高さ
	m_Transform.fScale = { HEAL_ITEM_SCALE_X, HEAL_ITEM_SCALE_Y, HEAL_ITEM_SCALE_Z };	//サイズ調整
	float radY = DirectX::XMConvertToRadians(HEALITEM_ANGLE_X);
	m_Transform.fRadian = { radY,0.0f,0.0f };	//角度初期化
	m_Sphere.fRadius = 1.0f;

	m_pModel = pModel;
	m_pVS = pVS;
	m_pModel->SetVertexShader(m_pVS);
}

/* ========================================
   デストラクタ
   ----------------------------------------
   内容：終了処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CHealItem::~CHealItem()
{

}

/* ========================================
   更新処理
   ----------------------------------------
   内容：毎フレーム呼び出す処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItem::Update()
{
	m_fAnimeCnt += COUNT_UP / HEALITEM_MOVE_INTERVAL;					//1秒60フレームで360カウント
	int degree = int(m_fAnimeCnt) % 360;								//360(一周)で剰余演算
	float rad = DirectX::XMConvertToRadians((float)degree);				//ラジアン角に変換
	m_Transform.fPos.y = cosf(rad) * HEALITEM_MOVE_Y + HEALITEM_HEIGHT;	//cosで1～-1をまわる
	m_Transform.fRadian.y = rad;										//cosで1～-1で回転する
}

/* ========================================
   描画処理
   ----------------------------------------
   内容：毎フレーム呼び出す処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItem::Draw()
{
	if (!m_pCamera) { return; }

	//-- モデル表示
	if (m_pModel) {
		DirectX::XMFLOAT4X4 mat[3];

		//拡縮、回転、移動(Y軸回転を先にしたかったのでSRTは使わない)
		DirectX::XMStoreFloat4x4(&mat[0],DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z)
			* DirectX::XMMatrixRotationY(m_Transform.fRadian.y)
			* DirectX::XMMatrixRotationX(m_Transform.fRadian.x) * DirectX::XMMatrixRotationZ(m_Transform.fRadian.z)
			* DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();

		//-- 行列をシェーダーへ設定
		m_pVS->WriteBuffer(0, mat);

		// レンダーターゲット、深度バッファの設定
		RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
		DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
		SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

		m_pModel->Draw();
	}
}
