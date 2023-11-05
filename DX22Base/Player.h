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
	TTriType<float> playerPosition;	//�v���C���[�̈ʒu
	TTriType<float> playerForward; // �v���C���[�̏����i�s����
	float playerRotation; // �v���C���[�̉�]�p�x
	CHammer* m_pHammer;
	bool m_hammer;
};


#endif // !__PLAYER_H__

