/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�|�[�Y��������
	---------------------------------------
	CharPause.cpp

	�쐬��	takagi

	�ύX����
	�E2023/12/09 ���� takagi
	�E2023/12/10 ����i�s takagi

========================================== */

// =============== �C���N���[�h ===================
#include "CharPause.h"	//���g�̃w�b�_
#include "GameParameter.h"

// =============== �萔��` ===================
const float AMPITUDE(25.0f);											//�U��
const float ANGLE_SPEED(DirectX::XMConvertToRadians(1.5f));				//�P�U���̊p���x
#if !MODE_GAME_PARAMETER
const float CHARA_WIDTH = 100.0f;										//�|�[�Y�\�L����
const float CHARA_HEIGHT = 100.0f;										//�|�[�Y�\�L�c��
#endif // !MODE_GAME_PARAMETER
const TPos3d<float> SCALE(CHARA_WIDTH, CHARA_HEIGHT, 0.0f);	//�傫��


/* ========================================
	�R���X�g���N�^
	----------------------------------------
	���e�F�������ɍs������
	----------------------------------------
	����1�Fconst int& nWaitTime�F�ҋ@����
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CCharPause::CCharPause(const int& nWaitTime)
	:m_fMoveAngle(0.0f)		//�ړ��p
	,CPauseObj(nWaitTime)	//�Ϗ�
{
	// =============== ������ ===================
	SetSize(SCALE);	//�傫��������
}

/* ========================================
	�ʒu�Z�o�֐�
	----------------------------------------
	���e�F�������Ŏ󂯎�����ʒu��\���ϐ��ɃY���𒼐ڔ��f����B
	----------------------------------------
	����1�FTPos3d<float>& fPos�F���ʂ��i�[�����A�ŏI�ڕW�ʒu�̏�񂪓������ϐ�
	----------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CCharPause::CulculatePos(TPos3d<float>& fPos)
{
	// =============== �Z�o ===================
	CPauseObj::CulculatePos(fPos);							//�e�̊֐��g�p
	fPos.y = m_fReach.y + AMPITUDE * sinf(m_fMoveAngle);	//�⊮

	// =============== �X�V ===================
	m_fMoveAngle += ANGLE_SPEED;	//�p�X�V
}