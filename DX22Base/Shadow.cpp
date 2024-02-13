/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�e�\���pcpp
	---------------------------------------
	Shadow.cpp

	�쐬�� nieda

	�ύX����
	�E2023/11/27 ���� nieda
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ� takagi
	�E2024/02/13 UsingCamera�g�p takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Shadow.h"			// ���g�̃w�b�_
#include "Sprite.h"			// �\���p�w�b�_
#define _USE_MATH_DEFINES	// �~����
#include <math.h>			// �~����
#include "UsingCamera.h"	//�J�����g�p

// =============== �萔��` ===================
const float PI = 3.14159f;					// �~����


/* ========================================
   �R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CShadow::CShadow()
	: m_bDisp(true)	// �\������
{
	// �e�e�N�X�`���Ǎ�
	m_pTextureShadow = new Texture();
	if (FAILED(m_pTextureShadow->Create("Assets/Texture/Direction/Shadow/Shadow.png")))
	{
		MessageBox(NULL, "Shadow.png", "Error", MB_OK);
	}

}

/* ========================================
   �R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   ����1�F�傫��
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CShadow::CShadow(float fScale)
   : CShadow::CShadow()
{
   m_Transform.fScale = { fScale ,fScale ,fScale };
}

/* ========================================
   �f�X�g���N�^
   ----------------------------------------
   ���e�F�j�����ɍs������
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CShadow::~CShadow()
{
	SAFE_DELETE(m_pTextureShadow);	// �e�N�X�`���j��
}

/* ========================================
   �X�V�����֐��֐�
   ----------------------------------------
   ���e�F�X�V����
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CShadow::Update()
{
	// ��U����Ă݂�
	m_bDisp ^= 1;	// �\���A��\���̐؂�ւ�
}

/* ========================================
   �`�揈���֐�
   ----------------------------------------
   ���e�F�`�揈��
   ----------------------------------------
   ����1�F�v���C���[�̌��݈ʒu
   ����2�F�\������e�N�X�`���̑傫��
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CShadow::Draw(tagTransform3d m_Pos, float fScale)
{
	if (m_bDisp)	// �\���t���O��ON�̏ꍇ
	{		
		DirectX::XMMATRIX mat_shadow = DirectX::XMMatrixTranslation(m_Pos.fPos.x, m_Pos.fPos.z, m_Pos.fPos.y) * DirectX::XMMatrixRotationX(PI / 2);	// �ړ��s������߂�
		DirectX::XMFLOAT4X4 world;	// �ǂݎ��p�̍s��̐錾
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat_shadow));	// �i�[����
		Sprite::SetWorld(world);															// ���[���h�s��̐ݒ�
		Sprite::SetView(CUsingCamera::GetThis().GetCamera()->GetViewMatrix());				// �r���[�s��̐ݒ�
		Sprite::SetProjection(CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix());	// �v���W�F�N�V�����s��̐ݒ�
		Sprite::SetSize(DirectX::XMFLOAT2(fScale, fScale));		// �T�C�Y��ݒ�
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));		// UV�̈ʒu
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));		// UV�̕�����
		Sprite::SetTexture(m_pTextureShadow);					// �e�N�X�`����ݒ�
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f,1.0f,1.0f,0.6f));// �����x��������
		Sprite::Draw();											// �X�v���C�g��`��
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));// �����x��߂�(���ɉe�����o���Ȃ�����)
	}
}

/* ========================================
   �`�揈���֐�
   ----------------------------------------
   ���e�F�`�揈��
   ----------------------------------------
   ����1�F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CShadow::Draw()
{
	if (m_bDisp)	// �\���t���O��ON�̏ꍇ
	{
		DirectX::XMMATRIX mat_shadow = DirectX::XMMatrixTranslation(m_Transform.fPos.x, m_Transform.fPos.z, m_Transform.fPos.y) * DirectX::XMMatrixRotationX(PI / 2);	// �ړ��s������߂�
		DirectX::XMFLOAT4X4 world;	// �ǂݎ��p�̍s��̐錾
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat_shadow));	// �i�[����
		Sprite::SetWorld(world);															// ���[���h�s��̐ݒ�
		Sprite::SetView(CUsingCamera::GetThis().GetCamera()->GetViewMatrix());				// �r���[�s��̐ݒ�
		Sprite::SetProjection(CUsingCamera::GetThis().GetCamera()->GetProjectionMatrix());	// �v���W�F�N�V�����s��̐ݒ�
		Sprite::SetSize(DirectX::XMFLOAT2(m_Transform.fScale.x, m_Transform.fScale.z));		// �T�C�Y��ݒ�
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));		// UV�̈ʒu
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));		// UV�̕�����
		Sprite::SetTexture(m_pTextureShadow);					// �e�N�X�`����ݒ�
		Sprite::Draw();											// �X�v���C�g��`��
	}
}
