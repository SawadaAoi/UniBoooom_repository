/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	BoooomUI表示
	------------------------------------
	BoooomUI.cpp
	------------------------------------
	作成者
		鄭宇恩
	変更履歴
	・2023/11/20 cpp,作成 Tei
	・2023/11/20 描画で必要な関数を作成 Tei
	・2023/12/07 ゲームパラメータから定数移動 takagi

========================================== */

// =============== インクルード ===================
#include "BoooomUI.h"

// =============== 定数定義 ===================
const int MAX_ANIM(1);			//アニメーション数
const TDiType<int> MAX_SEAT(1);	//1x1

const float BOOOOM_UI_SIZE_X = 1.0f;		//BoooomUIのXの長さ（textureの比率と合わせる）
const float BOOOOM_UI_SIZE_Y = 0.565f;		//BoooomUIのYの長さ（textureの比率と合わせる）
const float BOOOOM_UI_SCALE_X = 6.0f;		//BoooomUIサイズのスケール
const float BOOOOM_UI_SCALE_Y = 6.0f;		//BoooomUIサイズのスケール

const float BOOOOM_UI_MAX_SCALE_X = BOOOOM_UI_SCALE_X * 2.5f;
const float BOOOOM_UI_MAX_SCALE_Y = BOOOOM_UI_SCALE_Y * 2.5f;

const float ANIM_TIME_RATE = 0.7f;	// 爆発総時間の内、BOOOOM表示を行うのは何割か(0.0f~1.0f)

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CBoooomUI::CBoooomUI(TPos3d<float> pos, Texture* pTex, const CCamera* pCamera, float fTime /*,const int & nFrame*/)
	://m_pBoooomTex(pTex)
	//,m_pos(pos)
	//,m_scale{ BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f}
	 m_fExplodeTime(fTime * ANIM_TIME_RATE)	//爆発総時間をセットする
	, m_nDelFrame(0)
	, m_bDelFlg(false)
	, m_nAnimFrame(0)
	, m_fAnimRate(0.0f)
	, m_fAddScaleX(0.0f)
	, m_fAddScaleY(0.0f)
	, m_fScalingTime(fTime * ANIM_TIME_RATE)
	, CDrawAnim(MAX_ANIM, MAX_SEAT)	//委譲
	, m_pCnt(nullptr)				//縮小用カウンタ
{

	SetCamera(pCamera);		//カメラセット
	SetPos(pos);
	SetSize(TTriType<float>(BOOOOM_UI_SCALE_X, BOOOOM_UI_SCALE_Y, 0.0f));
	SetTexture(pTex);
	m_pCnt = new CFrameCnt((int)m_fScalingTime);	//カウント開始

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
CBoooomUI::~CBoooomUI()
{
	SAFE_DELETE(m_pCnt);

}

void CBoooomUI::Update()
{
	// =============== 更新 ===================
	CDrawAnim::Update();	//親の関数使用
	

	DisplayTimeAdd();
	//TODO爆発連鎖するときのスケール ?

	m_nAnimFrame++;

	float fExpandTime = m_fScalingTime / 2.0f;
	if (m_nAnimFrame < (int)fExpandTime)
	{
		m_fAnimRate += 1.0f / fExpandTime ;	//フレーム加算
		
	}
	else if(m_nAnimFrame > 0)
	{
		m_fAnimRate -= 1.0f / (m_fScalingTime - fExpandTime);	//フレーム減算

		//-- 徐々に消えていく処理
		if (m_pCnt)	//ヌルチェック
		{
			--*m_pCnt;	//カウントダウン
			if (m_pCnt->IsFin())
			{
				delete m_pCnt;		//メモリ解放
				m_pCnt = nullptr;	//空アドレス代入
			}
			else
			{
				SetAlpha(m_pCnt->GetRate());					//透明度更新
			}
		}
	}
	// 0を下回らないように
	if (m_fAnimRate < 0) m_fAnimRate = 0;

	// 補間値を使用してスケールを計算
	float scalingFactor = (sqrt(1 - pow(m_fAnimRate - 1, 2)));
	// スケールの設定
	SetSize(TTriType<float>(BOOOOM_UI_SCALE_X + ((BOOOOM_UI_MAX_SCALE_X - BOOOOM_UI_SCALE_X) * scalingFactor),
		BOOOOM_UI_SCALE_Y + ((BOOOOM_UI_MAX_SCALE_Y - BOOOOM_UI_SCALE_Y) * scalingFactor),0.0f));
	// uvのズレを調整
	SetUvScale(TDiType<float>(1.0f, 1.565f));


}

/* ========================================
	描画関数
	----------------------------------------
	内容：Boooomの描画
	----------------------------------------
	引数1：描画モード
	----------------------------------------
	戻値：なし
=========================================== */
void CBoooomUI::Draw(const E_DRAW_MODE & eMode)
{
	if (m_pCnt)	//ヌルチェック
	{
		// =============== 描画 ===================
		CDrawAnim::Draw();	//親の関数使用
		if (!m_bAnim)	//アニメーション部分の描画が終わっている
		{
			C2dPolygon::Draw(E_DRAW_MODE_BILLBOARD);	//最後の場面を描き続ける
		}
	}
}

/* ========================================
	boooomUI表示カウント加算処理関数
	-------------------------------------
	内容：boooomUI表示カウントを加算して一定秒数超えたら終了フラグをオンにする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CBoooomUI::DisplayTimeAdd()
{
	m_nDelFrame++;		// フレーム加算

	// 一定秒数時間が経ったら
	if (m_fExplodeTime <= m_nDelFrame)
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
bool CBoooomUI::GetDelFlg()
{
	return m_bDelFlg;
}


/* ========================================
	終了確認関数
	-------------------------------------
	内容：終了確認
	-------------------------------------
	引数：なし
	-------------------------------------
	戻値：このオブジェクトの役目が終了したか
=========================================== */
bool CBoooomUI::IsFin()
{
	if (m_pCnt)
	{
		// =============== 提供 ===================
		return false;	//カウンタが存在する
	}
	else
	{
		// =============== 提供 ===================
		return true;	//カウンタが存在しない
	}
}