/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スコア管理用cpp
	---------------------------------------
	TotalScore.cpp

	作成者	山本凱翔

	変更履歴
	・2023/11/22　作成

========================================== */

// =============== インクルード ===================
#include "TotalScore.h"
#include "Sprite.h"

/* ========================================
	関数：コンストラクタ
	-------------------------------------
	内容：実行時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CTotalScore::CTotalScore()
	: m_nTotalScore(0)
	, m_pToScoreTexture(nullptr)
	, TotalScoreArray{}
	, digitArray{}
	, nArraySize(0)
	, digits{}
{
	m_pToScoreTexture = new Texture();
	if (FAILED(m_pToScoreTexture->Create("Assets/Texture/numbers_v1/combo_numbers.png")))
	{
		MessageBox(NULL, "ToScore数字読み込み", "Error", MB_OK);
	}
	for (int i = 0; i < TOTALSCORE_DIGIT; i++)//トータルスコアの桁を作る
	{
		TotalScoreArray.push_back(0);
	}
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_PlusScore[i].nAddScore = 0;
		m_PlusScore[i].fComboMagnification = 0;
		m_PlusScore[i].bEndComboFlg = false;
		m_PlusScore[i].bDispTotalScoreFlg = true;
		m_PlusScore[i].nDispFrame = 0;
	}
}
/* ========================================
	関数：デストラクタ
	-------------------------------------
	内容：破棄時に行う処理
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
CTotalScore::~CTotalScore()
{
	SAFE_DELETE(m_pToScoreTexture);
	TotalScoreArray.clear();
}
void CTotalScore::Update()
{
	
}
/* ========================================
	関数：描画関数
	----------------------------------------
	内容：爆発マネージャーの描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::Draw()
{
	DirectX::XMFLOAT4X4 time[3];
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&time[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&time[2], DirectX::XMMatrixTranspose(proj));
	
	//トータルスコア（一番右上）の描画設定
	//スプライトの設定
	Sprite::SetView(time[1]);
	Sprite::SetProjection(time[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pToScoreTexture);

	for (int i = 0; i < TOTALSCORE_DIGIT; i++)
	{
		int width = 50 * i;
		//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y, 0.0f);
		DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

		//スプライトの設定
		Sprite::SetWorld(time[0]);
		
		int y = TotalScoreArray[i] % 5;	//ここ名前募集します
		int x = TotalScoreArray[i] / 5;	//配列に入ってる数字の場所を計算してます
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));
		Sprite::Draw();
	}
	//加算予定のスコア（トータルの下）の描画設定サイズ以外は同じなので省略
	Sprite::SetSize(DirectX::XMFLOAT2(30.0f, -30.0f));

	for (int i = 0, lineNum=1; i < MAX_COMBO_NUM; i++)
	{
		if (m_PlusScore[i].nAddScore == 0)continue;//何もなければスルー

		if (m_PlusScore[i].bDispTotalScoreFlg == true) 
		{

 			digitArray = digitsToArray(m_PlusScore[i].nAddScore);	
			nArraySize = digitArray.size();				//何桁か確認
			for (int i = 0; i < nArraySize; i++)
			{
				int width = 30 * i;
				int hight = 40 * lineNum;
				//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//スプライトの設定
				Sprite::SetWorld(time[0]);

				int y = digitArray[i] % 5;	//ここ名前募集します
				int x = digitArray[i] / 5;	//配列に入ってる数字の場所を計算してます
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));

				Sprite::Draw();
			}
			lineNum++;
		}
		else
		{
			AddTotalScore();
			m_PlusScore[i].bDispTotalScoreFlg = true;
			m_PlusScore[i].nAddScore = 0;
			m_PlusScore[i].bEndComboFlg = true;
			m_PlusScore[i].nDispFrame = 0;
		}
		//if (m_PlusScore[i].bEndComboFlg
		//	&&!m_PlusScore[i].bDispTotalScoreFlg)//コンボ終了時
		m_PlusScore[i].nDispFrame++;
		if (!m_PlusScore[i].bEndComboFlg)
		{
			// 暫くコンボ数を表示する
			
			if (m_PlusScore[i].nDispFrame >= 5 * 60)
			{
				m_PlusScore[i].bEndComboFlg = true;
			}
			digitArray = digitsToArray(m_PlusScore[i].fComboMagnification*10);
			nArraySize = digitArray.size();				//何桁か確認
			for (int i = 0; i < nArraySize; i++)
			{
				int width = 30 * i;
				int hight = 40 * lineNum;
				//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//スプライトの設定
				Sprite::SetWorld(time[0]);

				int y = digitArray[i] % 5;	//ここ名前募集します
				int x = digitArray[i] / 5;	//配列に入ってる数字の場所を計算してます
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.5f*x));

				Sprite::Draw();
			}
			lineNum++;

		}
		
		if (m_PlusScore[i].nDispFrame >= 8 * 60)
		{
			m_PlusScore[i].bDispTotalScoreFlg = false;
		}
	}

}
/* ========================================
	プラススコア加算関数
	----------------------------------------
	内容：プラススコアの加算
	----------------------------------------
	引数1：構造体,配列番号
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::AddScore(CCombo::ComboInfo comboInfo,int num)
{

	m_PlusScore[num].nAddScore = comboInfo.dScore;

	//m_PlusScore[num].fComboMagnification= comboInfo.dCnt
	
}
/* ========================================
	倍率確定関数
	----------------------------------------
	内容：コンボ終了時の倍率を確定
	----------------------------------------
	引数1：構造体,配列番号
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::ComboCheck(CCombo::ComboInfo comboInfo, int num)
{
	if (comboInfo.dCnt <= 5) m_PlusScore[num].fComboMagnification = 1.0f;
	else if (comboInfo.dCnt == 6)m_PlusScore[num].fComboMagnification = 1.1f;
	else if (comboInfo.dCnt == 7)m_PlusScore[num].fComboMagnification = 1.2f;
	else if (comboInfo.dCnt == 8)m_PlusScore[num].fComboMagnification = 1.3f;
	else if (comboInfo.dCnt == 9)m_PlusScore[num].fComboMagnification = 1.4f;
	else if (comboInfo.dCnt >= 10) m_PlusScore[num].fComboMagnification = 1.5f;

	m_PlusScore[num].bEndComboFlg = false;
	
}

/* ========================================
	トータルスコア加算関数
	----------------------------------------
	内容：トータルスコアの加算
	----------------------------------------
	引数1：
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::AddTotalScore()
{

	m_nTotalScore += m_PlusScore->nAddScore;
	if (m_nTotalScore > MAX_TOTALSCORE)
	{
		m_nTotalScore = MAX_TOTALSCORE;
	}

	digitArray = digitsToArray(m_nTotalScore);
	nArraySize = digitArray.size();

	TotalScoreArray.clear();					//加算前のトータルスコア削除
	for (int i = 0; i < TOTALSCORE_DIGIT; i++)//トータルスコアの桁を作る
	{
		TotalScoreArray.push_back(0);
	}
	for (int i = 0; i < nArraySize; i++)	//加算後のトータルスコア作成
	{
		TotalScoreArray[i] = digitArray[i];
	}
	digitArray.clear();
}
/* ========================================
	トータルスコア取得関数
	----------------------------------------
	内容：トータルスコアの取得
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：トータルスコアの数値
======================================== */
int CTotalScore::GetTotalScore()
{
	return m_nTotalScore;
}


/* ========================================
	配列収納処理関数
	-------------------------------------
	内容：表示したい数字を一桁ずつ配列に入れる
	-------------------------------------
	引数1：表示したいスコア
	-------------------------------------
	戻値：収納した配列
=========================================== */
std::vector<int> CTotalScore::digitsToArray(int score)
{
	digits.clear();
	while (score > 0) {
		digits.push_back(score % 10);
		score /= 10;
	}
	// １の位から入っているので反転する
	//std::reverse(digits.begin(), digits.end());
	return digits;
}


