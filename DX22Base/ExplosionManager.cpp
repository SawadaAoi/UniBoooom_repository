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
{
	// 爆発配列の初期化
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		m_pExplosion[i] = nullptr;
	}
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
	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos,size,time);	// 座標を指定して生成
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