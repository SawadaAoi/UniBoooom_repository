/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   爆発管理
   ---------------------------------------
   ExplosionManager.h

   作成者 鄭 宇恩

   変更履歴
   ・2023/11/06 爆発マネージャークラス作成 /鄭　宇恩


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