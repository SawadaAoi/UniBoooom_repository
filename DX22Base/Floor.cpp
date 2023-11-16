#include "Floor.h"

CFloor::CFloor()
	:m_pModel(nullptr)
	,m_pVS(nullptr)
	,m_pCamera(nullptr)
{
	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//���̃��f���ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/floor/floor_1.1.FBX", 0.1f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "slime_blue", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pModel->SetVertexShader(m_pVS);

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

	m_Transform.fPos = { 0.0f, 0.0f, 0.0f };
	m_Transform.fScale = { 1.0f, 1.0f, 1.0f };
	m_Transform.fRadian = { 0.0f, 0.0f, 0.0f };
}

CFloor::~CFloor()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}

void CFloor::Update()
{
}

void CFloor::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	//-- ���f���\��
	if (m_pModel) {
		m_pModel->Draw();
	}
}

void CFloor::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
