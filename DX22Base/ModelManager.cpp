/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	モデル管理クラス
	---------------------------------------
	ModelManager.h

	作成者
			yamashita

	変更履歴
	・2024/02/08 新規作成

========================================== */

#include "ModelManager.h"
#include "ShaderList.h"

/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CModelManager::CModelManager()
{
	m_fModelSize[MODEL_PLAYER] = 1.0f;			// プレイヤーのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_BLUE] = 0.15f;		// 青スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_GREEN] = 0.15f;	// 緑スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_YELLOW] = 0.15f;	// 黄色スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_RED] = 0.18f;		// 赤スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_FLAME] = 0.3f;		// 炎スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_HEAL] = 0.45f;		// 回復スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_ROCK] = 0.5f;		// 岩スライムのモデルサイズの倍率
	m_fModelSize[MODEL_SLIME_DEVIL] = 0.23f;	// デビルスライムのモデルサイズの倍率
	m_fModelSize[MODEL_ITEM_HEART] = 1.0f;		// 回復アイテムのハートのモデルサイズの倍率

	m_sFileName[MODEL_PLAYER] = 1.0f;			// プレイヤーのモデルのファイル名
	m_sFileName[MODEL_SLIME_BLUE] = 0.15f;		// 青スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_GREEN] = 0.15f;		// 緑スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_YELLOW] = 0.15f;	// 黄色スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_RED] = 0.18f;		// 赤スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_FLAME] = 0.3f;		// 炎スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_HEAL] = 0.45f;		// 回復スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_ROCK] = 0.5f;		// 岩スライムのモデルのファイル名
	m_sFileName[MODEL_SLIME_DEVIL] = 0.23f;		// デビルスライムのモデルのファイル名
	m_sFileName[MODEL_ITEM_HEART] = 1.0f;		// 回復アイテムのハートのモデルのファイル名
	
	// 各モデルの読み込み
	for (int i = 0; i < (int)MODEL_MAX; i++)
	{
		// モデルの動的確保
		m_pModelList.emplace(MODEL_KIND(i), new AnimeModel());
		// モデルの読み込み
		if (!m_pModelList.at(MODEL_KIND(i))->Load(m_sFileName[MODEL_KIND(i)].c_str(), m_fModelSize[MODEL_KIND(i)], AnimeModel::XFlip)) {		//倍率と反転は省略可
			MessageBox(NULL, m_sFileName[MODEL_KIND(i)].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
		// 頂点シェーダーをセット
		m_pModelList.at((MODEL_KIND)i)->SetVertexShader(ShaderList::GetVS(ShaderList::VS_ANIME));	
	}
}

/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：破棄時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CModelManager::~CModelManager()
{
	// 動的確保したモノを削除
	for (int i = 0; i, MODEL_KIND(i); i++)
	{
		SAFE_DELETE(m_pModelList.at(MODEL_KIND(i)));
	}
}


/* ========================================
   関数：クラスの作成および取得関数
   ----------------------------------------
   内容：クラスをインスタンスして取得する(既に作成されている場合は作成しない)
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：このクラス
======================================== */
CModelManager & CModelManager::GetInstance()
{
	static CModelManager modelManager; return modelManager;
}
