#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "Box.h"
#include "SlimeManager.h"

CSlimeManager* g_pSlimeMng;

SceneGame::SceneGame()
{
	
	// ���_�V�F�[�_�̓Ǎ�
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}


	// ���f���̓ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/eyeBat/eyeBat.FBX", 0.075f, Model::XFlip))	//�{���w��Ɣ��]�ݒ�͏ȗ���
	{
		MessageBox(NULL, "eyeBat", "Error", MB_OK);	//�G���[���b�Z�[�W�̕\��
	}
	m_pBox = new CBox;
	m_pPlayer = new CBox;
	
	m_pModel->SetVertexShader(m_pVS);	// ���_�V�F�[�_�����f���ɃZ�b�g

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
	

	m_pCamera = new CameraDebug() ;

	// �X���C���}�l�[�W���[����
	g_pSlimeMng = new CSlimeManager();
}

SceneGame::~SceneGame()
{
	// �X���C���}�l�[�W���[�폜
	if (g_pSlimeMng)
	{
		delete g_pSlimeMng;
		g_pSlimeMng = nullptr;
	}
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pBox)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pVS) {
		delete m_pVS;
		m_pVS = nullptr;
	}
	
}

 
void SceneGame::Update(float tick)
{
	m_pCamera->Update();

	// �X���C���}�l�[�W���[�X�V
	g_pSlimeMng->Update();
}

void SceneGame::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	// --- ���[���h�s��̌v�Z
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	// �ʒu���ړ�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);		// �傫����ύX
	DirectX::XMMATRIX world = T * S;
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);
	
	//--�r���[�s��̌v�Z
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),	 // �J�����̈ʒu
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),	 // �J���������ڂ��Ă���ʒu
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));	 // �J�����̏����
	view = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&mat[1], view);

	//-- �v���W�F�N�V�����s��̌v�Z 
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f),	// �c�����̉�p
		16.0f / 9.0f,						// �A�X�y�N�g��
		0.1f,								// ��ʂɎʂ�n�߂鋗��
		100.0f);							// �ʂ�����E����
	proj = DirectX::XMMatrixTranspose(proj);
	DirectX::XMStoreFloat4x4(&mat[2], proj);


	// �s����V�F�[�_�[�� 
	m_pVS->WriteBuffer(0, mat);

	// Genetory �p�� �ϊ��s���ݒ�
	if (m_pBox)
	{

		m_pBox->SetWorld(mat[0]);
		m_pBox->SetView(mat[1]);
		m_pBox->SetProjection(mat[2]);

		m_pBox->Draw();
	}
	// ���f���̕`��
	if (m_pModel)
	{
		m_pModel->Draw();
	}


	// Genetory �p�̕ϊ��s����v�Z
	T = DirectX::XMMatrixTranslation(0.0f, -0.05f, 0.0f);	// �ʒu���ړ�
	S = DirectX::XMMatrixScaling(5.0f, 0.1f, 5.0f);		// �傫����ύX
	world = T * S;	// �S�Ă̍s�����ɂ���
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	
	// Genetory �p�� �ϊ��s���ݒ�
	if (m_pBox)
	{

		m_pBox->SetWorld(mat[0]);
		m_pBox->SetView(mat[1]);
		m_pBox->SetProjection(mat[2]);

		m_pBox->Draw();
	}
	
	// �X���C���}�l�[�W���[�`��
	g_pSlimeMng->Draw();

}
