/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�R�A�Ǘ��pcpp
	---------------------------------------
	TotalScore.cpp

	�쐬��	�R�{�M��

	�ύX����
	�E2023/11/22�@�쐬

========================================== */

// =============== �C���N���[�h ===================
#include "TotalScore.h"
#include "Sprite.h"

/* ========================================
	�֐��F�R���X�g���N�^
	-------------------------------------
	���e�F���s���ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTotalScore::CTotalScore()
	: m_nTotalScore(0)
	, m_pToScoreTexture(nullptr)
{
	m_pToScoreTexture = new Texture();
	if (FAILED(m_pToScoreTexture->Create("Assets/Texture/numbers_v1/combo_numbers.png")))
	{
		MessageBox(NULL, "ToScore�����ǂݍ���", "Error", MB_OK);
	}
}
/* ========================================
	�֐��F�f�X�g���N�^
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CTotalScore::~CTotalScore()
{
	SAFE_DELETE(m_pToScoreTexture);
}
/* ========================================
	�֐��F�`��֐�
	----------------------------------------
	���e�F�����}�l�[�W���[�̕`�揈��
	----------------------------------------
	�����F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CTotalScore::Draw()
{
	//DirectX::XMFLOAT4X4 time[3];
	//
	////���[���h�s���X��Y�݂̂��l�����č쐬(Z��10���炢�ɔz�u
	//DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(pos.x, pos.y, 0.0f);
	//DirectX::XMStoreFloat4x4(&time[0], DirectX::XMMatrixTranspose(world));
	//
	////�r���[�s���2D���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��i�P�ʍs��͌��
	//DirectX::XMStoreFloat4x4(&time[1], DirectX::XMMatrixIdentity());
	//
	////�v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	////���̍s���2D�̃X�N���[���̑����������܂�
	//DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);
	//DirectX::XMStoreFloat4x4(&time[2], DirectX::XMMatrixTranspose(proj));
	//
	////�X�v���C�g�̐ݒ�
	//Sprite::SetWorld(time[0]);
	//Sprite::SetView(time[1]);
	//Sprite::SetProjection(time[2]);
	//Sprite::SetSize(DirectX::XMFLOAT2(50.0f, -50.0f));
}
void CTotalScore::AddScore(int Score)
{
	m_nTotalScore += Score;
}
/* ========================================
	�g�[�^���X�R�A�擾�֐�
	----------------------------------------
	���e�F�g�[�^���X�R�A�̎擾
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�g�[�^���X�R�A�̐��l
======================================== */
int CTotalScore::GetTotalScore()
{
	return m_nTotalScore;
}
