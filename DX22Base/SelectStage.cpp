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
const float TEXTURE_SELECT_STAGE_POSY = 400.0f;
const float TEXTURE_SELECT_STAGE_WIDTH = 900.0f;
const float TEXTURE_SELECT_STAGE_HEIGHT = 700.0f;

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
{
	mStageNum[0].Type = E_TYPE_STAGE1;
	mStageNum[0].m_pTexture= new Texture();
	if (FAILED(mStageNum[0].m_pTexture->Create("Assets/Texture/tehaisyo1.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}

	mStageNum[1].Type = E_TYPE_STAGE2;
	mStageNum[1].m_pTexture = new Texture();
	if (FAILED(mStageNum[1].m_pTexture->Create("Assets/Texture/tehaisyo2.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
	}
	mStageNum[2].Type = E_TYPE_STAGE3;
	mStageNum[2].m_pTexture = new Texture();
	if (FAILED(mStageNum[2].m_pTexture->Create("Assets/Texture/tehaisyo3.png")))
	{
		MessageBox(NULL, "Title gamstart.png", "Error", MB_OK);
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
CSelectStage::~CSelectStage()
{
	// 破棄処理
	for (int i = 0; i >= SUTAGE_NUM; ++i)
	{
		SAFE_DELETE(mStageNum[i].m_pTexture);
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
	for (int i = SUTAGE_NUM-1; i > 0-1; i--)
	{
		Draw2d(TEXTURE_SELECT_STAGE_POSX+i*100
			, TEXTURE_SELECT_STAGE_POSY + i * 70
			, TEXTURE_SELECT_STAGE_WIDTH
			, TEXTURE_SELECT_STAGE_HEIGHT
			, mStageNum[i].m_pTexture);
	}
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
	if (IsKeyTrigger('A'))
	{
		EscapeStageNum = mStageNum[2];
		mStageNum[2] = mStageNum[1];
		mStageNum[1] = mStageNum[0];
		mStageNum[0] = EscapeStageNum;
	}
	if (IsKeyTrigger('D'))
	{
		EscapeStageNum = mStageNum[0];
		mStageNum[0] = mStageNum[1];
		mStageNum[1] = mStageNum[2];
		mStageNum[2] = EscapeStageNum;
	}
	TPos3d<float> fMoveInput;	// スティックの入力値を入れる変数

	if (GetUseVController())
	{// コントローラーの左スティックの傾きを取得
		fMoveInput.x = IsStickLeft().x;
		//fMoveInput.z = IsStickLeft().y * -1;	// 上下逆(↑が－1)
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
	return mStageNum[0].Type;	//遷移先シーンの種類
}