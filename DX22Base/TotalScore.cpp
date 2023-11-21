/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スコア管理用cpp
	---------------------------------------
	TotalScore.cpp

	作成者	山本凱翔

	変更履歴
	・2023/11/22　作成

========================================== */

// =============== インクルード ===================
#include "TotalScore.h"
#include "Sprite.h"

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CTotalScore::CTotalScore()
	: m_nTotalScore(0)
	, m_pToScoreTexture(nullptr)
{
	m_pToScoreTexture = new Texture();
	if (FAILED(m_pToScoreTexture->Create("Assets/Texture/numbers_v1/combo_numbers.png")))
	{
		MessageBox(NULL, "ToScore数字読み込み", "Error", MB_OK);
	}
}
/* ========================================
	関数：デストラクタ
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CTotalScore::~CTotalScore()
{
	SAFE_DELETE(m_pToScoreTexture);
}
/* ========================================
	関数：描画関数
	----------------------------------------
	内容：爆発マネージャーの描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::Draw()
{
	//DirectX::XMFLOAT4X4 time[3];
	//
	////ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	//DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f);
	//DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));
	//
	////ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	//DirectX::XMStoreFloat4x4(&time[1], DirectX::XMMatrixIdentity());
	//
	////プロジェクション行列には2Dとして表示するための行列を設定する
	////この行列で2Dのスクリーンの多いさが決まる
	//DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	//DirectX::XMStoreFloat4x4(&time[2], DirectX::XMMatrixTranspose(proj));
	//
	////スプライトの設定
	//Sprite::SetWorld(time[0]);
	//Sprite::SetView(time[1]);
	//Sprite::SetProjection(time[2]);
	//Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
}
void CTotalScore::AddScore(int Score)
{
	m_nTotalScore += Score;
}
/* ========================================
	トータルスコア取得関数
	----------------------------------------
	内容：トータルスコアの取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：トータルスコアの数値
======================================== */
int CTotalScore::GetTotalScore()
{
	return m_nTotalScore;
}
