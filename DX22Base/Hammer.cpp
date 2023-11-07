#include "hammer.h"
#include "Sphere.h"
CHammer::CHammer()
{
	m_hammerPosition = { 0.0f,0.0f,0.0f };
	m_stateangle = 0.0f;
	m_nowangle = 1.5f;
	m_anglepuls = 0.02f;
	m_bHammer = false;
	m_CHammer = new CSphere();
}

CHammer::~CHammer()
{
	if (m_CHammer != nullptr)
	{
		delete m_CHammer;
		m_CHammer = nullptr;
	}
}

void CHammer::Update(TTriType<float> pPos, float angle)
{
	m_bHammer = true;
	m_stateangle = angle;//-2.5f ;	//~‚èŽn‚ß‚ÌŠp“x	

	float angularSpeed = 0.1f;
	m_nowangle -= angularSpeed;
	float radius = 1.0f;			//ƒvƒŒƒCƒ„[‚ÌŽü‚è‚ð‚Ü‚í‚é‚Æ‚«‚Ì”¼Œa
	float azimuth = m_stateangle + m_nowangle; // •ûˆÊŠpiŠp“xj
	float inclination = 1.0f; // ‹ÂŠp
	azimuth -= inclination;
	// ‹…–ÊÀ•W‚©‚ç’¼ŒðÀ•WŒn‚Ö‚Ì•ÏŠ·
	m_hammerPosition.x = pPos.x + radius * sin(azimuth);

	m_hammerPosition.y = pPos.y + radius * cos(inclination);
	m_hammerPosition.z = pPos.z + radius * cos(azimuth);

	m_T = DirectX::XMMatrixTranslation(m_hammerPosition.x, m_hammerPosition.y, m_hammerPosition.z);


	DirectX::XMMATRIX mat = m_T;
	mat = DirectX::XMMatrixTranspose(mat);
	DirectX::XMFLOAT4X4 fMat;	//s—ñ‚ÌŠi”[æ
	DirectX::XMStoreFloat4x4(&fMat, mat);
	m_CHammer->SetWorld(fMat);

	if (m_nowangle <= 0.0f)
	{
		m_bHammer = false;
		m_nowangle = 1.5f;
	}

}

void CHammer::Draw()
{
	m_CHammer->Draw();
}

bool CHammer::Gethammer()
{
	return m_bHammer;
}
