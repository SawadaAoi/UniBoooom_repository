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
========================================== */

// =============== インクルード ===================
#include "SelectStage.h"	//自身のヘッダ
#include "Input.h"
#include "GameParameter.h"
// =============== 定数定義 =======================
const float TEXTURE_SELECT_STAGE_POSX = 900.0f;
const float TEXTURE_SELECT_STAGE_POSY = 300.0f;
const float TEXTURE_SELECT_STAGE_WIDTH = 400.0f;
const float TEXTURE_SELECT_STAGE_HEIGHT =500.0f;
const float SELECT_CONTOROLLER_INTERVAL =60.0f;	//スティック入力の間隔

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
	, Num(0)
	, m_bSelect(false)
	, m_nCount(0)
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
	


	if (!(0 == Num))
	{//ステージ1
		m_2dObj[0]->SetTexture(mStageNum[0].m_pTexture);
		m_2dObj[0]->SetPos({ 250.0f, 300.0f,1.0f });
		m_2dObj[0]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
		m_2dObj[0]->SetRotate({ 0.0f,0.0f,-0.25f });
		m_2dObj[0]->SetColor(0.5f, 1.0f);
		m_2dObj[0]->Draw();
	}
	if (!(1 == Num))
	{
		//ステージ2
		m_2dObj[1]->SetTexture(mStageNum[1].m_pTexture);
		m_2dObj[1]->SetPos({ 600.0f, 300.0f,1.0f });
		m_2dObj[1]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
		m_2dObj[1]->SetRotate({ 0.0f,0.0f,0.05f });
		m_2dObj[1]->SetColor(0.5f, 1.0f);
		m_2dObj[1]->Draw();
	}
	if (!(2 == Num))
	{
		//ステージ3
		m_2dObj[2]->SetTexture(mStageNum[2].m_pTexture);
		m_2dObj[2]->SetPos({ 950.0f, 300.0f,1.0f });
		m_2dObj[2]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
		m_2dObj[2]->SetRotate({ 0.0f,0.0f,0.1f });
		m_2dObj[2]->SetColor(0.5f, 1.0f);
		m_2dObj[2]->Draw();
	}

	m_2dObj[Num]->SetTexture(mStageNum[Num].m_pTexture);
	m_2dObj[Num]->SetColor(1.0f, 1.0f);
	m_2dObj[Num]->Draw();

	//for (int i = SUTAGE_NUM-1; i > 0-1; i--)
	//{
	//	if (i == Num) continue;
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
	//キーボード入力
	if (IsKeyTrigger('A')){
		Num -= 1;
		if (Num < 0) Num = 0;
	}
	if (IsKeyTrigger('D')){
		Num += 1;
		if (Num > 2)Num = 2;
	}

	

	if (!m_bSelect)
	{
		TPos3d<float> fMoveInput;	// スティックの入力値を入れる変数
		if (GetUseVController())
		{// コントローラーの左スティックの傾きを取得
			fMoveInput.x = IsStickLeft().x;
			if (fMoveInput.x < 0.0f)
			{
				EscapeStageNum = mStageNum[2];
				mStageNum[2] = mStageNum[1];
				mStageNum[1] = mStageNum[0];
				mStageNum[0] = EscapeStageNum;
			}
			if (fMoveInput.x > 0.0f)
			{
				EscapeStageNum = mStageNum[0];
				mStageNum[0] = mStageNum[1];
				mStageNum[1] = mStageNum[2];
				mStageNum[2] = EscapeStageNum;
			}
			
			m_bSelect = true;	
		}
	}
	else
	{
		m_nCount += 1;
		if (m_nCount >= SELECT_CONTOROLLER_INTERVAL)
		{
			m_bSelect = false;
			m_nCount = 0;
		}
	}

	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
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
	return mStageNum[Num].Type;	//遷移先シーンの種類
}