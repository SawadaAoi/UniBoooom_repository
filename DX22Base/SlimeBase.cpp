/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �X���C���x�[�X �N���X����
   ---------------------------------------
   SlimeBase.cpp

   �쐬�ҁF�鑺 ����

   �ύX����
   �E2023/11/04 �X���C���x�[�X�N���X�쐬 /�鑺 ����
   �E2023/11/06 �n���}�[�������͓G�ɂ�萁����΂����֐���ǉ�	/�R�����C

   �E2023/11/06 �C���N���[�h�뎚�̏C�� / �A �F��
   ======================================== */

  // =============== �C���N���[�h ===================
#include "SlimeBase.h"
#include "Geometry.h"
#include "Model.h"

// =============== �萔��` =======================

// =============== �v���g�^�C�v�錾 ===============

// =============== �O���[�o���ϐ���` =============

// =============== �R���X�g���N�^ =============
CSlimeBase::CSlimeBase()
	:m_pModel(nullptr)
	,m_pVS(nullptr)
	//,m_pos(0.0f,0.0f,0.0f)
	//,m_sphere{(0.0f,0.0f,0.0f),0.0f}
	,m_move(0.0f, 0.0f, 0.0f)
	,m_scale(1.0f,1.0f,1.0f)
	,m_fVecAngle(0.0f)
	//,m_playerPos(0.0f, 0.0f, 0.0f)
	,m_bUse(false)
	,m_bHitMove(false)
	,m_anglePlayer(0.0f)
	,m_distancePlayer(0.0f)
	, m_fSpeed(ENEMY_MOVE_SPEED)

{
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/eyeBat/eyeBat.FBX", 0.075f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "eyeBat", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}

	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	//��������
	m_sphere.pos = { 0.0f, 0.0f, 0.0f };
	m_sphere.radius = 0.0f;

	//��(player)������
	m_playerSphere.pos = { 0.0f, 0.0f, 0.0f };
	m_playerSphere.radius = 0.0f;


	

}

// =============== �f�X�g���N�^ =================
CSlimeBase::~CSlimeBase()
{

	// Model�폜
	if (m_pModel) {
		delete m_pModel;
		m_pModel = nullptr;
	}

	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}
}

/*
 ========================================
   �֐� Update()
 ----------------------------------------
   ���e�F�X�V����
 ======================================== */
void CSlimeBase::Update()
{
	// �g�p���ĂȂ��Ȃ�return
	if (m_bUse == false) return;

	if (!m_bHitMove)	//�G���ʏ�̈ړ���Ԃ̎�
	{
		//== �Ǐ]���� ==
		// �G����G�l�~�[�̋����A�p�x���v�Z
		m_distancePlayer = m_sphere.Distance(m_playerSphere);
		m_anglePlayer = m_sphere.Angle(m_playerSphere);

		TTriType<float> movePos = m_playerSphere.pos - m_sphere.pos;
		if (m_distancePlayer != 0)	//0���Z���
		{
			m_move.x = movePos.x / m_distancePlayer * m_fSpeed;
			m_move.z = movePos.z / m_distancePlayer * m_fSpeed;
		}
	}
	else
	{
		//�G�̐�����шړ�
		HitMove();
	}

	// -- ���W�X�V
	m_sphere.pos.x += m_move.x;
	m_sphere.pos.z += m_move.z;
}

/*
 ========================================
   �֐� Draw()
 ----------------------------------------
   ���e�F�`�揈��
 ======================================== */
void CSlimeBase::Draw()
{
	// �g�p���ĂȂ��Ȃ�return
	if (m_bUse == false) return;

	DirectX::XMFLOAT4X4 mat[3];

	//-- ���[���h�s��̌v�Z
	//DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);			//�ړ��s��
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(m_sphere.pos.x, m_sphere.pos.y, m_sphere.pos.z);			//�ړ��s��

	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);		//�g��k���s��
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationY(0.0f);		//��]�s��
	DirectX::XMMATRIX world = S * T * R;										//���[���h�s��̐ݒ�
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

	//-- ���f���\��
	if (m_pModel) {
		m_pModel->Draw();
	}
}

CSphereInfo::Sphere CSlimeBase::GetPos()
{
	return m_sphere;
}

/*
TTriType<float> CSlimeBase::GetPos()
{
	return m_pos;
}
*/
bool CSlimeBase::GetUse()
{
	return m_bUse;
}

/* ========================================
	�n���}�[���G�ɐ�����΂���Ď��ۂɈړ��ʂ��m�肷��֐�
	----------------------------------------
	���e�FX������Z�����̈ړ��ʂ��m�肷�鏈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::HitMove()
{
	//�G�L�����̈ړ����x�ƈړ��p�x�ɉ�����X������Z�����̈ړ��ʂ����߂�
	m_move.x = cos(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);
	m_move.z = sin(m_fVecAngle) * (m_fSpeed * SPEED_DOWN_RATIO);

	//���t���[���̑��x�̌��Z����
	m_fSpeed -= MOVE_RESIST;
	if (m_fSpeed <= 0)	//���x��0�ȉ��ɂȂ�����
	{
		m_fSpeed = ENEMY_MOVE_SPEED;	//�G�͒ʏ�̈ړ����x�ɂȂ�ʏ�ړ�����
		m_bHitMove = false;
	}
}

/* ========================================
	�n���}�[���G�ɐ�����΂����֐�
	----------------------------------------
	���e�F�����ɉ����Ĕ�ԕ����ƈړ����x�����߂鏈��
	----------------------------------------
	����1�F���x
	����2�F�p�x
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CSlimeBase::HitMoveStart(float speed, float angle)
{
	m_fSpeed = speed;		//�ړ��ʂ�����
	m_fVecAngle = angle;		//�ړ�����������
	m_bHitMove = true;		//������я�Ԃ�ON�ɂ���
}

//void CSlimeBase::SetPos(TTriType<float> pos)
//{
//	m_pos = pos;
//}

void CSlimeBase::SetPos(CSphereInfo::Sphere sphere)
{
	m_sphere.pos = sphere.pos;
}

void CSlimeBase::SetUse(bool onoff)
{
	m_bUse = onoff;
}

void CSlimeBase::SetPlayer(CSphereInfo::Sphere player)
{
	m_playerSphere = player;
}




