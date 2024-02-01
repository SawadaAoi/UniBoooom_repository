/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージセレクト定義
	---------------------------------------
	SelectStage.h

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 ステージセレクト用の構造体、配列、関数追加 yamamoto
	・2024/01/26 拡縮実装 takagi
	・2024/01/26 選択、決定SE追加 suzumura
	・2024/01/28 落下実装 takagi
	・2024/01/29 画像修正 takagi

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.hインクルードガード
#define __SELECT_STAGE_H__

// =============== インクルード ===================
#include "Scene.h"		//親のヘッダ
#include "2dPolygon.h"
#include "FrameCnt.h"	//割合検出用
#include "Sound.h"		//サウンドヘッダ
#include <string>		//文字列操作
#include "BattleData.h"	//メンバのヘッダ


// =============== 定数定義 =======================
const int STAGE_NUM = 3;						// ステージの数

// =============== クラス定義 =====================
class CSelectStage :public CScene	//シーン
{
private:
	// ===列挙定義===========
	enum E_2D_OBJECT
	{
		E_2D_OBJECT_BACK_GROUND,		// 背景
		E_2D_OBJECT_STAGE_1_REMINE,		// ステージ1手配書残る方
		E_2D_OBJECT_STAGE_1_LEAVE,		// ステージ1手配書離れる方
		E_2D_OBJECT_STAGE_2_REMINE,		// ステージ2手配書残る方
		E_2D_OBJECT_STAGE_2_LEAVE,		// ステージ2手配書離れる方
		E_2D_OBJECT_STAGE_3_REMINE,		// ステージ3手配書残る方
		E_2D_OBJECT_STAGE_3_LEAVE,		// ステージ3手配書離れる方
		E_2D_OBJECT_BACK_SCENE_NAME,	//シーン名
		E_2D_OBJECT_HISCORE_BG,			// ハイスコア背景
		E_2D_OBJECT_HISCORE_TEXT,		// ハイスコアテキスト
		E_2D_OBJECT_HISCORE_NUM,		// ハイスコア数字
		E_2D_OBJECT_BUTTON_EXPLANATION,	// 操作ボタン指示

		E_2D_OBJECT_MAX,				// 要素数
	};	//2dで扱うオブジェクト

	// ===定数定義===========
	const float MIN_SIZE_ARR_LET		= 350.0f;			// 手配書最小サイズ
	const float MAX_SIZE_ARR_LET		= 450.0f;			// 手配書最大サイズ
	const float ASPECT_RATE_ARR_LET		= 400.0f / 500.0f;	// 手配書縦に対する横の比率
	const TTriType<float> INIT_SIZE_ARR_LET = { MIN_SIZE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f };	//手配書初期サイズ
	const float MARGIN_FALL				= 0.0f;			// 落ち切ったと判断するときに補正する余裕
	const int	FALL_TIME_ARR_LET		= 60;			// 手配書が落ちるのにかかる時間

	const TDiType<float> STAGE_TEXTURE_OFFSET = { 0.0f, -0.5f };				// ステージ手配書画像の中心座標移動値
	const float POS_OFFSET_ADJUST_Y = MIN_SIZE_ARR_LET * STAGE_TEXTURE_OFFSET.y;	// ステージ手配書画像のオフセットによるズレを直す 

