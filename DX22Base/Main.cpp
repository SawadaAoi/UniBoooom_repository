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
	・2023/11/09 カメラの様々動作チェック。 髙木駿輔

========================================== */

#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometry.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneGame.h"
#include "Defines.h"


//--- グローバル変数
SceneGame* g_pGame;	//

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX初期化
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	CGeometry::MakeShader();	//シェーダ作成

	Sprite::Init();
	InitInput();

	// シーン作成
	g_pGame = new SceneGame();

	return hr;
}

void Uninit()
{
	delete g_pGame;
	CGeometry::Uninit();
	UninitInput();
	Sprite::Uninit();
	UninitDirectX();
}

void Update(float tick)
{
	UpdateInput();
	g_pGame->Update(tick);
}

void Draw()
{
	BeginDrawDirectX();



	g_pGame->Draw();
	EndDrawDirectX();
}

// EOF