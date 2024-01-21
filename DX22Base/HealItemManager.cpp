/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	回復アイテム管理用ソース
	------------------------------------
	HealItemManager.cpp
	------------------------------------
	作成者	yamashita

	変更履歴
	・2023/11/27 cpp作成 yamashita
	・2023/11/28 生成関数を作成 yamashita
	・2023/11/28 リストのポインタ取得関数を作成 yamashita
	・2024/01/21 コメント改修・MessageBox改善 takagi

========================================== */

// =============== インクルード ===================
#include "HealItemManager.h"

/* ========================================
   コンストラクタ
   ----------------------------------------
   内容：開始処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CHealItemManager::CHealItemManager()
	:m_pModel(nullptr)
	,m_pVS(nullptr)
{
	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "VS_Model.cso読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);								//エラー通知
#endif
	}
	//回復アイテムのモデル読み込み
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/heart/heart_1.FBX", 1.0f, Model::None)) {		//倍率と反転は省略可
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "HealItem:Model読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);								//エラー通知
#endif
	}
	m_pModel->SetVertexShader(m_pVS);
}

/* ========================================
   デストラクタ
   ----------------------------------------
   内容：終了処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CHealItemManager::~CHealItemManager()
{
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pModel);

	for (auto i = m_pHealItemList.begin(); i != m_pHealItemList.end();)
	{
		delete (*i);
		i = m_pHealItemList.erase(i);
	}
}

/* ========================================
   更新処理
   ----------------------------------------
   内容：毎フレーム呼び出す処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItemManager::Update()
{
	for (auto i = m_pHealItemList.begin(); i != m_pHealItemList.end();i++)
	{
		(*i)->Update();
	}
}

/* ========================================
   描画処理
   ----------------------------------------
   内容：毎フレーム呼び出す処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItemManager::Draw()
{
	if (m_pHealItemList.size() == 0) { return; }

	for (auto i = m_pHealItemList.begin(); i != m_pHealItemList.end(); i++)
	{
		(*i)->Draw();
	}
}

/* ========================================
   生成処理
   ----------------------------------------
   内容：回復アイテムを指定した座標に生成する
   ----------------------------------------
   引数：座標
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItemManager::Create(TPos3d<float> pos)
{
	m_pHealItemList.push_back(new CHealItem(pos, m_pModel, m_pVS));	//生成
	m_pHealItemList.back()->SetCamera(m_pCamera);					//生成したアイテムにカメラをセット
}

/* ========================================
   回復アイテムコンテナ取得関数
   ----------------------------------------
   内容：回復アイテムのコンテナを取得する
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：回復アイテムのコンテナ
======================================== */
std::vector<CHealItem*>* CHealItemManager::GetHealItemConPtr()
{
	return &m_pHealItemList;
}

/* ========================================
   カメラ取得関数
   ----------------------------------------
   内容：カメラのポインタを取得する
   ----------------------------------------
   引数：カメラのポインタ
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItemManager::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}