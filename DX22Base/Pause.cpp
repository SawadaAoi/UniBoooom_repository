/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ画面実装
	---------------------------------------
	Pause.cpp

	作成者	takagi

	変更履歴
	・2023/12/01 制作 takagi
	・2023/12/04 続き takagi
	・2023/12/05 続き takagi
	・2023/12/06 pose→pause修正、ポーズ文字表示 takagi
	・2023/12/08 更新部分制作進行 takagi
	・2023/12/09 オブジェクト分割 takagi
	・2023/12/10 制作進行 takagi

========================================== */

// =============== インクルード ===================
#include "Pause.h"		//自身のヘッダ
#include <map>			//関係性コンテナ
#include <array>		//配列
#include "CameraDef.h"	//疑似カメラ
#include "Input.h"		//キー入力
#include "CharPause.h"	//インスタンス候補
#include "BgPause.h"	//インスタンス候補

// =============== 列挙型定義 ===================
enum E_2D
{
	E_2D_BACK,		//背景
	E_2D_PA,		//ポーズの”ポ”
	E_2D_U,			//ポーズの”ー”
	E_2D_SE,		//ポーズの”ズ”
	E_2D_CONTINUE,	//継続コマンド
	E_2D_FINISH,	//終了コマンド
	E_2D_MAX,		//要素数
};	//2Dのオブジェクト
enum E_COMMAND
{
	E_COMMAND_CONTINUE,	//ゲームを続ける
	E_COMMAND_FINISH,	//ゲームをやめる
	E_COMMAND_MAX,		//要素数
};	//コマンド分岐
enum E_SHADER_TYPE
{
	E_SHADER_TYPE_VERTEX,	//頂点シェーダー
	E_SHADER_TYPE_PIXEL,	//ピクセルシェーダー
	E_SHADER_TYPE_MAX,		//要素数
};	//シェーダーの種類

// =============== 定数定義 ===================
///<summary>ゲームパラメータ用
///<para>定数の一部をいじれるように切り出したもの</para>
///</summary>
#include "GameParameter.h"
#if GAME_PARAMETER
const float COMMAND_SPACE_HALF = 85.0f;	//コマンド同士の縦の間
const float PAUSE_Y = 520.0f;			//ポーズ表示部中心y位置
const float PAUSE_SPACE = 85.0f;		//ポーズ表記の横の間
const float COMMAND_WIDTH = 320.0f;		//コマンド縦幅
const float COMMAND_HEIGHT = 70.0f;		//コマンド横幅
#endif // !GAME_PARAMETER
const std::string BGM_FILE_PASS("Assets/Sound/BGM/BGM_maou.mp3");
const std::string SE_FILE_PASS("Assets/Sound/SE/Smash.mp3");
const std::map<int, int> MAP_WAIT = {	//更新順
	{E_2D_BACK, 0},		//背景
	{E_2D_PA, 0},		//ポーズの”ポ”
	{E_2D_U, 0},		//ポーズの”ー”
	{E_2D_SE, 30},		//ポーズの”ズ”
	{E_2D_CONTINUE, 15},	//継続コマンド
	{E_2D_FINISH, 30},	//終了コマンド
};	//ポリゴンと表示開始待機時間の対応表
const std::map<int, std::string> MAP_TEXTURE = {	//更新順
	{E_2D_BACK, "Assets/Texture/Pause/PauseBg.png"},			//背景
	{E_2D_PA, "Assets/Texture/Pause/Pause_po.png"},				//ポーズの”ポ”
	{E_2D_U, "Assets/Texture/Pause/Pause_-.png"},				//ポーズの”ー”
	{E_2D_SE, "Assets/Texture/Pause/Pause_zu.png"},				//ポーズの”ズ
	{E_2D_CONTINUE, "Assets/Texture/Pause/Pause_Continue.png"},	//継続コマンド
	{E_2D_FINISH, "Assets/Texture/Pause/Pause_Finish.png"},		//終了コマンド
};	//ポリゴンとテクスチャの対応表
const std::map<int, TPos3d<float>> MAP_POS = {	//更新順
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},								//背景
	{E_2D_PA, {static_cast<float>(SCREEN_WIDTH) / 2.0f - CHARA_SPACE, CHARA_Y, 0.0f}},													//ポーズの”ポ”
	{E_2D_U, {static_cast<float>(SCREEN_WIDTH) / 2.0f, CHARA_Y, 0.0f}},																	//ポーズの”ー”
	{E_2D_SE, {static_cast<float>(SCREEN_WIDTH) / 2.0f + CHARA_SPACE, CHARA_Y, 0.0f}},													//ポーズの”ズ”
	{E_2D_CONTINUE, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f + COMMAND_SPACE_HALF, 0.0f}},	//継続コマンド
	{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f - COMMAND_SPACE_HALF, 0.0f}},		//終了コマンド
};	//ポリゴンと初期座標の対応表
const std::map<int, TPos3d<float>> MAP_SIZE = {	//更新順
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f}},	//背景
	{E_2D_PA, {CHARA_WIDTH, CHARA_HEIGHT, 0.0f}},												//ポーズの”ポ”
	{E_2D_U, {CHARA_WIDTH, CHARA_HEIGHT, 0.0f}},												//ポーズの”ー”
	{E_2D_SE, {CHARA_WIDTH, CHARA_HEIGHT, 0.0f}},												//ポーズの”ズ”
	{E_2D_CONTINUE, {COMMAND_WIDTH, COMMAND_HEIGHT, 0.0f}},										//継続コマンド
	{E_2D_FINISH, {COMMAND_WIDTH, COMMAND_HEIGHT, 0.0f}},										//終了コマンド
};	//ポリゴンと初期サイズの対応表
const std::map<int, std::array<std::string, E_SHADER_TYPE_MAX>> MAP_SHADER = {
	{E_2D_BACK, {"Assets/Shader/VsPause.cso", "Assets/Shader/PsPause.cso"}},	//背景
	//TODO:この先オブジェクトを追加したときに読み込むシェーダーがずれたりする恐れがあるので通常時用のシェーダーも作って読み込ませる？
};	//ポリゴンとシェーダー[頂点, ピクセル]の対応表

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：const CCamera* pCamera：カメラのポインタ
	----------------------------------------
	戻値：なし
