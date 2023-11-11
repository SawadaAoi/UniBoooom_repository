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

// =============== デファインモード =======================
#define MODE_DEFINE	(true)

//--.h
//===ExplosionManager.h======
const int MAX_EXPLOSION_NUM = 20;    //最大爆発数

//===SlimeBase.h=======
const float ENEMY_MOVE_SPEED = 0.01f;    //敵の移動速度

//===SlimeManager.h======
const int MAX_SLIME = 30;    //スライムの最大生成数


//--.cpp
//===Explosion.cpp=======
const float MAX_DISPLAY_TIME = 60 * 3.0f;    // 爆発持続秒数
const float ONE_SECOND_FRAME = 60;           // 大きくなるまでの秒数

//===Hammer.cpp=======
const float ANGULAR_ANGLE = 0.1f;        //毎フレーム移動する角度量
const float ROTATE_RADIUS = 1.0f;        //ハンマーが回転するプレイヤーからの距離
const float HAMMER_SIZE = 1.0f;          //ハンマーの当たり判定の大きさ

//===Player.cpp======
const float PLAYERMOVE(0.1f);		//プレイヤーの移動速度
const int PLAYER_HP = 5;			//プレイヤーのHP
const float PLAYER_RADIUS = 0.5f;   //プレイヤーの当たり判定の大きさ
const int NO_DAMAGE_TIME = 3 * 60;  //プレイヤーの無敵時間

//===SlimeBase.cpp======
const float SPEED_DOWN_RATIO = 0.6f;		//スライムが接触して吹き飛ぶ際にかかる移動速度の変化の割合    RATIO=>割合
const float MOVE_RESIST = 0.1f;				//吹き飛び移動中のスライムの移動速度に毎フレームかかる減算数値
const float REFLECT_RATIO = 0.1f;			//スライムがスライムを吹き飛ばした際に吹き飛ばした側のスライムの移動量を変える割合
const float MOVE_DISTANCE_PLAYER = 20.0f;   // プレイヤー追跡移動に切り替える距離
const float SLIME_BASE_RADIUS = 0.5f;		// スライムの基準の大きさ

//===Slime_01.cpp======
const float LEVEL1_SCALE = 1.0f;
const float LEVEL1_SPEED = ENEMY_MOVE_SPEED;	

//===Slime_02.cpp======
const float LEVEL2_SCALE = 2.0f;
const float LEVEL2_SPEED = ENEMY_MOVE_SPEED * 0.95;

//===Slime_03.cpp======
const float LEVEL3_SCALE = 3.0f;
const float LEVEL3_SPEED = ENEMY_MOVE_SPEED * 0.90;

//===Slime_04.cpp======
const float LEVEL4_SCALE = 4.0f;
const float LEVEL4_SPEED = ENEMY_MOVE_SPEED * 0.85;

//===SlimeManager.cpp======
const int ENEMY_GENERATE_INTERVAL = 3 * 60;		// 生成間隔
const int RANDOM_POS_MIN = -15;					// 生成座標範囲下限(x,z共通)
const int RANDOM_POS_MAX = 15;					// 生成座標範囲上限(x,z共通)
const int CREATE_DISTANCE = 10;					// 生成距離最小値
const int SLIME_LEVEL1_PER = 50;                // スライム_1の生成確立
const int SLIME_LEVEL2_PER = 30;                // スライム_2の生成確立
const int SLIME_LEVEL3_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER;    // スライム_3の生成確立
const float MAX_SIZE_EXPLODE = 5.0f;		// スライム4同士の爆発の大きさ
const float EXPLODE_BASE_RATIO = 1.0f;		// スライムの爆発接触での爆発の大きさのベース


#endif // !__GAME_PARAMETER_H__




