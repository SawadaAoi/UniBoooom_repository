/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージ1実装
	---------------------------------------
	Stage1.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/05 制作 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 Prot.cpp→Stage1.cpp takagi

========================================== */

// =============== インクルード ===================
#include "Stage1.h"	//自身のヘッダ
#include "CameraChase.h"


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CStage1::CStage1()
	: m_nNum(0)
	, m_fSize(100.0f)
	, m_bStart(false)
{
	// 頂点シェーダの読込
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/text_start.png")))
	{
		MessageBox(NULL, "Stage1 text_start.png", "Error", MB_OK);
	}

	// レンダーターゲット、深度バッファの設定
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる

	m_pCollision = new CCOLLISION();
	m_pPlayer = new CPlayer();
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());
	m_pPlayer->SetCamera(m_pCamera);

	m_pFloor = new CFloor(m_pPlayer->GetPosAddress());
	m_pFloor->SetCamera(m_pCamera);
	// スライムマネージャー生成
	m_pSlimeMng = new CSlimeManager();
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pExplosionMng = new CExplosionManager();
	m_pExplosionMng->SetCamera(m_pCamera);

	// タイマー生成
	m_pTimer = new CTimer();
	m_pTimer->TimeStart();
}

/* ========================================
	デストラクタ
	----------------------------------------
	内容：破棄時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CStage1::~CStage1()
{
	SAFE_DELETE(m_pTimer);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// スライムマネージャー削除
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);
	SAFE_DELETE(m_pVs);
}

/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CStage1::Update()
{
	if (!m_bStart)
	{
		m_nNum++;
		if (m_nNum > 10)
		{
			m_fSize += 10.0f;
		}

		if (m_nNum > 50)
		{
			m_bStart = true;
		}
	}
	else
	{
		m_pCamera->Update();
		m_pPlayer->Update();
		m_pSlimeMng->SetPlayerPos(m_pPlayer->GetPos());

		// スライムマネージャー更新
		m_pSlimeMng->Update(m_pExplosionMng);
		m_pExplosionMng->Update();
		m_pTimer->Update();

		Collision();
	}
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
//!memo(見たら消してー)：constが邪魔になったら外してね(.hの方も)
void CStage1::Draw()
{
	if (!m_bStart)
	{
		Draw2d(600.0f, 300.0f, m_fSize, m_fSize, m_pTexture);
	}

	//床の描画
	m_pFloor->Draw();
	// スライムマネージャー描画
	m_pSlimeMng->Draw();
	m_pPlayer->Draw();

	//爆発マネージャー描画
	m_pExplosionMng->Draw();

	//タイマー描画
	m_pTimer->Draw();
	
}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がステージ1であることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CStage1::E_TYPE CStage1::GetType() const
{
	// =============== 提供 ===================
	return CStage1::E_TYPE_STAGE1;	//自身の種類
}

/* ========================================
	次シーンゲッタ
	----------------------------------------
	内容：遷移したいシーンが何かを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：遷移先シーンの種類
=========================================== */
CStage1::E_TYPE CStage1::GetNext() const
{
	// =============== 提供 ===================
	return CStage1::E_TYPE_RESULT;	//遷移先シーンの種類
}