	const std::map<E_2D_OBJECT, std::string> MAP_TEXTURE_FILE= {
	{ E_2D_OBJECT_STAGE_1_REMINE, "Assets/Texture/StageSelect/zako1-3.png" },		// ステージ1手配書残る方
	{ E_2D_OBJECT_STAGE_1_LEAVE,	"Assets/Texture/StageSelect/zako1-2.png" },		// ステージ1手配書離れる方
	{ E_2D_OBJECT_STAGE_2_REMINE, "Assets/Texture/StageSelect/stone1-3.png" },		// ステージ2手配書残る方
	{ E_2D_OBJECT_STAGE_2_LEAVE,	"Assets/Texture/StageSelect/stone1-2.png" },	// ステージ2手配書離れる方
	{ E_2D_OBJECT_STAGE_3_REMINE, "Assets/Texture/StageSelect/boss1-3.png" },		// ステージ3手配書残る方
	{ E_2D_OBJECT_STAGE_3_LEAVE, "Assets/Texture/StageSelect/boss1-2.png" },		// ステージ3手配書離れる方
	{ E_2D_OBJECT_BACK_GROUND, "Assets/Texture/StageSelect/StageSelectBG.png"},		// 背景
	{ E_2D_OBJECT_BACK_SCENE_NAME, "Assets/Texture/StageSelect/stselectUI.png"},		// 背景
	{ E_2D_OBJECT_HISCORE_BG,	 "Assets/Texture/StageSelect/HiscoreBG.png"},		// ハイスコア背景
	{ E_2D_OBJECT_HISCORE_TEXT, "Assets/Texture/StageSelect/HiscoreText.png"},		// ハイスコアテキスト
	{ E_2D_OBJECT_HISCORE_NUM, "Assets/Texture/StageSelect/HiscoreNum.png"},		// ハイスコア数字
	{ E_2D_OBJECT_BUTTON_EXPLANATION, "Assets/Texture/StageSelect/Select_Button.png"},		// 操作ボタン指示

	};	//テクスチャのファイル名


