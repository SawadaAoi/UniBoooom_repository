/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルシーン実装
	---------------------------------------
	Title.cpp

	作成者
			takagi
			nieda

	変更履歴
	・2023/10/26 仮制作 takagi
	・2023/11/05 現段階のコーディング規約適用 takagi
	・2023/11/07 コメント修正 takagi
	・2023/11/16 オーバーライド関数追加 takagi
	・2023/11/22 仮テクスチャ表示、画面遷移 nieda
	・2023/11/23 コントローラーに対応 nieda
	・2023/11/24 コメント、定数定義、列挙追加 nieda
	・2023/12/12 遷移先シーンをステージセレクトに変更 yamamoto
	・2023/12/16 描画物改善 takagi
	・2023/12/17 コマンドが表示されていないときは決定キーを受け付けないように takagi
	・2023/12/18 画像差し替え・コマンド位置調整・オープニング使用切換作成 takagi
	・2024/01/26 選択、決定SE追加
	・2024/01/29 背景変更 takagi
	・2024/02/02 リファクタリング takagi
	・2024/02/05 リファクタリング takagi
	・2024/02/06 リファクタリング takagi
	・2024/02/09 GetType()関数削除・UsingCamera使用 takagi
	・2024/02/09 GetType()関数削除 takagi
	・2024/02/12 テクスチャ管理法変更に伴う修正 takagi
	・2024/02/13 コマンド選択時のバグ修正 takagi
	・2024/02/16 先行入力防止 takagi
	
========================================== */

// =============== インクルード ===================
#include "Title.h"				//自身のヘッダ
#include "Input.h"				//入力受付
#include "TitleInitCounter.h"	//初動カウンタ
#include "FixedCamera.h"		//インスタンス候補
#include "UsingCamera.h"		//カメラ使用

