/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	リザルトシーン実装
	---------------------------------------
	Result.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/11/20 仮テクスチャ表示、画面遷移 nieda
	・2023/11/23 コントローラーに対応 nieda
	・2023/11/24 コメント、定数定義、列挙追加 nieda
	・2023/12/08 シーン遷移用に変数追加 takagi
	・2023/12/11 成績仮表示 takagi
	・2023/12/25 表示内容の変更 Sawada
	・2024/01/26 決定SE追加 suzumura
	・2024/01/26 アニメーション追加 goto
	・2024/02/01 遷移先変更 sawada
	・2024/02/03 リザルト表示位置等微調整 suzumura
	・2024/02/09 GetType()関数削除 takagi

========================================== */

// =============== インクルード ===================
#include "Result.h"	//自身のヘッダ
#include "DirectXTex/TextureLoad.h"	
#include "FixedCamera.h"	//インスタンス候補
#include "Pos3d.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"
#include <array>					//配列
#include <map>						//連想型コンテナ
#include "Defines.h"				//画面サイズ情報

// =============== 定数定義 ===================
const std::map<int, std::string> MAP_TEX_PATH = {
	{CResult::BG_SCREEN_CLEAR,		"Assets/Texture/Result/ResultBG.png"},			// 画面全体の背景
	{CResult::BG_SCREEN_GAMEOVER,	"Assets/Texture/Result/ResultBG_blue.png"},		// 画面全体の背景
	{CResult::BG_PANEL_CLEAR,		"Assets/Texture/Result/result_waku.png"},		// 各項目の背景(黒い背景)
	{CResult::BG_PANEL_GAMEOVER,	"Assets/Texture/Result/result_waku_blue.png"},	// 各項目の背景(黒い背景)
	{CResult::RESULT_TEXT,		"Assets/Texture/Result/result.png"},			// 文字(Result)
	{CResult::SVL_TIME_TEXT,	"Assets/Texture/Result/SurvivalTime.png"},		// 文字(生存時間)
	{CResult::SCORE_TEXT,		"Assets/Texture/Result/SCORE.png"},				// 文字(SCORE)	
	{CResult::HIGH_SCORE_TEXT,	"Assets/Texture/Result/HISCORE.png"},			// 文字(HISCORE)
	{CResult::NEW_RECORD_TEXT,	"Assets/Texture/Result/NewRecord.png"},			// 文字(NEW RECORD)
	{CResult::TOTAL_HUNT_TEXT,	"Assets/Texture/Result/TotalHunt.png"},			// 文字(スライム討伐数)
	{CResult::HUNT_TEXT,		"Assets/Texture/Result/slimeCnt.png"},			// 文字(総討伐数)
	{CResult::SLIME_BLUE,		"Assets/Texture/Result/Slime_Blue.png"},		// スライム画像(青)
	{CResult::SLIME_GREEN,		"Assets/Texture/Result/Slime_Green.png"},		// スライム画像(緑)
	{CResult::SLIME_YELLOW,		"Assets/Texture/Result/Slime_Yellow.png"},		// スライム画像(黄)
	{CResult::SLIME_RED,		"Assets/Texture/Result/Slime_Red.png"},			// スライム画像(赤)
	{CResult::SLIME_BOSS,		"Assets/Texture/Result/Slime_Boss.png"},		// スライム画像(ボス)
	{CResult::MAX_COMBO_TEXT,	"Assets/Texture/Result/MaxCombo.png"},			// 文字(最大コンボ数)
	{CResult::NUM,				"Assets/Texture/Result/ResultSpliteSheet.png"},	// 数字
	{CResult::COLON,			"Assets/Texture/Result/Colon.png"},				// コロン
	{CResult::LINE,				"Assets/Texture/Result/Line.png"},				// 線
	{CResult::MULTI,			"Assets/Texture/Result/kakeru.png"},			// ×
	{CResult::PARENTHESIS,		"Assets/Texture/Result/parenthesis.png"},		// ()
	{CResult::WARNING_STAGE_1,	"Assets/Texture/Result/Lv1.png"},				// ステージ1の手配書
	{CResult::WARNING_STAGE_2,	"Assets/Texture/Result/Lv2.png"},				// ステージ2の手配書
	{CResult::WARNING_STAGE_3,	"Assets/Texture/Result/Lv3.png"},				// ステージ3の手配書
	{CResult::CLEAR_STAMP,		"Assets/Texture/Result/stamp.png"},				// CLEARスタンプ
	{CResult::SELECT,			"Assets/Texture/Result/Result_Button.png"},		// 決定ボタン
};	

