/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �~������
   ---------------------------------------
   Cylinder.cpp

   �쐬��	takagi

   �ύX����
   �E2023/11/05 ���� takagi
   �E2023/11/06 �R���X�g���N�^���C takagi

   ======================================== */



// =============== �C���N���[�h ===================
#include "Cylinder.h"	//���g�̃w�b�_

// =============== �萔��` ===================
const float CYLINDER_RADIUS = 0.5f;
const float CYLINDER_HEIGHT = 2.0f;
const int CORNER_NUM = 8;
const int VTX_TOP_SURFACE = CORNER_NUM;
const int VTX_BOTTOM_SURFACE = VTX_TOP_SURFACE;
const int VTX_CIRCLE = VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE;
const int VTX_SIDE_SURFACE = VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE + 2;
const int SURFACE_TOP = CORNER_NUM - 2;
const int SURFACE_BOTTOM = CORNER_NUM - 2;
const int SURFACE_SIDE = CORNER_NUM * 2;
const int SURFACE_CYLINDER_NUM = SURFACE_TOP + SURFACE_BOTTOM + SURFACE_SIDE;



/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CCylinder::CCylinder()
{
	// =============== ���_�̍쐬 ===================
	// �V�ʁA���
	Vertex vtx[CORNER_NUM + VTX_BOTTOM_SURFACE + VTX_SIDE_SURFACE];
	float angle = 0.0f;
	float radian;
	float posX;
	float posY;
	float posZ;
	float u, v;

	for (int i = 0; i < VTX_TOP_SURFACE; i++)
	{
		angle = i * (360 / CORNER_NUM);
		radian = DirectX::XMConvertToRadians(angle);
		posX = sin(radian) * CYLINDER_RADIUS;
		posY = CYLINDER_HEIGHT / 2;
		posZ = cos(radian) * CYLINDER_RADIUS;
		u = (posX / CYLINDER_RADIUS) + 0.5f;
		v = -(posZ / CYLINDER_RADIUS) + 0.5f;

		vtx[i] = { {posX,posY,posZ},{u,v} };
	}

	for (int i = 0; i < VTX_BOTTOM_SURFACE; i++)
	{
		angle = i * (360 / CORNER_NUM);
		radian = DirectX::XMConvertToRadians(angle);
		posX = sin(radian) * CYLINDER_RADIUS;
		posY = -CYLINDER_HEIGHT / 2;
		posZ = cos(radian) * CYLINDER_RADIUS;
		u = (posX / CYLINDER_RADIUS) + 0.5f;
		v = -(posZ / CYLINDER_RADIUS) + 0.5f;

		vtx[VTX_TOP_SURFACE + i] = { {posX,posY,posZ},{u,v} };
	}

	// ����

	//TOOD==>u,v�̒���

	for (int i = 0; i < VTX_SIDE_SURFACE; i++)
	{
		if (i < VTX_SIDE_SURFACE / 2)
		{
			angle = (i % (VTX_SIDE_SURFACE / 2)) * (360 / CORNER_NUM);
			radian = DirectX::XMConvertToRadians(angle);
			posX = sin(radian) * CYLINDER_RADIUS;
			posY = CYLINDER_HEIGHT / 2;
			posZ = cos(radian) * CYLINDER_RADIUS;
			u = 1.0f / CORNER_NUM * (i % (VTX_SIDE_SURFACE / 2));
			v = 0.5f + -(posY / CYLINDER_HEIGHT);

			vtx[VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE + i] = { {posX,posY,posZ},{u,v} };
		}
		else
		{
			angle = (i % (VTX_SIDE_SURFACE / 2)) * (360 / CORNER_NUM);
			radian = DirectX::XMConvertToRadians(angle);
			posX = sin(radian) * CYLINDER_RADIUS;
			posY = -CYLINDER_HEIGHT / 2;
			posZ = cos(radian) * CYLINDER_RADIUS;
			u = 1.0f / CORNER_NUM * (i % (VTX_SIDE_SURFACE / 2));
			v = 0.5f + -(posY / CYLINDER_HEIGHT);

			vtx[VTX_TOP_SURFACE + VTX_BOTTOM_SURFACE + i] = { {posX,posY,posZ},{u,v} };
		}
	}

	// =============== �C���f�b�N�X�̍쐬 ===================
	// �V��
	int idx[SURFACE_CYLINDER_NUM * 3];

	for (int i = 0; i < SURFACE_TOP; i++)
	{
		idx[i * 3] = 0;
		idx[i * 3 + 1] = i + 1;
		idx[i * 3 + 2] = i + 2;
	}
	// ���
	for (int i = 0; i < SURFACE_BOTTOM; i++)
	{
		idx[(SURFACE_TOP * 3) + i * 3] = VTX_TOP_SURFACE;
		idx[(SURFACE_TOP * 3) + i * 3 + 1] = VTX_TOP_SURFACE + i + 2;
		idx[(SURFACE_TOP * 3) + i * 3 + 2] = VTX_TOP_SURFACE + i + 1;
	}
	// ����
	for (int i = 0; i < SURFACE_SIDE / 2; i++)
	{
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i)] = VTX_CIRCLE + i;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 1] = VTX_CIRCLE + (VTX_SIDE_SURFACE / 2) + i;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 2] = VTX_CIRCLE + i + 1;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 3] = VTX_CIRCLE + i + 1;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 4] = VTX_CIRCLE + (VTX_SIDE_SURFACE / 2) + i;
		idx[((SURFACE_TOP + SURFACE_BOTTOM) * 3) + (6 * i) + 5] = VTX_CIRCLE + (VTX_SIDE_SURFACE / 2) + i + 1;
	}

	// =============== �o�b�t�@�̍쐬 ===================
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);					// ���_�̐�
	desc.vtxSize = sizeof(vtx[0]);	// ���_�������̃f�[�^�T�C�Y
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);					// �C���f�b�N�X�̐�
	desc.idxSize = sizeof(int);			// �C���f�b�N�X�������̃f�[�^�T�C�Y
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	m_pObj = new MeshBuffer(desc);
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
CCylinder::CCylinder(CCylinder & Obj)
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
CCylinder::~CCylinder()
{
}

/* ========================================
   �֐��F�`��֐�
   ----------------------------------------
   ���e�F�`�揈��
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CCylinder::Draw()
{
	// =============== ���� ===============
	if (m_pObj == nullptr)	//�k���`�F�b�N
	{
		// =============== �I�� ===============
		return;	//�����I��
	}

	// =============== �`�� ===============
	m_pVS->WriteBuffer(0, m_WVP);	//��������
	m_pVS->Bind();					//���_�V�F�[�_�g�p
	m_pPS->Bind();					//�s�N�Z���V�F�[�_�g�p
	m_pObj->Draw();					//�����̕`��
}