// =============== 定数・マクロ定義 ===================
const float START_RADIUS_CAMERA = 0.5f;						//初期カメラ距離
const float END_RADIUS_CAMERA = 15.0f;						//最終カメラ距離
#define PTR_UPDATE(ptr) do{if(ptr){ptr->Update();}}while(0)	//ヌルチェック・更新
#define PTR_DRAW(ptr) do{if(ptr){ptr->Draw();}}while(0)		//ヌルチェック・描画

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
=========================================== */
CTitle::CTitle()
	:m_ucFlag(E_FLAG_COMMAND_START)	//フラグ
	, m_pSE{ nullptr,nullptr}
	, m_pSESpeaker{ nullptr ,nullptr}
{
	// =============== レンダラー ===================
	RenderTarget*  p = GetDefaultRTV();	//2D描画用レンダラー
	SetRenderTargets(1, &p, nullptr);	//2D描画用レンダラーセット

	// =============== 動的確保 ===================
	m_pLogo = std::make_shared<CTitleLogo>();		//タイトルロゴ
	m_pBgBase = std::make_shared<CTitleBgBase>();	//背景
	m_pBgCloud = std::make_shared<CTitleBgCloud>();	//背景の雲
	m_pBgGrass = std::make_shared<CTitleBgGrass>();	//背景の草
	m_pMainCamera = std::make_shared<CFixedCamera>();	//固定カメラ
	m_pCommandStart = std::make_shared<CTitleCommandStart>();	//開始コマンド
	m_pCommandFinish = std::make_shared<CTitleCommandFinish>();	//終了コマンド
	m_pBgPlayer = std::make_shared<CTitleBgPlayer>();			//背景のプレイヤー

	// =============== カメラ登録 ===================
	CUsingCamera::GetThis().SetCamera(m_pMainCamera);	//カメラ登録

	// =============== アニメーション開始 ===================
	CTitleInitCounter::GetThis().StartCount();	//カウント開始

	//===サウンドファイル読み込み=====
	LoadSound();
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
CTitle::~CTitle()
{
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
void CTitle::Update()
{
	// =============== 変数宣言 ===================
	auto pCounter = CTitleInitCounter::GetThis().GetCounter().lock();	//カウンタ

	// =============== 破棄 ===================
	if (m_pBgPlayer && !m_pBgPlayer->GetAnimFlg())	//ヌルチェック・アニメーション検査
	{
		m_pBgPlayer.reset();	//削除
	}

	// =============== 入力受付 ===================
	if (!pCounter || pCounter->IsFin())	//ヌル・時間チェック
	{
		if (GetUseVController())	// コントローラが接続されている場合
		{
			// =============== カーソル移動 ===================
			if (IsStickLeft().y < 0)		//↑入力時
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_START))	//既に開始コマンドを選択していない
				{
					// =============== 状態遷移 ===================
					if (m_pCommandStart)	//ヌルチェック
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_SELECTED);	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_START);									//上のコマンド採用
					}
					if (m_pCommandFinish)	//ヌルチェック
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド不採用
					}
					//===== SEの再生 =======
					PlaySE(SE_CHOOSE);
				}
			}
			if (IsStickLeft().y > 0)	//↓入力時
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_FINISH))	//既に終了コマンドを選択していない
				{
					// =============== 状態遷移 ===================
					if (m_pCommandFinish)	//ヌルチェック
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_SELECTED);	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド採用
					}
					if (m_pCommandStart)	//ヌルチェック
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_START);										//上のコマンド不採用
					}
					//===== SEの再生 =======
					PlaySE(SE_CHOOSE);
				}
			}

			// =============== 決定 ===================
			if (IsKeyTriggerController(BUTTON_B) || IsKeyTriggerController(BUTTON_Y) && !(m_ucFlag & E_FLAG_DECIDE_COMMAND))	//Bボタン入力かつ非決定時
			{
				// =============== 選択状態判定 ===================
				if (m_ucFlag & E_FLAG_COMMAND_START && m_pCommandStart)	//開始コマンド・ヌルチェック
				{
					// =============== 状態遷移 ===================
					m_pCommandStart->ChangeState(CTitleCommand::E_STATE_DECIDE);	//決定状態遷移

					// =============== フラグ操作 ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//決定

					//===== SEの再生 =======
					PlaySE(SE_DECISION);
				}
				if (m_ucFlag & E_FLAG_COMMAND_FINISH && m_pCommandFinish)	//終了コマンド・ヌルチェック
				{
					// =============== 状態遷移 ===================
					m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_DECIDE);	//決定状態遷移

					// =============== フラグ操作 ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//決定

					//===== SEの再生 =======
					PlaySE(SE_DECISION);
				}
			}
		}
		else
		{//キーボード操作
			// =============== カーソル移動 ===================
			if (IsKeyTrigger(VK_UP) || IsKeyTrigger('W'))	//↑・W入力時
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_START))	//既に開始コマンドを選択していない
				{
					// =============== 状態遷移 ===================
					if (m_pCommandStart)	//ヌルチェック
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_SELECTED);	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_START);									//上のコマンド採用
					}
					if (m_pCommandFinish)	//ヌルチェック
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド不採用
					}
					//===== SEの再生 =======
					PlaySE(SE_CHOOSE);
				}
			}
			if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//↓・S入力時
			{
				if (!(m_ucFlag & E_FLAG_COMMAND_FINISH))	//既に終了コマンドを選択していない
				{
					// =============== 状態遷移 ===================
					if (m_pCommandFinish)	//ヌルチェック
					{
						m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_SELECTED);	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド採用
					}
					if (m_pCommandStart)	//ヌルチェック
					{
						m_pCommandStart->ChangeState(CTitleCommand::E_STATE_UNSELECTED);	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_START);										//上のコマンド不採用
					}
					//===== SEの再生 =======
					PlaySE(SE_CHOOSE);
				}
			}

			// =============== 決定 ===================
			if ((IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE)) && !(m_ucFlag & E_FLAG_DECIDE_COMMAND))	//Enter・Space入力かつ非決定時
			{
				// =============== 選択状態判定 ===================
				if (m_ucFlag & E_FLAG_COMMAND_START && m_pCommandStart)	//開始コマンド・ヌルチェック
				{
					// =============== 状態遷移 ===================
					m_pCommandStart->ChangeState(CTitleCommand::E_STATE_DECIDE);	//決定状態遷移

					// =============== フラグ操作 ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//決定

					//===== SEの再生 =======
					PlaySE(SE_DECISION);
				}
				if (m_ucFlag & E_FLAG_COMMAND_FINISH && m_pCommandFinish)	//終了コマンド・ヌルチェック
				{
					// =============== 状態遷移 ===================
					m_pCommandFinish->ChangeState(CTitleCommand::E_STATE_DECIDE);	//決定状態遷移

					// =============== フラグ操作 ===================
					UpFlag(E_FLAG_DECIDE_COMMAND);	//決定

					//===== SEの再生 =======
					PlaySE(SE_DECISION);
				}
			}
		}
	}

	// =============== 選択確定 ===================
	if (m_ucFlag & E_FLAG_DECIDE_COMMAND)	//コマンド決定時
	{
		// =============== 選択状態判定 ===================
		if (m_ucFlag & E_FLAG_COMMAND_START && m_pCommandStart && m_pCommandStart->DesideAnimeFin())	//開始コマンド・ヌルチェック・アニメ再生完了
		{
			// =============== 決定状態反映 ===================
			m_bFinish = true;					//シーンの終了申請
			m_eNextScene = E_TYPE_SELECT_STAGE;	//ステージ選択へ
			DownFlag(E_FLAG_DECIDE_COMMAND);	//決定処理完了
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH && m_pCommandFinish && m_pCommandFinish->DesideAnimeFin())	//終了コマンド・ヌルチェック・アニメ再生完了
		{
			// =============== 決定状態反映 ===================
			m_bFinish = true;					//シーンの終了申請
			m_eNextScene = E_TYPE_FINISH_ALL;	//アプリ終了
			DownFlag(E_FLAG_DECIDE_COMMAND);	//決定処理完了
		}
	}

	// =============== 更新 ===================
	CTitleInitCounter::GetThis().Update();	//カウンタ更新
	PTR_UPDATE(m_pBgBase);					//背景更新
	PTR_UPDATE(m_pBgCloud);					//雲更新
	if (!pCounter || pCounter->IsFin())	//ヌル・時間チェック
	{
		PTR_UPDATE(m_pBgPlayer);			//プレイヤー更新
	}
	PTR_UPDATE(m_pBgGrass);					//草原更新
	if (!pCounter || pCounter->IsFin())	//ヌル・時間チェック
	{
		PTR_UPDATE(m_pCommandStart);		//開始コマンド更新
		PTR_UPDATE(m_pCommandFinish);		//終了コマンド更新
	}
	PTR_UPDATE(m_pLogo);					//タイトルロゴ更新
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
void CTitle::Draw()
{
	// =============== 変数宣言 ===================
	auto pCounter = CTitleInitCounter::GetThis().GetCounter().lock();	//カウンタ

	// =============== 描画 ===================
	PTR_DRAW(m_pBgBase);		//背景描画
	PTR_DRAW(m_pBgCloud);		//雲描画
	if (!pCounter || pCounter->IsFin())	//ヌル・時間チェック
	{
	PTR_DRAW(m_pBgPlayer);		//プレイヤー描画
	}
	PTR_DRAW(m_pBgGrass);		//草原描画
	if (!pCounter || pCounter->IsFin())	//ヌル・時間チェック
	{
		PTR_DRAW(m_pCommandStart);	//開始コマンド描画
		PTR_DRAW(m_pCommandFinish);	//終了コマンド描画
	}
	PTR_DRAW(m_pLogo);			//タイトルロゴ描画
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
CTitle::E_TYPE CTitle::GetNext() const
{
	// =============== 提供 ===================
	return CTitle::m_eNextScene;	//遷移先シーンの種類
}

/* ========================================
	フラグオン関数
	-------------------------------------
	内容：引数に対応したフラグを起こす
	-------------------------------------
	引数1：const unsigned char & ucBitFlag：対象フラグ
	-------------------------------------
	戻値：なし
=========================================== */
void CTitle::UpFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag |= ucBitFlag;	//フラグ操作
}

