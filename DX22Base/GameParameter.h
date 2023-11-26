/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームパラメーター調整用ヘッダ
	---------------------------------------
	GameParameter.h

	作成者	鈴村朋也

	変更履歴
	・2023/11/11 ヘッダ作成 Suzumura
	・2023/11/13 パラメーター追加(LEVEL_〇_EXPLODE_TIME) Suzumura
	・2023/11/14 パラメーター追加(// フレイムスライム) Suzumura
	・2023/11/15 パラメーター追加(// フレイムスライム) Suzumura
	・2023/11/18 パラメーター追加(// スコア) yamamoto
	・2023/11/21 パラメーター追加(// コンボ数) Sawada
	・2023/11/23 パラメーター追加(// ボス１スライム) Suzumura
	・2023/11/23 パラメーター追加(// 2D描画) nieda
	・2023/11/24 パラメーター削除(// カメラ) Takagi
	・2023/11/25 パラメーター追加(// スコア) yamamoto

=========================================== */
#ifndef __GAME_PARAMETER_H__
#define __GAME_PARAMETER_H__

// =============== インクルード ===================
#include "Pos2d.h"
#include "Pos3d.h"
#include <DirectXMath.h>

// =============== パラメーター モード =======================
#define MODE_GAME_PARAMETER	(true)

#if MODE_GAME_PARAMETER

// =============== インクルード ===================
#include "Pos3d.h"

//ゲームシーン================================================
const float BGM_VOLUME = 0.02f;				//シーンゲームの音量
const float SE_HAMMER_HIT_VOLUME = 0.5f;	// スライムを打った時のSEの音量
// 画面サイズ
const int SCREEN_WIDTH_ = 1280;
const int SCREEN_HEIGHT_ = 720;

// プレイヤー ================================================
const float PLAYER_MOVE_SPEED	= 0.1f;			// プレイヤーの移動速度
const int	PLAYER_HP			= 5;			// プレイヤーのHP
const float PLAYER_RADIUS		= 0.1f;			// プレイヤーの当たり判定の大きさ
const float PLAYER_SIZE			= 0.2f;			// プレイヤーの大きさ
const int	NO_DAMAGE_TIME		= 3 * 60;		// プレイヤーの無敵時間
const int	DAMAGE_FLASH_FRAME	= 0.1f * 60;	// プレイヤーのダメージ点滅の切り替え間隔
const int	SE_RUN_INTERVAL		= 0.4f * 60;	//プレイヤーの移動によるSE発生の間隔
const float	SE_RUN_VOLUME		= 0.3f;			//移動によるSEの音量

// ハンマー
const float HAMMER_ANGLE_X		= DirectX::XMConvertToRadians(180.0f);								//ハンマーの表示角度
const float HAMMER_ANGLE_Y		= DirectX::XMConvertToRadians(0.0f);								//ハンマーの表示角度
const float HAMMER_ANGLE_Z		= DirectX::XMConvertToRadians(0.0f);								//ハンマーの表示角度
const float SWING_ANGLE			= DirectX::XMConvertToRadians(90.0f);	// ハンマーを振る範囲(扇形の角度の大きさ)
const float SWING_TIME_FRAME	= 0.15f * 60;							// ハンマーを振る時間(フレーム単位)
const float ROTATE_RADIUS		= 1.0f;									// ハンマーが回転するプレイヤーからの距離
const float HAMMER_COL_SIZE		= 0.75f;								//ハンマーの当たり判定の大きさ
const float HAMMER_SIZE			= 0.2f;									//ハンマーの大きさ


// 敵キャラ ==================================================

// 共通
const int	MAX_SLIME_NUM = 50;		// スライムの最大生成数
const int	MAX_BOSS_SLIME_NUM = 5;		// ボススライムの最大生成数
const int	START_ENEMY_NUM = 6;		// ゲーム開始時の敵キャラの数
const float ENEMY_MOVE_SPEED = 0.035f;	// 敵の通常移動速度
const float HAMMER_HIT_MOVE_SPEED = 1.0f;		// ハンマーに吹き飛ばされた時のスピード
const int	RANDOM_MOVE_SWITCH_TIME = 3 * 60;	// ランダム移動の方向切り替え

const float SPEED_DOWN_RATIO = 0.6f;		// 吹き飛ぶ際にかかる移動速度の変化の割合    RATIO=>割合
const float MOVE_RESIST = 0.05f;	// 吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値
const float MOVE_DISTANCE_PLAYER = 13.0f;	// プレイヤー追跡移動に切り替える距離
const float SLIME_BASE_RADIUS = 0.5f;		// スライムの基準の大きさ

const int ENEMY_CREATE_INTERVAL = 2 * 60;													// 生成間隔
const int RANDOM_POS = 15;														// 生成座標範囲
const int CREATE_DISTANCE = 10;														// プレイヤーからどれくらい離れた距離に生成するか
const int SLIME_LEVEL1_PER = 45;																// スライム_1の生成確立
const int SLIME_LEVEL2_PER = 35;																// スライム_2の生成確立
const int SLIME_LEVEL3_PER = 10;																// スライム_3の生成確立
const int SLIME_LEVEL_FLAME_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// スライム_フレイムの生成確立
const float MAX_SIZE_EXPLODE = 5.0f;										// スライム4同士の爆発の大きさ
const float EXPLODE_BASE_RATIO = 1.5f;										// スライムの爆発接触での爆発の大きさのベース


// スライム同士の反射の減算値
// ↓1.0fでそのまま
const float COL_SUB_HIT_TO_BIG = 0.1f;			// スライム衝突(小→大)の衝突側の減算値(反射する移動)
const float COL_SUB_STAND_TO_SMALL = 0.8f;			// スライム衝突(小→大)の衝突される側の減算値(衝突された方向)
const float COL_SUB_HIT_TO_SMALL = 0.3f;			// スライム衝突(大→小)の衝突側の減算値(移動方向)
const float COL_SUB_STAND_TO_BIG = 1.2f;			// スライム衝突(大→小)の衝突される側の減算値(衝突された方向)

// サイズ1
const float LEVEL1_SCALE = 1.0f;					// スライム＿レベル１の大きさ(当たり判定含む)
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;		// 移動速度

// サイズ2
const float LEVEL2_SCALE = 2.0f;					// スライム＿レベル２の大きさ(当たり判定含む)
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.9f;	// 移動速度

// サイズ3
const float LEVEL3_SCALE = 3.0f;					// スライム＿レベル３の大きさ(当たり判定含む)
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.7f;	// 移動速度

// サイズ4
const float LEVEL4_SCALE = 5.0f;					// スライム＿レベル４の大きさ(当たり判定含む)
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.5f;	// 移動速度

// フレイムスライム
const float LEVEL_FLAME_SCALE = 1.0f;						// スライム＿フレイムの大きさ(当たり判定含む)
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;	// 移動速度

const int LEVEL_1_SCORE = 10;				// スライム_1のスコア
const int LEVEL_2_SCORE = 30;				// スライム_2のスコア
const int LEVEL_3_SCORE = 100;				// スライム_3のスコア
const int LEVEL_4_SCORE = 500;				// スライム_4のスコア
const int LEVEL_4x4_SCORE = 1000;			// 赤々の爆発のスコア
// ボススライム
#define DEBUG_BOSS	(false)	// デバッグ用にゲーム開始時ボスを生成するかどうか

const float LEVEL_BOSS_1_SCALE = 6.0f;								// ボス１の大きさ
const float LEVEL_BOSS_1_SPEED = ENEMY_MOVE_SPEED * 0.4f;			// ボス１のスピード
const int	BOSS_1_MAX_HP = 10;								// ボス１の最大HP

const float ASSAULT_DISTANCE = 0.2f;								// 突撃反応距離
const int	ASSAULT_COOL_TIME = 10 * 60;							// 突撃クルータイム
const int	ASSAULT_CHARGE_TIME = 2 * 60;							// 突撃チャージ時間
const int	ASSAULT_TIME = 1.0f * 60;						// 突撃総時間
const float ASSAULT_SPEED = LEVEL_BOSS_1_SPEED * 20.0f;		// 突撃時のスピード

const int BOSS_DAMAGE_FLASH_FRAME = 0.1 * 60;					// ダメージ受けた際の点滅フレーム(無敵ではない)
const int BOSS_DAMAGE_FLASH_TOTAL_FRAME = 0.5 * 60;					// ダメージを受けた際の点滅を何フレーム行うか

// 爆発 =====================================================
const int	MAX_EXPLOSION_NUM = 20;			// 最大爆発数
const float EXPAND_QUICK_RATE = 0.2f;			// 膨張加速割合 
const int MAX_BOOOOM_NUM = 10;					//最大boom数
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// スライム_1の爆発総時間
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// スライム_2の爆発総時間
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// スライム_3の爆発総時間
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// スライム_4の爆発総時間
const float LEVEL_BOSS_EXPLODE_TIME = 4.0f * 60.0f;	// スライム_ボスの爆発総時間
const int	DELAY_TIME = 0.2f * 60;		// 遅延秒数

const int	LEVEL_1_EXPLODE_DAMAGE = 1;
const int	LEVEL_2_EXPLODE_DAMAGE = 2;
const int	LEVEL_3_EXPLODE_DAMAGE = 3;
const int	LEVEL_4_EXPLODE_DAMAGE = 4;
// スコア =====================================================
const float SLIME_SCORE_HEIGHT = 4.0f;			//爆発時頭上スコアの表示位置

const int TOTALSCORE_DIGIT = 5;				//トータルスコアの桁数
const int MAX_TOTALSCORE = 99999;			//↑一緒に変えてください（桁数分9を追加）//最大トータアルスコア
const TPos2d<float> TOTALSCORE_POS(1100.0f, 25.0f);			//トータルスコアの位置設定

const DirectX::XMFLOAT2 TOTALSCORE_SIZE(50.0f, -50.0f);		//トータルスコアの表示の大きさ
const DirectX::XMFLOAT2 PLUSSCORE_SIZE(30.0f, -30.0f);		//プラススコアの表示の大きさ
const int ROW_HIGHT = 40;			//スコアを複数個表示時一番上からどのくらい下げるか（PLUSSCORE_SIZE.yの絶対値より大きい数字で）

const DirectX::XMFLOAT2 SMALLDECIMAL_SIZE(15.0f, -15.0f);	//小数点の大きさ
const int MAGNIFICATION = 40;		//倍率表示時の間隔。一番右の数字からどれだけ左にずらすか（小数点を入れるのでそこもケアする）
const TPos2d<float> SMALLDECIMAL_POS(2.0f, -3.0f);//この値で小数点の位置の微調節


// カメラ =====================================================
const TPos3d<float> INIT_POS(0.0f, 2.6f, -3.0f);					// 初期位置

const float INIT_ANGLE = DirectX::XMConvertToRadians(73.0f);       // カメラの角度
const float INIT_NEAR = 1.0f;										// 画面手前初期z値
const float INIT_FAR = 150.0f;									// 画面奥初期z値
const float INIT_RADIUS = 15.0f;									// カメラと注視点との距離(初期値)

// UI =====================================================
// 2D表示
const float VIEW_LEFT = 0.0f;		// 画面左端の座標
const float VIEW_RIGHT = 1280.0f;	// 画面右端の座標（画面横幅）
const float VIEW_BOTTOM = 720.0f;	// 画面下端の座標（画面縦幅）
const float VIEW_TOP = 0.0f;		// 画面上端の座標
const float NEAR_Z = 0.1f;			// 画面に写り始める距離
const float FAR_Z = 10.0f;			// 写せる限界距離

// タイマー =====================================================
const int STAGE_TIME = 180 * 60;	//ステージ制限時間（秒*フレーム）
const TPos2d<float> MINUTE_POS(565.0f, 25.0f);			//分の位置設定
const TPos2d<float> SECOND_TENS_POS(640.0f, 25.0f);	//十の桁秒の位置設定
const TPos2d<float> SECOND_ONE_POS(690.0f, 25.0f);		//一の桁秒の位置設定
const TPos2d<float> TIME_BACKGROUND_POS(630.0f, 25.0f);	//バックグラウンド位置設定
const TPos2d<float> TIME_COLON_POS(602.5f, 25.0f);		//コロンの位置設定
const float TIME_BACK_GROUND_SIZE_X = 200.0f;			//タイマーのバックグランドのXの長さ設定
const float TIME_BACK_GROUND_SIZE_Y = -75.0f;			//タイマーのバックグランドのYの長さ設定
const float TIME_COLON_SIZE_X = 35.0f;					//タイマーのコロンのXの長さ設定
const float TIME_COLON_SIZE_Y = -35.0f;					//タイマーのコロンのYの長さ設定

// ボスゲージ =====================================================
const int BOSS_GAUGE_FULL_TIME = 45 * 60;		//ボスゲージMAXになる時間(何秒出現) * 60フレーム
const int SECOND_EMPTY_BOSS_GAUGE = 75 * 60;		//二体目のボス空ゲージ表す時間 * 60フレーム
const TPos2d<float> BOSS_GAUGE_EMPTY_POS(765.0f, 30.0f);	//ボスゲージ（空）の位置設定
const TPos2d<float> BOSS_GAUGE_FULL_POS(765.0f, 31.5f);	//ボスゲージ（満）の位置設定
const float BOSS_GAUGE_EMPTY_SIZE_X = 60.0f;			//ボスゲージ（空）のXの長さ設定
const float BOSS_GAUGE_EMPTY_SIZE_Y = -60.0f;			//ボスゲージ（空）のYの長さ設定
const float BOSS_GAUGE_FULL_SIZE_X = (6.0f / 7.0f) * BOSS_GAUGE_EMPTY_SIZE_X;			//ボスゲージ（満）のXの長さ設定
const float BOSS_GAUGE_FULL_SIZE_Y = (6.0f / 7.0f) * BOSS_GAUGE_EMPTY_SIZE_Y;			//ボスゲージ（満）のYの長さ設定
const float BOSS_GAUGE_FULL_POS_Y_ADJUST = BOSS_GAUGE_FULL_SIZE_X / 2;		//ボスゲージ増加時、位置表示するための調整量
const float BOSS_GAUGE_FULL_SIZE_Y_ADJUST = BOSS_GAUGE_FULL_SIZE_Y;	//ボスゲージ増加時、サイズ計算用（計算して表示したい比率かける元々のサイズ(100.0f)）
const int FADE_TIME = 5 * 60;							//ボスゲージが溜まってから消える時間


// HP
const float DRAW_POSX = 80.0f;	// テクスチャを表示する位置のX座標
const float DRAW_FIRSTPOSX = 0.9f;		// 1つ目のテクスチャを表示する位置の調節用
const float DRAW_GAP = 1.15f;	// テクスチャ同士の間隔
const float DRAW_POSY = 60.0f;	// テクスチャを表示する位置のY座標
const float DRAW_HEIGHT = 90.0f;	// テクスチャの縦幅
const float DRAW_WIDTH = 90.0f;	// テクスチャの横幅

// BoooomUI =====================================================
const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUIのXの長さ（textureの比率と合わせる）
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUIのYの長さ（textureの比率と合わせる）
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUIサイズのスケール
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUIサイズのスケール

// コンボ =========================================================
const int	MAX_COMBO_NUM = 5;					// 最大同時コンボ数
const TPos2d<float> COMBO_UI_POSITION = { 1025.0f, 600.0f };	// コンボUIの描画位置
const TPos2d<float> COMBO_UI_SIZE = { 70.0f, 130.0f };	// コンボUIの大きさ
const float COMBO_UI_NUM_SPACE = 80.0f;				// 数字の間スペース
const float COMBO_UI_MULTI_DISP_SPACE = 100.0f;				// 同時コンボ描画時の上下の空白
const int COMBO_UI_DISP_DILAY_TIME = 2.0f * 60;			// 残コンボ数表示の秒数

const TPos2d<float> COMBO_UI_BACK_POS = { 1100.0f, 600.0f };	// コンボUIの背景の描画位置
const TPos2d<float> COMBO_UI_BACK_SIZE = { 370.0f, 280.0f };	// コンボUIの背景の大きさ
const TPos2d<float> COMBO_UI_STRING_POS = { 1150.0f, 615.5f };	// コンボUIの文字の描画位置
const TPos2d<float> COMBO_UI_STRING_SIZE = { 180.0f, 100.0f };		// コンボUIの文字の大きさ

// 床 ====================================
const float FLOOR_SCALE_X = 1.1f;
const float FLOOR_SCALE_Z = 1.1f;
const float FLOOR_OFFSET_X = 48.0f * FLOOR_SCALE_X;
const float FLOOR_OFFSET_Z = 48.0f * FLOOR_SCALE_Z;

// タイトル画面 =========================================================
const float TEXTURE_TITLE_TITLE_POSX = SCREEN_WIDTH_ / 2;	// タイトル画像表示位置のX座標
const float TEXTURE_TITLE_TITLE_POSY = 400.0f;				// タイトル画像表示位置のY座標
const float TEXTURE_TITLE_TITLE_WIDTH = 300.0f;				// タイトル画像の横幅
const float TEXTURE_TITLE_TITLE_HEIGHT = 50.0f;				// タイトル画像の縦幅
const float TEXTURE_TITLE_BUTTON_POSX = SCREEN_WIDTH_ / 2;	// タイトル画像表示位置のX座標
const float TEXTURE_TITLE_BUTTON_POSY = 100.0f;				// タイトル画面ボタン押下指示画像表示位置のY座標
const float TEXTURE_TITLE_BUTTON_WIDTH = 300.0f;			// タイトル画面ボタン押下指示画像の横幅
const float TEXTURE_TITLE_BUTTON_HEIGHT = 100.0f;			// タイトル画面ボタン押下指示画像の縦幅

#endif

#endif // !__GAME_PARAMETER_H__




