/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HealItem�p�w�b�_
	------------------------------------
	HealItem.cpp
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/27 cpp�쐬 yamashita
	�E2023/11/28 �㉺�ɓ���������ǉ� yamashita
	�E2023/11/28 ��]�̋�����ǉ� yamashita
	�E2023/12/07 �Q�[���p�����[�^�Ɉˑ����Ă����̂ŏC���E�Q�[���p�����[�^����萔�ړ��E�s�v�萔���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "HealItem.h"

// =============== �萔��` ===================
const float HEAL_ITEM_SCALE_X = 1.5f;		//�@�A�C�e���̃X�P�[��X
const float HEAL_ITEM_SCALE_Y = 1.5f;		//�@�A�C�e���̃X�P�[��Y
const float HEAL_ITEM_SCALE_Z = 1.5f;		//�@�A�C�e���̃X�P�[��Z
const float	HEALITEM_ANGLE_X = 50.0f;		//�@�񕜃A�C�e���̊p�x
const float	HEALITEM_MOVE_INTERVAL = 4.0f;		//  �A�j���[�V�����̎���
const int	COUNT_UP = 6;						//  1�b��360�ɂȂ�悤�ɒ���
const float	HEALITEM_MOVE_Y = 0.5f;				//  �A�C�e���̏㉺�ɗh��鍂��(-1�`1�܂ł��ړ�����̂ňړ��ʂ�2)
const float	HEALITEM_HEIGHT = HEALITEM_MOVE_Y;	//  �񕜃A�C�e���̏����̍���

/* ========================================
   �R���X�g���N�^
   ----------------------------------------
   ���e�F�J�n����
   ----------------------------------------
   �����F����������W�A���f���̃|�C���^�A���_�V�F�[�_�[�̃|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CHealItem::CHealItem(TPos3d<float> pos, Model* pModel, VertexShader* pVS)
	:m_fAnimeCnt(0.0f)
	,m_pModel(nullptr)
	,m_pVS(nullptr)
{
	m_Transform.fPos = pos;
	m_Transform.fPos.y = HEALITEM_HEIGHT;		//�\������鏉���̍���
	m_Transform.fScale = { HEAL_ITEM_SCALE_X, HEAL_ITEM_SCALE_Y, HEAL_ITEM_SCALE_Z };	//�T�C�Y����
	float radY = DirectX::XMConvertToRadians(HEALITEM_ANGLE_X);
	m_Transform.fRadian = { radY,0.0f,0.0f };	//�p�x������
	m_Sphere.fRadius = 1.0f;

	m_pModel = pModel;
	m_pVS = pVS;
	m_pModel->SetVertexShader(m_pVS);
}

/* ========================================
   �f�X�g���N�^
   ----------------------------------------
   ���e�F�I������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CHealItem::~CHealItem()
{

}

/* ========================================
   �X�V����
   ----------------------------------------
   ���e�F���t���[���Ăяo������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CHealItem::Update()
{
	m_fAnimeCnt += COUNT_UP / HEALITEM_MOVE_INTERVAL;					//1�b60�t���[����360�J�E���g
	int degree = int(m_fAnimeCnt) % 360;								//360(���)�ŏ�]���Z
	float rad = DirectX::XMConvertToRadians((float)degree);				//���W�A���p�ɕϊ�
	m_Transform.fPos.y = cosf(rad) * HEALITEM_MOVE_Y + HEALITEM_HEIGHT;	//cos��1�`-1���܂��
	m_Transform.fRadian.y = rad;										//cos��1�`-1�ŉ�]����
}

/* ========================================
   �`�揈��
   ----------------------------------------
   ���e�F���t���[���Ăяo������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CHealItem::Draw()
{
	if (!m_pCamera) { return; }

	//-- ���f���\��
	if (m_pModel) {
		DirectX::XMFLOAT4X4 mat[3];

		//�g�k�A��]�A�ړ�(Y����]���ɂ����������̂�SRT�͎g��Ȃ�)
		DirectX::XMStoreFloat4x4(&mat[0],DirectX::XMMatrixTranspose(DirectX::XMMatrixScaling(m_Transform.fScale.x, m_Transform.fScale.y, m_Transform.fScale.z)
			* DirectX::XMMatrixRotationY(m_Transform.fRadian.y)
			* DirectX::XMMatrixRotationX(m_Transform.fRadian.x) * DirectX::XMMatrixRotationZ(m_Transform.fRadian.z)
			* DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.y, m_Transform.fPos.z)));
		mat[1] = m_pCamera->GetViewMatrix();
		mat[2] = m_pCamera->GetProjectionMatrix();

		//-- �s����V�F�[�_�[�֐ݒ�
		m_pVS->WriteBuffer(0, mat);

		// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
		RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
		DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
		SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

		m_pModel->Draw();
	}
}
