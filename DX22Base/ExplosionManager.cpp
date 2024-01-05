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
	・2023/11/18 爆発時にSEを再生するように変更 Yamahsita
	・2023/11/19 Create関数の引数にdamageを追加 Suzumura
	・2023/11/20 コンボ数機能追加 Sawada
	・2023/11/21 コンボ数機能の一部をコンボクラスに移動 Sawada
	・2023/11/21 爆発時にBoooomUIの表示を追加 Tei
	・2023/12/07 Effekseer.hのインクルード追加 Takagi

========================================== */

// =============== インクルード ===================
#include "ExplosionManager.h"	//自身のヘッダー
#include "Explosion.h"			//爆発処理ヘッダー
#include "Sphere.h"				//球定義ヘッダー
#include "DirectWrite.h"
#include "Input.h"
#include "LibEffekseer.h"

// =============== 定数定義 =======================
const float EXPLODE_VOLUME = 0.5f;

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
	:m_pSEExplode(nullptr)
	, m_pSEExplodeSpeaker(nullptr)
	, m_pTexUI(nullptr)
{
	// 爆発配列の初期化
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		m_pExplosion[i] = nullptr;
	}

	m_pTexUI = new Texture();
	// boooomUI配列の初期化
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		m_pBoooomUI[i] = nullptr;
	}
	if (FAILED(m_pTexUI->Create("Assets/Texture/boooom.png")))
	{
		MessageBox(NULL, "boooom.png", "Error", MB_OK);
	}
	//サウンドファイルの読み込み
	m_pSEExplode = CSound::LoadSound("Assets/Sound/SE/Explode.mp3");

	//エフェクト初期化
	m_explodeEffect = LibEffekseer::Create("Assets/Effect/mega/mega_reverse (2).efkefc");
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
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		SAFE_DELETE(m_pBoooomUI[i]);
	}
	SAFE_DELETE(m_pTexUI);
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

		if (m_pExplosion[i]->GetSeFlg() == true)
		{
			m_pSEExplodeSpeaker = CSound::PlaySound(m_pSEExplode);	//爆発の再生
			m_pSEExplodeSpeaker->SetVolume(EXPLODE_VOLUME);			//音量調整
			m_pExplosion[i]->SetSeFlg(false);
		}
		
	}
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		//未使用のBoooomUIはスルー
		if (m_pBoooomUI[i] == nullptr) continue;

		m_pBoooomUI[i]->Update();
	}
	DeleteCheck();	// 削除チェック
	ComboEndCheck();	// コンボの削除
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
	// boooomUIの検索
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		//未使用のBoooomUIはスルー
		if (m_pBoooomUI[i] == nullptr) continue;

		m_pBoooomUI[i]->Draw();	// boooomUIの描画
	}
}

/* ========================================
	生成処理関数
	-------------------------------------
	内容：爆発の生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：爆発の大きさ
	引数3：爆発総時間
	引数4：爆発のダメージ
	-------------------------------------
	戻値：なし
=========================================== */
void CExplosionManager::Create(TTriType<float> pos,float size, float time, int damage, E_SLIME_LEVEL level)
{
	int comboNum = m_pCombo->FirstComboSet();		// コンボ配列の添え字を取得
	m_pCombo->AddScore(level, comboNum);

	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos, size, time, comboNum, true, damage,m_explodeEffect,m_pCamera);	// 座標を指定して生成
		m_pExplosion[i]->SetCamera(m_pCamera);

		break;

	}	
}

/* ========================================
	生成処理関数
	-------------------------------------
	内容：爆発の生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：爆発の大きさ
	引数3：爆発総時間
	引数4：コンボ配列添え字
	引数5：爆発のダメージ
	-------------------------------------
	戻値：なし
=========================================== */
void CExplosionManager::Create(TTriType<float> pos, float size, float time, int comboNum, int damage, E_SLIME_LEVEL level)
{
	m_pCombo->AddCombo(comboNum);	// 対応するコンボ配列の値を加算する
	m_pCombo->AddScore(level, comboNum);

	// 爆発を検索
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		// 使用済みの爆発はスルー
		if (m_pExplosion[i] != nullptr) continue;

		m_pExplosion[i] = new CExplosion(pos, size, time, comboNum, true, damage, m_explodeEffect, m_pCamera);	// 座標を指定して生成
		m_pExplosion[i]->SetCamera(m_pCamera);

		return;
	}
}



/* ========================================
	爆発削除関数
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

	//BoooomUIを検索
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		//未使用のBoooomUIはスルー
		if (m_pBoooomUI[i] == nullptr) continue;
		//削除フラグがたってないBoooomUIはスルー
		if (m_pBoooomUI[i]->GetDelFlg() == false) continue;

		delete m_pBoooomUI[i]; m_pBoooomUI[i] = nullptr;
	}
}

/* ========================================
	UI生成処理関数
	-------------------------------------
	内容：BoooomUIの生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	-------------------------------------
	戻値：なし
=========================================== */
void CExplosionManager::CreateUI(TPos3d<float> pos, float fTime)
{
	for (int i = 0; i < MAX_BOOOOM_NUM; i++)
	{
		// 使用済みのBoooomUiはスルー
		if (m_pBoooomUI[i] != nullptr) continue;

		m_pBoooomUI[i] = new CBoooomUI(pos, m_pTexUI, m_pCamera, fTime);	// 座標を指定して生成
		m_pBoooomUI[i]->SetCamera(m_pCamera);

		return;
	}
}



