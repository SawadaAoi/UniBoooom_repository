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
const std::string TEXTURE_PATH[CTotalScore::TEXTURE_MAX][2] =
{
	{"トータルスコア数字","Assets/Texture/numbers_v1/combo_numbers.png"},
	{"加算スコア数字","Assets/Texture/numbers_v1/plus_score_numbers.png"},
	{"トータルスコア背景","Assets/Texture/total_score_back_1.png"},
	{"加算スコア背景","Assets/Texture/plus_score_back_1.png"},
};


const int TOTAL_SCORE_DIGIT = 5;								//トータルスコアの桁数
const int MAX_TOTALSCORE = 99999;							//↑一緒に変えてください（桁数分9を追加）//最大トータアルスコア

const TDiType<float> TOTAL_SCORE_POS(1230.0f, 50.0f);	// トータルスコアの位置設定
const TDiType<float> TOTAL_SCORE_SIZE(50.0f, -75.0f);	// トータルスコアの表示の大きさ
const TDiType<float> TOTAL_SCORE_UVSIZE(0.2f, 0.5f);	// トータルスコアのUVの大きさ
const float TOTAL_SCORE_WIDTH = 50.0f;					   
														   
const TDiType<float> ADD_SCORE_POS(1230.0f, 50.0f);		// 加算スコアの位置設定
const TDiType<float> ADD_SCORE_SIZE(30.0f, -40.0f);		// 加算スコアの表示の大きさ
const TDiType<float> ADD_SCORE_UVSIZE(0.2f, 0.333f);	// 加算スコアのUVの大きさ
const float ADD_SCORE_WIDTH = 30.0f;					   
const float ADD_SCORE_HIGHT = 60.0f;		


const TDiType<float> PLUS_SYMBOL_SIZE(30.0f, -40.0f);	// +の表示の大きさ
const TDiType<float> PLUS_SYMBOL_UVPOS(0.2f, 0.666f);	// +の表示のUV座標
													   
const float CONBO_MULTI_WIDTH = 40.0f;
const float CONBO_MULTI_HIGHT = 60.0f;


const TDiType<float> DECIMAL_POINT_POS(2.0f, -3.0f);	// 小数点の位置設定
const TDiType<float> DECIMAL_POINT_SIZE(15.0f, -15.0f);	// 小数点の表示の大きさ
const TDiType<float> DECIMAL_POINT_UVPOS(0.4f, 0.666f); // 小数点のUV座標

const TDiType<float> CROSS_SYMBOL_SIZE(30.0f, -40.0f);	// ×の表示の大きさ
const TDiType<float> CROSS_SYMBOL_UVPOS(0.2f, 0.666f);	// ×の表示のUV座標


const TPos2d<float> TOTAL_SCORE_BG_POS(1130.0f, 55.0f);		// トータルスコアの背景位置設定
const DirectX::XMFLOAT2 TOTAL_SCORE_BG_SIZE(320.0f, -110.0f);	// トータルスコアの背景の表示の大きさ

const TPos2d<float> PLUS_SCORE_BG_POS(1175.0f, 60.0f);		// トータルスコアの背景位置設定
const DirectX::XMFLOAT2 PLUS_SCORE_BG_SIZE(200.0f, -50.0f);	// トータルスコアの背景の表示の大きさ


const CTotalScore::NumbersParam SCORE_MULTI_PARAM	 = { {50.0f, -75.0f},{1230.0f, 50.0f},{0.2f, 0.5f}, 50.0f };

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

