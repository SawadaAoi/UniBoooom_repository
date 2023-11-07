/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �����Ǘ�
   ---------------------------------------
   ExplosionManager.h

   �쐬�� �A �F��

   �ύX����
   �E2023/11/06 �����}�l�[�W���[�N���X�쐬 /�A�@�F��


   ======================================== */
#ifndef __EXPLOSION_MANAGER_H__
#define __EXPLOSION_MANAGER_H__

#include "TriType.h"
#include "Explosion.h"

#define MAX_EXPLOSION_NUM 20

class CExplosionManager
{
public:
	CExplosionManager();
	~CExplosionManager();

	void Update();
	void Draw();
	void CreateExplosion(CSphereInfo::Sphere pos);
	void DeleteExplosion();
protected:

	CExplosionManager* m_pExplosionMng[MAX_EXPLOSION_NUM];
private:
};

#endif // __EXPLOSION_MANAGER_H__