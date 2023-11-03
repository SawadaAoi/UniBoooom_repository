#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "Model.h"
#include "Shader.h"
#include "CameraBase.h"


class SceneGame
{
public:
	SceneGame();
	~SceneGame();
	void Update(float tick);
	void Draw();

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;
};

#endif // __SCENE_GAME_H__