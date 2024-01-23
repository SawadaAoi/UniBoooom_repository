/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	HP�e�N�X�`���\���Ǘ��p�\�[�X
	------------------------------------
	HP_UI.cpp
	------------------------------------
	�쐬��	nieda

	�ύX����
	�E2023/11/16 �V�K�쐬 nieda
	�E2023/11/28 ����������悤�ɏC�� sawada
	�E2023/11/29 �A�j���[�V�����ǉ� nieda
	�E2023/12/01 ������HP�A�j���[�V�����ǉ� nieda
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ��E�s�v������ takagi
	�E2024/01/21 �R�����g���C�EMessageBox���P takagi

========================================== */

// =============== �C���N���[�h ===================
#include "HP_UI.h"					
#include "DirectXTex/TextureLoad.h"		
#include "Sprite.h"						
#include "Pos3d.h"						
#include "GameParameter.h"		
#include "Player.h"

// =============== �萔��` ===================
const TTriType<float> HP_UI_POS = { 45.0f, 50.0f ,0.0f };	// �e�N�X�`���̏c���A����
const TTriType<float> HP_UI_SIZE = { 60.0f, 55.0f ,0.0f };	// �e�N�X�`���̏c���A����
const float DRAW_WIDTH = 65.0f;	// �e�N�X�`���̉���
const int SWITCH_HP_ANIM = 0;				// �A�j���[�V�����؂�ւ��̊Ԋu
const int HP_ANIM_WIDTH_NUM_MAX = 6;		// ���������ő吔
const int HP_ANIM_HEIGHT_NUM_MAX = 6;		// �c�������ő吔
const float HP_ANIM_SIZEX = 1.0f / HP_ANIM_WIDTH_NUM_MAX;	// �e�N�X�`���������T�C�Y
const float HP_ANIM_SIZEY = 1.0f / HP_ANIM_HEIGHT_NUM_MAX;	// �e�N�X�`���c�����T�C�Y
const float DRAW_ANIM_HEIGHT = HP_UI_SIZE.y + 40.0f;		// �A�j���[�V�����̕\���ʒu
const float DRAW_ANIM_WIDTH = HP_UI_SIZE.x + 40.0f;		// �A�j���[�V�����̕\���ʒu
//TODO:�����J�����g����
const float VIEW_LEFT = 0.0f;		// ��ʍ��[�̍��W
const float VIEW_RIGHT = 1280.0f;	// ��ʉE�[�̍��W�i��ʉ����j
const float VIEW_BOTTOM = 720.0f;	// ��ʉ��[�̍��W�i��ʏc���j
const float VIEW_TOP = 0.0f;		// ��ʏ�[�̍��W
const float NEAR_Z = 0.1f;			// ��ʂɎʂ�n�߂鋗��
const float FAR_Z = 10.0f;			// �ʂ�����E����

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	�����F�v���C���[��HP�̃A�h���X
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CHP_UI::CHP_UI()
	: m_bPlayAnim(false)
	, m_nPlayerOldHp(PLAYER_HP)
	, m_nCnt(0)
	, m_fUVposX(0)
	, m_fUVposY(0)
	, m_nCntWidth(0)
	, m_nCntHeight(0)
{
	m_pTexture[HEART_FULL] = new Texture();	// ���^����HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_FULL]->Create("Assets/Texture/HP_UI/HP_Full_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "HP_Full_2.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);								//�G���[�ʒm
#endif
	}

	m_pTexture[HEART_HALF] = new Texture();	// ������HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_HALF]->Create("Assets/Texture/HP_UI/HP_Half_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "HP_Half_2.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);								//�G���[�ʒm
#endif
	}

	m_pTexture[HEART_NONE] = new Texture();	// ���HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_NONE]->Create("Assets/Texture/HP_UI/HP_Lost_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "HP_Lost_2.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);								//�G���[�ʒm
