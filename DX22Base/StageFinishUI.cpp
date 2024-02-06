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
	�E2023/12/07 �����ŃV�[���J�ڂ����邽�߂̃t���O�擾�֐��ǉ� nieda
	�E2023/12/16 �A�j���[�V�����`�揑���ς� nieda
	�E2024/01/28 �����̗�����C�� Sawada


========================================== */
#include "DirectXTex/TextureLoad.h"		
#include "StageFinishUI.h"
#include "DirectWrite.h"
#include "Sprite.h"
#include "GameParameter.h"
#include "Input.h"


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
CStageFinish::CStageFinish(CCamera* pCamera, CPlayer* pPlayer, int* pTimeCnt)
	: m_eGameState(GAME_PLAY)
	, m_pPlayer(pPlayer)	// �v���C���[�̃|�C���^���Z�b�g
	, m_pTimeCnt(nullptr)
	, m_bGameEnd(false)
{
	m_pTimeCnt = pTimeCnt;		//�������Ԃ̃|�C���^���擾

	m_pClear = new CClearText(pCamera);
	m_pOver = new COverText(pCamera);
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
	SAFE_DELETE(m_pOver);
	SAFE_DELETE(m_pClear);

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
	switch (m_eGameState)
	{
	case CStageFinish::GAME_PLAY:
		ChangeGameState();

		break;

	case CStageFinish::GAME_CLEAR:	// �Q�[���N���A

		m_pClear->Update();
		// �A�j���[�V�������I��������
		if (!m_pClear->GetAnimFlg())
		{
			m_bGameEnd = true;
		}
		break;

	case CStageFinish::GAME_OVER:	// �Q�[���I�[�o�[

		m_pOver->Update();
		// �A�j���[�V�������I��������
		if (!m_pOver->GetAnimFlg())
		{
			m_bGameEnd = true;
		}
		break;
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
	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, nullptr);	//DSV��null����2D�\���ɂȂ�

	// �Q�[���̏�Ԃɂ���ĕ���
	switch (m_eGameState)	
	{
	case (GAME_PLAY):	//�Q�[�����v���C���̕`��
		break;
	case (GAME_CLEAR):	//�Q�[���N���A�̕`��
		m_pClear->Draw();
		break;
	case (GAME_OVER):	//�Q�[���I�[�o�[�̕`��
		m_pOver->Draw();
		break;
	}
}

/* ========================================
	�Q�[���V�[����ԕύX�֐�
	----------------------------------------
	���e�F�Q�[���N���Aor�I�[�o�[��Ԃɕω�����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CStageFinish::ChangeGameState()
{
	// �v���C���[�����S������
	if (m_pPlayer->GetDieFlg())
	{
		m_eGameState = GAME_OVER;	// �Q�[���I�[�o�[
	}
	// �������ԃ^�C�}�[���I��������
	else if ( *m_pTimeCnt <= 0 )
	{
		m_eGameState = GAME_CLEAR;	// �Q�[���N���A
	}

}

/* ========================================
	��ʑJ�ڃt���O�擾�֐�
	----------------------------------------
	���e�F��ʑJ�ڃt���O�̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Ftrue:�V�[���J�ڂ��� / false:�V�[���J�ڂ��Ȃ�
=========================================== */
bool CStageFinish::GetGameEndFlg()
{
	return m_bGameEnd;
}

/* ========================================
	�Q�[���N���A�t���O�擾�֐�
	----------------------------------------
	���e�F�Q�[���N���A�t���O�̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�Ftrue:�Q�[���N���A / false:�Q�[���N���A���Ă��Ȃ�
=========================================== */
bool CStageFinish::GetClearFlg()
{
	// �Q�[����Ԃ��Q�[���N���A�ɂȂ��Ă��邩
	if (m_eGameState == CStageFinish::GAME_CLEAR)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


