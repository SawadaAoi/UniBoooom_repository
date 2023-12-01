/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	ポーズ画面実装
	---------------------------------------
	Pose.cpp

	作成者	takagi

	変更履歴
	・2023/12/01 制作 takagi

========================================== */

// =============== インクルード ===================
#include "Pose.h"	//自身のヘッダ
#include <map>		//関係性コンテナ
#include "DiType.h"	//２つの型

// =============== 列挙型定義 ===================
enum E_2D
{
	E_2D_BACK,		//背景
	E_2D_COMMAND_A,	//コマンドA用
	E_2D_COMMAND_B,	//コマンドA用
	E_2D_COMMAND_C,	//コマンドA用
};	//2Dのオブジェクト

// =============== 定数定義 ===================
const std::string BGM_FILE_PASS("Assets/Sound/BGM/BGM_maou.mp3");
const std::string SE_FILE_PASS("Assets/Sound/SE/Smash.mp3");
const std::map<int, std::string> MAP_TEXTURE = {
	{E_2D_BACK, "Assets/Texture/PoseBg.png"},	//背景
};	//ポリゴンとテクスチャの対応表
const std::map<int, TDiType<std::string>> MAP_SHADER = {
	{E_2D_BACK, {"VsPose.cso", "PsPose.cso"}},	//背景
};	//ポリゴンとシェーダー[頂点, ピクセル]の対応表

/* ========================================
	コンストラクタ
	----------------------------------------
	内容：生成時に行う処理
	----------------------------------------
	引数1：CCamera* pCamera：カメラのポインタ
	----------------------------------------
	戻値：なし
=========================================== */
CPose::CPose(CCamera* pCamera)
	:m_pBgPs(nullptr)	//背景用ピクセルシェーダ
	,m_pBgVs(nullptr)	//背景用頂点シェーダ
{
	// =============== 初期化 ===================
	if (pCamera)	//ヌルチェック
	{
		m_pCamera = pCamera;	//カメラ
	}

	// =============== 動的確保 ===================
	m_2dObj = {	//更新順
		new C2dPolygon(),	//背景用
		new C2dPolygon(),	//コマンドA用
		new C2dPolygon(),	//コマンドB用
		new C2dPolygon(),	//コマンドC用
	};	//平面ポリゴン
	
	// =============== ファイル読み込み ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(), int nCnt = 0; Iterator < m_2dObj.end(); Iterator++, nCnt++)
	{
		if (MAP_TEXTURE.size() < nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->SetTexture(MAP_TEXTURE.at(nCnt).c_str());	//テクスチャ登録
		}
	}
	m_pBGM = CSound::LoadSound(BGM_FILE_PASS.c_str(), true);	//BGMの読み込み
	m_pSEHitHammer = CSound::LoadSound(SE_FILE_PASS.c_str());	//SEの読み込み
	
	// =============== シェーダー設定 ===================
	m_2dObj[E_2D_BACK]->SetVertexShader(MAP_SHADER.at(E_2D_BACK).x.c_str());
	m_2dObj[E_2D_BACK]->SetPixelShader(MAP_SHADER.at(E_2D_BACK).y.c_str());
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
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.end(); Iterator < m_2dObj.begin();)
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
	// =============== 描画 ===================
	for (std::vector<C2dPolygon*>::iterator Iterator = m_2dObj.begin(), int nCnt = 0; Iterator < m_2dObj.end(); Iterator++, nCnt++)
	{
		if (MAP_TEXTURE.size() < nCnt)	//mapの配列が存在する添え字
		{
			(*Iterator)->Draw();	//平面描画
		}
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
	return m_bFinish;	//終了フラグ
}