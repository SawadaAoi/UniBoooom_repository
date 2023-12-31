/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムマネージャー クラス実装
   ---------------------------------------
   SlimeManager.cpp

   作成者：鈴村 朋也

   変更履歴
	・2023/11/05 スライムマネージャークラス作成 Suzumura
	・2023/11/08 スライム同士が接触した際の分岐処理を作成(分岐した後に行う処理は未実装　※TODOをつけておいた)の Yamashita
	・2023/11/08 結合処理を作成(結合後の生成処理は未実装 Slime_2〜Slime_4がまだ無いから) Yamashita
	・2023/11/09 生成処理、変数の変更 Sawada
	・2023/11/09 コメントの追加 Sawada
	・2023/11/11 parameter用ヘッダ追加 Suzumura
	・2023/11/11 スライム同士が重ならない関数を追加 Yamashita
	・2023/11/13 スライムレベルごとに爆発時間を設定できるように変更 Suzumura

=========================================== */

// =============== インクルード ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include "Slime_2.h"
#include "Slime_3.h"
#include "Slime_4.h"
#include "Input.h"		//後で消す
#include "GameParameter.h"		//定数定義用ヘッダー

#include <stdlib.h>

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const int ENEMY_CREATE_INTERVAL	= 3 * 60;		// 生成間隔
const int RANDOM_POS			= 15;			// 生成座標範囲
const int CREATE_DISTANCE		= 10;			// 生成距離最小値
const int SLIME_LEVEL1_PER		= 10;			// スライム_1の生成確立
const int SLIME_LEVEL2_PER		= 10;			// スライム_2の生成確立
const int SLIME_LEVEL3_PER		= 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER;	// スライム_3の生成確立

const float MAX_SIZE_EXPLODE	= 5.0f;			// スライム4同士の爆発の大きさ
const float EXPLODE_BASE_RATIO	= 1.5f;			// スライムの爆発接触での爆発の大きさのベース
const int START_ENEMY_NUM		= 10;			// ゲーム開始時の敵キャラの数

const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// スライム_1の爆発総時間
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// スライム_2の爆発総時間
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// スライム_3の爆発総時間
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// スライム_4の爆発総時間