const std::map<CResult::E_2D_OBJ_ID, TTriType<float>> MAP_TEX_POS = {
	{CResult::OBJ_BG_SCREEN,			{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , 1.0f} },	// 背景
	{CResult::OBJ_BG_PANEL,				{ 905.0f, SCREEN_HEIGHT / 2, 1.0f } },				// 項目背景
	{CResult::OBJ_WARNING_STAGE,		{ 260.0f, 340.0f, 1.0f } },							// 手配書画像
	{CResult::OBJ_CLEAR_STAMP,			{ 260.0f, 340.0f, 1.0f } },							// スタンプ画像
	{CResult::OBJ_RESULT_TEXT,			{ 275.0f, 660.0f, 1.0f } },							// リザルト(文字)
	{CResult::OBJ_SVL_TIME_TEXT,		{ 650.0f, 690.0f, 1.0f } },							// 生存時間(文字)
	{CResult::OBJ_SVL_TIME_SECOND_NUM,	{ 1200.0f,670.0f, 1.0f } },							// 生存時間(秒)
	{CResult::OBJ_SVL_TIME_COLON,		{ 1083.0f,670.0f, 1.0f } },							// 生存時間(コロン)	
	{CResult::OBJ_SVL_TIME_MINUTE_NUM,	{ 1035.0f,670.0f, 1.0f } },							// 生存時間(分)		
	{CResult::OBJ_SVL_TIME_LINE,		{ 907.0f, 620.0f, 1.0f } },							// 区切り線
	{CResult::OBJ_SCORE_TEXT,			{ 655.0f, 590.0f, 1.0f } },							// スコア(文字)
	{CResult::OBJ_NEW_RECORD_TEXT,		{ 800.0f, 540.0f, 1.0f } },							// 新記録(文字)
	{CResult::OBJ_SCORE_NUM,			{ 1200.0f,560.0f, 1.0f } },							// スコア(数字)
	{CResult::OBJ_HIGH_SCORE_TEXT,		{ 645.0f, 480.0f, 1.0f } },							// ハイスコア(文字)
	{CResult::OBJ_HIGH_SCORE_NUM,		{ 1200.0f,460.0f, 1.0f } },							// ハイスコア(数字)
	{CResult::OBJ_SCORE_LINE,			{ 907.0f, 420.0f, 1.0f } },							// 区切り線
	{CResult::OBJ_HUNT_TEXT,			{ 710.0f, 380.0f, 1.0f } },							// 討伐数(文字)
	{CResult::OBJ_SLIME_HUNT_BG,		{ 650.0f, 290.0f, 1.0f } },							// 討伐数背景スライム画像
	{CResult::OBJ_SLIME_HUNT_NUM,		{ 650.0f, 290.0f, 1.0f } },							// スライム別討伐数
	{CResult::OBJ_PARENTHESIS,			{ 600.0f, 210.0f, 1.0f } },							// ()
	{CResult::OBJ_MULTI,				{ 650.0f, 210.0f, 1.0f } },							// ×
	{CResult::OBJ_MULTI_BLUE_SLIME,		{ 615.0f, 210.0f, 1.0f } },							// 青スライム画像の位置
	{CResult::OBJ_MULTI_NUM,			{ 685.0f, 210.0f, 1.0f } },							// 青スライムの倍数
	{CResult::OBJ_TOTAL_HUNT_TEXT,		{ 670.0f, 160.0f, 1.0f } },							// 総討伐数(文字)
	{CResult::OBJ_TOTAL_HUNT_NUM,		{ 1200.0f,140.0f, 1.0f } },							// 総討伐数(数字)
	{CResult::OBJ_HUNT_LINE,			{ 907.0f, 100.0f, 1.0f } },							// 区切り線
	{CResult::OBJ_MAX_COMBO_TEXT,		{ 695.0f,  65.0f, 1.0f } },							// 最大コンボ数(文字)
	{CResult::OBJ_MAX_COMBO_NUM,		{ 1200.0f, 50.0f, 1.0f } },							// 最大コンボ数(数字)
	{CResult::OBJ_SELECT_BUTTON,		{ 65.0f,   40.0f, 1.0f } },							// 決定 
};

