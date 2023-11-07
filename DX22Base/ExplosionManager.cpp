/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   爆発管理
   ---------------------------------------
   ExplosionManager.cpp

   作成者 鄭 宇恩

   変更履歴
   ・2023/11/06 爆発マネージャークラス作成 /鄭　宇恩
   ・2023/11/06 爆発発生、削除関数作成 / 鄭 宇恩
   ・2023/11/07 爆発生成関数名の変更、DeleteExplosin()の修正/ 鄭 宇恩
   ======================================== */
#include "ExplosionManager.h"
#include "Explosion.h"
#include "Sphere.h"

CExplosion* g_pExplosion[MAX_EXPLOSION_NUM];

CExplosionManager::CExplosionManager()
{
	//爆発
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		g_pExplosion[i] = new CExplosion;
	}
}

CExplosionManager::~CExplosionManager()
{
	
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (g_pExplosion[i] != nullptr)
		{
			delete g_pExplosion[i];
			g_pExplosion[i] = nullptr;
		}
	}
}

/*========================================
関数：Update関数
----------------------------------------
内容：爆発マネージャーの更新処理
----------------------------------------
引数：なし
----------------------------------------
戻値：なし
======================================== */
void CExplosionManager::Update()
{

}


/*========================================
関数：CreateExplosion関数
----------------------------------------
内容：爆発の生成
----------------------------------------
引数：CSphere::Sphere スライム結合の位置
----------------------------------------
戻値：一旦なし
======================================== */
void CExplosionManager::Create()
{
	//スライム結合、位置の変数
	//?
	
	//爆発する判定
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		//スライム結合したかどうか
		g_pExplosion[i]->SetExplode(true);	//Explosionをtrueに
		&CSphere::Draw;
	}
}

/*========================================
関数：DeleteExplosion関数
----------------------------------------
内容：爆発の削除
----------------------------------------
引数：なし
----------------------------------------
戻値：なし
======================================== */
void CExplosionManager::Delete()
{
	int CntDeleteTime = 0;
	CntDeleteTime++;
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (CntDeleteTime % 120 == 0)
		{
			if(g_pExplosion[i]->GetExplode() == true)
			g_pExplosion[i]->SetExplode(false);
		}
	}
}

/*========================================
関数：Draw関数
----------------------------------------
内容：爆発マネージャーの描画処理
----------------------------------------
引数：なし
----------------------------------------
戻値：なし
======================================== */
void CExplosionManager::Draw()
{
	
	//爆発の描画
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		bool bExploded = g_pExplosion[i]->GetExplode();
		if (g_pExplosion[i]->GetExplode() == false) continue;
		g_pExplosion[i]->Draw();
	}
}