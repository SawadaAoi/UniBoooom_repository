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
	・2024/01/26 処理を見やすく修正&&トータルスコア加算アニメ処理追加 sawada
	・2024/02/02 ゲーム終了間際の加算スコアがトータルスコアに反映されるように suzumura
	・2024/02/05 ゲーム終了間際の加算スコアがトータルスコアに反映されるように(改) sawada

========================================== */

// =============== インクルード ===================
#include "TotalScore.h"
#include "Sprite.h"
#include "Pos2d.h"	//二次元座標
#include "UIStageManager.h"

// =============== 定数定義 ===================
const std::string TEXTURE_PATH[CTotalScore::TEXTURE_MAX][2] =
{
	{"トータルスコア数字","Assets/Texture/Score/score_numbers.png"},
	{"加算スコア数字","Assets/Texture/Score/plus_score_numbers.png"},
	{"トータルスコア背景","Assets/Texture/Score/total_score_back_1.png"},
	{"加算スコア背景","Assets/Texture/Score/plus_score_back_1.png"},
};

const int ADD_SCORE_DISP_FRAME = 1.5f * 60;		// 加算スコア表示時間
const int COMBO_MULT_DISP_FRAME = 1.0f * 60;	// コンボ倍率表示時間
const int TOTAL_SCORE_MOVE_FRAME = 0.05f * 60;	// トータルスコア加算アニメ処理切り替え時間
const int TOTAL_SCORE_MOVE_ADD_POINT = 100;		// トータルスコア加算アニメ処理加算値


const int COMBO_MULTI_DISPLAY_NUM	= 6;					// 倍率表示最小コンボ数
const int COMBO_MULTI_MAX_NUM		= 10;					// 倍率変化最大コンボ数

const float COMBO_MULTI_NUM[COMBO_MULTI_MAX_NUM + 1] = {	// コンボ数による加算スコアの倍率
	1.0f,	// 0
	1.0f,	// 1
	1.0f,	// 2
	1.0f,	// 3
	1.0f,	// 4
	1.0f,	// 5
	1.1f,	// 6
	1.2f,	// 7
	1.3f,	// 8
	1.4f,	// 9
	1.5f,	// 10
};


const int TOTAL_SCORE_DIGIT = 5;						//トータルスコアの桁数
const int MAX_TOTALSCORE = 99999;						//↑一緒に変えてください（桁数分9を追加）//最大トータアルスコア

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
const TDiType<float> PLUS_SYMBOL_UVPOS(0.0f, 0.666f);	// +の表示のUV座標
													   
const float CONBO_MULTI_WIDTH = 40.0f;

const TDiType<float> DECIMAL_POINT_POS(CONBO_MULTI_WIDTH / 2, -0.0f);	// 小数点の位置設定
const TDiType<float> DECIMAL_POINT_SIZE(30.0f, -30.0f);	// 小数点の表示の大きさ
const TDiType<float> DECIMAL_POINT_UVPOS(0.4f, 0.666f); // 小数点のUV座標

const TDiType<float> CROSS_SYMBOL_SIZE(40.0f, -65.0f);	// ×の表示の大きさ
const TDiType<float> CROSS_SYMBOL_UVPOS(0.2f, 0.666f);	// ×の表示のUV座標


const TPos2d<float> TOTAL_SCORE_BG_POS(1130.0f, 55.0f);		// トータルスコアの背景位置設定
const DirectX::XMFLOAT2 TOTAL_SCORE_BG_SIZE(320.0f, -110.0f);	// トータルスコアの背景の表示の大きさ

const TPos2d<float> PLUS_SCORE_BG_POS(1175.0f, 60.0f);		// トータルスコアの背景位置設定
const DirectX::XMFLOAT2 PLUS_SCORE_BG_SIZE(200.0f, -50.0f);	// トータルスコアの背景の表示の大きさ


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
	: m_nTotalScoreDisp(0)
	, m_nTotalScore(0)
	, m_nToScoreAddCnt(0)

