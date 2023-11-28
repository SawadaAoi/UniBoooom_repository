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
CHP_UI::CHP_UI(const int* pPlayerHp, const CCamera* pCamera)
{

	m_pTexture[HEART_FULL] = new Texture();	// HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_FULL]->Create("Assets/Texture/HP_Full_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Full_1.png", "Error", MB_OK);
	}

	m_pTexture[HEART_HALF] = new Texture();	// HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_HALF]->Create("Assets/Texture/HP_Half.png")))
	{
		MessageBox(NULL, "HpUI HP_Full_1.png", "Error", MB_OK);
	}


	m_pTexture[HEART_NONE] = new Texture();	// ���HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_NONE]->Create("Assets/Texture/HP_Lost_1.png")))
	{
		MessageBox(NULL, "HpUI HP_Lost_1.png", "Error", MB_OK);
	}

	m_pPlayerHp = pPlayerHp;

	if (*m_pPlayerHp % 2 == 0)
	{
		m_HeartNone.resize(*m_pPlayerHp / 2);
	}
	else
	{
		m_HeartNone.resize((*m_pPlayerHp / 2 + 1));
	}
	m_HeartFull.resize(*m_pPlayerHp / 2 + 1);

	for (int i = 0; i < m_HeartNone.size(); i++)
	{
		m_HeartNone[i].SetCamera(pCamera);
		m_HeartNone[i].SetSize(HP_UI_SIZE);
		m_HeartNone[i].SetTexture(m_pTexture[HEART_NONE]);
		m_HeartNone[i].SetPos(TPos3d<float>(HP_UI_POS.x + (i * DRAW_WIDTH), HP_UI_POS.y, 0.0f));

	}

	for (int i = 0; i < m_HeartFull.size(); i++)
	{
		m_HeartFull[i].SetCamera(pCamera);
		m_HeartFull[i].SetSize(HP_UI_SIZE);
		m_HeartFull[i].SetPos(TPos3d<float>(HP_UI_POS.x + (i * DRAW_WIDTH), HP_UI_POS.y, 0.0f));
		m_HeartFull[i].SetTexture(m_pTexture[HEART_FULL]); 	// �n�[�g1��

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
CHP_UI::~CHP_UI()
{
	SAFE_DELETE(m_pTexture[HEART_FULL]);
	SAFE_DELETE(m_pTexture[HEART_HALF]);
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

	HEART_STATE tex;	// �\���摜���w�肷��
	int hpCnt = 0;		// �����̎��ɐi�߂�(�\���ʒu�����p)
	for (int i = 0; i < m_HeartFull.size(); i++)
	{
		if (*m_pPlayerHp < i)
		{
			m_HeartFull[hpCnt].SetTexture(m_pTexture[HEART_NONE]);
		}

		// ��̏ꍇ
		if ((i+1) % 2 != 0)
		{
			m_HeartFull[hpCnt].SetTexture(m_pTexture[HEART_HALF]);
		}
		// �����̏ꍇ
		else
		{
			m_HeartFull[hpCnt].SetTexture(m_pTexture[HEART_FULL]); 	// �n�[�g1��
			hpCnt++;

		}
	}
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
	//for (auto i= m_HeartNone.begin();i != m_HeartNone.end(); i++)
	//{
	//	//m_HeartNone[i].Draw();
	//	i->Draw();


	//}

	for (auto i = m_HeartFull.begin(); i != m_HeartFull.end(); i++)
	{
		i->Draw();

	}

	return;

	int hpNum = 0;	// ���ڂ̃n�[�g��(�\���ʒu�����p)
	// ��̃n�[�g��\��
	for (int i = 1; i <= PLAYER_HP; i++)
	{
		// ��ڂ̃��C�t���ǂ���
		if (i % 2 != 0)
		{	
			// ���݂̕\�����C�t�ʒu���ő�l�łȂ�(�ő�l����̏ꍇ�̓n�[�g��\������(��:HP3�̏ꍇ��5�\������))
			if (i != PLAYER_HP)
			{
				continue;

			}
		}

		DirectX::XMFLOAT4X4 mat[3];

		// ���[���h�s���X��Y�݂̂��l�����č쐬
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpNum * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

		// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
		DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

		// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
		// ���̍s���2D�̃X�N���[���̑傫�������܂�
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// ���t���e�s���ݒ�
		DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

		// �X�v���C�g�̐ݒ�
		//Sprite::SetWorld(mat[0]);
		//Sprite::SetView(mat[1]);
		//Sprite::SetProjection(mat[2]);
		//Sprite::SetSize(DirectX::XMFLOAT2(DRAW_HEIGHT, -DRAW_WIDTH));
		//Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		//Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		//Sprite::SetTexture(m_pTexture[HEART_NONE]);
		//Sprite::Draw();


		hpNum++;	// �\��������ʒu��i�߂�
	}

	HEART_STATE tex;	// �\���摜���w�肷��
	int hpCnt = 0;		// �����̎��ɐi�߂�(�\���ʒu�����p)
	for (int i = 1; i <= *m_pPlayerHp; i++)
	{
		DirectX::XMFLOAT4X4 mat_Full[3];

		// ���[���h�s���X��Y�݂̂��l�����č쐬
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpCnt * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
		DirectX::XMStoreFloat4x4(&mat_Full[0], DirectX::XMMatrixTranspose(world));

		// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
		DirectX::XMStoreFloat4x4(&mat_Full[1], DirectX::XMMatrixIdentity());

		// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
		// ���̍s���2D�̃X�N���[���̑傫�������܂�
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// ���t���e�s���ݒ�
		DirectX::XMStoreFloat4x4(&mat_Full[2], DirectX::XMMatrixTranspose(proj));

		// ��̏ꍇ
		if (i % 2 != 0)
		{
			tex = HEART_HALF;	// �n�[�g����
		}
		// �����̏ꍇ
		else
		{
			tex = HEART_FULL;	// �n�[�g1��
			hpCnt++;

		}

		// �X�v���C�g�̐ݒ�
		//Sprite::SetWorld(mat_Full[0]);
		//Sprite::SetView(mat_Full[1]);
		//Sprite::SetProjection(mat_Full[2]);
		//Sprite::SetSize(DirectX::XMFLOAT2(DRAW_HEIGHT, -DRAW_WIDTH));
		//Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		//Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		//Sprite::SetTexture(m_pTexture[tex]);
		//Sprite::Draw();


	}

}


