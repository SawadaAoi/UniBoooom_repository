/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ゲームタイマー
	------------------------------------
	Timer.cpp
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/14 cpp,作成 Tei
	・2023/11/17 開始処理を複数種類追加、タイマーストップ実装 Sawada
	・2023/11/18 タイマー描画処理、数字部分の描画関数追加 Tei
	・2023/11/22 現時点のタイマーを取得関数追加 Tei
	・2023/12/01 時間経過でスライムのパラメータを変更する処理を修正 Sawada
	・2023/12/07 ゲームパラメータから一部定数移動・暗黙の型キャスト除去 takagi

========================================== */

// =============== インクルード ===================
#include "Timer.h"
#include "Sprite.h"
#include "GameParameter.h"

// =============== 定数定義 =======================
const TPos2d<float> MINUTE_POS(565.0f, 45.0f);			//分の位置設定
const TPos2d<float> SECOND_TENS_POS(640.0f, 45.0f);	//十の桁秒の位置設定
const TPos2d<float> SECOND_ONE_POS(690.0f, 45.0f);		//一の桁秒の位置設定
const TPos2d<float> TIME_BACKGROUND_POS(630.0f, 45.0f);	//バックグラウンド位置設定
const TPos2d<float> TIME_COLON_POS(602.5f, 45.0f);		//コロンの位置設定
const float TIME_BACK_GROUND_SIZE_X = 200.0f;			//タイマーのバックグランドのXの長さ設定
const float TIME_BACK_GROUND_SIZE_Y = -75.0f;			//タイマーのバックグランドのYの長さ設定
const float TIME_COLON_SIZE_X = 35.0f;					//タイマーのコロンのXの長さ設定
const float TIME_COLON_SIZE_Y = -35.0f;					//タイマーのコロンのYの長さ設定
#if MODE_GAME_PARAMETER
#else
const float SLM_PARAM_CHANGE_TIME[STATE_MAX] = { 60.0f, 120.0f, 180.0f };	// 経過時間の秒数
const int	SLM_CREATE_NUM[STATE_MAX] = { 20, 25, MAX_SLIME_NUM };	// 最大生成数
const int SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 1.0f, 1.5f, 1.5f };			// 生成間隔
const float SLM_MOVE_ADD_SPEED[STATE_MAX] = { 1.0f, 1.1f, 1.2f };			// 移動スピード
#endif



