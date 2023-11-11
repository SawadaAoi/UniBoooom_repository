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
	
=========================================== */

// =============== インクルード ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include "Slime_2.h"
#include "Slime_3.h"
#include "Slime_4.h"
#include <time.h>
#include "Input.h"		//後で消す

#include <stdlib.h>

// =============== 定数定義 =======================
#if MODE_DEFINE
#else
const int ENEMY_GENERATE_INTERVAL	= 3 * 60;	// 生成間隔
const int RANDOM_POS_MIN			= -15;		// 生成座標範囲下限(x,z共通)
const int RANDOM_POS_MAX			= 15;		// 生成座標範囲上限(x,z共通)
const int CREATE_DISTANCE			= 10;		// 生成距離最小値
const int SLIME_LEVEL1_PER = 50;				// スライム_1の生成確立
const int SLIME_LEVEL2_PER = 30;				// スライム_2の生成確立
const int SLIME_LEVEL3_PER = 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER;	// スライム_3の生成確立
const float MAX_SIZE_EXPLODE = 5.0f;	// スライム4同士の爆発の大きさ
const float EXPLODE_BASE_RATIO = 1.0f;	// スライムの爆発接触での爆発の大きさのベース
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
CSlimeManager::CSlimeManager()
	: m_CreateCnt(0)
{

	srand((unsigned int)time(NULL));	// 乱数パターン設定

	// スライム初期化
	for (int i = 0; i < MAX_SLIME; i++)
	{
		m_pSlime[i] = nullptr;
	}
	
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
	// スライム削除
	for (int i = 0; i < MAX_SLIME; i++)
	{
		SAFE_DELETE(m_pSlime[i]);
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
	
	// スライム更新
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Update(m_pPlayerPos);

	}

	m_CreateCnt++;
	if(ENEMY_GENERATE_INTERVAL<= m_CreateCnt)
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
	//"スライム1"描画
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Draw(m_pCamera);
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

	for (int i = 0; i < MAX_SLIME; i++)
	{
		// スライムのuseを検索
		if (m_pSlime[i] != nullptr) continue;

		// 適切な座標が出るまで繰り返す
		while (true)
		{
			// 乱数をセットする
			CreatePos.x = GetRandom(RANDOM_POS_MIN, RANDOM_POS_MAX);	//乱数取得
			CreatePos.z = GetRandom(RANDOM_POS_MIN, RANDOM_POS_MAX);
			CreatePos.y = 0;

			float Distance = CreatePos.Distance(m_pPlayerPos);	// 生成座標のプレイヤーとの距離

			if (Distance >= CREATE_DISTANCE) break;	// プレイヤーから一定の距離離れていれば抜ける
		}
		
		switch (level)
		{
		case LEVEL_1:
			m_pSlime[i] = new CSlime_1(CreatePos);	// 動的生成
			break;
		case LEVEL_2:
			m_pSlime[i] = new CSlime_2(CreatePos);	// 動的生成
			break;
		case LEVEL_3:
			m_pSlime[i] = new CSlime_3(CreatePos);	// 動的生成
			break;
		case LEVEL_4:
			m_pSlime[i] = new CSlime_4(CreatePos);	// 動的生成
			break;
		}

		m_pSlime[i]->SetCamera(m_pCamera);	//カメラをセット
		break;						// 生成したら終了
		
	}
}

