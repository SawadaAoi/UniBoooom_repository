/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ロードインジケータ定義
	---------------------------------------
	LoadIndicator.cpp

	作成者	takagi

	変更履歴
	・2024/03/06 制作開始 takagi

========================================== */

// =============== インクルード =====================
#include "LoadIndicator.h"	//自身のヘッダ

// =============== 定数定義 ===================
const std::string TEX = "Assets/Texture/Title/PlayerToRight.png";	//テクスチャファイル
const TPos3d<float> POS{ static_cast<float>(SCREEN_WIDTH) - 200.0f, 100.0f, 0.0f };	//位置
const TPos3d<float> SCALE(320.0f, 180.0f, 0.0f);				//小さいときの大きさ
const int MAX_ANIM(55);																								//アニメーション数
const TDiType<int> MAX_SEAT(5, 11);																					//5x11
const /*TODO:unsigned*/ int ANIMATION_INTERVAL = 2;																	//アニメーションフレーム間隔
const unsigned int REST_FRAME = 180;

/* ========================================
	自身提供関数
	----------------------------------------
	内容：自身を唯一つのみ存在させ、そのアドレスを提供する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身のアドレス
=========================================== */
CLoadIndicator& CLoadIndicator::GetThis()
{
	// =============== 生成 =====================
	static CLoadIndicator LoadIndicator;	//自身のインスタンスを生成

	// =============== 提供 =====================
	return LoadIndicator;	//生成された自身のアドレスを提供
}

void CLoadIndicator::BeginDraw()
{
	if (!m_DrawThread.joinable())	//スレッドの中身がない時
	{
		std::jthread Thread{ [this](std::stop_token ThreadStop) {

	while (!ThreadStop.stop_requested())
	{
		if (m_p2d)	//ヌルチェック
		{
			C2dPolygon Tex;
			Tex.SetTexture("Assets/Texture/Start/Wait.png");
			Tex.SetPos({ static_cast<float>(SCREEN_WIDTH / 2.0f), static_cast<float>(SCREEN_HEIGHT / 2.0f), 0.0f });
			Tex.SetSize({ static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f });
			if (GetContext())
			{
				BeginDrawDirectX();	//書き出し開始
				Tex.Draw();			//描画
				m_p2d->Update();
				m_p2d->Draw();	//描画
				EndDrawDirectX();	//書き出し完了
			}
		}
	}
			} };			//一時的なスレッド宣言
		//m_DrawThread = std::move(Thread);	//swapではなく一時変数をムーブして書き換える
		m_DrawThread.swap(Thread);
		std::stop_token token;
		m_DrawThread.get_stop_token().swap(token);
	}
}

void CLoadIndicator::EndDraw()
{
	if (m_DrawThread.joinable())	//スレッドの中身がある時
	{
		m_DrawThread.request_stop();	//関数引数のstd::stop_tokenを停止要求状態にする
		m_DrawThread.join();			//スレッド終了待機
	}
}

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CLoadIndicator::CLoadIndicator()
{
	m_p2d = std::make_shared<CDrawAnim>(MAX_ANIM, MAX_SEAT, ANIMATION_INTERVAL);//アニメ画像

	m_p2d->SetTexture(TEX.c_str());	//テクスチャ登録
	m_p2d->SetPos(POS);				//位置登録
	m_p2d->SetSize(SCALE);			//大きさ登録
	m_p2d->SetLoopFlg(true);		//ループ設定
}

/* ========================================
	コピーコンストラクタ
	----------------------------------------
	内容：複製時に行う処理
	----------------------------------------
	引数1：const CLoadIndicator& Obj：コピー元
	----------------------------------------
	戻値：なし
=========================================== */
CLoadIndicator::CLoadIndicator(const CLoadIndicator& Obj)
{	//Nothing to do
}

/* ========================================
	代入演算子
	----------------------------------------
	内容：複製に行う処理
	----------------------------------------
	引数1：const CLoadIndicator& Obj：コピー元
	----------------------------------------
	戻値：何もしていない自身の参照
=========================================== */
CLoadIndicator& CLoadIndicator::operator=(const CLoadIndicator& Obj)
{
	// =============== 提供 =====================
	return *this;	//自身の参照
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
CLoadIndicator::~CLoadIndicator()
{
}