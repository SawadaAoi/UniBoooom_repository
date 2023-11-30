/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムマネージャー クラス実装
   ---------------------------------------
   SlimeManager.cpp

   作成者：鈴村 朋也

   変更履歴
	・2023/11/05 スライムマネージャークラス作成 suzumura
	・2023/11/08 スライム同士が接触した際の分岐処理を作成(分岐した後に行う処理は未実装　※TODOをつけておいた)の yamashita
	・2023/11/08 結合処理を作成(結合後の生成処理は未実装 Slime_2～Slime_4がまだ無いから) yamashita
	・2023/11/09 生成処理、変数の変更 sawada
	・2023/11/09 コメントの追加 sawada
	・2023/11/11 parameter用ヘッダ追加 suzumura
	・2023/11/11 スライム同士が重ならない関数を追加 yamashita
	・2023/11/13 スライムレベルごとに爆発時間を設定できるように変更 Suzumura
	・2023/11/14 炎スライムの処理を実装 Suzumura
	・2023/11/14 SphereInfoの変更に対応 Takagi
	・2023/11/15 各モデルの読み込みをbaseから移動 yamashita
	・2023/11/15 各モデルの読み込みを関数化 yamashita
	・2023/11/20 ボス用の配列を追加
	・2023/11/21 ボス用の当たり判定時の処理(HitSlimeBossBranch...etc)を追加
	・2023/11/21 ボス用の通常時の処理(PreventSlimeBossOverlap...etc)を追加
	・2023/11/21 BoooomUi表示する関数を呼び出す Tei
	・2023/11/23 スライムの生成位置をプレイヤー中心に変更 yamashita
	・2023/11/23 スライムの生成位置が前回の生成位置から一定以上離れるように変更	yamashita
	・2023/11/23 スライムがプレイヤーから一定以上離れると対角線上に移動するように変更 yamashita
	・2023/11/26 ボス生成用関数追加	Sawada
	・2023/11/26 スライムと爆発の距離を調べ逃げるか判定する関数を作成 yamashita
	・2023/11/27 赤赤の爆発生成時にヒットストップと画面揺れするように修正	Sawada
	・2023/11/29 画面揺れを横強→縦強に変更 takagi
	・2023/11/29 プレイヤーのポインタを取得 yamashita
	・2023/11/30 モデルの読み込みをMaya準拠からDirectX準拠に変更 yamashita
	・2023/11/30 振動する箇所増設・ヒットストップ除去・火スライムと赤スライム衝突時に振動強化 takagi

=========================================== */

// =============== インクルード ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include "Slime_2.h"
#include "Slime_3.h"
#include "Slime_4.h"
#include "Slime_Flame.h"
#include "Slime_Boss_1.h"
#include "Input.h"		//後で消す
#include "GameParameter.h"		//定数定義用ヘッダー
#include "HitStop.h"

#include <stdlib.h>

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
#define DEBUG_BOSS	(false)						// デバッグ用にゲーム開始時ボスを生成するかどうか

const int ENEMY_CREATE_INTERVAL	= 3 * 60;		// 生成間隔
const int RANDOM_POS			= 15;			// 生成座標範囲
const int CREATE_DISTANCE		= 10;			// 生成距離最小値
const int SLIME_LEVEL1_PER		= 10;			// スライム_1の生成確立
const int SLIME_LEVEL2_PER		= 15;			// スライム_2の生成確立
const int SLIME_LEVEL3_PER		= 10;			// スライム_3の生成確立
const int SLIME_LEVEL_FLAME_PER	= 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// スライム_フレイムの生成確立

const int START_ENEMY_NUM		= 10;			// ゲーム開始時の敵キャラの数

// ↓1.0fでそのまま
const float COL_SUB_HIT_TO_BIG = 0.7f;				// スライム衝突(小→大)の衝突側の減算値(反射する移動)
const float COL_SUB_STAND_TO_SMALL = 0.3f;			// スライム衝突(小→大)の衝突される側の減算値(衝突された方向)
const float COL_SUB_HIT_TO_SMALL = 0.3f;			// スライム衝突(大→小)の衝突側の減算値(移動方向)
const float COL_SUB_STAND_TO_BIG = 1.2f;			// スライム衝突(大→小)の衝突される側の減算値(衝突された方向)
const float LEAVE_DISTANCE = 20.0f;					// これ以上離れたら対角線上に移動する

#endif

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlimeManager::CSlimeManager(CPlayer* pPlayer)
	: m_CreateCnt(0)
	, m_pVS(nullptr)
	, m_pBlueModel(nullptr)
	, m_pGreenModel(nullptr)
	, m_pYellowModel(nullptr)
	, m_pRedModel(nullptr)
	, m_pFlameModel(nullptr)
	, m_pBossModel(nullptr)
	, m_pSEHitSlime(nullptr)
	, m_pSEUnion(nullptr)
	, m_pSEHitSlimeSpeaker(nullptr)
	, m_pSEUnionSpeaker(nullptr)
	, m_oldCreatePos{ 0.0f,0.0f,0.0f }
	, m_pPlayer(pPlayer)
	, m_pExpMng(nullptr)
{
	//スライムのモデルと頂点シェーダーの読み込み
	LoadModel();

	// スライム初期化
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		m_pSlime[i] = nullptr;
	}
	// ボススライム初期化
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		m_pBoss[i] = nullptr;
	}

	// ゲーム開始時に敵キャラを生成する
	for (int i = 0; i < START_ENEMY_NUM; i++)
	{
		int ranLv = rand() % 3 + 1;		// 生成するスライムのレベルを乱数で指定
		Create((E_SLIME_LEVEL)ranLv);	// 生成処理
	}

