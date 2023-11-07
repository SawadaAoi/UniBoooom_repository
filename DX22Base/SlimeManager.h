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
#include "SlimeBase.h"

enum E_SLIME_LEVEL
{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4
};

#define MAX_SLIME_1 20
#define MAX_SLIME_2 12
#define MAX_SLIME_3 8
#define MAX_SLIME_4 4

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Generate(TTriType<float> pos);

private:
	CSlimeBase* m_pSlime[MAX_SLIME_1];

	int m_nRandNum;	//乱数用
};

#endif // __SLIME_MANAGER_H__