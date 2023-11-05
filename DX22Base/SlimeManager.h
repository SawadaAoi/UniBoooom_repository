/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   スライムベース クラス定義
   ---------------------------------------
   SlimeManager.h

   作成者 鈴村 朋也

   変更履歴
   ・2023/11/05 スライムマネージャークラス作成 /鈴村 朋也


   ======================================== */
#ifndef __SLIME_MANAGER_H__
#define __SLIME_MANAGER_H__

#include "TriType.h"

#define MAX_SLIME_1 10

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Generate(TTriType<float> pos);

private:
	int m_nRandNum;	//乱数用
};

#endif // __SLIME_MANAGER_H__