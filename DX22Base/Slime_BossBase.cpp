/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライム.cpp
	------------------------------------
	Slime_Boss.cpp
	------------------------------------
	作成者	鈴村朋也

	変更履歴
	・2023/11/17 クラス作成 Suzumura
	・2023/11/23 Damage,IsDead関数を追加 Suzumura
	・2023/11/27 HP表示追加 yamamoto
	・2023/11/28 影の描画を追加 nieda
	・2023/11/30 メモリリーク除去 takagi

========================================== */

// =============== インクルード ===================
#include "Slime_BossBase.h"
#include "Sprite.h"
// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const float SLIME_HP_HEIGHT = 5.0f;		//ボスの体力表示位置（Y）
const float BOSS_HP_SIZEX = 0.3f;		//体力１分の大きさ（X）
const float BOSS_HP_SIZEY = 0.5f;		//体力１分の大きさ（Y）
const float BOSS_HPFRAME_SIZEX = 0.2f;	//体力ゲージよりどれだけ大きいか（X）
const float BOSS_HPFRAME_SIZEY = 0.2f;	//体力ゲージよりどれだけ大きいか（Y）
const float BOSS_HP_POSX = 17.0f;		//体力ゲージ（減る方）の位置

const int BOSS_DAMAGE_FLASH_FRAME = 0.1 * 60;					// ダメージ受けた際の点滅フレーム(無敵ではない)
const int BOSS_DAMAGE_FLASH_TOTAL_FRAME = 0.5 * 60;					// ダメージを受けた際の点滅を何フレーム行うか


#endif
/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：コンストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_BossBase::CSlime_BossBase()
	: m_nHp(0)
	, m_nMaxHp(0)
	, m_bDead(false)
	, m_nInvFrame(0)
	, m_bDrawFlg(true)
	, m_bFlash(false)
	, m_pBossHpTexture(nullptr)
	, m_pHpFrameTexture(nullptr)
	, m_nMoveState(0)	// 0はNormal
{

	m_pBossHpTexture = new Texture();
	if (FAILED(m_pBossHpTexture->Create("Assets/Texture/Boss_Hp.png")))
	{
		MessageBox(NULL, "HPゲージ読み込み", "Error", MB_OK);
	}
	m_pHpFrameTexture = new Texture();
	if (FAILED(m_pHpFrameTexture->Create("Assets/Texture/Boss_HpFrame.png")))
	{
		MessageBox(NULL, "HPフレーム読み込み", "Error", MB_OK);
	}
	
}


