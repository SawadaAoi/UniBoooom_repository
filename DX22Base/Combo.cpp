/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	コンボUI用cpp
	------------------------------------
	Combo.cpp
	------------------------------------
	作成者
		澤田蒼生
	変更履歴
	・2023/11/21 作成 Sawada
	・2023/11/23 スコアを加算する処理の追加　yamamoto
	・2023/11/30 UIアニメーション追加　nieda
	・2023/12/07 ゲームパラメータから定数移動 takagi

========================================== */

// =============== インクルード ===================
#include "Combo.h"
#include "ExplosionManager.h"
#include "GameParameter.h"
#include "Pos2d.h"
#include "TotalScore.h"
#include "DiType.h"	//2つの同じ型を持つ型


// =============== 定数定義 =======================
const TTriType<float> COMBO_NUM_POS = { 930.0f, 120.0f, 1.0f };	// コンボUIの大きさ
const TTriType<float> COMBO_NUM_SIZE = { 70.0f, 130.0f, 1.0f };	// コンボUIの大きさ
const TDiType<float> COMBO_NUM_UV_SCALE = { 0.2f, 0.5f };

const float COMBO_UI_NUM_SPACE = 80.0f;							// 数字の間スペース
const float COMBO_UI_LINE_SPACE_X = 50.0f;						// 同時コンボ描画時の上下の空白
const float COMBO_UI_LINE_SPACE_Y = 100.0f;						// 同時コンボ描画時の上下の空白
const int COMBO_END_DISP_DILAY_TIME = int(2.0f * 60);			// 残コンボ数表示の秒数

const TTriType<float> COMBO_UI_BG_POS = { 1030.0f, 120.0f, 1.0f };	// コンボUIの背景の描画位置
const TTriType<float> COMBO_UI_BG_SIZE = { 370.0f, 300.0f, 1.0f };	// コンボUIの背景の大きさ
const TDiType<int> COMBO_UI_BG_SPLIT_NUM = { 3,3 };					// コンボUIの画像の縦横の分割数

const int COMBO_UI_BG_MAX_NUM = 7;					// BGアニメーション最大コマ数
const int SWITCH_COMBO_BG_ANIM_FLAME = 5;			// BGアニメーション切り替えの間隔

const std::string TEXTURE_PATH[CCombo::TEXTURE_KIND::TEX_MAX] =	// 画像パス
{
	{"Assets/Texture/Combo/combo_numbers.png"},
	{"Assets/Texture/Combo/combo_back_sprite_1.png"},
};

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CCombo::CCombo()
	: m_nMaxComboNum(0)
	, m_pTexNumber(nullptr)
{
	// 画像初期化
	for (int i = 0; i < TEXTURE_KIND::TEX_MAX; i++)
	{
		// 画像を読み込む
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(TEXTURE_PATH[i].c_str())))
		{
			MessageBox(NULL, "combo Texture", "Error", MB_OK);
		}
	}

	// コンボ情報の初期化
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_dComboInfo[i].dComboCnt = 0;
		m_dComboInfo[i].dDispFrame = 0;
		m_dComboInfo[i].bEndFlg = false;
		m_dComboInfo[i].dScore = 0;
		m_dComboInfo[i].nOldComboCnt = 0;		// 直前までのコンボ数格納用変数を初期化


		m_pComboBG[i] = new CDrawAnim(COMBO_UI_BG_MAX_NUM, COMBO_UI_BG_SPLIT_NUM, SWITCH_COMBO_BG_ANIM_FLAME);
		m_pComboBG[i]->SetTexture(m_pTexture[TEXTURE_KIND::TEX_BG]);
		m_pComboBG[i]->SetSize(COMBO_UI_BG_SIZE);
	}

	m_pTexNumber = new C2dPolygon();	// 数字画像初期化

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
CCombo::~CCombo()
{
	SAFE_DELETE(m_pTexNumber);

	for (int i = 0; i < 2; ++i)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
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
void CCombo::Update()
{
	// 発生コンボ数分
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		if (m_dComboInfo[i].dComboCnt == 0) continue;	// コンボが発生してない場合はスルー
		if (m_dComboInfo[i].bEndFlg)	continue;		// コンボが終了済みの場合はスルー

		m_pTotalScore->SetAddScore(m_dComboInfo[i],i);	// 加算スコアの値をセット

		m_pComboBG[i]->Update();	// コンボ背景のアニメーション更新

		// コンボ数が直前と違ったら
		if (m_dComboInfo[i].nOldComboCnt != m_dComboInfo[i].dComboCnt)	
		{
			m_pComboBG[i]->AnimReset();									// アニメーションをリセット
			m_dComboInfo[i].nOldComboCnt = m_dComboInfo[i].dComboCnt;	// 現在のコンボ数を格納
		}


	}
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画用処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CCombo::Draw()
{
	int lineCnt = 0;	// 表示するコンボUIの行番号

	// 発生コンボ数分
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// 0コンボは表示しない
		if (m_dComboInfo[i].dComboCnt == 0) continue;

		DispComboBG(i, lineCnt);							// コンボ背景
		DisplayNumber(m_dComboInfo[i].dComboCnt, lineCnt);	// 数字の表示

		// コンボが途切れた場合
		if (m_dComboInfo[i].bEndFlg)
		{
			// 暫くコンボ数を表示する
			m_dComboInfo[i].dDispFrame++;

			// 指定時間表示したらコンボ数の表示を消す
			if (COMBO_END_DISP_DILAY_TIME <= m_dComboInfo[i].dDispFrame )
			{
				if (m_nMaxComboNum < m_dComboInfo[i].dComboCnt)
				{
					m_nMaxComboNum = m_dComboInfo[i].dComboCnt;	// 最大コンボ数更新(リザルト用)
				}

				m_dComboInfo[i].dComboCnt		= 0;
				m_dComboInfo[i].dDispFrame		= 0;
				m_dComboInfo[i].bEndFlg			= false;
				m_dComboInfo[i].dScore			= 0;	
				m_dComboInfo[i].nOldComboCnt	= 0;	// コンボ数をリセット
				m_pComboBG[i]->AnimReset();
			}
		}

		lineCnt++;	// 同時に発生しているコンボ数を数える

	}
}

