/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	プログラムのメイン部分
	------------------------------------
	Main.cpp
	------------------------------------
	作成者 

	変更履歴
   ・↓まで 学校の配布物(授業に沿い変形)・Geometryに合わせた改造
	・2023/11/09 カメラの様々動作チェック。 takagi
	・2023/11/17 シーン管理を実装 takagi
	・2023/11/18 sound.hをインクルードしてsoundの初期化と終了を追加 yamashita
	・2023/11/21 3dアニメーション用配布物適用

========================================== */

// =============== インクルード ===================
#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometry.h"
#include "Sprite.h"
#include "Input.h"
#if USE_SCENE_MANAGER
#include "SceneManager.h"
#else
#include "SceneGame.h"
#endif
#include "Defines.h"
#include <time.h>
#include "Sound.h"
#include "ShaderList.h"	//モデルアニメーション用
#include "LibEffekseer.h"

// =============== グローバル変数定義 =============
#if USE_SCENE_MANAGER
CSceneManager* g_pSceneMng;
#else
SceneGame* g_pGame;
#endif

/* ========================================
	初期化処理関数
	-------------------------------------
	内容：初期化処理
	-------------------------------------
	引数1：(hWnd)	//TODO：分からない
	-------------------------------------
	引数2：画面サイズ横幅(width)
	-------------------------------------
	引数3：画面サイズ縦幅(height)
	-------------------------------------
	戻値：無し
=========================================== */
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX初期化
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	CSound::InitSound();
	LibEffekseer::Init(GetDevice(), GetContext());

	CGeometry::MakeShader();			//シェーダ作成
	srand((unsigned int)time(NULL));	// 乱数パターン設定

	Sprite::Init();
	InitInput();

	ShaderList::Init();
	ShaderList::Uninit();

	// シーン作成
#if USE_SCENE_MANAGER
	g_pSceneMng = new CSceneManager();
#else
	g_pGame = new SceneGame();
#endif

	return hr;
}

/* ========================================
	終了処理関数
	-------------------------------------
	内容：終了処理
	-------------------------------------
	引数：無し
	-------------------------------------
	戻値：無し
=========================================== */
void Uninit()
{
#if USE_SCENE_MANAGER
	if (g_pSceneMng)	//ヌルチェック
	{
		delete g_pSceneMng;
		g_pSceneMng = nullptr;
	}
#else
	delete g_pGame;
#endif
	CGeometry::Uninit();
	UninitInput();
	Sprite::Uninit();
	LibEffekseer::Uninit();
	CSound::UninitSound();
	UninitDirectX();
}

/* ========================================
	更新処理関数
	-------------------------------------
	内容：更新処理
	-------------------------------------
	引数：ティック数(tick)
	-------------------------------------
	戻値：無し
=========================================== */
void Update(float tick)
{
	UpdateInput();
#if USE_SCENE_MANAGER
	if (g_pSceneMng)	//ヌルチェック
	{
		g_pSceneMng->Update();
	}
#else
	g_pGame->Update(tick);
#endif
}

/* ========================================
	描画処理関数
	-------------------------------------
	内容：描画処理
	-------------------------------------
	引数：無し
	-------------------------------------
	戻値：無し
=========================================== */
void Draw()
{
	BeginDrawDirectX();
#if USE_SCENE_MANAGER
	if (g_pSceneMng)	//ヌルチェック
	{
		g_pSceneMng->Draw();
	}
#else
	g_pGame->Draw();
#endif
	LibEffekseer::Draw();
	EndDrawDirectX();
}

#if USE_SCENE_MANAGER
/* ========================================
	終了検査関数
	-------------------------------------
	内容：このアプリを終了するかどうか判定する
	-------------------------------------
	引数：無し
	-------------------------------------
	戻値：終了判定
=========================================== */
bool IsFin()
{
	if (g_pSceneMng)	//ヌルチェック
	{
		return g_pSceneMng->IsFin();
	}
	else
	{
		return false;	//継続
	}
}
#endif

// EOF