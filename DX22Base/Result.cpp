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
	{CResult::BG_SCREEN,		"Assets/Texture/Result/ResultBG.png"},			// 画面全体の背景
	{CResult::BG_PANEL,			"Assets/Texture/Result/result_waku.png"},		// 各項目の背景(黒い背景)
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


// 画像表示用パラメータまとめ
typedef struct
{
	TDiType<float> fPos;
	TDiType<float> fSize;
}Display_Param;

typedef struct
{
	TTriType<float> fPos;
	TTriType<float> fSize;
}Display_Param_3;

const Display_Param WARNING_TEXTURE_PARAM	= { {260.0f, 380.0f} ,{460.0f, 580.0f} };	// 手配書
const Display_Param CLEAR_STAMP_PARAM		= { {260.0f, 380.0f} ,{460.0f, 580.0f} };	// スタンプ
const Display_Param_3 RESULT_TEXT_PARAM = { { 275.0f, 660.0f, 1.0f},{ 640.0f,  280.0f, 1.0f} };	// リザルト
const int			RESULT_TEXT_FLASH = 0.04 * 60;

const float DEF_NUM_SPACE = 68.0f;
const TDiType<int> NUM_SPLIT = { 5, 2 };
const TDiType<float> NUM_UVSCALE = { (1.0f / 5) ,(1.0f / 2) };

const Display_Param BG_SCREEN_PARAM		= { { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },{ SCREEN_WIDTH, SCREEN_HEIGHT } };	// 背景
const Display_Param BG_PANEL_PARAM		= { { 905.0f, SCREEN_HEIGHT / 2 } ,{ 750.0f, SCREEN_HEIGHT } };					// 項目背景

const Display_Param SVL_TIME_TEXT_PARAM = { { 650.0f, 30.0f },{ 200.0f, 80.0f } };	// 生存時間(文字)
const Display_Param SVL_TIME_NUM__PARAM = { { 1200.0f, 50.0f },{ 85.0f, 95.0f } };	// 生存時間(数字)
const Display_Param SVL_TIME_LINE_PARAM = { { 907.0f, 100.0f },{ 729.0f, 5.0f } };	// 線
const float SVL_TIME_NUM_SPACE = 55.0f;		// 時間の間(例 12□:□33)

const Display_Param SCORE_TEXT_PARAM		= { { 655.0f, 130.0f },{ 220.0f, 75.0f } };		// スコア(文字)
const Display_Param NEW_RECORD_TEXT_PARAM	= { { 820.0f,180.0f },{ 170.0f, 55.0f } };		// 新記録(文字)
const Display_Param SCORE_NUM_PARAM			= { { 1200.0f, 160.0f },{ 85.0f, 105.0f } };	// スコア(数字)
const Display_Param HIGH_SCORE_TEXT_PARAM	= { { 645.0f, 240.0f },{ 180.0f, 75.0f } };		// ハイスコア(文字)
const Display_Param HIGH_SCORE_NUM_PARAM	= { { 1200.0f, 260.0f },{ 55.0f, 55.0f } };		// ハイスコア(数字)
const Display_Param SCORE_LINE_PARAM		= { { 907.0f, 300.0f },{ 729.0f, 5.0f } };		// 線
const float SCORE_NUM_SPACE = 70.0f;
const float HIGH_SCORE_NUM_SPACE = 45.0f;


const Display_Param HUNT_TEXT_PARAM			= { { 710.0f, 340.0f },{ 330.0f, 110.0f } };	// 討伐数(文字)
const Display_Param SLIME_TEXTURE_PARAM		= { { 650.0f, 430.0f },{ 160.0f, 160.0f } };	// スライム画像
const float SLIME_SPACE_Y = 130.0f;	// スライム画像の間
const Display_Param SLIME_HUNT_NUM_PARAM	= { { 650.0f, 430.0f },{ 60.0f, 60.0f } };		// スライム別討伐数
const Display_Param PARENTHESIS_PARAM		= { { 650.0f, 530.0f },{ 0.0f, 0.0f } };		// ()
const Display_Param MULTI_PARAM				= { { 650.0f, 510.0f },{ 40.0f, 40.0f } };		// ×
const Display_Param MULTI_SLIME_PARAM		= { { 615.0f, 510.0f },{ 30.0f, 30.0f } };		// 青スライム画像の位置
const Display_Param MULTI_NUM_PARAM			= { { 685.0f, 510.0f },{ 40.0f, 40.0f } };		// 青スライムの倍数
const Display_Param TOTAL_HUNT_TEXT_PARAM	= { { 670.0f, 560.0f },{ 250.0f, 80.0f } };		// 総討伐数(文字)
const Display_Param TOTAL_HUNT_NUM_PARAM	= { { 1200.0f, 580.0f },{ 85.0f, 105.0f } };	// 総討伐数(数字)
const Display_Param HUNT_LINE_PARAM			= { { 907.0f, 620.0f } , { 729.0f, 5.0f } };	// 線
const float HUNT_NUM_SPACE = 45.0f;															// 数字間の距離


