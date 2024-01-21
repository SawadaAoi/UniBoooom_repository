/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���X�^�[�g�`��
	---------------------------------------
	GameOverText.h
	---------------------------------------
	�쐬��
			nieda

	�ύX����
	�E2023/12/17 �V�K�쐬 nieda
	�E2024/01/21 �R�����g���C takagi

========================================== */

// =============== �C���N���[�h ===================
#include "GameOverText.h"	// ���g�̃w�b�_
#include "Defines.h"
#include "GameParameter.h"

// =============== �萔��` ===================
const int OVER_SPLIT_NUM_MAX = 54;				// �X�^�[�g��UI�A�j���[�V�����̕������̍ő吔
const TDiType<int> OVER_SPLIT_NUM = { 6, 9 };	// �X�^�[�g��UI�A�j���[�V�����̏c���������̍ő吔
const TPos2d<float> OVER_POS = { SCREEN_WIDTH_ / 2.0f, SCREEN_HEIGHT_ / 2.0f };		// �`��ʒu
const TDiType<float> OVER_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// �`��T�C�Y
const int OVER_SWITCH_CNT = 1;


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�J�����N���X�̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
COverText::COverText(CCamera* pCamera)
	: CDrawAnim(OVER_SPLIT_NUM_MAX, OVER_SPLIT_NUM, OVER_SWITCH_CNT)
{
	SetTexture("Assets/Texture/StageFinish/GameOver.png");
	SetCamera(pCamera);
	SetPos({ OVER_POS.x, OVER_POS.y, 0.0f });
	SetSize({ OVER_SCALE.x, OVER_SCALE.y, 0.0f });
}
