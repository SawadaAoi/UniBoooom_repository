#ifndef __EXPLOSION_MANAGER_H__
#define __EXPLOSION_MANAGER_H__
/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �����Ǘ�
   ---------------------------------------
   ExplosionManager.h

   �쐬�� �A �F��

   �ύX����
   �E2023/11/06 �����}�l�[�W���[�N���X�쐬 /�A�@�F��
	
========================================== */

// =============== �C���N���[�h ===================
#include "TriType.h"
#include "Explosion.h"

// =============== �萔��` =======================
const int MAX_EXPLOSION_NUM = 20;

// =============== �N���X��` =====================
class CExplosionManager
{
public:
	// ===�����o�֐��錾===
	CExplosionManager();
	~CExplosionManager();

	void Update();
	void Draw();


	void Create(TTriType<float> pos);
	void DeleteCheck();
protected:
	// ===�����o�ϐ��錾===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];
private:
};

#endif // __EXPLOSION_MANAGER_H__