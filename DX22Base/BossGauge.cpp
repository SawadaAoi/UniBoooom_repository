/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�Q�[�W
	------------------------------------
	BossGauge.cpp
	------------------------------------
	�쐬��	tei

	�ύX����
	�E2023/11/17 cpp,�쐬 tei
	�E2023/11/19 �`�揈���A�Q�[�W�o���A���������ǉ� tei
	�E2023/11/22 �{�X�Q�[�W�\���̃t�F�[�h�A�E�g�ǉ��A�p�����[�^����
	�E2023/11/27 �{�X�o�������ǉ�	sawada
	�E2023/12/07 �Q�[���p�����[�^����ꕔ�萔�ړ��E�C���N���[�h�ǉ� takagi
	�E2024/01/21 �R�����g���C�EMessageBox���P takagi

========================================== */

// =============== �C���N���[�h ===================
#include "BossGauge.h"
#include "Timer.h"	//STAGE_TIME�p

// =============== �萔��` =======================
const TPos2d<float> BOSS_GAUGE_FRAME_POS(765.0f, 45.0f);		// �{�X�Q�[�W�i�g�j�̈ʒu�ݒ�
const TPos2d<float> BOSS_GAUGE_FULL_POS(765.0f, 46.5f);			// �{�X�Q�[�W�i���g�j�̈ʒu�ݒ�
const TPos2d<float> BOSS_GAUGE_FRAME_SIZE = { 60.0f ,-60.0f };	// �{�X�Q�[�W�i�g�j�̑傫��
const TPos2d<float> BOSS_GAUGE_FULL_SIZE = {					// �{�X�Q�[�W�i���g�j�̑傫��
	(6.0f / 7.0f) * BOSS_GAUGE_FRAME_SIZE.x ,
	(6.0f / 7.0f) * BOSS_GAUGE_FRAME_SIZE.y };			
const float BOSS_GAUGE_FULL_POS_Y_ADJUST = BOSS_GAUGE_FULL_SIZE.x / 2;		//�{�X�Q�[�W�i���g�j�������A�ʒu�\�����邽�߂̒�����
const float BOSS_GAUGE_FULL_SIZE_Y_ADJUST = BOSS_GAUGE_FULL_SIZE.y;			//�{�X�Q�[�W�i���g�j�������A�T�C�Y�v�Z�p�i�v�Z���ĕ\���������䗦�����錳�X�̃T�C�Y(100.0f)�j
#if MODE_GAME_PARAMETER
#else
typedef struct
{
	float startTime;	// �J�n����(�b)
	float maxTime;		// �Q�[�W�o�ߍő厞��(�b)

}BossGaugeSetParam;

const BossGaugeSetParam BOSS_GAUGE_S1[2] = { {0, 45},{75, 45} };	// �X�e�[�W1�̃{�X�Q�[�W�ݒ�
const int FADE_TIME = 5 * 60;										// �{�X�Q�[�W�����܂��Ă�������鎞��
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
CBossGauge::CBossGauge()
	: m_pTexFrame(nullptr)
	, m_pTexGauge(nullptr)
	, m_pTimer(nullptr)
{

	//�{�X�Q�[�W�̃e�N�X�`���ǂލ���
	m_pTexFrame = new Texture();
	m_pTexGauge = new Texture();
	if (FAILED(m_pTexFrame->Create("Assets/Texture/bossgauge_empty.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "bossgauge_empty.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);						//�G���[�ʒm
#endif
	}
	if (FAILED(m_pTexGauge->Create("Assets/Texture/bossgauge_full.png")))
	{
#if _DEBUG
		std::string ErrorSpot = static_cast<std::string>(__FILE__) + ".L" + std::to_string(__LINE__) + '\n' + __FUNCTION__ + "()->Error�F";	//�G���[�ӏ�
		MessageBox(nullptr, (ErrorSpot + "bossgauge_full.png�ǂݍ��ݎ��s").c_str(), "Error", MB_OK | MB_ICONERROR);							//�G���[�ʒm
#endif
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
CBossGauge::~CBossGauge()
{
	SAFE_DELETE(m_pTexFrame);
	SAFE_DELETE(m_pTexGauge);
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
void CBossGauge::Update()
{
	// �{�X�Q�[�W�z�񐔕�(�\������{�X����)
	for (auto itr = m_BossGauges.begin(); itr != m_BossGauges.end(); ++itr)
	{
		// �{�X�Q�[�W�J�n���Ԃ����O�̏ꍇ
		if ((*itr).nStartFrame >= m_pTimer->GetErapsedTime()) continue;
		// �폜�ς݂̃{�X�Q�[�W�̏ꍇ
		if ((*itr).bDelFlg == true) continue;

		// �Q�[�W���Z�l < �ő���Z�l(�ő�܂ŃQ�[�W�����܂��ĂȂ�)
		if ((*itr).nGaugeCnt < (*itr).nMaxGaugeFrame)
		{
			(*itr).nGaugeCnt++;
			(*itr).fGaugeDispPer = (float)((*itr).nGaugeCnt) / (float)(*itr).nMaxGaugeFrame;
		}
		//�@�Q�[�W���ő�܂ł��܂����ꍇ
		else
		{
			// �t�F�[�h�t���O���܂��I�t�̏ꍇ
			if ((*itr).bFadeFlg == false)
			{
				m_pSlimeMng->CreateBoss((*itr).nBossNum);	// �{�X�X���C���𐶐�
				(*itr).bFadeFlg = true;		// �t�F�[�h�t���O�I��
			}
			else
			{
				(*itr).nFadeCnt++;
				// �t�F�[�h���Ԍo�߂�����
				if (FADE_TIME <= (*itr).nFadeCnt)
				{
					(*itr).bDelFlg = true;	// �폜�t���O���I��
				}
			}
		}



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
void CBossGauge::Draw()
{
	// �{�X�Q�[�W�z�񐔕�(�\������{�X����)
	for (auto itr = m_BossGauges.begin(); itr != m_BossGauges.end(); ++itr)
	{
		// �{�X�Q�[�W�J�n���Ԃ����O�̏ꍇ
		if ((*itr).nStartFrame >= m_pTimer->GetErapsedTime()) continue;
		// �폜�ς݂̃{�X�Q�[�W�̏ꍇ
		if ((*itr).bDelFlg == true) continue;
		

		DrawFrame(itr);		// �g�̕\��
		DrawGauge(itr);		// �Q�[�W�̕\��

	}
}

/* ========================================
	�{�X�Q�[�W�g�`��֐�
	----------------------------------------
	���e�F�{�X�Q�[�W�̕`�揈��
	----------------------------------------
	����1�F�C�e���[�^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossGauge::DrawFrame(std::vector<BossGauge>::iterator itr)
{
	//�{�X�Q�[�W�e�N�X�`���i��j
	DirectX::XMFLOAT4X4 bossempty[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldBossempty = DirectX::XMMatrixTranslation(BOSS_GAUGE_FRAME_POS.x, BOSS_GAUGE_FRAME_POS.y, 0.0f);
	DirectX::XMStoreFloat4x4(&bossempty[0], DirectX::XMMatrixTranspose(worldBossempty));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&bossempty[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projBossempty = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&bossempty[2], DirectX::XMMatrixTranspose(projBossempty));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(bossempty[0]);
	Sprite::SetView(bossempty[1]);
	Sprite::SetProjection(bossempty[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_GAUGE_FRAME_SIZE.x, BOSS_GAUGE_FRAME_SIZE.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f - ((float)(*itr).nFadeCnt / (float)FADE_TIME)));
	Sprite::SetTexture(m_pTexFrame);
	Sprite::Draw();
}

/* ========================================
	�Q�[�W�����֐�
	----------------------------------------
	���e�F�{�X�Q�[�W�����ʂ̕`�揈��
	----------------------------------------
	����1�F�C�e���[�^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossGauge::DrawGauge(std::vector<BossGauge>::iterator itr)
{

	//�{�X�Q�[�W�e�N�X�`���i���j
	DirectX::XMFLOAT4X4 bossfull[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldBossfull = DirectX::XMMatrixTranslation(
		BOSS_GAUGE_FULL_POS.x, 
		BOSS_GAUGE_FULL_POS.y + (BOSS_GAUGE_FULL_POS_Y_ADJUST - (BOSS_GAUGE_FULL_POS_Y_ADJUST * (*itr).fGaugeDispPer))
		, 0.0f);
	DirectX::XMStoreFloat4x4(&bossfull[0], DirectX::XMMatrixTranspose(worldBossfull));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&bossfull[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projBossfull = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 0.0f);
	DirectX::XMStoreFloat4x4(&bossfull[2], DirectX::XMMatrixTranspose(projBossfull));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(bossfull[0]);
	Sprite::SetView(bossfull[1]);
	Sprite::SetProjection(bossfull[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(BOSS_GAUGE_FULL_SIZE.x, ((*itr).fGaugeDispPer * BOSS_GAUGE_FULL_SIZE_Y_ADJUST)));		//�`��傫���ݒ�
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, (1.0f - (*itr).fGaugeDispPer)));		//�`���texture�͈̔͐ݒ�
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, (*itr).fGaugeDispPer));				//�\������texture�̑傫���ݒ�
	Sprite::SetTexture(m_pTexGauge);
	Sprite::Draw();
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

}


/* ========================================
	�X���C���Ǘ��|�C���^�Z�b�g�֐�
	----------------------------------------
	���e�F�X���C���Ǘ��̃|�C���^���Z�b�g����
	----------------------------------------
	����1�F�X���C���Ǘ��|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossGauge::SetSlimeManager(CSlimeManager* pSlimeMng)
{
	m_pSlimeMng = pSlimeMng;
}

/* ========================================
	�{�X�Q�[�W�Z�b�g�֐�
	----------------------------------------
	���e�F�{�X�Q�[�W�����Z�b�g����
	----------------------------------------
	����1�F�J�n����
	����1�F�ő厞��
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CBossGauge::AddBossGauge(int BossNum, float fStartTime, float fMaxTime)
{
	BossGauge addPram = { 
		BossNum,
		false,					// �폜�t���O
		false,					// �t�F�[�h�t���O
		(int)fStartTime * 60,	// �J�n����Frame
		(int)fMaxTime * 60,		// �ő�lFrame
		0,						// �Q�[�W���Z
		0,						// �t�F�[�h���Z
		0.0f,					// �\������ 
	};

	m_BossGauges.push_back(addPram);	// �z��ɒǉ�

}

void CBossGauge::SetTimer(CTimer * pTimer)
{
	m_pTimer = pTimer;
}