#if DEBUG_BOSS
	// 開始時ボス生成
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		// スライムのuseを検索
		if (m_pBoss[i] != nullptr) continue;
		m_pBoss[i] = new CSlime_Boss_1(TPos3d<float>(5.0f,0.0f,3.0f), m_pVS, m_pBossModel);	//動的生成

		break;
	}
#endif
	

	//サウンドファイルの読み込み
	m_pSEHitSlime = CSound::LoadSound("Assets/Sound/SE/SlimeHitSlime.mp3");		//ハンマーを振った時のSEの読み込み
	m_pSEUnion = CSound::LoadSound("Assets/Sound/SE/Union.mp3");		//スライムがくっついた時ののSEの読み込み


}

/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlimeManager::~CSlimeManager()
{
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pFlameModel);
	SAFE_DELETE(m_pRedModel);
	SAFE_DELETE(m_pYellowModel);
	SAFE_DELETE(m_pGreenModel);
	SAFE_DELETE(m_pBlueModel);
	SAFE_DELETE(m_pBossModel);

	// スライム削除
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		SAFE_DELETE(m_pSlime[i]);
	}

	// ボススライム削除
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		SAFE_DELETE(m_pBoss[i]);
	}

}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeManager::Update(CExplosionManager* pExpMng)
{
	CheckEscape();	//Updateの前に近くに爆発があるか確認する

	// スライム更新
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Update(m_pPlayer->GetTransform());

	}

	OutOfRange();	//スライムがプレイヤーから一定距離離れたら対角線に移動

	// ボススライム更新
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		if (m_pBoss[i] == nullptr) continue;
		m_pBoss[i]->Update(m_pPlayer->GetTransform());

	}


	m_CreateCnt++;
	if(ENEMY_CREATE_INTERVAL<= m_CreateCnt)
	{
		// 敵 生成
		Create(GetRandomLevel());	//スライムのレベルをランダムに選んで生成する
		m_CreateCnt = 0;				//カウントをリセット
	}
}