/* ========================================
	爆発コンボリセット関数
	----------------------------------------
	内容：爆発が連鎖しているかチェックしてリセット
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CExplosionManager::ComboEndCheck()
{
	// コンボ数分確認
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// コンボ数が入ってない所はスルー
		if (m_pCombo->GetCombo(i) == 0) continue;
		bool bComboFlg = false;	// 爆発連鎖有効フラグ

		// 爆発数分チェック
		for (int j = 0; j < MAX_EXPLOSION_NUM; j++)
		{
			// 未使用の爆発はスルー
			if (m_pExplosion[j] == nullptr) continue;

			// コンボが有効かどうか(対応添え字の爆発が画面上に残っているか)
			if (m_pExplosion[j]->GetComboNum() == i)
			{
				bComboFlg = true;
				break;
			}
		}
		// 画面外に対応添え字の爆発が全てなくなったら
		if (bComboFlg == false)
		{
			m_pCombo->EndCombo(i); 	// コンボをリセット
		}
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
	コンボ情報セット関数
	----------------------------------------
	内容：コンボ情報ポインタセット
	----------------------------------------
	引数1：コンボ情報ポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CExplosionManager::SetCombo(CCombo * pCombo)
{
	m_pCombo = pCombo;
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
	if (!m_pExplosion[num]) { return nullptr; }
	return m_pExplosion[num];
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
void CExplosionManager::SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize)
{
	float ExplosionSize = slimeSize.x * EXPLODE_BASE_RATIO;
	float ExplodeTime;
	int ExplodeDamage;

	// ぶつけられたスライムのレベルによって分岐
	switch (slimeLevel) {
	case LEVEL_1:		ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;
	case LEVEL_2:		ExplodeTime = LEVEL_2_EXPLODE_TIME;		ExplodeDamage = LEVEL_2_EXPLODE_DAMAGE; break;
	case LEVEL_3:		ExplodeTime = LEVEL_3_EXPLODE_TIME;		ExplodeDamage = LEVEL_3_EXPLODE_DAMAGE; break;
	case LEVEL_4:		ExplodeTime = LEVEL_4_EXPLODE_TIME;		ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;
	case LEVEL_FLAME:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// 炎スライムと爆発が接触した際は一番小さい爆発
	case LEVEL_HEAL:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// 回復スライムと爆発が接触した際は一番小さい爆発
	case LEVEL_BOSS:	ExplodeTime = LEVEL_BOSS_EXPLODE_TIME;	ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;
	}

	Create(pos, ExplosionSize, ExplodeTime, ExplodeDamage, slimeLevel);	// 爆発生成

}
/* ========================================
	関数：爆発分岐関数
	----------------------------------------
	内容：スライムのレベルに応じて爆発の時間と大きさを変更
	----------------------------------------
	引数1：スライムのレベル
	引数2：発生場所
	引数3：スライムの大きさ
	引数4：コンボ配列の添え字
	----------------------------------------
	戻値：なし
======================================== */
void CExplosionManager::SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize, int comboNum)
{
	float ExplosionSize = slimeSize.x * EXPLODE_BASE_RATIO;
	float ExplodeTime;
	int ExplodeDamage;

	// ぶつけられたスライムのレベルによって分岐
	switch (slimeLevel) {
	case LEVEL_1:		ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;
	case LEVEL_2:		ExplodeTime = LEVEL_2_EXPLODE_TIME;		ExplodeDamage = LEVEL_2_EXPLODE_DAMAGE; break;
	case LEVEL_3:		ExplodeTime = LEVEL_3_EXPLODE_TIME;		ExplodeDamage = LEVEL_3_EXPLODE_DAMAGE; break;
	case LEVEL_4:		ExplodeTime = LEVEL_4_EXPLODE_TIME;		ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;
	case LEVEL_FLAME:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// 炎スライムと爆発が接触した際は一番小さい爆発
	case LEVEL_HEAL:	ExplodeTime = LEVEL_1_EXPLODE_TIME;		ExplodeDamage = LEVEL_1_EXPLODE_DAMAGE; break;	// 回復スライムと爆発が接触した際は一番小さい爆発
	case LEVEL_BOSS:	ExplodeTime = LEVEL_BOSS_EXPLODE_TIME;	ExplodeDamage = LEVEL_4_EXPLODE_DAMAGE; break;

	}

	Create(pos, ExplosionSize, ExplodeTime, comboNum, ExplodeDamage, slimeLevel);	// 爆発生成
//	m_pCombo->AddScore(slimeLevel, comboNum);

}


