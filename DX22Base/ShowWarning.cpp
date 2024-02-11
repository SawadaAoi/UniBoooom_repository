/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボス出現警告文字処理
	------------------------------------
	ShowWarning.cpp
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2024/02/11 クラス作成 Tei

========================================== */

// =============== インクルード ===================
#include "ShowWarning.h"
#include "Sprite.h"

// =============== 定数定義 =======================
const TPos2d<float> WARNING_BACKGROUND_TOPPOS(640.0f, 100.0f);		//一枚目上のバックグラウンド位置設定
const TPos2d<float> WARNING_BACKGROUND_TOPPOS_2(1920.0f, 100.0f);	//二枚目上のバックグラウンド位置設定
const TPos2d<float> WARNING_TEX_TOPPOS(640.0f, 100.0f);				//一枚目上の文字の位置設定
const TPos2d<float> WARNING_TEX_TOPPOS_2(1920.0f, 100.0f);			//二枚目上の文字の位置設定
const TPos2d<float> WARNING_BACKGROUND_BOTPOS(640.0f, 620.0f);		//一枚目下バックグラウンド位置設定
const TPos2d<float> WARNING_BACKGROUND_BOTPOS_2(1920.0f, 620.0f);	//二枚目下のバックグラウンド位置設定
const TPos2d<float> WARNING_TEX_BOTPOS(640.0f, 620.0f);				//一枚目下の文字の位置設定
const TPos2d<float> WARNING_TEX_BOTPOS_2(-640.0f, 620.0f);			//二枚目下の文字の位置設定
const TPos2d<float> WARNING_BACKGROUND_SIZE(1285.0f, -125.0f);		//バックグランド大きさ設定
const TPos2d<float> WARNING_TEX_SIZE(1280.0f, -100.0f);				//文字大きさ設定
const TPos2d<float> WARNING_ARRANGEMENT_POS(640.0f, 360.0f);		//手配書の位置設定
const TPos2d<float> WARNING_ARRANGEMENT_SIZE(315.0f, -420.0f);		//手配書大きさ設定
const DirectX::XMFLOAT4 WARNING_BG_COLOR(1.0f, 1.0f, 1.0f, 0.65f);	//バックグランド色設定


/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CShowWarning::CShowWarning()
	: m_pWarningBG(nullptr)
	, m_pWarningTex(nullptr)
	, m_fBGMove(0.0f)
	, m_fBotTexMove(0.0f)
	, m_fTopTexMove(0.0f)
	, m_pTimer(nullptr)
	, m_pBoss(nullptr)
	, m_fBGAlpha(0.7f)
	, m_pBossS2(nullptr)
	, m_pBossS3(nullptr)
	, m_fArrangementSizeAdjust(WARNING_ARRANGEMENT_SIZE.x / 2, WARNING_ARRANGEMENT_SIZE.y / 2)	// 変更量は元のサイズの半分（最初出る時は元のサイズの1.5倍
	, m_fArrangementAlpha(0.0f)
{
	// テクスチャ読み込む
	m_pWarningBG = new Texture;
	if (FAILED(m_pWarningBG->Create("Assets/Texture/Warning/obi.png")))
	{
		MessageBox(NULL, "WarningBG.png", "Error", MB_OK);
	}
	m_pWarningTex = new Texture;
	if (FAILED(m_pWarningTex->Create("Assets/Texture/Warning/WARNING_4.png")))
	{
		MessageBox(NULL, "WarningTex.png", "Error", MB_OK);
	}
	m_pBossS2 = new Texture;
	if (FAILED(m_pBossS2->Create("Assets/Texture/Warning/Lv2.png")))
	{
		MessageBox(NULL, "WarningBoss2.png", "Error", MB_OK);
	}
	m_pBossS3 = new Texture;
	if (FAILED(m_pBossS3->Create("Assets/Texture/Warning/Lv3.png")))
	{
		MessageBox(NULL, "WarningBoss3.png", "Error", MB_OK);
	}
	
}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CShowWarning::~CShowWarning()
{

	SAFE_DELETE(m_pWarningBG);
	SAFE_DELETE(m_pWarningTex);
}