/* ========================================
	描画処理関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeManager::Draw()
{
	//"スライム"描画
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Draw(m_pCamera);
	}
				
	// ボススライム更新
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		if (m_pBoss[i] == nullptr) continue;
		m_pBoss[i]->Draw(m_pCamera);

	}
}


/* ========================================
	スライム生成関数
	-------------------------------------
	内容：スライムの生成
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeManager::Create(E_SLIME_LEVEL level)
{
	TPos3d<float> CreatePos;	// スライムの生成位置

	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		// スライムのuseを検索
		if (m_pSlime[i] != nullptr) continue;

		// 適切な座標が出るまで繰り返す
		while (true)
		{
			// 乱数をセットする
			CreatePos.x = float(GetRandom(int(m_pPlayer->GetPos().x - RANDOM_POS), int(m_pPlayer->GetPos().x + RANDOM_POS)));	//乱数取得
			CreatePos.z = float(GetRandom(int(m_pPlayer->GetPos().z - RANDOM_POS), int(m_pPlayer->GetPos().z + RANDOM_POS)));
			CreatePos.y = 0;

			float PlayerCreateDistance = CreatePos.Distance(m_pPlayer->GetPos());	// 生成座標のプレイヤーとの距離
			float oldCreateDistance = CreatePos.Distance(m_oldCreatePos);	// 生成座標のプレイヤーとの距離

			// プレイヤーから一定の距離離れていれば抜ける
			if (PlayerCreateDistance >= CREATE_DISTANCE && oldCreateDistance >= CREATE_DISTANCE) break;	
		}

		m_oldCreatePos = CreatePos;	//生成座標を保持
		
		switch (level)
		{
		case LEVEL_1:
			m_pSlime[i] = new CSlime_1(CreatePos,m_pVS,m_pBlueModel);	// 動的生成
			break;
		case LEVEL_2:
			m_pSlime[i] = new CSlime_2(CreatePos, m_pVS, m_pGreenModel);	// 動的生成
			break;
		case LEVEL_3:
			m_pSlime[i] = new CSlime_3(CreatePos, m_pVS, m_pYellowModel);	// 動的生成
			break;
		case LEVEL_4:
			m_pSlime[i] = new CSlime_4(CreatePos, m_pVS, m_pRedModel);	// 動的生成
			break;
		case LEVEL_FLAME:
			m_pSlime[i] = new CSlime_Flame(CreatePos,m_pVS,m_pFlameModel);	// 動的生成
			break;

		}

		m_pSlime[i]->SetCamera(m_pCamera);	//カメラをセット
		break;						// 生成したら終了
		
	}
}

/* ========================================
	ボススライム生成関数
	-------------------------------------
	内容：ボススライムの生成
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeManager::CreateBoss()
{
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		// スライムのuseを検索
		if (m_pBoss[i] != nullptr) continue;
		m_pBoss[i] = new CSlime_Boss_1(TPos3d<float>(0.0f, 0.0f, 0.0f), m_pVS, m_pBossModel);	//動的生成(取り合えず位置は仮)

		break;
	}
}

/* ========================================
	スライム接触分岐関数
	----------------------------------------
	内容：スライム同士が接触した際に分岐して正しい処理を実行する
	----------------------------------------
	引数1：衝突するスライムの配列番号
	引数2：衝突されたスライムの配列番号
	引数3：爆発マネージャー
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::HitBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel, standSlimeLevel;				// レベル
	tagTransform3d hitSlimeTransform, standSlimeTransform;		//ワールド座標系
	float hitSlimeSpeed;						// 移動スピード
	float travelAngle, reflectionAngle;							// 移動方向

	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();		// 衝突するスライムのサイズを取得
	hitSlimeTransform = m_pSlime[HitSlimeNum]->GetTransform();	// 衝突するスライムのワールド座標情報を取得
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();			// 衝突するスライムの速度を取得

	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();	// 衝突されたスライムのサイズを取得
	standSlimeTransform = m_pSlime[StandSlimeNum]->GetTransform();	// 衝突するスライムのワールド座標情報を取得

	travelAngle = hitSlimeTransform.Angle(standSlimeTransform);		// 衝突する側の進行方向
	reflectionAngle = standSlimeTransform.Angle(hitSlimeTransform);	// 衝突する側の逆方向(反射)
	TPos3d<float> pos = m_pSlime[StandSlimeNum]->GetPos();        // 衝突されたスライムの位置を確保
	
	//-- フレイムスライムヒット処理 呼び出し
	if (HitFlameBranch(HitSlimeNum, StandSlimeNum, pExpMng)) 
	{
		return; //フレイムスライム接触が行われたなら処理が重ならないようにreturnする
	}
	
	//-- ノーマルスライムヒット処理
	// 衝突するスライムが小さい場合(小→大)
	if (hitSlimeLevel < standSlimeLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_BIG, reflectionAngle);	// 衝突するスライムに吹き飛び移動処理
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_SMALL, travelAngle);	// 衝突されたスライムに吹き飛び移動処理
		m_pSEHitSlimeSpeaker = CSound::PlaySound(m_pSEHitSlime);									// SEの再生
	}
	
	// 衝突するスライムが大きい場合(大→小)
	else if (hitSlimeLevel > standSlimeLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);		// 衝突するスライムに吹き飛び移動処理
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_BIG, travelAngle);	// 衝突されたスライムに吹き飛び移動処理
		m_pSEHitSlimeSpeaker = CSound::PlaySound(m_pSEHitSlime);									// SEの再生
	}
	//スライムのサイズが同じだった場合
	else
	{

		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// 衝突するスライムを削除
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// 衝突されたスライムを削除

		if (hitSlimeLevel == MAX_LEVEL)	//スライムのサイズが最大の時
		{
			//スライム爆発処理
			pExpMng->Create(pos, MAX_SIZE_EXPLODE * EXPLODE_BASE_RATIO, LEVEL_4_EXPLODE_TIME, LEVEL_4_EXPLODE_DAMAGE, E_SLIME_LEVEL::LEVEL_4x4);	//衝突されたスライムの位置でレベル４爆発
			m_pScoreOHMng->DisplayOverheadScore(pos, LEVEL_4_SCORE * 2, SLIME_SCORE_HEIGHT);
			pExpMng->CreateUI(pos, LEVEL_4_EXPLODE_TIME);		//レベル４爆発した位置boooomUI表示

			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
		}
		else	//最大サイズじゃない場合は1段階大きいスライムを生成する
		{
			UnionSlime(hitSlimeLevel,pos);	//スライムの結合処理
		}
	}
}

/* ========================================
	フレイムスライム接触分岐関数
	----------------------------------------
	内容：フレイムスライムが接触した際、正しい処理を実行する
	----------------------------------------
	引数1：衝突するスライムの配列番号
	引数2：衝突されたスライムの配列番号
	引数3：爆発マネージャー
	----------------------------------------
	戻値：なし
======================================== */
bool CSlimeManager::HitFlameBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel, standSlimeLevel;						// レベル
	float hitSlimeSpeed;												// 移動スピード
	float travelAngle;													// 移動方向
	tagTransform3d hitSlimeTransform, standSlimeTransform;				//ワールド行列に関わる情報

	TTriType<float> hitSlimeSize = m_pSlime[HitSlimeNum]->GetScale();		// 衝突先のスライムのサイズを確保
	TTriType<float> standSlimeSize = m_pSlime[StandSlimeNum]->GetScale();	// 吹っ飛んできたスライムのサイズを確保

	hitSlimeTransform = m_pSlime[HitSlimeNum]->GetTransform();				// 衝突するのワールド行列に関わる情報
	standSlimeTransform = m_pSlime[StandSlimeNum]->GetTransform();			// 衝突されたワールド行列に関わる情報
	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();					// 衝突するスライムのサイズを取得
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();						// 衝突するスライムの速度を取得
	travelAngle = hitSlimeTransform.Angle(standSlimeTransform);				// 衝突する側の進行方向
	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();				// 衝突されたスライムのサイズを取得

	//-- フレイムスライムヒット処理
	// フレイム　→　フレイム
	if (hitSlimeLevel == LEVEL_FLAME && standSlimeLevel == LEVEL_FLAME)
	{
		// 『衝突するスライムが大きい場合(大→小)』と同じ動きをさせる
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);		// 衝突するスライムに吹き飛び移動処理
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_BIG, travelAngle);	// 衝突されたスライムに吹き飛び移動処理
		m_pSEHitSlimeSpeaker = CSound::PlaySound(m_pSEHitSlime);									//SEの再生

		return true;
	}
	// フレイム　→　ノーマル
	else if (hitSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(standSlimeLevel, standSlimeTransform.fPos,standSlimeSize);	//スライムのレベルによって爆発の時間とサイズを分岐
		m_pScoreOHMng->DisplayOverheadScore(standSlimeTransform.fPos, standSlimeLevel);

		//赤スライム(Stand)と激突したときだけ爆発の振動を大きくする
		if (typeid(CSlime_4) == typeid(*m_pSlime[HitSlimeNum]))
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
		}
		else
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_WEAK);
		}

		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// 衝突するスライムを削除
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// 衝突されたスライムを削除

		return true;
	}
	// ノーマル　→　フレイム
	else if (standSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(hitSlimeLevel, hitSlimeTransform.fPos, hitSlimeSize);	//スライムのレベルによって爆発の時間とサイズを分岐
		m_pScoreOHMng->DisplayOverheadScore(hitSlimeTransform.fPos, hitSlimeLevel);

		//赤スライム(Hit)と激突したときだけ爆発の振動を大きくする
		if (typeid(CSlime_4) == typeid(*m_pSlime[HitSlimeNum]))
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
		}
		else
		{
			m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG | CCamera::E_BIT_FLAG_VIBRATION_SIDE_WEAK);
		}

		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// 衝突するスライムを削除
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// 衝突されたスライムを削除

		return true;

	}
	return false;
}

