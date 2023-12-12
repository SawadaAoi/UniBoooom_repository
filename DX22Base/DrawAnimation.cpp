/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	UIアニメーション描画用cpp
	---------------------------------------
	DrawAnimation.h

	作成者
			nieda

	変更履歴
	・2023/12/08 新規作成 nieda
	・2023/12/09 続き nieda
	・2023/12/11 続き nieda
	・2023/12/12 tkg先生の指導により2dpolygonに対応 nieda

========================================== */

// =============== インクルード ===================
#include "DrawAnimation.h"	// 自身のヘッダ


/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：読み込むファイルのパス
	引数2：カメラクラスのポインタ
	引数3：分割数の最大数
	引数4：縦横の分割数の最大数
	引数5：アニメーションの切り替え間隔
	----------------------------------------
	戻値：なし
=========================================== */
CDrawAnim::CDrawAnim(const char* textureFile, CCamera* pCamera, int nMax, TDiType<int> nCut, int nCntSwitch)
	: m_nNumAnim(0)
	, m_nNumAnimMax(0)
	, m_NumCut(0, 0)
	, m_fUvpos(0.0f, 0.0f)
	, m_fUvscale(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntFrame(0)
	, bRoop(true)
{
	SetTexture(textureFile);	// テクスチャをセット
	SetCamera(pCamera);			// カメラをセット
	m_fUvscale = { 1.0f / m_NumCut.x, 1.0f / m_NumCut.y };	// UV分割サイズを格納
	m_nNumAnimMax = nMax;		// 分割数の最大値を格納
	m_NumCut = nCut;			// 縦横の分割数を格納
	m_nCntSwitch = nCntSwitch;	// アニメーションの切り替え間隔を格納
}

/* ========================================
	2Dアニメーション更新関数
	-------------------------------------
	内容：2Dアニメーションの更新処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CDrawAnim::Update()
{
	if (bRoop)
	{
		m_nCntFrame++;	// 描画切り替え用カウントを1進める

		if (m_nCntFrame > m_nCntSwitch)		// 一定時間経過したら描画を更新する
		{
			m_nCntSwitch = 0;	// カウントをリセット
			m_fUvpos.x = (m_fUvscale.x) * (m_nNumAnim % m_NumCut.x);	// 描画するUV座標を計算
			m_fUvpos.y = (m_fUvscale.y) * (m_nNumAnim / m_NumCut.x);	// 描画するUV座標を計算

			m_nNumAnim++;			// 描画するアニメーション番号を更新
			SetUvOffset(m_fUvpos);	// UV座標をセット
			SetUvScale(m_fUvscale);	// UV分割サイズをセット
		}

		if (m_nNumAnim == m_nNumAnimMax)		// 最下段の描画が終わったら
		{
			m_nNumAnim = 0;		// カウントをリセット
			bRoop = false;		// 表示フラグをOFF
		}
	}
}

/* ========================================
	2Dアニメーション描画関数
	-------------------------------------
	内容：2Dアニメーションの描画処理
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CDrawAnim::Draw()
{
	if (bRoop)	// 描画フラグがONの間は描画する
	{
		C2dPolygon::Draw();		// 描画
	}
}
