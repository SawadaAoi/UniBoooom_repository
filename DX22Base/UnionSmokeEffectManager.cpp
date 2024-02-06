/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	結合エフェクトマネージャ―
	---------------------------------------
	UnionSmokeEffectManager.cpp

	作成者
			Tei

	変更履歴
	・2024/02/06 クラス作成 Tei

========================================== */

// =============== インクルード ===================
#include "UnionSmokeEffectManager.h"

// =============== 定数定義 ===================
const std::map<int, std::string> MAP_TEX_PATH = {
	{CUnionSmokeEffectManager::GREEN_SMOKE,		"Assets/Effect/Union/green_v1.png"},		// 結合煙の画像（緑）
	{CUnionSmokeEffectManager::YELLOW_SMOKE,	"Assets/Effect/Union/yellow_v1.png"},		// 結合煙の画像（黄）
	{CUnionSmokeEffectManager::RED_SMOKE,		"Assets/Effect/Union/red_v1.png"},			// 結合煙の画像（赤）
	
};
const int	EFFECT_SPEED = 0.02 * 60;		// エフェクト再生スピード

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CUnionSmokeEffectManager::CUnionSmokeEffectManager()
{
	for (int i = 0; i < E_SMOKE::SMOKE_MAX; i++)
	{
		// リザルト画像読込
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(MAP_TEX_PATH.at(i).c_str())))
		{
			MessageBox(NULL, "Union Smoke Texture", "Error", MB_OK);
		}
	}

	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		m_pUnionSmokeEffect[i] = nullptr;
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
CUnionSmokeEffectManager::~CUnionSmokeEffectManager()
{
	// メモリ削除
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		SAFE_DELETE(m_pUnionSmokeEffect[i]);
	}
}

/* ========================================
	生成処理関数
	-------------------------------------
	内容：結合エフェクトの生成
	-------------------------------------
	引数1：生成座標(x,y,z)
	引数2：生成サイズ(x,y,z)
	引数3：スライムのレベル(緑、黄、赤)
	-------------------------------------
	戻値：なし
=========================================== */
void CUnionSmokeEffectManager::Create(TPos3d<float> fpos, TPos3d<float> fsize, int slimelevel)
{
	// 結合エフェクトを検索
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// 使用済みの結合エフェクトはスルー
		if (m_pUnionSmokeEffect[i] != nullptr) continue;

		// 座標、大きさ、使用のテクスチャ、カメラを指定して生成
		m_pUnionSmokeEffect[i] = new CUnionSmokeEffect(fpos, fsize, m_pTexture[slimelevel - 1], m_pCamera);

		return;
	}
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：結合エフェクトマネージャーの更新処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CUnionSmokeEffectManager::Update()
{
	// 結合エフェクトを検索
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// 未使用の結合エフェクトはスルー
		if (m_pUnionSmokeEffect[i] == nullptr) continue;
		m_pUnionSmokeEffect[i]->Update();
	}
	DeleteCheck();
}

/* ========================================
	関数：描画関数
	----------------------------------------
	内容：結合エフェクトマネージャーの描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CUnionSmokeEffectManager::Draw()
{
	// Unionエフェクトの検索
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// 未使用のUnionエフェクトはスルー
		if (m_pUnionSmokeEffect[i] == nullptr) continue;

		m_pUnionSmokeEffect[i]->Draw(); // Unionエフェクトの描画

	}
}

/* ========================================
	結合エフェクト削除関数
	----------------------------------------
	内容：結合エフェクトが生成したらチェックしてから削除
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CUnionSmokeEffectManager::DeleteCheck()
{
	// 結合エフェクトを検索
	for (int i = 0; i < MAX_UNION_SMOKE_NUM; i++)
	{
		// 未使用の結合エフェクトはスルー
		if (m_pUnionSmokeEffect[i] == nullptr) continue;
		// 削除フラグがたってない結合エフェクトはスルー
		if (m_pUnionSmokeEffect[i]->GetDelFlg() == false) continue;

		delete m_pUnionSmokeEffect[i]; m_pUnionSmokeEffect[i] = nullptr;	// 結合エフェクトを削除する

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
void CUnionSmokeEffectManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
