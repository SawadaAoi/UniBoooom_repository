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

========================================== */

#ifndef __SELECT_STAGE_H__	//SelectStage.hインクルードガード
#define __SELECT_STAGE_H__

// =============== インクルード ===================
#include "Scene.h"	//親のヘッダ
#include "2dPolygon.h"
#include "FrameCnt.h"	//割合検出用
#include <string>		//文字列操作
// =============== 定数定義 =======================
const int SUTAGE_NUM = 3;						// ステージの数

// =============== クラス定義 =====================
class CSelectStage :public CScene	//シーン
{
private:
	// ===列挙定義===========
	enum E_2D_OBJECT
	{
		E_2D_OBJECT_BACK_GROUND,		//背景
		E_2D_OBJECT_STAGE_1_REMINE,		//ステージ1手配書残る方
		E_2D_OBJECT_STAGE_1_LEAVE,		//ステージ1手配書離れる方
		E_2D_OBJECT_STAGE_2_REMINE,		//ステージ2手配書残る方
		E_2D_OBJECT_STAGE_2_LEAVE,		//ステージ2手配書離れる方
		E_2D_OBJECT_STAGE_3_REMINE,		//ステージ3手配書残る方
		E_2D_OBJECT_STAGE_3_LEAVE,		//ステージ3手配書離れる方
		E_2D_OBJECT_BACK_SCENE_NAME,	//シーン名
		E_2D_OBJECT_MAX,				//要素数
	};	//2dで扱うオブジェクト
	// ===定数定義===========
	const float MIN_SIZE_ARR_LET = 450.0f;				//手配書最小サイズ
	const float MAX_SIZE_ARR_LET = 550.0f;				//手配書最大サイズ
	const float ASPECT_RATE_ARR_LET = 400.0f / 500.0f;	//手配書縦に対する横の比率
	const TTriType<float> INIT_SIZE_ARR_LET = { MIN_SIZE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f };	//手配書初期サイズ
	const int CHANGE_SCALE_HALF_TIME = 120;	//拡縮半周あたりにかかる時間
	const std::map<E_2D_OBJECT, std::string> MAP_TEXTURE_FILE= {
	{ E_2D_OBJECT_STAGE_1_REMINE, "Assets/Texture/StageSelect/zako1-1.png" },	//ステージ1手配書残る方
	{ E_2D_OBJECT_STAGE_1_LEAVE,	"Assets/Texture/StageSelect/zako1-2.png" },	//ステージ1手配書離れる方
	{ E_2D_OBJECT_STAGE_2_REMINE, "Assets/Texture/StageSelect/boss1-1.png" },	//ステージ2手配書残る方
	{ E_2D_OBJECT_STAGE_2_LEAVE,	"Assets/Texture/StageSelect/boss1-2.png" },	//ステージ2手配書離れる方
	{ E_2D_OBJECT_STAGE_3_REMINE, "Assets/Texture/StageSelect/stone1-1.png" },	//ステージ3手配書残る方
	{ E_2D_OBJECT_STAGE_3_LEAVE, "Assets/Texture/StageSelect/stone1-2.png" },	//ステージ3手配書離れる方
	{ E_2D_OBJECT_BACK_GROUND, "Assets/Texture/StageSelect/StageSelectBG.png"},	//背景
	{ E_2D_OBJECT_BACK_SCENE_NAME, "Assets/Texture/StageSelect/stselectUI.png"},//シーン名
	};	//テクスチャのファイル名
	const std::map<E_2D_OBJECT, TPos3d<float>> INIT_MAP_POS = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { 250.0f, 300.0f,1.0f } },							//ステージ1手配書残る方
	{ E_2D_OBJECT_STAGE_1_LEAVE, { 250.0f, 300.0f,1.0f } },								//ステージ1手配書離れる方
	{ E_2D_OBJECT_STAGE_2_REMINE, { 600.0f, 300.0f,1.0f } },							//ステージ2手配書残る方
	{ E_2D_OBJECT_STAGE_2_LEAVE, { 600.0f, 300.0f,1.0f } },								//ステージ2手配書離れる方
	{ E_2D_OBJECT_STAGE_3_REMINE, { 950.0f, 300.0f,1.0f } },							//ステージ3手配書残る方
	{ E_2D_OBJECT_STAGE_3_LEAVE, { 950.0f, 300.0f,1.0f } },								//ステージ3手配書離れる方
	{ E_2D_OBJECT_BACK_GROUND, { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f ,1.0f }},	//背景
	{ E_2D_OBJECT_BACK_SCENE_NAME, { 640.0f, 660.0f  ,1.0f }},							//シーン名
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
	};	//オブジェクト毎の初期回転
	const std::map<E_2D_OBJECT, TTriType<float>> INIT_MAP_SIZE = {
	{ E_2D_OBJECT_STAGE_1_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ1手配書残る方
	{ E_2D_OBJECT_STAGE_1_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ1手配書離れる方
	{ E_2D_OBJECT_STAGE_2_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ2手配書残る方
	{ E_2D_OBJECT_STAGE_2_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ2手配書離れる方
	{ E_2D_OBJECT_STAGE_3_REMINE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ3手配書残る方
	{ E_2D_OBJECT_STAGE_3_LEAVE, { MIN_SIZE_ARR_LET * ASPECT_RATE_ARR_LET, MIN_SIZE_ARR_LET, 1.0f } },	//ステージ3手配書離れる方
	{ E_2D_OBJECT_BACK_GROUND, { SCREEN_WIDTH, SCREEN_HEIGHT,1.0f }},									//背景
	{ E_2D_OBJECT_BACK_SCENE_NAME, { SCREEN_WIDTH, 120.0f ,1.0f }},										//シーン名
	};	//オブジェクト毎の初期拡縮
public:
	// =============== プロトタイプ宣言 ===============
	CSelectStage();						//コンストラクタ
	~CSelectStage();					//デストラクタ
	void Update();						//更新
	void Draw();// const;				//描画	
	void Select();
	E_TYPE GetType() const override;	//自身の種類ゲッタ
	E_TYPE GetNext() const override;	//次のシーンゲッタ
private:
	std::map<E_2D_OBJECT, C2dPolygon*> m_p2dObject;	//2dで扱うオブジェクト
	bool m_bStickFlg;			// コントローラーのスティックをたおしているか
	CFrameCnt* m_pFrameCnt;		//イージング用タイマー
	bool m_bCntUpDwn;			//カウントアップ・ダウン
	E_TYPE m_eNextType;			//次のシーンの種類
};	//ステージセレクト

#endif	//!__SELECT_STAGE_H__