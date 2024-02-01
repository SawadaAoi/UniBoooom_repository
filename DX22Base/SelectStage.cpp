/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージセレクト実装
	---------------------------------------
	SelectStage.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 ステージセレクトを追加　yamamoto
	・2024/01/26 拡縮実装 takagi

========================================== */

// =============== インクルード ===================
#include "SelectStage.h"	//自身のヘッダ
#include "Input.h"
#include "GameParameter.h"
#define _USE_MATH_DEFINES	//math.hの定義使用
#include <math.h>			//M_PI使用
#include <algorithm>		//clamp使用
// =============== 定数定義 =======================
const float TEXTURE_SELECT_STAGE_POSX = 900.0f;
const float TEXTURE_SELECT_STAGE_POSY = 300.0f;
const float TEXTURE_SELECT_STAGE_WIDTH = 400.0f;
const float TEXTURE_SELECT_STAGE_HEIGHT =500.0f;

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CSelectStage::CSelectStage()
	: m_pStageSelectBG(nullptr)
	, m_pStageSelectUI(nullptr)
	, m_nSelectNum(0)
	, m_bStickFlg(false)
	, m_pFrameCnt(nullptr)	//フレームカウンタ
	,m_bCntUpDwn(false)	//カウントアップ・ダウン
{
	mStageNum[0].Type = E_TYPE_STAGE1;
	mStageNum[0].m_pTexture= new Texture();
	if (FAILED(mStageNum[0].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo1.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	mStageNum[1].Type = E_TYPE_STAGE2;
	mStageNum[1].m_pTexture = new Texture();
	if (FAILED(mStageNum[1].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo2.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}
	mStageNum[2].Type = E_TYPE_STAGE3;
	mStageNum[2].m_pTexture = new Texture();
	if (FAILED(mStageNum[2].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo3.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	for (int i = 0; i < 5; i++)
	{
		m_2dObj[i] = new C2dPolygon();
		m_2dObj[i]->SetCamera(m_pCamera);					//カメラセッタ
	}
	m_pStageSelectBG= new Texture();
	if (FAILED(m_pStageSelectBG->Create("Assets/Texture/StageSelect/StageSelectBG.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}
	m_pStageSelectUI = new Texture();
	if (FAILED(m_pStageSelectUI->Create("Assets/Texture/StageSelect/stselectUI.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	m_2dObj[0]->SetPos({ 250.0f, 300.0f,1.0f });
	m_2dObj[0]->SetRotate({ 0.0f,0.0f,-0.25f });
	m_2dObj[1]->SetPos({ 600.0f, 300.0f,1.0f });
	m_2dObj[1]->SetRotate({ 0.0f,0.0f,0.05f });
	m_2dObj[2]->SetPos({ 950.0f, 300.0f,1.0f });
	m_2dObj[2]->SetRotate({ 0.0f,0.0f,0.1f });
	m_2dObj[0]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
	m_2dObj[1]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
	m_2dObj[2]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });

	// =============== 動的確保 =====================
	m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//フレーム初期化
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
CSelectStage::~CSelectStage()
{
	// 破棄処理
	for (int i = 0; i >= SUTAGE_NUM; ++i)
	{
		SAFE_DELETE(mStageNum[i].m_pTexture);
	}
	SAFE_DELETE(m_pStageSelectBG);
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
void CSelectStage::Update()
{
	Select();
}

/* ========================================
	描画関数
	----------------------------------------
	内容：描画処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
	//!memo(見たら消してー)：constが邪魔になったら外してね(.hの方も)
void CSelectStage::Draw() //const
{
	//背景
	m_2dObj[3]->SetTexture(m_pStageSelectBG);
	m_2dObj[3]->SetPos({ SCREEN_WIDTH/2, SCREEN_HEIGHT/2 ,1.0f });
	m_2dObj[3]->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT ,1.0f });
	m_2dObj[3]->Draw();
	


	if (!(0 == m_nSelectNum))
	{//ステージ1
		m_2dObj[0]->SetTexture(mStageNum[0].m_pTexture);
		m_2dObj[0]->SetPos({ 250.0f, 300.0f,1.0f });
		m_2dObj[0]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
		m_2dObj[0]->SetRotate({ 0.0f,0.0f,-0.25f });
		m_2dObj[0]->SetColor(0.5f, 1.0f);
		m_2dObj[0]->Draw();
	}
	if (!(1 == m_nSelectNum))
	{
		//ステージ2
		m_2dObj[1]->SetTexture(mStageNum[1].m_pTexture);
		m_2dObj[1]->SetPos({ 600.0f, 300.0f,1.0f });
		m_2dObj[1]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
		m_2dObj[1]->SetRotate({ 0.0f,0.0f,0.05f });
		m_2dObj[1]->SetColor(0.5f, 1.0f);
		m_2dObj[1]->Draw();
	}
	if (!(2 == m_nSelectNum))
	{
		//ステージ3
		m_2dObj[2]->SetTexture(mStageNum[2].m_pTexture);
		m_2dObj[2]->SetPos({ 950.0f, 300.0f,1.0f });
		m_2dObj[2]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
		m_2dObj[2]->SetRotate({ 0.0f,0.0f,0.1f });
		m_2dObj[2]->SetColor(0.5f, 1.0f);
		m_2dObj[2]->Draw();
	}


	// =============== 変数宣言 =====================
	float fSize = MIN_SIZE_ARR_LET;	//大きさ

	if (m_pFrameCnt)	//ヌルチェック
	{
		m_pFrameCnt->Count();	//カウント進行
		fSize = -(cosf(static_cast<float>(M_PI) * m_pFrameCnt->GetRate()) - 1.0f) / 2.0f * (MAX_SIZE_ARR_LET - MIN_SIZE_ARR_LET) + MIN_SIZE_ARR_LET;	//イージングを使った大きさ変更
		if (m_pFrameCnt->IsFin())	//カウント完了
		{
			m_bCntUpDwn ^= 1;													//カウントアップダウン逆転
			SAFE_DELETE(m_pFrameCnt);											//カウンタ削除
			m_pFrameCnt = new CFrameCnt(CHANGE_SCALE_HALF_TIME, m_bCntUpDwn);	//カウントアップ・ダウン
		}
	}

	m_2dObj[m_nSelectNum]->SetTexture(mStageNum[m_nSelectNum].m_pTexture);
	m_2dObj[m_nSelectNum]->SetColor(1.0f, 1.0f);
	m_2dObj[m_nSelectNum]->SetSize({ fSize * TEXTURE_SELECT_STAGE_WIDTH / TEXTURE_SELECT_STAGE_HEIGHT, fSize, 1.0f });	//拡縮
	m_2dObj[m_nSelectNum]->Draw();

	//for (int i = SUTAGE_NUM-1; i > 0-1; i--)
	//{
	//	if (i == m_nSelectNum) continue;
	//	m_2dObj[i]->SetTexture(mStageNum[i].m_pTexture);
	//	m_2dObj[i]->SetPos({ TEXTURE_SELECT_STAGE_POSX + i * 100,TEXTURE_SELECT_STAGE_POSY-i*70,1.0f });
	//	m_2dObj[i]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f});
	//	m_2dObj[i]->SetRotate({ 0.0f,0.0f,-0.3f });
	//	m_2dObj[i]->Draw();
	//}
	//文字
	m_2dObj[4]->SetTexture(m_pStageSelectUI);
	m_2dObj[4]->SetPos({ 640.0f, 660.0f  ,1.0f });
	m_2dObj[4]->SetSize({ SCREEN_WIDTH, 120.0f ,1.0f });
	m_2dObj[4]->Draw();
}
/* ========================================
	ステージを選択する関数
	----------------------------------------
	内容：ステージを選択する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CSelectStage::Select()
{
	// ゲームコントローラー
	if (GetUseVController())
	{
		TPos3d<float> fMoveInput;	// スティックの入力値を入れる変数
		fMoveInput.x = IsStickLeft().x;// コントローラーの左スティックの傾きを取得

		// 左スティックを倒している
		if (!m_bStickFlg)
		{
			// スティック左
			if (fMoveInput.x < 0.0f)
			{
				m_nSelectNum -= 1;
				if (m_nSelectNum < 0) m_nSelectNum = 0;
				m_bStickFlg = true;
			}
			// スティック右
			else if ( 0.0f < fMoveInput.x )
			{
				m_nSelectNum += 1;
				if (m_nSelectNum > 2)m_nSelectNum = 2;
				m_bStickFlg = true;
			}
		}
		// 左スティックがニュートラル
		else
		{
			if (fabs(fMoveInput.x) <= 0.5f )
			{
				m_bStickFlg = false;
			}
		}
	}
	//キーボード入力
	if (IsKeyTrigger('A')) {
		m_nSelectNum -= 1;
		if (m_nSelectNum < 0) m_nSelectNum = 0;
	}
	if (IsKeyTrigger('D')) {
		m_nSelectNum += 1;
		if (m_nSelectNum > 2)m_nSelectNum = 2;
	}

	if (IsKeyTrigger(VK_SPACE) || IsKeyTrigger(VK_RETURN) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// タイトルシーン終了フラグON
	}
}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がステージセレクトであることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetType() const
{
	// =============== 提供 ===================
	return CSelectStage::E_TYPE_SELECT_STAGE;	//自身の種類
}

/* ========================================
	次シーンゲッタ
	----------------------------------------
	内容：遷移したいシーンが何かを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：遷移先シーンの種類
=========================================== */
CSelectStage::E_TYPE CSelectStage::GetNext() const
{
	// =============== 提供 ===================
	//return CSelectStage::E_TYPE_STAGE1;	//遷移先シーンの種類
	return mStageNum[m_nSelectNum].Type;	//遷移先シーンの種類
}