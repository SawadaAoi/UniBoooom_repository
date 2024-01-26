/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	スコア管理用cpp
	---------------------------------------
	TotalScore.cpp

	作成者	山本凱翔

	変更履歴
	・2023/11/22　作成 yamamoto
	・2023/11/23　描画処理追加 yamamoto
	・2023/11/24　テクスチャの張替,コメント訂正 yamamoto
	・2023/11/26　コンボ倍率の表示の変更 yamamoto
	・2023/12/07 ゲームパラメータから一部定数移動・インクルード追加 takagi

========================================== */

// =============== インクルード ===================
#include "TotalScore.h"
#include "Sprite.h"
#include "Pos2d.h"	//二次元座標

// =============== 定数定義 ===================
const int TOTALSCORE_DIGIT = 5;				//トータルスコアの桁数
const int MAX_TOTALSCORE = 99999;			//↑一緒に変えてください（桁数分9を追加）//最大トータアルスコア
const TPos2d<float> TOTALSCORE_POS(1230.0f, 50.0f);			//トータルスコアの位置設定
const DirectX::XMFLOAT2 TOTALSCORE_SIZE(50.0f, -75.0f);		//トータルスコアの表示の大きさ
const DirectX::XMFLOAT2 PLUSSCORE_SIZE(30.0f, -40.0f);		//プラススコアの表示の大きさ
const int ROW_HIGHT = 60;			//スコアを複数個表示時一番上からどのくらい下げるか（PLUSSCORE_SIZE.yの絶対値より大きい数字で）
const DirectX::XMFLOAT2 SMALLDECIMAL_SIZE(15.0f, -15.0f);	//小数点の大きさ
const int MAGNIFICATION = 40;		//倍率表示時の間隔。一番右の数字からどれだけ左にずらすか（小数点を入れるのでそこもケアする）
const TPos2d<float> SMALLDECIMAL_POS(2.0f, -3.0f);//この値で小数点の位置の微調節
const TPos2d<float> TOTAL_SCORE_BG_POS(1130.0f, 55.0f);			// トータルスコアの背景位置設定
const DirectX::XMFLOAT2 TOTAL_SCORE_BG_SIZE(320.0f, -110.0f);	// トータルスコアの背景の表示の大きさ
const TPos2d<float> PLUS_SCORE_BG_POS(1175.0f, 60.0f);			// トータルスコアの背景位置設定
const DirectX::XMFLOAT2 PLUS_SCORE_BG_SIZE(200.0f, -50.0f);		// トータルスコアの背景の表示の大きさ

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
	, m_pPlusScoreTexture(nullptr)
	, m_pTScoreBGTex(nullptr)
	, m_pPScoreBGTex(nullptr)
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
	m_pPlusScoreTexture = new Texture();
	if (FAILED(m_pPlusScoreTexture->Create("Assets/Texture/numbers_v1/plus_score_numbers.png")))
	{
		MessageBox(NULL, "PlusScore数字読み込み", "Error", MB_OK);
	}
	m_pTScoreBGTex = new Texture();
	if (FAILED(m_pTScoreBGTex->Create("Assets/Texture/total_score_back_1.png")))
	{
		MessageBox(NULL, "TScoreBack読み込み", "Error", MB_OK);
	}
	m_pPScoreBGTex = new Texture();
	if (FAILED(m_pPScoreBGTex->Create("Assets/Texture/plus_score_back_1.png")))
	{
		MessageBox(NULL, "TScoreBack読み込み", "Error", MB_OK);
	}
	for (int i = 0; i < TOTALSCORE_DIGIT; i++)//トータルスコアの桁を作る
	{
		TotalScoreArray.push_back(0);
	}
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_PlusScore[i].nAddScore = 0;
		m_PlusScore[i].fComboMagnification = 0;
		m_PlusScore[i].bEndComboFlg = true;
		m_PlusScore[i].bDispTotalScoreFlg = true;
		m_PlusScore[i].nDispFrame = 0;
		m_PlusScore[i].bDispFlg = false;
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
	SAFE_DELETE(m_pPlusScoreTexture);
	TotalScoreArray.clear();
}
void CTotalScore::Update()
{
	
}
/* ========================================
	関数：描画関数
	----------------------------------------
	内容：スコアの描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();	//デフォルトで使用しているRenderTargetViewの取得
	DepthStencil* pDSV = GetDefaultDSV();	//デフォルトで使用しているDepthStencilViewの取得
	SetRenderTargets(1, &pRTV, nullptr);		//DSVがnullだと2D表示になる
	DrawTotalScoreBG();		// トータルスコアの背景の描画


	DirectX::XMFLOAT4X4 time[3];
	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&time[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&time[2], DirectX::XMMatrixTranspose(proj));
	
	//トータルスコア（一番右上）の描画設定
	//スプライトの設定
	Sprite::SetView(time[1]);
	Sprite::SetProjection(time[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(TOTALSCORE_SIZE.x, TOTALSCORE_SIZE.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.5f));
	Sprite::SetTexture(m_pToScoreTexture);

	for (int i = 0; i < TOTALSCORE_DIGIT; i++)
	{
		int width = int(TOTALSCORE_SIZE.x * i);
		//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y, 0.0f);
		DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

		//スプライトの設定
		Sprite::SetWorld(time[0]);
		
		int x = TotalScoreArray[i] % 5;
		int y = TotalScoreArray[i] / 5;	//配列に入ってる数字の場所を計算してます
		
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*x, 0.5f*y));
		Sprite::Draw();
	}
	
	
		
	for (int i = 0, lineNum=1; i < MAX_COMBO_NUM; i++)
	{
		
		if (m_PlusScore[i].nAddScore == 0)continue;//何もなければスルー
		
		if (m_PlusScore[i].bDispTotalScoreFlg == true) 
		{
			DrawPlusScoreBG(lineNum);
 			digitArray = digitsToArray(m_PlusScore[i].nAddScore);	
			nArraySize = int(digitArray.size());				//何桁か確認
			//加算予定のスコア（トータルの下）の描画設定サイズ以外は同じなので省略
			Sprite::SetSize(DirectX::XMFLOAT2(PLUSSCORE_SIZE.x, PLUSSCORE_SIZE.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(0.2f, 0.333f));
			Sprite::SetTexture(m_pPlusScoreTexture);
			for (int i = 0; i < nArraySize; i++)
			{
				
				int width = int(PLUSSCORE_SIZE.x * i);
				int hight = int(ROW_HIGHT * lineNum);
				//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//スプライトの設定
				Sprite::SetWorld(time[0]);

				int y = digitArray[i] % 5;	//ここ名前募集します
				int x = digitArray[i] / 5;	//配列に入ってる数字の場所を計算してます
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.333f*x));
				

				Sprite::Draw();
			}
			
			//+の表示
			int width = int(PLUSSCORE_SIZE.x * nArraySize);
			int hight = int(ROW_HIGHT * lineNum);
			//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
			DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
			DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

			//スプライトの設定
			Sprite::SetWorld(time[0]);
			Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.666f));

			Sprite::Draw();
			lineNum++;
		}
		else
		{
			AddTotalScore();
			m_PlusScore[i].bDispTotalScoreFlg = true;
			m_PlusScore[i].nAddScore = 0;
			m_PlusScore[i].bEndComboFlg = true;
			m_PlusScore[i].nDispFrame = 0;
			m_PlusScore[i].bDispFlg = false;
		}

		m_PlusScore[i].nDispFrame++;
		if (!m_PlusScore[i].bEndComboFlg)
		{
			// 暫くコンボ倍率を表示する
			
			if (m_PlusScore[i].nDispFrame >= 1 * 60)
			{
				m_PlusScore[i].bEndComboFlg = true;
				m_PlusScore[i].bDispFlg = true;
				m_PlusScore[i].nAddScore = static_cast<int>(m_PlusScore[i].nAddScore * m_PlusScore[i].fComboMagnification);
				m_PlusScore[i].nDispFrame = 0;
			}
			if (m_PlusScore[i].fComboMagnification != 1.0f)
			{
				digitArray = digitsToArray(int(m_PlusScore[i].fComboMagnification * 10));
				nArraySize = int(digitArray.size());				//何桁か確認
				for (int i = 0; i < nArraySize; i++)
				{
					
					int width = MAGNIFICATION * i;
					int hight = ROW_HIGHT * lineNum;
					//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
					DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
					DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

					//スプライトの設定
					Sprite::SetWorld(time[0]);

					int y = digitArray[i] % 5;	//ここ名前募集します
					int x = digitArray[i] / 5;	//配列に入ってる数字の場所を計算してます
					Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f*y, 0.333f*x));

					Sprite::Draw();
				}

				//×表示
				int width = int(PLUSSCORE_SIZE.x * 2 + SMALLDECIMAL_SIZE.x);
				int hight = int(ROW_HIGHT * lineNum);
				//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
				DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//スプライトの設定
				Sprite::SetWorld(time[0]);
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.2f, 0.666f));

				Sprite::Draw();

				Sprite::SetSize(DirectX::XMFLOAT2(SMALLDECIMAL_SIZE.x, SMALLDECIMAL_SIZE.y));
				//小数点表示
				width = int(PLUSSCORE_SIZE.x - SMALLDECIMAL_POS.x);
				hight -= int(SMALLDECIMAL_POS.y);
				//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
				world = DirectX::XMMatrixTranslation(TOTALSCORE_POS.x - width, TOTALSCORE_POS.y + hight, 0.0f);
				DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));

				//スプライトの設定
				Sprite::SetWorld(time[0]);
				Sprite::SetUVPos(DirectX::XMFLOAT2(0.4f, 0.666f));

				Sprite::Draw();
				lineNum++;
			}
			
		}
		if (m_PlusScore[i].nDispFrame >= 2 * 60&& m_PlusScore[i].bDispFlg)
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
	m_PlusScore[num].nDispFrame = 0;
	
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
	nArraySize = int(digitArray.size());

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

/* ========================================
	トタルスコア背景描画関数
	-------------------------------------
	内容：トタルスコアの背景を描画する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */

