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
	�E2023/11/19 �`�揈���A�Q�[�W�o���A���������ǉ� Tei

========================================== */

// =============== �C���N���[�h ===================
#include "BossGauge.h"
#include "Timer.h"

// =============== �萔��` =======================

#if MODE_GAME_PARAMETER
#else
const int BOSS_GAUGE_FULL_TIME = 45 * 60;		//�{�X�Q�[�WMAX�ɂȂ鎞��(���b�o��) * 60�t���[��
const int SECOND_EMPTY_BOSSGAUGE = 75 * 60;		//��̖ڂ̃{�X��Q�[�W�\������ * 60�t���[��
const TPos2d<float> BOSSGAUGE_EMPTY_POS(765.0f, 25.0f);	//�{�X�Q�[�W�i��j�̈ʒu�ݒ�
const TPos2d<float> BOSSGAUGE_FULL_POS(765.0f, 25.0f);	//�{�X�Q�[�W�i���j�̈ʒu�ݒ�

#endif


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
	:m_pBossGaugeEmpty(nullptr)
	,m_pBossGaugeFull(nullptr)
	,m_nGaugeCnt(0)
	,m_bGaugeFull(false)
	,m_bShowBossGauge(true)
{
	//�{�X�Q�[�W�̃e�N�X�`���ǂލ���
	m_pBossGaugeEmpty = new Texture();
	m_pBossGaugeFull = new Texture();
	if (FAILED(m_pBossGaugeEmpty->Create("Assets/Texture/bossgauge_empty.png")))
	{
		MessageBox(NULL, "bossgauge_empty.png", "Error", MB_OK);
	}
	if (FAILED(m_pBossGaugeFull->Create("Assets/Texture/bossgauge_full.png")))
	{
		MessageBox(NULL, "bossgauge_full.png", "Error", MB_OK);
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
CBossgauge::~CBossgauge()
{
	SAFE_DELETE(m_pBossGaugeEmpty);
	SAFE_DELETE(m_pBossGaugeFull);
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F���Ԃ��J�E���g���āA�o���̎��ԂɂȂ�����A�{�X�o��A�Q�[�W����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossgauge::Update()
{
	//�{�X�o���J�E���g
	m_nGaugeCnt++;
	if (m_nGaugeCnt == BOSS_GAUGE_FULL_TIME)
	{
		m_bGaugeFull = true;		//�Q�[�W���^��
		m_bShowBossGauge = false;	//�{�X�o���A�Q�[�W�t���O��false�ɁA�Q�[�W������

		//��TODO�{�X�����{�X�̕��Ɏ����Ă����������ŌĂԂ�
	}
	//��̖ڂ̃{�X�̃Q�[�W�\��
	if (m_nGaugeCnt == SECOND_EMPTY_BOSSGAUGE)
	{
		m_bShowBossGauge = true;
		m_nGaugeCnt = 0;
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
void CBossgauge::Draw()
{
	//�Q�[�W�\���t���Ofalse�������� return�i�\�����܂���j
	if (m_bShowBossGauge == false) return;

	//�{�X�Q�[�W�e�N�X�`���i��j
	DirectX::XMFLOAT4X4 bossempty[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldBossempty = DirectX::XMMatrixTranslation(BOSSGAUGE_EMPTY_POS.x,BOSSGAUGE_EMPTY_POS.y, 10.0f);;
	DirectX::XMStoreFloat4x4(&bossempty[0], DirectX::XMMatrixTranspose(worldBossempty));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&bossempty[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projBossempty = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&bossempty[2], DirectX::XMMatrixTranspose(projBossempty));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(bossempty[0]);
	Sprite::SetView(bossempty[1]);
	Sprite::SetProjection(bossempty[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(100.0f, -100.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pBossGaugeEmpty);
	Sprite::Draw();

	float fFillGauge = 0;
	fFillGauge = (float)m_nGaugeCnt / (float)BOSS_GAUGE_FULL_TIME;
	FillGauge(fFillGauge);
}

/* ========================================
	�Q�[�W�������֐�
	----------------------------------------
	���e�F�{�X�Q�[�W�����ʂ̕`�揈��
	----------------------------------------
	����1�F�{�X�Q�[�W���̕����`���͈�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossgauge::FillGauge(float textureRange)
{

	//�{�X�Q�[�W�e�N�X�`���i���j
	DirectX::XMFLOAT4X4 bossfull[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldBossfull = DirectX::XMMatrixTranslation(BOSSGAUGE_FULL_POS.x, BOSSGAUGE_FULL_POS.y + (50.0f - 50 * textureRange ), 10.0f);;
	DirectX::XMStoreFloat4x4(&bossfull[0], DirectX::XMMatrixTranspose(worldBossfull));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&bossfull[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projBossfull = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&bossfull[2], DirectX::XMMatrixTranspose(projBossfull));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(bossfull[0]);
	Sprite::SetView(bossfull[1]);
	Sprite::SetProjection(bossfull[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(100.0f, (-textureRange * 100) ));		//�`��傫���ݒ�
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, (1.0f - textureRange) ));		//�`���texture�͈̔͐ݒ�
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, textureRange));				//�\������texture�̑傫���ݒ�
	Sprite::SetTexture(m_pBossGaugeFull);
	Sprite::Draw();
}

