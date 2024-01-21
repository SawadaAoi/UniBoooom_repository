/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�����\�����p�\�[�X
	------------------------------------
	BossArrow.cpp
	------------------------------------
	�쐬��	tei

	�ύX����
	�E2023/12/08 cpp,�쐬 tei
	�E2023/12/12 �{�X�w�����\���A��] tei
	�E2023/12/14 �{�X�w�����ʒu�ʒu�v�Z�֐��ǉ� tei
	�E2024/01/21 �R�����g���C takagi

========================================== */

// =============== �C���N���[�h ===================
#include "BossArrow.h"
#include <math.h>

// =============== �萔��` =======================
const TPos2d<float> BOSS_ARROW_POS(640.0f, 360.0f);		// �{�X�����̈ʒu�ݒ�
const float BOSS_ARROW_SIZE_X = 60.0f;					// �{�X������X�̒����ݒ�
const float BOSS_ARROW_SIZE_Y = -60.0f;					// �{�X������Y�̒����ݒ�
const float OUT_OF_SCREEN_DISTANCE_RIGHT = 23.5f;		// �v���C���[����E���E�̋���
const float OUT_OF_SCREEN_DISTANCE_LEFT = -23.5f;		// �v���C���[���獶���E�̋���
const float OUT_OF_SCREEN_DISTANCE_TOP = 17.5f;			// �v���C���[����㋫�E�̋���
const float OUT_OF_SCREEN_DISTANCE_BUTTOM = -12.5f;		// �v���C���[���牺���E�̋���
const float MULTIPLE_NUM_LEFT_RIGHT = 30.0f;			// �{�X�w����󂪐^�񒆂���E���[�ɍs���K�v�Ȕ{��
const float MULTIPLE_NUM_TOP_BUTTOM = 20.0f;			// �{�X�w����󂪐^�񒆂���㉺�[�ɍs���K�v�Ȕ{��
const float ARROW_POS_ADJUST = 100.0f;					// �{�X�w�����𑼂�UI�Ɣ��Ȃ��悤�ɂ̒����l


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�Fint ���݂̎��Ԏ��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CBossArrow::CBossArrow()
	:m_bBossInsideScreen(true)
	,m_pArrowTex(nullptr)
	,m_pos(BOSS_ARROW_POS.x, BOSS_ARROW_POS.y)
	,m_radian(0.0f)
	,m_fDistanceX(0.0f)
	,m_fDistanceZ(0.0f)
{

	m_pArrowTex = new Texture();
	if (FAILED(m_pArrowTex->Create("Assets/Texture/Arrow.png")))
	{
		MessageBox(NULL, "Arrow.png", "Error", MB_OK);
	}

}

/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�j�����ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CBossArrow::~CBossArrow()
{
	SAFE_DELETE(m_pArrowTex);
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�v���C���[�ƃ{�X�̈ʒu���v�Z�A
	      ���ʂɂ���ă{�X�����w���̖��̈ʒu��ݒ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossArrow::Update()
{
	
	m_bBossInsideScreen = true;

	// �{�X�����݂�����A�v���C���[�ƃ{�X�̊p�x���v�Z
	if (m_pBoss->IsBossPtrExist())
	{
		
		// �v���C���[�ƃ{�X�̋����v�Z
		m_fDistanceX = m_pBoss->GetBossSlimePtr(0)->GetPos().x - m_pPlayer->GetPos().x;
		m_fDistanceZ = m_pBoss->GetBossSlimePtr(0)->GetPos().z - m_pPlayer->GetPos().z;
		m_radian = atan2(m_fDistanceX, m_fDistanceZ);		// �v���C���[�ƃ{�X�̊p�x
		
		// ��ʓ�����
		if ( m_fDistanceX <= OUT_OF_SCREEN_DISTANCE_LEFT || OUT_OF_SCREEN_DISTANCE_RIGHT <= m_fDistanceX)
		{
			
			m_bBossInsideScreen = false;		// ��ʊO��������false
		}
		if (m_fDistanceZ <= OUT_OF_SCREEN_DISTANCE_BUTTOM || OUT_OF_SCREEN_DISTANCE_TOP <= m_fDistanceZ)
		{
			m_bBossInsideScreen = false;		// ��ʊO��������false
		}

		ArrowMove();
	}
	
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�{�X�Q�[�W�̕`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossArrow::Draw()
{
	//�{�X�����Ȃ������� or ��ʓ��ɂ��� return�i�\�����܂���j
	if (!m_pBoss->IsBossPtrExist() || m_bBossInsideScreen) return;

	//�{�X�Q�[�W�e�N�X�`���i��j
	DirectX::XMFLOAT4X4 bossArrow[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX worldBossempty = DirectX::XMMatrixRotationZ((m_radian)) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y , 0.0f);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(10.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&bossArrow[0], DirectX::XMMatrixTranspose(worldBossempty));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&bossArrow[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projBossempty = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&bossArrow[2], DirectX::XMMatrixTranspose(projBossempty));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(bossArrow[0]);
	Sprite::SetView(bossArrow[1]);
	Sprite::SetProjection(bossArrow[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_ARROW_SIZE_X, BOSS_ARROW_SIZE_Y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pArrowTex);
	Sprite::Draw();

}

/* ========================================
	�X���C���}�l�[�W���[���Z�b�g�֐�
	----------------------------------------
	���e�F�X���C���}�l�[�W���[���|�C���^�Z�b�g
	----------------------------------------
	����1�F�X���C���}�l�[�W���[���|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CBossArrow::SetSlimeMng(CSlimeManager * mSlimeMng)
{
	m_pBoss = mSlimeMng;
}

/* ========================================
	�v���C���[���Z�b�g�֐�
	----------------------------------------
	���e�F�v���C���[���|�C���^�Z�b�g
	----------------------------------------
	����1�F�v���C���[���|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CBossArrow::SetPlayer(CPlayer * mPlayer)
{
	m_pPlayer = mPlayer;
}

/* ========================================
	���ړ��֐�
	----------------------------------------
	���e�F�{�X�w�����̈ړ��v�Z
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CBossArrow::ArrowMove()
{
	if (m_fDistanceX >= 0.0f)
	{
		m_pos.x = BOSS_ARROW_POS.x + m_fDistanceX * MULTIPLE_NUM_LEFT_RIGHT;
		if (m_pos.x >= SCREEN_WIDTH - ARROW_POS_ADJUST)
		{
			m_pos.x = SCREEN_WIDTH - ARROW_POS_ADJUST;
		}
		if (m_fDistanceZ <= 0.0f)
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;

			if (m_pos.y >= SCREEN_HEIGHT - ARROW_POS_ADJUST)
			{
				m_pos.y = SCREEN_HEIGHT - ARROW_POS_ADJUST;
			}
		}
		else
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;
			if (m_pos.y <= ARROW_POS_ADJUST)
			{
				m_pos.y = ARROW_POS_ADJUST;
			}
		}
	}
	else
	{
		m_pos.x = BOSS_ARROW_POS.x + m_fDistanceX * MULTIPLE_NUM_LEFT_RIGHT;
		if (m_pos.x <= ARROW_POS_ADJUST)
		{
			m_pos.x = ARROW_POS_ADJUST;
		}

		if (m_fDistanceZ <= 0.0f)
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;

			if (m_pos.y >= SCREEN_HEIGHT - ARROW_POS_ADJUST)
			{
				m_pos.y = SCREEN_HEIGHT - ARROW_POS_ADJUST;
			}
		}
		else
		{
			m_pos.y = BOSS_ARROW_POS.y - m_fDistanceZ * MULTIPLE_NUM_TOP_BUTTOM;
			if (m_pos.y <= ARROW_POS_ADJUST)
			{
				m_pos.y = ARROW_POS_ADJUST;
			}
		}
	}
}


