/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	SceneGame�������蔻��pcpp
	------------------------------------
	SceneGameCollision.cpp
	------------------------------------
	�쐬�� �m�}����

	�ύX����
	�E2023/11/07 �V�K�쐬 �m�}����
	�E2023/11/08 HammerSlimeCollision�֐�
				 SlimeSlimeCollision�֐�
				 ExplosionSlimeCollision�֐�
				 ���e�ǋL	�m�}����
========================================== */

// =============== �C���N���[�h ===================
#include "SceneGame.h"

// =============== �萔��` =======================

// =============== �v���g�^�C�v�錾 ===============

// =============== �O���[�o���ϐ���` =============


/* ========================================
   �֐��FSceneGameCollision�֐�
   ----------------------------------------
   ���e�FSceneGame�����蔻����܂Ƃ߂�֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::SceneGameCollision()
{
	PlayerSlimeCollision();
	HammerSlimeCollision();
	SlimeSlimeCollision();
	ExplosionSlimeCollision();
}

/* ========================================
   �֐��FPlayerSlimeCollision�֐�
   ----------------------------------------
   ���e�F�v���C���[�ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::PlayerSlimeCollision()
{
	if (m_pPlayer->GetCollide()) return;	//	���G���Ԃ̎��̓X���[

	// �X���C��
	for (int i = 0; i < MAX_SLIME; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// �X���C�����

		if (pSlimeNow == nullptr)				continue;	// �����ȃX���C���̓X���[

		// �X���C���ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetPlayerSphere(), pSlimeNow->GetSphere()))
		{
			m_pPlayer->Damage();
		}
	}
}

/* ========================================
   �֐��FHammerSlimeCollision�֐�
   ----------------------------------------
   ���e�F�n���}�[�ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::HammerSlimeCollision()
{
	CHammer* playerHammer = m_pPlayer->GetHammer();	// �v���C���[�̃n���}�[

	if (m_pPlayer->GetHammerFlg() == false) return;	// �n���}�[�U�����ĂȂ��ꍇ�͕Ԃ�

	// �X���C��
	for (int i = 0; i < MAX_SLIME; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// �X���C�����

		if (pSlimeNow == nullptr)				continue;	// �����ȃX���C���̓X���[
		if (pSlimeNow->GetHitMoveFlg()==true)	continue; 	// �����Ԃ̃X���C���̓X���[

		// �X���C���ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pSlimeNow->GetSphere()))
		{
			float fAngleSlime
				= m_pPlayer->GetPlayerSphere().Angle(pSlimeNow->GetSphere());	// �X���C������Ԋp�x���擾

			pSlimeNow->HitMoveStart(1.0,fAngleSlime);	// �X���C�����΂�
		}
	}
}

/* ========================================
   �֐��FSlimeSlimeCollision�֐�
   ----------------------------------------
   ���e�F�X���C���ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::SlimeSlimeCollision()
{
	// �Փ˂���X���C��
	for (int i = 0; i < MAX_SLIME; i++)
	{
		CSlimeBase* pSlimeFly = m_pSlimeMng->GetSlimePtr(i);	// �Փ˂���X���C���̃|�C���^

		if (pSlimeFly == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pSlimeFly->GetHitMoveFlg() == false)	continue; 	// �ʏ��Ԃ̃X���C���̓X���[

		// �Փ˂����X���C��
		for (int j = 0; j < MAX_SLIME; j++)
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pSlimeTarget == nullptr)	continue;	// �����ȃX���C���̓X���[
			if (i == j)						continue;	// �����Ɠ����X���C���̓X���[

			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pSlimeTarget->GetSphere()))
			{

				m_pSlimeMng->HitBranch(i, j,m_pExplosionMng);	// ���������A��������(�X���C�����m�̏��ɂ���ď�����ς���)
				break;
			}
		}

	}
}

/* ========================================
   �֐��FExplosionSlimeCollision�֐�
   ----------------------------------------
   ���e�F�����ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::ExplosionSlimeCollision()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; ++i)	// ����
	{
		CExplosion* pExplosion = m_pExplosionMng->GetExplosionPtr(i);	// �Փ˂��锚���̃|�C���^
		if (pExplosion == nullptr) { continue; }	// ���g�p�̔����̓X���[

		for (int j = 0; j < MAX_SLIME; ++j)	// �X���C��
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pSlimeTarget == nullptr)	continue;	// �����ȃX���C���̓X���[

			if (m_pCollision->CheckCollisionSphere(pExplosion->GetSphere(), pSlimeTarget->GetSphere()))
			{
				m_pSlimeMng->TouchExplosion(j, m_pExplosionMng);// �X���C���̔�������
				break;
			}
		}

	}
}