/* ========================================
	結合関数
	----------------------------------------
	内容：1段階上のスライムを生成する関数
	----------------------------------------
	引数1：スライムのレベル
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::UnionSlime(E_SLIME_LEVEL level ,TPos3d<float> pos)
{
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		if (m_pSlime[i] != nullptr) { continue; }

		switch (level)
		{
		case LEVEL_1:
			//サイズ2のスライムを生成
			m_pSlime[i] = new CSlime_2(pos, m_pVS, m_pGreenModel);
			break;
		case LEVEL_2:
			//サイズ3のスライムを生成
			m_pSlime[i] = new CSlime_3(pos, m_pVS, m_pYellowModel);
			break;
		case LEVEL_3:
			//サイズ4のスライムを生成
			m_pSlime[i] = new CSlime_4(pos, m_pVS, m_pRedModel);
			break;
		}

		m_pSlime[i]->SetCamera(m_pCamera);	//カメラをセット
		m_pSEUnionSpeaker = CSound::PlaySound(m_pSEUnion);	//SEの再生

		break;
	}
}

/* ========================================
	爆発接触関数
	----------------------------------------
	内容：画面上の爆発にスライムが接触した時の処理
	----------------------------------------
	引数1：爆発するスライムの配列番号
	引数2：爆発マネージャーのポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::TouchExplosion(int DelSlime, CExplosionManager * pExpMng, int comboNum)
{
	TPos3d<float> pos(m_pSlime[DelSlime]->GetPos());			// 衝突先のスライムの位置を確保
	E_SLIME_LEVEL level = m_pSlime[DelSlime]->GetSlimeLevel();	// 衝突先のスライムのレベルを確保
	TTriType<float> size = m_pSlime[DelSlime]->GetScale();		// 衝突先のスライムサイズを確保

	pExpMng->SwitchExplode(level, pos, size, comboNum);
	m_pScoreOHMng->DisplayOverheadScore(pos, level);
	//トータルスコア（level,combo)
	SAFE_DELETE(m_pSlime[DelSlime]);					//ぶつかりに来たスライムを削除

}

/* ========================================
	スライム→ボス接触分岐関数
	----------------------------------------
	内容：スライムからボスとの接触を正しい処理に分岐させる
	----------------------------------------
	引数1：衝突するスライムの配列番号
	引数2：衝突されたスライムの配列番号
	引数3：爆発マネージャー
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::HitSlimeBossBranch(int HitSlimeNum, int StandBossNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel;								// レベル
	E_SLIME_LEVEL standBossLevel;								// レベル(ボス)
	tagTransform3d hitSlimeTransform;							// ワールド座標系
	tagTransform3d standBossTransform;							// ワールド座標系(ボス)
	TTriType<float> hitSlimeSize;								// サイズを確保						
	float hitSlimeSpeed;										// 移動スピード
	float travelAngle, reflectionAngle;							// 移動方向

	// --参照
	// ノーマル
	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();			// 衝突するスライムのサイズを取得
	hitSlimeTransform = m_pSlime[HitSlimeNum]->GetTransform();		// 衝突するスライムのワールド座標情報を取得
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();				// 衝突するスライムの速度を取得
	hitSlimeSize = m_pSlime[HitSlimeNum]->GetScale();				// 衝突先のスライムのサイズを確保

	// ボス
	standBossLevel = LEVEL_BOSS;									// 衝突する	ボススライムのサイズを取得
	standBossTransform = m_pBoss[StandBossNum]->GetTransform();		// 衝突する	ボススライムのワールド座標情報を取得

	// その他
	travelAngle = hitSlimeTransform.Angle(standBossTransform);		// 衝突する側の進行方向
	reflectionAngle = standBossTransform.Angle(hitSlimeTransform);	// 衝突する側の逆方向(反射)

	//-- フレイムスライムヒット処理
	// フレイム　→　ボス
	if (hitSlimeLevel == LEVEL_FLAME && standBossLevel == LEVEL_BOSS)
	{
		// フレイムが爆発してボスは残る
		pExpMng->SwitchExplode(hitSlimeLevel, hitSlimeTransform.fPos, hitSlimeSize);	//スライムのレベルによって爆発の時間とサイズを分岐
		SAFE_DELETE(m_pSlime[HitSlimeNum]);												// 衝突するスライムを削除
	}

	//-- ノーマルスライムヒット処理
	// ボスが衝突される場合(小→大)
	else if (hitSlimeLevel < standBossLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_BIG, reflectionAngle);			// 衝突するスライムに吹き飛び移動処理
		m_pBoss[StandBossNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_SMALL, travelAngle);			// 衝突されたスライムに吹き飛び移動処理

	}

}

/* ========================================
	ボス→スライム接触分岐関数
	----------------------------------------
	内容：ボスからスライムとの接触を正しい処理に分岐させる
	----------------------------------------
	引数1：衝突するスライムの配列番号
	引数2：衝突されたスライムの配列番号
	引数3：爆発マネージャー
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::HitBossSlimeBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL standSlimeLevel;				// レベル
	E_SLIME_LEVEL hitBossLevel;					// レベル(ボス)
	tagTransform3d standSlimeTransform;			// ワールド座標系
	tagTransform3d hitBossTransform;			// ワールド座標系(ボス)
	TTriType<float> standSlimeSize;				// サイズを確保						
	float hitBossSpeed;							// 移動スピード(ボス)
	float travelAngle, reflectionAngle;			// 移動方向

	// --参照
	// // ノーマル
	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();		// 衝突するスライムのサイズを取得
	standSlimeTransform = m_pSlime[StandSlimeNum]->GetTransform();	// 衝突するスライムのワールド座標情報を取得
	standSlimeSize = m_pSlime[StandSlimeNum]->GetScale();			// スライムのサイズを確保

	// ボス
	hitBossLevel = LEVEL_BOSS;										// 衝突する	ボススライムのサイズを取得
	hitBossTransform = m_pBoss[HitSlimeNum]->GetTransform();		// 衝突する	ボススライムのワールド座標情報を取得
	hitBossSpeed = m_pBoss[HitSlimeNum]->GetSpeed();				// 衝突する	ボススライムの速度を取得	※ボスは一定なはずだから変えたい
	
	// その他
	travelAngle = hitBossTransform.Angle(standSlimeTransform);		// 衝突する側の進行方向
	reflectionAngle = standSlimeTransform.Angle(hitBossTransform);	// 衝突する側の逆方向(反射)

	//-- フレイムスライムヒット処理
	// ボス　→　フレイム
	if (hitBossLevel == LEVEL_BOSS && standSlimeLevel == LEVEL_FLAME)
	{
		// フレイムが爆発してボスは残る
		pExpMng->SwitchExplode(standSlimeLevel, standSlimeTransform.fPos, standSlimeSize);	//スライムのレベルによって爆発の時間とサイズを分岐
		SAFE_DELETE(m_pSlime[StandSlimeNum]);												// 衝突するスライムを削除
	}

	//-- ノーマルスライムヒット処理
	// ボスが衝突する場合(大→小) 
	else if (hitBossLevel > standSlimeLevel)
	{
		m_pBoss[HitSlimeNum]->HitMoveStart(hitBossSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);				// 衝突するスライムに吹き飛び移動処理
		m_pSlime[StandSlimeNum]->HitMoveStart(hitBossSpeed * COL_SUB_STAND_TO_BIG, travelAngle);			// 衝突されたスライムに吹き飛び移動処理

	}
}

/* ========================================
	ボス→ボス接触分岐関数
	----------------------------------------
	内容：スライムからボスとの接触を正しい処理に分岐させる
	----------------------------------------
	引数1：衝突するスライムの配列番号
	引数2：衝突されたスライムの配列番号
	引数3：爆発マネージャー
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::HitBossBossBranch(int HitBossNum, int StandBossNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitBossLevel, standBossLevel;					// レベル(ボス)
	tagTransform3d hitBossTransform, standBossTransform;		// ワールド座標系(ボス)					
	float hitBossSpeed;											// 移動スピード(ボス)
	float travelAngle, reflectionAngle;							// 移動方向

	// --参照
	// ボス
	hitBossLevel = LEVEL_BOSS;									// 衝突する	ボススライムのサイズを取得
	hitBossTransform = m_pBoss[HitBossNum]->GetTransform();		// 衝突する	ボススライムのワールド座標情報を取得
	hitBossSpeed = m_pBoss[HitBossNum]->GetSpeed();				// 衝突する	ボススライムの速度を取得	※ボスは一定なはずだから変えたい
	standBossLevel = LEVEL_BOSS;								// 衝突する	ボススライムのサイズを取得
	standBossTransform = m_pBoss[StandBossNum]->GetTransform();	// 衝突する	ボススライムのワールド座標情報を取得

	// その他
	travelAngle = hitBossTransform.Angle(standBossTransform);		// 衝突する側の進行方向
	reflectionAngle = standBossTransform.Angle(hitBossTransform);	// 衝突する側の逆方向(反射)

	// --ボス同士ヒット処理
	if (hitBossLevel == LEVEL_BOSS && standBossLevel == LEVEL_BOSS)
	{
		//(大→小)と同じ挙動を行う
		m_pBoss[HitBossNum]->HitMoveStart(hitBossSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);				// 衝突するスライムに吹き飛び移動処理
		m_pBoss[StandBossNum]->HitMoveStart(hitBossSpeed * COL_SUB_STAND_TO_BIG, travelAngle);			// 衝突されたスライムに吹き飛び移動処理

	}
}

/* ========================================
	爆発接触関数(ボス)
	----------------------------------------
	内容：画面上の爆発にボスが接触した時の処理
	----------------------------------------
	引数1：接触したボスの配列番号(int)
	引数2：爆発マネージャーのポインタ
	引数3：接触した爆発の配列番号(int)
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::TouchBossExplosion(int BossNum, CExplosionManager* pExpMng, int ExpNum)
{
	CExplosion* touchExplosion = pExpMng->GetExplosionPtr(ExpNum);	// 接触した爆発を取得
	TPos3d<float> pos(m_pBoss[BossNum]->GetPos());					// 衝突先のスライムの位置を確保
	E_SLIME_LEVEL level = m_pBoss[BossNum]->GetSlimeLevel();		// 衝突先のスライムのレベルを確保
	TTriType<float> size = m_pBoss[BossNum]->GetScale();			// 衝突先のスライムサイズを確保

	// 既に接触済みか検索
	if (touchExplosion->GetBossTouched() == false)
	{
		// 爆発威力分のダメージをボスに与える
		m_pBoss[BossNum]->Damage(pExpMng->GetExplosionPtr(ExpNum)->GetDamage());
		// 一度ダメージを与えたら同じ爆発ではダメージを与えない
		touchExplosion->BossTouched();
	}
	// 死亡処理
	if (m_pBoss[BossNum]->IsDead() == true)
	{
		SAFE_DELETE(m_pBoss[BossNum]);	//ぶつかりに来たスライム(ボス)を削除
		
		pExpMng->SwitchExplode(level, pos, size, pExpMng->GetExplosionPtr(ExpNum)->GetComboNum());	// 爆発生成
		m_pScoreOHMng->DisplayOverheadScore(pos, LEVEL_Boss_SCORE, SLIME_SCORE_HEIGHT);
		m_pHealItemMng->Create(pos);

	}

}

/* ========================================
	スライム配列取得関数
	----------------------------------------
	内容：スライム配列の取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：スライムの配列
======================================== */
E_SLIME_LEVEL CSlimeManager::GetRandomLevel()
{
	int random = abs(rand() % 100);	//ランダムに0～99の数字を作成
	
	//定数で定義した確率で1～3レベルのスライムを生成
	if (SLIME_LEVEL1_PER > random)	
	{
		return LEVEL_1;
	}
	else if ((SLIME_LEVEL1_PER + SLIME_LEVEL2_PER) > random)
	{
		return LEVEL_2;
	}
	else if ((SLIME_LEVEL1_PER + SLIME_LEVEL2_PER + SLIME_LEVEL3_PER) > random)
	{
		return LEVEL_3;
	}
	else
	{
		return LEVEL_FLAME;
	}
	
}

