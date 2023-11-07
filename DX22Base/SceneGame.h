#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Model.h"
#include "Shader.h"
#include "CameraBase.h"
#include "Player.h"
#include "SlimeManager.h"
#include "ExplosionManager.h"


class SceneGame
{
public:
	SceneGame();
	~SceneGame();
	void Update(float tick);
	void Draw();

private:
	CameraBase* m_pCamera;
	CPlayer* m_pPlayer;
	CSlimeManager* g_pSlimeMng;
	CExplosionManager* g_pExplodeMng;
};

#endif // __SCENE_GAME_H__