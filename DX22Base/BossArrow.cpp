/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボス方向表示矢印用cpp
	------------------------------------
	BossArrow.cpp
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/12/08 cpp,作成 Tei

========================================== */

// =============== インクルード ===================
#include "BossArrow.h"
#include <math.h>

// =============== 定数定義 =======================
const TPos2d<float> BOSS_ARROW_POS(640.0f, 100.0f);	//ボス方向の位置設定
const float BOSS_ARROW_SIZE_X = 60.0f;				//ボス方向のXの長さ設定
const float BOSS_ARROW_SIZE_Y = -60.0f;				//ボス方向のYの長さ設定


#if MODE_GAME_PARAMETER
#else

#endif


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：int 現在の時間取る
	----------------------------------------
	戻値：なし
=========================================== */
CBossArrow::CBossArrow()
	:m_bShowArrowFlg(false)
	,m_pArrowTex(nullptr)
	,m_pos(BOSS_ARROW_POS.x, BOSS_ARROW_POS.y)
	,m_radian(0.0f)
{

	m_pArrowTex = new Texture();
	if (FAILED(m_pArrowTex->Create("Assets/Texture/Arrow.png")))
	{
		MessageBox(NULL, "Arrow.png", "Error", MB_OK);
	}

}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CBossArrow::~CBossArrow()
{
	SAFE_DELETE(m_pArrowTex);
}

/* ========================================
	更新関数
	----------------------------------------
	内容：プレイヤーとボスの位置を計算、
	      結果によってボス方向指示の矢印の位置を設定
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CBossArrow::Update()
{
	float fDistanceX;		// ポスとプレイヤーのX座標の差
	float fDistanceZ;		// ポスとプレイヤーのZ座標の差

	// ボスが存在したら、プレイヤーとボスの角度を計算
	if (m_pBoss->IsBossPtrExist())
	{
		fDistanceX = m_pBoss->GetBossSlimePtr(0)->GetPos().x - m_pPlayer->GetPos().x;
		fDistanceZ = m_pBoss->GetBossSlimePtr(0)->GetPos().z - m_pPlayer->GetPos().z;

		m_radian = atan2(fDistanceX, fDistanceZ);		// プレイヤーとボスの角度
	}
	
}

/* ========================================
	描画関数
	----------------------------------------
	内容：ボスゲージの描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CBossArrow::Draw()
{
	//ボスがいなかったら return（表示しません）
	if (!m_pBoss->IsBossPtrExist()) return;

	//ボスゲージテクスチャ（空）
	DirectX::XMFLOAT4X4 bossArrow[3];

	//ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX worldBossempty = DirectX::XMMatrixRotationZ((m_radian)) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y , 0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(10.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&bossArrow[0], DirectX::XMMatrixTranspose(worldBossempty));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&bossArrow[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projBossempty = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&bossArrow[2], DirectX::XMMatrixTranspose(projBossempty));

	//スプライトの設定
	Sprite::SetWorld(bossArrow[0]);
	Sprite::SetView(bossArrow[1]);
	Sprite::SetProjection(bossArrow[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_ARROW_SIZE_X, BOSS_ARROW_SIZE_Y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pArrowTex);
	Sprite::Draw();

}

/* ========================================
	スライムマネージャー情報セット関数
	----------------------------------------
	内容：スライムマネージャー情報ポインタセット
	----------------------------------------
	引数1：スライムマネージャー情報ポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CBossArrow::SetSlimeMng(CSlimeManager * mSlimeMng)
{
	m_pBoss = mSlimeMng;
}

/* ========================================
	プレイヤー情報セット関数
	----------------------------------------
	内容：プレイヤー情報ポインタセット
	----------------------------------------
	引数1：プレイヤー情報ポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CBossArrow::SetPlayer(CPlayer * mPlayer)
{
	m_pPlayer = mPlayer;
}


