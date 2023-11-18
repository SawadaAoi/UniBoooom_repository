/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�Q�[�W
	------------------------------------
	BossGauge.cpp
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2023/11/17 cpp,�쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "BossGauge.h"
#include "Timer.h"

// =============== �萔��` =======================
const int MAX_GAUGE = 45;	//�}�b�N�X�Q�[�W��(���b�ɏo��)


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CBossgauge::CBossgauge()
	:m_pBossGauge(nullptr)
	,m_nGaugeCnt(0)
	,m_bGaugeFull(false)
{
	//�{�X�Q�[�W�̃e�N�X�`���ǂލ���
	/*m_pBossGauge = new Texture();

	if (FAILED(m_pBossGauge->Create("Assets/Texture/Star.png")))
	{
		MessageBox(NULL, "ItemUI Star.png", "Error", MB_OK);
	}*/
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
CBossgauge::~CBossgauge()
{
	if (m_pBossGauge)
	{
		delete m_pBossGauge;
		m_pBossGauge = nullptr;
	}
}

/* ========================================
	�^�C�}�[�X�V�֐�
	----------------------------------------
	���e�F�^�C�}�[�̃J�E���g�_�E������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossgauge::Update()
{

}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�^�C�}�[�̕`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossgauge::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(1080.0f, 100.0f, 10.0f);;
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(100.0f, -100.0f));
	Sprite::SetTexture(m_pBossGauge);
	Sprite::Draw();
}