/* ========================================
	スライムとスライムが重ならない関数
	----------------------------------------
	内容：ぶつかったスライムが少し押し戻される関数
	----------------------------------------
	引数1：衝突したスライムのポインタ
	引数2：衝突されたスライムのポインタ
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeManager::PreventSlimeSlimeOverlap(CSlimeBase * pMoveSlime, CSlimeBase * pStandSlime)
{
	//↓のコメントアウトは理想的な処理のやりかけ
	/*
	tagSphereInfo::Sphere standSlimeSphere = pStandSlime->GetSphere();						//衝突されたスライムのSphereを取得
	tagSphereInfo::Sphere moveSlimeSphere = pMoveSlime->GetSphere();						//衝突したスライムのSphereを取得
	float standSlimeToPlayerAngle = standSlimeSphere.Angle(m_pPlayer->GetPlayerSphere());	//衝突されたスライムからPlayerへの角度を取得
	float standSlimeToMoveSlimeAngle = standSlimeSphere.Angle(moveSlimeSphere);				//衝突されたスライムから衝突したスライムへの角度を取得
	float Distance = standSlimeSphere.Distance(pMoveSlime->GetSphere());					//スライム同士の距離を取得
	float posX, posY, posZ;																	//座標

	if (standSlimeToMoveSlimeAngle < 0) { standSlimeToMoveSlimeAngle = (2 * PI) + standSlimeToMoveSlimeAngle; }	//
	if (standSlimeToPlayerAngle < 0) { standSlimeToPlayerAngle = (2 * PI) + standSlimeToPlayerAngle; }			
	standSlimeToMoveSlimeAngle -= standSlimeToPlayerAngle;

	if (PI < standSlimeToMoveSlimeAngle)
	{
		standSlimeToMoveSlimeAngle -= DirectX::XMConvertToRadians(5.0f);
	}
	else
	{
		standSlimeToMoveSlimeAngle += DirectX::XMConvertToRadians(5.0f);
	}
	TPos3d<float> pos = pStandSlime->GetPos();
	pos.x +=  cosf(standSlimeToMoveSlimeAngle) * (standSlimeSphere.radius + moveSlimeSphere.radius + 0.05);
	pos.z += sinf(standSlimeToMoveSlimeAngle) * (standSlimeSphere.radius + moveSlimeSphere.radius + 0.05);

	pMoveSlime->SetPos(pos);

	pMoveSlime->ReversePos();
	*/

	float angle = pStandSlime->GetTransform().Angle(pMoveSlime->GetTransform());				//衝突してきた角度
	float distance = pStandSlime->GetSphere().fRadius + pMoveSlime->GetSphere().fRadius;	//お互いのスライムの半径を足した数

	TPos3d<float> pos = pStandSlime->GetPos();		//押し戻す基準の座標
	pos.x += cosf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定
	pos.z += sinf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定

	pMoveSlime->SetPos(pos);						//ぶつからないギリギリの距離に移動
}

