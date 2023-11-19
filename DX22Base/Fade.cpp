/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�t�F�[�h����
	------------------------------------
	Fade.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/18 ���� takagi

========================================== */

// =============== �f�o�b�O���[�h ===================
#if _DEBUG
#define USE_FADE (true)	//�t�F�[�h���^�]
#endif

// =============== �C���N���[�h ===================
#include "Fade.h"	//���g�̃w�b�_
#if USE_FADE
#include "Input.h"	//�L�[���͗p
#endif

// =============== �萔��` =====================
const std::string TEX_PASS = "Assets/Fade.png";	//�e�N�X�`���̃p�X��


// =============== �O���[�o���ϐ��錾 =====================
int CFade::ms_nCntFade;				//���g�̐�����
VertexShader* CFade::ms_pVs;		//���_�V�F�[�_�[
PixelShader* CFade::ms_pPs;			//�s�N�Z���V�F�[�_�[
const void* CFade::ms_pVtx;			//���_���
unsigned int CFade::ms_unVtxSize;	//���_�T�C�Y
unsigned int CFade::ms_unVtxCount;	//���_��
const void* CFade::ms_pIdx;			//���_�̃C���f�b�N�X
unsigned int CFade::ms_unIdxSize;	//�C���f�b�N�X�T�C�Y
unsigned int CFade::ms_unIdxCount;	//�C���f�b�N�X��
ID3D11Buffer* CFade::ms_pVtxBuffer;	//���_�o�b�t�@
ID3D11Buffer* CFade::ms_pIdxBuffer;	//�C���f�b�N�X�o�b�t�@ 

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CFade::CFade(const CCamera* pCamera)
	:m_pTexture(nullptr)	//
	, m_pCamera(pCamera)	//
	, m_nFrame(0)
	, m_bFadeOut(false)
	, m_bFadeIn(false)
	, m_bStop(false)
{
	if (0 == ms_nCntFade)	//���݁A���ɂ��̃N���X���쐬����Ă��Ȃ�
	{
		MakeShader();
		Make();
	}
	param[0] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	param[1] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	param[2] = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&matrix[1], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&matrix[2], DirectX::XMMatrixIdentity());

	ms_nCntFade++;
}

