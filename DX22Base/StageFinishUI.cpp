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

========================================== */

#include "StageFinishUI.h"
#include "DirectWrite.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"

// =============== 定数定義 =======================
const int SCALE_X = 500;	//UIの横幅
const int SCALE_Y = 100;	//UIの縦幅

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
	,m_eGameState(GAME_PLAY)
	,m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	,m_bDeleteDisp(false)
	, m_pTexGameClear(nullptr)
	,m_pTexGameOver(nullptr)
{
	m_pPlayerHp = pPlayerHp;	//プレイヤーのHPのポインタを取得
	m_pTimeCnt = pTimeCnt;		//制限時間のポインタを取得

	//ゲームクリアのテクスチャ読み込む
	m_pTexGameClear = new Texture;
	if (FAILED(m_pTexGameClear->Create("Assets/Texture/StageFinish/GameClear.png")))
	{
		MessageBox(NULL, "GameClear読み込み失敗", "Error", MB_OK);
	}

	//ゲームオーバーのテクスチャ読み込む
	m_pTexGameOver = new Texture;
	if (FAILED(m_pTexGameOver->Create("Assets/Texture/StageFinish/GameOver.png")))
	{
		MessageBox(NULL, "GameOver読み込み失敗", "Error", MB_OK);
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
	if		(0 >= *m_pPlayerHp && m_eGameState == GAME_PLAY)	
	{	//タイマーが0になったらクリア状態に遷移
		m_bDispFlg = true;
		m_eGameState = GAME_OVER;
	}
	else if (0 >= *m_pTimeCnt && m_eGameState == GAME_PLAY)		
	{	//体力が0になったらゲームオーバー状態に遷移
		m_bDispFlg = true;
		m_eGameState = GAME_CLEAR;
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
		std::string txt = "右SHIFTで クリア／ゲームオーバーのUI表示を切り替え";
		DirectWrite::DrawString(txt,DirectX::XMFLOAT2(0.0f,0.0f));
	}
	if (m_bDeleteDisp) { return; }	//邪魔な時にUIを表示せずに終了


	std::string txt;
	switch (m_eGameState)	//ゲームの状態によって分岐
	{
	case (GAME_PLAY):	//ゲームをプレイ中の描画

		break;
	case (GAME_CLEAR):	//ゲームクリアの描画

		//行列変換を行ってからテクスチャをセットして描画
		EditSprite();
		Sprite::SetTexture(m_pTexGameClear);
		Sprite::Draw();
		break;
	case (GAME_OVER):	//ゲームオーバーの描画

		//行列変換を行ってからテクスチャをセットして描画
		EditSprite();
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
	スプライト設定関数
	----------------------------------------
	内容：UIの表示の設定
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStageFinish::EditSprite()
{
	DirectX::XMFLOAT4X4 matrix[3];

	//ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(SCREEN_WIDTH_ / 2, SCREEN_HEIGHT_ / 2, 0.0f);
	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(world));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&matrix[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH_, SCREEN_HEIGHT_, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&matrix[2], DirectX::XMMatrixTranspose(proj));

	//スプライトの設定
	Sprite::SetWorld(matrix[0]);
	Sprite::SetView(matrix[1]);
	Sprite::SetProjection(matrix[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(SCALE_X, -SCALE_Y));

	//変更は無いがSpriteが静的なため他の所での変更を反映されないために戻す
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
}
