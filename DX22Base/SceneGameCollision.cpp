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
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/19 �X���C����ł�������SE�̍Đ� yamashita
	�E2023/11/20 ���������̈�����ύX
	�E2023/11/21 �{�X�p�̓����蔻��(SlimeBossCollision...etc)�𑽐��ǉ� Suzumura

========================================== */

// =============== �C���N���[�h ===================
#include "SceneGame.h"
#include "GameParameter.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float HAMMER_HIT_MOVE_SPEED = 1.0f;	// �n���}�[�ɔ�΂��ꂽ���̃X�s�[�h
const float SE_HAMMER_HIT_VOLUME = 0.5f;	// �X���C����ł�������SE�̉���

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
	PlayerBossCollision();
	HammerSlimeCollision();
	HammerBossCollision();
	SlimeSlimeCollision();
	SlimeBossCollision();
	BossSlimeCollision();
	BossBossCollision();
	ExplosionSlimeCollision();
	ExplosionBossCollision();
	BossBossNormalMoveCollision();
	SlimeBossNormalMoveCollision();
	BossSlimeNormalMoveCollision();
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
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetSphere(), pSlimeNow->GetSphere(), m_pPlayer->GetPos(), pSlimeNow->GetPos()))
		{
			m_pPlayer->Damage(pSlimeNow->GetAttack());
			return;
		}
	}
}

