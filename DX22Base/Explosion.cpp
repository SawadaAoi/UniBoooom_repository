//CPP用----------------------------------------------------
/*========================================
HEW/UniBoooom!!
---------------------------------------
爆発用cpp
---------------------------------------
Explosion.cpp

TeiUon

変更履歴
・2023/11/03 cpp作成 鄭宇恩
・2023/11/05 爆発cppの初期設定　鄭宇恩

======================================== */


//=============== インクルード ===================
#include "Explosion.h"
#include "Geometry.h"
#include <DirectXMath.h>

//=============== 定数定義 =======================
#define MAX_EXPLOSION_NUM (30)	//画面内最大爆発数(仮

//=============== プロトタイプ宣言 ===============

//=============== グローバル変数定義 =============
Model* m_pExplosion;

CExplosion::CExplosion()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
	
	m_pExplosion = new Model[MAX_EXPLOSION_NUM];				//爆発数の格納
	Position = DirectX::XMMatrixTranslation(1.0f, 1.0f, 1.0f);	//爆発位置初期化
	m_fSize = 1.0f;												//爆発の大きさ（スケール）
}

CExplosion::~CExplosion()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (m_pExplosion) {
			delete[] m_pExplosion;
			m_pExplosion = nullptr;
		}

	}
	
	
}

/*========================================
関数：Update関数
----------------------------------------
内容：爆発内の更新処理
----------------------------------------
引数：一旦なし
----------------------------------------
戻値：一旦なし
======================================== */

void CExplosion::Update()
{
	
}

/*========================================
関数：Draw関数
----------------------------------------
内容：爆発の描画処理
----------------------------------------
引数：一旦なし
----------------------------------------
戻値：一旦なし
======================================== */

void CExplosion::Draw()
{
	
	
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (m_pExplosion) {
			m_pExplosion->Draw();
		}
	}

	//CGeometory::DrawBox();
}

void CExplosion::DeleteExplosion()
{

}
