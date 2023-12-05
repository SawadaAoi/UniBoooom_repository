/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ画面実装
	---------------------------------------
	Pose.cpp

	作成者	takagi

	変更履歴
	・2023/12/01 制作 takagi
	・2023/12/04 続き takagi
	・2023/12/05 続き takagi

========================================== */

// =============== インクルード ===================
#include "Pose.h"		//自身のヘッダ
#include <map>			//関係性コンテナ
#include <array>		//配列
#include "CameraDef.h"	//疑似カメラ
#include "Input.h"		//キー入力

// =============== 列挙型定義 ===================
enum E_2D
{
	E_2D_BACK,		//背景
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
const float COMMAND_WIDTH = 320.0f;		//コマンド縦幅
const float COMMAND_HEIGHT = 70.0f;		//コマンド横幅
#endif // !GAME_PARAMETER


const std::string BGM_FILE_PASS("Assets/Sound/BGM/BGM_maou.mp3");
const std::string SE_FILE_PASS("Assets/Sound/SE/Smash.mp3");
const std::map<int, std::string> MAP_TEXTURE = {
	{E_2D_BACK, "Assets/Texture/PoseBg.png"},			//背景
	{E_2D_CONTINUE, "Assets/Texture/pre_title.png"},	//コマンドA
	{E_2D_FINISH, "Assets/Texture/pre_result.png"},	//コマンドB
};	//ポリゴンとテクスチャの対応表
const std::map<int, TPos3d<float>> MAP_POS = {	//更新順
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f}},					//背景
	{E_2D_CONTINUE, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f + COMMAND_SPACE_HALF, 0.0f}},	//コマンドA
	{E_2D_FINISH, {static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f - COMMAND_SPACE_HALF, 0.0f}},	//コマンドB
};	//ポリゴンと初期座標の対応表
const std::map<int, TPos3d<float>> MAP_SIZE = {	//更新順
	{E_2D_BACK, {static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f}},	//背景
	{E_2D_CONTINUE, {COMMAND_WIDTH, COMMAND_HEIGHT, 0.0f}},													//コマンドA
	{E_2D_FINISH, {COMMAND_WIDTH, COMMAND_HEIGHT, 0.0f}},													//コマンドB
};	//ポリゴンと初期サイズの対応表
const std::map<int, std::array<std::string, E_SHADER_TYPE_MAX>> MAP_SHADER = {
	{E_2D_BACK, {"Assets/Shader/VsPose.cso", "Assets/Shader/PsPose.cso"}},	//背景
	//TODO:この先オブジェクトを追加したときに読み込むシェーダーがずれたりする恐れがあるので通常時用のシェーダーも作って読み込ませる
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
CPose::CPose(const CCamera* pCamera)
	:m_ucFlag(0x00)			//フラグ
	,m_pBgPs(nullptr)		//背景用ピクセルシェーダ
	,m_pBgVs(nullptr)		//背景用頂点シェーダ
	//,m_pCamera(nullptr)		//カメラ管理
	,m_pCameraDef(nullptr)	//疑似カメラ
{
	// =============== 変数宣言 ===================
	int nCnt = 0;	//ループカウント用

	// =============== 動的確保 ===================
	m_2dObj = {	//更新順
		new C2dPolygon(),				//背景用
		new C2dPolygon(),				//コマンドA用
		new C2dPolygon(),				//コマンドB用
		new C2dPolygon(),				//コマンドC用
	};	//平面ポリゴン
	m_pBgVs = new VertexShader;			//頂点シェーダー
	m_pBgPs = new PixelShader;			//ピクセルシェーダー
	m_pCameraDef = new CCameraDef();	//疑似カメラ
	
	// =============== 初期化 ===================
	SetCamera(pCamera);	//カメラ初期化
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(); Iterator != m_2dObj.end(); Iterator++)
	{
		if (MAP_POS.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetPos({ MAP_POS.at(nCnt) });	//位置初期化
		}
		if (MAP_SIZE.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetSize({ MAP_SIZE.at(nCnt) });	//サイズ初期化
		}
		if (MAP_TEXTURE.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetTexture(MAP_TEXTURE.at(nCnt).c_str());	//テクスチャ登録
		}

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
	m_2dObj[E_2D_BACK]->SetVertexShader(m_pBgVs);	//頂点シェーダー登録
	m_2dObj[E_2D_BACK]->SetPixelShader(m_pBgPs);	//ピクセルシェーダー登録
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
CPose::~CPose()
{	
	// =============== 終了 ===================
	SAFE_DELETE(m_pCameraDef);				//疑似カメラ削除
	SAFE_DELETE(m_pBgPs);					//ピクセルシェーダー削除
	SAFE_DELETE(m_pBgVs);					//頂点シェーダー削除
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.end(); Iterator != m_2dObj.begin();)
	{
		delete (*(--Iterator));				//メモリ解放
		Iterator = m_2dObj.erase(Iterator);	//イテレータ削除・移動
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
void CPose::Update()
{
	// =============== キー入力 ===================
	// =============== 決定 ===================
	// =============== カーソル移動 ===================

	// =============== 選択確定 ===================
	if (m_ucFlag & E_FLAG_DECIDE_COMMAND)	//コマンド決定時
	{
		// =============== 選択状態判定 ===================
		if (m_ucFlag & E_FLAG_COMMAND_CONTINUE)	//継続
		{
			// =============== フラグ操作 ===================
			DownFlag(E_FLAG_POSEMODE | E_FLAG_COMMAND_CONTINUE);	//ポーズを中断し、ゲームを再開する
		}
		if (m_ucFlag & E_FLAG_COMMAND_FINISH)	//継続
		{
			// =============== フラグ操作 ===================
			DownFlag(E_FLAG_POSEMODE | E_FLAG_COMMAND_FINISH);	//ポーズを中断する
			UpFlag(E_FLAG_CALL_FINISH);							//ゲームの終了申請
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
void CPose::Draw()
{
	// =============== モード検査 ===================
	if (!(m_ucFlag & E_FLAG_POSEMODE))	//ポーズモードのフラグが立っていない
	{
		// =============== 終了 ==================
		return;	//処理中断
	}

	// =============== 変数宣言 ===================
	int nCnt = 0;	//ループカウント用

	// =============== 描画 ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(); Iterator != m_2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->Draw();	//平面描画
		}

		// =============== カウンタ ===================
		nCnt++;	//カウント進行
	}
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
bool CPose::IsFin() const
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
void CPose::SetCamera(const CCamera * pCamera)
{
	// =============== 変数宣言 ===================
	int nCnt = 0;				//ループカウント用
	const CCamera* pCameraUse;	//カメラアドレス退避用

	// =============== 初期化 ===================
	if (pCamera)	//ヌルチェック
	{
		pCameraUse = pCamera;		//新規カメラ登録
	}
	else
	{
		pCameraUse = m_pCameraDef;	//カメラ代用
	}
	
	// =============== カメラ登録 ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(); Iterator < m_2dObj.end(); Iterator++)
	{
		if (MAP_TEXTURE.size() > nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetCamera(pCameraUse);	//カメラ登録
		}

		// =============== カウンタ ===================
		nCnt++;	//カウント進行
	}
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
bool CPose::IsPose() const
{
	// =============== 提供 ===================
	return (m_ucFlag & E_FLAG_POSEMODE);	//ポーズモードフラグが立っているか
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
void CPose::Boot()
{
	// =============== フラグ操作 ===================
	UpFlag(E_FLAG_POSEMODE);	//ポーズ開始
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
void CPose::UpFlag(const unsigned char & ucBitFlag)
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
void CPose::DownFlag(const unsigned char & ucBitFlag)
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
void CPose::SetFlag(const unsigned char & ucBitFlag)
{
	// =============== 代入 ===================
	m_ucFlag ^= ucBitFlag;	//フラグ操作
}