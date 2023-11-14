/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�Փ˔���pcpp
	---------------------------------------
	Collision.cpp

	�ύX����
	�E2023/11/05 �ύX���e
	�E2023/11/14 CheckCollisionSphere�֐��̈����ǉ� takagi

======================================== */

// =============== �C���N���[�h ===================
#include "Collision.h"	// ���g�̃w�b�_

/* ========================================
	���̏Փ˔���֐�
	-------------------------------------
	���e�F���̂̏Փ˔���
	-------------------------------------
	����1�F������ɍs�����̋��̂̏��i�\���́j
	-------------------------------------
	����2�F�������鑤�̋��̂̏��i�\���́j
	-------------------------------------
	����1�F������ɍs�����̕\���ʒu
	-------------------------------------
	����2�F�������鑤�̕\���ʒu
	-------------------------------------
	�ߒl�Ftrue �܂��� false
=========================================== */
bool CCOLLISION::CheckCollisionSphere(tagSphereInfo HitObj, tagSphereInfo NoMoveObj, TPos3d<float> fHitPos, TPos3d<float> fNoMovePos)
{
	TPos3d<float> HitCol = HitObj.GetCollisionPos(fHitPos);				//������ɍs�����̓����蔻��ʒu
	TPos3d<float> NoMoveCol = NoMoveObj.GetCollisionPos(fNoMovePos);	//�������鑤�̓����蔻��ʒu

	float Distance = HitCol.Distance(NoMoveCol);	// �I�u�W�F�N�g�Ԃ̋���

	if (Distance < HitObj.fRadius + NoMoveObj.fRadius)	// �I�u�W�F�N�g�Ԃ̋����̋��������a�̍��v��菬�����Ȃ�����
	{
		return true;	// �Փ˂��Ă���
	}

	return false;	// ����ȊO�͏Փ˂��Ă��Ȃ�
}