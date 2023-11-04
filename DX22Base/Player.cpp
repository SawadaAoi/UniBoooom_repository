#include"Player.h"
#include "Geometory.h"
//#include <DirectXMath.h>
#include "Input.h"

CHammer* g_phammer;
#define XM_PI (3.141593f)
CPlayer::CPlayer()
{
	T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
	Ry = DirectX::XMMatrixRotationY(0.0f);
	//for (int i = 0; i < 3; i++) point[i] = 0.0f;
	playerPosition = { 0.0f,0.0f,0.0f };
	playerForward = { 0.0f,0.0f,1.0f };
	playerRotation = 0.0f;
	g_phammer = new CHammer();
	m_hammer = false;

}

CPlayer::~CPlayer()
{
	//delete[] point;
	//point = nullptr;
}

void CPlayer::Update()
{
	if (IsKeyPress('W'))
	{
		playerPosition.z += 0.1f;	//player‚ðZ•ûŒü‚ÉˆÚ“®
		playerForward.z = 1.0f;
		playerForward.x = 0.0f;
		if (IsKeyPress('A'))
		{
			playerPosition.x -= 0.1f;
			playerForward.x = -1.0f;
		}
		else if (IsKeyPress('D'))
		{
			playerPosition.x += 0.1f;
			playerForward.x = 1.0f;
		}
	}
	else if (IsKeyPress('S'))
	{
		playerPosition.z -= 0.1f;
		playerForward.z = -1.0f;
		playerForward.x = 0.0f;
		if (IsKeyPress('A'))
		{
			playerPosition.x -= 0.1f;
			playerForward.x = -1.0f;
		}
		else if (IsKeyPress('D'))
		{
			playerPosition.x += 0.1f;
			playerForward.x = 1.0f;
		}
	}
	else if (IsKeyPress('D'))
	{
		playerPosition.x += 0.1f;
		playerForward.x = 1.0f;
		playerForward.z = 0.0f;
	}
	else if (IsKeyPress('A'))
	{
		playerPosition.x -= 0.1f;
		playerForward.x = -1.0f;
		playerForward.z = 0.0f;
	}

	//is•ûŒü‚©‚çplayer‚ÌŒü‚«‚ðŒˆ‚ß‚é
	if (playerForward.x == 0.0f) {
		if (playerForward.z > 0.0f) {
			playerRotation = 0.0f; // ‘O•ûŒü
		}
		else {
			playerRotation = XM_PI; // Œã•ûŒü
		}
	}
	else {
		playerRotation = atan(playerForward.x / playerForward.z);
		if (playerForward.z < 0.0f) {
			playerRotation += XM_PI; // Œã•ûŒü•â³
		}
	}
	T = DirectX::XMMatrixTranslation(playerPosition.x, playerPosition.y, playerPosition.z);
	DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(playerRotation);
	DirectX::XMMATRIX mat = Ry * T;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;	//s—ñ‚ÌŠi”[æ
	DirectX::XMStoreFloat4x4(&fMat, mat);
	//Geometory::SetWorldPlayer(fMat);

	if (IsKeyTrigger(VK_SPACE))
	{
		g_phammer->Update(playerPosition, playerRotation);
		m_hammer = true;
	}
}

void CPlayer::Draw()
{
	//Geometory::DrawPlayerBox();
	if (m_hammer)
	{
		g_phammer->Draw();
	}
}
