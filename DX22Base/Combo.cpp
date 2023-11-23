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

========================================== */

// =============== インクルード ===================
#include "Combo.h"
#include "ExplosionManager.h"
#include "GameParameter.h"
#include "Pos2d.h"
#include "TotalScore.h"
// =============== 定数定義 =======================
#if MODE_GAME_PARAMETER
#else
const TPos2d<float> COMBO_UI_POSITION = { 1100.0f,600.0f };
const TPos2d<float> COMBO_UI_SIZE = { 70.0f,70.0f };
const float COMBO_UI_NUM_SPACE = 80.0f;
const float COMBO_UI_MULTI_DISP_SPACE = 100.0f;
const int COMBO_UI_DISP_DILAY_TIME = 2.0f * 60;
#endif



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
	: m_pTextureNum(nullptr)
	, m_pTotalScore(nullptr)
{

	// 数字画像を読み込む
	m_pTextureNum = new Texture();
	if (FAILED(m_pTextureNum->Create("Assets/Texture/numbers_v1/number.png")))
	{
		MessageBox(NULL, "number.png", "Error", MB_OK);
	}

	// コンボ情報の初期化
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_dComboInfo[i].dCnt = 0;
		m_dComboInfo[i].dDispFrame = 0;
		m_dComboInfo[i].bEndFlg = false;
		m_dComboInfo[i].dScore = 0;
	}
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
	SAFE_DELETE(m_pTextureNum);
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
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		if (m_dComboInfo[i].dCnt == 0) continue;
		m_pTotalScore->AddScore(m_dComboInfo[i],i);
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
	int dispCnt = 0;	// 描画コンボ数
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// 0コンボは表示しない
		if (m_dComboInfo[i].dCnt == 0) continue;

		float shiftPosY = dispCnt * COMBO_UI_MULTI_DISP_SPACE;	// コンボ同時表示の際の上下の空白をセット
		DisplayNumber(m_dComboInfo[i].dCnt, shiftPosY);			// 数字の表示

		// コンボが途切れた場合
		if (m_dComboInfo[i].bEndFlg == true)
		{	
			// 暫くコンボ数を表示する
			m_dComboInfo[i].dDispFrame++;
			// 指定時間表示したらコンボ数の表示を消す
			if (m_dComboInfo[i].dDispFrame >= COMBO_UI_DISP_DILAY_TIME)
			{
				m_dComboInfo[i].dCnt = 0;
				m_dComboInfo[i].dDispFrame = 0;
				m_dComboInfo[i].bEndFlg = false;
			}
		}

		dispCnt++;	// 同時に発生しているコンボ数を数える

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
void CCombo::DisplayNumber(int cnt, float shiftPosY)
{
	DirectX::XMFLOAT4X4 mat[3];	// 描画用の行列

	int num[2];			// 各桁数をセットする
	num[0] = cnt % 10;	// 一桁目
	num[1] = cnt / 10;	// 十桁目

	// 桁数分回す
	for (int j = 0; j < 2; j++)
	{
		// コンボ数が2桁以下で、一の桁以外の場合は表示しない(0埋めしない)
		if (cnt < 10 && j != 0 ) continue;

		// 桁ごとに位置をずらす
		float width = j * COMBO_UI_NUM_SPACE;

		//ワールド行列はXとYのみを考慮して作成
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(COMBO_UI_POSITION.x - width, COMBO_UI_POSITION.y - shiftPosY, 0.0f);
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

		//プロジェクション行列には2Dとして表示するための行列を設定する
		//この行列で2Dのスクリーンの多いさが決まる
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
		DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

		//スプライトの設定
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(COMBO_UI_SIZE.x, -COMBO_UI_SIZE.y));
		//spriteシートの上部分表示（0～4）
		if (num[j] < 5)
		{
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * num[j], 0.0f));
		}
		//spriteシートの下部分表示（5～9）
		else
		{
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f * (num[j] - 5), 0.5f));
		}
		Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
		Sprite::SetTexture(m_pTextureNum);
		Sprite::Draw();
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
		if (m_dComboInfo[i].dCnt != 0) continue;

		m_dComboInfo[i].dCnt++;	// 1コンボ目をセット
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
	m_dComboInfo[num].dCnt++;

}

void CCombo::AddScore(int num, int combo)
{
	switch (num) {
	case LEVEL_1:		m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;
	case LEVEL_2:		m_dComboInfo[combo].dScore += LEVEL_2_SCORE;	break;
	case LEVEL_3:		m_dComboInfo[combo].dScore += LEVEL_3_SCORE;	break;
	case LEVEL_4:		m_dComboInfo[combo].dScore += LEVEL_4_SCORE;	break;
	case LEVEL_4x4:		m_dComboInfo[combo].dScore += LEVEL_4x4_SCORE;	break;
	case LEVEL_FLAME:	m_dComboInfo[combo].dScore += LEVEL_1_SCORE;	break;	// 炎スライムと爆発が接触した際は一番小さい爆発
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
int CCombo::GetCombo(int num)
{
	return m_dComboInfo[num].dCnt;
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
	m_dComboInfo[num].bEndFlg = true;	// コンボ終了フラグをオン
	m_pTotalScore->ComboCheck(m_dComboInfo[num], num);	//倍率を決める
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