/* ========================================
	デストラクタ関数
	-------------------------------------
	内容：デストラクタ
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
CSlime_BossBase::~CSlime_BossBase()
{
	// =============== 終了 ===================
	delete m_pBossHpTexture;		//メモリ解放
	m_pBossHpTexture = nullptr;		//空アドレス代入
	delete m_pHpFrameTexture;		//メモリ解放
	m_pHpFrameTexture = nullptr;	//空アドレス代入
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数1：プレイヤー座標(TPos3d)
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_BossBase::Update(tagTransform3d playerTransform)
{
	m_PlayerTran = playerTransform;

	if (!m_bHitMove)	//敵が通常の移動状態の時
	{
		NormalMove();
	}
	else
	{
		//敵の吹き飛び移動
		HitMove();
	}

	// -- 座標更新
	m_Transform.fPos.x += m_move.x;
	m_Transform.fPos.z += m_move.z;

	// ダメージ発生中じゃないなら点滅処理を行わない
	if (m_bFlash == false) return;
	// 点滅処理
	m_nInvFrame++;						//毎フレームでカウントを追加
	if (0 == m_nInvFrame % BOSS_DAMAGE_FLASH_FRAME)
	{
		// 描画するかしない切り替え
		if (m_bDrawFlg)
		{
			m_bDrawFlg = false;	// true→false
		}
		else
		{
			m_bDrawFlg = true;	// false→true
		}

	}
	// 総点滅時間を過ぎたら終了
	if (m_nInvFrame >= BOSS_DAMAGE_FLASH_TOTAL_FRAME)
	{
		m_bFlash = false;
		m_nInvFrame = 0;
		m_bDrawFlg = true;
	}
}

/* ========================================
	描画処理関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数1：カメラ
	-------------------------------------
	戻値：無し
=========================================== */
void CSlime_BossBase::Draw(const CCamera* pCamera)
{
	// DrawFlgがtrueなら描画処理を行う
	if (m_bDrawFlg == false) return;

	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = pCamera->GetViewMatrix();
	mat[2] = pCamera->GetProjectionMatrix();

	//-- 行列をシェーダーへ設定
	m_pVS->WriteBuffer(0, mat);

	//-- モデル表示
	if (m_pModel) {
		// レンダーターゲット、深度バッファの設定
		RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
		DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
		SetRenderTargets(1, &pRTV, pDSV);		//DSVがnullだと2D表示になる
		m_pModel->Draw();
	}
	
	//-- 影の描画
	m_pShadow->Draw(pCamera);

	//HP表示
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, nullptr);		//DSVがnullだと2D表示になる

	mat[1] = pCamera->GetViewMatrix();
	mat[2] = pCamera->GetProjectionMatrix();
	DirectX::XMFLOAT4X4 inv;//逆行列の格納先
	inv = pCamera->GetViewMatrix();

	//カメラの行列はGPUに渡す際に転置されているため、逆行列のために一度元に戻す
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixTranspose(matInv);

	//移動成分は逆行列で打ち消す必要が無いので0を設定して移動を無視する
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);



	//フレーム
	DirectX::XMMATRIX world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y + SLIME_HP_HEIGHT, m_Transform.fPos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	Sprite::SetSize(DirectX::XMFLOAT2(3.2f, 0.7f));

	Sprite::SetUVPos(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));


	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetTexture(m_pHpFrameTexture);
	Sprite::Draw();


	HPWidth = 3.0f / m_nMaxHp;	
	float width = (HPWidth /2)*(m_nMaxHp - m_nHp);
	

	 world = matInv * DirectX::XMMatrixTranslation(m_Transform.fPos.x - width, m_Transform.fPos.y+ SLIME_HP_HEIGHT, m_Transform.fPos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));
	Sprite::SetSize(DirectX::XMFLOAT2(HPWidth*m_nHp, BOSS_HP_SIZEY));
	
	Sprite::SetUVPos(DirectX::XMFLOAT2(1.0f,1.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f,1.0f));

	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetTexture(m_pBossHpTexture);
	Sprite::Draw();

}


/* ========================================
	ワープ関数
	-------------------------------------
	内容：ボスが離れすぎたら近くにワープ
	-------------------------------------
	引数1：プレイヤー座標(TPos3d)
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_BossBase::Warp(TPos3d<float> playerPos)
{

}

/* ========================================
	ダメージ関数
	-------------------------------------
	内容：ボスにダメージを与える関数
	-------------------------------------
	引数1：ダメージ量
	-------------------------------------
	戻値：なし
=========================================== */
void CSlime_BossBase::Damage(int num)
{
	m_nHp -= num;		// HP減少
	m_bFlash = true;	// 点滅ON

	if (m_nHp <= 0) m_bDead = true;	// HPが０以下なら死亡
}

/* ========================================
	生死確認関数
	-------------------------------------
	内容：ボスが死んでいるかどうかを返す
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：死んでいるかどうか(bool)
=========================================== */
bool CSlime_BossBase::IsDead()
{
	return m_bDead;
}


/* ========================================
	移動種類取得関数
	-------------------------------------
	内容：ボスの現在の移動の種類を返す
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：移動種類
=========================================== */
int CSlime_BossBase::GetMoveState()
{
	return m_nMoveState;
}