/* ========================================
	コンボ背景画像関数
	----------------------------------------
	内容：コンボ背景画像を表示する
	----------------------------------------
	引数1：配列番号
	引数2：同時発生の表示位置の調節値
	----------------------------------------
	戻値：なし
=========================================== */
void CCombo::DispComboBG(int ArrayNum, int lineNum)
{

	float shiftPosX = lineNum * COMBO_UI_LINE_SPACE_X;	// 横の表示位置調整値
	float shiftPosY = lineNum * COMBO_UI_LINE_SPACE_Y;	// 縦の表示位置調整値

	TTriType<float> pos = {
			COMBO_UI_BG_POS.x + shiftPosX,
			COMBO_UI_BG_POS.y + shiftPosY,
			1.0f };

	m_pComboBG[ArrayNum]->SetPos(pos);

	if (m_pComboBG[ArrayNum]->GetAnimFlg())
	{
		m_pComboBG[ArrayNum]->Draw();
	}
	else
	{
		m_pComboBG[ArrayNum]->SetAnimNum(COMBO_UI_BG_MAX_NUM);
		m_pComboBG[ArrayNum]->C2dPolygon::Draw();
	}
}

/* ========================================
	数字描画関数
	----------------------------------------
	内容：コンボ数を表示する
	----------------------------------------
	引数1：コンボ数
	引数2：同時発生の表示高さの調節値
	----------------------------------------
	戻値：なし
=========================================== */
void CCombo::DisplayNumber(int cnt, int lineNum)
{
	int num[2];			// 各桁数をセットする
	num[0] = cnt % 10;	// 一桁目
	num[1] = cnt / 10;	// 十桁目

	float shiftPosX = lineNum * COMBO_UI_LINE_SPACE_X;	// 横の表示位置調整値
	float shiftPosY = lineNum * COMBO_UI_LINE_SPACE_Y;	// 縦の表示位置調整値

	// 桁数分回す
	for (int i = 0; i < 2; i++)
	{
		// コンボ数が2桁以下で、一の桁以外の場合は表示しない(0埋めしない)
		if (cnt < 10 && i != 0 ) continue;

		// 桁ごとに位置をずらす
		float width = i * COMBO_UI_NUM_SPACE;

		TTriType<float> pos = {
			COMBO_NUM_POS.x - width + shiftPosX,
			COMBO_NUM_POS.y + shiftPosY,
			1.0f };

		int x = num[i] % 5;	// 数字テクスチャの横方向位置
		int y = num[i] / 5;	// 数字テクスチャの縦方向位置

		m_pTexNumber->SetPos(pos);
		m_pTexNumber->SetSize(COMBO_NUM_SIZE);
		m_pTexNumber->SetUvOffset({ COMBO_NUM_UV_SCALE.x * x, COMBO_NUM_UV_SCALE.y * y });// テクスチャUV座標
		m_pTexNumber->SetUvScale(COMBO_NUM_UV_SCALE);
		m_pTexNumber->SetTexture(m_pTexture[0]);

		m_pTexNumber->Draw();

	}
}



