/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���ʃ|���S������
	------------------------------------
	2dPolygon.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/11/21 �쐬 takagi
	�E2023/11/22 ���b�V���T�C�Y��1x1�ɏC�� takagi

========================================== */

// =============== �f�o�b�O���[�h ===================
#if _DEBUG
#define USE_2D_POLYGON (true)	//�t�F�[�h���^�]
#endif

// =============== �C���N���[�h ===================
#include "2dPolygon.h"	//���g�̃w�b�_

#if USE_2D_POLYGON
#include "Input.h"	//�L�[���͗p
#endif

#if _DEBUG
#include <Windows.h>	//���b�Z�[�W�{�b�N�X�p
#endif

// =============== �萔��` =====================
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);	//�ʒu������
const TTriType<float> INIT_SCALE(1.0f, 1.0f, 0.0f);	//�����g�k
const TTriType<float> INIT_RADIAN(0.0f);			//������]
const int FRAME_MIN(0);								//�t�F�[�h���Ԃ̍ŏ�
const int FRAME_TURNING_1(50);						//�g�k���]�P���]
const int FRAME_TURNING_2(100);						//�g�k���]�Q���]
const int FRAME_MAX(150);							//�t�F�[�h���Ԃ̍ő�
const float SCALE_MIN(0.0f);						//�ŏ��T�C�Y
const float SCALE_TURNINIG_2(30.0f);				//�T�C�Y���]�Q���]
const float SCALE_TURNINIG_1(100.0f);				//�T�C�Y���]�P���]
const float SCALE_MAX(1000.0f);						//�ő�T�C�Y
const float ROTATE_ACCEL_RATE(4.0f);				//�p���x��������
const char* VS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float2 uvPos;
	float2 uvScale;
	float4 color;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;
	vout.color = color;
	return vout;
})EOT";	//���_�V�F�[�_�[�R���p�C���Ώ�
const char* PS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET {
	return tex.Sample(samp, pin.uv) * pin.color;
})EOT";	//�s�N�Z���V�F�[�_�[�R���p�C���Ώ�

// =============== �O���[�o���ϐ��錾 =====================
int C2dPolygon::ms_nCnt2dPolygon;					//���g�̐�����
const void* C2dPolygon::ms_pVtx = nullptr;			//���_���
unsigned int C2dPolygon::ms_unVtxSize;				//���_�T�C�Y
unsigned int C2dPolygon::ms_unVtxCount;				//���_��
const void* C2dPolygon::ms_pIdx = nullptr;			//���_�̃C���f�b�N�X
unsigned int C2dPolygon::ms_unIdxSize;				//�C���f�b�N�X�T�C�Y
unsigned int C2dPolygon::ms_unIdxCount;				//�C���f�b�N�X��
ID3D11Buffer* C2dPolygon::ms_pVtxBuffer = nullptr;	//���_�o�b�t�@
ID3D11Buffer* C2dPolygon::ms_pIdxBuffer = nullptr;	//�C���f�b�N�X�o�b�t�@ 

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
C2dPolygon::C2dPolygon()
	:m_Transform(INIT_POS, INIT_SCALE, INIT_RADIAN)	//���[���h���W
	,m_Param{{0.0f}, {1.0f, 1.0f}, {0.0f}, 1.0f}	//�V�F�[�_�[�ɏ������ޏ��
	,m_pVs(nullptr)									//���_�V�F�[�_�[
	,m_pPs(nullptr)									//�s�N�Z���V�F�[�_�[
	,m_pTexture(nullptr)							//�e�N�X�`��
	,m_pCamera(nullptr)								//�J����
{
	// =============== �ÓI�쐬 ===================
	if (0 == ms_nCnt2dPolygon)	//���݁A���ɂ��̃N���X���쐬����Ă��Ȃ���
	{
		// =============== �V�F�[�_�[�쐬 ===================
		MakeVertexShader();	//���_�V�F�[�_�[�쐬
		MakePixelShader();	//�s�N�Z���V�F�[�_�[�쐬

	// =============== �`��쐬 ===================
		Make();	//���ʃ|���S���쐬
	}

	// =============== �s��쐬 ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//���[���h�s��
	DirectX::XMStoreFloat4x4(&m_aMatrix[1], DirectX::XMMatrixIdentity());	//�r���[�s��F�P�ʍs��
	DirectX::XMStoreFloat4x4(&m_aMatrix[2], DirectX::XMMatrixIdentity());	//�v���W�F�N�V�����s��

	// =============== �J�E���^ ===================
	ms_nCnt2dPolygon++;	//���g�̐��J�E���g
}

