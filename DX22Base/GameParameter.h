/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ゲームパラメーター調整用ヘッダ
	---------------------------------------
	GameParameter.h

	作成者	鈴村朋也

	変更履歴
	・2023/11/11 ヘッダ作成 suzumura


=========================================== */
#ifndef __GAME_PARAMETER_H__
#define __GAME_PARAMETER_H__

// =============== パラメーター モード =======================
#define MODE_GAME_PARAMETER	(true)

#if MODE_GAME_PARAMETER

// プレイヤー ================================================
const float PLAYER_MOVE_SPEED	= 0.1f;		// プレイヤーの移動速度
const int	PLAYER_HP			= 5;		// プレイヤーのHP
const float PLAYER_RADIUS		= 0.1f;		// プレイヤーの当たり判定の大きさ
const float PLAYER_SIZE			= 1.0f;		// プレイヤーの大きさ
const int	NO_DAMAGE_TIME		= 3 * 60;	// プレイヤーの無敵時間
const int	DAMAGE_FLASH_FRAME	= 0.1 * 60;	// プレイヤーのダメージ点滅の切り替え間隔

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


const int ENEMY_CREATE_INTERVAL		= 2 * 60;									// 生成間隔
const int RANDOM_POS				= 15;										// 生成座標範囲
const int CREATE_DISTANCE			= 10;										// プレイヤーからどれくらい離れた距離に生成するか
const int SLIME_LEVEL1_PER			= 50;										// スライム_1の生成確立
const int SLIME_LEVEL2_PER			= 30;										// スライム_2の生成確立
const int SLIME_LEVEL3_PER			= 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER;// スライム_3の生成確立
const float MAX_SIZE_EXPLODE		= 8.0f;										// スライム4同士の爆発の大きさ
const float EXPLODE_BASE_RATIO		= 2.0f;										// スライムの爆発接触での爆発の大きさのベース

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
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.9;	// 移動速度

// サイズ3
const float LEVEL3_SCALE = 3.0f;					// スライム＿レベル３の大きさ(当たり判定含む)
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.7;	// 移動速度

// サイズ4
const float LEVEL4_SCALE = 5.0f;					// スライム＿レベル４の大きさ(当たり判定含む)
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.5;	// 移動速度


// 爆発 =====================================================
const int	MAX_EXPLOSION_NUM		= 20;				// 最大爆発数
const float MAX_DISPLAY_TIME		= 2.0f * 60;		// 爆発持続秒数
const float ONE_SECOND_FRAME		= 1.0f * 30;		// 大きくなるまでの秒数


// カメラ =====================================================
const TPos3d<float> INIT_POS(0.0f, 2.6f, -3.0f);					// 初期位置

const float INIT_ANGLE	= DirectX::XMConvertToRadians(73.0f);       // カメラの角度
const float INIT_NEAR	= 1.0f;										// 画面手前初期z値
const float INIT_FAR	= 150.0f;									// 画面奥初期z値
const float INIT_RADIUS = 15.0f;									// カメラと注視点との距離(初期値)





#endif

#endif // !__GAME_PARAMETER_H__




