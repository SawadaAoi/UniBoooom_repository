/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	�X�e�[�W�̓����蔻�菈������
	---------------------------------------
	CollisionOfStage.cpp

	�쐬��
			takagi
			nieda

	�ύX����
	�E2023/11/16 ���� takagi

========================================== */

// =============== �C���N���[�h ===================
#include "Stage.h"	//���g�̃w�b�_
#include "GameParameter.h"


/* ========================================
   �����蔻��܂Ƃߊ֐�
   ----------------------------------------
   ���e�FStage�����蔻����܂Ƃ߂�֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CStage::Collision()
{
	PlayerSlimeCollision();
	HammerSlimeCollision();
	SlimeSlimeCollision();
	ExplosionSlimeCollision();
	SlimeSlimeNormalMoveCollision();
}

/* ========================================
   �v���C���[�X���C�������蔻��֐�
   ----------------------------------------
   ���e�F�v���C���[�ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CStage::PlayerSlimeCollision()
{
	if (m_pPlayer->GetCollide()) return;	//	���G���Ԃ̎��̓X���[

	// �X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// �X���C�����

		if (pSlimeNow == nullptr)				continue;	// �����ȃX���C���̓X���[

		// �X���C���ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetSphere(), pSlimeNow->GetSphere(), m_pPlayer->GetPos(), pSlimeNow->GetPos()))
		{
			m_pPlayer->Damage();
		}
	}
}

/* ========================================
   �n���}�[�X���C�������蔻��֐�
   ----------------------------------------
   ���e�F�n���}�[�ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CStage::HammerSlimeCollision()
{
	CHammer* playerHammer = m_pPlayer->GetHammerPtr();	// �v���C���[�̃n���}�[

	if (m_pPlayer->GetAttackFlg() == false) return;	// �n���}�[�U�����ĂȂ��ꍇ�͕Ԃ�

	// �X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// �X���C�����

		if (pSlimeNow == nullptr)				continue;	// �����ȃX���C���̓X���[
		if (pSlimeNow->GetHitMoveFlg() == true)	continue; 	// �����Ԃ̃X���C���̓X���[

		// �X���C���ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pSlimeNow->GetSphere(), playerHammer->GetPos(), pSlimeNow->GetPos()))
		{
			float fAngleSlime
				= m_pPlayer->GetTransform().Angle(pSlimeNow->GetTransform());	// �X���C������Ԋp�x���擾

			pSlimeNow->HitMoveStart(HAMMER_HIT_MOVE_SPEED, fAngleSlime);	// �X���C�����΂�
		}
	}
}

/* ========================================
   �X���C�����m�����蔻��֐�(������)
   ----------------------------------------
   ���e�F�X���C���ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CStage::SlimeSlimeCollision()
{
	// �Փ˂���X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeFly = m_pSlimeMng->GetSlimePtr(i);	// �Փ˂���X���C���̃|�C���^

		if (pSlimeFly == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pSlimeFly->GetHitMoveFlg() == false)	continue; 	// �ʏ��Ԃ̃X���C���̓X���[

		// �Փ˂����X���C��
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pSlimeTarget == nullptr)	continue;	// �����ȃX���C���̓X���[
			if (i == j)						continue;	// �����Ɠ����X���C���̓X���[
			if (pSlimeTarget->GetHitMoveFlg() == true)	continue; 	// �ʏ��Ԃ̃X���C���̓X���[


			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pSlimeTarget->GetSphere(), pSlimeFly->GetPos(), pSlimeTarget->GetPos()))
			{

				m_pSlimeMng->HitBranch(i, j, m_pExplosionMng);	// ���������A��������(�X���C�����m�̏��ɂ���ď�����ς���)
				break;
			}
		}
	}
}

/* ========================================
   �����X���C�������蔻��֐�
   ----------------------------------------
   ���e�F�����ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CStage::ExplosionSlimeCollision()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; ++i)	// ����
	{
		CExplosion* pExplosion = m_pExplosionMng->GetExplosionPtr(i);	// �Փ˂��锚���̃|�C���^
		if (pExplosion == nullptr) { continue; }	// ���g�p�̔����̓X���[

		for (int j = 0; j < MAX_SLIME_NUM; ++j)	// �X���C��
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pSlimeTarget == nullptr)	continue;	// �����ȃX���C���̓X���[

			if (m_pCollision->CheckCollisionSphere(pExplosion->GetSphere(), pSlimeTarget->GetSphere(), pExplosion->GetPos(), pSlimeTarget->GetPos()))
			{
				m_pSlimeMng->TouchExplosion(j, m_pExplosionMng, pExplosion->GetComboNum());// �X���C���̔�������
				break;
			}
		}
	}
}

/* ========================================
   �X���C�����m�d���h�~�֐�
   ----------------------------------------
   ���e�F�X���C�����m���ʏ�ړ��ŏd�Ȃ�Ȃ��悤�ɂ���֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void CStage::SlimeSlimeNormalMoveCollision()
{
	// �Փ˂���X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pMoveSlime = m_pSlimeMng->GetSlimePtr(i);	//�ړ�����X���C���̃|�C���^

		if (pMoveSlime == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// ������ђ��̃X���C���̓X���[

		// �Փ˂����X���C��
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pStandSlime = m_pSlimeMng->GetSlimePtr(j);	// �~�܂��Ă���X���C���̃|�C���^

			if (pStandSlime == nullptr)					continue;	// �����ȃX���C���̓X���[
			if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// ������ђ��̃X���C���̓X���[
			if (i == j)									continue;	// �����Ɠ����X���C���̓X���[

			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandSlime->GetSphere(), pMoveSlime->GetPos(), pStandSlime->GetPos()))
			{
				m_pSlimeMng->PreventOverlap(pMoveSlime, pStandSlime);	//�X���C���̈ʒu�������߂�����

				break;
			}
		}
	}
}
