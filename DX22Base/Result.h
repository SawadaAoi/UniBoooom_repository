/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	リザルトシーン定義
	---------------------------------------
	Result.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/08 シーン遷移用に変数追加 takagi
	・2023/12/11 成績仮表示 takagi
	・2023/12/25 表示内容の変更 Sawada
	・2024/01/26 決定SE追加 suzumura
	・2024/01/26 アニメーション追加 goto
	・2024/02/03 リザルト表示位置等微調整 suzumura
	・2024/02/09 GetType()関数削除 takagi

========================================== */

#ifndef __RESULT_H__	//Result.hインクルードガード
#define __RESULT_H__

// =============== インクルード ===================
#include "Scene.h"		//親のヘッダ
#include "Texture.h"
#include "BattleData.h"	//メンバのヘッダ
#include <vector>		//配列型コンテナ
#include "2dPolygon.h"	// 2Dオブジェクト用
#include "NumberText.h"
#include "DrawAnimation.h"
#include "Sound.h"
#include "FrameCnt.h"	//割合検出用


// =============== クラス定義 =====================
class CResult :public CScene	//シーン
{
public:
	// ===列挙定義===========
	enum E_TEXTURE	// 表示画像
	{
		BG_SCREEN_CLEAR,		// 画面全体の背景 赤：ゲームクリア
		BG_SCREEN_GAMEOVER,		// 画面全体の背景 青：ゲームオーバー
		BG_PANEL_CLEAR,			// 各項目の背景(黒い背景) 赤枠：ゲームクリア
		BG_PANEL_GAMEOVER,		// 各項目の背景(黒い背景) 青枠：ゲームオーバー
		RESULT_TEXT,			// 文字(Result)
		SVL_TIME_TEXT,			// 文字(生存時間)
		SCORE_TEXT,				// 文字(SCORE)	
		HIGH_SCORE_TEXT,		// 文字(HISCORE)
		NEW_RECORD_TEXT,		// 文字(NEW RECORD)
		HUNT_TEXT,				// 文字(スライム討伐数)
		TOTAL_HUNT_TEXT,		// 文字(総討伐数)
		SLIME_BLUE,				// スライム画像(青)
		SLIME_GREEN,			// スライム画像(緑)
		SLIME_YELLOW,			// スライム画像(黄)
		SLIME_RED,				// スライム画像(赤)
		SLIME_BOSS,				// スライム画像(ボス)
		MAX_COMBO_TEXT,			// 文字(最大コンボ数)

		NUM,					// 数字
		COLON,					// コロン
		LINE,					// 線
		MULTI,					// ×
		PARENTHESIS,			// ()

		WARNING_STAGE_1,		// ステージ1の手配書
		WARNING_STAGE_2,		// ステージ2の手配書
		WARNING_STAGE_3,		// ステージ3の手配書
		CLEAR_STAMP,			// CLEARスタンプ
		SELECT,					// 決定ボタン

		TEXTURE_MAX,

	};

	enum SE
	{
		SE_DECISION,	//決定音

		SE_MAX			//SEの総数
	}; //SE

	enum E_2D_OBJ_ID
	{
		OBJ_BG_SCREEN,				// 背景
		OBJ_BG_PANEL,				// 項目背景
		OBJ_WARNING_STAGE,			// 手配書画像
		OBJ_CLEAR_STAMP,			// スタンプ画像
		OBJ_RESULT_TEXT,			// リザルト(文字)
		OBJ_SVL_TIME_TEXT,			// 生存時間(文字)
		OBJ_SVL_TIME_SECOND_NUM,	// 生存時間(秒)
		OBJ_SVL_TIME_COLON,			// 生存時間(コロン)	
		OBJ_SVL_TIME_MINUTE_NUM,	// 生存時間(分)		
		OBJ_SVL_TIME_LINE,			// 区切り線
		OBJ_SCORE_TEXT,				// スコア(文字)
		OBJ_NEW_RECORD_TEXT,		// 新記録(文字)
		OBJ_SCORE_NUM,				// スコア(数字)
		OBJ_HIGH_SCORE_TEXT,		// ハイスコア(文字)
		OBJ_HIGH_SCORE_NUM,			// ハイスコア(数字)
		OBJ_SCORE_LINE,				// 区切り線
		OBJ_HUNT_TEXT,				// 討伐数(文字)
		OBJ_SLIME_HUNT_BG,			// 討伐数背景スライム画像
		OBJ_SLIME_HUNT_NUM,			// スライム別討伐数
		OBJ_PARENTHESIS,			// ()
		OBJ_MULTI,					// ×
		OBJ_MULTI_BLUE_SLIME,		// 青スライム画像の位置
		OBJ_MULTI_NUM,				// 青スライムの倍数
		OBJ_TOTAL_HUNT_TEXT,		// 総討伐数(文字)
		OBJ_TOTAL_HUNT_NUM,			// 総討伐数(数字)
		OBJ_HUNT_LINE,				// 区切り線
		OBJ_MAX_COMBO_TEXT,			// 最大コンボ数(文字)
		OBJ_MAX_COMBO_NUM,			// 最大コンボ数(数字)
		OBJ_SELECT_BUTTON,			// 決定 

		OBJ_2D_MAX,
	};

public:
	// =============== プロトタイプ宣言 ===============
	CResult();													//コンストラクタ
	~CResult();													//デストラクタ
	void Update();												//更新
	void Draw();												//描画
	E_TYPE GetNext() const override;							//次のシーンゲッタ

private:
	void DrawBgScreen();
	void DrawWarningTexture();
	void DrawSurvivalTime();
	void DrawScore();
	void DrawHunt();
	void DrawMaxCombo();

	void DispTime();
	void DispNum(int dispNum, int nDigits, E_2D_OBJ_ID objId, TTriType<float> fPos, float NumSpace);
	void NumStorage(std::vector<int>* digitArray,int nNumber, int nDigits);

	void LoadSound();								//サウンドをロード
	void PlaySE(SE se, float volume = 1.0f);		//SEを再生する
	// =============== メンバ変数定義 ===============
	
	Texture* m_pTexture[TEXTURE_MAX];
	BattleData m_Data;					// 戦闘結果
	CDrawAnim* m_pTextureResultText;	// リザルトの文字
	int m_nButtonAlphaCnt;			// 点滅用
	int m_nNewRecoAlphaCnt;			// 点滅用

	C2dPolygon* m_p2dObj[OBJ_2D_MAX];

	int m_nStAnimCnt;
	bool m_nStartAnimEnd;

	//=====SE関連=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Decision.mp3",				// 決定音
	};


};	//リザルト

#endif	//!__RESULT_H__