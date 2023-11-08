/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スライムマネージャー クラス実装
	---------------------------------------
	SlimeManager.cpp
	
	作成者：鈴村 朋也
	
	変更履歴
	・2023/11/05 スライムマネージャークラス作成 /鈴村 朋也
	・2023/11/09 生成処理、変数の変更           /澤田 蒼生
	
========================================== */

// =============== インクルード ===================
#include "SlimeManager.h"
#include "Slime_1.h"
#include <time.h>

#include <stdlib.h>


// =============== 定数定義 =======================
const int ENEMY_GENERATE_INTERVAL = 5 * 60;



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
	: m_GeneCnt(0)
{

	srand((unsigned int)time(NULL));	//時間により乱数生成


	//"スライム1"生成
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
	//"スライム1"削除
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
void CSlimeManager::Update(CSphereInfo::Sphere playerSphere)
{
	
	//"スライム1"更新
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] == nullptr) continue;

		
		

		m_pSlime[i]->Update(playerSphere);
	

	}

	m_GeneCnt++;
	if(ENEMY_GENERATE_INTERVAL<=m_GeneCnt)
	{
		// 敵 生成
		Generate(TPos<float>(playerSphere.pos.x, 0.0f, playerSphere.pos.z));
		m_GeneCnt = 0;
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
	引数1：生成する位置
	-------------------------------------
	戻値：無し
=========================================== */
void CSlimeManager::Generate(const TPos<float> pos)
{
	TPos<float> Pos;

	for (int i = 0; i < MAX_SLIME; i++)
	{
		// スライムのuseを検索
		if (m_pSlime[i] != nullptr) continue;


		float m_distanceFromPlayer = 0.0f;
		float m_posX, m_posZ;

		while (true)
		{
			Pos.x = GetRandom(1, 30);	//乱数取得
			Pos.z = GetRandom(1, 30);
			Pos.y = 0;
			float Distance = sqrt(pow(Pos.x - pos.x, 2.0f) + pow(Pos.z - pos.z, 2.0f));

			

			if (Distance >= 10) break;
		}
		
		m_pSlime[i] = new CSlime_1();	//useをtrueに
		m_pSlime[i]->SetPos(Pos);	//posを設定
		break;						//見つけたらbreak
		
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
void CSlimeManager::HitBranch(int HitSlimeArrayNum, int standSlimeArrayNum)
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
		SAFE_DELETE(m_pSlime[HitSlimeArrayNum]);	//ぶつかりに来たスライムを削除
		SAFE_DELETE(m_pSlime[standSlimeArrayNum]);	//ぶつかられたスライムを削除

		if (hitSlimeLevel == MAX_LEVEL)	//スライムのサイズが最大の時
		{
			//爆発処理を行う<=TODO
		}
		else	//最大サイズじゃない場合は1段階大きいスライムを生成する
		{
			UnionSlime(hitSlimeLevel);	//スライムの結合処理
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
void CSlimeManager::UnionSlime(E_SLIME_LEVEL level)
{
	for (int i = 0; i < MAX_SLIME; i++)
	{
		if (m_pSlime[i] != nullptr) { continue; }

		switch (level)
		{
		case LEVEL_1:
			//サイズ2のスライムを生成<=TODO
			break;
		case LEVEL_2:
			//サイズ3のスライムを生成<=TODO
			break;
		case LEVEL_3:
			//サイズ4のスライムを生成<=TODO
			break;
		}
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
CSlimeBase* CSlimeManager::GetSlimePtr(int num)
{
	return m_pSlime[num];
}

void CSlimeManager::SetCamera(CCamera * pCamera)
{
	m_pCamera = pCamera;
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