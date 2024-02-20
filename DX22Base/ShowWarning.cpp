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
	・2024/02/20 手配書描画調整 Tei

========================================== */

// =============== インクルード ===================
#include "ShowWarning.h"
#include "Sprite.h"
#include "UIStageManager.h"


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
const float DRAWING_MAX_LEFT_POS = -1280.0f;						//描画の左端
const float DRAWING_MAX_RIGHT_POS = 1280.0f;						//描画の右端
const float TEX_MOVE_SPEED = 1.5f;									//警告文字移動スピード
const float ARRANGEMENT_ALPHA = 0.95f;								//手配書描画のα値
const float ALPHA_ADD = 0.1f;										//α置加算値
const TPos2d<float> ARRANGEMENT_SIZE_ADD(7.5f, 10.0f);				//手配書サイズ加算値
const int TIME_OF_ARRANGEMENT_PER_CHANGE = 120;						//手配書一回拡縮、色改変のフレーム数
const TPos2d<float> ARRANGEMENT_SCALE_ADD(1.5f, 2.0f);				//手配書拡縮加算値
const float COLOR_CHANGE_ADD = 0.02f;								//手配書色改変の加算値
const int WARNING_TIME_FLAME = 4.0f * 60;							//警告の表示時間

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CShowWarning::CShowWarning(int nStageNum)
	: m_pWarningBG(nullptr)
	, m_pWarningTex(nullptr)
	, m_fBGMove(0.0f)
	, m_fBotTexMove(0.0f)
	, m_fTopTexMove(0.0f)
	, m_fBGAlpha(ARRANGEMENT_ALPHA)
	, m_pBossS2(nullptr)
	, m_pBossS3(nullptr)
	, m_fArrangementSizeAdjust(WARNING_ARRANGEMENT_SIZE.x / 2, WARNING_ARRANGEMENT_SIZE.y / 2)	// 変更量は元のサイズの半分（最初出る時は元のサイズの1.5倍
	, m_fArrangementAlpha(0.0f)
	, m_nStageNum(nStageNum)
	, m_bDispFlg(false)
	, m_nDispCnt(0)
	, m_fArrangementColorAdjust(0.0f)
	, m_fArrangementScaleAdjust(0.0f, 0.0f)
	, m_nArrangementCnt(0)
	, m_bArrangementShow(false)
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
	if (m_bDispFlg)
	{
		//---警告バックグランドと文字の移動---
		// 帯の部分
		m_fBGMove--;
		if (m_fBGMove <= DRAWING_MAX_LEFT_POS)
		{
			m_fBGMove = 0.0f;
		}

		// 文字の部分
		m_fTopTexMove -= TEX_MOVE_SPEED;
		if (m_fTopTexMove <= DRAWING_MAX_LEFT_POS)
		{
			m_fTopTexMove = 0.0f;
		}
		m_fBotTexMove += TEX_MOVE_SPEED;
		if (m_fBotTexMove >= DRAWING_MAX_RIGHT_POS)
		{
			m_fBotTexMove = 0.0f;
		}

		m_nDispCnt++;

		// 描画時間を過ぎていたら
		if (WARNING_TIME_FLAME < m_nDispCnt)
		{
			m_bDispFlg = false;	// 描画終了
			m_pUIMng->StopSE(CUIStageManager::SE_BOSS_WARNING);
		}

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
	//ボス出現後の4秒間警告出る		 
	//-手配書部分-
	if (m_bDispFlg)
	{
		// 表示する前と後の拡縮を別々にする
		if (!m_bArrangementShow)
		{
			ShowArrangement();	// 手配書サイズとα値変更	
		}
		else
		{
			//色、サイズ改変
			ArrangementColorMotion(COLOR_CHANGE_ADD, TIME_OF_ARRANGEMENT_PER_CHANGE, ARRANGEMENT_ALPHA);
			ArrangementScaleMotion(ARRANGEMENT_SCALE_ADD, TIME_OF_ARRANGEMENT_PER_CHANGE, ARRANGEMENT_ALPHA);
		}

		// 手配書画像(ステージごとに変える)
		switch (m_nStageNum)
		{
		case 2:
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, 
				m_fArrangementScaleAdjust, m_pBossS2);

			break;

		case 3:
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust,	
				m_fArrangementScaleAdjust, m_pBossS3);

			break;
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
   引数3：拡縮サイズ(x,y)
   引数4：使うテクスチャ(Texture*)
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, TPos2d<float> fScale, Texture* pBoss)
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
	Sprite::SetSize(DirectX::XMFLOAT2(WARNING_ARRANGEMENT_SIZE.x + fsize.x + fScale.x, WARNING_ARRANGEMENT_SIZE.y + fsize.y + fScale.y));	// 元のサイズ＋変動量
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f - m_fArrangementColorAdjust, 1.0f - m_fArrangementColorAdjust, m_fArrangementAlpha));
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
void CShowWarning::ShowArrangement()
{
	// 手配書のα値変更
	m_fArrangementAlpha += ALPHA_ADD;
	if (m_fArrangementAlpha >= ARRANGEMENT_ALPHA)
	{
		m_fArrangementAlpha = ARRANGEMENT_ALPHA;        // 0.95に越えたら0.95にする
	}

	// 手配書のサイズ変動量調整
	m_fArrangementSizeAdjust.x -= ARRANGEMENT_SIZE_ADD.x;
	m_fArrangementSizeAdjust.y += ARRANGEMENT_SIZE_ADD.y;
	if (m_fArrangementSizeAdjust.x <= 0)
	{
		m_fArrangementSizeAdjust.x = 0;
	}
	if (m_fArrangementSizeAdjust.y >= 0)
	{
		m_fArrangementSizeAdjust.y = 0;
	}

	// 表示したら、表示フラグtrueに
	m_bArrangementShow = true;
}

