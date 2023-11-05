#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometry.h"
#include "Line.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneGame.h"
#include "Defines.h"

// =============== デバッグモード =======================
#define MODE_COORD_AXIS (true)	//座標軸映すかどうか

//--- グローバル変数
SceneGame* g_pGame;	//

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	// DirectX初期化
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }

	CGeometry::MakeShader();	//シェーダ作成

	CLine::Init();
	Sprite::Init();
	InitInput();

	// シーン作成
	g_pGame = new SceneGame();

	return hr;
}

void Uninit()
{
	delete g_pGame;
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

	// 軸線の表示
#if MODE_COORD_AXIS
	// グリッド
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
	}
	// 軸
	CLine::Add(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(size,0,0), DirectX::XMFLOAT4(1,0,0,1));
	CLine::Add(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,size,0), DirectX::XMFLOAT4(0,1,0,1));
	CLine::Add(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,0,size), DirectX::XMFLOAT4(0,0,1,1));
	CLine::Add(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(-size,0,0),  DirectX::XMFLOAT4(0,0,0,1));
	CLine::Add(DirectX::XMFLOAT3(0,0,0), DirectX::XMFLOAT3(0,0,-size),  DirectX::XMFLOAT4(0,0,0,1));

	CLine::Draw();
#endif

	g_pGame->Draw();
	EndDrawDirectX();
}

// EOF