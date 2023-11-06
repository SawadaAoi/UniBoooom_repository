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

#define MAX_EXPLOSION_NUM 20

class CExplosionManager
{
public:
	CExplosionManager();
	~CExplosionManager();

	void Update();
	void Draw();
	void Explosion(TTriType<float> pos, bool bUnion);
	void DeleteExplosion();

private:
	
};

#endif // __EXPLOSION_MANAGER_H__