/* ========================================
	フラグオフ関数
	-------------------------------------
	内容：引数に対応したフラグを降ろす
	-------------------------------------
	引数1：const unsigned char & ucBitFlag：対象フラグ
	-------------------------------------
	戻値：なし
=========================================== */
void CTitle::DownFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag &= (ucBitFlag ^ 0xFF);	//フラグ操作
}

/* ========================================
	フラグスイッチ関数
	-------------------------------------
	内容：引数に対応したフラグの反転
	-------------------------------------
	引数1：const unsigned char & ucBitFlag：対象フラグ
	-------------------------------------
	戻値：なし
=========================================== */
void CTitle::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag ^= ucBitFlag;	//フラグ操作
}

/* ========================================
   タイトル用SE読み込み関数
   ----------------------------------------
   内容：タイトル用のSEのファイルを読み込む
   ----------------------------------------
   引数：無し
   ----------------------------------------
   戻値：無し
======================================== */
void CTitle::LoadSound()
{
	//SEの読み込み
	for (int i = 0; i < SE_MAX; i++)
	{
		m_pSE[i] = CSound::LoadSound(m_sSEFile[i].c_str());
		if (!m_pSE[i])
		{
			MessageBox(NULL, m_sSEFile[i].c_str(), "Error", MB_OK);	//ここでエラーメッセージ表示
		}
	}
}

/* ========================================
	SEの再生関数
	----------------------------------------
	内容：SEの再生
	----------------------------------------
	引数1：SEの種類(enum)
	引数2：音量
	----------------------------------------
	戻値：なし
======================================== */
void CTitle::PlaySE(SE se, float volume)
{
	m_pSESpeaker[se] = CSound::PlaySound(m_pSE[se]);	//SE再生
	m_pSESpeaker[se]->SetVolume(volume);				//音量の設定
}