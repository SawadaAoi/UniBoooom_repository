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
#include "HP_UI.h"					
#include "DirectXTex/TextureLoad.h"		
#include "Sprite.h"						
#include "Pos3d.h"						
#include "GameParameter.h"		
#include "Player.h"

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	�����F�v���C���[��HP�̃A�h���X
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CHP_UI::CHP_UI(const int* pPlayerHp)
{

	m_pTexture[HEART_FULL] = new Texture();	// HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_FULL]->Create("Assets/Texture/HP_Full_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Full_1.png", "Error", MB_OK);
	}

	m_pTexture[HEART_NONE] = new Texture();	// ���HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_NONE]->Create("Assets/Texture/HP_Lost_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Lost_1.png", "Error", MB_OK);
	}

	m_HpState.resize(PLAYER_HP);

	m_pPlayerHp = pPlayerHp;
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
CHP_UI::~CHP_UI()
{
	SAFE_DELETE(m_pTexture[HEART_FULL]);
	SAFE_DELETE(m_pTexture[HEART_NONE]);
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
void CHP_UI::Update()
{
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
void CHP_UI::Draw()
{
	SetHpTexture();

	for (int i = 0; i < m_HpState.size(); i++)
	{
		DirectX::XMFLOAT4X4 mat[3];

		// ���[���h�s���X��Y�݂̂��l�����č쐬
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(DRAW_POSX * (i + DRAW_FIRSTPOSX) * DRAW_GAP, DRAW_POSY, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
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
		Sprite::SetSize(DirectX::XMFLOAT2(DRAW_HEIGHT, -DRAW_WIDTH));
		Sprite::SetTexture(m_pTexture[m_HpState[i]]);
		Sprite::Draw();
	}
}



void CHP_UI::SetHpTexture()
{
	for (int i = 0; i < PLAYER_HP; i++)
	{
		if (i <= *m_pPlayerHp - 1)
		{
			m_HpState[i] = HEART_FULL;
		}
		else
		{
			m_HpState[i] = HEART_NONE;
		}
	}
}