/* ========================================
	�R�s�[�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst C2dPolygon & Obj�F�R�s�[���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
C2dPolygon::C2dPolygon(const C2dPolygon & Obj)
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
C2dPolygon::~C2dPolygon()
{
	// =============== �J�E���^ ===================
	ms_nCnt2dPolygon--;			//���g�̐��J�E���g

	// =============== ��� ===================
	SAFE_DELETE(m_pVs);			//���_�V�F�[�_�[���
	SAFE_DELETE(m_pPs);			//�s�N�Z���V�F�[�_�[���
	SAFE_DELETE(m_pTexture);	//�e�N�X�`�����
	//SAFE_DELETE(ms_pVtx);		//���_�����
	//SAFE_DELETE(ms_pIdx);		//���_�C���f�b�N�X���
	//SAFE_DELETE(ms_pVtxBuffer);	//���_�o�b�t�@���
	//SAFE_DELETE(ms_pIdxBuffer);	//�C���f�b�N�X�o�b�t�@���
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::Draw()
{
	// =============== ���� ===================
	if (!m_pTexture)	//�k���`�F�b�N
	{
#if _DEBUG
		MessageBox(nullptr, "�e�N�X�`�����o�^����Ă��܂���", "2dPolygon.cpp->Draw->Error", MB_OK);	//�G���[�ʒm
#endif
		return;	//�������f
	}
	if (!m_pCamera)	//�k���`�F�b�N
	{
#if _DEBUG
		MessageBox(nullptr, "�J�������o�^����Ă��܂���", "2dPolygon.cpp->Draw->Error", MB_OK);	//�G���[�ʒm
#endif
		return;	//�������f
	}

	// =============== �s��X�V ===================
	m_aMatrix[0] = m_Transform.GetWorldMatrixSRT();							//���[���h�s��X�V
	m_aMatrix[2] = m_pCamera->GetProjectionMatrix(CCamera::E_DRAW_TYPE_2D);	//�v���W�F�N�V�����s��X�V

	// =============== �ϐ��錾 ===================
	float Param[8] = { m_Param.fUvOffset.x, m_Param.fUvOffset.y, m_Param.fUvScale.x, m_Param.fUvScale.y,
			m_Param.fColor.x, m_Param.fColor.y, m_Param.fColor.z, m_Param.fAlpha};	//�萔�o�b�t�@�������ݗp

	// =============== �V�F�[�_�[�g�p ===================
	m_pVs->WriteBuffer(0, m_aMatrix);	//�萔�o�b�t�@�ɍs���񏑂�����
	m_pVs->WriteBuffer(1, &Param);		//�萔�o�b�t�@��UV��񏑂�����
	m_pVs->Bind();						//���_�V�F�[�_�[�g�p
	m_pPs->SetTexture(0, m_pTexture);	//�e�N�X�`���o�^
	m_pPs->Bind();						//�s�N�Z���V�F�[�_�[�g�p

	// =============== �ϐ��錾 ===================
	ID3D11DeviceContext* pContext = GetContext();	//�`�摮���̏��
	unsigned int unOffset = 0;						//���_�o�b�t�@�z����̃o�b�t�@��

	// =============== �g�|���W�[�ݒ� ===================
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		//�O�p�|���S���̃g�|���W�[		TODO:���ʂ�����strip�ł��ǂ����������ǂǂ����̕����y�������ׂ�

	// =============== ���_�o�b�t�@�o�^ ===================
	pContext->IASetVertexBuffers(0, 1, &ms_pVtxBuffer, &ms_unVtxSize, &unOffset);	//���_�o�b�t�@�o�^

	// =============== �C���f�b�N�X�̗L�� ===================
	if (ms_unIdxCount > 0)	//�C���f�b�N�X�����鎞
	{
		// =============== �T�C�Y�Ⴂ ===================
		DXGI_FORMAT Format;	//���\�[�X�f�[�^�t�H�[�}�b�g
		switch (ms_unIdxSize)	//�C���f�b�N�X�T�C�Y
		{
		case 4: Format = DXGI_FORMAT_R32_UINT; break;	//1����32�r�b�g�����Ȃ�����(unsigned int (�V�������))
		case 2: Format = DXGI_FORMAT_R16_UINT; break;	//1����16�r�b�g�����Ȃ�����(unsigned int (�Â����))
		}

		// =============== �C���f�b�N�X�o�b�t�@�o�^ ===================
		pContext->IASetIndexBuffer(ms_pIdxBuffer, Format, 0);	//�C���f�b�N�X�o�b�t�@�o�^

		// =============== �`�� ===================
		pContext->DrawIndexed(ms_unIdxCount, 0, 0);	//���_�̃C���f�b�N�X���g���ĕ`��
	}
	else
	{
		// =============== �`�� ===================
		pContext->Draw(ms_unVtxCount, 0);	// ���_�o�b�t�@�݂̂ŕ`��
	}
}

/* ========================================
	�J�����Z�b�^�֐�
	-------------------------------------
	���e�F�J�����o�^
	-------------------------------------
	����1�Fconst CCamera* pCamera�F���g���f���J����
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetCamera(const CCamera* pCamera)
{
	// =============== �|�C���^�ǐ� ===================
	m_pCamera = pCamera;	//�A�h���X�i�[
}

/* ========================================
	�ʒu�Z�b�^�֐�
	-------------------------------------
	���e�F�ʒu�o�^
	-------------------------------------
	����1�FTPos3d<float> fPos�F�V�K�ʒu���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetPos(TPos3d<float> fPos)
{
	// =============== �i�[ ===================
	m_Transform.fPos = fPos;	//�ʒu���i�[
}

/* ========================================
	�傫���Z�b�^�֐�
	-------------------------------------
	���e�F�傫���o�^
	-------------------------------------
	����1�FTTriType<float> fScale�F�V�K�g�k���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetSize(TTriType<float> fScale)
{
	// =============== �i�[ ===================
	m_Transform.fScale = fScale;	//�g�k�i�[
}

/* ========================================
	��]�Z�b�^�֐�
	-------------------------------------
	���e�F��]�o�^
	-------------------------------------
	����1�FTTriType<float> fRotate�F�V�K��]���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetRotate(TTriType<float> fRotate)
{
	// =============== �i�[ ===================
	m_Transform.fRadian = fRotate;	//��]�i�[
}

/* ========================================
	���[���h�s��Z�b�^�֐�
	-------------------------------------
	���e�F���[���h�s��o�^
	-------------------------------------
	����1�FTPos3d<float> fPos�F�V�K���[���h�n���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetTransform(tagTransform3d Transform)
{
	// =============== �i�[ ===================
	m_Transform = Transform;	//���[���h�s��i�[
}

/* ========================================
	UV����Z�b�^�֐�
	-------------------------------------
	���e�FUV����o�^
	-------------------------------------
	����1�FTDiType<float> fUvPos�F�V�Kuv������
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetUvOffset(TDiType<float> fUvOffset)
{
	// =============== �i�[ ===================
	m_Param.fUvOffset = fUvOffset;	//UV������i�[
}

/* ========================================
	UV�g�k�Z�b�^�֐�
	-------------------------------------
	���e�FUV�g�k�o�^
	-------------------------------------
	����1�FTDiType<float> fUvPos�F�V�Kuv�g�k���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetUvScale(TDiType<float> fUvScale)
{
	// =============== �i�[ ===================
	m_Param.fUvScale = fUvScale;	//UV�g�k���i�[
}

/* ========================================
	�F�Z�b�^�֐�
	-------------------------------------
	���e�F�F���o�^
	-------------------------------------
	����1�FTTriType<float> fRGB�FRGB���
	����2�Ffloat fAlpha�F�����x
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetColor(TTriType<float> fRGB, float fAlpha)
{
	// =============== �i�[ ===================
	m_Param.fColor = fRGB;		//RGB���i�[
	m_Param.fAlpha = fAlpha;	//�����x���i�[
}

/* ========================================
	�F�Z�b�^�֐�
	-------------------------------------
	���e�F�F���o�^
	-------------------------------------
	����1�FTTriType<float> fRGB�FRGB���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetColor(TTriType<float> fRGB)
{
	// =============== �i�[ ===================
	m_Param.fColor = fRGB;	//RGB���i�[
}

/* ========================================
	�F�Z�b�^�֐�
	-------------------------------------
	���e�F�F���o�^
	-------------------------------------
	����1�Ffloat fColor�FRGBA�S�Ăɓo�^����l
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetColor(float fColor)
{
	// =============== �i�[ ===================
	m_Param.fColor = 0.0f;	//RGB���i�[
	m_Param.fAlpha = 0.0f;	//�����x�i�[
}

/* ========================================
	�����x�Z�b�^�֐�
	-------------------------------------
	���e�F�����x���o�^
	-------------------------------------
	����1�Ffloat fAlpha�F�����x
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetAlpha(float fAlpha)
{
	// =============== �i�[ ===================
	m_Param.fAlpha = fAlpha;	//�����x�i�[
}


/* ========================================
	�e�N�X�`���Z�b�^�֐�
	-------------------------------------
	���e�F�e�N�X�`���쐬�E�o�^
	-------------------------------------
	����1�Fconst char* pcTexPass�F�e�N�X�`���̃p�X
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetTexture(const char* pcTexPass)
{
	// =============== ��� ===================
	SAFE_DELETE(m_pTexture);	//�e�N�X�`�����

	// =============== �쐬 ===================
	m_pTexture = new Texture;		//���I�m��
	m_pTexture->Create(pcTexPass);	//�V�K�e�N�X�`���o�^
}

/* ========================================
	���_�V�F�[�_�[�֐�
	-------------------------------------
	���e�F���_�V�F�[�_�[�o�^
	-------------------------------------
	����1�FVertexShader* pVs�F���_�V�F�[�_�[�̃|�C���^
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetVertexShader(VertexShader* pVs)
{
}

/* ========================================
	�s�N�Z���V�F�[�_�[�֐�
	-------------------------------------
	���e�F�s�N�Z���V�F�[�_�[�o�^
	-------------------------------------
	����1�FPixelShader* pPs�F�s�N�Z���V�F�[�_�[�̃|�C���^
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::SetPixelShader(PixelShader* pPs)
{
}

/* ========================================
	���_�V�F�[�_�[�쐬�֐�
	-------------------------------------
	���e�F���_�V�F�[�_�[�̃R���p�C��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::MakeVertexShader()
{
	// =============== �쐬 ===================
	if (m_pVs)	//�k���`�F�b�N
	{
		SAFE_DELETE(m_pVs);	//���
	}
	m_pVs = new VertexShader();	//���I�m��
	m_pVs->Compile(VS);			//�R���p�C��
}

/* ========================================
	�s�N�Z���V�F�[�_�[�쐬�֐�
	-------------------------------------
	���e�F�s�N�Z���V�F�[�_�[�̃R���p�C��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::MakePixelShader()
{
	// =============== �쐬 ===================
	if (m_pPs)	//�k���`�F�b�N
	{
		SAFE_DELETE(m_pPs);	//���
	}
	m_pPs = new PixelShader();	//���I�m��
	m_pPs->Compile(PS);			//�R���p�C��
}

/* ========================================
	�`�󐶐��֐�
	-------------------------------------
	���e�F�`�󐶐��E���o�^
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::Make()
{
	// =============== �ϐ��錾 ===================
	Vertex aVtx[] = {
		{{-0.5f, 0.5f, -0.0f}, {0.0f, 0.0f}},	//���ʃ|���S������
		{{ 0.5f, 0.5f, -0.0f}, {1.0f, 0.0f}},	//���ʃ|���S���E��
		{{-0.5f,-0.5f, -0.0f}, {0.0f, 1.0f}},	//���ʃ|���S������
		{{ 0.5f,-0.5f, -0.0f}, {1.0f, 1.0f}},	//���ʃ|���S���E��
	};	//���_���
	int aIdx[] = {
		0, 1, 2, 2, 1, 3	//���ʃ|���S��
	};	//���_�C���f�b�N�X

	// =============== ������ ===================
	ms_pVtx = aVtx;					//���_���
	ms_unVtxSize = sizeof(Vertex);	//���_�^�T�C�Y
	ms_unVtxCount = _countof(aVtx);	//���_��
	ms_pIdx = aIdx;					//���_�̃C���f�b�N�X
	ms_unIdxSize = sizeof(int);		//�C���f�b�N�X�T�C�Y
	ms_unIdxCount = _countof(aIdx);	//�C���f�b�N�X��

	// =============== ���� ===================
	CreateVtxBuffer();	//���_�o�b�t�@�쐬
	CreateIdxBuffer();	//�C���f�b�N�X�o�b�t�@
}

/* ========================================
	���_�o�b�t�@�쐬�֐�
	-------------------------------------
	���e�F�C���f�b�N�X��񂩂�f�[�^�쐬
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::CreateVtxBuffer()
{
	// =============== �o�b�t�@���ݒ� ===================
	D3D11_BUFFER_DESC BufDesc;							//�o�b�t�@���
	ZeroMemory(&BufDesc, sizeof(BufDesc));				//���g��S��0�ŏ�����
	BufDesc.ByteWidth = ms_unVtxSize * ms_unVtxCount;	//�o�b�t�@�̑傫��
	BufDesc.Usage = D3D11_USAGE_DEFAULT;				//��������ł̊Ǘ����@
	BufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//GPU��ł̗��p���@

	//���o�b�t�@�����f�[�^�ݒ�
	D3D11_SUBRESOURCE_DATA SubResource;				//�T�u���\�[�X
	ZeroMemory(&SubResource, sizeof(SubResource));	//�f�[�^������
	SubResource.pSysMem = ms_pVtx;					//�o�b�t�@�ɓ��ꍞ�ރf�[�^

	// =============== �쐬 ===================
	HRESULT hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pVtxBuffer);	//���_�o�b�t�@�쐬
	if (FAILED(hr))	//�G���[����
	{
		// =============== ��֏��� ===================
		ms_pVtxBuffer = nullptr;	//��A�h���X���
	}
}

/* ========================================
	�C���f�b�N�X�o�b�t�@�쐬�֐�
	-------------------------------------
	���e�F�C���f�b�N�X��񂩂�f�[�^�쐬
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void C2dPolygon::CreateIdxBuffer()
{
	// =============== �C���f�b�N�X�T�C�Y�̊m�F ===================
	switch (ms_unIdxSize)
	{
		// =============== �T�C�Y�Ⴂ ===================
	default:	//���L�ȊO
#if _DEBUG
		MessageBox(nullptr, "�^�̃T�C�Y��int�^�ƈ�v���܂���", "2dPolygon.cpp->Error", MB_OK);	//�G���[�ʒm
#endif
		return;	//�������f

		// =============== int�^�Ɠ��� ===================
	case 2:	//�Â�int�^�̃T�C�Y
	case 4:	//����int�^�̃T�C�Y
		break;	//���򏈗��I��
	}

	// =============== �o�b�t�@�̏���ݒ� ===================
	D3D11_BUFFER_DESC BufDesc;							//�o�b�t�@���
	ZeroMemory(&BufDesc, sizeof(BufDesc));				//���g��S��0�ŏ�����
	BufDesc.ByteWidth = ms_unIdxSize * ms_unIdxCount;	//�f�[�^�̃o�C�g��
	BufDesc.Usage = D3D11_USAGE_DEFAULT;				//��������ł̊Ǘ����@
	BufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//GPU��ł̗��p���@

	// =============== �o�b�t�@�̏����f�[�^ ===================
	D3D11_SUBRESOURCE_DATA SubResource = {};	//�T�u���\�[�X
	SubResource.pSysMem = ms_pIdx;				//�o�b�t�@�ɓ��ꍞ�ރf�[�^

	// =============== �쐬 ===================
	HRESULT hr = GetDevice()->CreateBuffer(&BufDesc, &SubResource, &ms_pIdxBuffer);	//�C���f�b�N�X�̃o�b�t�@�쐬
	if (FAILED(hr))	//�G���[����
	{
		// =============== ��֏��� ===================
		ms_pIdxBuffer = nullptr;	//��A�h���X���
	}
}