/* ========================================
   �v���C���[�{�X�����蔻��֐�
   ----------------------------------------
   ���e�F�v���C���[�ƃ{�X���Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::PlayerBossCollision()
{
	if (m_pPlayer->GetCollide()) return;	//	���G���Ԃ̎��̓X���[

	// �{�X�X���C��
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossNow = m_pSlimeMng->GetBossSlimePtr(i);	// �X���C�����

		if (pBossNow == nullptr)				continue;	// �����ȃX���C���̓X���[

		// �{�X�ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(m_pPlayer->GetSphere(), pBossNow->GetSphere(), m_pPlayer->GetPos(), pBossNow->GetPos()))
		{
			m_pPlayer->Damage(pBossNow->GetAttack());
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
	CHammer* playerHammer = m_pPlayer->GetHammerPtr();	// �v���C���[�̃n���}�[

	if (m_pPlayer->GetAttackFlg() == false) return;	// �n���}�[�U�����ĂȂ��ꍇ�͕Ԃ�

	// �X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeNow = m_pSlimeMng->GetSlimePtr(i);	// �X���C�����

		if (pSlimeNow == nullptr)				continue;	// �����ȃX���C���̓X���[
		if (pSlimeNow->GetHitMoveFlg()==true)	continue; 	// �����Ԃ̃X���C���̓X���[

		// �X���C���ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pSlimeNow->GetSphere(), playerHammer->GetPos(), pSlimeNow->GetPos()))
		{
			float fAngleSlime
				= m_pPlayer->GetTransform().Angle(pSlimeNow->GetTransform());	// �X���C������Ԋp�x���擾

			pSlimeNow->HitMoveStart(HAMMER_HIT_MOVE_SPEED,fAngleSlime);	// �X���C�����΂�

			m_pSEHitHammerSpeaker = CSound::PlaySound(m_pSEHitHammer);	//SE�̍Đ�
			m_pSEHitHammerSpeaker->SetVolume(SE_HAMMER_HIT_VOLUME);
		}
	}
}

/* ========================================
   �n���}�[�{�X�����蔻��֐�
   ----------------------------------------
   ���e�F�n���}�[�ƃ{�X���Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::HammerBossCollision()
{
	CHammer* playerHammer = m_pPlayer->GetHammerPtr();	// �v���C���[�̃n���}�[

	if (m_pPlayer->GetAttackFlg() == false) return;	// �n���}�[�U�����ĂȂ��ꍇ�͕Ԃ�

	// �{�X�X���C��
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossNow = m_pSlimeMng->GetBossSlimePtr(i);	// �X���C�����

		if (pBossNow == nullptr)				continue;	// �����ȃX���C���̓X���[
		if (pBossNow->GetHitMoveFlg() == true)	continue; 	// �����Ԃ̃X���C���̓X���[

		// �X���C���ƃn���}�[���Փ˂����ꍇ
		if (m_pCollision->CheckCollisionSphere(playerHammer->GetSphere(), pBossNow->GetSphere(), playerHammer->GetPos(), pBossNow->GetPos()))
		{
			float fAngleSlime
				= m_pPlayer->GetTransform().Angle(pBossNow->GetTransform());	// �X���C������Ԋp�x���擾

			pBossNow->HitMoveStart(HAMMER_HIT_MOVE_SPEED, fAngleSlime);	// �X���C�����΂�
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
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pSlimeTarget->GetSphere(), pSlimeFly->GetPos(), pSlimeTarget->GetPos()))
			{

				m_pSlimeMng->HitBranch(i, j,m_pExplosionMng);	// ���������A��������(�X���C�����m�̏��ɂ���ď�����ς���)
				break;
			}
		}

	}
}

/* ========================================
   �X���C�����{�X�̓����蔻��֐�(������)
   ----------------------------------------
   ���e�F�X���C������{�X�ɏՓ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::SlimeBossCollision()
{
	// �Փ˂���X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pSlimeFly = m_pSlimeMng->GetSlimePtr(i);	// �Փ˂���X���C���̃|�C���^

		if (pSlimeFly == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pSlimeFly->GetHitMoveFlg() == false)	continue; 	// �ʏ��Ԃ̃X���C���̓X���[

		// �Փ˂����{�X
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pBossTarget = m_pSlimeMng->GetBossSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pBossTarget == nullptr)					continue;	// �����ȃX���C���̓X���[
			if (pBossTarget->GetHitMoveFlg() == true)	continue; 	// �ʏ��Ԃ̃X���C���̓X���[

			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pSlimeFly->GetSphere(), pBossTarget->GetSphere(), pSlimeFly->GetPos(), pBossTarget->GetPos()))
			{

				m_pSlimeMng->HitSlimeBossBranch(i, j, m_pExplosionMng);	// ���������A��������(�X���C�����m�̏��ɂ���ď�����ς���)
				break;
			}
		}

	}
}
/* ========================================
   �{�X���X���C�������蔻��֐�(������)
   ----------------------------------------
   ���e�F�{�X�ƃX���C�����Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::BossSlimeCollision()
{
	// �Փ˂���{�X
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossFly = m_pSlimeMng->GetBossSlimePtr(i);	// �Փ˂���X���C���̃|�C���^

		if (pBossFly == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pBossFly->GetHitMoveFlg() == false)		continue; 	// �ʏ��Ԃ̃X���C���̓X���[

		// �Փ˂����X���C��
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pSlimeTarget = m_pSlimeMng->GetSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pSlimeTarget == nullptr)				continue;	// �����ȃX���C���̓X���[
			if (pSlimeTarget->GetHitMoveFlg() == true)	continue; 	// �ʏ��Ԃ̃X���C���̓X���[


			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pBossFly->GetSphere(), pSlimeTarget->GetSphere(), pBossFly->GetPos(), pSlimeTarget->GetPos()))
			{

				m_pSlimeMng->HitBossSlimeBranch(i, j, m_pExplosionMng);	// ���������A��������(�X���C�����m�̏��ɂ���ď�����ς���)
				break;
			}
		}

	}
}

/* ========================================
   �{�X���m�����蔻��֐�(������)
   ----------------------------------------
   ���e�F�{�X�ƃ{�X���Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::BossBossCollision()
{
	// �Փ˂���{�X
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pBossFly = m_pSlimeMng->GetBossSlimePtr(i);	// �Փ˂���X���C���̃|�C���^

		if (pBossFly == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pBossFly->GetHitMoveFlg() == false)		continue; 	// �ʏ��Ԃ̃X���C���̓X���[

		// �Փ˂����{�X
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pBossTarget = m_pSlimeMng->GetBossSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pBossTarget == nullptr)					continue;	// �����ȃX���C���̓X���[
			if (i == j)									continue;	// �����Ɠ����X���C���̓X���[
			if (pBossTarget->GetHitMoveFlg() == true)	continue; 	// �ʏ��Ԃ̃X���C���̓X���[


			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pBossFly->GetSphere(), pBossTarget->GetSphere(), pBossFly->GetPos(), pBossTarget->GetPos()))
			{

				m_pSlimeMng->HitBossBossBranch(i, j, m_pExplosionMng);	// ���������A��������(�X���C�����m�̏��ɂ���ď�����ς���)
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

			if (m_pCollision->CheckCollisionSphere(pExplosion->GetSphere(), pSlimeTarget->GetSphere(), pExplosion->GetPos(), pSlimeTarget->GetPos()))
			{
				m_pSlimeMng->TouchExplosion(j, m_pExplosionMng, pExplosion->GetComboNum());// �X���C���̔�������
				break;
			}
		}

	}
}

/* ========================================
   �����X���C���ƃ{�X�̓����蔻��֐�
   ----------------------------------------
   ���e�F�����ƃX���C��(�{�X)���Փ˂����ۂɍs������
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::ExplosionBossCollision()
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; ++i)	// ����
	{
		CExplosion* pExplosion = m_pExplosionMng->GetExplosionPtr(i);	// �Փ˂��锚���̃|�C���^
		if (pExplosion == nullptr) { continue; }	// ���g�p�̔����̓X���[

		for (int j = 0; j < MAX_BOSS_SLIME_NUM; ++j)	// �X���C��
		{
			CSlime_BossBase* pBossTarget = m_pSlimeMng->GetBossSlimePtr(j);	// �Փ˂����X���C���̃|�C���^

			if (pBossTarget == nullptr)	continue;	// �����ȃX���C���̓X���[

			if (m_pCollision->CheckCollisionSphere(pExplosion->GetSphere(), pBossTarget->GetSphere(), pExplosion->GetPos(), pBossTarget->GetPos()))
			{
				m_pSlimeMng->TouchBossExplosion(j, m_pExplosionMng,i);// �X���C���̔�������
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
			if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandSlime->GetSphere(), pMoveSlime->GetPos(), pStandSlime->GetPos()))
			{
				m_pSlimeMng->PreventSlimeSlimeOverlap(pMoveSlime, pStandSlime);	//�X���C���̈ʒu�������߂�����


				break;
			}
		}

	}
}

/* ========================================
   �X���C�����{�X�d���h�~�֐�
   ----------------------------------------
   ���e�F�X���C������{�X���ʏ�ړ��ŏd�Ȃ�Ȃ��悤�ɂ���֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::SlimeBossNormalMoveCollision()
{
	// �Փ˂���X���C��
	for (int i = 0; i < MAX_SLIME_NUM; i++)
	{
		CSlimeBase* pMoveSlime = m_pSlimeMng->GetSlimePtr(i);	//�ړ�����X���C���̃|�C���^

		if (pMoveSlime == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// ������ђ��̃X���C���̓X���[

		// �Փ˂����{�X
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pStandBoss = m_pSlimeMng->GetBossSlimePtr(j);	// �~�܂��Ă���X���C���̃|�C���^

			if (pStandBoss == nullptr)					continue;	// �����ȃX���C���̓X���[
			if (pMoveSlime->GetHitMoveFlg() == true)	continue;	// ������ђ��̃X���C���̓X���[

			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pMoveSlime->GetSphere(), pStandBoss->GetSphere(), pMoveSlime->GetPos(), pStandBoss->GetPos()))
			{
				m_pSlimeMng->PreventSlimeBossOverlap(pMoveSlime, pStandBoss);	//�X���C���̈ʒu�������߂�����


				break;
			}
		}

	}
}

/* ========================================
   �{�X���X���C���d���h�~�֐�
   ----------------------------------------
   ���e�F�{�X����X���C�����ʏ�ړ��ŏd�Ȃ�Ȃ��悤�ɂ���֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::BossSlimeNormalMoveCollision()
{
	// �Փ˂���{�X
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pMoveBoss = m_pSlimeMng->GetBossSlimePtr(i);	//�ړ�����X���C���̃|�C���^

		if (pMoveBoss == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// ������ђ��̃X���C���̓X���[

		// �Փ˂����X���C��
		for (int j = 0; j < MAX_SLIME_NUM; j++)
		{
			CSlimeBase* pStandSlime = m_pSlimeMng->GetSlimePtr(j);	// �~�܂��Ă���X���C���̃|�C���^

			if (pStandSlime == nullptr)					continue;	// �����ȃX���C���̓X���[
			if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// ������ђ��̃X���C���̓X���[

			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pMoveBoss->GetSphere(), pStandSlime->GetSphere(), pMoveBoss->GetPos(), pStandSlime->GetPos()))
			{
				m_pSlimeMng->PreventBossSlimeOverlap(pMoveBoss, pStandSlime);	//�X���C���̈ʒu�������߂�����


				break;
			}
		}

	}

}

/* ========================================
   �{�X���{�X�d���h�~�֐�
   ----------------------------------------
   ���e�F�{�X����{�X���ʏ�ړ��ŏd�Ȃ�Ȃ��悤�ɂ���֐�
   ----------------------------------------
   �����F�Ȃ�
   ----------------------------------------
   �ߒl�F�Ȃ�
   ======================================== */
