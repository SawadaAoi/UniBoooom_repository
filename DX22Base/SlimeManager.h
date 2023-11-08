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
#include "Camera.h"



const int MAX_SLIME = 20;	//スライムの最大生成数

class CSlimeManager
{
public:
	CSlimeManager();
	~CSlimeManager();

	void Update(CSphereInfo::Sphere playerSphere);
	void Draw();
	void Generate(const TPos<float> pos);
	void HitBranch(int HitSlimeArrayNum,int standSlimeArrayNum);	//スライムの接触が起きた際の分岐処理
	void UnionSlime(E_SLIME_LEVEL level);							//スライムの結合処理
	CSlimeBase* GetSlimePtr(int num);

	void SetCamera(CCamera* pCamera);

private:
	int GetRandom(int min, int max);

	CSlimeBase* m_pSlime[MAX_SLIME];
	CCamera* m_pCamera;

	int m_GeneCnt;


	
};

#endif // __SLIME_MANAGER_H__