/* ========================================
   手配書色変換関数
   -------------------------------------
   内容：手配書の色の変更処理
   -------------------------------------
   引数1：色の調整値(float)
   引数2：一回の色変換のフレーム数(int)
   引数3：描画のα値(float)
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::ArrangementColorMotion(float fColor, int nFlame, float fAlpha)
{
	m_nArrangementCnt++;								// 手配書描画カウント加算
	m_fArrangementAlpha = fAlpha;						
	if (m_nArrangementCnt % nFlame <= (nFlame / 2) - 1)	// 設定したフレーム数の前半加算(色赤くなる)、後半減算(色元に戻す)
	{
		m_fArrangementColorAdjust += fColor;
	}
	else
	{
		m_fArrangementColorAdjust -= fColor;
	}
}

/* ========================================
   手配書拡縮関数
   -------------------------------------
   内容：手配書の拡縮処理
   -------------------------------------
   引数1：色の調整値(float)
   引数2：一回の色変換のフレーム数(int)
   引数3：描画のα値(float)
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::ArrangementScaleMotion(TPos2d<float> fSize, int nFlame, float fAlpha)
{
	m_fArrangementAlpha = fAlpha;
	m_fArrangementSizeAdjust.x = 0.0f;						// 描画した後のサイズ調整値0にする
	m_fArrangementSizeAdjust.y = 0.0f;					
	m_nArrangementCnt++;									// 手配書描画カウント加算
	if (m_nArrangementCnt % nFlame <= (nFlame / 2) - 1)		// 設定したフレーム数の前半加算(拡大)、後半減算(縮小)
	{
		m_fArrangementScaleAdjust.x += fSize.x;
		m_fArrangementScaleAdjust.y -= fSize.y;
	}
	else
	{
		m_fArrangementScaleAdjust.x -= fSize.x;
		m_fArrangementScaleAdjust.y += fSize.y;
	}
}


/* ========================================
   ボス警告描画開始関数
   -------------------------------------
   内容：ボス警告描画を開始する
   -------------------------------------
   引数1：なし
   -------------------------------------
   戻値：なし
=========================================== */
void CShowWarning::StartShowWarning()
{
	if (m_nStageNum == 1) return;
	m_bDispFlg = true;
	m_pUIMng->PlaySE(CUIStageManager::SE_BOSS_WARNING);
}

/* ========================================
	UIマネージャーポインタセッター関数
	----------------------------------------
	内容：UIマネージャーポインタをセットする
	----------------------------------------
	引数1：UIマネージャーポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CShowWarning::SetUIStageManagerPtr(CUIStageManager * pUIMng)
{
	m_pUIMng = pUIMng;
}

/* ========================================
   表示中フラグ取得関数
   -------------------------------------
   内容：表示中かどうかのフラグを取得する
   -------------------------------------
   引数1：なし
   -------------------------------------
   戻値：true=表示中/false=非表示
=========================================== */
bool CShowWarning::GetDispFlg()
{
	return m_bDispFlg;
}

