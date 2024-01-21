/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボス方向表示矢印用ソース
	------------------------------------
	BossArrow.cpp
	------------------------------------
	作成者	tei

	変更履歴
	・2023/12/08 cpp,作成 tei
	・2023/12/12 ボス指示矢印表示、回転 tei
	・2023/12/14 ボス指示矢印位置位置計算関数追加 tei
	・2024/01/21 コメント改修 takagi

========================================== */

// =============== インクルード ===================
#include "BossArrow.h"
#include <math.h>

// =============== 定数定義 =======================
const TPos2d<float> BOSS_ARROW_POS(640.0f, 360.0f);		// ボス方向の位置設定
const float BOSS_ARROW_SIZE_X = 60.0f;					// ボス方向のXの長さ設定
const float BOSS_ARROW_SIZE_Y = -60.0f;					// ボス方向のYの長さ設定
const float OUT_OF_SCREEN_DISTANCE_RIGHT = 23.5f;		// プレイヤーから右境界の距離
const float OUT_OF_SCREEN_DISTANCE_LEFT = -23.5f;		// プレイヤーから左境界の距離
const float OUT_OF_SCREEN_DISTANCE_TOP = 17.5f;			// プレイヤーから上境界の距離
const float OUT_OF_SCREEN_DISTANCE_BUTTOM = -12.5f;		// プレイヤーから下境界の距離
const float MULTIPLE_NUM_LEFT_RIGHT = 30.0f;			// ボス指示矢印が真ん中から右左端に行く必要な倍率
const float MULTIPLE_NUM_TOP_BUTTOM = 20.0f;			// ボス指示矢印が真ん中から上下端に行く必要な倍率
const float ARROW_POS_ADJUST = 100.0f;					// ボス指示矢印を他のUIと被らないようにの調整値


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
	:m_bBossInsideScreen(true)
	,m_pArrowTex(nullptr)
	,m_pos(BOSS_ARROW_POS.x, BOSS_ARROW_POS.y)
	,m_radian(0.0f)
	,m_fDistanceX(0.0f)
	,m_fDistanceZ(0.0f)
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
	
	m_bBossInsideScreen = true;

	// ボスが存在したら、プレイヤーとボスの角度を計算
	if (m_pBoss->IsBossPtrExist())
	{
		
		// プレイヤーとボスの距離計算
		m_fDistanceX = m_pBoss->GetBossSlimePtr(0)->GetPos().x - m_pPlayer->GetPos().x;
		m_fDistanceZ = m_pBoss->GetBossSlimePtr(0)->GetPos().z - m_pPlayer->GetPos().z;
		m_radian = atan2(m_fDistanceX, m_fDistanceZ);		// プレイヤーとボスの角度
		
		// 画面内判定
		if ( m_fDistanceX <= OUT_OF_SCREEN_DISTANCE_LEFT || OUT_OF_SCREEN_DISTANCE_RIGHT <= m_fDistanceX)
		{
			
			m_bBossInsideScreen = false;		// 画面外だったらfalse
		}
		if (m_fDistanceZ <= OUT_OF_SCREEN_DISTANCE_BUTTOM || OUT_OF_SCREEN_DISTANCE_TOP <= m_fDistanceZ)
		{
			m_bBossInsideScreen = false;		// 画面外だったらfalse
		}

		ArrowMove();
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
	//ボスがいなかったら or 画面内にいる return（表示しません）
	if (!m_pBoss->IsBossPtrExist() || m_bBossInsideScreen) return;

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

/* ========================================
	矢印移動関数
	----------------------------------------
	内容：ボス指示矢印の移動計算
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CBossArrow::ArrowMove()
{
	if (m_fDistanceX >= 0.0f)
	{
		m_pos.x = BOSS_ARROW_POS.x + m_fDistanceX * MULTIPLE_NUM_LEFT_RIGHT;
		if (m_pos.x >= SCREEN_WIDTH - ARROW_POS_ADJUST)
		{
			m_pos.x = SCREEN_WIDTH - ARROW_POS_ADJUST;
		}
		if (m_fDistanceZ <= 0.0f)
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;

			if (m_pos.y >= SCREEN_HEIGHT - ARROW_POS_ADJUST)
			{
				m_pos.y = SCREEN_HEIGHT - ARROW_POS_ADJUST;
			}
		}
		else
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;
			if (m_pos.y <= ARROW_POS_ADJUST)
			{
				m_pos.y = ARROW_POS_ADJUST;
			}
		}
	}
	else
	{
		m_pos.x = BOSS_ARROW_POS.x + m_fDistanceX * MULTIPLE_NUM_LEFT_RIGHT;
		if (m_pos.x <= ARROW_POS_ADJUST)
		{
			m_pos.x = ARROW_POS_ADJUST;
		}

		if (m_fDistanceZ <= 0.0f)
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;

			if (m_pos.y >= SCREEN_HEIGHT - ARROW_POS_ADJUST)
			{
				m_pos.y = SCREEN_HEIGHT - ARROW_POS_ADJUST;
			}
		}
		else
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;
			if (m_pos.y <= ARROW_POS_ADJUST)
			{
				m_pos.y = ARROW_POS_ADJUST;
			}
		}
	}
}


