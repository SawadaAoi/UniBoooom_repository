/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�^�C�g���p�A�j���w�i����(�v���C���[�p�^�[��)
	---------------------------------------
	TitleBgPlayer.cpp

	�쐬��	takagi

	�ύX����
	�E2024/01/29 ���� takagi
	�E2024/02/06 ����i�s takagi
	�E2024/02/12 �e�N�X�`��delete�n�ύX takagi

========================================== */

// =============== �C���N���[�h ===================
#include "TitleBgPlayer.h"	//���g�̃w�b�_
#include "Defines.h"		//��ʏ��p
#include "Delete.h"			//�폜�}�N��

// =============== �萔��` ===================
const TPos3d<float> POS{ static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f, 0.0f };	//�ʒu
const TPos3d<float> SCALE(static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f);				//�������Ƃ��̑傫��
const int MAX_ANIM(55);																								//�A�j���[�V������
const TDiType<int> MAX_SEAT(5, 11);																					//5x11
const /*TODO:unsigned*/ int ANIMATION_INTERVAL = 2;																	//�A�j���[�V�����t���[���Ԋu
const unsigned int REST_FRAME = 180;																				//�A�j���[�V�����Ԃ̋x�~����

/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTitleBgPlayer::CTitleBgPlayer()
	:CDrawAnim(MAX_ANIM, MAX_SEAT, ANIMATION_INTERVAL)	//�Ϗ�
{
	// =============== ������ ===================
	SetPos(POS);										//�ʒu������
	SetSize(SCALE);										//�傫��������
	for (auto Iterator = LIST_ANIMATION_DUSH.begin(); Iterator != LIST_ANIMATION_DUSH.end(); Iterator++)
	{
		// =============== �ϐ��錾 ===================
		Texture* pTex;	//���X�g�ɓo�^����e�N�X�`���̃|�C���^

		// =============== ���I�m�� ===================
		pTex = new Texture;	//�|�C���^�̒��g�m��

		// =============== ������ ===================
		pTex->Create(Iterator->c_str());		//�e�N�X�`������

		// =============== �i�[ ===================
		m_pDushAnimeTexture.push_back(pTex);	//�e�N�X�`���i�[
	}
	m_DushAnimeIterator = m_pDushAnimeTexture.begin();	//�C�e���[�^������
	SetTexture(*m_DushAnimeIterator);					//�e�N�X�`���o�^
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
CTitleBgPlayer::~CTitleBgPlayer()
{
	// =============== �폜 ===================
	SAFE_DELETE_POINTER_VECTOR(m_pDushAnimeTexture);	//���X�g�폜
}

/* ========================================
	�X�V�֐�
	----------------------------------------
	���e�F�X�V����
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitleBgPlayer::Update()
{
	// =============== �x�~ ===================
	if (m_pCounter)	//�x�~��
	{
		m_pCounter->Count();	//�J�E���g�i�s
		if (m_pCounter->IsFin())	//�J�E���g����
		{
			m_pCounter.reset();		//�J�E���^�폜
		}

		// =============== �I�� ===================
		return;	//�������f
	}

	// =============== �X�V ===================
	CDrawAnim::Update();	//�e�̊֐��g�p
	if(!m_bAnim)	//�`�抮����
	{
		// =============== ������ ===================
		m_DushAnimeIterator++;						//�C�e���[�^�i�s
		//if (m_DushAnimeIterator != LIST_ANIMATION_DUSH.end())	//���X�g�͈̔͊O
		//{
		//	SetTexture(m_DushAnimeIterator->c_str());	//list�̃t�@�C���ǂݍ���

		//	// =============== �␳ ===================
		//	m_bAnim = true;								//�A�j���[�V�����`�����蒼��(�������������Ȃ�)	TODO:������₷������
		//}
		// =============== �␳ ===================
		if (m_DushAnimeIterator == m_pDushAnimeTexture.end())	//���X�g�͈̔͊O
		{
			m_DushAnimeIterator = m_pDushAnimeTexture.begin();	//�C�e���[�^�z��
		}
		SetTexture(*m_DushAnimeIterator);	//list�̃e�N�X�`���؊�

		m_bAnim = true;								//�A�j���[�V�����`�����蒼��(�������������Ȃ�)	TODO:������₷������

		// =============== ���I�m�� ===================
		m_pCounter = std::make_shared<CFrameCnt>(REST_FRAME);	//�x�~���ԃJ�E���^�쐬
	}
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	�����Fconst E_DRAW_MODE & eMode�F�`�惂�[�h
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CTitleBgPlayer::Draw(const E_DRAW_MODE& eMode)
{
	// =============== �`�� ===================
	if (!m_pCounter)	//�J�E���^���Ȃ���
	{
		CDrawAnim::Draw(eMode);	//�e�̊֐��g�p
	}
}