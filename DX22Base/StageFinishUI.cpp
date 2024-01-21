/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	StageFinishUI用ソース
	------------------------------------
	StageFinishUI.cpp
	------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/20 cpp作成 yamashita
	・2023/11/20 ゲームのプレイ状態によってUIを表示する yamashita
	・2023/11/20 UIが邪魔な時に非表示にできるように変更 yamashita
	・2023/11/23 表示フラグ取得関数作成 nieda
	・2023/11/30 素材変更 nieda
	・2023/12/07 自動でシーン遷移させるためのフラグ取得関数追加 nieda
	・2023/12/16 アニメーション描画書き変え nieda
	・2024/01/21 コメント改修 takagi

========================================== */
#include "DirectXTex/TextureLoad.h"		
#include "StageFinishUI.h"
#include "DirectWrite.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：プレイヤーのHPのポインタ
	引数1：制限時間のポインタ
	----------------------------------------
	戻値：なし
=========================================== */
CStageFinish::CStageFinish(CCamera* pCamera, int* pPlayerHp, int* pTimeCnt)
	: m_eGameState(GAME_PLAY)
	, m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	, m_bGameEnd(false)
{
	m_pPlayerHp = pPlayerHp;	//プレイヤーのHPのポインタを取得
	m_pTimeCnt = pTimeCnt;		//制限時間のポインタを取得

	m_pClear = new CClearText(pCamera);
	m_pOver = new COverText(pCamera);
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：削除時の処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CStageFinish::~CStageFinish()
{
	SAFE_DELETE(m_pOver);
	SAFE_DELETE(m_pClear);
}

/* ========================================
	更新関数
	----------------------------------------
	内容：毎フレーム行う更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStageFinish::Update()
{
	//ゲームクリアかゲームオーバーを判断
	//※ゲーム終了後にクリアとゲームオーバーが勝手に切り替わらないように「&&」で「GAME_PLAY」状態だったらを入れた
	if (0 >= *m_pPlayerHp && m_eGameState == GAME_PLAY)
	{	//タイマーが0になったらクリア状態に遷移
		m_eGameState = GAME_OVER;
	}
	else if (0 >= *m_pTimeCnt && m_eGameState == GAME_PLAY)
	{	//体力が0になったらゲームオーバー状態に遷移
		m_eGameState = GAME_CLEAR;
	}

	// ゲームオーバー
	if (m_eGameState == GAME_OVER)
	{
		m_pOver->Update();
		// アニメーションが終了したら
		if (!m_pOver->GetAnimFlg())
		{
			m_bGameEnd = true;
		}
	}
	// ゲームクリア
	else if (m_eGameState == GAME_CLEAR)
	{
		m_pClear->Update();
		// アニメーションが終了したら
		if (!m_pClear->GetAnimFlg())
		{
			m_bGameEnd = true;
		}
	}
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStageFinish::Draw()
{
	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, nullptr);	//DSVがnullだと2D表示になる

	switch (m_eGameState)	//ゲームの状態によって分岐
	{
	case (GAME_PLAY):	//ゲームをプレイ中の描画
		break;
	case (GAME_CLEAR):	//ゲームクリアの描画
		m_pClear->Draw();
		break;
	case (GAME_OVER):	//ゲームオーバーの描画
		m_pOver->Draw();
		break;
	}
}

/* ========================================
	画面遷移フラグ取得関数
	----------------------------------------
	内容：画面遷移フラグの取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：true:シーン遷移する / false:シーン遷移しない
=========================================== */
bool CStageFinish::GetGameEndFlg()
{
	return m_bGameEnd;
}

/* ========================================
	ゲームクリアフラグ取得関数
	----------------------------------------
	内容：ゲームクリアフラグの取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：true:ゲームクリア / false:ゲームクリアしていない
=========================================== */
bool CStageFinish::GetClearFlg()
{
	// ゲーム状態がゲームクリアになっているか
	if (m_eGameState == CStageFinish::GAME_CLEAR)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