// ↓1.0fでそのまま
const float COL_SUB_HIT_TO_BIG = 0.7f;				// スライム衝突(小→大)の衝突側の減算値(反射する移動)
const float COL_SUB_STAND_TO_SMALL = 0.3f;			// スライム衝突(小→大)の衝突される側の減算値(衝突された方向)
const float COL_SUB_HIT_TO_SMALL = 0.3f;			// スライム衝突(大→小)の衝突側の減算値(移動方向)
const float COL_SUB_STAND_TO_BIG = 1.2f;			// スライム衝突(大→小)の衝突される側の減算値(衝突された方向)
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


	// スライム初期化
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		m_pSlime[i] = nullptr;
	}

	// ゲーム開始時に敵キャラを生成する
	for (int i = 0; i < START_ENEMY_NUM; i++)
	{
		int ranLv = rand() % 3 + 1;		// 生成するスライムのレベルを乱数で指定
		Create((E_SLIME_LEVEL)ranLv);	// 生成処理
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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		if (m_pSlime[i] == nullptr) continue;
		m_pSlime[i]->Update(m_pPlayerPos);

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
	//"スライム1"描画
	for (int i = 0; i < MAX_SLIME_NUM; i++)
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

	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		// スライムのuseを検索
		if (m_pSlime[i] != nullptr) continue;

		// 適切な座標が出るまで繰り返す
		while (true)
		{
			// 乱数をセットする
			CreatePos.x = GetRandom(-RANDOM_POS, RANDOM_POS);	//乱数取得
			CreatePos.z = GetRandom(-RANDOM_POS, RANDOM_POS);
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
	引数1：衝突するスライムの配列番号
	引数2：衝突されたスライムの配列番号
	引数3：爆発マネージャー
	----------------------------------------
	戻値：なし
======================================== */
void CSlimeManager::HitBranch(int HitSlimeNum, int StandSlimeNum, CExplosionManager* pExpMng)
{
	E_SLIME_LEVEL hitSlimeLevel, standSlimeLevel;				// レベル
	CSphereInfo::Sphere hitSlimeSphere, standSlimeSphere;		// 当たり判定
	float hitSlimeSpeed, standSlimeSpeed;						// 移動スピード
	float travelAngle, reflectionAngle;							// 移動方向

	hitSlimeLevel = m_pSlime[HitSlimeNum]->GetSlimeLevel();		// 衝突するスライムのサイズを取得
	hitSlimeSphere = m_pSlime[HitSlimeNum]->GetSphere();		// 衝突するスライムの当たり判定を取得
	hitSlimeSpeed = m_pSlime[HitSlimeNum]->GetSpeed();			// 衝突するスライムの速度を取得

	standSlimeLevel = m_pSlime[StandSlimeNum]->GetSlimeLevel();	// 衝突されたスライムのサイズを取得
	standSlimeSphere = m_pSlime[StandSlimeNum]->GetSphere();	// 衝突されたスライムの当たり判定を取得

	travelAngle = hitSlimeSphere.Angle(standSlimeSphere);		// 衝突する側の進行方向
	reflectionAngle = standSlimeSphere.Angle(hitSlimeSphere);	// 衝突する側の逆方向(反射)
	
	// 衝突するスライムが小さい場合(小→大)
	if (hitSlimeLevel < standSlimeLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_BIG, reflectionAngle);	// 衝突するスライムに吹き飛び移動処理
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_SMALL, travelAngle);			// 衝突されたスライムに吹き飛び移動処理

	}
	
	// 衝突するスライムが大きい場合(大→小)
	else if (hitSlimeLevel > standSlimeLevel)
	{
		m_pSlime[HitSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_HIT_TO_SMALL, travelAngle);	// 衝突するスライムに吹き飛び移動処理
		m_pSlime[StandSlimeNum]->HitMoveStart(hitSlimeSpeed * COL_SUB_STAND_TO_BIG, travelAngle);			// 衝突されたスライムに吹き飛び移動処理

	}
	//スライムのサイズが同じだった場合
	else
	{
		TPos3d<float> pos(m_pSlime[StandSlimeNum]->GetPos());			// 衝突されたスライムの位置を確保
		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// 衝突するスライムを削除
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// 衝突されたスライムを削除

		if (hitSlimeLevel == MAX_LEVEL)	//スライムのサイズが最大の時
		{
			//スライム爆発処理
			pExpMng->Create(pos, MAX_SIZE_EXPLODE * EXPLODE_BASE_RATIO, LEVEL_4_EXPLODE_TIME);	//衝突されたスライムの位置でレベル４爆発

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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
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
	TPos3d<float> pos(m_pSlime[DelSlime]->GetPos());			// 衝突先のスライムの位置を確保
	E_SLIME_LEVEL level = m_pSlime[DelSlime]->GetSlimeLevel();	// 衝突先のスライムのレベルを確保
	TTriType<float> size = m_pSlime[DelSlime]->GetScale();		// 衝突先のスライムサイズを確保

	float ExplosionSize;							// 爆発の大きさ
	ExplosionSize = size.x * EXPLODE_BASE_RATIO;	// 爆発の大きさを スライムの大きさ * 定数倍 に設定 ->補足:size.xのみを取ってきているが、現状x,y,zは等しいため問題なし

	switch (level)
	{
	case LEVEL_1:
		//ExplosionSize = 1.0f * EXPLODE_BASE_RATIO;
		pExpMng->Create(pos, ExplosionSize, LEVEL_1_EXPLODE_TIME);	//衝突されたスライムの位置でレベル１爆発

		break;
	case LEVEL_2:
		//ExplosionSize = 2.0f * EXPLODE_BASE_RATIO;
		pExpMng->Create(pos, ExplosionSize, LEVEL_2_EXPLODE_TIME);	//衝突されたスライムの位置でレベル２爆発

		break;
	case LEVEL_3:
		//ExplosionSize = 3.0f * EXPLODE_BASE_RATIO;
		pExpMng->Create(pos, ExplosionSize, LEVEL_3_EXPLODE_TIME);	//衝突されたスライムの位置でレベル３爆発

		break;
	case LEVEL_4:
		//ExplosionSize = 4.0f * EXPLODE_BASE_RATIO;
		pExpMng->Create(pos, ExplosionSize, LEVEL_4_EXPLODE_TIME);	//衝突されたスライムの位置でレベル４爆発

		break;
	
	}
	SAFE_DELETE(m_pSlime[DelSlime]);					//ぶつかりに来たスライムを削除

	//pExpMng->Create(pos, ExplosionSize);				//衝突先のスライムの位置で爆発
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
	int random = abs(rand() % 100);	//ランダムに0〜99の数字を作成
	
	//定数で定義した確率で1〜3レベルのスライムを生成
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
	重ならない関数
	----------------------------------------
	内容：ぶつかったスライムが少し押し戻される関数
	----------------------------------------
	引数1：衝突したスライムのポインタ
	引数2：衝突されたスライムのポインタ
	----------------------------------------
	戻値：
======================================== */
void CSlimeManager::PreventOverlap(CSlimeBase * pMoveSlime, CSlimeBase * pStandSlime)
{
	//↓のコメントアウトは理想的な処理のやりかけ
	/*
	CSphereInfo::Sphere standSlimeSphere = pStandSlime->GetSphere();
	CSphereInfo::Sphere moveSlimeSphere = pMoveSlime->GetSphere();
	float standSlimeToPlayerAngle = standSlimeSphere.Angle(m_pPlayer->GetPlayerSphere());
	float standSlimeToMoveSlimeAngle = standSlimeSphere.Angle(moveSlimeSphere);
	float Distance = standSlimeSphere.Distance(pMoveSlime->GetSphere());
	float posX, posY, posZ;

	if (standSlimeToMoveSlimeAngle < 0) { standSlimeToMoveSlimeAngle = (2 * PI) + standSlimeToMoveSlimeAngle; }
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

	float angle = pStandSlime->GetSphere().Angle(pMoveSlime->GetSphere());				//衝突してきた角度
	float distance = pStandSlime->GetSphere().radius + pMoveSlime->GetSphere().radius;	//お互いのスライムの半径を足した数

	TPos3d<float> pos = pStandSlime->GetPos();		//押し戻す基準の座標
	pos.x += cosf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定
	pos.z += sinf(angle) * (distance + 0.001f);		//ぶつからないギリギリの距離を設定

	pMoveSlime->SetPos(pos);						//ぶつからないギリギリの距離に移動
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