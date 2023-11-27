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
	・2023/11/21 BoooomUi表示する関数を呼び出す Tei
	・2023/11/26 スライムと爆発の距離を調べ逃げるか判定する関数を作成 yamashita

=========================================== */

// =============== インクルード ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include "Slime_2.h"
#include "Slime_3.h"
#include "Slime_4.h"
#include "Slime_Flame.h"
#include "Input.h"		//後で消す
#include "GameParameter.h"		//定数定義用ヘッダー

#include <stdlib.h>

// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const int ENEMY_CREATE_INTERVAL	= 3 * 60;		// 生成間隔
const int RANDOM_POS			= 15;			// 生成座標範囲
const int CREATE_DISTANCE		= 10;			// 生成距離最小値
const int SLIME_LEVEL1_PER		= 50;			// スライム_1の生成確立
const int SLIME_LEVEL2_PER		= 35;			// スライム_2の生成確立
const int SLIME_LEVEL3_PER		= 10;			// スライム_3の生成確立
const int SLIME_LEVEL_FLAME_PER	= 100 - SLIME_LEVEL1_PER - SLIME_LEVEL2_PER - SLIME_LEVEL3_PER;	// スライム_フレイムの生成確立

const int START_ENEMY_NUM		= 10;			// ゲーム開始時の敵キャラの数

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
	, m_pVS(nullptr)
	, m_pBlueModel(nullptr)
	, m_pGreenModel(nullptr)
	, m_pYellowModel(nullptr)
	, m_pRedModel(nullptr)
	, m_pFlameModel(nullptr)
	, m_pSEHitSlime(nullptr)
	, m_pSEUnion(nullptr)
	, m_pSEHitSlimeSpeaker(nullptr)
	, m_pSEUnionSpeaker(nullptr)
	, m_pExpMng(nullptr)
{
	//スライムのモデルと頂点シェーダーの読み込み
	LoadModel();

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
	CheckEscape();	//Updateの前に近くに爆発があるか確認する

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
	float hitSlimeSpeed, standSlimeSpeed;						// 移動スピード
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
			pExpMng->Create(pos, MAX_SIZE_EXPLODE * EXPLODE_BASE_RATIO, LEVEL_4_EXPLODE_TIME, E_SLIME_LEVEL::LEVEL_4x4);	//衝突されたスライムの位置でレベル４爆発
			m_pScoreOHMng->DisplayOverheadScore(pos, LEVEL_4_SCORE * 2, LEVEL_4_HEIGHT);
			pExpMng->CreateUI(pos, LEVEL_4_EXPLODE_TIME);		//レベル４爆発した位置boooomUI表示
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
		SAFE_DELETE(m_pSlime[HitSlimeNum]);								// 衝突するスライムを削除
		SAFE_DELETE(m_pSlime[StandSlimeNum]);							// 衝突されたスライムを削除

		return true;
	}
	// ノーマル　→　フレイム
	else if (standSlimeLevel == LEVEL_FLAME)
	{
		pExpMng->SwitchExplode(hitSlimeLevel, hitSlimeTransform.fPos, hitSlimeSize);	//スライムのレベルによって爆発の時間とサイズを分岐
		m_pScoreOHMng->DisplayOverheadScore(hitSlimeTransform.fPos, hitSlimeLevel);

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
	モデル読み込み関数
	----------------------------------------
	内容：スライムのモデルと頂点シェーダーの読み込み
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：
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
	if (!m_pBlueModel->Load("Assets/Model/slime/slime_blue1.28.FBX", 0.15f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_blue", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pBlueModel->SetVertexShader(m_pVS);
	//レベル2スライムのモデル読み込み
	m_pGreenModel = new Model;
	if (!m_pGreenModel->Load("Assets/Model/slime/slime_green1.28.FBX", 0.15f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_green", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pGreenModel->SetVertexShader(m_pVS);
	//レベル3スライムのモデル読み込み
	m_pYellowModel = new Model;
	if (!m_pYellowModel->Load("Assets/Model/slime/slime_Yellow1.28.FBX", 0.15f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_yellow", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pYellowModel->SetVertexShader(m_pVS);
	//レベル4スライムのモデル読み込み
	m_pRedModel = new Model;
	if (!m_pRedModel->Load("Assets/Model/slime/slime_red1.28.FBX", 0.18f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "slime_red", "Error", MB_OK);		//ここでエラーメッセージ表示
	}
	m_pRedModel->SetVertexShader(m_pVS);
	//フレイムスライムのモデル読み込み
	m_pFlameModel = new Model;
	if (!m_pFlameModel->Load("Assets/Model/Golem/Golem.FBX", 0.015f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "Flame_Slime", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pFlameModel->SetVertexShader(m_pVS);
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
void CSlimeManager::SetScoreOHMng(CScoreOHManager * pScoreMng)
{
	m_pScoreOHMng = pScoreMng;
}
