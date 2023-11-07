/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �����Ǘ�
   ---------------------------------------
   ExplosionManager.cpp

   �쐬�� �A �F��

   �ύX����
   �E2023/11/06 �����}�l�[�W���[�N���X�쐬 /�A�@�F��
   �E2023/11/06 ���������A�폜�֐��쐬 / �A �F��

   ======================================== */
#include "ExplosionManager.h"
#include "Explosion.h"

CExplosion* g_pExplosion[MAX_EXPLOSION_NUM];

CExplosionManager::CExplosionManager()
{
	//����
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		g_pExplosion[i] = new CExplosion;
	}
}

CExplosionManager::~CExplosionManager()
{
	
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (g_pExplosion[i] != nullptr)
		{
			delete g_pExplosion[i];
			g_pExplosion[i] = nullptr;
		}
	}
}

/*========================================
�֐��FUpdate�֐�
----------------------------------------
���e�F�����}�l�[�W���[�̍X�V����
----------------------------------------
�����F�Ȃ�
----------------------------------------
�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::Update()
{

}


/*========================================
�֐��FExplosion�֐�
----------------------------------------
���e�F�����̏���
----------------------------------------
�����FTTriType<float>�X���C�������̈ʒu
	�Fbool������������
----------------------------------------
�ߒl�F��U�Ȃ�
======================================== */
void CExplosionManager::Explosion(TTriType<float> pos, bool bUnion)
{
	//�X���C�������A�ʒu�̕ϐ�
	//?
	
	//�������锻��
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		//�X���C�������������ǂ���
		if (bUnion)
		{
			g_pExplosion[i]->SetExplode(true);	//Explosion��true��
			g_pExplosion[i]->SetPos(pos);		//pos��ݒ�
		}
	}
}

/*========================================
�֐��FDeleteExplosion�֐�
----------------------------------------
���e�F�����̍폜
----------------------------------------
�����F�Ȃ�
----------------------------------------
�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::DeleteExplosion()
{
	int CntDeleteTime;
	CntDeleteTime++;
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (CntDeleteTime % 120 == 0)
		{
			g_pExplosion[i]->SetExplode(false);
		}
	}
}

/*========================================
�֐��FDraw�֐�
----------------------------------------
���e�F�����}�l�[�W���[�̕`�揈��
----------------------------------------
�����F�Ȃ�
----------------------------------------
�ߒl�F�Ȃ�
======================================== */
void CExplosionManager::Draw()
{
	
	//�����̕`��
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		bool bExploded = g_pExplosion[i]->GetExplode();
		if (!bExploded) continue;
		g_pExplosion[i]->Draw();
	}
}