/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	タイトルシーン実装
	---------------------------------------
	Title.cpp
	------------------------------------
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
	・2024/01/20 GetType()関数削除・リファクタリング takagi
	
========================================== */

// =============== デバッグモード ===================
#define USE_OPENING (false)	//オープニングが存在するか

// =============== インクルード ===================
#include "Title.h"			//自身のヘッダ
#include "Input.h"			//入力受付
#include "FixedCamera.h"	//インスタンス候補
#include "BgTitle.h"		//インスタンス候補
#include "CommandTitle.h"	//インスタンス候補
#include "TitleLogo.h"		//インスタンス候補
#include "OpeningTitle.h"	//インスタンス候補

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
	:m_ucFlag(E_FLAG_COMMAND_CONTINUE)	//フラグ
{
	// =============== レンダラー ===================
	RenderTarget*  p = GetDefaultRTV();	//2D描画用レンダラー
	SetRenderTargets(1, &p, nullptr);	//2D描画用レンダラーセット

	// =============== 動的確保 ===================
	m_p2dObjectOnScreen.emplace(E_2D_BACK, new CBgTitle(MAP_WAIT_START.at(E_2D_BACK)));			//背景
	m_p2dObjectOnScreen.emplace(E_2D_START, new CCommandTitle(MAP_WAIT_START.at(E_2D_START)));	//継続コマンド
	m_p2dObjectOnScreen.emplace(E_2D_FINISH, new CCommandTitle(MAP_WAIT_START.at(E_2D_FINISH)));	//終了コマンド
	m_p2dObjectOnScreen.emplace(E_2D_LOGO, new CTitleLogo(MAP_WAIT_START.at(E_2D_LOGO)));		//タイトルロゴ
#if USE_OPENING
	m_p2dObjectOnScreen.emplace(E_2D_OPENING, new COpeningTitle());							//開始映像
#endif
	m_pCamera = new CFixedCamera();	//固定カメラ

	// =============== 初期化 ===================
	//m_pCamera->SetRadius(START_RADIUS_CAMERA);	//初期距離設定
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		// =============== 検査 ===================
		if (m_p2dObjectOnScreen.find(nIdx) == m_p2dObjectOnScreen.end() || !m_p2dObjectOnScreen.at(nIdx))	//アクセスチェック・ヌルチェック
		{
			// =============== 終了 ===================
			continue;	//処理対象外
		}
		if (MAP_POS.find(nIdx) != MAP_POS.end())	//mapの配列が存在する添え字
		{
			m_p2dObjectOnScreen.at(nIdx)->SetPos({ MAP_POS.at(nIdx) });				//位置初期化
		}
		if (MAP_TEXTURE.find(nIdx) != MAP_TEXTURE.end())	//mapの配列が存在する添え字
		{
			m_p2dObjectOnScreen.at(nIdx)->SetTexture(MAP_TEXTURE.at(nIdx).c_str());	//テクスチャ登録
		}

		// =============== カメラ登録 ===================
		m_p2dObjectOnScreen.at(nIdx)->SetCamera(m_pCamera);	//カメラ登録
	}

	// =============== 状態 ===================
	if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
		&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Selected();	//選択状態遷移
	}
