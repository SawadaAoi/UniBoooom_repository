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
#include "ShowWarning.h"
#include "Sprite.h"

// =============== 定数定義 =======================
const TPos2d<float> WARNING_BACKGROUND_TOPPOS(640.0f, 100.0f);		//バックグラウンド位置設定
const TPos2d<float> WARNING_TEX_TOPPOS(640.0f, 100.0f);				//文字の位置設定
const TPos2d<float> WARNING_BACKGROUND_BOTPOS(640.0f, 620.0f);		//バックグラウンド位置設定
const TPos2d<float> WARNING_TEX_BOTPOS(640.0f, 620.0f);				//文字の位置設定
const TPos2d<float> WARNING_BACKGROUND_TOPPOS_2(1920.0f, 100.0f);	//二枚目バックグラウンド位置設定
const TPos2d<float> WARNING_TEX_TOPPOS_2(1920.0f, 100.0f);			//二枚目文字の位置設定
const TPos2d<float> WARNING_BACKGROUND_BOTPOS_2(1920.0f, 620.0f);	//二枚目バックグラウンド位置設定
const TPos2d<float> WARNING_TEX_BOTPOS_2(-640.0f, 620.0f);			//二枚目文字の位置設定
const TPos2d<float> WARNING_BACKGROUND_SIZE(1285.0f, -125.0f);		//バックグランド大きさ設定
const TPos2d<float> WARNING_TEX_SIZE(1280.0f, -100.0f);				//文字大きさ設定
const TPos2d<float> WARNING_ARRANGEMENT_POS(640.0f, 360.0f);		//手配書の位置設定
const TPos2d<float> WARNING_ARRANGEMENT_SIZE(105.0f, -140.0f);			//手配書大きさ設定
const DirectX::XMFLOAT4 WARNING_BG_COLOR(1.0f, 1.0f, 1.0f, 0.65f);	//バックグランド色設定

const float PI = 3.1415926f;

CShowWarning::CShowWarning()
	: m_pWarningBG(nullptr)
	, m_pWarningTex(nullptr)
	, m_fBGMove(0.0f)
	, m_fBotTexMove(0.0f)
	, m_fTopTexMove(0.0f)
	, m_pTimer(nullptr)
	, m_pBoss(nullptr)
	, m_fBGalpha(0.7f)
	, m_pBossS2(nullptr)
	, m_pBossS3(nullptr)
	, m_fArrangementSizeAdjust(0.0f, 0.0f)
	, m_fArrangementSping(0.0f)
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

CShowWarning::~CShowWarning()
{

	SAFE_DELETE(m_pWarningBG);
	SAFE_DELETE(m_pWarningTex);
}

void CShowWarning::Update()
{
	m_fBGMove--;
	if (m_fBGMove <= -1280.0f)
	{
		m_fBGMove = 0.0f;
	}

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
	
	if (m_pTimer->GetErapsedTime() >= 45 * 60 && m_pTimer->GetErapsedTime() <= 49 * 60 && m_pBoss->IsBossPtrExist())
	{
		m_fArrangementSizeAdjust.x += 3.0f;
		m_fArrangementSizeAdjust.y -= 4.0f;
		if (m_fArrangementSizeAdjust.x >= WARNING_ARRANGEMENT_SIZE.x * 2)
		{
			m_fArrangementSizeAdjust.x = WARNING_ARRANGEMENT_SIZE.x * 2;
		}
		if (m_fArrangementSizeAdjust.y <= WARNING_ARRANGEMENT_SIZE.y * 2)
		{
			m_fArrangementSizeAdjust.y = WARNING_ARRANGEMENT_SIZE.y * 2;
		}

		m_fArrangementSping+=0.375f;
		if (m_fArrangementSping >= PI * 8.0f)
		{
			m_fArrangementSping = PI * 8.0f;
		}
	}
	
}

void CShowWarning::Draw()
{
	if ( m_pTimer->GetErapsedTime() >= 45 * 60 && m_pTimer->GetErapsedTime() <= 49 * 60 && m_pBoss->IsBossPtrExist())
	{
		// 上半の警告描画
		DrawWarningBG(WARNING_BACKGROUND_TOPPOS, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningBG(WARNING_BACKGROUND_TOPPOS_2, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningTex(WARNING_TEX_TOPPOS, WARNING_TEX_SIZE, m_fTopTexMove);
		DrawWarningTex(WARNING_TEX_TOPPOS_2, WARNING_TEX_SIZE, m_fTopTexMove);

		// 下半の警告描画
		DrawWarningBG(WARNING_BACKGROUND_BOTPOS, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningBG(WARNING_BACKGROUND_BOTPOS_2, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningTex(WARNING_TEX_BOTPOS, WARNING_TEX_SIZE, m_fBotTexMove);
		DrawWarningTex(WARNING_TEX_BOTPOS_2, WARNING_TEX_SIZE, m_fBotTexMove);
	}

	if (m_pTimer->GetErapsedTime() >= 45 * 60 && m_pTimer->GetErapsedTime() <= 49 * 60 && m_pBoss->IsBossPtrExist())
	{
		if (BOSS_GAUGE_S2)
		{
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, m_pBossS2, m_fArrangementSping);
		}
		else if(BOSS_GAUGE_S3)
		{
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, m_pBossS3, m_fArrangementSping);
		}
	}
	
}

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

void CShowWarning::DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, Texture* pBoss, float fSping)
{
	//--警告の手配書部分--
	DirectX::XMFLOAT4X4 warningArrangement[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldWarningArrangement =  DirectX::XMMatrixRotationZ(fSping) * DirectX::XMMatrixTranslation(fpos.x, fpos.y, 0.0f);
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
	Sprite::SetSize(DirectX::XMFLOAT2(WARNING_ARRANGEMENT_SIZE.x + fsize.x, WARNING_ARRANGEMENT_SIZE.y + fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.9f));
	Sprite::SetTexture(pBoss);
	Sprite::Draw();
}

void CShowWarning::SetTimer(CTimer* pTimer)
{
	m_pTimer = pTimer;
}

void CShowWarning::SetSlimeMng(CSlimeManager * pBoss)
{
	m_pBoss = pBoss;
}