void CTotalScore::DrawTotalScoreBG()
{
	//ボスゲージテクスチャ（空）
	DirectX::XMFLOAT4X4 TScoreBG[3];

	//ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX worldTscorebg = DirectX::XMMatrixTranslation(TOTAL_SCORE_BG_POS.x, TOTAL_SCORE_BG_POS.y, 0.0f);
	
	DirectX::XMStoreFloat4x4(&TScoreBG[0], DirectX::XMMatrixTranspose(worldTscorebg));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&TScoreBG[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projTscorebg = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&TScoreBG[2], DirectX::XMMatrixTranspose(projTscorebg));

	//スプライトの設定
	Sprite::SetWorld(TScoreBG[0]);
	Sprite::SetView(TScoreBG[1]);
	Sprite::SetProjection(TScoreBG[2]);
	Sprite::SetSize(TOTAL_SCORE_BG_SIZE);
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTScoreBGTex);
	Sprite::Draw();
}

/* ========================================
	プラススコア背景描画関数
	-------------------------------------
	内容：プラススコアの背景を描画する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */

void CTotalScore::DrawPlusScoreBG(int lineNum)
{
	//ボスゲージテクスチャ（空）
	DirectX::XMFLOAT4X4 PScoreBG[3];
	int hight = int(ROW_HIGHT * lineNum);
	//ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX worldPscorebg = DirectX::XMMatrixTranslation(PLUS_SCORE_BG_POS.x, PLUS_SCORE_BG_POS.y+ hight, 0.0f);
	DirectX::XMStoreFloat4x4(&PScoreBG[0], DirectX::XMMatrixTranspose(worldPscorebg));

	//ビュー行列は2Dだとカメラの位置があまり関係ないので、単位行列を設定する（単位行列は後日
	DirectX::XMStoreFloat4x4(&PScoreBG[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列には2Dとして表示するための行列を設定する
	//この行列で2Dのスクリーンの多いさが決まる
	DirectX::XMMATRIX projPscorebg = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&PScoreBG[2], DirectX::XMMatrixTranspose(projPscorebg));

	//スプライトの設定
	Sprite::SetWorld(PScoreBG[0]);
	Sprite::SetView(PScoreBG[1]);
	Sprite::SetProjection(PScoreBG[2]);
	Sprite::SetSize(PLUS_SCORE_BG_SIZE);
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pPScoreBGTex);
	Sprite::Draw();
}