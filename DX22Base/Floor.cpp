/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	Floor�pcpp
	------------------------------------
	Floor.cpp
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/16 h,�쐬 yamashita
	�E2023/11/16 �R���X�g���N�^�ɒ��_�V�F�[�_�[�ƃ��f���̓ǂݍ��݂�ǉ� yamashita
	�E2023/11/16 �J�����̃Z�b�g�֐����쐬 yamashita
========================================== */
#include "Floor.h"

/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
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
	if (!m_pModel->Load("Assets/Model/floor/floor_1.1.FBX", 1.0f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "floor", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pModel->SetVertexShader(m_pVS);

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

	m_Transform.fPos = { 0.0f, 0.0f, 0.0f };	//�|�W�V�����̏�����
	m_Transform.fScale = { 1.0f, 1.0f, 1.0f };	//�X�P�[���̏�����
	m_Transform.fRadian = { 0.0f, 0.0f, 0.0f };	//��]�p��������
}

/* ========================================
   �֐��F�f�X�g���N�^
   ----------------------------------------
   ���e�F�I�����ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CFloor::~CFloor()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}

/* ========================================
	�A�b�v�f�[�g�֐�
   ----------------------------------------
   ���e�F���t���[���s������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CFloor::Update()
{
}

/* ========================================
   �`��֐�
   ----------------------------------------
   ���e�F�I�u�W�F�N�g�̕`��
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CFloor::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	mat[0] = m_Transform.GetWorldMatrixSRT();
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	//-- �s����V�F�[�_�[�֐ݒ�
	m_pVS->WriteBuffer(0, mat);

	//-- ���f���\��
	if (m_pModel) {
		m_pModel->Draw();
	}
}

/* ========================================
   �J�����Z�b�g�֐�
   ----------------------------------------
   ���e�F���̃I�u�W�F�N�g�Ɠ����J�������Z�b�g����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CFloor::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
