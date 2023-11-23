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
	・2023/11/21 パラメーター追加(// コンボ数) Sawada

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
const float PLAYER_SIZE			= 1.0f;			// プレイヤーの大きさ
const int	NO_DAMAGE_TIME		= 3 * 60;		// プレイヤーの無敵時間
const int	DAMAGE_FLASH_FRAME	= 0.1f * 60;	// プレイヤーのダメージ点滅の切り替え間隔
const int	SE_RUN_INTERVAL		= 0.4f * 60;	//プレイヤーの移動によるSE発生の間隔
const float	SE_RUN_VOLUME		= 0.3f;			//移動によるSEの音量

// ハンマー
const float SWING_ANGLE			= DirectX::XMConvertToRadians(90.0f);	// ハンマーを振る範囲(扇形の角度の大きさ)
const float SWING_TIME_FRAME	= 0.15f * 60;							// ハンマーを振る時間(フレーム単位)
const float ROTATE_RADIUS		= 1.0f;									// ハンマーが回転するプレイヤーからの距離
const float HAMMER_COL_SIZE		= 0.75f;								//ハンマーの当たり判定の大きさ
const float HAMMER_SIZE			= 1.5f;									//ハンマーの大きさ

// 敵キャラ ==================================================

// 共通
const int	MAX_SLIME_NUM			= 50;		// スライムの最大生成数
const int	START_ENEMY_NUM			= 6;		// ゲーム開始時の敵キャラの数
const float ENEMY_MOVE_SPEED		= 0.035f;	// 敵の通常移動速度
const float HAMMER_HIT_MOVE_SPEED	= 1.0f;		// ハンマーに吹き飛ばされた時のスピード
const int	RANDOM_MOVE_SWITCH_TIME = 3 * 60;	// ランダム移動の方向切り替え

const float SPEED_DOWN_RATIO		= 0.6f;		// 吹き飛ぶ際にかかる移動速度の変化の割合    RATIO=>割合
const float MOVE_RESIST				= 0.05f;	// 吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値
const float MOVE_DISTANCE_PLAYER	= 13.0f;	// プレイヤー追跡移動に切り替える距離
const float SLIME_BASE_RADIUS		= 0.5f;		// スライムの基準の大きさ

const int ENEMY_CREATE_INTERVAL		= 2 * 60;													// 生成間隔
const int RANDOM_POS				= 15;														// 生成座標範囲
const int CREATE_DISTANCE			= 10;														// プレイヤーからどれくらい離れた距離に生成するか
const int SLIME_LEVEL1_PER = 45;																// スライム_1の生成確立
const int SLIME_LEVEL2_PER = 35;																// スライム_2の生成確立
const int SLIME_LEVEL3_PER = 10;																// スライム_3の生成確立
const int SLIME_LEVEL_FLAME_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// スライム_フレイムの生成確立
const float MAX_SIZE_EXPLODE		= 5.0f;										// スライム4同士の爆発の大きさ
const float EXPLODE_BASE_RATIO		= 1.5f;										// スライムの爆発接触での爆発の大きさのベース


// スライム同士の反射の減算値
// ↓1.0fでそのまま
const float COL_SUB_HIT_TO_BIG		= 0.1f;			// スライム衝突(小→大)の衝突側の減算値(反射する移動)
const float COL_SUB_STAND_TO_SMALL	= 0.8f;			// スライム衝突(小→大)の衝突される側の減算値(衝突された方向)
const float COL_SUB_HIT_TO_SMALL	= 0.3f;			// スライム衝突(大→小)の衝突側の減算値(移動方向)
const float COL_SUB_STAND_TO_BIG	= 1.2f;			// スライム衝突(大→小)の衝突される側の減算値(衝突された方向)

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

// 爆発 =====================================================
const int	MAX_EXPLOSION_NUM		= 20;		// 最大爆発数
const float EXPAND_QUICK_RATE		= 0.2f;		// 膨張加速割合 
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// スライム_1の爆発総時間
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// スライム_2の爆発総時間
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// スライム_3の爆発総時間
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// スライム_4の爆発総時間
const int	DELAY_TIME			 = 0.2f * 60;		// 遅延秒数


// カメラ =====================================================
const TPos3d<float> INIT_POS(0.0f, 2.6f, -3.0f);					// 初期位置

const float INIT_ANGLE	= DirectX::XMConvertToRadians(73.0f);       // カメラの角度
const float INIT_NEAR	= 1.0f;										// 画面手前初期z値
const float INIT_FAR	= 150.0f;									// 画面奥初期z値
const float INIT_RADIUS = 15.0f;									// カメラと注視点との距離(初期値)


// タイマー =====================================================
const int STAGE_TIME = 180 * 60;	//ステージ制限時間（秒*フレーム）
const TPos2d<float> MINUTE_POS(565.0f, 25.0f);			//分の位置設定
const TPos2d<float> SECOND_TENS_POS (640.0f, 25.0f);	//十の桁秒の位置設定
const TPos2d<float> SECOND_ONE_POS (690.0f, 25.0f);		//一の桁秒の位置設定
const TPos2d<float> TIME_BACKGROUND_POS (630.0f, 25.0f);	//バックグラウンド位置設定
const TPos2d<float> TIME_COLON_POS (615.0f, 25.0f);		//コロンの位置設定

// コンボ =========================================================
const int	MAX_COMBO_NUM				= 5;					// 最大同時コンボ数
const TPos2d<float> COMBO_UI_POSITION	= { 1100.0f, 600.0f };	// コンボUIの描画位置
const TPos2d<float> COMBO_UI_SIZE		= {   70.0f, 130.0f };	// コンボUIの大きさ
const float COMBO_UI_NUM_SPACE			= 80.0f;				// 数字の間スペース
const float COMBO_UI_MULTI_DISP_SPACE	= 100.0f;				// 同時コンボ描画時の上下の空白
const int COMBO_UI_DISP_DILAY_TIME		= 2.0f * 60;			// 残コンボ数表示の秒数

const TPos2d<float> COMBO_UI_BACK_POS	 = {1100.0f, 600.0f};	// コンボUIの背景の描画位置
const TPos2d<float> COMBO_UI_BACK_SIZE	 = {370.0f, 280.0f};	// コンボUIの背景の大きさ
const TPos2d<float> COMBO_UI_STRING_POS  = {1200.0f, 620.0f};	// コンボUIの文字の描画位置
const TPos2d<float> COMBO_UI_STRING_SIZE = {130.0f, 85.0f};		// コンボUIの文字の大きさ

// 床 ====================================
const float FLOOR_SCALE_X = 1.1f;
const float FLOOR_SCALE_Z = 1.1f;
const float FLOOR_OFFSET_X = 48.0f * FLOOR_SCALE_X;
const float FLOOR_OFFSET_Z = 48.0f * FLOOR_SCALE_Z;

#endif

#endif // !__GAME_PARAMETER_H__