/* ========================================
	スライム→ボスが重ならない関数
	----------------------------------------
	内容：ぶつかったスライムが少し押し戻される関数
	----------------------------------------
	引数1：衝突したスライムのポインタ
	引数2：衝突されたボスのポインタ
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeManager::PreventSlimeBossOverlap(CSlimeBase* pMoveSlime, CSlime_BossBase* pStandBoss)
{

	float angle = pStandBoss->GetTransform().Angle(pMoveSlime->GetTransform());				//衝突してきた角度
	float distance = pStandBoss->GetSphere().fRadius + pMoveSlime->GetSphere().fRadius;	//お互いのスライムの半径を足した数

	TPos3d<float> pos = pStandBoss->GetPos();		//押し戻す基準の座標
	pos.x += cosf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定
	pos.z += sinf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定

	pMoveSlime->SetPos(pos);						//ぶつからないギリギリの距離に移動
}

/* ========================================
	ボス→スライムが重ならない関数
	----------------------------------------
	内容：ぶつかられたスライムが少し押し戻される関数
	----------------------------------------
	引数1：衝突したスライムのポインタ
	引数2：衝突されたスライムのポインタ
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeManager::PreventBossSlimeOverlap(CSlime_BossBase* pMoveBoss, CSlimeBase* pStandSlime)
{

	float angle = pStandSlime->GetTransform().Angle(pMoveBoss->GetTransform());				//衝突してきた角度
	float distance = pStandSlime->GetSphere().fRadius + pMoveBoss->GetSphere().fRadius;	//お互いのスライムの半径を足した数

	TPos3d<float> pos = pStandSlime->GetPos();		//押し戻す基準の座標
	pos.x += cosf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定
	pos.z += sinf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定

	pStandSlime->SetPos(pos);						//ぶつからないギリギリの距離に移動
}

/* ========================================
	ボスとボスが重ならない関数
	----------------------------------------
	内容：ぶつかったボスが少し押し戻される関数
	----------------------------------------
	引数1：衝突したスライムのポインタ
	引数2：衝突されたスライムのポインタ
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeManager::PreventBossBossOverlap(CSlime_BossBase* pMoveBoss, CSlime_BossBase* pStandBoss)
{

	float angle = pStandBoss->GetTransform().Angle(pMoveBoss->GetTransform());				//衝突してきた角度
	float distance = pStandBoss->GetSphere().fRadius + pMoveBoss->GetSphere().fRadius;	//お互いのスライムの半径を足した数

	TPos3d<float> pos = pStandBoss->GetPos();		//押し戻す基準の座標
	pos.x += cosf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定
	pos.z += sinf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定

	pMoveBoss->SetPos(pos);						//ぶつからないギリギリの距離に移動
}

/* ========================================
	モデル読み込み関数
	----------------------------------------
	内容：スライムのモデルと頂点シェーダーの読み込み
	----------------------------------------
	引数1：無し
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeManager::LoadModel()
{
	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//レベル1スライムのモデル読み込み
	m_pBlueModel = new Model;
	if (!m_pBlueModel->Load("Assets/Model/slime/slime_blue1.28.FBX", 0.15f, Model::ZFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_blue", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pBlueModel->SetVertexShader(m_pVS);
	//レベル2スライムのモデル読み込み
	m_pGreenModel = new Model;
	if (!m_pGreenModel->Load("Assets/Model/slime/slime_green1.28.FBX", 0.15f, Model::ZFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_green", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pGreenModel->SetVertexShader(m_pVS);
	//レベル3スライムのモデル読み込み
	m_pYellowModel = new Model;
	if (!m_pYellowModel->Load("Assets/Model/slime/slime_Yellow1.28.FBX", 0.15f, Model::ZFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_yellow", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pYellowModel->SetVertexShader(m_pVS);
	//レベル4スライムのモデル読み込み
	m_pRedModel = new Model;
	if (!m_pRedModel->Load("Assets/Model/slime/slime_red1.28.FBX", 0.18f, Model::ZFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_red", "Error", MB_OK);		//ここでエラーメッセージ表示
	}
	m_pRedModel->SetVertexShader(m_pVS);
	//フレイムスライムのモデル読み込み
	m_pFlameModel = new Model;
	if (!m_pFlameModel->Load("Assets/Model/Golem/Golem.FBX", 0.015f, Model::ZFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "Flame_Slime", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pFlameModel->SetVertexShader(m_pVS);
	//ボススライムのモデル読み込み
	m_pBossModel = new Model;
	if (!m_pBossModel->Load("Assets/Model/boss_slime_1/boss_slime_1.fbx", 0.23f, Model::ZFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "Boss_Slime", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pBossModel->SetVertexShader(m_pVS);
}

/* ========================================
	範囲外スライム移動関数
	----------------------------------------
	内容：プレイヤーから離れすぎたスライムをプレイヤーから見た対角線の位置に移動
	----------------------------------------
	引数：ゲットしたいスライムの要素番号
	----------------------------------------
	戻値：スライムの配列
======================================== */
void CSlimeManager::OutOfRange()
{
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		if (!m_pSlime[i]) { continue; }	//nullならスキップ

		TPos3d<float> slimePos = m_pSlime[i]->GetPos();
		float distance = slimePos.Distance(m_pPlayer->GetPos());

		if (distance >= LEAVE_DISTANCE)	//距離が離れすぎていたら
		{
			//相対距離を計算
			float disX = m_pPlayer->GetPos().x - slimePos.x;
			float disZ = m_pPlayer->GetPos().z - slimePos.z;

			//少し近づけてから対角線に移動させる
			if (disX > 0.0f) { disX -= 1.0f; }
			else { disX += 1.0f; }
			if (disZ > 0.0f) { disZ -= 1.0f; }
			else { disZ += 1.0f; }
			//対角線の座標をセット
			TPos3d<float> setPos = { m_pPlayer->GetPos().x + disX,0.0f,m_pPlayer->GetPos().z + disZ};
			m_pSlime[i]->SetPos(setPos);
		}
	}
}


