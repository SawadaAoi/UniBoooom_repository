#ifndef __EXPLOSION_MANAGER_H__
#define __EXPLOSION_MANAGER_H__
/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   爆発管理
   ---------------------------------------
   ExplosionManager.h

   作成者 鄭 宇恩

   変更履歴
	・2023/11/06 爆発マネージャークラス作成 /鄭　宇恩
	・2023/11/09 爆発配列を返す処理の追加/ 澤田蒼生
	
========================================== */

// =============== インクルード ===================
#include "TriType.h"
#include "Explosion.h"

// =============== 定数定義 =======================
const int MAX_EXPLOSION_NUM = 20;

// =============== クラス定義 =====================
class CExplosionManager
{
public:
	// ===メンバ関数宣言===
	CExplosionManager();
	~CExplosionManager();

	void Update();
	void Draw();


	void Create(TTriType<float> pos);
	void DeleteCheck();

	CExplosion* GetExplosionPtr(int num);

protected:
	// ===メンバ変数宣言===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];
private:
};

#endif // __EXPLOSION_MANAGER_H__