=========================================== */
CPause::CPause(const CCamera* pCamera)
	:m_ucFlag(0x00)			//フラグ
	,m_pBgPs(nullptr)		//背景用ピクセルシェーダ
	,m_pBgVs(nullptr)		//背景用頂点シェーダ
{	
	// =============== 初期化 ===================
	m_pCamera = pCamera;	//カメラ初期化
	InitObjects();			//オブジェクト初期化
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
CPause::~CPause()
{	
	// =============== 終了 ===================
	SAFE_DELETE(m_pBgPs);						//ピクセルシェーダー削除
	SAFE_DELETE(m_pBgVs);						//頂点シェーダー削除
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.end(); Iterator != m_p2dObj.begin();)
	{
		if (*(--Iterator))	//ヌルチェック
		{
			delete (*Iterator);					//メモリ解放
		}
		Iterator = m_p2dObj.erase(Iterator);	//イテレータ削除・移動
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
void CPause::Update()
{
	// =============== コントローラ ==================
	if (GetUseVController())	// コントローラが接続されている場合
	{
		// =============== カーソル移動 ===================
		if (IsStickLeft().y < 0)	//↑入力時
		{
			// =============== フラグ操作 ===================
			UpFlag(E_FLAG_COMMAND_CONTINUE);	//上のコマンド採用
			DownFlag(E_FLAG_COMMAND_FINISH);	//下のコマンド不採用
		}
		if (IsStickLeft().y > 0)	//↓入力時
		{
			// =============== フラグ操作 ===================
			UpFlag(E_FLAG_COMMAND_FINISH);		//下のコマンド採用
			DownFlag(E_FLAG_COMMAND_CONTINUE);	//上のコマンド不採用
		}

		// =============== 決定 ===================
		if (IsKeyTriggerController(BUTTON_A))	//Aボタン入力時
		{
			// =============== フラグ操作 ===================
			UpFlag(E_FLAG_DECIDE_COMMAND);	//決定
		}
	}
	else
	{
		// =============== 起動・終了 ===================
		if (IsKeyTrigger('P'))
		{
			// =============== フラグ操作 ===================
			if (IsPause())	//すでにポーズ中
			{
				Destroy();
			}
			else
			{
				//UpFlag(E_FLAG_PAUSEMODE | E_FLAG_COMMAND_CONTINUE);	//ポーズ反転
				Boot();
			}
		}

		// =============== 検査 ===================
		if (!IsPause())	//ポーズ中でない
		{
			// =============== 終了 ===================
			return;	//処理中断
		}

		// =============== カーソル移動 ===================
		if (IsKeyTrigger(VK_UP))		//↑入力時
		{
			// =============== フラグ操作 ===================
			UpFlag(E_FLAG_COMMAND_CONTINUE);	//上のコマンド採用
			DownFlag(E_FLAG_COMMAND_FINISH);	//下のコマンド不採用
		}
		if (IsKeyTrigger(VK_DOWN))	//↓入力時
		{
			// =============== フラグ操作 ===================
			UpFlag(E_FLAG_COMMAND_FINISH);		//下のコマンド採用
			DownFlag(E_FLAG_COMMAND_CONTINUE);	//上のコマンド不採用
		}

		// =============== 決定 ===================
		if (IsKeyTrigger(VK_RETURN))	//Enter入力時
		{
			// =============== フラグ操作 ===================
			UpFlag(E_FLAG_DECIDE_COMMAND);	//決定
		}
	}
	
	// =============== 選択確定 ===================
	if (m_ucFlag & E_FLAG_DECIDE_COMMAND)	//コマンド決定時
	{
		// =============== 選択状態判定 ===================
		if (m_ucFlag & E_FLAG_COMMAND_CONTINUE)	//継続
		{
			// =============== フラグ操作 ===================
			DownFlag(E_FLAG_PAUSEMODE | E_FLAG_COMMAND_CONTINUE | E_FLAG_DECIDE_COMMAND);	//ポーズを中断し、ゲームを再開する
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH)	//継続
		{
			// =============== フラグ操作 ===================
			DownFlag(E_FLAG_PAUSEMODE | E_FLAG_COMMAND_FINISH | E_FLAG_DECIDE_COMMAND);	//ポーズを中断する
			UpFlag(E_FLAG_CALL_FINISH);													//ゲームの終了申請
		}
	}

	// =============== 変数宣言 ===================
	int nCnt = 0;	//ループカウント用

	// =============== 更新 ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); )
	{
		if (MAP_TEXTURE.size() > nCnt)	//mapの配列が存在する添え字
		{
			if (*Iterator)	//ヌルチェック
			{
				(*Iterator)->Update();						//平面描画
				if ((*Iterator)->IsDestroyed())	//破棄しても良いとき
				{
					delete(*Iterator);						//メモリ解放
					Iterator = m_p2dObj.erase(Iterator);	//イテレータ削除
				}
				else
				{
					Iterator++;								//イテレータ補正
				}
			}
		}

		// =============== カウンタ ===================
		nCnt++;	//カウント進行
	}

	// =============== ポーズ解除 ===================
	if (0 == m_p2dObj.size())	//オブジェクト無し時
	{
		// =============== フラグ操作 ===================
		DownFlag(0xFF);	//フラグ無効化
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
void CPause::Draw()
{
	// =============== モード検査 ===================
	if (!(m_ucFlag & E_FLAG_PAUSEMODE))	//ポーズモードのフラグが立っていない
	{
		// =============== 終了 ==================
		return;	//処理中断
	}

	// =============== 変数宣言 ===================
	int nCnt = 0;	//ループカウント用
	RenderTarget*  p = GetDefaultRTV();
	SetRenderTargets(1, &p , nullptr);

	// =============== 描画 ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//mapの配列が存在する添え字
		{
			if (*Iterator)	//ヌルチェック
			{
				(*Iterator)->Draw();	//平面描画
			}
		}

		// =============== カウンタ ===================
		nCnt++;	//カウント進行
	}
	SetRenderTargets(1, &p, GetDefaultDSV());
}

/* ========================================
	終了検査関数
	----------------------------------------
	内容：終了フラグの値を返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
bool CPause::IsFin() const
{
	// =============== 提供 ===================
	return (m_ucFlag & E_FLAG_CALL_FINISH);	//終了フラグ
}

/* ========================================
	カメラ登録関数
	----------------------------------------
	内容：nullptrでないカメラのアドレスを受け取り使用する。
	----------------------------------------
	引数1：const CCamera * pCamera：カメラのポインタ
	----------------------------------------
	戻値：なし
	======================================== */
void CPause::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
	ポーズ判定関数
	----------------------------------------
	内容：ポーズ中かどうかを返す
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
bool CPause::IsPause() const
{
	// =============== 提供 ===================
	return (m_ucFlag & E_FLAG_PAUSEMODE);	//ポーズモードフラグが立っているか
}

/* ========================================
	起動関数
	----------------------------------------
	内容：ポーズモードを起動する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CPause::Boot()
{
	// =============== フラグ操作 ===================
	UpFlag(E_FLAG_PAUSEMODE);	//ポーズ開始
}

/* ========================================
	メンバー初期化関数
	----------------------------------------
	内容：メンバーのオブジェクトを動的確保・初期化する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CPause::InitObjects()
{
	// =============== 変数宣言 ===================
	int nCnt = 0;	//ループカウント用

	// =============== 動的確保 ===================
	m_p2dObj = {	//更新順
		new CBgPause(MAP_WAIT.at(E_2D_BACK)),		//背景用
		new CCharPause(MAP_WAIT.at(E_2D_PA)),		//ポの字用
		new CCharPause(MAP_WAIT.at(E_2D_U)),		//ーの字用
		new CCharPause(MAP_WAIT.at(E_2D_SE)),		//ズの字用
		new CPauseObj(MAP_WAIT.at(E_2D_CONTINUE)),	//継続コマンド用
		new CPauseObj(MAP_WAIT.at(E_2D_FINISH)),	//終了コマンド用
	};	//平面ポリゴン
	m_pBgVs = new VertexShader;			//頂点シェーダー
	m_pBgPs = new PixelShader;			//ピクセルシェーダー

	// =============== 初期化 ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); Iterator++)
	{
		if (MAP_POS.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetReach({ MAP_POS.at(nCnt) });	//位置初期化
		}
		if (MAP_SIZE.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetSize({ MAP_SIZE.at(nCnt) });	//サイズ初期化
		}
		if (MAP_TEXTURE.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetTexture(MAP_TEXTURE.at(nCnt).c_str());	//テクスチャ登録
		}

		// =============== カメラ登録 ===================
		(*Iterator)->SetCamera(m_pCamera);	//カメラ登録

		// =============== カウンタ ===================
		nCnt++;	//カウント進行
	}

	// =============== ファイル読み込み ===================
	m_pBGM = CSound::LoadSound(BGM_FILE_PASS.c_str(), true);	//BGMの読み込み
	m_pSEHitHammer = CSound::LoadSound(SE_FILE_PASS.c_str());	//SEの読み込み

	// =============== シェーダー設定 ===================
	m_pBgVs->Load(MAP_SHADER.at(E_2D_BACK)[E_SHADER_TYPE_VERTEX].c_str());	//頂点シェーダー作成
	m_pBgPs->Load(MAP_SHADER.at(E_2D_BACK)[E_SHADER_TYPE_PIXEL].c_str());	//ピクセルシェーダー作成

	// =============== シェーダー登録 ===================
	m_p2dObj[E_2D_BACK]->SetVertexShader(m_pBgVs);	//頂点シェーダー登録
	m_p2dObj[E_2D_BACK]->SetPixelShader(m_pBgPs);	//ピクセルシェーダー登録
}

/* ========================================
	終了関数
	----------------------------------------
	内容：ポーズモードを終了する
	----------------------------------------
	引数1：なし
	----------------------------------------
	戻値：なし
	======================================== */
void CPause::Destroy()
{
	// =============== 変数宣言 ===================
	int nCnt = 0;	//ループカウント用

	// =============== 更新 ===================
	for (std::vector<CPauseObj*>::iterator Iterator = m_p2dObj.begin(); Iterator != m_p2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//mapの配列が存在する添え字
		{
			if (*Iterator)
			{
				(*Iterator)->Destroy();	//平面描画
			}
		}

		// =============== カウンタ ===================
		nCnt++;	//カウント進行
	}
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
void CPause::UpFlag(const unsigned char & ucBitFlag)
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
void CPause::DownFlag(const unsigned char & ucBitFlag)
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
void CPause::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag ^= ucBitFlag;	//フラグ操作
}