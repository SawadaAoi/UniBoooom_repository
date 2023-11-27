/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�e�\���pcpp
	---------------------------------------
	Shadow.cpp

	�쐬�� nieda

	�ύX����
	�E2023/11/27 ���� nieda

========================================== */

// =============== �C���N���[�h ===================
#include "Shadow.h"			// ���g�̃w�b�_
#include "Sprite.h"			// �\���p�w�b�_
#include "GameParameter.h"	// �萔��`�p�w�b�_


/* ========================================
   �֐��F�R���X�g���N�^
   ----------------------------------------
   ���e�F�������ɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
CShadow::CShadow()
	: m_bDisp(true)	// �\������
{
	// �e�e�N�X�`���Ǎ�
	m_pTextureShadow = new Texture();
	if (FAILED(m_pTextureShadow->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "Shadow.png", "Error", MB_OK);
	}

	m_pObject = new CObject();	// �I�u�W�F�N�g����
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
CShadow::~CShadow()
{
	SAFE_DELETE(m_pObject);			// �I�u�W�F�N�g�j��
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
}

/* ========================================
   �`�揈���֐�
   ----------------------------------------
   ���e�F�`�揈��
   ----------------------------------------
   ����1�F�v���C���[�̌��݈ʒu
   ����2�F�\������e�N�X�`���̑傫��
   ����3�F�J�����N���X�̃|�C���^
   ----------------------------------------
   �ߒl�F�Ȃ�
======================================== */
void CShadow::Draw(tagTransform3d m_Pos, float fScale, CCamera* pCamera)
{
	if (m_bDisp)	// �\���t���O��ON�̏ꍇ
	{
		// �ړ��s������߂�
		DirectX::XMMATRIX mat_shadow = DirectX::XMMatrixTranslation(m_Pos.fPos.x, m_Pos.fPos.z, m_Pos.fPos.y) * DirectX::XMMatrixRotationX(PI / 2);
		DirectX::XMFLOAT4X4 world;	// �ǂݎ��p�̍s��̐錾
		DirectX::XMStoreFloat4x4(&world, DirectX::XMMatrixTranspose(mat_shadow));	// �i�[����
		Sprite::SetWorld(world);								// ���[���h�s��̐ݒ�
		Sprite::SetView(pCamera->GetViewMatrix());				// �r���[�s��̐ݒ�
		Sprite::SetProjection(pCamera->GetProjectionMatrix());	// �v���W�F�N�V�����s��̐ݒ�
		Sprite::SetSize(DirectX::XMFLOAT2(fScale, fScale));		// �T�C�Y��ݒ�
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));		// UV�̈ʒu
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));		// UV�̕�����
		Sprite::SetTexture(m_pTextureShadow);					// �e�N�X�`����ݒ�
		Sprite::Draw();											// �X�v���C�g��`��
	}
}