#endif
	}

	m_pTexture[HEART_FH_ANIM] = new Texture();	// ���^����������HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_FH_ANIM]->Create("Assets/Texture/HP_UI/hp_FtoH_sprite_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "hp_FtoH_sprite_2.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
	}

	m_pTexture[HEART_HE_ANIM] = new Texture();	// ���������HP�̃e�N�X�`���ǂݍ���
	if (FAILED(m_pTexture[HEART_HE_ANIM]->Create("Assets/Texture/HP_UI/HP_HtoE_sprite_2.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "HP_HtoE_sprite_2.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
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
	SAFE_DELETE(m_pTexture[HEART_FH_ANIM]);
	SAFE_DELETE(m_pTexture[HEART_HE_ANIM]);
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
	if (m_nPlayerOldHp != *m_pPlayerHp)	// HP�ɕύX����������
	{
		// HP�������̂݃A�j���[�V�����Đ�
		if (m_nPlayerOldHp > *m_pPlayerHp)
		{
			m_bPlayAnim = true;		// �A�j���Đ���ON
		}

		m_nPlayerOldHp = *m_pPlayerHp;	// ���݂�HP���i�[

	}

	if (m_bPlayAnim)	// �A�j���[�V�����Đ���ON�Ȃ�
	{
		m_nCnt++;	// �J�E���g��i�߂�

		if (m_nCnt > SWITCH_HP_ANIM)	// ��莞�Ԍo�߂�����؂�ւ���
		{
			m_nCnt = 0;		// �J�E���g��������

			m_fUVposX = (HP_ANIM_SIZEX) * m_nCntWidth;		// ��������UV���W�v�Z
			m_fUVposY = (HP_ANIM_SIZEY) * m_nCntHeight;		// �c������UV���W�v�Z

			++m_nCntWidth;		// �������ɍ��W��1�i�߂�
			if (m_nCntWidth == HP_ANIM_WIDTH_NUM_MAX)	// �e�N�X�`���̉E�[�܂ōs������ 
			{
				m_nCntWidth = 0;	// �J�E���g��������
				++m_nCntHeight;		// �c��1�i�߂�
			}
			if (m_nCntHeight == HP_ANIM_HEIGHT_NUM_MAX)		// �e�N�X�`���̉��[�܂ōs����r
			{ 
				m_nCntHeight = 0;	// �J�E���g��������
				m_nCntHeight = 0; 
				m_bPlayAnim = false;	// �A�j���[�V�����Đ���OFF
			}
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
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(HP_UI_SIZE.x, -HP_UI_SIZE.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[HEART_NONE]);
		Sprite::Draw();


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
		Sprite::SetWorld(mat_Full[0]);
		Sprite::SetView(mat_Full[1]);
		Sprite::SetProjection(mat_Full[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(HP_UI_SIZE.x, -HP_UI_SIZE.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
		Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[tex]);
		Sprite::Draw();


	}

	if (m_bPlayAnim)	// �A�j���[�V�����Đ���ON�Ȃ�`�悷��
	{
		DirectX::XMFLOAT4X4 mat_Anim[3];

		// ���[���h�s���X��Y�݂̂��l�����č쐬
		DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(HP_UI_POS.x + (hpCnt * DRAW_WIDTH), HP_UI_POS.y, 0.0f);	// ���[���h�s��i�K�v�ɉ����ĕϐ��𑝂₵����A�����������L�q�����肷��j
		DirectX::XMStoreFloat4x4(&mat_Anim[0], DirectX::XMMatrixTranspose(world));

		// �r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
		DirectX::XMStoreFloat4x4(&mat_Anim[1], DirectX::XMMatrixIdentity());

		// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
		// ���̍s���2D�̃X�N���[���̑傫�������܂�
		DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, NEAR_Z, FAR_Z);	// ���t���e�s���ݒ�
		DirectX::XMStoreFloat4x4(&mat_Anim[2], DirectX::XMMatrixTranspose(proj));


		// �X�v���C�g�̐ݒ�
		Sprite::SetWorld(mat_Anim[0]);
		Sprite::SetView(mat_Anim[1]);
		Sprite::SetProjection(mat_Anim[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(DRAW_ANIM_HEIGHT, -DRAW_ANIM_WIDTH));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVposX, m_fUVposY));				
		Sprite::SetUVScale(DirectX::XMFLOAT2(HP_ANIM_SIZEX, HP_ANIM_SIZEY));
		if (*m_pPlayerHp % 2 == 0)	// HP������������ɂ���ĕ\������e�N�X�`����ύX����
		{
			Sprite::SetTexture(m_pTexture[HEART_HE_ANIM]);
		}
		else
		{
			Sprite::SetTexture(m_pTexture[HEART_FH_ANIM]);
		}
		Sprite::Draw();
	}

}

void CHP_UI::SetPlayerHp(const int * pPlayerHp)
{
	m_pPlayerHp = pPlayerHp;
}