/* ========================================
	スライム接触分岐関数
	----------------------------------------
	内容：スライム同士が接触した際に分岐して正しい処理を実行する
	----------------------------------------
	引数1：ぶつかりにきたスライムの配列番号
	引数2：ぶつかられたスライムの配列番号
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::HitBranch(int HitSlimeArrayNum, int standSlimeArrayNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel, standSlimeLevel;
	hitSlimeLevel = m_pSlime[HitSlimeArrayNum]->GetSlimeLevel();		//ぶつかりに来たスライムのサイズを取得
	standSlimeLevel = m_pSlime[standSlimeArrayNum]->GetSlimeLevel();	//ぶつかられたスライムのサイズを取得
	if (hitSlimeLevel > standSlimeLevel)								//ぶつかりにきたスライムが大きい場合
	{
		float speed = m_pSlime[HitSlimeArrayNum]->GetSpeed();					//ぶつかりに来たスライムの速度を取得
		CSphereInfo::Sphere sphere = m_pSlime[HitSlimeArrayNum]->GetSphere();		//ぶつかられたスライムのSphereを取得
		float angle = sphere.Angle(m_pSlime[standSlimeArrayNum]->GetSphere());		//ぶつかられたスライムの方向を割り出す
		m_pSlime[standSlimeArrayNum]->HitMoveStart(speed, angle);					//ぶつかられたスライムに吹き飛び移動処理
		m_pSlime[HitSlimeArrayNum]->Reflect();										//ぶつかりに来たスライムの速度に反発の割合を乗算する
	}
	else if(hitSlimeLevel < standSlimeLevel)	//ぶつかりにきたスライムが小さい場合
	{
		float speed = m_pSlime[HitSlimeArrayNum]->GetSpeed();					//ぶつかりに来たスライムの速度を取得
		CSphereInfo::Sphere sphere = m_pSlime[standSlimeArrayNum]->GetSphere();		//ぶつかられたスライムのSphereを取得
		float angle = sphere.Angle(m_pSlime[HitSlimeArrayNum]->GetSphere());		//ぶつかられたスライムの方向を割り出す
		m_pSlime[HitSlimeArrayNum]->HitMoveStart(speed, angle);						//ぶつかられたスライムに吹き飛び移動処理
	}
	else	//スライムのサイズが同じだった場合
	{
		TPos3d<float> pos(m_pSlime[standSlimeArrayNum]->GetPos());	//衝突先のスライムの位置を確保
		SAFE_DELETE(m_pSlime[HitSlimeArrayNum]);	//ぶつかりに来たスライムを削除
		SAFE_DELETE(m_pSlime[standSlimeArrayNum]);	//ぶつかられたスライムを削除

		if (hitSlimeLevel == MAX_LEVEL)	//スライムのサイズが最大の時
		{
			//爆発処理を行う<=TODO
			pExpMng->Create(pos, MAX_SIZE_EXPLODE);	//衝突先のスライムの位置で爆発
		}
		else	//最大サイズじゃない場合は1段階大きいスライムを生成する
		{
			UnionSlime(hitSlimeLevel,pos);	//スライムの結合処理
		}
	}
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
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] != nullptr) { continue; }

		switch (level)
		{
		case LEVEL_1:
			//サイズ2のスライムを生成
			m_pSlime[i] = new CSlime_2(pos);
			break;
		case LEVEL_2:
			//サイズ3のスライムを生成
			m_pSlime[i] = new CSlime_3(pos);
			break;
		case LEVEL_3:
			//サイズ4のスライムを生成
			m_pSlime[i] = new CSlime_4(pos);
			break;
		}

		m_pSlime[i]->SetCamera(m_pCamera);	//カメラをセット

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
void CSlimeManager::TouchExplosion(int DelSlime, CExplosionManager * pExpMng)
{
	TPos3d<float> pos(m_pSlime[DelSlime]->GetPos());	//衝突先のスライムの位置を確保

	float ExplosionSize;	// 爆発の大きさ
	switch (m_pSlime[DelSlime]->GetSlimeLevel())
	{
	case LEVEL_1:
		ExplosionSize = 1.0f * EXPLODE_BASE_RATIO;
		break;
	case LEVEL_2:
		ExplosionSize = 2.0f * EXPLODE_BASE_RATIO;
		break;
	case LEVEL_3:
		ExplosionSize = 3.0f * EXPLODE_BASE_RATIO;
		break;
	case LEVEL_4:
		ExplosionSize = 4.0f * EXPLODE_BASE_RATIO;
		break;
	
	}
	SAFE_DELETE(m_pSlime[DelSlime]);					//ぶつかりに来たスライムを削除
	pExpMng->Create(pos, ExplosionSize);				//衝突先のスライムの位置で爆発
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
	else
	{
		return LEVEL_3;
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
	プレイヤーの座標取得関数
	----------------------------------------
	内容：現在のプレイヤーの座標を取得する
	----------------------------------------
	引数1：プレイヤーの座標(現在はスフィアだが、今後変更する)
	----------------------------------------
	戻値：無し
======================================== */
void CSlimeManager::SetPlayerPos(TPos3d<float> pos)
{
	m_pPlayerPos = pos;
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