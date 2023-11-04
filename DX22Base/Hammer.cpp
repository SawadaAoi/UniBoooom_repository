#include "Hammer.h"
#include "Geometory.h"
CHammer::CHammer()
{
	hammerPosition = { 0.0f,0.0f,0.0f };
	m_stateangle = 0.0f;
	m_nowangle = 0.0f;
	m_anglepuls = 0.02f;
}

CHammer::~CHammer()
{
}

void CHammer::Update(TTriType<float> pPos, float angle)
{
	m_stateangle = angle;
	m_nowangle = angle - 0.2f;//


	T = DirectX::XMMatrixTranslation(hammerPosition.x, hammerPosition.y, hammerPosition.z);
	//DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(hammerPosition);
	//DirectX::XMMATRIX mat = Ry * T;
	DirectX::XMMATRIX mat = T;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;	//çsóÒÇÃäiî[êÊ
	DirectX::XMStoreFloat4x4(&fMat, mat);
	//Geometory::SetWorldHammer(fMat);
}

void CHammer::Draw()
{
	//Geometory::DrawHammerBox();
}

//void CHammer::SetPlayer(CPlayer * player)
//{
//	m_pPlayer = player;
//}
