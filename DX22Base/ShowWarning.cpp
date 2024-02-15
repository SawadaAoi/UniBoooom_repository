/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�o���x����������
	------------------------------------
	ShowWarning.cpp
	------------------------------------
	�쐬��
		�A�F��
	�ύX����
	�E2024/02/11 �N���X�쐬 Tei

========================================== */

// =============== �C���N���[�h ===================
#include "ShowWarning.h"
#include "Sprite.h"
#include "UIStageManager.h"


// =============== �萔��` =======================
const TPos2d<float> WARNING_BACKGROUND_TOPPOS(640.0f, 100.0f);		//�ꖇ�ڏ�̃o�b�N�O���E���h�ʒu�ݒ�
const TPos2d<float> WARNING_BACKGROUND_TOPPOS_2(1920.0f, 100.0f);	//�񖇖ڏ�̃o�b�N�O���E���h�ʒu�ݒ�
const TPos2d<float> WARNING_TEX_TOPPOS(640.0f, 100.0f);				//�ꖇ�ڏ�̕����̈ʒu�ݒ�
const TPos2d<float> WARNING_TEX_TOPPOS_2(1920.0f, 100.0f);			//�񖇖ڏ�̕����̈ʒu�ݒ�
const TPos2d<float> WARNING_BACKGROUND_BOTPOS(640.0f, 620.0f);		//�ꖇ�ډ��o�b�N�O���E���h�ʒu�ݒ�
const TPos2d<float> WARNING_BACKGROUND_BOTPOS_2(1920.0f, 620.0f);	//�񖇖ډ��̃o�b�N�O���E���h�ʒu�ݒ�
const TPos2d<float> WARNING_TEX_BOTPOS(640.0f, 620.0f);				//�ꖇ�ډ��̕����̈ʒu�ݒ�
const TPos2d<float> WARNING_TEX_BOTPOS_2(-640.0f, 620.0f);			//�񖇖ډ��̕����̈ʒu�ݒ�
const TPos2d<float> WARNING_BACKGROUND_SIZE(1285.0f, -125.0f);		//�o�b�N�O�����h�傫���ݒ�
const TPos2d<float> WARNING_TEX_SIZE(1280.0f, -100.0f);				//�����傫���ݒ�
const TPos2d<float> WARNING_ARRANGEMENT_POS(640.0f, 360.0f);		//��z���̈ʒu�ݒ�
const TPos2d<float> WARNING_ARRANGEMENT_SIZE(315.0f, -420.0f);		//��z���傫���ݒ�
const DirectX::XMFLOAT4 WARNING_BG_COLOR(1.0f, 1.0f, 1.0f, 0.65f);	//�o�b�N�O�����h�F�ݒ�

const int WARNING_TIME_FLAME = 4.0f * 60;

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CShowWarning::CShowWarning(int nStageNum)
	: m_pWarningBG(nullptr)
	, m_pWarningTex(nullptr)
	, m_fBGMove(0.0f)
	, m_fBotTexMove(0.0f)
	, m_fTopTexMove(0.0f)
	, m_fBGAlpha(0.95f)
	, m_pBossS2(nullptr)
	, m_pBossS3(nullptr)
	, m_fArrangementSizeAdjust(WARNING_ARRANGEMENT_SIZE.x / 2, WARNING_ARRANGEMENT_SIZE.y / 2)	// �ύX�ʂ͌��̃T�C�Y�̔����i�ŏ��o�鎞�͌��̃T�C�Y��1.5�{
	, m_fArrangementAlpha(0.0f)
	, m_nStageNum(nStageNum)
	, m_bDispFlg(false)
	, m_nDispCnt(0)
{
	// �e�N�X�`���ǂݍ���
	m_pWarningBG = new Texture;
	if (FAILED(m_pWarningBG->Create("Assets/Texture/Warning/obi.png")))
	{
		MessageBox(NULL, "WarningBG.png", "Error", MB_OK);
	}
	m_pWarningTex = new Texture;
	if (FAILED(m_pWarningTex->Create("Assets/Texture/Warning/WARNING_4.png")))
	{
		MessageBox(NULL, "WarningTex.png", "Error", MB_OK);
	}
	m_pBossS2 = new Texture;
	if (FAILED(m_pBossS2->Create("Assets/Texture/Warning/Lv2.png")))
	{
		MessageBox(NULL, "WarningBoss2.png", "Error", MB_OK);
	}
	m_pBossS3 = new Texture;
	if (FAILED(m_pBossS3->Create("Assets/Texture/Warning/Lv3.png")))
	{
		MessageBox(NULL, "WarningBoss3.png", "Error", MB_OK);
	}
	
}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CShowWarning::~CShowWarning()
{

	SAFE_DELETE(m_pWarningBG);
	SAFE_DELETE(m_pWarningTex);
}