void SceneGame::BossBossNormalMoveCollision()
{
	// �Փ˂���{�X
	for (int i = 0; i < MAX_BOSS_SLIME_NUM; i++)
	{
		CSlime_BossBase* pMoveBoss = m_pSlimeMng->GetBossSlimePtr(i);	//�ړ�����X���C���̃|�C���^

		if (pMoveBoss == nullptr)					continue;	// �����ȃX���C���̓X���[
		if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// ������ђ��̃X���C���̓X���[

		// �Փ˂����{�X
		for (int j = 0; j < MAX_BOSS_SLIME_NUM; j++)
		{
			CSlime_BossBase* pStandBoss = m_pSlimeMng->GetBossSlimePtr(j);	// �~�܂��Ă���X���C���̃|�C���^

			if (pStandBoss== nullptr)					continue;	// �����ȃX���C���̓X���[
			if (pMoveBoss->GetHitMoveFlg() == true)		continue;	// ������ђ��̃X���C���̓X���[
			if (i == j)									continue;	// �����Ɠ����X���C���̓X���[

			// �X���C�����m���Փ˂����ꍇ
			if (m_pCollision->CheckCollisionSphere(pMoveBoss->GetSphere(), pStandBoss->GetSphere(), pMoveBoss->GetPos(), pStandBoss->GetPos()))
			{
				m_pSlimeMng->PreventBossBossOverlap(pMoveBoss, pStandBoss);	//�X���C���̈ʒu�������߂�����


				break;
			}
		}

	}
}