/* ========================================
   更新処理関数
   -------------------------------------
   内容：更新処理
   -------------------------------------
   引数：なし
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::Update()
{
	//---警告バックグランドと文字の移動---
	// 帯の部分
	m_fBGMove--;
	if (m_fBGMove <= -1280.0f)
	{
		m_fBGMove = 0.0f;
	}

	// 文字の部分
	m_fTopTexMove -= 1.5f;
	if (m_fTopTexMove <= -1280.0f)
	{
		m_fTopTexMove = 0.0f;
	}
	m_fBotTexMove += 1.5f;
	if (m_fBotTexMove >= 1280.0f)
	{
		m_fBotTexMove = 0.0f;
	}
	
}

/* ========================================
   描画処理関数
   -------------------------------------
   内容：描画処理
   -------------------------------------
   引数：なし
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::Draw()
{
	//ボス出現後の4秒間警告出る		  (出現前の4秒出したいけど、現状はボスのポインタで判断してる↓
	//-手配書部分-
	if ( m_pTimer->GetErapsedTime() >= 45 * 60 && m_pTimer->GetErapsedTime() <= 49 * 60 && m_pBoss->IsBossPtrExist())
	{
		ArrangementAdjust();	// 手配書サイズとα値変更									    ↑																												
		if (BOSS_GAUGE_S2)		// ステージ２	→		→		→		  ステージで判断したら、↑これはいらない
		{
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, m_pBossS2);
		}
		else if (BOSS_GAUGE_S3)	// ステージ３
		{
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, m_pBossS3);
		}

		// 上半部の警告描画
		DrawWarningBG(WARNING_BACKGROUND_TOPPOS, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningBG(WARNING_BACKGROUND_TOPPOS_2, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningTex(WARNING_TEX_TOPPOS, WARNING_TEX_SIZE, m_fTopTexMove);
		DrawWarningTex(WARNING_TEX_TOPPOS_2, WARNING_TEX_SIZE, m_fTopTexMove);

		// 下半部の警告描画
		DrawWarningBG(WARNING_BACKGROUND_BOTPOS, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningBG(WARNING_BACKGROUND_BOTPOS_2, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningTex(WARNING_TEX_BOTPOS, WARNING_TEX_SIZE, m_fBotTexMove);
		DrawWarningTex(WARNING_TEX_BOTPOS_2, WARNING_TEX_SIZE, m_fBotTexMove);
	}

}

/* ========================================
   警告背景描画関数
   -------------------------------------
   内容：警告の背景（帯）の描画処理
   -------------------------------------
   引数1：描画座標(x,y)
   引数2：描画サイズ(x,y)
   引数3：描画移動量(float)
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove)
{
	//--警告の背景部分--
	DirectX::XMFLOAT4X4 warningbg[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldWarningBG = DirectX::XMMatrixTranslation(fpos.x + xMove, fpos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&warningbg[0], DirectX::XMMatrixTranspose(worldWarningBG));
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&warningbg[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projWarningBG = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&warningbg[2], DirectX::XMMatrixTranspose(projWarningBG));

	//スプライトの設定
	Sprite::SetWorld(warningbg[0]);
	Sprite::SetView(warningbg[1]);
	Sprite::SetProjection(warningbg[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(fsize.x, fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(WARNING_BG_COLOR));
	Sprite::SetTexture(m_pWarningBG);
	Sprite::Draw();
}

/* ========================================
   警告文字描画関数
   -------------------------------------
   内容：警告の文字の描画処理
   -------------------------------------
   引数1：描画座標(x,y)
   引数2：描画サイズ(x,y)
   引数3：描画移動量(float)
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove)
{

	//--警告の文字部分--
	DirectX::XMFLOAT4X4 warningTex[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldWarningTEX = DirectX::XMMatrixTranslation(fpos.x + xMove, fpos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&warningTex[0], DirectX::XMMatrixTranspose(worldWarningTEX));
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&warningTex[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projWarningTEX = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&warningTex[2], DirectX::XMMatrixTranspose(projWarningTEX));

	//スプライトの設定
	Sprite::SetWorld(warningTex[0]);
	Sprite::SetView(warningTex[1]);
	Sprite::SetProjection(warningTex[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(fsize.x, fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pWarningTex);
	Sprite::Draw();
}

/* ========================================
   警告手配書描画関数
   -------------------------------------
   内容：警告の手配書の描画処理
   -------------------------------------
   引数1：描画座標(x,y)
   引数2：描画サイズ(x,y)
   引数3：使うテクスチャ(Texture*)
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, Texture* pBoss)
{
	//--警告の手配書部分--
	DirectX::XMFLOAT4X4 warningArrangement[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldWarningArrangement = DirectX::XMMatrixTranslation(fpos.x, fpos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&warningArrangement[0], DirectX::XMMatrixTranspose(worldWarningArrangement));
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&warningArrangement[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projWarningArrangement = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&warningArrangement[2], DirectX::XMMatrixTranspose(projWarningArrangement));

	//スプライトの設定
	Sprite::SetWorld(warningArrangement[0]);
	Sprite::SetView(warningArrangement[1]);
	Sprite::SetProjection(warningArrangement[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(WARNING_ARRANGEMENT_SIZE.x + fsize.x, WARNING_ARRANGEMENT_SIZE.y + fsize.y));	// 元のサイズ＋変動量
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fArrangementAlpha));
	Sprite::SetTexture(pBoss);
	Sprite::Draw();
}

/* ========================================
   手配書描画調整関数
   -------------------------------------
   内容：手配書部分のサイズとα置の変更処理
   -------------------------------------
   引数：なし
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::ArrangementAdjust()
{
	// 手配書のα値変更
	m_fArrangementAlpha += 0.15;
	if (m_fArrangementAlpha >= 0.9f)
	{
		m_fArrangementAlpha = 0.9f;		// 0.9に越えたら0.9にする
	}

	// 手配書のサイズ変動量調整
	m_fArrangementSizeAdjust.x -= 15.0f;
	m_fArrangementSizeAdjust.y += 20.0f;
	if (m_fArrangementSizeAdjust.x <= 0 )
	{
		m_fArrangementSizeAdjust.x = 0;
	}
	if (m_fArrangementSizeAdjust.y >= 0)
	{
		m_fArrangementSizeAdjust.y = 0;
	}
}

/* ========================================
   タイマーセット関数
   -------------------------------------
   内容：タイマーポインタセット処理
   -------------------------------------
   引数1：タイマーのポインタ
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::SetTimer(CTimer* pTimer)
{
	m_pTimer = pTimer;
}

/* ========================================
   スライムマネージャセット関数
   -------------------------------------
   内容：タイマーマネージャセット処理
   -------------------------------------
   引数1：スライムマネージャのポインタ
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::SetSlimeMng(CSlimeManager * pBoss)
{
	m_pBoss = pBoss;
}