{
	for (int i = 0; i < TextureType::TEXTURE_MAX; i++)
	{
		m_pTexture[i] = new Texture();
		if (FAILED(m_pTexture[i]->Create(TEXTURE_PATH[i][1].c_str())))
		{
			MessageBox(NULL, TEXTURE_PATH[i][0].c_str(), "Error", MB_OK);
		}
	}

	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		// スコア加算値配列リセット
		m_AddScore[i] = ResetAddScore();

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


/* ========================================
	更新関数
	----------------------------------------
	内容：更新処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
void CTotalScore::Update()
{
	TotalScoreMove();	// トータルスコア

	// 加算スコア
	for (int i = 0, lineNum = 1; i < MAX_COMBO_NUM; i++)
	{
		if (m_AddScore[i].nAddScore == 0)	continue;	// 値のない物はスルー

		if (!m_AddScore[i].bEndComboFlg)	continue;	// コンボ継続中の場合は後続の処理は行わない

		// コンボ終了後------------------------------

		// コンボ倍率表示が終了していない場合
		if (!m_AddScore[i].bDispCombMultEndFlg)
		{
			// コンボ数が1～5の場合
			if (m_AddScore[i].nComboCnt < COMBO_MULTI_DISPLAY_NUM)
			{
				m_AddScore[i].bDispCombMultEndFlg = true; // コンボ倍率は表示しない為、表示終了
			}
			// コンボ倍率が6以上の場合
			else
			{
				m_AddScore[i].nDispCombMultCnt++;	// コンボ倍率表示カウント加算

				// 一定秒数コンボ倍率を表示したか
				if (m_AddScore[i].nDispCombMultCnt >= COMBO_MULT_DISP_FRAME)
				{
					m_AddScore[i].nAddScore = static_cast<int>
						( m_AddScore[i].nAddScore * m_AddScore[i].fCombScoreMult );	// コンボ倍率を加算スコアに掛ける
					m_AddScore[i].bDispCombMultEndFlg = true;						// コンボ倍率表示終了
				}
			}
			
			continue;	// ここで処理は終了
		}
		
		// コンボ倍率表示終了後 ----------------------------------

		// 加算スコア表示中の場合
		if (!m_AddScore[i].bDispAddScoreEndFlg)
		{
			m_AddScore[i].nDispAddScoreCnt++;	// 加算スコア表示カウント加算

			// 一定時間加算スコアを表示したか
			if (ADD_SCORE_DISP_FRAME <= m_AddScore[i].nDispAddScoreCnt)
			{
				AddTotalScore(m_AddScore[i].nAddScore);		// トータルスコアに加算
				m_AddScore[i].bDispAddScoreEndFlg = true;	// 加算スコア描画を辞める
				m_pUIMng->PlaySE(CUIStageManager::SE_ADD_SCORE);
			}
		}
		// 加算スコア表示終了後の場合
		else
		{
			m_AddScore[i] = ResetAddScore();		// 加算スコア配列値リセット

		}

	}
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
	for (int i = 0, lineNum = 1; i < MAX_COMBO_NUM; i++)
	{
		if (m_AddScore[i].nAddScore == 0)continue; // 何もなければスルー

		DrawBGAddScore(lineNum);	// 加算スコアの背景描画
		DrawAddScore(i, lineNum);	// 加算スコア描画
		lineNum++;					// 段落切り替え

		if (!m_AddScore[i].bEndComboFlg) continue;	// コンボ継続中の場合は後続の処理は行わない

		// コンボ倍率表示フラグが有効の場合(コンボ数が6未満の場合は行わない)
		if (!m_AddScore[i].bDispCombMultEndFlg)
		{
			DrawBGAddScore(lineNum);			// 背景描画(加算スコアと同様のもの)
			DrawScoreComboMulti(i, lineNum);	// 倍率描画(例:1.2)
			lineNum++;							// 段落切り替え

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
		m_nTotalScoreDisp, 
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


	//+の表示
	int AdScoDigi = digitsToArray(m_AddScore[nNum].nAddScore, 0).size();

	TDiType<float> fSetPos = { 
		ADD_SCORE_POS.x - (ADD_SCORE_SIZE.x * AdScoDigi), 
		ADD_SCORE_POS.y + (ADD_SCORE_HIGHT * lineNum) 
	};

	DrawTexture(
		PLUS_SYMBOL_SIZE, 
		fSetPos, 
		ADD_SCORE_UVSIZE, 
		PLUS_SYMBOL_UVPOS,
		m_pTexture[TextureType::NUM_ADD_SCORE]);

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
		ADD_SCORE_HIGHT * lineNum,
		m_pTexture[TextureType::NUM_ADD_SCORE],
		0);


	//小数点表示
	int AdScoDigi = digitsToArray(m_AddScore[nNum].nAddScore, 0).size();

	TDiType<float> fSetPos = { 
		ADD_SCORE_POS.x - DECIMAL_POINT_POS.x ,
		ADD_SCORE_POS.y + (ADD_SCORE_HIGHT* lineNum)+ DECIMAL_POINT_POS.y 
	};
	DrawTexture(
		DECIMAL_POINT_SIZE,
		fSetPos,
		ADD_SCORE_UVSIZE,
		DECIMAL_POINT_UVPOS,
		m_pTexture[TextureType::NUM_ADD_SCORE]);

	//×表示
	fSetPos = {
		ADD_SCORE_POS.x - (ADD_SCORE_SIZE.x * 2 + DECIMAL_POINT_SIZE.x),
		ADD_SCORE_POS.y + (ADD_SCORE_HIGHT* lineNum)
	};
	DrawTexture(
		CROSS_SYMBOL_SIZE,
		fSetPos,
		ADD_SCORE_UVSIZE,
		CROSS_SYMBOL_UVPOS,
		m_pTexture[TextureType::NUM_ADD_SCORE]);


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

	Sprite::SetWorld(Mat[0]);
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
	加算スコアリセット関数
	----------------------------------------
	内容：加算スコアをリセットする
	----------------------------------------
	引数1：無し
	----------------------------------------
	戻値：加算スコア構造体
======================================== */
CTotalScore::PlusScore CTotalScore::ResetAddScore()
{
	PlusScore reAddScore;	// 返す値
		
	reAddScore.nAddScore			= 0;
	reAddScore.nComboCnt			= 0;
	reAddScore.fCombScoreMult		= 0.0f;	// コンボスコア倍率
	reAddScore.bEndComboFlg			= false;
	reAddScore.nDispAddScoreCnt		= 0;
	reAddScore.bDispAddScoreEndFlg	= false;
	reAddScore.nDispCombMultCnt		= 0;
	reAddScore.bDispCombMultEndFlg	= false;

	return reAddScore;
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
void CTotalScore::SetAddScore(CCombo::ComboInfo comboInfo, int num)
{
	m_AddScore[num].nAddScore = comboInfo.dScore;	// コンボのスコアを更新する
	m_AddScore[num].nComboCnt = comboInfo.dComboCnt;		// コンボ数更新する
	
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
	SetCombScoreMult(num);						// コンボスコア倍率セット
	m_AddScore[num].bEndComboFlg = true;		// コンボ終了フラグ
	
}

/* ========================================
	トータルスコア加算関数
	----------------------------------------
	内容：トータルスコアの加算
	----------------------------------------
	引数1：加算するスコア値
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::AddTotalScore(int addScore)
{
	m_nTotalScore += addScore;	// トータルスコアに加算スコアを足す

	// 最大値超えしないようにする
	if ( MAX_TOTALSCORE < m_nTotalScore)
	{
		m_nTotalScore = MAX_TOTALSCORE;
	}


}

/* ========================================
	ゲーム終了トータルスコア加算関数
	----------------------------------------
	内容：ゲーム終了時に途中のトータルスコアの加算
	----------------------------------------
	引数1：加算するスコア値
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::GameEndAddTotal()
{
	for (int i = 0; i < MAX_COMBO_NUM; i++)
	{
		if (m_AddScore[i].nAddScore == 0)	continue;		// 値のない物はスルー
		if (m_AddScore[i].bDispAddScoreEndFlg)	continue;	// トータルスコアに加算済みのものはスルー

		if (!m_AddScore[i].bDispCombMultEndFlg						// コンボ倍率描画が未終了
			&& COMBO_MULTI_DISPLAY_NUM <= m_AddScore[i].nComboCnt )	// コンボ数が6以上の場合
		{
			// コンボ倍率を求める
			SetCombScoreMult(i);
			// コンボ倍率を加算スコアに掛ける
			m_AddScore[i].nAddScore = static_cast<int>(m_AddScore[i].nAddScore * m_AddScore[i].fCombScoreMult);	
		}

		AddTotalScore(m_AddScore[i].nAddScore);	// トータルスコアに加算

	}
}

/* ========================================
	UIマネージャーポインタセッター関数
	----------------------------------------
	内容：UIマネージャーポインタをセットする
	----------------------------------------
	引数1：UIマネージャーポインタ
	----------------------------------------
	戻値：なし
======================================== */
void CTotalScore::SetUIStageManagerPtr(CUIStageManager * pUIMng)
{
	m_pUIMng = pUIMng;
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


/* ========================================
	トータルスコア加算動作関数
	-------------------------------------
	内容：トータルスコアに加算スコアを足した値まで数字をアニメーションする
	-------------------------------------
	引数1：無し
	-------------------------------------
	戻値：無し
=========================================== */
void CTotalScore::TotalScoreMove()
{
	// 表示用トータルスコアが加算後トータルスコアが異なる
	if (m_nTotalScoreDisp != m_nTotalScore)
	{
		m_nToScoreAddCnt++;	// 表示用トータルスコアの数字切り替えカウント加算


		// 切り替え時間が過ぎているか
		if (TOTAL_SCORE_MOVE_FRAME <= m_nToScoreAddCnt)
		{
			m_nTotalScoreDisp += TOTAL_SCORE_MOVE_ADD_POINT;	// 表示用スコアを加算する


			// 表示用トータルスコアに値を足しすぎた場合
			if (m_nTotalScore <= m_nTotalScoreDisp)
			{
				m_nTotalScoreDisp = m_nTotalScore;	// 値を合わせる
				m_pUIMng->StopSE(CUIStageManager::SE_ADD_SCORE);
			}
			m_nToScoreAddCnt = 0;
			
		}
	}
}


/* ========================================
	コンボ数倍率セット関数
	-------------------------------------
	内容：コンボ数に応じて倍率をセットする
	-------------------------------------
	引数1：スコア加算配列の添え字
	-------------------------------------
	戻値：無し
=========================================== */
void CTotalScore::SetCombScoreMult(int num)
{
	int comboCnt	= m_AddScore[num].nComboCnt;	// コンボ数をセット(見やすさ重視)
	float fMult		= 1.0f;							// 加算スコア値に掛ける倍率(デフォルトは1.0f)

	// コンボ数が1～9
	if (comboCnt < COMBO_MULTI_MAX_NUM)
	{
		fMult = COMBO_MULTI_NUM[comboCnt];				// 設定したコンボ数による倍率をセットする
	}
	// コンボ数が10以上の場合
	else
	{
		fMult = COMBO_MULTI_NUM[COMBO_MULTI_MAX_NUM];	// 倍率は固定
	}

	m_AddScore[num].fCombScoreMult = fMult;	// コンボ加算スコア倍率セット
}

