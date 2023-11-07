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
   �E2023/11/07 ���������֐����̕ύX�ADeleteExplosin()�̏C��/ �A �F��
   ======================================== */
#include "ExplosionManager.h"
#include "Explosion.h"
#include "Sphere.h"

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
�֐��FCreateExplosion�֐�
----------------------------------------
���e�F�����̐���
----------------------------------------
�����FCSphere::Sphere �X���C�������̈ʒu
----------------------------------------
�ߒl�F��U�Ȃ�
======================================== */
void CExplosionManager::Create()
{
	//�X���C�������A�ʒu�̕ϐ�
	//?
	
	//�������锻��
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		//�X���C�������������ǂ���
		g_pExplosion[i]->SetExplode(true);	//Explosion��true��
		&CSphere::Draw;
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
void CExplosionManager::Delete()
{
	int CntDeleteTime = 0;
	CntDeleteTime++;
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (CntDeleteTime % 120 == 0)
		{
			if(g_pExplosion[i]->GetExplode() == true)
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
		if (g_pExplosion[i]->GetExplode() == false) continue;
		g_pExplosion[i]->Draw();
	}
}