#if !USE_OPENING	//開始映像がない場合かわりに縮小を呼ぶ
	// =============== 縮小 ===================
	if (m_p2dObjectOnScreen.find(E_2D_BACK) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_BACK)
		&& typeid(CBgTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_BACK)))	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CBgTitle*>(m_p2dObjectOnScreen[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//背景縮小開始
	}
	if (m_p2dObjectOnScreen.find(E_2D_LOGO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_LOGO)
		&& typeid(CTitleLogo) == typeid(*m_p2dObjectOnScreen.at(E_2D_LOGO)))	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CTitleLogo*>(m_p2dObjectOnScreen[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//ロゴ縮小開始
	}
#endif
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
	// =============== 終了 ===================
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		if (m_p2dObjectOnScreen.find(nIdx) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(nIdx))	//アクセスチェック・ヌルチェック
		{
			delete m_p2dObjectOnScreen.at(nIdx);	//対象削除
			m_p2dObjectOnScreen.erase(nIdx);		//mapから切除
		}
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
void CTitle::Update()
{
	// =============== 状態 ===================
	if (m_p2dObjectOnScreen.find(E_2D_OPENING) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_OPENING)
		&& typeid(COpeningTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_OPENING)))	//アクセスチェック・ヌルチェック・型チェック
	{
		if (!static_cast<COpeningTitle*>(m_p2dObjectOnScreen[E_2D_OPENING])->GetAnimFlg())	//OPアニメーション中は描画しない
		{
			// =============== 終了 ===================
			delete m_p2dObjectOnScreen.at(E_2D_OPENING);	//対象削除
			m_p2dObjectOnScreen.erase(E_2D_OPENING);		//mapから切除

			//// =============== ズームアウト ===================
			//if (m_pCamera)	//ヌルチェック
			//{
			//	m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);	//ズームアウト開始
			//}

			// =============== 縮小 ===================
			if (m_p2dObjectOnScreen.find(E_2D_BACK) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_BACK)
				&& typeid(CBgTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_BACK)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CBgTitle*>(m_p2dObjectOnScreen[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//背景縮小開始
			}
			if (m_p2dObjectOnScreen.find(E_2D_LOGO) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_LOGO)
				&& typeid(CTitleLogo) == typeid(*m_p2dObjectOnScreen.at(E_2D_LOGO)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CTitleLogo*>(m_p2dObjectOnScreen[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//ロゴ縮小開始
			}
		}
		else
		{
			// =============== 更新 ===================
			m_p2dObjectOnScreen[E_2D_OPENING]->Update();	//アニメ更新

			// =============== 終了 ===================
			return;	//これ以上更新しない
		}
	}

	// =============== 入力受付 ===================
	if (!(m_ucFlag.Check(E_FLAG_TIDYING_UP)))	//片付け中でない
	{
		// =============== コントローラ ==================
		if (GetUseVController())	// コントローラが接続されている場合
		{
			// =============== カーソル移動 ===================
			if (IsStickLeft().y < 0)		//↑入力時
			{
				// =============== 状態遷移 ===================
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Selected();		//選択状態遷移
						m_ucFlag.Up(E_FLAG_COMMAND_CONTINUE);								//上のコマンド採用
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->UnSelected();	//選択状態遷移
						m_ucFlag.Down(E_FLAG_COMMAND_FINISH);								//下のコマンド不採用
					}
				}
			}
			if (IsStickLeft().y > 0)	//↓入力時
			{
				// =============== 状態遷移 ===================
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->Selected();	//選択状態遷移
						m_ucFlag.Up(E_FLAG_COMMAND_FINISH);										//下のコマンド採用
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->UnSelected();	//選択状態遷移
						m_ucFlag.Down(E_FLAG_COMMAND_CONTINUE);									//上のコマンド不採用
					}
				}
			}

			// =============== 決定 ===================
			if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START))
				&& m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
			{
				if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//表示中
				{
					if (IsKeyTriggerController(BUTTON_B))	//Bボタン入力時
					{
						// =============== フラグ操作 ===================
						m_ucFlag.Up(E_FLAG_DECIDE_COMMAND);	//決定
					}
				}
			}
		}
		else
		{
			// =============== カーソル移動 ===================
			if (IsKeyTrigger(VK_UP) || IsKeyTrigger('W'))		//↑・W入力時
			{
				// =============== 状態遷移 ===================
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Selected();		//選択状態遷移
						m_ucFlag.Up(E_FLAG_COMMAND_CONTINUE);								//上のコマンド採用
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->UnSelected();	//選択状態遷移
						m_ucFlag.Down(E_FLAG_COMMAND_FINISH);								//下のコマンド不採用
					}
				}
			}
			if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//↓・S入力時
			{
				// =============== 状態遷移 ===================
				if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->Selected();	//選択状態遷移
						m_ucFlag.Up(E_FLAG_COMMAND_FINISH);									//下のコマンド採用
					}
				}
				if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->UnSelected();	//選択状態遷移
						m_ucFlag.Down(E_FLAG_COMMAND_CONTINUE);								//上のコマンド不採用
					}
				}
			}

			// =============== 決定 ===================
			if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START))
				&& m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
				if (static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->ChackDraw())	//表示中
				{
					if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE))	//Enter・Space入力時
					{
						// =============== フラグ操作 ===================
						m_ucFlag.Up(E_FLAG_DECIDE_COMMAND);	//決定
					}
				}
			}
		}
	}

	// =============== 選択確定 ===================
	if (m_ucFlag.Check(E_FLAG_DECIDE_COMMAND))	//コマンド決定時
	{
		// =============== 選択状態判定 ===================
		if (m_ucFlag.Check(E_FLAG_COMMAND_CONTINUE))	//継続
		{
			// =============== 状態遷移 ===================
			if (m_p2dObjectOnScreen.find(E_2D_START) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_START])->Decide();	//決定状態遷移
			}

			m_bFinish = true;						//シーンの終了申請
			m_eNextScene = E_TYPE_SELECT_STAGE;		//ステージ選択へ
			m_ucFlag.Down(E_FLAG_DECIDE_COMMAND);	//決定処理完了
		}
		if (m_ucFlag.Check(E_FLAG_COMMAND_FINISH))	//終了
		{
			// =============== 状態遷移 ===================
			if (m_p2dObjectOnScreen.find(E_2D_FINISH) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObjectOnScreen.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CCommandTitle*>(m_p2dObjectOnScreen[E_2D_FINISH])->Decide();	//決定状態遷移
			}
			m_bFinish = true;						//シーンの終了申請
			m_eNextScene = E_TYPE_FINISH_ALL;		//アプリ終了
			m_ucFlag.Down(E_FLAG_DECIDE_COMMAND);	//決定処理完了
		}
	}

	// =============== 更新 ===================
	if (m_pCamera)	//ヌルチェック
	{
		m_pCamera->Update();	//カメラ更新
	}
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		CScene::Update();	//親関数呼び出し
		//if (m_p2dObjectOnScreen.find(nIdx) != m_p2dObjectOnScreen.end() && m_p2dObjectOnScreen.at(nIdx))	//アクセスチェック・ヌルチェック
		//{
		//	m_p2dObjectOnScreen.at(nIdx)->Update();	//更新対象
		//}
	}
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
	// =============== 描画 ===================
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		CScene::Draw();	//親関数呼び出し
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
CTitle::E_TYPE CTitle::GetNext() const
{
	// =============== 提供 ===================
	return CTitle::m_eNextScene;	//遷移先シーンの種類
}