const std::map<CResult::E_2D_OBJ_ID, TTriType<float>> MAP_TEX_SIZE = {
	{CResult::OBJ_BG_SCREEN,			{ SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f} },	// 背景
	{CResult::OBJ_BG_PANEL,				{ 750.0f, SCREEN_HEIGHT, 1.0f } },		// 項目背景
	{CResult::OBJ_WARNING_STAGE,		{ 460.0f, 580.0f, 1.0f } },				// 手配書画像
	{CResult::OBJ_CLEAR_STAMP,			{ 460.0f, 580.0f, 1.0f } },				// スタンプ画像
	{CResult::OBJ_RESULT_TEXT,			{ 640.0f, 280.0f, 1.0f } },				// リザルト(文字)
	{CResult::OBJ_SVL_TIME_TEXT,		{ 200.0f, 80.0f,  1.0f } },				// 生存時間(文字)
	{CResult::OBJ_SVL_TIME_SECOND_NUM,	{ 85.0f,  95.0f , 1.0f } },				// 生存時間(秒数)
	{CResult::OBJ_SVL_TIME_COLON,		{ 85.0f,  95.0f,  1.0f } },				// 生存時間(コロン)	
	{CResult::OBJ_SVL_TIME_MINUTE_NUM,	{ 85.0f,  95.0f,  1.0f } },				// 生存時間(分)		
	{CResult::OBJ_SVL_TIME_LINE,		{ 729.0f, 5.0f ,  1.0f } },				// 区切り線
	{CResult::OBJ_SCORE_TEXT,			{ 220.0f, 75.0f,  1.0f } },				// スコア(文字)
	{CResult::OBJ_NEW_RECORD_TEXT,		{ 170.0f, 55.0f,  1.0f } },				// 新記録(文字)
	{CResult::OBJ_SCORE_NUM,			{ 85.0f, 105.0f,  1.0f } },				// スコア(数字)
	{CResult::OBJ_HIGH_SCORE_TEXT,		{ 180.0f, 75.0f,  1.0f } },				// ハイスコア(文字)
	{CResult::OBJ_HIGH_SCORE_NUM,		{ 55.0f, 55.0f,   1.0f } },				// ハイスコア(数字)
	{CResult::OBJ_SCORE_LINE,			{ 729.0f, 5.0f,   1.0f } },				// 区切り線
	{CResult::OBJ_HUNT_TEXT,			{ 330.0f, 110.0f, 1.0f } },				// 討伐数(文字)
	{CResult::OBJ_SLIME_HUNT_BG,		{ 160.0f, 160.0f, 1.0f } },				// 討伐数背景スライム画像
	{CResult::OBJ_SLIME_HUNT_NUM,		{ 60.0f, 60.0f,   1.0f } },				// スライム別討伐数
	{CResult::OBJ_PARENTHESIS,			{ 40.0f, 40.0f,   1.0f } },				// ()
	{CResult::OBJ_MULTI,				{ 40.0f, 40.0f,   1.0f } },				// ×
	{CResult::OBJ_MULTI_BLUE_SLIME,		{ 30.0f, 30.0f,   1.0f } },				// 青スライム画像の位置
	{CResult::OBJ_MULTI_NUM,			{ 40.0f, 40.0f,   1.0f } },				// 青スライムの倍数
	{CResult::OBJ_TOTAL_HUNT_TEXT,		{ 250.0f, 80.0f,  1.0f } },				// 総討伐数(文字)
	{CResult::OBJ_TOTAL_HUNT_NUM,		{ 85.0f, 105.0f,  1.0f } },				// 総討伐数(数字)
	{CResult::OBJ_HUNT_LINE,			{ 729.0f, 5.0f,   1.0f } },				// 区切り線
	{CResult::OBJ_MAX_COMBO_TEXT,		{ 300.0f, 90.0f,  1.0f } },				// 最大コンボ数(文字)
	{CResult::OBJ_MAX_COMBO_NUM,		{ 85.0f, 105.0f,  1.0f } },				// 最大コンボ数(数字)
	{CResult::OBJ_SELECT_BUTTON,		{ 130.0f, 65.0f,  1.0f } },				// 決定 
};

