/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ��Ԃɂ�����`��̒��ۃN���X����
   ---------------------------------------
   Geometry.cpp

   �쐬��	takagi

   �ύX����
   �E���܂� �w�Z�̔z�z��(���Ƃɉ����ό`)
   �E2023/11/05 �t�@�C�������E���ۃN���X���E�R�����g�t�^ takagi
   �E2023/11/10 Uninit�폜(���e�̓f�X�g���N�^�ֈړ�) takagi

   ======================================== */



// =============== �C���N���[�h ===================
#include "Geometry.h"	//���g�̃w�b�_
#include "Defines.h"

// =============== �O���[�o���ϐ���` =============
//MeshBuffer* CGeometry::m_pLines;
Shader* CGeometry::m_pVS;					//���_�V�F�[�_(���L)
Shader* CGeometry::m_pPS;					//�s�N�Z���V�F�[�_(���L)



/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CGeometry::CGeometry()
{
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
   �����FCGeometry & Obj�F�R�s�[��
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CGeometry::CGeometry(CGeometry & Obj)
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
CGeometry::~CGeometry()
{
	// =============== �I�� ===============
	SAFE_DELETE(m_pPS);
	SAFE_DELETE(m_pVS);
	if (m_pObj)	//�k���`�F�b�N
	{
		delete m_pObj;		//���������
		m_pObj = nullptr;	//��A�h���X���
	}
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
void CGeometry::MakeShader()
{
	// =============== �쐬 ===============
	MakeVS();	//���_�V�F�[�_�쐬
	MakePS();	//�s�N�Z���V�F�[�_�쐬
}

/* ========================================
   �֐��F���[���h�s��o�^�֐�
   ----------------------------------------
   ���e�F���[���h�s����󂯎��A�i�[����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CGeometry::SetWorld(DirectX::XMFLOAT4X4 World)
{
	// =============== ��� ===============
	m_WVP[E_MATRIX_WORLD] = World;	//���[���h�s����
}

/* ========================================
   �֐��F�r���[�s��o�^�֐�
   ----------------------------------------
   ���e�F�r���[�s����󂯎��A�i�[����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CGeometry::SetView(DirectX::XMFLOAT4X4 View)
{
	// =============== ��� ===============
	m_WVP[E_MATRIX_VIEW] = View;	//�r���[�s����
}

/* ========================================
   �֐��F�v���W�F�N�V�����s��o�^�֐�
   ----------------------------------------
   ���e�F�v���W�F�N�V�����s����󂯎��A�i�[����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CGeometry::SetProjection(DirectX::XMFLOAT4X4 Proj)
{
	// =============== ��� ===============
	m_WVP[E_MATRIX_PROJECTION] = Proj;	//�v���W�F�N�V�����s����
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
void CGeometry::MakeVS()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
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
void CGeometry::MakePS()
{
#ifdef _DEBUG
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	float4 color = float4(1,1,1,1);
	float2 halfGrid = floor(abs(pin.uv) * 2.0f);
	float2 quatGrid = floor(abs(pin.uv) * 8.0f);

	float half = fmod(halfGrid.x + halfGrid.y, 2.0f);
	float quat = fmod(quatGrid.x + quatGrid.y, 2.0f);

	color.rgb = ((half * 0.1f) * quat + 0.45f) + (1 - quat) * 0.05f;
	return color;
})EOT";
#else
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return float4(1.0f, 0.0f, 1.0f, 1.0f);
})EOT";
#endif

	m_pPS = new PixelShader();
	m_pPS->Compile(PSCode);
}