	const std::map<E_2D_OBJECT, TPos3d<float>> INIT_MAP_POS = {
	{ E_2D_OBJECT_STAGE_1_REMINE,	{ 250.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// ステージ1手配書残る方
	{ E_2D_OBJECT_STAGE_1_LEAVE,	{ 250.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// ステージ1手配書離れる方
	{ E_2D_OBJECT_STAGE_2_REMINE,	{ 600.0f, 300.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// ステージ2手配書残る方
	{ E_2D_OBJECT_STAGE_2_LEAVE,	{ 600.0f, 300.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// ステージ2手配書離れる方
	{ E_2D_OBJECT_STAGE_3_REMINE,	{ 950.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// ステージ3手配書残る方
	{ E_2D_OBJECT_STAGE_3_LEAVE,	{ 950.0f, 400.0f - POS_OFFSET_ADJUST_Y, 1.0f } },		// ステージ3手配書離れる方
	{ E_2D_OBJECT_BACK_GROUND,		{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f ,1.0f }},	// 背景
	{ E_2D_OBJECT_BACK_SCENE_NAME,	{ 640.0f, 660.0f, 1.0f }},								// シーン名
	{ E_2D_OBJECT_HISCORE_BG,		{ 0.0f	, 0.0f	, 1.0f }},								// ハイスコア背景
	{ E_2D_OBJECT_HISCORE_TEXT,		{ -45.0f, 20.0f	, 1.0f }},								// ハイスコアテキスト
	{ E_2D_OBJECT_HISCORE_NUM,		{ 110.0f, -20.0f, 1.0f }},								// ハイスコア数字
	{ E_2D_OBJECT_BUTTON_EXPLANATION,	{ 1150.0f	, 50.0f	, 1.0f }},						// 操作ボタン指示
	};	//オブジェクト毎の初期位置


	const std::map<E_2D_OBJECT, TTriType<float>> INIT_MAP_ROTATE = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { 0.0f,0.0f,-0.25f } },	//ステージ1手配書残る方
	{ E_2D_OBJECT_STAGE_1_LEAVE, { 0.0f,0.0f,-0.25f } },	//ステージ1手配書離れる方
	{ E_2D_OBJECT_STAGE_2_REMINE, { 0.0f,0.0f,0.05f } },	//ステージ2手配書残る方
	{ E_2D_OBJECT_STAGE_2_LEAVE, { 0.0f,0.0f,0.05f } },		//ステージ2手配書離れる方
	{ E_2D_OBJECT_STAGE_3_REMINE, { 0.0f,0.0f,0.1f } },		//ステージ3手配書残る方
	{ E_2D_OBJECT_STAGE_3_LEAVE, { 0.0f,0.0f,0.1f } },		//ステージ3手配書離れる方
	{ E_2D_OBJECT_BACK_GROUND, {0.0f, 0.0f, 0.0f}},			//背景
	{ E_2D_OBJECT_BACK_SCENE_NAME, { 0.0f,0.0f,0.0f }},		//シーン名
	{ E_2D_OBJECT_HISCORE_BG,	 { 0.0f, 0.0f  ,0.0f }},	// ハイスコア背景
	{ E_2D_OBJECT_HISCORE_TEXT,	 { 0.0f, 0.0f  ,0.0f }},	// ハイスコアテキスト
	{ E_2D_OBJECT_HISCORE_NUM, { 0.0f, 0.0f  ,0.0f }},		// ハイスコア数字
	{ E_2D_OBJECT_BUTTON_EXPLANATION, { 0.0f, 0.0f  ,0.0f }},	// 操作ボタン指示
	};	//オブジェクト毎の初期回転


	const std::map<E_2D_OBJECT, TTriType<float>> INIT_MAP_SIZE = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ1手配書残る方
	{ E_2D_OBJECT_STAGE_1_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ1手配書離れる方
	{ E_2D_OBJECT_STAGE_2_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ2手配書残る方
	{ E_2D_OBJECT_STAGE_2_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ2手配書離れる方
	{ E_2D_OBJECT_STAGE_3_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ3手配書残る方
	{ E_2D_OBJECT_STAGE_3_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ3手配書離れる方
	{ E_2D_OBJECT_BACK_GROUND, { SCREEN_WIDTH, SCREEN_HEIGHT,1.0f }},									//背景
	{ E_2D_OBJECT_BACK_SCENE_NAME, { SCREEN_WIDTH, 130.0f ,1.0f }},										//シーン名
	{ E_2D_OBJECT_HISCORE_BG, { 280.0f, 100.0f  ,1.0f }},								// ハイスコア背景
	{ E_2D_OBJECT_HISCORE_TEXT, { 150.0f, 60.0f  ,1.0f }},								// ハイスコアテキスト
	{ E_2D_OBJECT_HISCORE_NUM, { 50.0f, 55.0f  ,1.0f }},								// ハイスコア数字
	{ E_2D_OBJECT_BUTTON_EXPLANATION, { 250.0f, 60.0f  ,1.0f }},						// 操作ボタン指示
	};	//オブジェクト毎の大きさ

public:
	// ===列挙宣言===========
	enum SE
	{
		SE_DECISION,	//決定音
		SE_CHOOSE,		//項目選択SE

		SE_MAX			//SEの総数
	}; //SE
public:
	// =============== プロトタイプ宣言 ===============
	CSelectStage();						// コンストラクタ
	~CSelectStage();					// デストラクタ
	void Update();						// 更新
	void Draw();// const;				// 描画	
	void StageSelect();						   
	E_TYPE GetType() const override;	// 自身の種類ゲッタ
	E_TYPE GetNext() const override;	// 次のシーンゲッタ
	void LoadSound();								// シーンセレクト用のサウンドをロード
	void PlaySE(SE se, float volume = 1.0f);		// SEを再生する
private:
	void SelectStageChange(int select);
	void SelectStageTextureAnimation(CScene::E_TYPE stage);
	void FallAnimationStageTexture();
	void ResetStageTexture(CScene::E_TYPE stage);

	void DrawStageTexture();
	void DrawHiscore();
	void DispNum(int dispNum, int nDigits, TTriType<float> pos);
	void NumStorage(std::vector<int>* digitArray, int nNumber, int nDigits);

	std::map<E_2D_OBJECT, C2dPolygon*> m_p2dObject;	// 2dで扱うオブジェクト
	float m_fChangeRotate;							// 選択しているステージ手配書画像の傾き変動値
	bool m_bStickFlg;								// スティックを一度ニュートラルに戻したか
	CFrameCnt* m_pFrameCntFall;						// 落下イージング用タイマー
	CFrameCnt* m_pFrameCntRotate;					// 拡縮イージング用タイマー
	bool m_bCntUpDwn;								// カウントアップ・ダウン切換フラグ
	E_TYPE m_eNextType;								// 次のシーンの種類
	BattleData m_Data;								// 戦闘結果
	int m_nButtonAlphaCnt;

	//=====SE関連=====
	XAUDIO2_BUFFER* m_pSE[SE_MAX];
	IXAudio2SourceVoice* m_pSESpeaker[SE_MAX];
	const std::string m_sSEFile[SE_MAX] = {
		"Assets/Sound/SE/Paper_break.mp3",			// 決定音
		"Assets/Sound/SE/Select_Cursor.mp3" 		// 選択音
	};
};	//ステージセレクト

#endif	//!__SELECT_STAGE_H__