/* ========================================
   �X�V�����֐�
   -------------------------------------
   ���e�F�X�V����
   -------------------------------------
   �����F�Ȃ�
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::Update()
{
	if (m_bDispFlg)
	{
		//---�x���o�b�N�O�����h�ƕ����̈ړ�---
		// �т̕���
		m_fBGMove--;
		if (m_fBGMove <= -1280.0f)
		{
			m_fBGMove = 0.0f;
		}

		// �����̕���
		m_fTopTexMove -= 1.5f;
		if (m_fTopTexMove <= -1280.0f)
		{
			m_fTopTexMove = 0.0f;
		}
		m_fBotTexMove += 1.5f;
		if (m_fBotTexMove >= 1280.0f)
		{
			m_fBotTexMove = 0.0f;
		}

		m_nDispCnt++;

		// �`�掞�Ԃ��߂��Ă�����
		if (WARNING_TIME_FLAME < m_nDispCnt)
		{
			m_bDispFlg = false;	// �`��I��
			m_pUIMng->StopSE(CUIStageManager::SE_BOSS_WARNING);
		}

	}

	
}

/* ========================================
   �`�揈���֐�
   -------------------------------------
   ���e�F�`�揈��
   -------------------------------------
   �����F�Ȃ�
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::Draw()
{
	//�{�X�o�����4�b�Ԍx���o��		 
	//-��z������-
	if (m_bDispFlg)
	{
		ArrangementAdjust();	// ��z���T�C�Y�ƃ��l�ύX									    				

		// ��z���摜(�X�e�[�W���Ƃɕς���)
		switch (m_nStageNum)
		{
		case 2:
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, m_pBossS2);

			break;

		case 3:
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, m_pBossS3);

			break;
		}


		// �㔼���̌x���`��
		DrawWarningBG(WARNING_BACKGROUND_TOPPOS, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningBG(WARNING_BACKGROUND_TOPPOS_2, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningTex(WARNING_TEX_TOPPOS, WARNING_TEX_SIZE, m_fTopTexMove);
		DrawWarningTex(WARNING_TEX_TOPPOS_2, WARNING_TEX_SIZE, m_fTopTexMove);

		// �������̌x���`��
		DrawWarningBG(WARNING_BACKGROUND_BOTPOS, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningBG(WARNING_BACKGROUND_BOTPOS_2, WARNING_BACKGROUND_SIZE, m_fBGMove);
		DrawWarningTex(WARNING_TEX_BOTPOS, WARNING_TEX_SIZE, m_fBotTexMove);
		DrawWarningTex(WARNING_TEX_BOTPOS_2, WARNING_TEX_SIZE, m_fBotTexMove);

	}

}

/* ========================================
   �x���w�i�`��֐�
   -------------------------------------
   ���e�F�x���̔w�i�i�сj�̕`�揈��
   -------------------------------------
   ����1�F�`����W(x,y)
   ����2�F�`��T�C�Y(x,y)
   ����3�F�`��ړ���(float)
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::DrawWarningBG(TPos2d<float> fpos, TPos2d<float> fsize, float xMove)
{
	//--�x���̔w�i����--
	DirectX::XMFLOAT4X4 warningbg[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldWarningBG = DirectX::XMMatrixTranslation(fpos.x + xMove, fpos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&warningbg[0], DirectX::XMMatrixTranspose(worldWarningBG));
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&warningbg[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projWarningBG = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&warningbg[2], DirectX::XMMatrixTranspose(projWarningBG));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(warningbg[0]);
	Sprite::SetView(warningbg[1]);
	Sprite::SetProjection(warningbg[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(fsize.x, fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(WARNING_BG_COLOR));
	Sprite::SetTexture(m_pWarningBG);
	Sprite::Draw();
}

/* ========================================
   �x�������`��֐�
   -------------------------------------
   ���e�F�x���̕����̕`�揈��
   -------------------------------------
   ����1�F�`����W(x,y)
   ����2�F�`��T�C�Y(x,y)
   ����3�F�`��ړ���(float)
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::DrawWarningTex(TPos2d<float> fpos, TPos2d<float> fsize, float xMove)
{

	//--�x���̕�������--
	DirectX::XMFLOAT4X4 warningTex[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldWarningTEX = DirectX::XMMatrixTranslation(fpos.x + xMove, fpos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&warningTex[0], DirectX::XMMatrixTranspose(worldWarningTEX));
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&warningTex[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projWarningTEX = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&warningTex[2], DirectX::XMMatrixTranspose(projWarningTEX));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(warningTex[0]);
	Sprite::SetView(warningTex[1]);
	Sprite::SetProjection(warningTex[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(fsize.x, fsize.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pWarningTex);
	Sprite::Draw();
}

/* ========================================
   �x����z���`��֐�
   -------------------------------------
   ���e�F�x���̎�z���̕`�揈��
   -------------------------------------
   ����1�F�`����W(x,y)
   ����2�F�`��T�C�Y(x,y)
   ����3�F�g���e�N�X�`��(Texture*)
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, Texture* pBoss)
{
	//--�x���̎�z������--
	DirectX::XMFLOAT4X4 warningArrangement[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	DirectX::XMMATRIX worldWarningArrangement = DirectX::XMMatrixTranslation(fpos.x, fpos.y, 0.0f);
	DirectX::XMStoreFloat4x4(&warningArrangement[0], DirectX::XMMatrixTranspose(worldWarningArrangement));
	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&warningArrangement[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX projWarningArrangement = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&warningArrangement[2], DirectX::XMMatrixTranspose(projWarningArrangement));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(warningArrangement[0]);
	Sprite::SetView(warningArrangement[1]);
	Sprite::SetProjection(warningArrangement[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(WARNING_ARRANGEMENT_SIZE.x + fsize.x, WARNING_ARRANGEMENT_SIZE.y + fsize.y));	// ���̃T�C�Y�{�ϓ���
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_fArrangementAlpha));
	Sprite::SetTexture(pBoss);
	Sprite::Draw();
}

/* ========================================
   ��z���`�撲���֐�
   -------------------------------------
   ���e�F��z�������̃T�C�Y�ƃ��u�̕ύX����
   -------------------------------------
   �����F�Ȃ�
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::ArrangementAdjust()
{
	// ��z���̃��l�ύX
	m_fArrangementAlpha += 0.1;
	if (m_fArrangementAlpha >= 0.95f)
	{
		m_fArrangementAlpha = 0.95f;        // 0.9�ɉz������0.9�ɂ���
	}

	// ��z���̃T�C�Y�ϓ��ʒ���
	m_fArrangementSizeAdjust.x -= 7.5f;
	m_fArrangementSizeAdjust.y += 10.0f;
	if (m_fArrangementSizeAdjust.x <= 0)
	{
		m_fArrangementSizeAdjust.x = 0;
	}
	if (m_fArrangementSizeAdjust.y >= 0)
	{
		m_fArrangementSizeAdjust.y = 0;
	}
}


/* ========================================
   �{�X�x���`��J�n�֐�
   -------------------------------------
   ���e�F�{�X�x���`����J�n����
   -------------------------------------
   ����1�F�Ȃ�
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::StartShowWarning()
{
	if (m_nStageNum == 1) return;
	m_bDispFlg = true;
	m_pUIMng->PlaySE(CUIStageManager::SE_BOSS_WARNING);
}

/* ========================================
	UI�}�l�[�W���[�|�C���^�Z�b�^�[�֐�
	----------------------------------------
	���e�FUI�}�l�[�W���[�|�C���^���Z�b�g����
	----------------------------------------
	����1�FUI�}�l�[�W���[�|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CShowWarning::SetUIStageManagerPtr(CUIStageManager * pUIMng)
{
	m_pUIMng = pUIMng;
}

/* ========================================
   �\�����t���O�擾�֐�
   -------------------------------------
   ���e�F�\�������ǂ����̃t���O���擾����
   -------------------------------------
   ����1�F�Ȃ�
   -------------------------------------
   �ߒl�Ftrue=�\����/false=��\��
=========================================== */
bool CShowWarning::GetDispFlg()
{
	return m_bDispFlg;
}