/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTimer::CTimer()
	: m_nTimeCnt(STAGE_TIME)
	, m_bStartFlg(false)
	, m_dWaitCnt(0)
	, m_bStopFlg(false)
	, m_pTextureBG(nullptr)
	, m_pTextureColon(nullptr)
	, m_pTextureNum(nullptr)
	, m_nMaxSlimeNum(SLM_CREATE_NUM[STATE_FIRST])
	, m_nSlimeCreateInterval(static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_FIRST]))
	, m_fSlimeMoveSpeed(SLM_MOVE_ADD_SPEED[STATE_FIRST])
{
	//数字のテクスチャ読む込み

	m_pTextureNum = new Texture();

	if (FAILED(m_pTextureNum->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "number.png", "Error", MB_OK);
	}

	//タイマーの裏テクスチャ読み込む
	m_pTextureBG = new Texture;
	if (FAILED(m_pTextureBG->Create("Assets/Texture/timer_back_1.png")))
	{
		MessageBox(NULL, "timebackground.png", "Error", MB_OK);
	}

	m_pTextureColon = new Texture;
	if (FAILED(m_pTextureColon->Create("Assets/Texture/numbers_v1/colon.png")))
	{
		MessageBox(NULL, "colon.png", "Error", MB_OK);
	}
}
/* ========================================
	コンストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTimer::~CTimer()
{

	SAFE_DELETE(m_pTextureColon);

	SAFE_DELETE(m_pTextureNum);

	SAFE_DELETE(m_pTextureBG);
}
/* ========================================
	タイマー更新関数
	----------------------------------------
	内容：タイマーのカウントダウン処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::Update()
{
	// 待機時間のチェック
	if (m_bStartFlg == false)
	{
		WaitTimeCheck();
		return;
	}

	// タイマーストップのチェック
	if (m_bStopFlg == true)
	{
		return;
	}
	// タイマー減算
	m_nTimeCnt--;
	//時間が0になったら終了処理に
	if (m_nTimeCnt <= 0)
	{
		// TODOゲーム終了処理
	}

	ChangeSlimeParam();
}
/* ========================================
	描画関数
	----------------------------------------
	内容：タイマーの描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::Draw()
{
	//-----時間UIの描画-----

	//タイマーが0になったら、return（表示しない）
	if (m_nTimeCnt <= 0) return;
	//--時間の背景部分(仮素材)--
	DirectX::XMFLOAT4X4 timebackground[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldTimerBG = DirectX::XMMatrixTranslation(TIME_BACKGROUND_POS.x, TIME_BACKGROUND_POS.y, 0.0f);
	DirectX::XMStoreFloat4x4(&timebackground[0], DirectX::XMMatrixTranspose(worldTimerBG));
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&timebackground[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projTimerBG = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&timebackground[2], DirectX::XMMatrixTranspose(projTimerBG));

	//スプライトの設定
	Sprite::SetWorld(timebackground[0]);
	Sprite::SetView(timebackground[1]);
	Sprite::SetProjection(timebackground[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(200.0f, -75.0f));
	Sprite::SetSize(DirectX::XMFLOAT2(TIME_BACK_GROUND_SIZE_X, TIME_BACK_GROUND_SIZE_Y));
	Sprite::SetTexture(m_pTextureBG);
	Sprite::Draw();

	//--コロンの描画--
	DirectX::XMFLOAT4X4 colon[3];
	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldColon = DirectX::XMMatrixTranslation(TIME_COLON_POS.x, TIME_COLON_POS.y, 0.0f);
	DirectX::XMStoreFloat4x4(&colon[0], DirectX::XMMatrixTranspose(worldColon));
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&colon[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projColon = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&colon[2], DirectX::XMMatrixTranspose(projColon));

	//スプライトの設定
	Sprite::SetWorld(colon[0]);
	Sprite::SetView(colon[1]);
	Sprite::SetProjection(colon[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(25.0f, -25.0f));
	Sprite::SetSize(DirectX::XMFLOAT2(TIME_COLON_SIZE_X, TIME_COLON_SIZE_Y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pTextureColon);
	Sprite::Draw();
	//--時間（数字部分）の描画
	DrawNumber(MINUTE_POS, GetMinite());				//分の秒画
	DrawNumber(SECOND_TENS_POS, (GetSecond() / 10));	//秒の十の桁の描画 
	DrawNumber(SECOND_ONE_POS, (GetSecond() % 10));		//秒の一の桁の描画
}
/* ========================================
	タイマー取得関数
	----------------------------------------
	内容：タイマーの分計算
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：時間の分
=========================================== */
int CTimer::GetMinite()
{
	int	minute = m_nTimeCnt / 3600;			//分 = 総タイム割る（60秒 * 60フレーム）
	return minute;
}
/* ========================================
	タイマー取得関数
	----------------------------------------
	内容：タイマーの秒数計算
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：時間の秒
=========================================== */
int CTimer::GetSecond()
{
	int second = (m_nTimeCnt / 60) % 60;	//秒 = 分の部分を抜くの残り
	return second;
}



