/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	StageFinishUI�p�w�b�_
	------------------------------------
	StageFinishUI.h
	------------------------------------
	�쐬��
		yamashita
	�ύX����
	�E2023/11/20 cpp�쐬 Yamashita
	�E2023/11/20 �Q�[���̃v���C��Ԃɂ����UI��\������ yamashita
	�E2023/11/20 UI���ז��Ȏ��ɔ�\���ɂł���悤�ɕύX yamashita
	�E2023/11/23 �\���t���O�擾�֐��쐬 nieda
	�E2023/11/30 �f�ޕύX nieda

========================================== */
#include "DirectXTex/TextureLoad.h"		
#include "StageFinishUI.h"
#include "DirectWrite.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"

// =============== �萔��` =======================
const int GAMECLEAR_UV_NUM_X = 5;	// �e�N�X�`���̉��̕�����
const int GAMECLEAR_UV_NUM_Y = 9;	// �e�N�X�`���̏c�̕�����
const int GAMEOVER_UV_NUM_X = 6;	// �e�N�X�`���̉��̕�����
const int GAMEOVER_UV_NUM_Y = 9;	// �e�N�X�`���̏c�̕�����

const float GAMECLEAR_UV_POS_X = 1.0f / GAMECLEAR_UV_NUM_X;		// ����UV���W�v�Z�p
const float GAMECLEAR_UV_POS_Y = 1.0f / GAMECLEAR_UV_NUM_Y;		// �c��UV���W�v�Z�p
const float GAMEOVER_UV_POS_X = 1.0f / GAMEOVER_UV_NUM_X;		// ����UV���W�v�Z�p
const float GAMEOVER_UV_POS_Y = 1.0f / GAMEOVER_UV_NUM_Y;		// �c��UV���W�v�Z�p


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�v���C���[��HP�̃|�C���^
	����1�F�������Ԃ̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CStageFinish::CStageFinish(int* pPlayerHp, int* pTimeCnt)
	:m_bDispFlg(false)
	, m_eGameState(GAME_PLAY)
	, m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	, m_bDeleteDisp(false)
	, m_pTexGameClear(nullptr)
	, m_pTexGameOver(nullptr)
	, m_fUVPos(0.0f, 0.0f)
	, m_nCntSwitch(0)
	, m_nCntW(0)
	, m_nCntH(0)
	, m_bTransition(false)
{
	m_pPlayerHp = pPlayerHp;	//�v���C���[��HP�̃|�C���^���擾
	m_pTimeCnt = pTimeCnt;		//�������Ԃ̃|�C���^���擾

	//�Q�[���N���A�̃e�N�X�`���ǂݍ���
	m_pTexGameClear = new Texture;

	if (FAILED(m_pTexGameClear->Create("Assets/Texture/StageFinish/finish.png")))
	{
		MessageBox(NULL, "GameClear.png", "Error", MB_OK);
	}

	//�Q�[���I�[�o�[�̃e�N�X�`���ǂݍ���
	m_pTexGameOver = new Texture;
	if (FAILED(m_pTexGameOver->Create("Assets/Texture/StageFinish/GameOver.png")))
	{
		MessageBox(NULL, "game_over.png", "Error", MB_OK);
	}
}

/* ========================================
	�f�X�g���N�^
	----------------------------------------
	���e�F�폜���̏���
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CStageFinish::~CStageFinish()
{
	SAFE_DELETE(m_pTexGameOver);
	SAFE_DELETE(m_pTexGameClear);
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F���t���[���s���X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStageFinish::Update()
{
	//�Q�[���N���A���Q�[���I�[�o�[�𔻒f
	//���Q�[���I����ɃN���A�ƃQ�[���I�[�o�[������ɐ؂�ւ��Ȃ��悤�Ɂu&&�v�ŁuGAME_PLAY�v��Ԃ����������ꂽ
	if (0 >= *m_pPlayerHp && m_eGameState == GAME_PLAY)
	{	//�^�C�}�[��0�ɂȂ�����N���A��ԂɑJ��

		m_bDispFlg = true;
		m_eGameState = GAME_OVER;
	}
	else if (0 >= *m_pTimeCnt && m_eGameState == GAME_PLAY)
	{	//�̗͂�0�ɂȂ�����Q�[���I�[�o�[��ԂɑJ��
		m_bDispFlg = true;
		m_eGameState = GAME_CLEAR;
	}

	if (m_eGameState == GAME_OVER)
	{
		// �^�C�g������J�ڌシ���Q�[���J�n�ɂȂ�Ȃ��悤�ɂ��鏈��
		if (!m_bDeleteDisp) { m_nCntSwitch++; }

		if (m_nCntSwitch > SWITCH_ANIM_OVER)
		{
			m_nCntSwitch = 0;		// �J�E���g��������

			m_fUVPos.x = (GAMEOVER_UV_POS_X)* m_nCntW;		// ��������UV���W�v�Z
			m_fUVPos.y = (GAMEOVER_UV_POS_Y)* m_nCntH;		// �c������UV���W�v�Z

			++m_nCntW;		// �������ɍ��W��1�i�߂�
			if (m_nCntW == GAMEOVER_UV_NUM_X)	// �e�N�X�`���̉E�[�܂ōs������ 
			{
				m_nCntW = 0;	// �J�E���g��������
				++m_nCntH;		// �c��1�i�߂�
			}

			if (m_nCntH == GAMEOVER_UV_NUM_Y)		// �e�N�X�`���̉��[�܂ōs������
			{
				m_nCntH = 0;	// �J�E���g��������
				m_nCntW = 0;
				m_bDeleteDisp = true;
				m_bTransition = true;
			}
		}
	}
	else if (m_eGameState == GAME_CLEAR)
	{
		// �^�C�g������J�ڌシ���Q�[���J�n�ɂȂ�Ȃ��悤�ɂ��鏈��
		if (!m_bDeleteDisp) { m_nCntSwitch++; }

		if (m_nCntSwitch > SWITCH_ANIM_CLEAR)
		{
			m_nCntSwitch = 0;		// �J�E���g��������

			m_fUVPos.x = (GAMECLEAR_UV_POS_X)* m_nCntW;		// ��������UV���W�v�Z
			m_fUVPos.y = (GAMECLEAR_UV_POS_Y)* m_nCntH;		// �c������UV���W�v�Z

			++m_nCntW;		// �������ɍ��W��1�i�߂�
			if (m_nCntW == GAMECLEAR_UV_NUM_X)	// �e�N�X�`���̉E�[�܂ōs������ 
			{
				m_nCntW = 0;	// �J�E���g��������
				++m_nCntH;		// �c��1�i�߂�
			}

			if (m_nCntH == GAMECLEAR_UV_NUM_Y)		// �e�N�X�`���̉��[�܂ōs������
			{
				m_nCntH = 0;	// �J�E���g��������
				m_nCntW = 0;
				m_bDeleteDisp = true;
				m_bTransition = true;
			}
		}
	}

	//�\�����ז��Ȏ��ɏ�����悤�ɂ���	<=TODO�@�Ō�ɂ͏�������
	if (IsKeyTrigger(VK_RSHIFT))
	{
		m_bDeleteDisp ^= true;
	}
}

/* ========================================
	�`��֐�
	----------------------------------------
	���e�F�`�揈��
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStageFinish::Draw()
{
	//UI�\�����Ɉē���\��
	if (m_eGameState != GAME_PLAY)
	{
		std::string txt = "�ESHIFT�� �N���A�^�Q�[���I�[�o�[��UI�\����؂�ւ�";	// TODO	��̃G���[�������������߃R�����g���e��ύX
		DirectWrite::DrawString(txt, DirectX::XMFLOAT2(0.0f, 0.0f));
	}
	if (m_bDeleteDisp) { return; }	//�ז��Ȏ���UI��\�������ɏI��

			// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);	//DSV��null����2D�\���ɂȂ�

	std::string txt;
	switch (m_eGameState)	//�Q�[���̏�Ԃɂ���ĕ���
	{
	case (GAME_PLAY):	//�Q�[�����v���C���̕`��

		break;
	case (GAME_CLEAR):	//�Q�[���N���A�̕`��

		//�s��ϊ����s���Ă���e�N�X�`�����Z�b�g���ĕ`��
		EditSprite(GAME_CLEAR);
		Sprite::SetTexture(m_pTexGameClear);
		Sprite::Draw();
		break;
	case (GAME_OVER):	//�Q�[���I�[�o�[�̕`��

		//�s��ϊ����s���Ă���e�N�X�`�����Z�b�g���ĕ`��
		EditSprite(GAME_OVER);
		Sprite::SetTexture(m_pTexGameOver);
		Sprite::Draw();
		break;
	}
}

/* ========================================
	�\���t���O�擾�֐�
	----------------------------------------
	���e�FUI�̕\���t���O�̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
bool CStageFinish::GetDispFlg()
{
	return m_bDispFlg;
}

/* ========================================
	��ʑJ�ڃt���O�擾�֐�
	----------------------------------------
	���e�F��ʑJ�ڃt���O�̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
bool CStageFinish::GetTransitionFlg()
{
	return m_bTransition;
}

/* ========================================
	�X�v���C�g�ݒ�֐�
	----------------------------------------
	���e�FUI�̕\���̐ݒ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStageFinish::EditSprite(int nState)
{
	DirectX::XMFLOAT4X4 matrix[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(STATE_POS_X, STATE_POS_Y, 0.0f);
	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(world));

	Sprite::SetSize(DirectX::XMFLOAT2(STATE_SCALE_X, -STATE_SCALE_Y));
	if (nState == GAME_OVER)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVPos.x, m_fUVPos.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(GAMEOVER_UV_POS_X, GAMEOVER_UV_POS_Y));
	}
	else if (nState == GAME_CLEAR)
	{
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_fUVPos.x, m_fUVPos.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(GAMECLEAR_UV_POS_X, GAMECLEAR_UV_POS_Y));
	}
}
