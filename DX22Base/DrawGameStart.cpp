/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Q�[���X�^�[�g�`��
	---------------------------------------
	DrawAnimation.h

	�쐬��
			nieda

	�ύX����
	�E2023/12/12 �V�K�쐬 nieda
	�E2023/12/15 �Q�[���X�^�[�g�̃e�N�X�`����V�K�̂��̂ɕύX nieda
	�E2023/12/16 DrawAnimation�̕ύX�𔽉f takagi

========================================== */

// =============== �C���N���[�h ===================
#include "DrawGameStart.h"	// ���g�̃w�b�_
#include "GameParameter.h"

// =============== �萔��` ===================
const int START_SPLIT_NUM_MAX = 60;				// �X�^�[�g��UI�A�j���[�V�����̕������̍ő吔
const TDiType<int> START_SPLIT_NUM = {5, 12};	// �X�^�[�g��UI�A�j���[�V�����̏c���������̍ő吔
const TDiType<float> START_SCALE = { (float)SCREEN_WIDTH_, (float)SCREEN_HEIGHT_ };		// �\���T�C�Y
const int START_SWITCH_CNT = 1;					// �A�j���[�V�����؂�ւ��Ԋu


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�F�J�����N���X�̃|�C���^
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CDrawStart::CDrawStart(CCamera* pCamera)
	: CDrawAnim(START_SPLIT_NUM_MAX, START_SPLIT_NUM, START_SWITCH_CNT)
{
	SetTexture("Assets/Texture/Start_sprit.png");		//�e�N�X�`��������
	SetCamera(pCamera);									//�J�����o�^
	SetSize({ START_SCALE.x, START_SCALE.y, 0.0f });	//�T�C�Y������
}

