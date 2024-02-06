/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	結合エフェクト描画
	---------------------------------------
	UnionEffectText.cpp

	作成者
			Tei

	変更履歴
	・2024/02/06 結合エフェクト nieda

========================================== */

// =============== インクルード ===================
#include "UnionSmokeEffect.h"
#include "Defines.h"
#include "GameParameter.h"

// =============== 定数定義 ===================
const int UNION_SMOKE_SPLIT_NUM_MAX = 55;				// 結合の煙アニメーションの分割数の最大数
const TDiType<int> UNION_SMOKE_SPLIT_NUM = { 5, 11 };	// 結合の煙アニメーションの縦横分割数の最大数
const int UNION_SMOKE_SWITCH_CNT = 1;					// アニメーション切り替え間隔

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：生成座標（x,y,z）
	引数2：生成サイズ（x,y,z）
	引数3：読み込むの画像
	引数4：カメラクラスのポインタ
	----------------------------------------
	戻値：なし
=========================================== */
CUnionSmokeEffect::CUnionSmokeEffect(TPos3d<float> pos, TPos3d<float> size, Texture* pTex, const CCamera * pCamera)
	: CDrawAnim(UNION_SMOKE_SPLIT_NUM_MAX, UNION_SMOKE_SPLIT_NUM, UNION_SMOKE_SWITCH_CNT)
	, m_bDelFlg(false)
	, m_nDelFrame(0)
	, m_fEffectTime(UNION_SMOKE_SPLIT_NUM_MAX)
{
	m_pTexUnionSmoke = new CDrawAnim(UNION_SMOKE_SPLIT_NUM_MAX, UNION_SMOKE_SPLIT_NUM, UNION_SMOKE_SWITCH_CNT);
	m_pTexUnionSmoke->SetCamera(pCamera);
	m_pTexUnionSmoke->SetTexture(pTex);
	m_pTexUnionSmoke->SetPos(pos);
	m_pTexUnionSmoke->SetSize(size);
	m_pTexUnionSmoke->SetLoopFlg(false);
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
CUnionSmokeEffect::~CUnionSmokeEffect()
{
	SAFE_DELETE(m_pTexUnionSmoke);
}

/* ========================================
	更新関数
	-------------------------------------
	内容：結合エフェクトの更新処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CUnionSmokeEffect::Update()
{
	// アニメションの速度速くするため、二回行う（力技）
	m_pTexUnionSmoke->Update();
	m_pTexUnionSmoke->Update();
	DisplayTimeAdd();
}

/* ========================================
	描画関数
	-------------------------------------
	内容：結合エフェクトの描画処理
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CUnionSmokeEffect::Draw()
{
	m_pTexUnionSmoke->Draw(E_DRAW_MODE_BILLBOARD);
}

/* ========================================
	結合エフェクト表示カウント加算処理関数
	-------------------------------------
	内容：結合エフェクト表示カウントを加算して再生秒数経ったら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CUnionSmokeEffect::DisplayTimeAdd()
{
	m_nDelFrame++;	// フレーム加算

	// 再生秒数経ったら削除
	if (m_fEffectTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// 削除フラグを立てる
	}
}

/* ========================================
	削除フラグ取得処理関数
	-------------------------------------
	内容：削除フラグを取得する
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：削除フラグ(bool)
=========================================== */
bool CUnionSmokeEffect::GetDelFlg()
{
	return m_bDelFlg;
}