const int	RESULT_TEXT_FLASH = 0.04 * 60;

const TDiType<int>		NUM_SPLIT = { 5, 2 };			// 数字画像分割値
const TDiType<float>	NUM_UVSCALE = {					// 数字画像UV値
						(1.0f / NUM_SPLIT.x) ,(1.0f / NUM_SPLIT.y) };

const TDiType<float>		PARENTHESIS_SPLIT = { 2, 1 };	// カッコ画像分割値
const TDiType<float>	PARENTHESIS_UVSCALE = {			// カッコ画像UV値
						(1.0f / PARENTHESIS_SPLIT.x) ,(1.0f / PARENTHESIS_SPLIT.y) };

const float DEF_NUM_SPACE			= 68.0f;			// 数時間の距離(デフォルト)
const float SVL_TIME_NUM_SPACE		= 55.0f;			// 時間の間(例 12□:□33)
const float SCORE_NUM_SPACE			= 70.0f;			// 数字間の距離(スコア)
const float HIGH_SCORE_NUM_SPACE	= 45.0f;			// 数字間の距離(ハイスコア)
const float HUNT_NUM_SPACE			= 45.0f;			// 数字間の距離(討伐数)

const float SLIME_SPACE_Y = 130.0f;						// スライム画像の間
const float FLASH_BUTTON_TEXT_ADJUST		= 0.02f;	//「決定」テキストの点滅間隔調整
const float FLASH_NEW_RECORD_TEXT_ADJUST	= 0.04f;	//「ハイスコア」テキストの点滅間隔調整

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CResult::CResult()
	: m_pSE{ nullptr }
	, m_pSESpeaker{ nullptr }
	, m_nButtonAlphaCnt(0)
	, m_nNewRecoAlphaCnt(0)
	, m_nStAnimCnt(0)
	, m_nStartAnimEnd(false)

