/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用オープニング実装
	---------------------------------------
	BgTitleAnime.cpp

	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi

========================================== */

// =============== インクルード ===================
#include "BgTitleAnime.h"	//自身のヘッダ
#include "Defines.h"		//画面情報用
#include "Pos3d.h"
#include "DiType.h"

// =============== 定数定義 ===================
const TPos3d<float> SCALE_L(static_cast<float>(SCREEN_WIDTH) * 2.0f,
	static_cast<float>(SCREEN_HEIGHT) * 2.0f, 0.0f);							//大きいときの大きさ
const TPos3d<float> SCALE_S(static_cast<float>(SCREEN_WIDTH),
	static_cast<float>(SCREEN_HEIGHT), 0.0f);									//小さいときの大きさ
const int MAX_ANIM(92);															//アニメーション数
const TDiType<int> MAX_SEAT(19, 5);												//1x1
const TPos3d<float> POS{ static_cast<float>(SCREEN_WIDTH) / 2.0f,
static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f };								//背景
const std::string TEXTURE_FILE="Assets/Texture/Title/TitleBg.png";	//テクスチャファイル名

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CBgTitleAnime::CBgTitleAnime()
	:CTitleAnime(MAX_ANIM, MAX_SEAT)
	,m_pCntLtoS(nullptr)					//縮小カウンタ
{
	// =============== 初期化 ===================
	SetSize(SCALE_L);					//大きさ初期化
	SetPos(POS);						//位置初期化
	SetTexture(TEXTURE_FILE.c_str());	//テクスチャ登録
	SetLoopFlg(true);
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
CBgTitleAnime::~CBgTitleAnime()
{
	// =============== 終了 ===================
	SAFE_DELETE(m_pCntLtoS);	//カウンタ削除
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CBgTitleAnime::Update()
{
	// =============== 更新 ===================
	if (m_pCntLtoS)	//ヌルチェック
	{
		--*m_pCntLtoS;	//カウントダウン
		if (m_pCntLtoS->IsFin())
		{
			delete m_pCntLtoS;		//メモリ解放
			m_pCntLtoS = nullptr;	//空アドレス代入
		}
		else
		{
			SetSize((SCALE_L - SCALE_S) * m_pCntLtoS->GetRate() + SCALE_S);	//カウンタ進行を利用した拡縮更新
		}
	}
	else
	{
		CTitleAnime::Update();	//親の関数使用
	}
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数：const E_DRAW_MODE & eMode：描画モード
	-------------------------------------
	戻値：なし
=========================================== */
void CBgTitleAnime::Draw(const E_DRAW_MODE & eMode)
{
	// =============== 描画 ===================
	CDrawAnim::Draw();	//親の関数使用
	if (!m_bAnim)	//アニメーション部分の描画が終わっている
	{
		C2dPolygon::Draw();	//最後の場面を描き続ける
	}
}

/* ========================================
	縮小関数
	-------------------------------------
	内容：(拡大状態から)縮小する	//TODO:フラグ管理で一度しか機能しないようにする
	-------------------------------------
	引数：const int & nFrame：かけるフレーム数
	-------------------------------------
	戻値：なし
=========================================== */
void CBgTitleAnime::ChangeLtoS(const int & nFrame)
{
	m_pCntLtoS = new CFrameCnt(nFrame);	//カウント開始
}