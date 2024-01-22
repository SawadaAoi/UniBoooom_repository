/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルロゴ実装
	---------------------------------------
	TitleLogo.cpp
	---------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/16 制作 takagi
	・2023/12/17 引数参照化 takagi
	・2023/12/18 素材変更に伴うサイズ調整 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修 takagi
	・2024/01/22 Draw()関数const化 takagi

========================================== */

// =============== インクルード ===================
#include "TitleLogo.h"	//自身のヘッダ
#include "Defines.h"	//画面情報用

// =============== 定数定義 ===================
const TPos3d<float> POS_L{ static_cast<float>(SCREEN_WIDTH) / 2.0f,
	static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f };								//大きいときの位置
const TPos3d<float> POS_S{ static_cast<float>(SCREEN_WIDTH) / 2.0f, 502.0f, 0.0f };	//小さいときの位置
const TPos3d<float> SCALE_L(3594.0f * 0.37f, 2190.0f * 0.37f, 0.0f);				//大きいときの大きさ
const TPos3d<float> SCALE_S(3594.0f * 0.235f, 2190.0f * 0.235f, 0.0f);				//小さいときの大きさ
const int MAX_ANIM(1);																//アニメーション数
const TDiType<int> MAX_SEAT(1);														//1x1

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：const int& nWaitTime：待機時間
	----------------------------------------
	戻値：なし
=========================================== */
CTitleLogo::CTitleLogo(const int& nWaitTime)
	:CTitleAnime(MAX_ANIM, MAX_SEAT, nWaitTime)	//委譲
	,m_pCntLtoS(nullptr)						//縮小用カウンタ
{
	// =============== 初期化 ===================
	SetSize(SCALE_L);	//大きさ初期化
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
CTitleLogo::~CTitleLogo()
{
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
void CTitleLogo::Update()
{
	// =============== 更新 ===================
	CTitleAnime::Update();	//親の関数使用
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
			SetPos((POS_L - POS_S) * m_pCntLtoS->GetRate() + POS_S);		//カウンタ進行を利用した位置更新
		}
	}
}

/* ========================================
	描画関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CTitleLogo::Draw() const
{
	// =============== 描画 ===================
	CDrawAnim::Draw();	//親の関数使用
	if (!m_bAnim)	//アニメーション部分の描画が終わっている
	{
		C2dObject::Draw();	//最後の場面を描き続ける
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
void CTitleLogo::ChangeLtoS(const int & nFrame)
{
	m_pCntLtoS = new CFrameCnt(nFrame);	//カウント開始
}