{
	for (int i = 0; i < E_TEXTURE::TEXTURE_MAX; i++)
	{
		// リザルト画像読込
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(MAP_TEX_PATH.at(i).c_str())))
		{
			MessageBox(NULL, "Result Texture", "Error", MB_OK);
		}
	}

	for (int i = 0; i < E_2D_OBJ_ID::OBJ_2D_MAX; i++)
	{
		m_p2dObj[i] = new C2dPolygon();
		m_p2dObj[i]->SetPos(MAP_TEX_POS.at(static_cast<E_2D_OBJ_ID>(i)));
		m_p2dObj[i]->SetSize(MAP_TEX_SIZE.at(static_cast<E_2D_OBJ_ID>(i)));
	}
	
	// リザルト文字のアニメーションの初期化
	m_pTextureResultText = new CDrawAnim(60, TDiType<int>(5, 12), RESULT_TEXT_FLASH);
	m_pTextureResultText->SetTexture(m_pTexture[E_TEXTURE::RESULT_TEXT]);
	m_pTextureResultText->SetPos(MAP_TEX_POS.at(E_2D_OBJ_ID::OBJ_RESULT_TEXT));
	m_pTextureResultText->SetSize(MAP_TEX_SIZE.at(E_2D_OBJ_ID::OBJ_RESULT_TEXT));
	m_pTextureResultText->SetLoopFlg(true);
	
	// データ受け継ぎ
	m_Data.Load();	//ファイルに上がっている情報を読み込む

	//=== サウンドファイル読み込み =====
	LoadSound();

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
CResult::~CResult()
{
	// =============== セーブ =====================
	m_Data.Save();	//ステージのデータセーブ

	// 破棄処理
	for (int i = 0; i < E_TEXTURE::TEXTURE_MAX; i++)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
	SAFE_DELETE(m_pTextureResultText);
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
void CResult::Update()
{
	// スペースキーを押した時、またはコントローラのBボタンを押した時 
	if (IsKeyTrigger(VK_SPACE) || IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// タイトルシーン終了フラグON
		//===== SEの再生 =======
		PlaySE(SE_DECISION);
	}

	// リザルトの文字のアニメーション
	m_pTextureResultText->Update();

	// 決定ボタン点滅加算値
	m_nButtonAlphaCnt++;
	m_nNewRecoAlphaCnt++;
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CResult::Draw()
{
	
	DrawBgScreen();			// 背景
	DrawWarningTexture();	// Result＆＆手配書
	DrawSurvivalTime();		// 生存時間
	DrawScore();			// スコア
	DrawHunt();				// 討伐数
	DrawMaxCombo();			// コンボ数
}

/* ========================================
	背景描画関数
	----------------------------------------
	内容：背景を描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DrawBgScreen()
{
	// ゲームクリア
	if (m_Data.bClearFlg)
	{
		// 全体の背景
		m_p2dObj[OBJ_BG_SCREEN]->SetTexture(m_pTexture[E_TEXTURE::BG_SCREEN_CLEAR]);
		// 右半分の各項目の背景
		m_p2dObj[OBJ_BG_PANEL]->SetTexture(m_pTexture[E_TEXTURE::BG_PANEL_CLEAR]);
	}
	// ゲームオーバー
	else
	{
		// 全体の背景
		m_p2dObj[OBJ_BG_SCREEN]->SetTexture(m_pTexture[E_TEXTURE::BG_SCREEN_GAMEOVER]);
		// 右半分の各項目の背景
		m_p2dObj[OBJ_BG_PANEL]->SetTexture(m_pTexture[E_TEXTURE::BG_PANEL_GAMEOVER]);
	}

	// 描画
	m_p2dObj[OBJ_BG_SCREEN]->Draw();
	m_p2dObj[OBJ_BG_PANEL]->Draw();

}

/* ========================================
	手配書描画関数
	----------------------------------------
	内容：手配書を描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DrawWarningTexture()
{
	Texture* pWarningTex;	// 手配書画像

	// リザルト文字
	m_pTextureResultText->Draw();

	// プレイしたステージによって手配書の画像を変える
	switch (m_Data.nStageNum)
	{
	case 1: pWarningTex = m_pTexture[E_TEXTURE::WARNING_STAGE_1]; break;
	case 2: pWarningTex = m_pTexture[E_TEXTURE::WARNING_STAGE_2]; break;
	case 3: pWarningTex = m_pTexture[E_TEXTURE::WARNING_STAGE_3]; break;
	}
	

	m_p2dObj[OBJ_WARNING_STAGE]->SetTexture(pWarningTex);
	m_p2dObj[OBJ_WARNING_STAGE]->Draw();

	// クリアした場合
	if (m_Data.bClearFlg)
	{
		// スタンプを表示する
		m_p2dObj[OBJ_CLEAR_STAMP]->SetTexture(m_pTexture[E_TEXTURE::CLEAR_STAMP]);
		m_p2dObj[OBJ_CLEAR_STAMP]->Draw();
	}

	// 決定ボタン
	m_p2dObj[OBJ_SELECT_BUTTON]->SetTexture(m_pTexture[E_TEXTURE::SELECT]);

	m_p2dObj[OBJ_SELECT_BUTTON]->SetAlpha(fabs(cosf(m_nButtonAlphaCnt * FLASH_BUTTON_TEXT_ADJUST)));	// 点滅の為、透明度変更
	m_p2dObj[OBJ_SELECT_BUTTON]->Draw();

}


/* ========================================
	生存時間描画関数
	----------------------------------------
	内容：生存時間を描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DrawSurvivalTime()
{
	// 生存時間(文字)
	m_p2dObj[OBJ_SVL_TIME_TEXT]->SetTexture(m_pTexture[E_TEXTURE::SVL_TIME_TEXT]);
	m_p2dObj[OBJ_SVL_TIME_TEXT]->Draw();

	// 生存時間(数字)
	DispTime();

	// 線
	m_p2dObj[OBJ_SVL_TIME_LINE]->SetTexture(m_pTexture[E_TEXTURE::LINE]);
	m_p2dObj[OBJ_SVL_TIME_LINE]->Draw();
}


/* ========================================
	スコア描画関数
	----------------------------------------
	内容：スコアを描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DrawScore()
{
	// スコア(文字)
	m_p2dObj[OBJ_SCORE_TEXT]->SetTexture(m_pTexture[E_TEXTURE::SCORE_TEXT]);
	m_p2dObj[OBJ_SCORE_TEXT]->Draw();


	// 総スコア(数字)
	DispNum(m_Data.nTotalScore, 5, OBJ_SCORE_NUM, MAP_TEX_POS.at(OBJ_SCORE_NUM), SCORE_NUM_SPACE);

	// ハイスコア(文字)
	m_p2dObj[OBJ_HIGH_SCORE_TEXT]->SetTexture(m_pTexture[E_TEXTURE::HIGH_SCORE_TEXT]);
	m_p2dObj[OBJ_HIGH_SCORE_TEXT]->Draw();

	// ハイスコアを更新していたら(ゲーム終了時にハイスコアを更新する為)
	if (m_Data.nHighScore[m_Data.nStageNum-1] == m_Data.nTotalScore)
	{
		// ニューレコード(文字)
		m_p2dObj[OBJ_NEW_RECORD_TEXT]->SetTexture(m_pTexture[E_TEXTURE::NEW_RECORD_TEXT]);
		m_p2dObj[OBJ_NEW_RECORD_TEXT]->SetAlpha(fabs(cosf(m_nNewRecoAlphaCnt * FLASH_NEW_RECORD_TEXT_ADJUST)));	// 点滅の為、透明度変更

		m_p2dObj[OBJ_NEW_RECORD_TEXT]->Draw();

	}

	// ハイスコア(数字)
	DispNum(m_Data.nHighScore[m_Data.nStageNum - 1], 5, OBJ_HIGH_SCORE_NUM, MAP_TEX_POS.at(OBJ_HIGH_SCORE_NUM), HIGH_SCORE_NUM_SPACE);
	

	// 線
	m_p2dObj[OBJ_SCORE_LINE]->SetTexture(m_pTexture[E_TEXTURE::LINE]);
	m_p2dObj[OBJ_SCORE_LINE]->Draw();
}


/* ========================================
	討伐数描画関数
	----------------------------------------
	内容：討伐数を描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DrawHunt()
{
	// 討伐数(文字)
	m_p2dObj[OBJ_HUNT_TEXT]->SetTexture(m_pTexture[E_TEXTURE::HUNT_TEXT]);
	m_p2dObj[OBJ_HUNT_TEXT]->Draw();

	// ステージ１ならボス討伐数を表示しない
	int nDispHuntNum = 5;	// 青＋緑＋黄＋赤＋ボス＝５
	if (m_Data.nStageNum == 1) nDispHuntNum = 4;	// ーボス＝４

	// スライムの種類数分画像を表示
	for (int i = 0; i < nDispHuntNum; i++)
	{
		// スライムの画像
		m_p2dObj[OBJ_SLIME_HUNT_BG]->SetPos({
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_BG).x + (i * SLIME_SPACE_Y),
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_BG).y,
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_BG).z,
			});
		m_p2dObj[OBJ_SLIME_HUNT_BG]->SetTexture(m_pTexture[E_TEXTURE::SLIME_BLUE + i]);
		m_p2dObj[OBJ_SLIME_HUNT_BG]->Draw();

		
		// スライム緑～赤の下に青の倍数を表示する(i = 1～3)
		if (1 <= i && i <= 3)
		{
			// ()
			for (int j = 0; j < 2; j++)
			{
				m_p2dObj[OBJ_PARENTHESIS]->SetPos({
								MAP_TEX_POS.at(OBJ_PARENTHESIS).x + (i * SLIME_SPACE_Y) + (j * 100),
								MAP_TEX_POS.at(OBJ_PARENTHESIS).y,
								MAP_TEX_POS.at(OBJ_PARENTHESIS).z,
					});
				m_p2dObj[OBJ_PARENTHESIS]->SetUvOffset({ PARENTHESIS_UVSCALE.x * j, PARENTHESIS_UVSCALE.y });
				m_p2dObj[OBJ_PARENTHESIS]->SetUvScale(PARENTHESIS_UVSCALE);
				m_p2dObj[OBJ_PARENTHESIS]->SetTexture(m_pTexture[E_TEXTURE::PARENTHESIS]);
				m_p2dObj[OBJ_PARENTHESIS]->Draw();
			}
			

			// 青スライム画像
			m_p2dObj[OBJ_MULTI_BLUE_SLIME]->SetPos({
				MAP_TEX_POS.at(OBJ_MULTI_BLUE_SLIME).x + (i * SLIME_SPACE_Y),
				MAP_TEX_POS.at(OBJ_MULTI_BLUE_SLIME).y,
				MAP_TEX_POS.at(OBJ_MULTI_BLUE_SLIME).z,
				});
			m_p2dObj[OBJ_MULTI_BLUE_SLIME]->SetTexture(m_pTexture[E_TEXTURE::SLIME_BLUE]);
			m_p2dObj[OBJ_MULTI_BLUE_SLIME]->Draw();

			// ×
			m_p2dObj[OBJ_MULTI]->SetPos({
				MAP_TEX_POS.at(OBJ_MULTI).x + (i * SLIME_SPACE_Y),
				MAP_TEX_POS.at(OBJ_MULTI).y,
				MAP_TEX_POS.at(OBJ_MULTI).z,
				});
			m_p2dObj[OBJ_MULTI]->SetTexture(m_pTexture[E_TEXTURE::MULTI]);
			m_p2dObj[OBJ_MULTI]->Draw();

			// 倍数
			DispNum(pow(2,i), 1, OBJ_MULTI_NUM, {
			MAP_TEX_POS.at(OBJ_MULTI_NUM).x + (i * SLIME_SPACE_Y),
			MAP_TEX_POS.at(OBJ_MULTI_NUM).y,
			MAP_TEX_POS.at(OBJ_MULTI_NUM).z },
			DEF_NUM_SPACE);
		}

		// スライム別討伐数
		std::vector<int> digitArray;
		NumStorage(&digitArray, m_Data.nKill[i], 1);
		DispNum(m_Data.nKill[i], 1, OBJ_SLIME_HUNT_NUM, {
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_NUM).x + (i * SLIME_SPACE_Y) + (20.0f * (digitArray.size() - 1)),
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_NUM).y,
			MAP_TEX_POS.at(OBJ_SLIME_HUNT_NUM).z },
			HUNT_NUM_SPACE);

	}

	// 総討伐数(文字)
	m_p2dObj[OBJ_TOTAL_HUNT_TEXT]->SetTexture(m_pTexture[E_TEXTURE::TOTAL_HUNT_TEXT]);
	m_p2dObj[OBJ_TOTAL_HUNT_TEXT]->Draw();

	// 総討伐数(数字)
	DispNum(m_Data.nTotalKill, 1, OBJ_TOTAL_HUNT_NUM, MAP_TEX_POS.at(OBJ_TOTAL_HUNT_NUM), DEF_NUM_SPACE);

	// 線
	m_p2dObj[OBJ_HUNT_LINE]->SetTexture(m_pTexture[E_TEXTURE::LINE]);
	m_p2dObj[OBJ_HUNT_LINE]->Draw();
}


/* ========================================
	最大コンボ数描画関数
	----------------------------------------
	内容：最大コンボ数を描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DrawMaxCombo()
{
	// 最大コンボ数(文字)
	m_p2dObj[OBJ_MAX_COMBO_TEXT]->SetTexture(m_pTexture[E_TEXTURE::MAX_COMBO_TEXT]);
	m_p2dObj[OBJ_MAX_COMBO_TEXT]->Draw();

	// 最大コンボ数(数字)
	DispNum(m_Data.nMaxCombo, 1, OBJ_MAX_COMBO_NUM, MAP_TEX_POS.at(OBJ_MAX_COMBO_NUM), DEF_NUM_SPACE);
}


/* ========================================
	制限時間描画関数
	----------------------------------------
	内容：制限時間を描画する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DispTime()
{
	// 秒数
	DispNum(m_Data.GetSecond(), 2, OBJ_SVL_TIME_SECOND_NUM, MAP_TEX_POS.at(OBJ_SVL_TIME_SECOND_NUM), DEF_NUM_SPACE);

	// コロン
	m_p2dObj[OBJ_SVL_TIME_COLON]->SetTexture(m_pTexture[E_TEXTURE::COLON]);
	m_p2dObj[OBJ_SVL_TIME_COLON]->Draw();

	// 分数
	DispNum(m_Data.GetMinute(), 2, OBJ_SVL_TIME_MINUTE_NUM, MAP_TEX_POS.at(OBJ_SVL_TIME_MINUTE_NUM), DEF_NUM_SPACE);
}

/* ========================================
	数字描画関数
	----------------------------------------
	内容：数字を描画する
	----------------------------------------
	引数1：描画する数字
	引数2：桁数
	引数3：位置
	引数4：大きさ
	引数5：数字間の大きさ
	----------------------------------------
	戻値：なし
=========================================== */
void CResult::DispNum(int dispNum, int nDigits, E_2D_OBJ_ID objId, TTriType<float> fPos, float NumSpace)
{

	std::vector<int> digitArray;
	int Num = dispNum;

	NumStorage(&digitArray, dispNum, nDigits);

	for (int i = 0; i < digitArray.size(); i++)
	{

		int width = int(NumSpace * i);

		TTriType<float> pos ={ 
			fPos.x - width,
			fPos.y,
			fPos.z };

		int x = digitArray[i] % NUM_SPLIT.x;	
		int y = digitArray[i] / NUM_SPLIT.x;	

		m_p2dObj[objId]->SetPos(pos);
		m_p2dObj[objId]->SetUvOffset({ NUM_UVSCALE.x * x, NUM_UVSCALE.y * y });
		m_p2dObj[objId]->SetUvScale({ NUM_UVSCALE.x, NUM_UVSCALE.y });

		m_p2dObj[objId]->SetTexture(m_pTexture[E_TEXTURE::NUM]);
		m_p2dObj[objId]->Draw();
	}
}


/* ========================================
	数字桁格納処理
	----------------------------------------
	内容：配列に数字を桁ごとに格納する
	----------------------------------------
	引数1：桁格納配列
	引数1：格納する数字
	引数1：桁数
	----------------------------------------
	戻値：無し
=========================================== */
void CResult::NumStorage(std::vector<int>* digitArray, int nNumber, int nDigits)
{
	// 数字桁配列をリセット
	(*digitArray).clear();

	// 表示する数字が0以上の場合
	if (0 < nNumber)
	{
		// nNumberを全て格納するまで繰り返す
		while (0 != nNumber) 
		{
			(*digitArray).push_back(nNumber % 10);	// nNumberの下1桁を格納する
			nNumber /= 10;							// nNumberを1桁スライドさせる
			
		}

	}

	// 指定桁数まで0埋めする
	while ((*digitArray).size() < nDigits)
	{
		(*digitArray).push_back(0);
	}
}

/* ========================================
	次シーンゲッタ
	----------------------------------------
	内容：遷移したいシーンが何かを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：遷移先シーンの種類
=========================================== */
CResult::E_TYPE CResult::GetNext() const
{
	// =============== 提供 ===================
	return CResult::E_TYPE_SELECT_STAGE;	//遷移先シーンの種類
}

/* ========================================
	リザルト用SE読み込み関数
   ----------------------------------------
   内容：リザルト用のSEのファイルを読み込む
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CResult::LoadSound()
{
	//SEの読み込み
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}
}

/* ========================================
	SEの再生関数
	----------------------------------------
	内容：SEの再生
	----------------------------------------
	引数1：SEの種類(enum)
	引数2：音量
	----------------------------------------
	戻値：なし
======================================== */
void CResult::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE再生
	m_pSESpeaker[se]->SetVolume(volume);				//音量の設定
}