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

========================================== */
#include "DirectXTex/TextureLoad.h"		
#include "StageFinishUI.h"
#include "DirectWrite.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"

// =============== 定数定義 =======================
const int GAMECLEAR_UV_NUM_X = 5;	// テクスチャの横の分割数
const int GAMECLEAR_UV_NUM_Y = 9;	// テクスチャの縦の分割数
const int GAMEOVER_UV_NUM_X = 6;	// テクスチャの横の分割数
const int GAMEOVER_UV_NUM_Y = 9;	// テクスチャの縦の分割数

const float GAMECLEAR_UV_POS_X = 1.0f / GAMECLEAR_UV_NUM_X;		// 横のUV座標計算用
const float GAMECLEAR_UV_POS_Y = 1.0f / GAMECLEAR_UV_NUM_Y;		// 縦のUV座標計算用
const float GAMEOVER_UV_POS_X = 1.0f / GAMEOVER_UV_NUM_X;		// 横のUV座標計算用
const float GAMEOVER_UV_POS_Y = 1.0f / GAMEOVER_UV_NUM_Y;		// 縦のUV座標計算用


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
CStageFinish::CStageFinish(int* pPlayerHp, int* pTimeCnt)
	:m_bDispFlg(false)
	, m_eGameState(GAME_PLAY)
	, m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	, m_bDeleteDisp(false)
	, m_pTexGameClear(nullptr)
	, m_pTexGameOver(nullptr)
	, m_fUVPos(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntW(0)
	, m_nCntH(0)
	, m_bTransition(false)
{
	m_pPlayerHp = pPlayerHp;	//プレイヤーのHPのポインタを取得
	m_pTimeCnt = pTimeCnt;		//制限時間のポインタを取得

	//ゲームクリアのテクスチャ読み込む
	m_pTexGameClear = new Texture;

	if (FAILED(m_pTexGameClear->Create("Assets/Texture/StageFinish/finish.png")))
	{
		MessageBox(NULL, "GameClear.png", "Error", MB_OK);
	}

	//ゲームオーバーのテクスチャ読み込む
	m_pTexGameOver = new Texture;
	if (FAILED(m_pTexGameOver->Create("Assets/Texture/StageFinish/GameOver.png")))
	{
		MessageBox(NULL, "game_over.png", "Error", MB_OK);
	}
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
	SAFE_DELETE(m_pTexGameOver);
	SAFE_DELETE(m_pTexGameClear);
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
		// タイトルから遷移後すぐゲーム開始にならないようにする処理
		if (!m_bDeleteDisp) { m_nCntSwitch++; }

		if (m_nCntSwitch > SWITCH_ANIM_OVER)
		{
			m_nCntSwitch = 0;		// カウントを初期化

			m_fUVPos.x = (GAMEOVER_UV_POS_X)* m_nCntW;		// 横方向のUV座標計算
			m_fUVPos.y = (GAMEOVER_UV_POS_Y)* m_nCntH;		// 縦方向のUV座標計算

			++m_nCntW;		// 横方向に座標を1つ進める
			if (m_nCntW == GAMEOVER_UV_NUM_X)	// テクスチャの右端まで行ったら 
			{
				m_nCntW = 0;	// カウントを初期化
				++m_nCntH;		// 縦に1進める
			}

			if (m_nCntH == GAMEOVER_UV_NUM_Y)		// テクスチャの下端まで行ったら
			{
				m_nCntH = 0;	// カウントを初期化
				m_nCntW = 0;
				m_bDeleteDisp = true;
				m_bTransition = true;
			}
		}
	}
	else if (m_eGameState == GAME_CLEAR)
	{
		// タイトルから遷移後すぐゲーム開始にならないようにする処理
		if (!m_bDeleteDisp) { m_nCntSwitch++; }

		if (m_nCntSwitch > SWITCH_ANIM_CLEAR)
		{
			m_nCntSwitch = 0;		// カウントを初期化

			m_fUVPos.x = (GAMECLEAR_UV_POS_X)* m_nCntW;		// 横方向のUV座標計算
			m_fUVPos.y = (GAMECLEAR_UV_POS_Y)* m_nCntH;		// 縦方向のUV座標計算

			++m_nCntW;		// 横方向に座標を1つ進める
			if (m_nCntW == GAMECLEAR_UV_NUM_X)	// テクスチャの右端まで行ったら 
			{
				m_nCntW = 0;	// カウントを初期化
				++m_nCntH;		// 縦に1進める
			}

			if (m_nCntH == GAMECLEAR_UV_NUM_Y)		// テクスチャの下端まで行ったら
			{
				m_nCntH = 0;	// カウントを初期化
				m_nCntW = 0;
				m_bDeleteDisp = true;
				m_bTransition = true;
			}
		}
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

		//行列変換を行ってからテクスチャをセットして描画
		EditSprite(GAME_CLEAR);
		Sprite::SetTexture(m_pTexGameClear);
		Sprite::Draw();
		break;
	case (GAME_OVER):	//ゲームオーバーの描画

		//行列変換を行ってからテクスチャをセットして描画
		EditSprite(GAME_OVER);
		Sprite::SetTexture(m_pTexGameOver);
		Sprite::Draw();
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
	戻値：なし
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
	戻値：なし
=========================================== */
bool CStageFinish::GetTransitionFlg()
{
	return m_bTransition;
}

/* ========================================
	スプライト設定関数
	----------------------------------------
	内容：UIの表示の設定
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStageFinish::EditSprite(int nState)
{
	DirectX::XMFLOAT4X4 matrix[3];

	//ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(STATE_POS_X, STATE_POS_Y, 0.0f);
	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(world));

	Sprite::SetSize(DirectX::XMFLOAT2(STATE_SCALE_X, -STATE_SCALE_Y));
	if (nState == GAME_OVER)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVPos.x, m_fUVPos.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(GAMEOVER_UV_POS_X, GAMEOVER_UV_POS_Y));
	}
	else if (nState == GAME_CLEAR)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVPos.x, m_fUVPos.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(GAMECLEAR_UV_POS_X, GAMECLEAR_UV_POS_Y));
	}
}
