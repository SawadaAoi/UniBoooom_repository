/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem�pcpp
	------------------------------------
	HealItem.cpp
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/23 cpp�쐬 yamashita
========================================== */

#include "HealItem.h"
#include "DirectWrite.h"

// =============== �萔��` =====================
const float HEAL_ITEM_SCALE_X = 1.0f;		//�A�C�e���̃X�P�[��X
const float HEAL_ITEM_SCALE_Y = 1.0f;		//�A�C�e���̃X�P�[��Y
const float HEAL_ITEM_SCALE_Z = 1.0f;		//�A�C�e���̃X�P�[��Z
const int	HEALITEM_DELETE_TIME = 5 * 60;	//�A�C�e����������܂ł̎���

/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�v���C���[�̍��W�|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CHealItem::CHealItem()
	:m_pModel(nullptr)
	, m_pVS(nullptr)
	, m_pCamera(nullptr)
{
	//���_�V�F�[�_�ǂݍ���
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}
	//���̃��f���ǂݍ���
	m_pModel = new Model;
	if (!m_pModel->Load("Assets/Model/heart/heart.FBX", 0.01f, Model::XFlip)) {		//�{���Ɣ��]�͏ȗ���
		MessageBox(NULL, "floor", "Error", MB_OK);	//�����ŃG���[���b�Z�[�W�\��
	}
	m_pModel->SetVertexShader(m_pVS);
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
CHealItem::~CHealItem()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);

	for (auto i = m_healItem.begin(); i != m_healItem.end();)
	{
		i = m_healItem.erase(i);
	}
	m_healItem.clear();
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
void CHealItem::Update()
{
	for (auto i = m_healItem.begin(); i != m_healItem.end();)
	{
		if (i->m_bUse == true)
		{
			//�J�E���g����
			i->m_Cnt++;
			float radian = i->m_Cnt % 360;
			i->m_Transform.fPos.y = sin(DirectX::XMConvertToRadians((float)radian)) * 0.5f;	//�㉺�ɂ���炷��
			i->m_Transform.fRadian.y = DirectX::XMConvertToRadians((float)radian);			//Y���ł��邭���]����

			//�J�E���g�����ȏ�Ȃ����
			if (i->m_Cnt >= HEALITEM_DELETE_TIME) { i->m_bUse = false; }

			i++;	//���̃R���e�i�Ɉړ�
		}
		else	//bUse��false�Ȃ����
		{
			//�������Ď����I�Ɏ��̃R���e�i�Ɉړ�
			i = m_healItem.erase(i);
		}


		
	}
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
void CHealItem::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	for (auto i = m_healItem.begin();i != m_healItem.end(); i++)
	{
		//Transform�̊֐����g���Ɗp�x�̌v�Z��X��Y��Z�̏��Ԃ���Y��X��Z�̏��Ԃɂ��������ߎ蓮�ŕϊ��s���������
		DirectX::XMMATRIX worldMat;
		worldMat = DirectX::XMMatrixScaling(i->m_Transform.fScale.x, i->m_Transform.fScale.y, i->m_Transform.fScale.z) *	//�g�k
			DirectX::XMMatrixRotationY(i->m_Transform.fRadian.y) * DirectX::XMMatrixRotationX(i->m_Transform.fRadian.x) *	//Y��]��X��]
			DirectX::XMMatrixTranslation(i->m_Transform.fPos.x, i->m_Transform.fPos.y, i->m_Transform.fPos.z);				//�ړ�
		worldMat = DirectX::XMMatrixTranspose(worldMat);	//�]�u
		DirectX::XMFLOAT4X4 a;					//mat[0]�ɓ����ϐ�
		DirectX::XMStoreFloat4x4(&a, worldMat);	//Matrix�^����float4x4�ɕϊ�

		
		//mat[0] = i->m_Transform.GetWorldMatrixSRT();
		mat[0] = a;
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
   �q�[���A�C�e�������֐�
   ----------------------------------------
   ���e�F
   ----------------------------------------
   �����F����������W
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CHealItem::Create(TPos3d<float> pos)
{
	//�\���̂̕ϐ���������
	HEAL_ITEM healItem;
	healItem.m_Transform.fPos = pos;
	healItem.m_Transform.fScale = { HEAL_ITEM_SCALE_X ,HEAL_ITEM_SCALE_Y ,HEAL_ITEM_SCALE_Z };
	healItem.m_Transform.fRadian = {DirectX::XMConvertToRadians(70.0f),0.0f,0.0f};
	healItem.m_Cnt = 0;
	healItem.m_bUse = true;

	//�����������ϐ����R���e�i�Ɋi�[
	m_healItem.push_back(healItem);
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
void CHealItem::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}
