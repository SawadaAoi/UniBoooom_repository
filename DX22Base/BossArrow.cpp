/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�����\�����pcpp
	------------------------------------
	BossArrow.cpp
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/12/08 cpp,�쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "BossArrow.h"
#include <math.h>

// =============== �萔��` =======================
const TPos2d<float> BOSS_ARROW_POS(640.0f, 100.0f);	//�{�X�����̈ʒu�ݒ�
const float BOSS_ARROW_SIZE_X = 60.0f;				//�{�X������X�̒����ݒ�
const float BOSS_ARROW_SIZE_Y = -60.0f;				//�{�X������Y�̒����ݒ�


#if MODE_GAME_PARAMETER
#else

#endif


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
	:m_bShowArrowFlg(false)
	,m_pArrowTex(nullptr)
	,m_pos(BOSS_ARROW_POS.x, BOSS_ARROW_POS.y)
	,m_radian(0.0f)
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
	float fDistanceX;		// �|�X�ƃv���C���[��X���W�̍�
	float fDistanceZ;		// �|�X�ƃv���C���[��Z���W�̍�

	// �{�X�����݂�����A�v���C���[�ƃ{�X�̊p�x���v�Z
	if (m_pBoss->IsBossPtrExist())
	{
		fDistanceX = m_pBoss->GetBossSlimePtr(0)->GetPos().x - m_pPlayer->GetPos().x;
		fDistanceZ = m_pBoss->GetBossSlimePtr(0)->GetPos().z - m_pPlayer->GetPos().z;

		m_radian = atan2(fDistanceX, fDistanceZ);		// �v���C���[�ƃ{�X�̊p�x
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
	//�{�X�����Ȃ������� return�i�\�����܂���j
	if (!m_pBoss->IsBossPtrExist()) return;

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


