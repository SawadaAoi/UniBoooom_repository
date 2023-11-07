#ifndef __HAMMER_H__
#define __HAMMER_H__

#include "Shader.h"
#include"TriType.h"
#include "Geometry.h"
#include <DirectXMath.h>


class CHammer
{
public:
	CHammer();
	~CHammer();

	void Update(TTriType<float> pPos, float angle);
	void Draw();
	bool Gethammer();
private:
	DirectX::XMMATRIX m_T;
	DirectX::XMMATRIX m_S;
	TTriType<float> m_hammerPosition;
	float m_nowangle;	//ç°ÇÃäpìx
	float m_anglepuls;	//
	float m_stateangle;	//
	bool m_bHammer;
	CGeometry* m_CHammer;
};





#endif // !__HAMMER_H__

