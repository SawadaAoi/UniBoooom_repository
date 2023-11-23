/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem用cpp
	------------------------------------
	HealItem.cpp
	------------------------------------
	作成者
		yamashita
	変更履歴
	・2023/11/23 cpp作成 yamashita
========================================== */

#include "HealItem.h"
#include "DirectWrite.h"

// =============== 定数定義 =====================
const float HEAL_ITEM_SCALE_X = 1.0f;		//アイテムのスケールX
const float HEAL_ITEM_SCALE_Y = 1.0f;		//アイテムのスケールY
const float HEAL_ITEM_SCALE_Z = 1.0f;		//アイテムのスケールZ
const int	HEALITEM_DELETE_TIME = 5 * 60;	//アイテムが消えるまでの時間

/* ========================================
   関数：コンストラクタ
   ----------------------------------------
   内容：生成時に行う処理
   ----------------------------------------
   引数：プレイヤーの座標ポインタ
   ----------------------------------------
   戻値：なし
======================================== */
CHealItem::CHealItem()
	:m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_pCamera(nullptr)
{
	//頂点シェーダ読み込み
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//床のモデル読み込み
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/heart/heart.FBX", 0.01f, Model::XFlip)) {		//倍率と反転は省略可
		MessageBox(NULL, "floor", "Error", MB_OK);	//ここでエラーメッセージ表示
	}
	m_pModel->SetVertexShader(m_pVS);
}

/* ========================================
   関数：デストラクタ
   ----------------------------------------
   内容：終了時に行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
CHealItem::~CHealItem()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);

	for (auto i = m_healItem.begin(); i != m_healItem.end();)
	{
		i = m_healItem.erase(i);
	}
	m_healItem.clear();
}

/* ========================================
	アップデート関数
   ----------------------------------------
   内容：毎フレーム行う処理
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItem::Update()
{
	for (auto i = m_healItem.begin(); i != m_healItem.end();)
	{
		if (i->m_bUse == true)
		{
			//カウント増加
			i->m_Cnt++;
			float radian = i->m_Cnt % 360;
			i->m_Transform.fPos.y = sin(DirectX::XMConvertToRadians((float)radian)) * 0.5f;	//上下にゆらゆらする
			i->m_Transform.fRadian.y = DirectX::XMConvertToRadians((float)radian);			//Y軸でくるくる回転する

			//カウントが一定以上なら消去
			if (i->m_Cnt >= HEALITEM_DELETE_TIME) { i->m_bUse = false; }

			i++;	//次のコンテナに移動
		}
		else	//bUseがfalseなら消去
		{
			//消去して自動的に次のコンテナに移動
			i = m_healItem.erase(i);
		}


		
	}
}

/* ========================================
   描画関数
   ----------------------------------------
   内容：オブジェクトの描画
   ----------------------------------------
   引数：なし
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItem::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	for (auto i = m_healItem.begin();i != m_healItem.end(); i++)
	{
		//Transformの関数を使うと角度の計算がX→Y→Zの順番だがY→X→Zの順番にしたいため手動で変換行列を書いた
		DirectX::XMMATRIX worldMat;
		worldMat = DirectX::XMMatrixScaling(i->m_Transform.fScale.x, i->m_Transform.fScale.y, i->m_Transform.fScale.z) *	//拡縮
			DirectX::XMMatrixRotationY(i->m_Transform.fRadian.y) * DirectX::XMMatrixRotationX(i->m_Transform.fRadian.x) *	//Y回転→X回転
			DirectX::XMMatrixTranslation(i->m_Transform.fPos.x, i->m_Transform.fPos.y, i->m_Transform.fPos.z);				//移動
		worldMat = DirectX::XMMatrixTranspose(worldMat);	//転置
		DirectX::XMFLOAT4X4 a;					//mat[0]に入れる変数
		DirectX::XMStoreFloat4x4(&a, worldMat);	//Matrix型からfloat4x4に変換

		
		//mat[0] = i->m_Transform.GetWorldMatrixSRT();
		mat[0] = a;
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();

		//-- 行列をシェーダーへ設定
		m_pVS->WriteBuffer(0, mat);

		//-- モデル表示
		if (m_pModel) {
			m_pModel->Draw();
		}
	}
}

/* ========================================
   ヒールアイテム生成関数
   ----------------------------------------
   内容：
   ----------------------------------------
   引数：生成する座標
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItem::Create(TPos3d<float> pos)
{
	//構造体の変数を初期化
	HEAL_ITEM healItem;
	healItem.m_Transform.fPos = pos;
	healItem.m_Transform.fScale = { HEAL_ITEM_SCALE_X ,HEAL_ITEM_SCALE_Y ,HEAL_ITEM_SCALE_Z };
	healItem.m_Transform.fRadian = {DirectX::XMConvertToRadians(70.0f),0.0f,0.0f};
	healItem.m_Cnt = 0;
	healItem.m_bUse = true;

	//初期化した変数をコンテナに格納
	m_healItem.push_back(healItem);
}

/* ========================================
   カメラセット関数
   ----------------------------------------
   内容：他のオブジェクトと同じカメラをセットする
   ----------------------------------------
   引数：カメラのポインタ
   ----------------------------------------
   戻値：なし
======================================== */
void CHealItem::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