{
	for (int i = 0; i < TextureType::TEXTURE_MAX; i++)
	{
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(TEXTURE_PATH[i][1].c_str())))
		{
			MessageBox(NULL, TEXTURE_PATH[i][0].c_str(), "Error", MB_OK);
		}
	}

	// スコア加算値配列リセット
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		m_AddScore[i].nAddScore = 0;
		m_AddScore[i].fCombScoreMult = 0;
		m_AddScore[i].bEndComboFlg = false;
		m_AddScore[i].nDispFrame = 0;
		m_AddScore[i].bDispFlg = false;
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
	for (int i = 0; i < TextureType::TEXTURE_MAX; i++)
	{
		SAFE_DELETE(m_pTexture[i]);
	}
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

	DrawBGTotalScore();		// トータルスコア背景描画
	DrawTotalScore();		// トータルスコア描画
	

	// 加算スコア表示	-----------
	// 同時コンボ数分複数行で表示する
	for (int i = 0, lineNum=1; i < MAX_COMBO_NUM; i++)
	{
		if (m_AddScore[i].nAddScore == 0)continue;//何もなければスルー
		
		// コンボ継続中かどうか

		DrawBGAddScore(lineNum);	// 加算スコアの背景描画

		DrawAddScore(i, lineNum);	// 加算スコア描画
		lineNum++;


		m_AddScore[i].nDispFrame++;

		// コンボが終了した場合
		if (m_AddScore[i].bEndComboFlg)
		{
			// 一定時間コンボ倍率を表示したか
			if (m_AddScore[i].nDispFrame >= 1 * 60)
			{
				m_AddScore[i].bEndComboFlg = false;
				m_AddScore[i].bDispFlg = true;
				m_AddScore[i].nAddScore = static_cast<int>(m_AddScore[i].nAddScore * m_AddScore[i].fCombScoreMult);
				m_AddScore[i].nDispFrame = 0;
			}

			// 倍率を表示する場合
			if (m_AddScore[i].fCombScoreMult != 1.0f)
			{
				DrawScoreComboMulti(i, lineNum);
				lineNum++;

			}
			
		}
		// 一定秒数表示したら描画を辞める&&表示フラグがオフになっているか
		if (m_AddScore[i].nDispFrame >= 2 * 60&& m_AddScore[i].bDispFlg==true)
		{
			
			AddTotalScore();	// トータルスコアに加算
			// 以下加算スコア配列値リセット
			m_AddScore[i].nAddScore = 0;
			m_AddScore[i].bEndComboFlg = false;
			m_AddScore[i].nDispFrame = 0;
			m_AddScore[i].bDispFlg = false;
		}
	
	}
}

/* ========================================
	トータルスコア描画関数
	----------------------------------------
	内容：トータルスコア描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::DrawTotalScore()
{
	DrawNumber(
		m_nTotalScore, 
		TOTAL_SCORE_SIZE, 
		TOTAL_SCORE_POS, 
		TOTAL_SCORE_UVSIZE, 
		TOTAL_SCORE_WIDTH, 
		0.0f, 
		m_pTexture[TextureType::NUM_TOTAL_SCORE],
		TOTAL_SCORE_DIGIT);
}

/* ========================================
	加算スコア描画関数
	----------------------------------------
	内容：加算スコア描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::DrawAddScore(int nNum, int lineNum)
{
	DrawNumber(
		m_AddScore[nNum].nAddScore,
		ADD_SCORE_SIZE,
		ADD_SCORE_POS,
		ADD_SCORE_UVSIZE,
		ADD_SCORE_WIDTH,
		ADD_SCORE_HIGHT * lineNum,
		m_pTexture[TextureType::NUM_ADD_SCORE],
		0);

	return;

	//TDiType<float> fSetPos = { (ADD_SCORE_SIZE.x * nArraySize), (ADD_SCORE_HIGHT * lineNum) };
	//DrawTexture(ADD_SCORE_SIZE, fSetPos,);

	//+の表示
	DirectX::XMFLOAT4X4 PlusMat[3];

	int width = int(ADD_SCORE_SIZE.x * nArraySize);
	int hight = int(ADD_SCORE_HIGHT * lineNum);
	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(ADD_SCORE_POS.x - width, ADD_SCORE_POS.y + hight, 0.0f);
	DirectX::XMStoreFloat4x4(&PlusMat[0], DirectX::XMMatrixTranspose(world));

	//スプライトの設定
	Sprite::SetWorld(PlusMat[0]);
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.666f));

	Sprite::Draw();
}

/* ========================================
	トータルスコア背景描画関数
	-------------------------------------
	内容：トータルスコアの背景を描画する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CTotalScore::DrawBGTotalScore()
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
	Sprite::SetTexture(m_pTexture[TextureType::BG_TOTAL_SCORE] );
	Sprite::Draw();
}

/* ========================================
	加算スコア背景描画関数
	-------------------------------------
	内容：加算スコアの背景を描画する
	-------------------------------------
	引数1：なし
	-------------------------------------
	戻値：なし
=========================================== */
void CTotalScore::DrawBGAddScore(int lineNum)
{
	//ボスゲージテクスチャ（空）
	DirectX::XMFLOAT4X4 PScoreBG[3];
	int hight = int(ADD_SCORE_HIGHT * lineNum);
	//ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX worldPscorebg = DirectX::XMMatrixTranslation(PLUS_SCORE_BG_POS.x, PLUS_SCORE_BG_POS.y + hight, 0.0f);
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
	Sprite::SetTexture(m_pTexture[TextureType::BG_ADD_SCORE]);
	Sprite::Draw();
}


