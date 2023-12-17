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
	�E2023/12/16 �`��ʒu�ǉ� nieda
	�E2023/12/16 DrawAnimation�̕ύX�𔽉f takagi

========================================== */

// =============== �C���N���[�h ===================
#include "DrawGameStart.h"	// ���g�̃w�b�_
#include "Defines.h"

// =============== �萔��` ===================
const int START_SPLIT_NUM_MAX = 60;				// �X�^�[�g��UI�A�j���[�V�����̕������̍ő吔
const TDiType<int> START_SPLIT_NUM = {5, 12};	// �X�^�[�g��UI�A�j���[�V�����̏c���������̍ő吔
const TPos2d<float> START_POS = {SCREEN_WIDTH / 2.0f + 50.0f, SCREEN_HEIGHT / 2.0f + 150.0f };		// �`��ʒu
const TDiType<float> START_SCALE = { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };					// �`��T�C�Y
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
	SetPos({ START_POS.x, START_POS.y, 0.0f });			//�ʒu������
	SetSize({ START_SCALE.x, START_SCALE.y, 0.0f });	//�T�C�Y������
}