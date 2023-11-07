#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "Box.h"




SceneGame::SceneGame()
{
	m_pPlayer = new CPlayer();

	m_pCamera = new CameraDebug() ;

	// �X���C���}�l�[�W���[����
	g_pSlimeMng = new CSlimeManager();
}

SceneGame::~SceneGame()
{
	// �X���C���}�l�[�W���[�폜
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

	// �X���C���}�l�[�W���[�X�V
	g_pSlimeMng->Update();

	g_pExplodeMng->Update();
}

void SceneGame::Draw()
{
	
	
	// �X���C���}�l�[�W���[�`��
	g_pSlimeMng->Draw();
	
	//�����}�l�[�W���[�`��
	g_pExplodeMng->Draw();
	
}