/* ========================================
	スコアコンボ倍率描画関数
	----------------------------------------
	内容：スコアコンボ倍率描画処理
	----------------------------------------
	引数：なし
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::DrawScoreComboMulti(int nNum, int lineNum)
{
	DrawNumber(
		m_AddScore[nNum].fCombScoreMult * 10,
		ADD_SCORE_SIZE,
		ADD_SCORE_POS,
		ADD_SCORE_UVSIZE,
		CONBO_MULTI_WIDTH,
		CONBO_MULTI_HIGHT * lineNum,
		m_pTexture[TextureType::NUM_ADD_SCORE],
		0);


	//小数点表示
	Sprite::SetSize(DirectX::XMFLOAT2(DECIMAL_POINT_SIZE.x, DECIMAL_POINT_SIZE.y));

	DirectX::XMFLOAT4X4 DecimalMat[3];
	int width1 = int(ADD_SCORE_SIZE.x - DECIMAL_POINT_POS.x);
	int hight1 = int(DECIMAL_POINT_POS.y);
	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX world1 = DirectX::XMMatrixTranslation(TOTAL_SCORE_POS.x - width1, TOTAL_SCORE_POS.y + hight1, 0.0f);
	DirectX::XMStoreFloat4x4(&DecimalMat[0], DirectX::XMMatrixTranspose(world1));

	//スプライトの設定
	Sprite::SetWorld(DecimalMat[0]);
	Sprite::SetUVPos(DirectX::XMFLOAT2(DECIMAL_POINT_UVPOS.x, DECIMAL_POINT_UVPOS.y));

	Sprite::Draw();


	//×表示
	DirectX::XMFLOAT4X4 MultiMat[3];

	int width = int(CROSS_SYMBOL_SIZE.x * 2 + DECIMAL_POINT_SIZE.x);
	int hight = int(CONBO_MULTI_HIGHT * lineNum);
	//ワールド行列はXとYのみを考慮して作成(Zは10ぐらいに配置
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(ADD_SCORE_POS.x - width, ADD_SCORE_POS.y + hight, 0.0f);
	DirectX::XMStoreFloat4x4(&MultiMat[0], DirectX::XMMatrixTranspose(world));
	//スプライトの設定
	Sprite::SetWorld(MultiMat[0]);
	Sprite::SetUVPos(DirectX::XMFLOAT2(CROSS_SYMBOL_UVPOS.x, CROSS_SYMBOL_UVPOS.y));
	Sprite::Draw();
}


/* ========================================
	画像描画関数
	----------------------------------------
	内容：画像を表示する
	----------------------------------------
	引数1：大きさ
	引数2：表示位置
	引数3：UVサイズ
	引数4：UV座標
	引数5：画像ポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::DrawTexture(TDiType<float> fSize, TDiType<float> fPos, TDiType<float> fUVSize, TDiType<float> fUVPos, Texture * pTexture)
{
	// 行列のセット
	DirectX::XMFLOAT4X4 Mat[3];
	DirectX::XMStoreFloat4x4(&Mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&Mat[2], DirectX::XMMatrixTranspose(proj));

	// 行列
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(fPos.x, fPos.y, 0.0f);	// 座標移動
	DirectX::XMStoreFloat4x4(&Mat[0], DirectX::XMMatrixTranspose(world));
	Sprite::SetView(Mat[1]);		// ビュー行列
	Sprite::SetProjection(Mat[2]);	// プロジェクション行列

	Sprite::SetSize(DirectX::XMFLOAT2(fSize.x, fSize.y));			// 画像サイズ
	Sprite::SetUVScale(DirectX::XMFLOAT2(fUVSize.x, fUVSize.y));	// UVサイズ
	Sprite::SetUVPos(DirectX::XMFLOAT2(fUVPos.x, fUVPos.y));		// UV座標

	Sprite::SetTexture(pTexture);									// 画像ポインタ

	Sprite::Draw();
}

/* ========================================
	数字描画関数
	----------------------------------------
	内容：数字の並びを表示する
	----------------------------------------
	引数1：描画数字
	引数2：大きさ
	引数3：表示位置
	引数4：UVサイズ
	引数5：数字間の空白大きさ
	引数6：数字を縦にずらす位置
	引数7：画像ポインタ
	引数8：桁数
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::DrawNumber(int dispNum, TDiType<float> fSize, TDiType<float> fPos, 
	TDiType<float> fUVSize, float spaceW, float spaceH, Texture* pTexture, int digits)
{
	std::vector<int> digitArray = digitsToArray(dispNum, digits);

	// 行列のセット
	DirectX::XMFLOAT4X4 Mat[3];
	DirectX::XMStoreFloat4x4(&Mat[1], DirectX::XMMatrixIdentity());
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&Mat[2], DirectX::XMMatrixTranspose(proj));

	//トータルスコア（一番右上）の描画設定
	//スプライトの設定
	Sprite::SetView(Mat[1]);		// ビュー行列
	Sprite::SetProjection(Mat[2]);	// プロジェクション行列

	Sprite::SetSize(DirectX::XMFLOAT2(fSize.x, fSize.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(fUVSize.x, fUVSize.y));
	Sprite::SetTexture(pTexture);

	// 桁数分描画
	for (int i = 0; i < digitArray.size(); i++)
	{
		float width = spaceW * i;

		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(fPos.x - width, fPos.y + spaceH, 0.0f);
		DirectX::XMStoreFloat4x4(&Mat[0], DirectX::XMMatrixTranspose(world));

		//スプライトの設定
		Sprite::SetWorld(Mat[0]);

		int nUv_x = digitArray[i] % 5;	
		int nUv_y = digitArray[i] / 5;

		Sprite::SetUVPos(DirectX::XMFLOAT2(fUVSize.x * nUv_x, fUVSize.y * nUv_y));
		Sprite::Draw();
	}
}

/* ========================================
	加算スコアセット関数
	----------------------------------------
	内容：加算スコアをセットする
	----------------------------------------
	引数1：コンボ情報構造体
	引数2：配列番号
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::SetAddScore(CCombo::ComboInfo comboInfo,int num)
{

	m_AddScore[num].nAddScore = comboInfo.dScore;	// コンボのスコアを更新する

	//m_AddScore[num].fCombScoreMult= comboInfo.dCnt
	
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
	float fMult = 1.0f;	// 加算スコア値に掛ける倍率(デフォルトは1.0f)

	// コンボ数が6以上の場合
	if (6 <= comboInfo.dCnt)
	{
		switch (comboInfo.dCnt)	// コンボ数によって倍率が変わる
		{
		case 6: fMult = 1.1f; break;
		case 7: fMult = 1.2f; break;
		case 8: fMult = 1.3f; break;
		case 9: fMult = 1.4f; break;
		default:fMult = 1.5f; break;	// 10以上の場合は固定
		}
	}

	m_AddScore[num].fCombScoreMult = fMult;	// コンボ加算スコア倍率セット

	m_AddScore[num].bEndComboFlg = true;		// コンボ終了フラグ
	m_AddScore[num].nDispFrame = 0;
	
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
	std::vector<int> digitArray;
	
	m_nTotalScore += m_AddScore->nAddScore;	// トータルスコアに加算スコアを足す

	// 最大値超えしないようにする
	if (m_nTotalScore > MAX_TOTALSCORE)
	{
		m_nTotalScore = MAX_TOTALSCORE;
	}

	//digitArray = digitsToArray(m_nTotalScore,);
	//nArraySize = int(digitArray.size());

	//TotalScoreArray.clear();					//加算前のトータルスコア削除
	//for (int i = 0; i < TOTAL_SCORE_DIGIT; i++)//トータルスコアの桁を作る
	//{
	//	TotalScoreArray.push_back(0);
	//}
	//for (int i = 0; i < nArraySize; i++)	//加算後のトータルスコア作成
	//{
	//	TotalScoreArray[i] = digitArray[i];
	//}
	//digitArray.clear();
	

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
	引数2：表示する桁数(0埋めする)
	-------------------------------------
	戻値：収納した配列
=========================================== */
std::vector<int> CTotalScore::digitsToArray(int score, int digits)
{
	std::vector<int> digitsArray;
	digitsArray.clear();

	// 指定数字を配列に格納する
	while (score > 0) {
		digitsArray.push_back(score % 10);
		score /= 10;
	}


	// 指定桁数まで0埋めする
	while (digitsArray.size() < digits)
	{
		digitsArray.push_back(0);
	}

	return digitsArray;
}

