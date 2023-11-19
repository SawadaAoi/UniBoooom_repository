/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	爆発管理用cpp
	---------------------------------------
	ExplosionManager.cpp
	
	作成者	鄭 宇恩
	
	変更履歴
	・2023/11/06 爆発マネージャークラス作成 Tei
	・2023/11/06 爆発発生、削除関数作成 Tei
	・2023/11/07 爆発生成関数名の変更、DeleteExplosin()の修正 Tei
	・2023/11/09 爆発配列を返す処理の追加 Sawada
	・2023/11/10 他のオブジェクトと同一のカメラをセットするようにした Yamashita
	・2023/11/13 Create関数の引数にtimeを追加 Suzumura

========================================== */

// =============== インクルード ===================
#include "ExplosionManager.h"	//自身のヘッダー
#include "Explosion.h"			//爆発処理ヘッダー
#include "Sphere.h"				//球定義ヘッダー

// =============== 定数定義 =======================


/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CExplosionManager::CExplosionManager()
	: m_dComboCheckFrame(0)
{
	// 爆発配列の初期化
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		m_pExplosion[i] = nullptr;
	}

	for (int i = 0; i < 10; i++)m_dComboCnts[i] = 0;
}

/* ========================================
	関数：デストラクタ
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CExplosionManager::~CExplosionManager()
{
	// メモリ削除
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		SAFE_DELETE(m_pExplosion[i]);
	}
}


/* ========================================
	更新処理関数
	-------------------------------------
	内容：爆発マネージャーの更新処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CExplosionManager::Update()
{
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 未使用の爆発はスルー
		if (m_pExplosion[i] == nullptr)
		{
			continue;

		}

		m_pExplosion[i]->Update();
	}

	DeleteCheck();	// 削除チェック

	for (int i = 0; i < 10; i++)
	{
		if (m_dComboCnts[i] == 0) continue;
		bool bComboFlg = false;
		for (int j = 0; j < MAX_EXPLOSION_NUM; j++)
		{
			// 未使用の爆発はスルー
			if (m_pExplosion[j] == nullptr) continue;

			if (m_pExplosion[j]->m_dComboNum == i)
			{
				bComboFlg = true;
				break;
			}
		}
		m_dComboCnts[i] = 0;
	}
}



/* ========================================
	生成処理関数
	-------------------------------------
	内容：爆発の生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	-------------------------------------
	引数2：爆発の大きさ
	-------------------------------------
	引数3：爆発総時間
	-------------------------------------
	戻値：なし
=========================================== */
void CExplosionManager::Create(TTriType<float> pos,float size, float time)
{
	int comboNum = 0;
	for (int i = 0; i < 10; i++)
	{
		if (m_dComboCnts[i] != 0) continue;
		m_dComboCnts[i] ++;
		comboNum = i;
		break;
	}

	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos, size, time, comboNum);	// 座標を指定して生成
		m_pExplosion[i]->SetCamera(m_pCamera);

		break;

	}

	
}

void CExplosionManager::Create(TTriType<float> pos, float size, float time, int comboNum)
{
	m_dComboCnts[comboNum]++;

	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos, size, time, comboNum);	// 座標を指定して生成
		m_pExplosion[i]->SetCamera(m_pCamera);

		break;

	}

}

/* ========================================
	関数：爆発削除関数
	----------------------------------------
	内容：爆発があったらチェックしてから削除
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CExplosionManager::DeleteCheck()
{
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 未使用の爆発はスルー
		if (m_pExplosion[i] == nullptr) continue;
		// 削除フラグがたってない爆発はスルー
		if (m_pExplosion[i]->GetDelFlg() == false) continue;

		delete m_pExplosion[i]; m_pExplosion[i] = nullptr;	// 爆発を削除する

	}
}

/* ========================================
	カメラ情報セット関数
	----------------------------------------
	内容：描画処理で使用するカメラ情報セット
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
======================================== */
void CExplosionManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	爆発配列取得関数
	----------------------------------------
	内容：爆発配列の取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：爆発の配列
======================================== */
CExplosion* CExplosionManager::GetExplosionPtr(int num)
{
	return m_pExplosion[num];;
}

/* ========================================
	関数：爆発分岐関数
	----------------------------------------
	内容：スライムのレベルに応じて爆発の時間と大きさを変更
	----------------------------------------
	引数1：スライムのレベル
	引数2：発生場所
	引数3：スライムの大きさ
	----------------------------------------
	戻値：なし
======================================== */
void CExplosionManager::SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize, int comboNum)
{
	float ExplosionSize = slimeSize.x * EXPLODE_BASE_RATIO;

	// ぶつけられたスライムのレベルによって分岐
	switch (slimeLevel) {
	case LEVEL_1:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_1_EXPLODE_TIME, comboNum);	//衝突されたスライムの位置でレベル１爆発
		break;
	case LEVEL_2:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_2_EXPLODE_TIME, comboNum);	//衝突されたスライムの位置でレベル２爆発
		break;
	case LEVEL_3:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_3_EXPLODE_TIME, comboNum);	//衝突されたスライムの位置でレベル３爆発
		break;
	case LEVEL_4:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_4_EXPLODE_TIME, comboNum);	//衝突されたスライムの位置でレベル４爆発
		break;
	case LEVEL_FLAME:
		Create(pos, ExplosionSize, LEVEL_1_EXPLODE_TIME, comboNum);	//衝突されたスライムの位置でレベル１爆発

		break;
	}
}

void CExplosionManager::SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize)
{
	float ExplosionSize = slimeSize.x * EXPLODE_BASE_RATIO;

	// ぶつけられたスライムのレベルによって分岐
	switch (slimeLevel) {
	case LEVEL_1:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_1_EXPLODE_TIME);	//衝突されたスライムの位置でレベル１爆発
		break;
	case LEVEL_2:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_2_EXPLODE_TIME);	//衝突されたスライムの位置でレベル２爆発
		break;
	case LEVEL_3:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_3_EXPLODE_TIME);	//衝突されたスライムの位置でレベル３爆発
		break;
	case LEVEL_4:
		//スライム爆発処理
		Create(pos, ExplosionSize, LEVEL_4_EXPLODE_TIME);	//衝突されたスライムの位置でレベル４爆発
		break;
	case LEVEL_FLAME:
		Create(pos, ExplosionSize, LEVEL_1_EXPLODE_TIME);	//衝突されたスライムの位置でレベル１爆発

		break;
	}
}

/* ========================================
	関数：描画関数
	----------------------------------------
	内容：爆発マネージャーの描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CExplosionManager::Draw()
{
	// 爆発の検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 未使用の爆発はスルー
		if (m_pExplosion[i] == nullptr) continue;

		m_pExplosion[i]->Draw(); // 爆発の描画
	}
}