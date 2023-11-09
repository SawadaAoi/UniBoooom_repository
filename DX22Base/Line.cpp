/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ��������
   ---------------------------------------
   Line.cpp

   �쐬��	takagi

   �ύX����
   �E���܂� �w�Z�̔z�z��(���Ƃɉ����ό`)
   �E2023/11/05 �t�@�C�������E���ۃN���X���E�R�����g�t�^ takagi

   ======================================== */



// =============== �C���N���[�h ===================
#include "Line.h"	//���g�̃w�b�_
#include "Defines.h"

// =============== �O���[�o���ϐ���` =============
MeshBuffer* CLine::m_pLines;
DirectX::XMFLOAT4X4 CLine::m_WVP[3];	//�e���W�n�ɂ�����s��
Shader* CLine::m_pVS;					//���_�V�F�[�_(���L)
Shader* CLine::m_pPS;					//�s�N�Z���V�F�[�_(���L)
void* CLine::m_pLineVtx;
int CLine::m_lineCnt = 0;



/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::Init()
{
	MakeShader();
	Make();

	for (int i = 0; i < 3; ++i)
		DirectX::XMStoreFloat4x4(&m_WVP[i], DirectX::XMMatrixIdentity());

	// �W�I���g���p�J����������
	DirectX::XMFLOAT4X4 mat[2];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		)));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(60.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f)
	));
	SetView(mat[0]);
	SetProjection(mat[1]);
}

/* ========================================
   �֐��F�R�s�[�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����FCLine & Obj�F�R�s�[��
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CLine::CLine(CLine & Obj)
{
}

/* ========================================
   �֐��F�f�X�g���N�^
   ----------------------------------------
   ���e�F�j�����ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CLine::~CLine()
{
}

/* ========================================
   �֐��F�V�F�[�_�쐬�֐�
   ----------------------------------------
   ���e�F�V�F�[�_������ēǂݍ���
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::MakeShader()
{
	// =============== �쐬 ===============
	MakeVS();	//���_�V�F�[�_�쐬
	MakePS();	//�s�N�Z���V�F�[�_�쐬
}

/* ========================================
   �֐��F�I���֐�
   ----------------------------------------
   ���e�F�I������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::Uninit()
{
	// =============== �I�� ===============
	SAFE_DELETE_ARRAY(m_pLineVtx);
	SAFE_DELETE(m_pPS);
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pLines);
}

/* ========================================
   �֐��F���[���h�s��o�^�֐�
   ----------------------------------------
   ���e�F���[���h�s����󂯎��A�i�[����
   ----------------------------------------
   �����F���[���h�s��(XMFLOAT4X4)
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::SetWorld(DirectX::XMFLOAT4X4 World)
{
	// =============== ��� ===============
	m_WVP[E_MATRIX_WORLD] = World;	//���[���h�s����
}

/* ========================================
   �֐��F�r���[�s��o�^�֐�
   ----------------------------------------
   ���e�F�r���[�s����󂯎��A�i�[����
   ----------------------------------------
   �����F�r���[�s��(XMFLOAT4X4)
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::SetView(DirectX::XMFLOAT4X4 View)
{
	// =============== ��� ===============
	m_WVP[E_MATRIX_VIEW] = View;	//�r���[�s����
}

/* ========================================
   �֐��F�v���W�F�N�V�����s��o�^�֐�
   ----------------------------------------
   ���e�F�v���W�F�N�V�����s����󂯎��A�i�[����
   ----------------------------------------
   �����F�v���W�F�N�V�����s��(XMFLOAT4X4)
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::SetProjection(DirectX::XMFLOAT4X4 Proj)
{
	// =============== ��� ===============
	m_WVP[E_MATRIX_PROJECTION] = Proj;	//�v���W�F�N�V�����s����
}


void CLine::Add(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, DirectX::XMFLOAT4 color)
{
	if (m_lineCnt < MAX_LINE_NUM)
	{
		LineVertex* pVtx = reinterpret_cast<LineVertex*>(m_pLineVtx);
		pVtx[m_lineCnt * 2 + 0] = { start.x, start.y, start.z, color.x, color.y, color.z, color.w };
		pVtx[m_lineCnt * 2 + 1] = { end.x, end.y, end.z, color.x , color.y, color.z, color.w
		};
		++m_lineCnt;
	}
}

/* ========================================
	�`�揈���֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	�����F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CLine::Draw()
{
	// =============== ���� ===============
	//if (m_pLines == nullptr)	//�k���`�F�b�N
	//{
	//	// =============== �I�� ===============
	//	return;	//�����I��
	//}

	// =============== �`�� ===============
	m_pVS->WriteBuffer(0, m_WVP);	//��������
	m_pVS->Bind();					//���_�V�F�[�_�g�p
	m_pPS->Bind();					//�s�N�Z���V�F�[�_�g�p
	m_pLines->Write(m_pLineVtx);	//��������
	m_pLines->Draw(m_lineCnt * 2);	//�����̕`��
	m_lineCnt = 0;					//���`�搔0
}

/* ========================================
   �֐��F���_�V�F�[�_�쐬�֐�
   ----------------------------------------
   ���e�F���_�V�F�[�_������ēǂݍ���
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::MakeVS()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float4 color : COLOR0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.color = vin.color;
	return vout;
})EOT";
	
	m_pVS = new VertexShader();
	m_pVS->Compile(VSCode);
}

/* ========================================
   �֐��F�s�N�Z���V�F�[�_�쐬�֐�
   ----------------------------------------
   ���e�F�s�N�Z���V�F�[�_������ēǂݍ���
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CLine::MakePS()
{

	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return pin.color;
})EOT";

	m_pPS = new PixelShader();
	m_pPS->Compile(PSCode);
}

void CLine::Make()
{
	m_pLineVtx = new LineVertex[MAX_LINE_NUM * 2];
	m_lineCnt = 0;
	MeshBuffer::Description desc = {};
	desc.pVtx = m_pLineVtx;
	desc.vtxCount = MAX_LINE_NUM * 2;
	desc.vtxSize = sizeof(LineVertex);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	desc.isWrite = true;
	m_pLines = new MeshBuffer(desc);
}