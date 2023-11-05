#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Shader.h"

#include"Hammer.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void Update();
	void Draw();

private:
	DirectX::XMMATRIX T;
	DirectX::XMMATRIX S;
	DirectX::XMMATRIX Ry;
	TTriType<float> playerPosition;	//プレイヤーの位置
	TTriType<float> playerForward; // プレイヤーの初期進行方向
	float playerRotation; // プレイヤーの回転角度
	CHammer* m_pHammer;
	bool m_hammer;
};


#endif // !__PLAYER_H__

