/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�Q�[���V�[���̃X�e�[�W�P�pcpp
	------------------------------------
	SceneGameStage1.h
	------------------------------------
	�쐬�� �m�}����

	�ύX����
	�E2023/11/17 �V�K�쐬 �m�}����

========================================== */

// =============== �C���N���[�h ===================
#include "SceneGameStage1.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "CameraChase.h"
#include "Pos3d.h"
#include "Box.h"
#include "Line.h"
#include "Defines.h"

// =============== �f�o�b�O���[�h =======================
#define MODE_COORD_AXIS (true)	//���W���f�����ǂ���
#define MODE_GROUND (false)	//���W���f�����ǂ���

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	�����F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSceneGameStage1::CSceneGameStage1(DirectWrite* pDirectWrite)
{
	// ���_�V�F�[�_�̓Ǎ�
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
	SetDirectWrite(pDirectWrite);

#if MODE_COORD_AXIS
	// �����̕\��
	CLine::Init();
#endif

	m_pPlayer = new CPlayer();
	m_pCamera = new CCameraChase(m_pPlayer->GetPosAddress());
	m_pPlayer->SetCamera(m_pCamera);

#if MODE_GROUND
	m_pBox = new CBox();
#endif

	// �X���C���}�l�[�W���[����
	m_pSlimeMng = new CSlimeManager();
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pExplosionMng = new CExplosionManager();
	m_pExplosionMng->SetCamera(m_pCamera);

	// HP�}�l�[�W���[����
	m_pHpMng = new ChpManager;

	m_pColOfStg = new CCollisionOfStage();
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	�����F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CSceneGameStage1::~CSceneGameStage1()
{
	SAFE_DELETE(m_pHpMng);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// �X���C���}�l�[�W���[�폜
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
#if MODE_COORD_AXIS
	// �����̕\��
	CLine::Uninit();
#endif
	SAFE_DELETE(m_pVs);
}

/* ========================================
   �X�V�����֐�
   -------------------------------------
   ���e�F�X�V����
   -------------------------------------
   �����F����
   -------------------------------------
   �ߒl�F����
=========================================== */
void CSceneGameStage1::Update()
{
	m_pCamera->Update();
	m_pPlayer->Update();
	m_pSlimeMng->SetPlayerPos(m_pPlayer->GetPos());

	// �X���C���}�l�[�W���[�X�V
	m_pSlimeMng->Update(m_pExplosionMng);
	m_pExplosionMng->Update();
	m_pCamera->Update();

	m_pColOfStg->CollisionOfStage();
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
void CSceneGameStage1::Draw()
{
#if MODE_COORD_AXIS
	// �����̕\��
	CLine::SetView(m_pCamera->GetViewMatrix());
	CLine::SetProjection(m_pCamera->GetProjectionMatrix());
	// �O���b�h
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
	}
	// ��
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(size, 0, 0), DirectX::XMFLOAT4(1, 0, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, size, 0), DirectX::XMFLOAT4(0, 1, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, size), DirectX::XMFLOAT4(0, 0, 1, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(-size, 0, 0), DirectX::XMFLOAT4(0, 0, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -size), DirectX::XMFLOAT4(0, 0, 0, 1));

	CLine::Draw();
#endif

#if MODE_GROUND
	DirectX::XMFLOAT4X4 mat[3];

	//Geometory�p�̕ϊ��s���ݒ�
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, -0.5f * 0.1f, 0.0f);	//�O���b�h�������ɗ���悤�Ɉړ�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(100.0f, 0.1f, 100.0f);		//�n�ʂƂȂ�悤�ɁA�O�㍶�E�ɍL���㉺�ɋ���
	DirectX::XMMATRIX world = S * T;											//�S�Ă̍s�����ɂ܂Ƃ߂�
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);	//mat��fMat�Ɋi�[
	m_pBox->SetWorld(mat[0]);	//�{�b�N�X�ɕϊ��s���ݒ�

	//Geometory�p�̕ϊ��s���ݒ�
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pBox->SetView(mat[1]);		//�{�b�N�X�ɕϊ��s���ݒ�
	m_pBox->SetProjection(mat[2]);	//�{�b�N�X�ɕϊ��s���ݒ�

	//// �s����V�F�[�_�[�� 
	//m_pVs->WriteBuffer(0, mat);

	m_pBox->Draw();
#endif


	// �X���C���}�l�[�W���[�`��
	m_pSlimeMng->Draw();
	m_pPlayer->Draw();

	//�����}�l�[�W���[�`��
	m_pExplosionMng->Draw();

	// HP�}�l�[�W���[�`��
	m_pHpMng->Draw();
}

void CSceneGameStage1::SetDirectWrite(DirectWrite* pDirectWrite)
{
	m_pDirectWrite = pDirectWrite;
}

