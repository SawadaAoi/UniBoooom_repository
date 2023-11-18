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

========================================== */

// =============== インクルード ===================
#include "Timer.h"
#include "Sprite.h"

// =============== 定数定義 =======================



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
	: m_nTimeCnt(0)
	, m_bStartFlg(false)
	, m_dWaitCnt(0)
	, m_bStopFlg(false)
	, m_pTimeBackground(nullptr)
	, m_pShowColon(nullptr)
	, m_pShowTimer(nullptr)
{
	//数字のテクスチャ読む込み
	
	m_pShowTimer = new Texture();
	
	if (FAILED(m_pShowTimer->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "数字読む込み", "Error", MB_OK);
	}
	

	//タイマーの裏テクスチャ読み込む
	m_pTimeBackground = new Texture;
	if (FAILED(m_pTimeBackground->Create("Assets/Texture/time_background.png")))
	{
		MessageBox(NULL, "BG読む込み", "Error", MB_OK);
	}
	
	m_pShowColon = new Texture;
	if (FAILED(m_pShowColon->Create("Assets/Texture/colon.png")))
	{
		MessageBox(NULL, "colon読む込み", "Error", MB_OK);
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
	
	SAFE_DELETE(m_pShowTimer);
	
	SAFE_DELETE(m_pTimeBackground);
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
	//---時間UIの描画---
	//時間の裏部分(仮素材)
	DirectX::XMFLOAT4X4 timebackground[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldTimerBG = DirectX::XMMatrixTranslation(TIME_BACKGROUND_X, TIME_BACKGROUND_Y, TIME_BACKGROUND_Z);
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
	Sprite::SetTexture(m_pTimeBackground);
	Sprite::Draw();

	//コロンの描画
	DirectX::XMFLOAT4X4 colon[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldColon = DirectX::XMMatrixTranslation(TIME_COLON_X, TIME_COLON_Y, TIME_COLON_Z);
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
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pShowColon);
	Sprite::Draw();
	//分の秒画
	DirectX::XMFLOAT4X4 minute[3];
	
	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldMinute = DirectX::XMMatrixTranslation(MINUTEPOS_X, MINUTEPOS_Y, MINUTEPOS_Z);
	DirectX::XMStoreFloat4x4(&minute[0], DirectX::XMMatrixTranspose(worldMinute));
	
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&minute[1], DirectX::XMMatrixIdentity());
	
	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projMinute = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&minute[2], DirectX::XMMatrixTranspose(projMinute));
	
	//スプライトの設定
	Sprite::SetWorld(minute[0]);
	Sprite::SetView(minute[1]);
	Sprite::SetProjection(minute[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*GetMinite(), 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pShowTimer);
	Sprite::Draw();

	//十の桁秒の描画
	DirectX::XMFLOAT4X4 secondTen[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldSecondTen = DirectX::XMMatrixTranslation(SECOND_TENS_DIGIT_X, SECOND_TENS_DIGIT_Y, SECOND_TENS_DIGIT_Z);
	DirectX::XMStoreFloat4x4(&secondTen[0], DirectX::XMMatrixTranspose(worldSecondTen));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&secondTen[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projSecondTen = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&secondTen[2], DirectX::XMMatrixTranspose(projSecondTen));

	//スプライトの設定
	Sprite::SetWorld(secondTen[0]);
	Sprite::SetView(secondTen[1]);
	Sprite::SetProjection(secondTen[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	if (GetSecond() / 10 == 5)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f*(GetSecond() / 10), 0.5f));
	}
	else
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*(GetSecond() / 10), 0.0f));

	}
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pShowTimer);
	Sprite::Draw();

	//一の桁秒の描画
	DirectX::XMFLOAT4X4 second[3];

	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX worldSecond = DirectX::XMMatrixTranslation(SECOND_UNITS_DIGIT_X, SECOND_UNITS_DIGIT_Y, SECOND_UNITS_DIGIT_Z);
	DirectX::XMStoreFloat4x4(&second[0], DirectX::XMMatrixTranspose(worldSecond));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&second[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projSecond = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&second[2], DirectX::XMMatrixTranspose(projSecond));

	//スプライトの設定
	Sprite::SetWorld(second[0]);
	Sprite::SetView(second[1]);
	Sprite::SetProjection(second[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	if (GetSecond()-(GetSecond()/10*10) >= 5)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*(GetSecond() % 5), 0.5f));
	}
	else
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*(GetSecond() % 5), 0.0f));
	}
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pShowTimer);
	Sprite::Draw();
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
	int second = ( m_nTimeCnt / 60 ) % 60;	//秒 = 分の部分を抜くの残り

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
	m_nTimeCnt = maxTime * 60;	// 制限時間をセット
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
	m_dWaitCnt = waitTime * 60;	// 待ち時間
	m_nTimeCnt = maxTime * 60;	// 制限時間
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
