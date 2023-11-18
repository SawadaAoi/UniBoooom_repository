/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HP�e�N�X�`���\���Ǘ��pcpp
	------------------------------------
	HpManager.cpp
	------------------------------------
	�쐬��	�m�}����

	�ύX����
	�E2023/11/16 �V�K�쐬 �m�}����

========================================== */

// =============== �C���N���[�h ===================
#include "HpManager.h"
#include "DirectXTex/TextureLoad.h"
#include "Sprite.h"
#include "Pos3d.h"
#include "GameParameter.h"

// =============== �萔��` =======================


/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	�����F�v���C���[��HP�̃A�h���X
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CHpManager::CHpManager(const int* nHp)
	:m_bLost(false)
{
	m_pnPlayerHp = nHp;		// �v���C���[��HP�̃A�h���X���i�[

	m_pTexture[0] = new Texture();
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/HP_Full_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Full_1.png", "Error", MB_OK);
	}

	m_pTexture[1] = new Texture();
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/HP_Lost_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Lost_1.png", "Error", MB_OK);
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
CHpManager::~CHpManager()
{
	SAFE_DELETE(m_pTexture[0]);
	SAFE_DELETE(m_pTexture[1]);
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�FHP�̍X�V����
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CHpManager::Update()
{
	for (int i = PLAYER_HP; i >= *m_pnPlayerHp; --i)
	{
		m_bLost ^= 1;
	}
	//��X���o�ȂǋL�q
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�FHP�̕`�揈��
	-------------------------------------
	�����F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CHpManager::Draw()
{
	for (int i = 0; i < *m_pnPlayerHp; ++i)
	{
		// HP�̃e�N�X�`����\��
		Draw2d(DRAW_POSX * (i + DRAW_FIRSTPOSX) * DRAW_GAP, DRAW_POSY, DRAW_HEIGHT, DRAW_WIDTH, m_pTexture[0]);
	}

	for (int j = PLAYER_HP; j > *m_pnPlayerHp; --j)
	{
		// HP�̃e�N�X�`����\��
		Draw2d(DRAW_POSX * (j + DRAW_FIRSTPOSX - 1) * DRAW_GAP, DRAW_POSY, DRAW_HEIGHT, DRAW_WIDTH, m_pTexture[1]);
	}
}

/* ========================================
	2D�`��֐�
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
	����5�F�\������e�N�X�`���̃|�C���^
	-------------------------------------
	�ߒl�F�Ȃ�
========================================== = */
void CHpManager::Draw2d(float posX, float posY, float h, float w, Texture *pTexture)
{
	DirectX::XMFLOAT4X4 mat[3];

	// ���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(posX, posY, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	// ���̍s���2D�̃X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// ���t���e�s���ݒ�
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	// �X�v���C�g�̐ݒ�
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(h, -w));
	Sprite::SetTexture(pTexture);
	Sprite::Draw();
}
