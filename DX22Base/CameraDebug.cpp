#include "CameraDebug.h"

CameraDebug::CameraDebug()
{

}

CameraDebug::~CameraDebug()
{

}

void CameraDebug::Update()
{
	// ↑↓→←Shift、Ctrlでカメラの注視点を動かす
	if (IsKeyPress(VK_UP))
	{
		m_look.z += 0.1f;
	}
	if (IsKeyPress(VK_DOWN))
	{
		m_look.z -= 0.1f;
	}
	if (IsKeyPress(VK_RIGHT))
	{
		m_look.x += 0.1f;
	}
	if (IsKeyPress(VK_LEFT))
	{
		m_look.x += 0.1f;
	}

	// W,A,S,D,Q,Eでカメラの位置を動かす
	if (IsKeyPress('W'))
	{
		m_pos.z += 0.1f;
	}
	if (IsKeyPress('S'))
	{
		m_pos.z -= 0.1f;
	}
	if (IsKeyPress('A'))
	{
		m_pos.x -= 0.1f;
	}
	if (IsKeyPress('D'))
	{
		m_pos.x += 0.1f;
	}
}