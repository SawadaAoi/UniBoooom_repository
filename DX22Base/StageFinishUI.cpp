/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	StageFinishUI用ヘッダ
	------------------------------------
	StageFinishUI.h
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/20 cpp作成 Yamashita
	・2023/11/20 ゲームのプレイ状態によってUIを表示する yamashita
	・2023/11/20 UIが邪魔な時に非表示にできるように変更 yamashita
	・2023/11/23 表示フラグ取得関数作成 nieda
	・2023/11/30 素材変更 nieda
	・2023/12/07 自動でシーン遷移させるためのフラグ取得関数追加 nieda
	・2023/12/16 アニメーション描画書き変え nieda

========================================== */
#include "DirectXTex/TextureLoad.h"		
#include "StageFinishUI.h"
#include "DirectWrite.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"

// =============== 定数定義 =======================
const int CLEAR_SPLIT_NUM_MAX = 45;				// スタートのUIアニメーションの分割数の最大数
const TDiType<int> CLEAR_SPLIT_NUM = { 5, 9 };	// スタートのUIアニメーションの縦横分割数の最大数
const TPos2d<float> CLEAR_POS = { SCREEN_WIDTH_ / 2.0f, SCREEN_HEIGHT_ / 2.0f };		// 描画位置
const TDiType<float> CLEAR_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// 描画サイズ
const int CLEAR_SWITCH_CNT = 1;					// アニメーション切り替え間隔

const int OVER_SPLIT_NUM_MAX = 54;				// スタートのUIアニメーションの分割数の最大数
const TDiType<int> OVER_SPLIT_NUM = { 6, 9 };	// スタートのUIアニメーションの縦横分割数の最大数
const TPos2d<float> OVER_POS = { SCREEN_WIDTH_ / 2.0f, SCREEN_HEIGHT_ / 2.0f };		// 描画位置
const TDiType<float> OVER_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// 描画サイズ
const int OVER_SWITCH_CNT = 1;					// アニメーション切り替え間隔


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
	: m_bDispFlg(false)
	, m_eGameState(GAME_PLAY)
	, m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	, m_bDeleteDisp(false)
{
	m_pPlayerHp = pPlayerHp;	//プレイヤーのHPのポインタを取得
	m_pTimeCnt = pTimeCnt;		//制限時間のポインタを取得

	//ゲームクリアの描画準備
	m_pClear = new CDrawAnim("Assets/Texture/StageFinish/finish.png",
		pCamera,
		CLEAR_SPLIT_NUM_MAX,
		CLEAR_POS,
		CLEAR_SCALE,
		CLEAR_SPLIT_NUM,
		CLEAR_SWITCH_CNT);

	//ゲームオーバーの描画準備
	m_pOver = new CDrawAnim("Assets/Texture/StageFinish/GameOver.png",
		pCamera,
		OVER_SPLIT_NUM_MAX,
		OVER_POS,
		OVER_SCALE,
		OVER_SPLIT_NUM,
		OVER_SWITCH_CNT);
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
		m_bDispFlg = true;
		m_eGameState = GAME_OVER;
	}
	else if (0 >= *m_pTimeCnt && m_eGameState == GAME_PLAY)
	{	//体力が0になったらゲームオーバー状態に遷移
		m_bDispFlg = true;
		m_eGameState = GAME_CLEAR;
	}

	if (m_eGameState == GAME_OVER)
	{
		m_pOver->Update();
	}
	else if (m_eGameState == GAME_CLEAR)
	{
		m_pClear->Update();
	}

	//表示が邪魔な時に消せるようにする	<=TODO　最後には消去する
	if (IsKeyTrigger(VK_RSHIFT))
	{
		m_bDeleteDisp ^= true;
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
	//UI表示時に案内を表示
	if (m_eGameState != GAME_PLAY)
	{
		std::string txt = "右SHIFTで クリア／ゲームオーバーのUI表示を切り替え";	// TODO	謎のエラーが発生したためコメント内容を変更
		DirectWrite::DrawString(txt, DirectX::XMFLOAT2(0.0f, 0.0f));
	}
	if (m_bDeleteDisp) { return; }	//邪魔な時にUIを表示せずに終了

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, nullptr);	//DSVがnullだと2D表示になる

	std::string txt;
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
	表示フラグ取得関数
	----------------------------------------
	内容：UIの表示フラグの取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：true:表示する / false:表示しない
=========================================== */
bool CStageFinish::GetDispFlg()
{
	return m_bDispFlg;
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
bool CStageFinish::GetDeleteDispFlg()
{
	return m_bDeleteDisp;
}
