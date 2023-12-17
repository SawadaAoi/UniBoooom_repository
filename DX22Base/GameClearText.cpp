/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���X�^�[�g�`��
	---------------------------------------
	GameClearText.h

	�쐬��
			nieda

	�ύX����
	�E2023/12/17 �V�K�쐬 nieda

========================================== */

// =============== �C���N���[�h ===================
#include "GameClearText.h"	// ���g�̃w�b�_
#include "Defines.h"
#include "GameParameter.h"

// =============== �萔��` ===================
const int CLEAR_SPLIT_NUM_MAX = 45;				// �X�^�[�g��UI�A�j���[�V�����̕������̍ő吔
const TDiType<int> CLEAR_SPLIT_NUM = { 5, 9 };	// �X�^�[�g��UI�A�j���[�V�����̏c���������̍ő吔
const TPos2d<float> CLEAR_POS = { SCREEN_WIDTH_ / 2.0f, SCREEN_HEIGHT_ / 2.0f };		// �`��ʒu
const TDiType<float> CLEAR_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// �`��T�C�Y
const int CLEAR_SWITCH_CNT = 1;					// �A�j���[�V�����؂�ւ��Ԋu


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�J�����N���X�̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CClearText::CClearText(CCamera* pCamera)
	: CDrawAnim(CLEAR_SPLIT_NUM_MAX, CLEAR_SPLIT_NUM, CLEAR_SWITCH_CNT)
{
	//�Q�[���N���A�̕`�揀��
	SetTexture("Assets/Texture/StageFinish/finish.png");
	SetCamera(pCamera);
	SetPos({ CLEAR_POS.x, CLEAR_POS.y, 0.0f });
	SetSize({ CLEAR_SCALE.x, CLEAR_SCALE.y, 0.0f });
}