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

#define MAX_SLIME_1 20
#define MAX_SLIME_2 12
#define MAX_SLIME_3 8
#define MAX_SLIME_4 4

const int MAX_SLIME = 20;	//スライムの最大生成数

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update();
	void Draw();
	void Generate(TTriType<float> pos);
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum);	//スライムの接触が起きた際の分岐処理
	void UnionSlime(E_SLIME_LEVEL level);							//スライムの結合処理
	
private:
	CSlimeBase* m_pSlime[MAX_SLIME_1];

	int m_nRandNum;	//乱数用
};

#endif // __SLIME_MANAGER_H__