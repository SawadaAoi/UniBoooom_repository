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

========================================== */
#include "DirectXTex/TextureLoad.h"		
#include "StageFinishUI.h"
#include "DirectWrite.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"

// =============== �萔��` =======================
const int SCALE_X = 500;	//UI�̉���
const int SCALE_Y = 100;	//UI�̏c��

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
	,m_eGameState(GAME_PLAY)
	,m_pPlayerHp(nullptr)
	, m_pTimeCnt(nullptr)
	,m_bDeleteDisp(false)
	, m_pTexGameClear(nullptr)
	,m_pTexGameOver(nullptr)
{
	m_pPlayerHp = pPlayerHp;	//�v���C���[��HP�̃|�C���^���擾
	m_pTimeCnt = pTimeCnt;		//�������Ԃ̃|�C���^���擾

	//�Q�[���N���A�̃e�N�X�`���ǂݍ���
	m_pTexGameClear = new Texture;

	if (FAILED(m_pTexGameClear->Create("Assets/Texture/StageFinish/GameClear.png")))
	{
		MessageBox(NULL, "GameClear�ǂݍ��ݎ��s", "Error", MB_OK);
	}

	//�Q�[���I�[�o�[�̃e�N�X�`���ǂݍ���
	m_pTexGameOver = new Texture;
	if (FAILED(m_pTexGameOver->Create("Assets/Texture/StageFinish/GameOver.png")))
	{
		MessageBox(NULL, "GameOver�ǂݍ��ݎ��s", "Error", MB_OK);
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
	if		(0 >= *m_pPlayerHp && m_eGameState == GAME_PLAY)	
	{	//�^�C�}�[��0�ɂȂ�����N���A��ԂɑJ��

    m_bDispFlg = true;
		m_eGameState = GAME_OVER;
	}
	else if (0 >= *m_pTimeCnt && m_eGameState == GAME_PLAY)		
	{	//�̗͂�0�ɂȂ�����Q�[���I�[�o�[��ԂɑJ��
		m_bDispFlg = true;
		m_eGameState = GAME_CLEAR;
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
		std::string txt = "�ESHIFT�� �N���A�^�Q�[���I�[�o�[��UI�\����؂�ւ�";
		DirectWrite::DrawString(txt,DirectX::XMFLOAT2(0.0f,0.0f));
	}
	if (m_bDeleteDisp) { return; }	//�ז��Ȏ���UI��\�������ɏI��


	std::string txt;
	switch (m_eGameState)	//�Q�[���̏�Ԃɂ���ĕ���
	{
	case (GAME_PLAY):	//�Q�[�����v���C���̕`��

		break;
	case (GAME_CLEAR):	//�Q�[���N���A�̕`��

		//�s��ϊ����s���Ă���e�N�X�`�����Z�b�g���ĕ`��
		EditSprite();
		Sprite::SetTexture(m_pTexGameClear);
		Sprite::Draw();
		break;
	case (GAME_OVER):	//�Q�[���I�[�o�[�̕`��

		//�s��ϊ����s���Ă���e�N�X�`�����Z�b�g���ĕ`��
		EditSprite();
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
	�X�v���C�g�ݒ�֐�
	----------------------------------------
	���e�FUI�̕\���̐ݒ�
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStageFinish::EditSprite()
{
	DirectX::XMFLOAT4X4 matrix[3];

	//���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(SCREEN_WIDTH_ / 2, SCREEN_HEIGHT_ / 2, 0.0f);
	DirectX::XMStoreFloat4x4(&matrix[0], DirectX::XMMatrixTranspose(world));

	//�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	DirectX::XMStoreFloat4x4(&matrix[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2D�̃X�N���[���̑����������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH_, SCREEN_HEIGHT_, 0.0f, 0.1f, 10.0f);
	DirectX::XMStoreFloat4x4(&matrix[2], DirectX::XMMatrixTranspose(proj));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(matrix[0]);
	Sprite::SetView(matrix[1]);
	Sprite::SetProjection(matrix[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(SCALE_X, -SCALE_Y));

	//�ύX�͖�����Sprite���ÓI�Ȃ��ߑ��̏��ł̕ύX�𔽉f����Ȃ����߂ɖ߂�
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
}
