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
	�E2024/02/20 ��z���`�撲�� Tei

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
const float DRAWING_MAX_LEFT_POS = -1280.0f;						//�`��̍��[
const float DRAWING_MAX_RIGHT_POS = 1280.0f;						//�`��̉E�[
const float TEX_MOVE_SPEED = 1.5f;									//�x�������ړ��X�s�[�h
const float ARRANGEMENT_ALPHA = 0.95f;								//��z���`��̃��l
const float ALPHA_ADD = 0.1f;										//���u���Z�l
const TPos2d<float> ARRANGEMENT_SIZE_ADD(7.5f, 10.0f);				//��z���T�C�Y���Z�l
const int TIME_OF_ARRANGEMENT_PER_CHANGE = 120;						//��z�����g�k�A�F���ς̃t���[����
const TPos2d<float> ARRANGEMENT_SCALE_ADD(1.5f, 2.0f);				//��z���g�k���Z�l
const float COLOR_CHANGE_ADD = 0.02f;								//��z���F���ς̉��Z�l
const int WARNING_TIME_FLAME = 4.0f * 60;							//�x���̕\������

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
	, m_fBGAlpha(ARRANGEMENT_ALPHA)
	, m_pBossS2(nullptr)
	, m_pBossS3(nullptr)
	, m_fArrangementSizeAdjust(WARNING_ARRANGEMENT_SIZE.x / 2, WARNING_ARRANGEMENT_SIZE.y / 2)	// �ύX�ʂ͌��̃T�C�Y�̔����i�ŏ��o�鎞�͌��̃T�C�Y��1.5�{
	, m_fArrangementAlpha(0.0f)
	, m_nStageNum(nStageNum)
	, m_bDispFlg(false)
	, m_nDispCnt(0)
	, m_fArrangementColorAdjust(0.0f)
	, m_fArrangementScaleAdjust(0.0f, 0.0f)
	, m_nArrangementCnt(0)
	, m_bArrangementShow(false)
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
		if (m_fBGMove <= DRAWING_MAX_LEFT_POS)
		{
			m_fBGMove = 0.0f;
		}

		// �����̕���
		m_fTopTexMove -= TEX_MOVE_SPEED;
		if (m_fTopTexMove <= DRAWING_MAX_LEFT_POS)
		{
			m_fTopTexMove = 0.0f;
		}
		m_fBotTexMove += TEX_MOVE_SPEED;
		if (m_fBotTexMove >= DRAWING_MAX_RIGHT_POS)
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
		// �\������O�ƌ�̊g�k��ʁX�ɂ���
		if (!m_bArrangementShow)
		{
			ShowArrangement();	// ��z���T�C�Y�ƃ��l�ύX	
		}
		else
		{
			//�F�A�T�C�Y����
			ArrangementColorMotion(COLOR_CHANGE_ADD, TIME_OF_ARRANGEMENT_PER_CHANGE, ARRANGEMENT_ALPHA);
			ArrangementScaleMotion(ARRANGEMENT_SCALE_ADD, TIME_OF_ARRANGEMENT_PER_CHANGE, ARRANGEMENT_ALPHA);
		}

		// ��z���摜(�X�e�[�W���Ƃɕς���)
		switch (m_nStageNum)
		{
		case 2:
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust, 
				m_fArrangementScaleAdjust, m_pBossS2);

			break;

		case 3:
			DrawWarningBoss(WARNING_ARRANGEMENT_POS, m_fArrangementSizeAdjust,	
				m_fArrangementScaleAdjust, m_pBossS3);

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
   ����3�F�g�k�T�C�Y(x,y)
   ����4�F�g���e�N�X�`��(Texture*)
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::DrawWarningBoss(TPos2d<float> fpos, TPos2d<float> fsize, TPos2d<float> fScale, Texture* pBoss)
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
	Sprite::SetSize(DirectX::XMFLOAT2(WARNING_ARRANGEMENT_SIZE.x + fsize.x + fScale.x, WARNING_ARRANGEMENT_SIZE.y + fsize.y + fScale.y));	// ���̃T�C�Y�{�ϓ���
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f - m_fArrangementColorAdjust, 1.0f - m_fArrangementColorAdjust, m_fArrangementAlpha));
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
void CShowWarning::ShowArrangement()
{
	// ��z���̃��l�ύX
	m_fArrangementAlpha += ALPHA_ADD;
	if (m_fArrangementAlpha >= ARRANGEMENT_ALPHA)
	{
		m_fArrangementAlpha = ARRANGEMENT_ALPHA;        // 0.95�ɉz������0.95�ɂ���
	}

	// ��z���̃T�C�Y�ϓ��ʒ���
	m_fArrangementSizeAdjust.x -= ARRANGEMENT_SIZE_ADD.x;
	m_fArrangementSizeAdjust.y += ARRANGEMENT_SIZE_ADD.y;
	if (m_fArrangementSizeAdjust.x <= 0)
	{
		m_fArrangementSizeAdjust.x = 0;
	}
	if (m_fArrangementSizeAdjust.y >= 0)
	{
		m_fArrangementSizeAdjust.y = 0;
	}

	// �\��������A�\���t���Otrue��
	m_bArrangementShow = true;
}

/* ========================================
   ��z���F�ϊ��֐�
   -------------------------------------
   ���e�F��z���̐F�̕ύX����
   -------------------------------------
   ����1�F�F�̒����l(float)
   ����2�F���̐F�ϊ��̃t���[����(int)
   ����3�F�`��̃��l(float)
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::ArrangementColorMotion(float fColor, int nFlame, float fAlpha)
{
	m_nArrangementCnt++;								// ��z���`��J�E���g���Z
	m_fArrangementAlpha = fAlpha;						
	if (m_nArrangementCnt % nFlame <= (nFlame / 2) - 1)	// �ݒ肵���t���[�����̑O�����Z(�F�Ԃ��Ȃ�)�A�㔼���Z(�F���ɖ߂�)
	{
		m_fArrangementColorAdjust += fColor;
	}
	else
	{
		m_fArrangementColorAdjust -= fColor;
	}
}

/* ========================================
   ��z���g�k�֐�
   -------------------------------------
   ���e�F��z���̊g�k����
   -------------------------------------
   ����1�F�F�̒����l(float)
   ����2�F���̐F�ϊ��̃t���[����(int)
   ����3�F�`��̃��l(float)
   -------------------------------------
   �ߒl�F�Ȃ�
=========================================== */
void CShowWarning::ArrangementScaleMotion(TPos2d<float> fSize, int nFlame, float fAlpha)
{
	m_fArrangementAlpha = fAlpha;
	m_fArrangementSizeAdjust.x = 0.0f;						// �`�悵����̃T�C�Y�����l0�ɂ���
	m_fArrangementSizeAdjust.y = 0.0f;					
	m_nArrangementCnt++;									// ��z���`��J�E���g���Z
	if (m_nArrangementCnt % nFlame <= (nFlame / 2) - 1)		// �ݒ肵���t���[�����̑O�����Z(�g��)�A�㔼���Z(�k��)
	{
		m_fArrangementScaleAdjust.x += fSize.x;
		m_fArrangementScaleAdjust.y -= fSize.y;
	}
	else
	{
		m_fArrangementScaleAdjust.x -= fSize.x;
		m_fArrangementScaleAdjust.y += fSize.y;
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