/* ========================================
	コンボ配列値セット関数
	----------------------------------------
	内容：爆発が発生した際にコンボ配列に値をセットする
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：配列の添え字
======================================== */
int CCombo::FirstComboSet()
{
	int num;	// 返すコンボ配列の添え字

	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// 既にコンボ数を数えている配列は飛ばす
		if (m_dComboInfo[i].dComboCnt != 0) continue;

		m_dComboInfo[i].dComboCnt++;	// 1コンボ目をセット
		num = i;				// 添え字を記録する
		break;					// コンボを記録したので抜ける
	}

	return num;
}

/* ========================================
	コンボ数加算関数
	----------------------------------------
	内容：爆発が発生した際にコンボ数を増やす
	----------------------------------------
	引数：配列の添え字
	----------------------------------------
	戻値：なし
======================================== */
void CCombo::AddCombo(int num)
{
	m_dComboInfo[num].dComboCnt++;

}

void CCombo::AddScore(int num, int combo)
{
	switch (num) {
	case LEVEL_1:		m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;
	case LEVEL_2:		m_dComboInfo[combo].dScore += LEVEL_2_SCORE;	break;
	case LEVEL_3:		m_dComboInfo[combo].dScore += LEVEL_3_SCORE;	break;
	case LEVEL_4:		m_dComboInfo[combo].dScore += LEVEL_4_SCORE;	break;
	case LEVEL_4x4:		m_dComboInfo[combo].dScore += LEVEL_4x4_SCORE;	break;
	case LEVEL_BOSS:	m_dComboInfo[combo].dScore += LEVEL_Boss_SCORE;	break;
	case LEVEL_FLAME:	m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;	// 炎スライムと爆発が接触した際は一番小さい爆発
	case LEVEL_HEAL:	m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;	// 回復スライムと爆発が接触した際は一番小さい爆発
	}
}

/* ========================================
	コンボ数取得関数
	----------------------------------------
	内容：対応添え字のコンボ数を取得する
	----------------------------------------
	引数：配列の添え字
	----------------------------------------
	戻値：コンボ数
======================================== */
int CCombo::GetComboNum(int num)
{
	return m_dComboInfo[num].dComboCnt;
}

/* ========================================
	コンボ終了フラグ取得関数
	----------------------------------------
	内容：対応添え字のコンボ終了フラグを取得する
	----------------------------------------
	引数：配列の添え字
	----------------------------------------
	戻値：コンボ終了フラグ
======================================== */
int CCombo::GetComboEndFlg(int num)
{
	return m_dComboInfo[num].bEndFlg;
}

/* ========================================
	最大コンボ数取得関数
	----------------------------------------
	内容：最大コンボ数を取得する
	----------------------------------------
	引数：無し
	----------------------------------------
	戻値：最大コンボ数
======================================== */
int CCombo::GetMaxCombo()
{
	return m_nMaxComboNum;
}

/* ========================================
	コンボ終了関数
	----------------------------------------
	内容：爆発の連鎖が終了した時の処理
	----------------------------------------
	引数：配列の添え字
	----------------------------------------
	戻値：無し
======================================== */
void CCombo::EndCombo(int num)
{
	m_dComboInfo[num].bEndFlg = true;					// コンボ終了フラグをオン
	
	m_pTotalScore->ComboCheck(m_dComboInfo[num], num);	// 倍率を決める
}

/* ========================================
	トータルスコア情報セット関数
	----------------------------------------
	内容：トータルスコア情報セット
	----------------------------------------
	引数1：トータルスコア
	----------------------------------------
	戻値：なし
======================================== */
void CCombo::SetTotalScore(CTotalScore* pTotalScore)
{
	m_pTotalScore = pTotalScore;
}