/* ========================================
	タイマー開始関数
	----------------------------------------
	内容：タイマーを開始する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::TimeStart()
{
	m_nTimeCnt = STAGE_TIME;	// デフォルトの制限時間をセット
	m_bStartFlg = true;			// 待ち時間なし
}
/* ========================================
	タイマー開始関数
	----------------------------------------
	内容：タイマーを開始する
	----------------------------------------
	引数1：制限時間(秒)
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::TimeStart(float maxTime)
{
	m_nTimeCnt = int(maxTime * 60);	// 制限時間をセット
	m_bStartFlg = true;			// 待ち時間なし
}
/* ========================================
	タイマー開始関数
	----------------------------------------
	内容：タイマーを開始する
	----------------------------------------
	引数1：制限時間(秒)
	引数2：開始待機時間(秒)
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::TimeStart(float maxTime, float waitTime)
{
	m_dWaitCnt = int(waitTime * 60);	// 待ち時間
	m_nTimeCnt = int(maxTime * 60);	// 制限時間
	m_bStartFlg = false;		// 待ち時間あり
}
/* ========================================
	タイマー停止関数
	----------------------------------------
	内容：タイマーをストップする
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::TimeStop()
{
	m_bStopFlg = true;
}
/* ========================================
	タイマー再開関数
	----------------------------------------
	内容：ストップしたタイマーを再び動かす
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::TimeRestart()
{
	m_bStopFlg = false;
}
/* ========================================
	タイマー数字部分描画関数
	----------------------------------------
	内容：タイマーの描画部分描画する
	----------------------------------------
	引数1：位置
	引数2：描画する数字
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::DrawNumber(TPos2d<float> pos, int number)
{
	DirectX::XMFLOAT4X4 time[3];
	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&time[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&time[2], DirectX::XMMatrixTranspose(proj));

	//スプライトの設定
	Sprite::SetWorld(time[0]);
	Sprite::SetView(time[1]);
	Sprite::SetProjection(time[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));

	//spriteシートの上部分表示（0~4）
	if ((number % 10) < 5)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * number, 0.0f));
	}
	//spriteシートの下部分表示（5~9）
	else
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * number, 0.5f));
	}
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pTextureNum);
	Sprite::Draw();
}

/* ========================================
	タイマー待機時間チェック関数
	----------------------------------------
	内容：設定した待機時間が経過しているか確認する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::WaitTimeCheck()
{
	m_dWaitCnt--;	// 待ち時間を減算
	// 0になったらタイムカウント開始
	if (m_dWaitCnt <= 0)
	{
		m_bStartFlg = true;
	}

}


/* ========================================
	スライムパラメータ変更関数
	----------------------------------------
	内容：経過時間によってスライムのパラメータを変更する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTimer::ChangeSlimeParam()
{
	int elapsedTimeFrame = STAGE_TIME - m_nTimeCnt;

	// 第一段階
	if (elapsedTimeFrame < SLM_PARAM_CHANGE_TIME[STATE_FIRST] * 60)
	{
		m_nMaxSlimeNum			= SLM_CREATE_NUM[STATE_FIRST];
		m_nSlimeCreateInterval	= static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_FIRST] * 60);
		m_fSlimeMoveSpeed		= SLM_MOVE_ADD_SPEED[STATE_FIRST];

	}
	// 第二段階
	else if (elapsedTimeFrame < SLM_PARAM_CHANGE_TIME[STATE_SECOND] * 60)
	{
		m_nMaxSlimeNum			= SLM_CREATE_NUM[STATE_SECOND];
		m_nSlimeCreateInterval	= static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_SECOND] * 60);
		m_fSlimeMoveSpeed = SLM_MOVE_ADD_SPEED[STATE_SECOND];


	}
	// 第三段階
	else
	{
		m_nMaxSlimeNum			= SLM_CREATE_NUM[STATE_THIRD];
		m_nSlimeCreateInterval	= static_cast<int>(SLM_CREATE_INTERVAL_TIME[STATE_THIRD] * 60);
		m_fSlimeMoveSpeed		= SLM_MOVE_ADD_SPEED[STATE_THIRD];


	}
}


/* ========================================
   制限時間取得関数
   ----------------------------------------
   内容：制限時間のポインタを取得
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：制限時間のメンバ変数のポインタ
======================================== */
int * CTimer::GetTimePtr()
{
	return &m_nTimeCnt;
}

/* ========================================
	経過時間取得関数
	----------------------------------------
	内容：現在のタイマーの経過時間を取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：int　経過時間
=========================================== */
int CTimer::GetElapsedFrame()
{
	return STAGE_TIME - m_nTimeCnt;
}

/* ========================================
	スライム変更最大生成数取得関数
	----------------------------------------
	内容：スライム最大生成数取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：int スライム最大生成数
=========================================== */
int CTimer::GetMaxSlimeNum()
{
	
	return m_nMaxSlimeNum;
}

/* ========================================
	スライム変更生成間隔取得関数
	----------------------------------------
	内容：スライムの生成間隔を取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：int 生成間隔の秒数
=========================================== */
int CTimer::GetSlimeCreateInterval()
{
	return m_nSlimeCreateInterval;
}

/* ========================================
	スライム変更スピード取得関数
	----------------------------------------
	内容：スライムのスピードを取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：float スライムのスピード
=========================================== */
float CTimer::GetSlimeMoveSpeed()
{
	return m_fSlimeMoveSpeed;
}
