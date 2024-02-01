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

// =============== 列挙型定義 ===================
enum E_2D	//更新順
{
	E_2D_BACK,		//背景
	E_2D_START,		//開始コマンド
	E_2D_FINISH,	//終了コマンド
	E_2D_LOGO,		//タイトルロゴ
	E_2D_OPENING,	//開始映像
	E_2D_MAX,		//要素数
};	//2Dのオブジェクト

// =============== 定数定義 ===================
const float START_RADIUS_CAMERA = 0.5f;		//初期カメラ距離
const float END_RADIUS_CAMERA = 15.0f;		//最終カメラ距離
const int ZOOMOUT_FRAME = 90;				//ズームアウトにかけるフレーム数
const float COMMAND_SPACE = 120.0f;			//コマンド同士の縦の間
const float COMMAND_DOWN = 160.0f;			//コマンドを中心からどれだけ下げるか
const std::map<int, int> MAP_WAIT_START = {
	{E_2D_BACK, 0},	//背景
	{E_2D_START, ZOOMOUT_FRAME},	//開始コマンド
	{E_2D_FINISH, ZOOMOUT_FRAME},	//終了コマンド
	{E_2D_LOGO, 0},		//タイトルロゴ
	{E_2D_OPENING, 0},	//開始映像
};	//ポリゴンと表示開始待機時間の対応表
const std::map<int, int> MAP_WAIT_FIN = {
	{E_2D_BACK, 30},	//背景
	{E_2D_START, 15},	//開始コマンド
	{E_2D_FINISH, 30},	//終了コマンド
	{E_2D_LOGO, 15},	//タイトルロゴ
};	//ポリゴンと表示終了待機時間の対応表
const std::map<int, std::string> MAP_TEXTURE = {
	{E_2D_BACK, "Assets/Texture//Title/TitleBg.png"},				//背景
	{E_2D_START, "Assets/Texture/Title/Title_Start.png"},			//開始コマンド
	{E_2D_FINISH, "Assets/Texture/Pause/Pause_Finish.png"},			//終了コマンド
	{E_2D_LOGO, "Assets/Texture/Title/TitleLogo.png"},				//タイトルロゴ
	{E_2D_OPENING, "Assets/Texture/Title/titleopening_kari.png"},	//開始映像
};	//ポリゴンとテクスチャの対応表
const std::map<int, TPos3d<float>> MAP_POS = {
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},		//背景
	{E_2D_START, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f, 0.0f}},										//開始コマンド
	{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 260.0f - COMMAND_SPACE, 0.0f}},						//終了コマンド
	//{E_2D_LOGO, {static_cast<float>(SCREEN_WIDTH) / 2.0f, 450.0f, 0.0f}},										//タイトルロゴ
	{E_2D_OPENING, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},	//オープニング
};	//ポリゴンと初期座標の対応表

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
	, m_pSE{ nullptr,nullptr}
	, m_pSESpeaker{ nullptr ,nullptr}
{
	// =============== レンダラー ===================
	RenderTarget*  p = GetDefaultRTV();	//2D描画用レンダラー
	SetRenderTargets(1, &p, nullptr);	//2D描画用レンダラーセット

	// =============== 動的確保 ===================
	m_p2dObj = {
		{E_2D_BACK,new CBgTitle(MAP_WAIT_START.at(E_2D_BACK))},				//背景用
		{E_2D_START,new CCommandTitle(MAP_WAIT_START.at(E_2D_START))},		//継続コマンド用
		{E_2D_FINISH,new CCommandTitle(MAP_WAIT_START.at(E_2D_FINISH))},	//終了コマンド用
		{E_2D_LOGO,new CTitleLogo(MAP_WAIT_START.at(E_2D_LOGO))},			//タイトルロゴ用
#if USE_OPENING
		{E_2D_OPENING,new COpeningTitle()},									//開始映像用
#endif
	};	//平面ポリゴン
	m_pCamera = new CFixedCamera();	//固定カメラ

	// =============== 初期化 ===================
	//m_pCamera->SetRadius(START_RADIUS_CAMERA);	//初期距離設定
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		// =============== 検査 ===================
		if (m_p2dObj.find(nIdx) == m_p2dObj.end() || !m_p2dObj.at(nIdx))	//アクセスチェック・ヌルチェック
		{
			// =============== 終了 ===================
			continue;	//処理対象外
		}
		if (MAP_POS.find(nIdx) != MAP_POS.end())	//mapの配列が存在する添え字
		{
			m_p2dObj.at(nIdx)->SetPos({ MAP_POS.at(nIdx) });				//位置初期化
		}
		if (MAP_TEXTURE.find(nIdx) != MAP_TEXTURE.end())	//mapの配列が存在する添え字
		{
			m_p2dObj.at(nIdx)->SetTexture(MAP_TEXTURE.at(nIdx).c_str());	//テクスチャ登録
		}

		// =============== カメラ登録 ===================
		m_p2dObj.at(nIdx)->SetCamera(m_pCamera);	//カメラ登録
	}

	// =============== 状態 ===================
	if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
		&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Selected();	//選択状態遷移
	}