/* ========================================
	逃走判定関数
	----------------------------------------
	内容：スライムと爆発の位置関係を確認して逃げるかどうか判定する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::CheckEscape()
{
	for (int j = 0; j < MAX_SLIME_NUM; j++)
	{
		if (!m_pSlime[j]) { continue; }						//nullptrならスキップ
		if (m_pSlime[j]->GetEscapeFlag()) { continue; }		//すでに逃げているならスキップ

		TPos3d<float> slimePos = m_pSlime[j]->GetPos();	//スライムの座標をゲット
		float distance = ESCAPE_DISTANCE;				//逃げる状態になる最大距離をセット
		//範囲内に爆発があれば逃げるためのフラグと座標をセット
		for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
		{
			CExplosion* pExp = m_pExpMng->GetExplosionPtr(i);	//爆発のポインタを取得
			if (!pExp) { continue; }							//nullptrならスキップ
			TPos3d<float> expPos = pExp->GetPos();				//爆発の座標をゲット
			float slimeExpDistance = slimePos.Distance(expPos);
			if (distance > slimeExpDistance)	//より近い爆発が見つかった場合
			{
				distance = slimeExpDistance;
				m_pSlime[j]->SetExplosionPos(expPos);	//爆発の座標をスライムにセット
				m_pSlime[j]->SetEscapeFlag(true);		//逃げるフラグをONにする
			}
		}
	}
}

/* ========================================
	スライム配列取得関数
	----------------------------------------
	内容：スライム配列の取得
	----------------------------------------
	引数1：ゲットしたいスライムの要素番号
	----------------------------------------
	戻値：スライムの配列
======================================== */
CSlimeBase* CSlimeManager::GetSlimePtr(int num)
{
	return m_pSlime[num];
}

