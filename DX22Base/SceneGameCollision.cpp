/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	SceneGame�������蔻��pcpp
	------------------------------------
	SceneGameCollision.cpp
	------------------------------------
	�쐬�� �m�}����

	�ύX����
	�E2023/11/07 �V�K�쐬 Nieda
	�E2023/11/08 �R�����g�C��	Nieda
	�E2023/11/12 �X���C�����m�d���h�~�֐��ǉ�	Yamashita

========================================== */

// =============== �C���N���[�h ===================
#include "SceneGame.h"
#include "GameParameter.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float HAMMER_HIT_MOVE_SPEED = 1.0f;		// �n���}�[�ɔ�΂��ꂽ���̃X�s�[�h

#endif 

// =============== �v���g�^�C�v�錾 ===============

// =============== �O���[�o���ϐ���` =============


/* ========================================
   �V�[���Q�[�������蔻��܂Ƃߊ֐�
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
void SceneGame::PlayerSlimeCollision()
{
	if (m_pPlayer->GetCollide()) return;	//	���G���Ԃ̎��̓X���[

	// �X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
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
   �n���}�[�X���C�������蔻��֐�
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
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// �X���C�����

		if (pSlimeNow == nullptr)				continue;	// �����ȃX���C���̓X���[
		if (pSlimeNow->GetHitMoveFlg()==true)	continue; 	// �����Ԃ̃X���C���̓X���[

		// �X���C���ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pSlimeNow->GetSphere()))
		{
			float fAngleSlime
				= m_pPlayer->GetPlayerSphere().Angle(pSlimeNow->GetSphere());	// �X���C������Ԋp�x���擾

			pSlimeNow->HitMoveStart(HAMMER_HIT_MOVE_SPEED,fAngleSlime);	// �X���C�����΂�
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
void SceneGame::SlimeSlimeCollision()
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
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pSlimeTarget->GetSphere()))
			{

				m_pSlimeMng->HitBranch(i, j,m_pExplosionMng);	// ���������A��������(�X���C�����m�̏��ɂ���ď�����ς���)
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
void SceneGame::ExplosionSlimeCollision()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; ++i)	// ����
	{
		CExplosion* pExplosion = m_pExplosionMng->GetExplosionPtr(i);	// �Փ˂��锚���̃|�C���^
		if (pExplosion == nullptr) { continue; }	// ���g�p�̔����̓X���[

		for (int j = 0; j < MAX_SLIME_NUM; ++j)	// �X���C��
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

/* ========================================
   �X���C�����m�d���h�~�֐�
   ----------------------------------------
   ���e�F�X���C�����m���ʏ�ړ��ŏd�Ȃ�Ȃ��悤�ɂ���֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::SlimeSlimeNormalMoveCollision()
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
			if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandSlime->GetSphere()))
			{
				m_pSlimeMng->PreventOverlap(pMoveSlime, pStandSlime);	//�X���C���̈ʒu�������߂�����


				break;
			}
		}

	}
}