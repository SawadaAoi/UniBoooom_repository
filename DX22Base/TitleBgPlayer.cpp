/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトル用アニメ背景実装(プレイヤーパターン)
	---------------------------------------
	TitleBgPlayer.cpp

	作成者	takagi

	変更履歴
	・2024/01/29 制作 takagi
	・2024/02/06 制作進行 takagi

========================================== */

// =============== インクルード ===================
#include "TitleBgPlayer.h"	//自身のヘッダ
#include "Defines.h"		//画面情報用

// =============== 定数定義 ===================
const TPos3d<float> POS{ static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f };	//位置
const TPos3d<float> SCALE(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f);				//小さいときの大きさ
const int MAX_ANIM(55);																								//アニメーション数
const TDiType<int> MAX_SEAT(5, 11);																					//5x11
const /*TODO:unsigned*/ int ANIMATION_INTERVAL = 2;																	//アニメーションフレーム間隔
const unsigned int REST_FRAME = 180;																				//アニメーション間の休止時間

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTitleBgPlayer::CTitleBgPlayer()
	:CDrawAnim(MAX_ANIM, MAX_SEAT, ANIMATION_INTERVAL)	//委譲
{
	// =============== 初期化 ===================
	SetPos(POS);										//位置初期化
	SetSize(SCALE);										//大きさ初期化
	m_DushAnimeIterator = LIST_ANIMATION_DUSH.begin();	//イテレータ
	SetTexture(m_DushAnimeIterator->c_str());			//テクスチャ登録
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
CTitleBgPlayer::~CTitleBgPlayer()
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
void CTitleBgPlayer::Update()
{
	// =============== 休止 ===================
	if (m_pCounter)	//休止中
	{
		m_pCounter->Count();	//カウント進行
		if (m_pCounter->IsFin())	//カウント完了
		{
			m_pCounter.reset();		//カウンタ削除
		}

		// =============== 終了 ===================
		return;	//処理中断
	}

	// =============== 更新 ===================
	CDrawAnim::Update();	//親の関数使用
	if(!m_bAnim)	//描画完了時
	{
		// =============== 初期化 ===================
		m_DushAnimeIterator++;						//イテレータ進行
		//if (m_DushAnimeIterator != LIST_ANIMATION_DUSH.end())	//リストの範囲外
		//{
		//	SetTexture(m_DushAnimeIterator->c_str());	//listのファイル読み込み

		//	// =============== 補正 ===================
		//	m_bAnim = true;								//アニメーション描画をやり直す(完了扱いさせない)	TODO:分かりやすく書く
		//}
		// =============== 補正 ===================
		if (m_DushAnimeIterator == LIST_ANIMATION_DUSH.end())	//リストの範囲外
		{
			m_DushAnimeIterator = LIST_ANIMATION_DUSH.begin();	//イテレータ循環
		}
		SetTexture(m_DushAnimeIterator->c_str());	//listのファイル読み込み

		m_bAnim = true;								//アニメーション描画をやり直す(完了扱いさせない)	TODO:分かりやすく書く

		// =============== 動的確保 ===================
		m_pCounter = std::make_shared<CFrameCnt>(REST_FRAME);	//休止時間カウンタ作成
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
void CTitleBgPlayer::Draw(const E_DRAW_MODE& eMode)
{
	// =============== 描画 ===================
	if (!m_pCounter)	//カウンタがない時
	{
		CDrawAnim::Draw(eMode);	//親の関数使用
	}
}