/* ========================================
	�R�s�[�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst CFade & Obj�F�R�s�[���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CFade::CFade(const CFade & Obj)
{
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CFade::~CFade()
{
	ms_nCntFade--;
	SAFE_DELETE(ms_pPs);
}

void CFade::Update()
{
}

void CFade::Draw()
{
	if (IsKeyTrigger('7'))
	{
		m_bFadeOut = true;
		m_nFrame = 150;
	}

	if (m_nFrame <= 0 && m_bFadeOut)
	{
		m_bFadeOut = false;
		m_nFrame = 60;
		m_bStop = true;
	}
	if (m_nFrame <= 0 && m_bFadeIn)
	{
		m_bFadeIn = false;
	}

	if (m_nFrame <= 0 && m_bStop)
	{
		m_bStop = false;
		m_nFrame = 150;
		m_bFadeIn = true;
	}

	if (!m_pTexture || !m_bFadeOut && !m_bFadeIn && !m_bStop)
	{
		return;
	}

	float rad;
	rad = 3.1f * 3.0f / 180.0f * (float)m_nFrame;

	if (m_bFadeIn)
	{
		rad *= -1.0f;
	}

	float size;
	int nTemp = 150 - m_nFrame;
	//size = A_3 * (float)(m_nFrame * m_nFrame * m_nFrame) + B_3 * (float)(m_nFrame * m_nFrame) + C_3 * (float)(m_nFrame) + D_3;
	if (nTemp <= 50)
	{
		if (m_bFadeIn)
		{
			size = 1000.0f - (1000.0f - 15.0f) * (float)nTemp / 50.0f;
		}
		if (m_bFadeOut)
		{
			size = 0.0f + (100.0f - 0.0f) * (float)nTemp / 50.0f;
		}
	}
	else
	{
		if (nTemp <= 100)
		{
			if (m_bFadeIn)
			{
				size = 30.0f + (100.0f - 30.0f) * (float)(nTemp - 50) / 50.0f;
			}
			if (m_bFadeOut)
			{
				size = 100.0f - (100.0f - 15.0f) * (float)(nTemp - 50) / 50.0f;
			}
		}
		else
		{
			if (nTemp < 150)
			{
				if (m_bFadeIn)
				{
					size = 100.0f - (100.0f - 0.0f) * (float)(nTemp - 100) / 50.0f;
				}
				if (m_bFadeOut)
				{
					size = 15.0f + (1000.0f - 15.0f) * (float)(nTemp - 100) / 50.0f;
				}
			}
			else
			{
				if (nTemp < 150)
				{
					size = 1000.0f;
				}
			}
		}
		
	}
	m_nFrame--;

	if (m_bStop)
	{
		size = 500.0f;
	}

	//size *= 1.06f;
	//param[1].x = -size / 2.0f;
	//param[1].y = -size / 2.0f;
	param[1].z = size;
	param[1].w = size;

	
	DirectX::XMMATRIX world =
		DirectX::XMMatrixScaling(80.0f, 80.0f, 0.0f) * DirectX::XMMatrixRotationZ(rad) * DirectX::XMMatrixTranslation(640.0f, 360.0f, 0.0f);

	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(world));
	matrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);

	//ms_pVs->WriteBuffer();
	ms_pVs->WriteBuffer(0, matrix);
	ms_pVs->WriteBuffer(1, param);
	ms_pVs->Bind();
	ms_pPs->SetTexture(0, m_pTexture);
	ms_pPs->Bind();

	ID3D11DeviceContext* pContext = GetContext();
		UINT offset = 0;

	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pContext->IASetVertexBuffers(0, 1, &ms_pVtxBuffer, &ms_unVtxSize, &offset);

	// �`��
	if (ms_unIdxCount > 0)
	{
		DXGI_FORMAT format;
		switch (ms_unIdxSize)
		{
		case 4: format = DXGI_FORMAT_R32_UINT; break;
		case 2: format = DXGI_FORMAT_R16_UINT; break;
		}
		pContext->IASetIndexBuffer(ms_pIdxBuffer, format, 0);
		pContext->DrawIndexed(ms_unIdxCount, 0, 0);
	}
	else
	{
		// ���_�o�b�t�@�݂̂ŕ`��
		pContext->Draw(ms_unVtxCount, 0);
	}

}

/* ========================================
	�V�F�[�_�[�쐬�֐�
	-------------------------------------
	���e�F�V�F�[�_�[���R���p�C���E�o�^
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::MakeShader()
{
	// =============== �R�[�h�L�q ===================
//	const char* pcVs = R"EOT(
//struct VS_IN {
//	float3 pos : POSITION0;
//	float3 normal : NORMAL0;
//	float2 uv : TEXCOORD0;
//};
//struct VS_OUT {
//	float4 pos : SV_POSITION;
//	float3 normal : NORMAL0;
//	float2 uv : TEXCOORD0;
//};
//cbuffer Matrix : register(b0) {
//	float4x4 world;
//	float4x4 view;
//	float4x4 proj;
//};
//VS_OUT main(VS_IN vin) {
//	VS_OUT vout;
//	//vout.pos = float4(vin.pos, 1.0f);
//	//vout.pos.z += 0.5f;
//	//vout.pos.y -= 0.8f;
//	vout.pos = mul(vout.pos, world);
//	vout.pos = mul(vout.pos, view);
//	vout.pos = mul(vout.pos, proj);
//	vout.normal = vin.normal;
//	vout.uv = vin.uv;
//	return vout;
//})EOT";
//	const char* pcPs = R"EOT(
//struct PS_IN {
//	float4 pos : SV_POSITION;
//	float3 normal : NORMAL0;
//	float2 uv : TEXCOORD0;
//};
//Texture2D tex : register(t0);
//SamplerState samp : register(s0);
//float4 main(PS_IN pin) : SV_TARGET
//{
//	return tex.Sample(samp, pin.uv);
//})EOT";

	ms_pVs = new VertexShader();
	ms_pVs->Load("Assets/Shader/VsFade.cso");
	ms_pPs = new PixelShader();
	ms_pPs->Load("Assets/Shader/PsFade.cso");
}

void CFade::Make()
{
	Vertex aVtx[] = {
		{{-10.5f, 10.5f, -0.0f}, {0.0f, 0.0f}},
		{{ 10.5f, 10.5f, -0.0f}, {1.0f, 0.0f}},
		{{-10.5f,-10.5f, -0.0f}, {0.0f, 1.0f}},
		{{ 10.5f,-10.5f, -0.0f}, {1.0f, 1.0f}},
	};	//���_���
	int aIdx[] = {
		0, 1, 2, 2, 1, 3
	};


	ms_pVtx = aVtx;					//���_���
	ms_unVtxSize = sizeof(Vertex);	//���_�^�T�C�Y
	ms_unVtxCount = _countof(aVtx);	//���_��
//	bool isWrite;				
	ms_pIdx = aIdx;
	ms_unIdxSize = sizeof(int);
	ms_unIdxCount = _countof(aIdx);


	CreateVtxBuffer();
	CreateIdxBuffer();
}

void CFade::CreateVtxBuffer()
{
	//���o�b�t�@���ݒ�
	D3D11_BUFFER_DESC BufDesc;
	ZeroMemory(&BufDesc, sizeof(BufDesc));	//���g��S��0�ŏ�����
	BufDesc.ByteWidth = ms_unVtxSize * ms_unVtxCount;	//�o�b�t�@�̑傫��
	BufDesc.Usage = D3D11_USAGE_DEFAULT;			//��������ł̊Ǘ����@
	BufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//GPU��ł̗��p���@

	//���o�b�t�@�����f�[�^�ݒ�
	D3D11_SUBRESOURCE_DATA SubResource;
	ZeroMemory(&SubResource, sizeof(SubResource));
	SubResource.pSysMem = ms_pVtx;				//�o�b�t�@�ɓ��ꍞ�ރf�[�^

	//�����_�o�b�t�@�̍쐬
	HRESULT hr;
	hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pVtxBuffer);
	if (FAILED(hr))
	{
		ms_pVtxBuffer = nullptr;
	}
}

void CFade::CreateIdxBuffer()
{
	// �C���f�b�N�X�T�C�Y�̊m�F
	switch (ms_unIdxSize)
	{
	default:
		//todo:error
		return;
	case 2:
	case 4:
		break;
	}

	// �o�b�t�@�̏���ݒ�
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = ms_unIdxSize * ms_unIdxCount;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// �o�b�t�@�̏����f�[�^
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = ms_pIdx;

	// �C���f�b�N�X�o�b�t�@����
	ID3D11Device* pDevice = GetDevice();
	pDevice->CreateBuffer(&bufDesc, &subResource, &ms_pIdxBuffer);
}


/* ========================================
	�e�N�X�`���Z�b�^�֐�
	-------------------------------------
	���e�F���������ƂɃe�N�X�`���[�쐬
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CFade::SetTexture()
{
	if (m_pTexture)
	{
		SAFE_DELETE(m_pTexture);
	}
	m_pTexture = new Texture;
	m_pTexture->Create(TEX_PASS.c_str());
}