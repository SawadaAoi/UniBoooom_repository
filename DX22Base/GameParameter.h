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
	・2023/11/24 パラメーター追加(// カメラ) Takagi
	・2023/11/27 パラメーター追加(// 影) nieda
	・2023/11/30 パラメーター編集(// カメラ) Takagi
	・2023/12/01 パラメーター追加(// HP、コンボのアニメーション関連) nieda
	・2023/12/05 パラメーター追加(// ポーズ) Takagi
	・2023/12/06 パラメーター編集(// ポーズ) Takagi
	・2023/12/07 パラメーター削除(// 不必要) Takagi

=========================================== */
#ifndef __GAME_PARAMETER_H__
#define __GAME_PARAMETER_H__

// =============== パラメーター モード =======================
#define MODE_GAME_PARAMETER	(true)

#if MODE_GAME_PARAMETER
// =============== インクルード ===================
#include "Pos2d.h"
#include "Pos3d.h"
#include <DirectXMath.h>


//ゲームシーン================================================
const float BGM_VOLUME = 0.02f;				//シーンゲームの音量
const float SE_HAMMER_HIT_VOLUME = 0.5f;	// スライムを打った時のSEの音量
// 画面サイズ
const int SCREEN_WIDTH_ = 1280;
const int SCREEN_HEIGHT_ = 720;


// プレイヤー ================================================
const float PLAYER_MOVE_SPEED	= 0.12f;			// プレイヤーの移動速度
const int	PLAYER_HP			= 10;			// プレイヤーのHP
const float PLAYER_RADIUS		= 0.12f;			// プレイヤーの当たり判定の大きさ
const float PLAYER_SIZE			= PLAYER_RADIUS * 2.0f;			// プレイヤーの大きさ
const int	NO_DAMAGE_TIME		= 3 * 60;		// プレイヤーの無敵時間
const int	DAMAGE_FLASH_FRAME	= int(0.1f * 60);	// プレイヤーのダメージ点滅の切り替え間隔


// ハンマー
const float SWING_TIME_FRAME	= 0.15f * 60;							// ハンマーを振る時間(フレーム単位)
const float ROTATE_RADIUS		= 2.0f;									// ハンマーが回転するプレイヤーからの距離
const float HAMMER_COL_SIZE		= 2.0f;								//ハンマーの当たり判定の大きさ
const float HAMMER_SIZE			= HAMMER_COL_SIZE * 0.26666f;									//ハンマーの大きさ
const float INTERVAL_INITIAL = 0.2f;								//ハンマー初期間隔
const float SwingSpeed_PLUS = 1.4f;									//ハンマーを一回振るときに乗算される値
const float SwingSpeed_MINUS = 0.99f;									//毎フレームハンマーを振る間隔を短くさせる値
const float SwingSpeed_SIOW = 50.0f;


// 敵キャラ ==================================================

// 共通
const int	MAX_SLIME_NUM = 25;					// スライムの最大生成数
const int	MAX_BOSS_SLIME_NUM = 1;				// ボススライムの最大生成数
const int	START_ENEMY_NUM = 6;				// ゲーム開始時の敵キャラの数
const float ENEMY_MOVE_SPEED = 0.035f;			// 敵の通常移動速度
const float MOVE_DISTANCE_PLAYER = 18.0f;	// プレイヤー追跡移動に切り替える距離
const int ENEMY_CREATE_INTERVAL		= int(1.0f * 60);			// 生成間隔
const int RANDOM_POS = 15;										// 生成座標範囲
const int CREATE_DISTANCE = 19;									// プレイヤーからどれくらい離れた距離に生成するか
const int SLIME_LEVEL1_PER = 65;								// スライム_1の生成確立
const int SLIME_LEVEL2_PER = 20;								// スライム_2の生成確立
const int SLIME_LEVEL3_PER = 5;									// スライム_3の生成確立
const int SLIME_LEVEL_FLAME_PER = 5;							// スライム_フレイムの生成確率
const int SLIME_LEVEL_HEAL_PER = 5;								// スライム_ヒールの生成確率
const float MAX_SIZE_EXPLODE		= 6.0f;						// スライム4同士の爆発の大きさ
const float EXPLODE_BASE_RATIO		= 1.5f;						// スライムの爆発接触での爆発の大きさのベース
const float ESCAPE_DISTANCE			= 15.0f;					// 爆発がこの距離より近かったら逃げる範囲
const int ESCAPE_TIME				= int(60 * 0.8f);			// この間隔で逃げる処理が終了する

// スライム同士の反射の減算値
const float LEAVE_DISTANCE = 29.0f;					// これ以上離れたら対角線上に移動する

// サイズ1
const float LEVEL1_SCALE = 1.0f;					// スライム＿レベル１の大きさ(当たり判定含む)
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;		// 移動速度

// サイズ2
const float LEVEL2_SCALE = 2.0f;					// スライム＿レベル２の大きさ(当たり判定含む)
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.9f;	// 移動速度

// サイズ3
const float LEVEL3_SCALE = 4.5f;					// スライム＿レベル３の大きさ(当たり判定含む)
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.7f;	// 移動速度
const float LEVEL3_STOP_RANGE = DirectX::XMConvertToRadians(20.0f);	// スライムが止まる角度の範囲
const int	LEVEL2_ATTACK_INTERVAL = int(60 * 4.0f);		// 攻撃終了から次の攻撃までの間隔
const int	LEVEL2_ATTACK_CHARGE_CNT = int(60 * 1.0f);	// 突進するまでのため時間
const int	LEVEL2_ATTACK_TACKLE_CNT = int(60 * 0.45f);	// 突進している時間
const float	LEVEL2_TACKLE_SPEED = 0.2f;					// 突進の速度

// サイズ4
const float LEVEL4_SCALE = 5.5f;					// スライム＿レベル４の大きさ(当たり判定含む)
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.5f;	// 移動速度
const int	LEVEL4_ATTACK = 2;						// 攻撃力

// フレイムスライム
const float LEVEL_FLAME_SCALE = 1.5f;						// スライム＿フレイムの大きさ(当たり判定含む)
const float LEVEL_FLAME_SPEED = ENEMY_MOVE_SPEED * 0.2f;	// 移動速度
const int	LEVEL_FLAME_ATTACK = 1;							// 攻撃力

// ヒールスライム
const float LEVEL_HEAL_SCALE = 1.5f;						// スライム＿ヒールの大きさ(当たり判定含む)
const float LEVEL_HEAL_SPEED = ENEMY_MOVE_SPEED * 0.3f;		// 移動速度
const int	LEVEL_HEAL_ATTACK = 1;							// 攻撃力 （いる？

// ボススライム
const float LEVEL_BOSS_1_SCALE = 6.0f;								// ボス１の大きさ
const float LEVEL_BOSS_1_SPEED = ENEMY_MOVE_SPEED * 0.4f;			// ボス１のスピード
const int	BOSS_1_MAX_HP = 10;								// ボス１の最大HP
const int	BOSS_1_ATTACK = 2;								// ボス１の攻撃力
const float SLIME_HP_HEIGHT = 5.0f;							//ボスの体力表示位置（Y）
const float ASSAULT_DISTANCE = 0.2f;								// 突撃反応距離
const int	ASSAULT_COOL_TIME = 10 * 60;							// 突撃クルータイム
const int	ASSAULT_CHARGE_TIME = int(2 * 60);						// 突撃チャージ時間
const int	ASSAULT_TIME = int(1.0f * 60);						// 突撃総時間
const float ASSAULT_SPEED = LEVEL_BOSS_1_SPEED * 20.0f;		// 突撃時のスピード
const float BOSS_HP_SIZEX = 0.3f;		// 体力１分の大きさ（X）
const float BOSS_HP_SIZEY = 0.5f;		// 体力１分の大きさ（Y）
const float BOSS_HPFRAME_SIZEX = 0.2f;	// 体力ゲージよりどれだけ大きいか（X）
const float BOSS_HPFRAME_SIZEY = 0.2f;	// 体力ゲージよりどれだけ大きいか（Y）
const float BOSS_HP_POSX = 8.6f;		// 体力バー（減る方）の位置
const int BOSS_DAMAGE_FLASH_FRAME = int(0.1f * 60);					// ダメージ受けた際の点滅フレーム(無敵ではない)
const int BOSS_DAMAGE_FLASH_TOTAL_FRAME = int(0.5f * 60);			// ダメージを受けた際の点滅を何フレーム行うか
const float ADD_CREATE_BOSS_POS_Z = 20.0f;							// ボスの生成位置(プレイヤーの生成位置に対してどれだけ奥に出すか)


// 爆発 =====================================================
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// スライム_1の爆発総時間
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// スライム_2の爆発総時間
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// スライム_3の爆発総時間
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// スライム_4の爆発総時間
const float LEVEL_BOSS_EXPLODE_TIME = 4.0f * 60.0f;	// スライム_ボスの爆発総時間
const int	DELAY_TIME = int(0.2f * 60);			// 遅延秒数


// スライム時間差生成 =====================================================
const enum TIME_STATE
{
	STATE_FIRST = 0,
	STATE_SECOND,
	STATE_THIRD,
	STATE_MAX,
};


// タイマー =====================================================
const float SLM_PARAM_CHANGE_TIME[STATE_MAX]	= { 60.0f, 120.0f, 180.0f };	// 経過時間の秒数
const int	SLM_CREATE_NUM[STATE_MAX]			= { 20, 25, MAX_SLIME_NUM };	// 最大生成数
const float SLM_CREATE_INTERVAL_TIME[STATE_MAX] = { 1.0f, 1.5f, 1.5f };			// 生成間隔
const float SLM_MOVE_ADD_SPEED[STATE_MAX]		= { 1.0f, 1.1f, 1.2f };			// 移動スピード


// ボスゲージ =====================================================
typedef struct
{
	float startTime;	// 開始時間(秒)
	float maxTime;		// ゲージ経過最大時間(秒)

}BossGaugeSetParam;

const BossGaugeSetParam BOSS_GAUGE_S1[2] = { {0, 45},{75, 45} };	// ステージ1のボスゲージ設定

const int FADE_TIME = 5 * 60;										// ボスゲージが溜まってから消える時間
 

// 床 ====================================
const float FLOOR_SCALE_X = 3.1f;
const float FLOOR_SCALE_Z = 3.1f;


// タイトル画面 =========================================================
const float TEXTURE_TITLE_TITLE_POSX = SCREEN_WIDTH_ / 2;	// タイトル画像表示位置のX座標
const float TEXTURE_TITLE_TITLE_POSY = 400.0f;				// タイトル画像表示位置のY座標
const float TEXTURE_TITLE_TITLE_WIDTH = 300.0f;				// タイトル画像の横幅
const float TEXTURE_TITLE_TITLE_HEIGHT = 50.0f;				// タイトル画像の縦幅
const float TEXTURE_TITLE_BUTTON_POSX = SCREEN_WIDTH_ / 2;	// タイトル画像表示位置のX座標
const float TEXTURE_TITLE_BUTTON_POSY = 100.0f;				// タイトル画面ボタン押下指示画像表示位置のY座標
const float TEXTURE_TITLE_BUTTON_WIDTH = 300.0f;			// タイトル画面ボタン押下指示画像の横幅
const float TEXTURE_TITLE_BUTTON_HEIGHT = 100.0f;			// タイトル画面ボタン押下指示画像の縦幅


// ヒットストップ =========================================================
const int FRAME_STOP_SOFT = 2;		//ストップ：軽　のフレーム数	// 現在使用している物
const int FRAME_STOP_NORMAL = 4;	//ストップ：中　のフレーム数


// ゲーム開始時スタート表示 ==================================================
const float TIME_WAIT_START = 75;				// ゲーム開始合図表示待ち時間
const int SWITCH_ANIM_START = 1;				// スタートアニメーション切り替え時間
const int START_SCALE_X = SCREEN_WIDTH_;		// UIの横幅
const int START_SCALE_Y = SCREEN_HEIGHT_;		// UIの縦幅
const float START_POS_X = SCREEN_WIDTH_ / 2;	// 表示位置のX座標
const float START_POS_Y = SCREEN_HEIGHT_ / 2;	// 表示位置のY座標


// ゲームクリア、ゲームオーバー表示 ==================================================
const int SWITCH_ANIM_CLEAR = 1;				// 成功アニメーション切り替え時間
const int SWITCH_ANIM_OVER = 1;					// 失敗アニメーション切り替え時間
const int STATE_SCALE_X = SCREEN_WIDTH_;		// UIの横幅
const int STATE_SCALE_Y = SCREEN_HEIGHT_;		// UIの縦幅
const float STATE_POS_X = SCREEN_WIDTH_ / 2;	// 表示位置のX座標
const float STATE_POS_Y = SCREEN_HEIGHT_ / 2;	// 表示位置のY座標


// ポーズ ====================================================================
const float COMMAND_SPACE_HALF = 85.0f;	//コマンド同士の縦の間
const float CHARA_Y = 620.0f;			//ポーズ表記部中心y位置
const float CHARA_SPACE = 85.0f;		//ポーズ表記の横の間
const float CHARA_WIDTH = 100.0f;		//ポーズ表記横幅
const float CHARA_HEIGHT = 100.0f;		//ポーズ表記縦幅
const float COMMAND_WIDTH = 360.0f;		//コマンド縦幅
const float COMMAND_HEIGHT = 78.0f;		//コマンド横幅

#endif // !MODE_GAME_PARAMETER
#endif // !__GAME_PARAMETER_H__