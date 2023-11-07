//CPP�p----------------------------------------------------
/*========================================
HEW/UniBoooom!!
---------------------------------------
�����pcpp
---------------------------------------
Explosion.cpp

TeiUon

�ύX����
�E2023/11/03 cpp�쐬 / �A �F��
�E2023/11/05 ����cpp�̏����ݒ�@/ �A �F��
�E2023/11/06 �����̃��f���ݒ�A�`��A�ʒu
	��bool�̐ݒ�Ǝ擾�֐����� / �A �F��

======================================== */


//=============== �C���N���[�h ===================
#include "Explosion.h"
#include "Geometry.h"


//=============== �萔��` =======================

//=============== �v���g�^�C�v�錾 ===============

//=============== �O���[�o���ϐ���` =============


CExplosion::CExplosion()
	:m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_fSize(1.0f)
	, m_bExploded(false)
{
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�



	if (!m_pModel->Load("Assets/Model/Golem/Golem.FBX", 1.0f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "Golem", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}

	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	//�����I�u�W�F�N�g������
	m_Sphere.pos = { 1.0f, 1.0f, 1.0f };
	m_Sphere.radius = 0.0f;
}

CExplosion::~CExplosion()
{

	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = nullptr;
	}
	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}

}

/*========================================
�֐��FUpdate�֐�
----------------------------------------
���e�F�������̍X�V����
----------------------------------------
�����F��U�Ȃ�
----------------------------------------
�ߒl�F��U�Ȃ�
======================================== */
void CExplosion::Update()
{

}


/*========================================
�֐��FDraw�֐�
----------------------------------------
���e�F�����̕`�揈��
----------------------------------------
�����F�Ȃ�
----------------------------------------
�ߒl�F�Ȃ�
======================================== */

void CExplosion::Draw()
{


	// �g�p���ĂȂ��Ȃ�return
	if (m_bExploded == false) return;

	DirectX::XMFLOAT4X4 mat[3];

	//-- ���[���h�s��̌v�Z
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(3.0f, 3.0f, 3.0f);			//�ړ��s��
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);		// �傫����ύX
	DirectX::XMMATRIX world = T * S;										//���[���h�s��̐ݒ�
	world = DirectX::XMMatrixTranspose(world);								//�]�u�s��ɕϊ�
	DirectX::XMStoreFloat4x4(&mat[0], world);								//XMMATRIX�^(world)����XMFLOAT4X4�^(mat[0])�֕ϊ����Ċi�[

	//-- �r���[�s��̌v�Z
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)); //�r���[�s��̐ݒ�
	view = DirectX::XMMatrixTranspose(view);		//�]�u�s��ɕϊ�
	DirectX::XMStoreFloat4x4(&mat[1], view);		//XMMATRIX�^(view)����XMFLOAT4X4�^(mat[1])�֕ϊ����Ċi�[

	//-- �v���W�F�N�V�����s��̌v�Z
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f), (float)16 / 9, 0.1f, 100.0f); //�v���W�F�N�V���s��̐ݒ�
	proj = DirectX::XMMatrixTranspose(proj);	//�]�u�s��ɕϊ�
	DirectX::XMStoreFloat4x4(&mat[2], proj);	//XMMATRIX�^(proj)����XMFLOAT4X4�^(mat[2])�֕ϊ����Ċi�[

	//-- �s����V�F�[�_�[�֐ݒ�
	m_pVS->WriteBuffer(0, mat);

	//--���f���\��
	if (m_pModel)
	{
		m_pModel->Draw();
	}
}

void CExplosion::SetSphere(CSphereInfo::Sphere sphere)
{
	 
}

/*========================================
�֐��FGetExplode�֐�
----------------------------------------
���e�F��������t���O���擾
----------------------------------------
�����F�Ȃ�
----------------------------------------
�ߒl�F�Ȃ�
======================================== */
bool CExplosion::GetExplode()
{
	return false;	//�ǂ����悤�킩��Ȃ������Ufalse��
}

/*========================================
�֐��FGetPos�֐�
----------------------------------------
���e�F�����̈ʒu���擾
----------------------------------------
�����F�Ȃ�
----------------------------------------
�ߒl�F�Ȃ�
======================================== */
CSphereInfo::Sphere CExplosion::GetSphere()
{
	return m_Sphere;
}

/*========================================
�֐��FSetExplode�֐�
----------------------------------------
���e�F�X���C���𔚔��ɐݒ�
----------------------------------------
�����Fbool(�������ǂ���)
----------------------------------------
�ߒl�F�Ȃ�
======================================== */
void CExplosion::SetExplode(bool YN)
{
	m_bExploded = YN;
}
