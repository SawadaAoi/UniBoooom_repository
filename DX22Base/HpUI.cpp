/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HP�e�N�X�`���\���pcpp
	------------------------------------
	HpUI.cpp
	------------------------------------
	�쐬��	�m�}����

	�ύX����
	�E2023/11/16 �V�K�쐬 �m�}����

========================================== */

// =============== �C���N���[�h ===================
#include "HpUI.h"
#include "DirectXTex/TextureLoad.h"
#include "Sprite.h"

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CHpUI::CHpUI()
{
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/Star.png")))
	{
		MessageBox(NULL, "ItemUI Star.png", "Error", MB_OK);
	}
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CHpUI::~CHpUI()
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�`��̍X�V����
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CHpUI::Update()
{
	m_bDisp ^= 1;
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�e�N�X�`���̕`�揈��
	-------------------------------------
	����1�F�\���ʒu��X���W
	-------------------------------------
	����2�F�\���ʒu��Y���W
	-------------------------------------
	����3�F�\������e�N�X�`���̏c��
	-------------------------------------
	����4�F�\������e�N�X�`���̉���
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CHpUI::Draw(float posX, float posY, float h, float w)
{
	DirectX::XMFLOAT4X4 mat[3];

	// ���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(posX, posY, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	// ���̍s���2D�̃X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);	// ���t���e�s���ݒ�
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	// �X�v���C�g�̐ݒ�
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(h, -w));
	Sprite::SetTexture(m_pTexture);
	if (m_bDisp) { Sprite::Draw(); }
}
