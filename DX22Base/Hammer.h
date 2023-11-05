#ifndef __HAMMER_H__
#define __HAMMER_H__

#include "Shader.h"
#include"TriType.h"
#include <DirectXMath.h>


class CHammer
{
public:
	CHammer();
	~CHammer();

	void Update(TTriType<float> pPos, float angle);
	void Draw();
private:
	DirectX::XMMATRIX T;
	DirectX::XMMATRIX S;
	TTriType<float> hammerPosition;
	float m_nowangle;	//ç°ÇÃäpìx
	float m_anglepuls;
	float m_stateangle;	//
};





#endif // !__HAMMER_H__