const Display_Param MAX_COMBO_TEXT_PARAM	= { { 695.0f, 655.0f } , {  300.0f, 90.0f } };	// 最大コンボ数(文字)
const Display_Param MAX_COMBO_NUM_PARAM		= { { 1200.0f, 670.0f } ,{ 85.0f, 105.0f } };	// 最大コンボ数(数字)

const Display_Param_3 SELECT_PARAM			= { { 65.0f, 40.0f, 1.0f } , { 130.0f, 65.0f, 1.0f } };		// 決定ボタン
const float FLASH_BUTTON_TEXT_ADJUST		= 0.02f;										//「決定」テキストの点滅間隔調整

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
	
	// リザルト文字のアニメーションの初期化
	m_pTextureResultText = new CDrawAnim(60, TDiType<int>(5, 12), RESULT_TEXT_FLASH);
	m_pTextureResultText->SetTexture(m_pTexture[E_TEXTURE::RESULT_TEXT]);
	m_pTextureResultText->SetPos(RESULT_TEXT_PARAM.fPos);
	m_pTextureResultText->SetSize(RESULT_TEXT_PARAM.fSize);
	m_pTextureResultText->SetLoopFlg(true);

	// 決定ボタン初期化
	m_pSelectButton = new C2dPolygon();
	m_pSelectButton->SetTexture(m_pTexture[E_TEXTURE::SELECT]);
	m_pSelectButton->SetPos(SELECT_PARAM.fPos);
	m_pSelectButton->SetSize(SELECT_PARAM.fSize);

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
	SAFE_DELETE(m_pSelectButton);
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
	// 決定ボタン
	m_pSelectButton->Update();
	m_nButtonAlphaCnt++;
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
	// 全体の背景
	Draw2d(
		BG_SCREEN_PARAM.fPos.x, BG_SCREEN_PARAM.fPos.y,
		BG_SCREEN_PARAM.fSize.x, BG_SCREEN_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::BG_SCREEN]);

	// 右半分の各項目の背景
	Draw2d(
		BG_PANEL_PARAM.fPos.x,BG_PANEL_PARAM.fPos.y,
		BG_PANEL_PARAM.fSize.x,BG_PANEL_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::BG_PANEL]);
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
	
	// 手配書表示
	Draw2d(
		WARNING_TEXTURE_PARAM.fPos.x,
		WARNING_TEXTURE_PARAM.fPos.y,
		WARNING_TEXTURE_PARAM.fSize.x,
		WARNING_TEXTURE_PARAM.fSize.y,
		pWarningTex);

	// クリアした場合
	if (m_Data.bClearFlg)
	{
		// スタンプを表示する
		Draw2d(
			CLEAR_STAMP_PARAM.fPos.x,
			CLEAR_STAMP_PARAM.fPos.y,
			CLEAR_STAMP_PARAM.fSize.x,
			CLEAR_STAMP_PARAM.fSize.y,
			m_pTexture[E_TEXTURE::CLEAR_STAMP]);
	}

	// 決定ボタン
	m_pSelectButton->SetAlpha(fabs(cosf(m_nButtonAlphaCnt * FLASH_BUTTON_TEXT_ADJUST)));	// 点滅の為、透明度変更
	m_pSelectButton->Draw();

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
	Draw2d(
		SVL_TIME_TEXT_PARAM.fPos.x,
		SVL_TIME_TEXT_PARAM.fPos.y,
		SVL_TIME_TEXT_PARAM.fSize.x,
		SVL_TIME_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::SVL_TIME_TEXT]);

	// 生存時間(数字)
	DispTime();

	// 線
	Draw2d(
		SVL_TIME_LINE_PARAM.fPos.x,
		SVL_TIME_LINE_PARAM.fPos.y,
		SVL_TIME_LINE_PARAM.fSize.x,
		SVL_TIME_LINE_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::LINE]);
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
	Draw2d(
		SCORE_TEXT_PARAM.fPos.x,
		SCORE_TEXT_PARAM.fPos.y,
		SCORE_TEXT_PARAM.fSize.x,
		SCORE_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::SCORE_TEXT]);


	// 総スコア(数字)
	DispNum(m_Data.nTotalScore, 5, SCORE_NUM_PARAM.fPos, SCORE_NUM_PARAM.fSize, SCORE_NUM_SPACE);

	// ハイスコア(文字)
	Draw2d(
		HIGH_SCORE_TEXT_PARAM.fPos.x,
		HIGH_SCORE_TEXT_PARAM.fPos.y,
		HIGH_SCORE_TEXT_PARAM.fSize.x,
		HIGH_SCORE_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::HIGH_SCORE_TEXT]);

	// ハイスコアを更新していたら(ゲーム終了時にハイスコアを更新する為)
	if (m_Data.nHighScore[m_Data.nStageNum-1] == m_Data.nTotalScore)
	{
		// ニューレコード(文字)
		Draw2d(
			NEW_RECORD_TEXT_PARAM.fPos.x,
			NEW_RECORD_TEXT_PARAM.fPos.y,
			NEW_RECORD_TEXT_PARAM.fSize.x,
			NEW_RECORD_TEXT_PARAM.fSize.y,
			m_pTexture[E_TEXTURE::NEW_RECORD_TEXT]);

	}

	// ハイスコア(数字)
	DispNum(m_Data.nHighScore[m_Data.nStageNum - 1], 5, HIGH_SCORE_NUM_PARAM.fPos, HIGH_SCORE_NUM_PARAM.fSize, HIGH_SCORE_NUM_SPACE);
	

	// 線
	Draw2d(
		SCORE_LINE_PARAM.fPos.x,
		SCORE_LINE_PARAM.fPos.y,
		SCORE_LINE_PARAM.fSize.x,
		SCORE_LINE_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::LINE]);
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
	Draw2d(
		HUNT_TEXT_PARAM.fPos.x,
		HUNT_TEXT_PARAM.fPos.y,
		HUNT_TEXT_PARAM.fSize.x,
		HUNT_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::HUNT_TEXT]);

	// ステージ１ならボス討伐数を表示しない
	int nDispHuntNum = 5;	// 青＋緑＋黄＋赤＋ボス＝５
	if (m_Data.nStageNum == 1) nDispHuntNum = 4;	// ーボス＝４

	// スライムの種類数分画像を表示
	for (int i = 0; i < nDispHuntNum; i++)
	{
		// スライムの画像
		Draw2d(
			SLIME_TEXTURE_PARAM.fPos.x + (i * SLIME_SPACE_Y),
			SLIME_TEXTURE_PARAM.fPos.y,
			SLIME_TEXTURE_PARAM.fSize.x,
			SLIME_TEXTURE_PARAM.fSize.y,
			m_pTexture[E_TEXTURE::SLIME_BLUE + i]);

		// スライム緑～赤の下に青の倍数を表示する
		if (1 <= i && i <= 3)
		{
			// ()
			Draw2d(
				PARENTHESIS_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				PARENTHESIS_PARAM.fPos.y,
				PARENTHESIS_PARAM.fSize.x,
				PARENTHESIS_PARAM.fSize.y,
				m_pTexture[E_TEXTURE::PARENTHESIS]);

			// 青スライム画像
			Draw2d(
				MULTI_SLIME_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				MULTI_SLIME_PARAM.fPos.y,
				MULTI_SLIME_PARAM.fSize.x,
				MULTI_SLIME_PARAM.fSize.y,
				m_pTexture[E_TEXTURE::SLIME_BLUE]);

			// ×
			Draw2d(
				MULTI_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				MULTI_PARAM.fPos.y,
				MULTI_PARAM.fSize.x,
				MULTI_PARAM.fSize.y,
				m_pTexture[E_TEXTURE::MULTI]);

		}
		// 倍数
		DispNum(2, 1, { MULTI_NUM_PARAM.fPos.x + (1 * SLIME_SPACE_Y), MULTI_NUM_PARAM.fPos.y }, MULTI_NUM_PARAM.fSize, DEF_NUM_SPACE);
		DispNum(4, 1, { MULTI_NUM_PARAM.fPos.x + (2 * SLIME_SPACE_Y), MULTI_NUM_PARAM.fPos.y }, MULTI_NUM_PARAM.fSize, DEF_NUM_SPACE);
		DispNum(8, 1, { MULTI_NUM_PARAM.fPos.x + (3 * SLIME_SPACE_Y), MULTI_NUM_PARAM.fPos.y }, MULTI_NUM_PARAM.fSize, DEF_NUM_SPACE);

		// スライム別討伐数
		//２桁以上の場合
		if (m_Data.nKill[i] >= 10)
		{
			DispNum(m_Data.nKill[i], 1, {
			SLIME_HUNT_NUM_PARAM.fPos.x + (i*SLIME_SPACE_Y) + (SLIME_HUNT_NUM_PARAM.fSize.x / 3),
			SLIME_HUNT_NUM_PARAM.fPos.y },
			SLIME_HUNT_NUM_PARAM.fSize, HUNT_NUM_SPACE);
		}
		//１桁の場合
		else
		{
			DispNum(m_Data.nKill[i], 1, {
				SLIME_HUNT_NUM_PARAM.fPos.x + (i*SLIME_SPACE_Y),
				SLIME_HUNT_NUM_PARAM.fPos.y },
				SLIME_HUNT_NUM_PARAM.fSize, HUNT_NUM_SPACE);
		}

	}

	// 総討伐数(文字)
	Draw2d(
		TOTAL_HUNT_TEXT_PARAM.fPos.x,
		TOTAL_HUNT_TEXT_PARAM.fPos.y,
		TOTAL_HUNT_TEXT_PARAM.fSize.x,
		TOTAL_HUNT_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::TOTAL_HUNT_TEXT]);

	// 総討伐数(数字)
	DispNum(m_Data.nTotalKill, 1, TOTAL_HUNT_NUM_PARAM.fPos, TOTAL_HUNT_NUM_PARAM.fSize, DEF_NUM_SPACE);

	// 線
	Draw2d(
		HUNT_LINE_PARAM.fPos.x,
		HUNT_LINE_PARAM.fPos.y,
		HUNT_LINE_PARAM.fSize.x,
		HUNT_LINE_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::LINE]);
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
	Draw2d(
		MAX_COMBO_TEXT_PARAM.fPos.x,
		MAX_COMBO_TEXT_PARAM.fPos.y,
		MAX_COMBO_TEXT_PARAM.fSize.x,
		MAX_COMBO_TEXT_PARAM.fSize.y,
		m_pTexture[E_TEXTURE::MAX_COMBO_TEXT]);

	// 最大コンボ数(数字)
	DispNum(m_Data.nMaxCombo, 1, MAX_COMBO_NUM_PARAM.fPos, MAX_COMBO_NUM_PARAM.fSize, DEF_NUM_SPACE);
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
	DispNum(m_Data.GetSecond(), 2, SVL_TIME_NUM__PARAM.fPos, SVL_TIME_NUM__PARAM.fSize, DEF_NUM_SPACE);

	// コロン
	Draw2d(
		SVL_TIME_NUM__PARAM.fPos.x - (SVL_TIME_NUM_SPACE * 2) -7.0f,	// -7.0fはコロンの位置の微調整
		SVL_TIME_NUM__PARAM.fPos.y,
		SVL_TIME_NUM__PARAM.fSize.x,
		SVL_TIME_NUM__PARAM.fSize.y,
		m_pTexture[E_TEXTURE::COLON]);

	TDiType<float> pos = { 
		SVL_TIME_NUM__PARAM.fPos.x - (SVL_TIME_NUM_SPACE * 3) ,
		SVL_TIME_NUM__PARAM.fPos.y };

	// 分数
	DispNum(m_Data.GetMinute(), 2, pos, SVL_TIME_NUM__PARAM.fSize, DEF_NUM_SPACE);
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
void CResult::DispNum(int dispNum, int nDigits, TDiType<float> pos, TDiType<float> size, float NumSpace)
{

	std::vector<int> digitArray;
	DirectX::XMFLOAT4X4 mat;
	int Num = dispNum;


	NumStorage(&digitArray, dispNum, nDigits);


	

	for (int i = 0; i < digitArray.size(); i++)
	{

		int width = int(NumSpace * i);
		//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x - width, pos.y, 0.0f);
		DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(world));

		//スプライトの設定
		Sprite::SetWorld(mat);

		int x = digitArray[i] % NUM_SPLIT.x;	//ここ名前募集します
		int y = digitArray[i] / NUM_SPLIT.x;	//配列に入ってる数字の場所を計算してます

		Sprite::SetSize(DirectX::XMFLOAT2(size.x, -size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(NUM_UVSCALE.x * x, NUM_UVSCALE.y * y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(NUM_UVSCALE.x, NUM_UVSCALE.y));
		Sprite::SetTexture(m_pTexture[E_TEXTURE::NUM]);
		Sprite::Draw();
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
	種類ゲッタ
	----------------------------------------
	内容：自身がリザルトシーンであることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CResult::E_TYPE CResult::GetType() const
{
	// =============== 提供 ===================
	return CResult::E_TYPE_RESULT;	//自身の種類
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