#if !USE_OPENING	//開始映像がない場合かわりに縮小を呼ぶ
	// =============== 縮小 ===================
	if (m_p2dObj.find(E_2D_BACK) != m_p2dObj.end() && m_p2dObj.at(E_2D_BACK)
		&& typeid(CBgTitle) == typeid(*m_p2dObj.at(E_2D_BACK)))	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CBgTitle*>(m_p2dObj[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//背景縮小開始
	}
	if (m_p2dObj.find(E_2D_LOGO) != m_p2dObj.end() && m_p2dObj.at(E_2D_LOGO)
		&& typeid(CTitleLogo) == typeid(*m_p2dObj.at(E_2D_LOGO)))	//アクセスチェック・ヌルチェック・型チェック
	{
		static_cast<CTitleLogo*>(m_p2dObj[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//ロゴ縮小開始
	}
#endif
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
	// =============== 終了 ===================
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		if (m_p2dObj.find(nIdx) != m_p2dObj.end() && m_p2dObj.at(nIdx))	//アクセスチェック・ヌルチェック
		{
			delete m_p2dObj.at(nIdx);	//対象削除
			m_p2dObj.erase(nIdx);		//mapから切除
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
	if (m_p2dObj.find(E_2D_OPENING) != m_p2dObj.end() && m_p2dObj.at(E_2D_OPENING)
		&& typeid(COpeningTitle) == typeid(*m_p2dObj.at(E_2D_OPENING)))	//アクセスチェック・ヌルチェック・型チェック
	{
		if (!static_cast<COpeningTitle*>(m_p2dObj[E_2D_OPENING])->GetAnimFlg())
		{
			// =============== 終了 ===================
			delete m_p2dObj.at(E_2D_OPENING);	//対象削除
			m_p2dObj.erase(E_2D_OPENING);		//mapから切除

			//// =============== ズームアウト ===================
			//if (m_pCamera)	//ヌルチェック
			//{
			//	m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);	//ズームアウト開始
			//}

			// =============== 縮小 ===================
			if (m_p2dObj.find(E_2D_BACK) != m_p2dObj.end() && m_p2dObj.at(E_2D_BACK)
				&& typeid(CBgTitle) == typeid(*m_p2dObj.at(E_2D_BACK)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CBgTitle*>(m_p2dObj[E_2D_BACK])->ChangeLtoS(ZOOMOUT_FRAME);	//背景縮小開始
			}
			if (m_p2dObj.find(E_2D_LOGO) != m_p2dObj.end() && m_p2dObj.at(E_2D_LOGO)
				&& typeid(CTitleLogo) == typeid(*m_p2dObj.at(E_2D_LOGO)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CTitleLogo*>(m_p2dObj[E_2D_LOGO])->ChangeLtoS(ZOOMOUT_FRAME);	//ロゴ縮小開始
			}
		}
		else
		{
			// =============== 更新 ===================
			m_p2dObj[E_2D_OPENING]->Update();	//アニメ更新

			// =============== 終了 ===================
			return;	//これ以上更新しない
		}
	}

	// =============== 入力受付 ===================
	if (!(m_ucFlag & E_FLAG_TIDYING_UP))	//片付け中でない
	{
		// =============== コントローラ ==================
		if (GetUseVController())	// コントローラが接続されている場合
		{
			// =============== カーソル移動 ===================
			if (IsStickLeft().y < 0)		//↑入力時
			{
				// =============== 状態遷移 ===================
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Selected();	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_CONTINUE);								//上のコマンド採用
					}
				}
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->UnSelected();	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド不採用

						//===== SEの再生 =======
						PlaySE(SE_CHOOSE);
					}
				}

			}
			if (IsStickLeft().y > 0)	//↓入力時
			{
				// =============== 状態遷移 ===================
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->Selected();	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド採用
					}
				}
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->UnSelected();	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_CONTINUE);									//上のコマンド不採用

						//===== SEの再生 =======
						PlaySE(SE_CHOOSE);
					}
				}

			}

			// =============== 決定 ===================
			if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START))
				&& m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
			{
				if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//表示中
				{
					if (IsKeyTriggerController(BUTTON_B))	//Bボタン入力時
					{
						// =============== フラグ操作 ===================
						UpFlag(E_FLAG_DECIDE_COMMAND);	//決定

						//===== SEの再生 =======
						PlaySE(SE_DECISION);
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
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Selected();	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_CONTINUE);								//上のコマンド採用
					}
				}
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->UnSelected();	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド不採用

						//===== SEの再生 =======
						PlaySE(SE_CHOOSE);
					}
				}

			}
			if (IsKeyTrigger(VK_DOWN) || IsKeyTrigger('S'))	//↓・S入力時
			{
				// =============== 状態遷移 ===================
				if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->Selected();	//選択状態遷移
						UpFlag(E_FLAG_COMMAND_FINISH);									//下のコマンド採用
					}
				}
				if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
					&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
				{
					if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw())	//表示中
					{
						static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->UnSelected();	//選択状態遷移
						DownFlag(E_FLAG_COMMAND_CONTINUE);									//上のコマンド不採用
						//===== SEの再生 =======
						PlaySE(SE_CHOOSE);
					}
				}

			}

			// =============== 決定 ===================
			if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START))
				&& m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
				{
				if (static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->ChackDraw() && static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->ChackDraw())	//表示中
				{
					if (IsKeyTrigger(VK_RETURN) || IsKeyTrigger(VK_SPACE))	//Enter・Space入力時
					{
						// =============== フラグ操作 ===================
						UpFlag(E_FLAG_DECIDE_COMMAND);	//決定

						//===== SEの再生 =======
						PlaySE(SE_DECISION);
					}
				}
			}
		}
	}

	// =============== 選択確定 ===================
	if (m_ucFlag & E_FLAG_DECIDE_COMMAND)	//コマンド決定時
	{
		// =============== 選択状態判定 ===================
		if (m_ucFlag & E_FLAG_COMMAND_CONTINUE)	//継続
		{
			// =============== 状態遷移 ===================
			if (m_p2dObj.find(E_2D_START) != m_p2dObj.end() && m_p2dObj.at(E_2D_START)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_START)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CCommandTitle*>(m_p2dObj[E_2D_START])->Decide();	//決定状態遷移
			}

			m_bFinish = true;					//シーンの終了申請
			m_eNextScene = E_TYPE_SELECT_STAGE;	//ステージ選択へ
			DownFlag(E_FLAG_DECIDE_COMMAND);	//決定処理完了
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH)	//終了
		{
			// =============== 状態遷移 ===================
			if (m_p2dObj.find(E_2D_FINISH) != m_p2dObj.end() && m_p2dObj.at(E_2D_FINISH)
				&& typeid(CCommandTitle) == typeid(*m_p2dObj.at(E_2D_FINISH)))	//アクセスチェック・ヌルチェック・型チェック
			{
				static_cast<CCommandTitle*>(m_p2dObj[E_2D_FINISH])->Decide();	//決定状態遷移
			}
			m_bFinish = true;					//シーンの終了申請
			m_eNextScene = E_TYPE_FINISH_ALL;	//アプリ終了
			DownFlag(E_FLAG_DECIDE_COMMAND);	//決定処理完了
		}
	}



	// =============== 更新 ===================
	if (m_pCamera)	//ヌルチェック
	{
		m_pCamera->Update();	//カメラ更新
	}
	for (int nIdx = 0; nIdx < E_2D_MAX; nIdx++)
	{
		if (m_p2dObj.find(nIdx) != m_p2dObj.end() && m_p2dObj.at(nIdx))	//アクセスチェック・ヌルチェック
		{
			m_p2dObj.at(nIdx)->Update();	//更新対象
		}
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
		if (m_p2dObj.find(nIdx) != m_p2dObj.end() && m_p2dObj.at(nIdx))	//アクセスチェック・ヌルチェック
		{
			m_p2dObj.at(nIdx)->Draw();	//描画対象
		}
	}
}

/* ========================================
	種類ゲッタ
	----------------------------------------
	内容：自身がタイトルシーンであることを示す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：自身の種類
=========================================== */
CTitle::E_TYPE CTitle::GetType() const
{
	// =============== 提供 ===================
	return CTitle::E_TYPE_TITLE;	//自身の種類
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