/* ========================================
	ボススライム配列取得関数
	----------------------------------------
	内容：ボススライム配列の取得
	----------------------------------------
	引数1：ゲットしたいボススライムの要素番号
	----------------------------------------
	戻値：ボススライムの配列
======================================== */
CSlime_BossBase* CSlimeManager::GetBossSlimePtr(int num)
{
	return m_pBoss[num];
}

/* ========================================
	カメラ情報セット関数
	----------------------------------------
	内容：描画処理で使用するカメラ情報セット
	----------------------------------------
	引数1：カメラ
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::SetCamera(CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	爆発マネージャーのポインタセット関数
	----------------------------------------
	内容：爆発マネージャーのポインタをセットする
	----------------------------------------
	引数1：爆発マネージャーのポインタ
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeManager::SetExplosionMng(CExplosionManager* pExpMng)
{
	m_pExpMng = pExpMng;
}

/* ========================================
	乱数関数
	----------------------------------------
	内容：毎回異なる乱数関数
	----------------------------------------
	引数1：乱数の最小値と最大値
	----------------------------------------
	戻値：乱数int
======================================== */
int CSlimeManager::GetRandom(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

/* ========================================
	スコア情報セット関数
	----------------------------------------
	内容：爆発生成時に必要なスコア情報セット
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::SetScoreOHMng(CScoreOHManager* pScoreMng)
{
	m_pScoreOHMng = pScoreMng;
}

/* ========================================
	回復アイテムセット関数
	----------------------------------------
	内容：回復アイテムのマネージャーのポインタをセット
	----------------------------------------
	引数1：回復アイテムマネージャーのポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::SetHealMng(CHealItemManager * pHealItemMng)
{
	m_pHealItemMng = pHealItemMng;
}
