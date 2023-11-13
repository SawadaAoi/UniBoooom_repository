/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   ������
   ---------------------------------------
   Sphere.cpp

   �쐬��	takagi

   �ύX����
   �E2023/11/05 ���� takagi
   �E2023/11/06 �R���X�g���N�^���C takagi

   ======================================== */



// =============== �C���N���[�h ===================
#include "Sphere.h"	//���g�̃w�b�_

// =============== �萔��` ===================
const int VTX_SPHERE_X_NUM = 18;	//���_�̉���̐�
const int VTX_SPHERE_Y_NUM = 18;	//���_�̏c��̐�
const int VTX_NUM = VTX_SPHERE_X_NUM * VTX_SPHERE_Y_NUM;	//���_�̑���
const int SURFACE_SPHERE_X_NUM = VTX_SPHERE_X_NUM - 1;	//����̕\�ʂ̐�(�l�p�`)
const int SURFACE_SPHERE_Y_NUM = VTX_SPHERE_Y_NUM - 1;	//�c��̕\�ʂ̐�(�l�p�`)
const int SURFACE_SPHERE_NUM = SURFACE_SPHERE_X_NUM * SURFACE_SPHERE_Y_NUM;	//�\�ʂ̑���(�l�p�`)
const float SPHERE_DIAMETER = 1.0f;	//�~�̒��a
const float SPHERE_RADIUS = SPHERE_DIAMETER / 2;	//�~�̔��a



/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
CSphere::CSphere()
{
	// =============== ���_�̍쐬 ===================
	Vertex vtx[VTX_NUM];
	float angle_XY = 0.0f;	//XY�ʂ̊p�x
	float angle_XZ = 0.0f;	//XZ�ʂ̊p�x
	float radian_XY;	//XY�ʂ̃��W�A���p
	float radian_XZ;	//XZ�ʂ̃��W�A���p
	float posX, posY, posZ;	//���_��X,Y�Z���W
	float Rate_XZ;		//XZ�̍��W��Y���W�ɂ���Ē������鐔
	float u, v;			//�e�N�X�`����\��t����uv���W	��u�����Av���c

	for (int i = 0; i < VTX_SPHERE_Y_NUM; i++)	//���_�̏c��̌J��Ԃ�
	{
		radian_XY = DirectX::XMConvertToRadians(angle_XY);
		posY = cosf(radian_XY) * SPHERE_RADIUS;		//XY�ʂ̃��W�A���p����Y���W������o��
		Rate_XZ = sin(radian_XY);	//���̂�1�ԑ傫����Ԃ�1.0�Ƃ����Ƃ���Y���W�ɉ������~���̊���

		for (int j = 0; j < VTX_SPHERE_X_NUM; j++)	//���_�̉���̌J��Ԃ�
		{
			radian_XZ = DirectX::XMConvertToRadians(angle_XZ);	//XZ�ʂ̃f�B�O���[�p�����W�A���p�ɕϊ�
			posX = sinf(radian_XZ) * Rate_XZ * SPHERE_RADIUS;		//XZ�ʂ�X���W���o���Ă���Y���W�ɉ����Ē���
			posZ = cosf(radian_XZ) * Rate_XZ * SPHERE_RADIUS;		//XZ�ʂ�Z���W���o���Ă���Y���W�ɉ����Ē���
			u = (1.0f / SURFACE_SPHERE_X_NUM) * j;			//�ʂ̐����œ�������0.0f,�E�E�E,1.0f�̐��ɂȂ�
			v = 0.5f - (posY / SPHERE_DIAMETER);	//Y���W�𒼌a�Ŋ���-0.5f�`0.5f�ɒ����Ă���0.0f�`1.0f�ɒ���

			vtx[i * VTX_SPHERE_X_NUM + j] = { {posX,posY,posZ},{u, v} };	//�o�����ϐ���vtx�ɓ����
			angle_XZ += 360.0f / SURFACE_SPHERE_X_NUM;	//XZ�ʂ̊p�x��ʂ̐��œ��������������i�߂�
		}
		angle_XY += 180.0f / SURFACE_SPHERE_Y_NUM;	//sin��0���`180����0.0�`1.0f�ɂȂ邽��
		angle_XZ = 0;	//XZ��360�𒴂��Ȃ��悤�ɒ���
	}

	// =============== �C���f�b�N�X�̍쐬 ===================
	int idx[SURFACE_SPHERE_NUM * 2 * 3];
	for (int i = 0; i < SURFACE_SPHERE_Y_NUM; i++)	//�c��̌J��Ԃ�
	{
		for (int j = 0; j < SURFACE_SPHERE_X_NUM; j++)	//����̌J��Ԃ�
		{
			//VTX_SPHERE_X_NUM��9�̏ꍇ{0,9,1,1,10,9,�E�E�E}�ƂȂ�
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6)] = i * VTX_SPHERE_X_NUM + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 1] = i * VTX_SPHERE_X_NUM + VTX_SPHERE_X_NUM + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 2] = i * VTX_SPHERE_X_NUM + 1 + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 3] = i * VTX_SPHERE_X_NUM + 1 + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 4] = i * VTX_SPHERE_X_NUM + VTX_SPHERE_X_NUM + j;
			idx[(i * (6 * SURFACE_SPHERE_X_NUM)) + (j * 6) + 5] = i * VTX_SPHERE_X_NUM + VTX_SPHERE_X_NUM + 1 + j;
		}
	}

	// =============== �o�b�t�@�̍쐬 ===================
	MeshBuffer::Description desc = {};
	desc.pVtx = vtx;
	desc.vtxCount = _countof(vtx);					// ���_�̐�
	desc.vtxSize = sizeof(vtx[0]);	// ���_�������̃f�[�^�T�C�Y
	desc.pIdx = idx;
	desc.idxCount = _countof(idx);					// �C���f�b�N�X�̐�
	desc.idxSize = sizeof(int);			// �C���f�b�N�X�������̃f�[�^�T�C�Y
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
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
CSphere::CSphere(CSphere & Obj)
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
CSphere::~CSphere()
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
void CSphere::Draw()
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