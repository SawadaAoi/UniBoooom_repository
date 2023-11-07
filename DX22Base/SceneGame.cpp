#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "Box.h"




SceneGame::SceneGame()
{
	m_pPlayer = new CPlayer();

	m_pCamera = new CameraDebug() ;

	// スライムマネージャー生成
	g_pSlimeMng = new CSlimeManager();
}

SceneGame::~SceneGame()
{
	// スライムマネージャー削除
	if (g_pSlimeMng)
	{
		delete g_pSlimeMng;
		g_pSlimeMng = nullptr;
	}
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

}

 
void SceneGame::Update(float tick)
{
	m_pPlayer->Update();

	m_pCamera->Update();

	// スライムマネージャー更新
	g_pSlimeMng->Update();

	g_pExplodeMng->Update();
}

void SceneGame::Draw()
{
	
	
	// スライムマネージャー描画
	g_pSlimeMng->Draw();
	
	//爆発マネージャー描画
	g_pExplodeMng->Draw();
	
}
