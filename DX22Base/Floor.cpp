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
	�E2023/11/22 ���̎��������@�\��ǉ� yamashita
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2023/12/15 �X�e�[�W�ʂɏ��̃��f����ݒ�ł���悤�ɏC�� Sawada

========================================== */
#include "Floor.h"
#include "DirectWrite.h"

// =============== �萔��` =====================
const float FLOOR_OFFSET_X = 48.0f * FLOOR_SCALE_X;
const float FLOOR_OFFSET_Z = 48.0f * FLOOR_SCALE_Z;
#if MODE_GAME_PARAMETER
#else
const float FLOOR_SCALE_X = 1.1f;
const float FLOOR_SCALE_Z = 1.1f;
#endif

/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�v���C���[�̍��W�|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CFloor::CFloor(TPos3d<float>* pPlayerPos)
	:m_pModel(nullptr)
	,m_pVS(nullptr)
	,m_pCamera(nullptr)
	,m_pPlayerFloor{0,0,0}
	,m_pPlayePos(pPlayerPos)
{
	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	

	//���̈ʒu��������
	TTriType<float> pos;
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		//X���W
		switch (i % 3)
		{
		case(0):	pos.x = -(FLOOR_OFFSET_X);
			break;
		case(1):	pos.x = 0.0f;
			break;
		case(2):	pos.x = FLOOR_OFFSET_X;
			break;
		}

		//Z���W
		switch (i / 3)
		{
		case(0):	pos.z = -(FLOOR_OFFSET_Z);
			break;
		case(1):	pos.z = 0.0f;
			break;
		case(2):	pos.z = FLOOR_OFFSET_Z;
			break;
		}

		m_Transform[i].fPos		= { pos.x, 0.0f, pos.z };					//�|�W�V�����̏�����
		m_Transform[i].fScale	= { FLOOR_SCALE_X, 1.0f, FLOOR_SCALE_Z };	//�X�P�[���̏�����
		m_Transform[i].fRadian	= { 0.0f, 0.0f, 0.0f };						//��]�p��������
	}	
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
	calculationPosition();
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

	for (int i = 0; i < FLOOR_NUM; i++)
	{
		mat[0] = m_Transform[i].GetWorldMatrixSRT();
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();

		//-- �s����V�F�[�_�[�֐ݒ�
		m_pVS->WriteBuffer(0, mat);

		//-- ���f���\��
		if (m_pModel) {
			m_pModel->Draw();
		}
	}
}

/* ========================================
	�|�W�V�����Z�o�֐�
   ----------------------------------------
   ���e�F�v���C���[�̍��W���珰�̕\�����W����肾��
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CFloor::calculationPosition()
{
	int offsetX = (int)m_pPlayePos->x;	//�v���C���[�̒��S�����X���W�̂���
	int offsetZ = (int)m_pPlayePos->z;	//�v���C���[�̒��S�����Z���W�̂���
	if (offsetX >= 0) { offsetX += int(FLOOR_OFFSET_X / 2.0f); }	//���W���v���X�Ȃ���Z
	else { offsetX -= int(FLOOR_OFFSET_X / 2.0f); }					//���W���}�C�i�X�Ȃ猸�Z
	if (offsetZ >= 0) { offsetZ += int(FLOOR_OFFSET_X / 2.0f); }	//���W���v���X�Ȃ���Z
	else { offsetZ -= int(FLOOR_OFFSET_X / 2.0f); }				//���W���}�C�i�X�Ȃ猸�Z

	//�v���C���[�����̑傫���ŉ����ڕ��̏��ɂ��邩
	m_pPlayerFloor.x = int(offsetX / FLOOR_OFFSET_X);
	m_pPlayerFloor.z = int(offsetZ / FLOOR_OFFSET_Z);


	//����\��������W���m��
	TTriType<float> pos;
	TTriType<float> centerPos = { m_pPlayerFloor.x * FLOOR_OFFSET_X,0.0f,m_pPlayerFloor.z * FLOOR_OFFSET_Z };
	for (int i = 0; i < FLOOR_NUM; i++)
	{
		//X���W
		switch (i % 3)
		{
		case(0):	pos.x = centerPos.x - (FLOOR_OFFSET_X);
			break;
		case(1):	pos.x = centerPos.x;
			break;
		case(2):	pos.x = centerPos.x + FLOOR_OFFSET_X;
			break;
		}

		//Z���W
		switch (i / 3)
		{
		case(0):	pos.z = centerPos.z - (FLOOR_OFFSET_Z);
			break;
		case(1):	pos.z = centerPos.z;
			break;
		case(2):	pos.z = centerPos.z + FLOOR_OFFSET_Z;
			break;
		}

		m_Transform[i].fPos = { pos.x, 0.0f, pos.z };	//���W���m��
	}
}

/* ========================================
   �J�����Z�b�g�֐�
   ----------------------------------------
   ���e�F���̃I�u�W�F�N�g�Ɠ����J�������Z�b�g����
   ----------------------------------------
   �����F�J�����̃|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CFloor::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}

/* ========================================
   �����f���Z�b�g�֐�
   ----------------------------------------
   ���e�F�X�e�[�W���ɈႤ�����ڂ̏����f�����Z�b�g����
   ----------------------------------------
   ����1�F�X�e�[�W�̎��
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CFloor::SetFloorModel(StageKinds stageKind)
{
	//���̃��f���ǂݍ���
	m_pModel = new Model;
	switch (stageKind)
	{
	case CFloor::Stage1:
		if (!m_pModel->Load("Assets/Model/floor/Stage1/floor_grass.fbx", 1.0f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
			MessageBox(NULL, "floor", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
		break;
	case CFloor::Stage2:
		if (!m_pModel->Load("Assets/Model/floor/Stage2/floor_cave.fbx", 1.0f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
			MessageBox(NULL, "floor", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
		break;
	case CFloor::Stage3:
		if (!m_pModel->Load("Assets/Model/floor/Stage3/floor_StainedGlass.FBX", 1.0f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
			MessageBox(NULL, "floor", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
		}
		break;
	default:
		break;
	}

	m_pModel->SetVertexShader(m_pVS);
}
