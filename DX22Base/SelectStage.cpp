/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ステージセレクト実装
	---------------------------------------
	SelectStage.cpp
	---------------------------------------
	作成者
			takagi
			nieda

	変更履歴
	・2023/11/16 制作 takagi
	・2023/12/12 ステージセレクトを追加　yamamoto
	・2024/01/20 リファクタリング takagi
	・2024/01/21 コメント改修・MessageBox改善 takagi

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
	,Num(0)
{
	mStageNum[0].Type = E_TYPE_STAGE1;
	mStageNum[0].m_pTexture= new Texture();
	if (FAILED(mStageNum[0].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo1.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "tehaisyo1.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
	}

	mStageNum[1].Type = E_TYPE_STAGE2;
	mStageNum[1].m_pTexture = new Texture();
	if (FAILED(mStageNum[1].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "tehaisyo2.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
	}
	mStageNum[2].Type = E_TYPE_STAGE3;
	mStageNum[2].m_pTexture = new Texture();
	if (FAILED(mStageNum[2].m_pTexture->Create("Assets/Texture/StageSelect/tehaisyo3.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "tehaisyo3.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
	}

	for (int i = 0; i < 5; i++)
	{
		m_2dObj[i] = new C2dObject();
		m_2dObj[i]->SetCamera(m_pCamera);					//カメラセッタ
	}
	m_pStageSelectBG= new Texture();
	if (FAILED(m_pStageSelectBG->Create("Assets/Texture/StageSelect/StageSelectBG.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "StageSelectBG.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
	}
	m_pStageSelectUI = new Texture();
	if (FAILED(m_pStageSelectUI->Create("Assets/Texture/StageSelect/stselectUI.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error：";	//エラー箇所
		MessageBox(nullptr, (ErrorSpot + "stselectUI.png読み込み失敗").c_str(), "Error", MB_OK | MB_ICONERROR);						//エラー通知
#endif
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
	// =============== 入力受付 ===================
	//if (!(m_ucFlag.Check(E_FLAG_TIDYING_UP)))	//片付け中でない
	//{
		// =============== コントローラ ==================
		if (GetUseVController())	// コントローラが接続されている場合
		{
			// =============== カーソル移動 ===================
			if (IsStickLeft().x < 0)		//←入力時
			{
				Num += 1;
				if (Num > 2)Num = 2;
			}
			if (IsStickLeft().x > 0)	//→入力時
			{
				Num -= 1;
				if (Num < 0) Num = 0;
			}

			// =============== 決定 ===================
			if (IsKeyTriggerController(BUTTON_B))	//Bボタン入力時
			{
				// =============== フラグ操作 ===================
				m_bFinish = true;	//シーン終了
			}
		}
		else
		{
			//// =============== カーソル移動 ===================
			//if (IsKeyTrigger(VK_UP) || IsKeyTrigger('W'))		//↑・W入力時
			//{
			//	// =============== 状態遷移 ===================
			//	if (m_p2dObject.find(E_2D_START) != m_p2dObject.end() && m_p2dObject.at(E_2D_START)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->ChackUpdate())	//表示中
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->Selected();		//選択状態遷移
			//			m_ucFlag.Up(E_FLAG_COMMAND_CONTINUE);								//上のコマンド採用
			//		}
			//	}
			//	if (m_p2dObject.find(E_2D_FINISH) != m_p2dObject.end() && m_p2dObject.at(E_2D_FINISH)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->ChackUpdate())	//表示中
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->UnSelected();	//選択状態遷移
			//			m_ucFlag.Down(E_FLAG_COMMAND_FINISH);								//下のコマンド不採用
			//		}
			//	}
			//}
			//if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//↓・S入力時
			//{
			//	// =============== 状態遷移 ===================
			//	if (m_p2dObject.find(E_2D_FINISH) != m_p2dObject.end() && m_p2dObject.at(E_2D_FINISH)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->ChackUpdate())	//表示中
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_FINISH])->Selected();	//選択状態遷移
			//			m_ucFlag.Up(E_FLAG_COMMAND_FINISH);									//下のコマンド採用
			//		}
			//	}
			//	if (m_p2dObject.find(E_2D_START) != m_p2dObject.end() && m_p2dObject.at(E_2D_START)
			//		&& typeid(CCommandTitle) == typeid(*m_p2dObject.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
			//	{
			//		if (static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->ChackUpdate())	//表示中
			//		{
			//			static_cast<CCommandTitle*>(m_p2dObject[E_2D_START])->UnSelected();	//選択状態遷移
			//			m_ucFlag.Down(E_FLAG_COMMAND_CONTINUE);								//上のコマンド不採用
			//		}
			//	}
			//}

			// =============== 決定 ===================
			if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE))	//Enter・Space入力時
			{
				// =============== フラグ操作 ===================
				m_bFinish = true;	//シーン終了
			}		
		}
	//}


	//背景
		m_2dObj[3]->SetTexture(m_pStageSelectBG);
		m_2dObj[3]->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 ,1.0f });
		m_2dObj[3]->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT ,1.0f });
		m_2dObj[3]->Update();



		if (!(0 == Num))
		{//ステージ1
			m_2dObj[0]->SetTexture(mStageNum[0].m_pTexture);
			m_2dObj[0]->SetPos({ 250.0f, 300.0f,1.0f });
			m_2dObj[0]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f });
			m_2dObj[0]->SetRotate({ 0.0f,0.0f,-0.25f });
			m_2dObj[0]->SetColor(0.5f, 1.0f);
			m_2dObj[0]->Update();
		}
		if (!(1 == Num))
		{
			//ステージ2
			m_2dObj[1]->SetTexture(mStageNum[1].m_pTexture);
			m_2dObj[1]->SetPos({ 600.0f, 300.0f,1.0f });
			m_2dObj[1]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
			m_2dObj[1]->SetRotate({ 0.0f,0.0f,0.05f });
			m_2dObj[1]->SetColor(0.5f, 1.0f);
			m_2dObj[1]->Update();
		}
		if (!(2 == Num))
		{
			//ステージ3
			m_2dObj[2]->SetTexture(mStageNum[2].m_pTexture);
			m_2dObj[2]->SetPos({ 950.0f, 300.0f,1.0f });
			m_2dObj[2]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH , TEXTURE_SELECT_STAGE_HEIGHT   ,1.0f });
			m_2dObj[2]->SetRotate({ 0.0f,0.0f,0.1f });
			m_2dObj[2]->SetColor(0.5f, 1.0f);
			m_2dObj[2]->Update();
		}

		m_2dObj[Num]->SetTexture(mStageNum[Num].m_pTexture);
		m_2dObj[Num]->SetColor(1.0f, 1.0f);
		m_2dObj[Num]->Update();

		//for (int i = SUTAGE_NUM-1; i > 0-1; i--)
		//{
		//	if (i == Num) continue;
		//	m_2dObj[i]->SetTexture(mStageNum[i].m_pTexture);
		//	m_2dObj[i]->SetPos({ TEXTURE_SELECT_STAGE_POSX + i * 100,TEXTURE_SELECT_STAGE_POSY-i*70,1.0f });
		//	m_2dObj[i]->SetSize({ TEXTURE_SELECT_STAGE_WIDTH, TEXTURE_SELECT_STAGE_HEIGHT ,1.0f});
		//	m_2dObj[i]->SetRotate({ 0.0f,0.0f,-0.3f });
		//	m_2dObj[i]->Update();
		//}
		//文字
		m_2dObj[4]->SetTexture(m_pStageSelectUI);
		m_2dObj[4]->SetPos({ 640.0f, 660.0f  ,1.0f });
		m_2dObj[4]->SetSize({ SCREEN_WIDTH, 120.0f ,1.0f });
		m_2dObj[4]->Update();
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
		Num -= 1;
		if (Num < 0) Num = 0;
	//EscapeStageNum = mStageNum[2];
	//mStageNum[2] = mStageNum[1];
	//mStageNum[1] = mStageNum[0];
	//mStageNum[0] = EscapeStageNum;
	}
	if (IsKeyTrigger('D'))
	{
		Num += 1;
		if (Num > 2)Num = 2;
		//EscapeStageNum = mStageNum[0];
		//mStageNum[0] = mStageNum[1];
		//mStageNum[1] = mStageNum[2];
		//mStageNum[2] = EscapeStageNum;
	}
	TPos3d<float> fMoveInput;	// スティックの入力値を入れる変数

	//if (GetUseVController())
	//{// コントローラーの左スティックの傾きを取得
	//	fMoveInput.x = IsStickLeft().x;
	//	//fMoveInput.z = IsStickLeft().y * -1;	// 上下逆(↑が－1)
	//	if (fMoveInput.x < 0.0f)
	//	{
	//		EscapeStageNum = mStageNum[2];
	//		mStageNum[2] = mStageNum[1];
	//		mStageNum[1] = mStageNum[0];
	//		mStageNum[0] = EscapeStageNum;
	//	}
	//	if (fMoveInput.x > 0.0f)
	//	{
	//		EscapeStageNum = mStageNum[0];
	//		mStageNum[0] = mStageNum[1];
	//		mStageNum[1] = mStageNum[2];
	//		mStageNum[2] = EscapeStageNum;
	//	}
	//}
	if (IsKeyTrigger(VK_SPACE) || IsKeyTriggerController(BUTTON_B))
	{
		m_bFinish = true;	// タイトルシーン終了フラグON
	}
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