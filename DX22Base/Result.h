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

// =============== クラス定義 =====================
class CResult :public CScene	//シーン
{
public:
	// ===列挙定義===========
	enum E_TEXTURE	// 表示画像
	{
		BG_SCREEN,			// 画面全体の背景
		BG_PANEL,			// 各項目の背景(黒い背景)
		RESULT_TEXT,		// 文字(Result)
		SVL_TIME_TEXT,		// 文字(生存時間)
		SCORE_TEXT,			// 文字(SCORE)	
		HIGH_SCORE_TEXT,	// 文字(HISCORE)
		NEW_RECORD_TEXT,	// 文字(NEW RECORD)
		HUNT_TEXT,			// 文字(スライム討伐数)
		TOTAL_HUNT_TEXT,	// 文字(総討伐数)
		SLIME_BLUE,			// スライム画像(青)
		SLIME_GREEN,		// スライム画像(緑)
		SLIME_YELLOW,		// スライム画像(黄)
		SLIME_RED,			// スライム画像(赤)
		SLIME_BOSS,			// スライム画像(ボス)
		MAX_COMBO_TEXT,		// 文字(最大コンボ数)

		NUM,				// 数字
		COLON,				// コロン
		LINE,				// 線
		MULTI,				// ×
		PARENTHESIS,		// ()

		WARNING_STAGE_1,	// ステージ1の手配書
		WARNING_STAGE_2,	// ステージ2の手配書
		WARNING_STAGE_3,	// ステージ3の手配書
		CLEAR_STAMP,		// CLEARスタンプ

		TEXTURE_MAX,

	};

	enum SE
	{
		SE_DECISION,	//決定音

		SE_MAX			//SEの総数
	}; //SE


public:
	// =============== プロトタイプ宣言 ===============
	CResult();							//コンストラクタ
	~CResult();							//デストラクタ
	void Update();						//更新
	void Draw();					//描画	
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	void DrawBgScreen();
	void DrawWarningTexture();
	void DrawSurvivalTime();
	void DrawScore();
	void DrawHunt();
	void DrawMaxCombo();

	void DispTime();
	void DispNum(int dispNum, int nDigits, TDiType<float> pos, TDiType<float> size, float NumSpace);
	void NumStorage(std::vector<int>* digitArray,int nNumber, int nDigits);

	void LoadSound();								//サウンドをロード
	void PlaySE(SE se, float volume = 1.0f);		//SEを再生する
	// =============== メンバ変数定義 ===============
	
	Texture* m_pTexture[TEXTURE_MAX];
	BattleData m_Data;					//戦闘結果
	CDrawAnim *m_pDrawAnim;				//リザルトの文字のアニメーション

	//=====SE関連=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Decision.mp3",				// 決定音
	};


};	//リザルト

#endif	//!__RESULT_H__