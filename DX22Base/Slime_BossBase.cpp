/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ボススライムソース
	------------------------------------
	Slime_BossBase.cpp
	------------------------------------
	作成者	suzumura

	変更履歴
	・2023/11/17 クラス作成 suzumura
	・2023/11/23 Damage,IsDead関数を追加 suzumura
	・2023/11/27 HP表示追加 yamamoto
	・2023/11/28 影の描画を追加 nieda
	・2023/11/30 メモリリーク除去 takagi
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修・MessageBox改善 takagi

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
const float BOSS_HP_POSX = 8.6f;		//体力ゲージ（減る方）の位置

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
	, m_pHpFrame(nullptr)
	,m_pBossHp(nullptr)
{

	m_pBossHpTexture = new Texture();
	if (FAILED(m_pBossHpTexture->Create("Assets/Texture/Boss_Hp.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "HPゲージ読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);									//エラー通知
#endif
	}
	m_pBossHp = new C2dObject;
	m_pBossHp->SetTexture(m_pBossHpTexture);
	m_pHpFrameTexture = new Texture();
	if (FAILED(m_pHpFrameTexture->Create("Assets/Texture/Boss_HpFrame.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "HPフレーム読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);									//エラー通知
#endif
	}
	m_pHpFrame = new C2dObject;
	m_pHpFrame->SetTexture(m_pHpFrameTexture);
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

void CSlime_BossBase::Update()
{
	if (m_pBossHp)
	{
		m_pBossHp->SetTransform(m_Transform);
		m_pBossHp->Update();
	}
	if (m_pHpFrame)
	{
		m_pHpFrame->SetTransform(m_Transform);
		m_pHpFrame->Update();
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
void CSlime_BossBase::Draw() const
{
	// DrawFlgがtrueなら描画処理を行う
	if (m_bDrawFlg == false) return;

	//-- 影の描画
	m_pShadow->Draw();
	
	C3dObject::Draw();

	if (m_pBossHp)
	{
		m_pBossHp->Draw();
	}
	if (m_pHpFrame)
	{
		m_pHpFrame->Draw();
	}

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



