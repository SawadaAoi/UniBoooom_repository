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
	・2023/11/09 カメラの様々動作チェック。 ��木駿輔

========================================== */

// =============== インクルード ===================
#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometry.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneGame.h"
#include "Defines.h"
#include <time.h>


// =============== グローバル変数定義 =============
SceneGame* g_pGame;

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

	CGeometry::MakeShader();			//シェーダ作成
	srand((unsigned int)time(NULL));	// 乱数パターン設定

	Sprite::Init();
	InitInput();

	// シーン作成
	g_pGame = new SceneGame(GetDirectWrite());

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
	delete g_pGame;
	CGeometry::Uninit();
	UninitInput();
	Sprite::Uninit();
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
	g_pGame->Update(tick);
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

	g_pGame->Draw();
	EndDrawDirectX();
}

// EOF